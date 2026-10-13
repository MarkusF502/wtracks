#include "AudioEngine.h"
#include <vector>
using namespace wtracks;

// Trimmed song-map areas: sample-exact jumps with a decoded bridge, cues inside do not fire, seek lands after the area.
class TrimTests : public juce::UnitTest {
public:
    TrimTests() : juce::UnitTest("Trimmed areas", "Audio") {}

    static float sample(int frame) { return static_cast<float>((frame % 997) + 1) / 2000.0f; }
    static juce::File ramp(const juce::File& dir, int frames) {
        auto file = dir.getChildFile("ramp.wav"); juce::WavAudioFormat format;
        auto stream = std::unique_ptr<juce::FileOutputStream>(file.createOutputStream());
        std::unique_ptr<juce::AudioFormatWriter> writer(format.createWriterFor(stream.get(), 48000, 2, 32, {}, 0)); stream.release();
        juce::AudioBuffer<float> data(2, frames);
        for (int i = 0; i < frames; ++i) { data.setSample(0, i, sample(i)); data.setSample(1, i, sample(i)); }
        writer->writeFromAudioSampleBuffer(data, 0, frames); writer.reset(); return file;
    }
    static std::vector<float> render(AudioEngine& engine, int total, int block) {
        std::vector<float> out; juce::AudioBuffer<float> buffer(2, block);
        for (int done = 0; done < total; done += block) {
            engine.waitForReadAhead(block, 2000);  // stands in for real time: the streams refill while the bridge plays
            const int n = std::min(block, total - done); juce::AudioSourceChannelInfo info(&buffer, 0, n); engine.getNextAudioBlock(info);
            for (int i = 0; i < n; ++i) out.push_back(buffer.getSample(0, i));
        }
        return out;
    }

    void runTest() override {
        auto dir = juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_trim", "", false); dir.createDirectory();
        auto file = ramp(dir, 10 * 48000);
        constexpr double rate = 48000;

        beginTest("Playback jumps over trimmed areas sample-exactly, through the bridge and back to streaming, any block size");
        for (int block : {64, 500, 1024}) {
            AudioEngine engine; engine.prepareToPlay(block, rate); expect(engine.loadTrack("trim", {file}));
            const double starts[2] = {24000 / rate, 300000 / rate}, ends[2] = {48000 / rate, 300100 / rate};
            expect(engine.configureSkips(starts, ends, 2)); engine.play();
            const int total = 24000 + 48000 * 4; const auto out = render(engine, total, block);
            for (int i = 0; i < total; ++i) {
                const int frame = i < 24000 ? i : (i + 24000 < 300000 ? i + 24000 : i + 24100);
                if (std::fabs(out[static_cast<size_t>(i)] - sample(frame)) > 1e-5f) { expect(false, "block " + juce::String(block) + " out " + juce::String(i)); break; }
            }
            expectEquals(engine.getUnderrunCount(), uint64_t(0));
        }

        beginTest("Cues inside a trimmed area do not fire; seeking into it lands at its end; loops ignore trims");
        {
            AudioEngine engine; engine.prepareToPlay(64, rate); expect(engine.loadTrack("trim", {file}));
            const double a = 1.0, b = 2.0; expect(engine.configureSkips(&a, &b, 1));
            const double times[3] = {0.5, 1.5, 2.5}; const uint8_t bytes[9] = {0}; const uint8_t sizes[3] = {0, 0, 0};
            expect(engine.configureCues(times, bytes, sizes, 3)); engine.play(); render(engine, 48000 * 2, 64);
            uint32_t fired[8]; const int n = engine.pollCues(fired, 8);
            expectEquals(n, 2); expect(fired[0] == 0 && fired[1] == 2);
            engine.seekToSeconds(1.2); expectWithinAbsoluteError(engine.getCurrentPositionSeconds(), 2.0, 1e-9);
            expect(engine.setLoop(0.5, 1.5, true)); engine.seekToSeconds(0.9); render(engine, 48000, 64);
            expect(engine.getCurrentPositionSeconds() >= 0.5 && engine.getCurrentPositionSeconds() < 1.5);
        }

        beginTest("Validation and lifetime: order, bounds, count; new songs and time scales drop the areas");
        {
            AudioEngine engine; engine.prepareToPlay(64, rate); const double a[2] = {1, 0.5}, b[2] = {2, 3};
            expect(!engine.configureSkips(a, b, 1));  // no song
            expect(engine.loadTrack("trim", {file}));
            expect(!engine.configureSkips(a, b, 2)); const double late = 11, later = 12; expect(!engine.configureSkips(&late, &later, 1));
            const double s0 = 2, e0 = 2; expect(!engine.configureSkips(&s0, &e0, 1)); expect(!engine.configureSkips(a, b, 33));
            const double end0 = 9.5, end1 = 10.0; expect(engine.configureSkips(&end0, &end1, 1));  // up to the end: no bridge needed
            engine.seekToSeconds(9.4); engine.play(); render(engine, 48000, 64); expect(!engine.isPlaying());
            expect(engine.configureSkips(a, b, 1)); expect(engine.setTimeScale(1.5)); engine.seekToSeconds(1.2 * 1.0);
            expectWithinAbsoluteError(engine.getCurrentPositionSeconds(), 1.2, 1e-6);
            expect(engine.configureSkips(nullptr, nullptr, 0));
        }
        dir.deleteRecursively();
    }
} trimTests;
