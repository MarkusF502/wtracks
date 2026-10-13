#include "AudioEngine.h"
#include "TimePitchFile.h"
#include <vector>
using namespace wtracks;

// Processed (time-stretched) stems: the engine keeps exposing song time, and the offline file renderer.
class TimeScaleTests : public juce::UnitTest {
public:
    TimeScaleTests() : juce::UnitTest("Time scale and offline file processing", "Audio") {}

    static juce::File wav(const juce::File& dir, const juce::String& name, double rate, int channels, int frames, float (*gen)(int, int)) {
        auto file = dir.getChildFile(name); juce::WavAudioFormat format;
        auto stream = std::unique_ptr<juce::FileOutputStream>(file.createOutputStream());
        std::unique_ptr<juce::AudioFormatWriter> writer(format.createWriterFor(stream.get(), rate, static_cast<unsigned>(channels), 24, {}, 0)); stream.release();
        juce::AudioBuffer<float> data(channels, frames);
        for (int ch = 0; ch < channels; ++ch) for (int i = 0; i < frames; ++i) data.setSample(ch, i, gen(ch, i));
        writer->writeFromAudioSampleBuffer(data, 0, frames); writer.reset(); return file;
    }
    static void render(AudioEngine& engine, int total, int block, std::vector<float>& l) {
        l.assign(static_cast<size_t>(total), 0.f); juce::AudioBuffer<float> out(2, block); int offset = 0;
        while (offset < total) {
            const int count = juce::jmin(block, total - offset); juce::AudioSourceChannelInfo info(&out, 0, count); engine.getNextAudioBlock(info);
            for (int i = 0; i < count; ++i) l[static_cast<size_t>(offset + i)] = out.getSample(0, i);
            offset += count;
        }
    }

    void runTest() override {
        constexpr double rate = 48000;
        auto dir = juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_scale", "", false); dir.createDirectory();
        auto silence = wav(dir, "silence.wav", rate, 2, 96000, [](int, int) { return 0.f; });
        auto marks = wav(dir, "marks.wav", rate, 2, 96000, [](int, int i) { return i % 1000 == 0 ? 0.5f : 0.f; });
        auto pulse = wav(dir, "pulse.wav", rate, 1, 1, [](int, int) { return 0.8f; });

        beginTest("Position, length, seek and loops are reported in song time");
        {
            AudioEngine engine; engine.prepareToPlay(256, rate); expect(engine.loadTrack("scaled", {marks}));
            expectEquals(engine.getTimeScale(), 1.0);
            for (double bad : {0.0, 0.2, 4.5, -1.0, std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::infinity()}) expect(!engine.setTimeScale(bad));
            expect(engine.setTimeScale(2.0));
            expectWithinAbsoluteError(engine.getTotalLengthSeconds(), 1.0, 1e-9);
            engine.seekToSeconds(0.25); expectWithinAbsoluteError(engine.getCurrentPositionSeconds(), 0.25, 1.0 / rate);
            engine.seekToSeconds(99); expectWithinAbsoluteError(engine.getCurrentPositionSeconds(), 1.0, 1.0 / rate);
            // Song-time loop 0.1..0.2 = processed frames 9600..19200.
            expect(engine.setLoop(0.1, 0.2, true)); double state[6]; engine.getLoopState(state);
            expectEquals(state[0], 1.0); expectWithinAbsoluteError(state[1], 0.1, 1e-9); expectWithinAbsoluteError(state[2], 0.2, 1e-9);
            expectWithinAbsoluteError(engine.getLoopStart(), 0.1, 1e-9); expectWithinAbsoluteError(engine.getLoopEnd(), 0.2, 1e-9);
            engine.seekToSeconds(0.1); engine.play(); std::vector<float> l; render(engine, 2 * 9600, 100, l);
            for (int i = 0; i < 2 * 9600; ++i) expectWithinAbsoluteError(l[static_cast<size_t>(i)], ((9600 + i % 9600) % 1000 == 0) ? 0.5f : 0.f, 1e-5f);
            expect(engine.enqueueLoop(0.5, 1.0)); expectWithinAbsoluteError(engine.getQueuedLoopEnd(), 1.0, 1e-9); // song end round trip is accepted
            expect(!engine.enqueueLoop(0.5, 1.01));
            engine.stop();
            // setTimeScale discards loops; loadTrack resets the scale.
            expect(engine.setLoop(0.1, 0.2, true)); expect(engine.setTimeScale(1.5)); expect(!engine.getLoopEnabled());
            expect(engine.loadTrack("again", {silence})); expectEquals(engine.getTimeScale(), 1.0); expectWithinAbsoluteError(engine.getTotalLengthSeconds(), 2.0, 1e-9);
            expect(engine.setTimeScale(2.0)); engine.unloadCurrentTrack(); expectEquals(engine.getTimeScale(), 1.0);
        }

        beginTest("Click beats and guide cues are placed on the processed timeline");
        {
            AudioEngine engine; engine.prepareToPlay(256, rate); expect(engine.loadTrack("click", {silence}));
            expect(engine.configureClick(120, 4, 4, 4, 0.0, 1, 1, 0, 0)); expect(engine.loadClickSound(0, pulse.getFullPathName()));
            engine.setClickEnabled(true); expect(engine.setTimeScale(2.0));
            // Song-time 120 BPM, 4/4: the downbeat repeats every 2 s of song time = 4 s processed; beat 2 is at 1 s processed.
            engine.play(); std::vector<float> l; render(engine, 96000, 256, l);
            expectWithinAbsoluteError(l[0], 0.8f, 1e-5f);
            float beforeBeat2 = 0; for (int i = 1; i < 47900; ++i) beforeBeat2 = std::max(beforeBeat2, std::fabs(l[static_cast<size_t>(i)]));
            expectEquals(beforeBeat2, 0.f); // nothing at the unscaled 24000
            float atBeat2 = 0; for (int i = 47990; i < 48100; ++i) atBeat2 = std::max(atBeat2, std::fabs(l[static_cast<size_t>(i)]));
            expect(atBeat2 > 0.f, "second beat at 1 s processed");
            // Offset and BPM changes keep the same song-time meaning.
            engine.setClickOffsetSeconds(0.25); engine.stop(); engine.play(); render(engine, 48000, 256, l);
            expectEquals(juce::FloatVectorOperations::findMaximum(l.data(), 23999), 0.f); expectWithinAbsoluteError(l[24000], 0.8f, 1e-5f);

            const char* path = nullptr; juce::String text = pulse.getFullPathName(); const auto utf8 = text.toStdString(); path = utf8.c_str();
            const double time = 0.1; const float gain = 1.f;
            expect(engine.configureGuides(&time, &path, &gain, 1)); engine.setGuidesEnabled(true); engine.setClickEnabled(false);
            engine.stop(); engine.play(); render(engine, 20000, 256, l);
            expectEquals(l[9599], 0.f); expectWithinAbsoluteError(l[9600], 0.8f, 1e-5f);
            const double late = 1.1; expect(!engine.configureGuides(&late, &path, &gain, 1)); // beyond the song end (1 s of song time)
            expect(engine.setTimeScale(1.0)); engine.stop(); engine.play(); render(engine, 6000, 256, l); expectWithinAbsoluteError(l[4800], 0.8f, 1e-5f);
        }

        beginTest("processTimePitchFile renders atomically, preserves format and honours cancel/invalid input");
        {
            auto tone = wav(dir, "tone.wav", 44100, 2, 44100, [](int ch, int i) { return 0.4f * std::sin(2 * 3.14159265f * (ch ? 660.f : 440.f) * static_cast<float>(i) / 44100.f); });
            auto out = dir.getChildFile("tone-slow.wav");
            auto result = processTimePitchFile(tone, out, {1.5, 1.0, true}, 11);
            expect(result.ok, result.error); expect(out.existsAsFile()); expect(!dir.getChildFile("tone-slow.wav.part").exists());
            juce::AudioFormatManager formats; formats.registerBasicFormats();
            std::unique_ptr<juce::AudioFormatReader> reader(formats.createReaderFor(out));
            expect(reader != nullptr);
            if (reader) { expectEquals(reader->sampleRate, 44100.0); expectEquals<int>(static_cast<int>(reader->numChannels), 2);
                expectEquals<int64_t>(reader->lengthInSamples, std::llround(44100 * 1.5)); expectEquals<int>(reader->bitsPerSample, 32); expect(reader->usesFloatingPointData); }
            const auto before = out.getSize(); const auto stamp = out.getLastModificationTime();
            for (auto bad : {timepitch::Options{0.1, 1, true}, timepitch::Options{1, 3, true}}) expect(!processTimePitchFile(tone, out, bad, 12).ok);
            expect(!processTimePitchFile(dir.getChildFile("missing.wav"), out, {1.2, 1, true}, 13).ok);
            expect(!processTimePitchFile(tone, tone, {1.2, 1, true}, 14).ok);
            expect(!processTimePitchFile(dir.getChildFile("silence.wav.txt"), out, {1.2, 1, true}, 15).ok);
            cancelTimePitch(16); auto cancelled = processTimePitchFile(tone, out, {1.2, 1.1, true}, 16);
            expect(!cancelled.ok && cancelled.cancelled); expectEquals<int64_t>(out.getSize(), before); expect(out.getLastModificationTime() == stamp);
            expect(!dir.getChildFile("tone-slow.wav.part").exists());
            auto text = dir.getChildFile("notes.txt"); text.replaceWithText("not audio"); expect(!processTimePitchFile(text, out, {1.2, 1, true}, 17).ok);
        }
        dir.deleteRecursively();
    }
};
static TimeScaleTests timeScaleTests;
