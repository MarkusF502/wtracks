#include "AudioEngine.h"
#include <vector>
using namespace wtracks;

// Counted section loops: N passes from the cache, then playback continues seamlessly after the loop end.
class CountedLoopTests : public juce::UnitTest {
public:
    CountedLoopTests() : juce::UnitTest("Counted section loops", "Audio") {}
    static float sample(int frame) { return frame % 13 == 0 ? 0.5f : (frame % 7 == 0 ? 0.25f : 0.f); }

    void runTest() override {
        constexpr double rate = 48000; constexpr int frames = 48000;
        auto dir = juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_counted", "", false); dir.createDirectory();
        auto file = dir.getChildFile("marks.wav");
        { juce::WavAudioFormat wav; auto stream = std::unique_ptr<juce::FileOutputStream>(file.createOutputStream());
          std::unique_ptr<juce::AudioFormatWriter> writer(wav.createWriterFor(stream.get(), rate, 2, 24, {}, 0)); stream.release();
          juce::AudioBuffer<float> data(2, frames); for (int i = 0; i < frames; ++i) { data.setSample(0, i, sample(i)); data.setSample(1, i, sample(i)); }
          writer->writeFromAudioSampleBuffer(data, 0, frames); }
        auto render = [&](AudioEngine& engine, int total, int block) {
            std::vector<float> out; juce::AudioBuffer<float> buffer(2, block);
            for (int done = 0; done < total; done += block) { const int n = std::min(block, total - done); juce::AudioSourceChannelInfo info(&buffer, 0, n); engine.getNextAudioBlock(info);
                for (int i = 0; i < n; ++i) out.push_back(buffer.getSample(0, i)); }
            return out;
        };

        beginTest("N passes, then the stream continues exactly after the loop end for any block size");
        for (int repeats : {1, 2, 3, 7}) for (int block : {64, 100, 1024}) {
            AudioEngine engine; engine.prepareToPlay(block, rate); expect(engine.loadTrack("counted", {file}));
            expect(engine.setLoop(1000 / rate, 1137 / rate, true, repeats)); engine.seekToSeconds(1000 / rate); expect(engine.waitForReadAhead(block, 2000)); engine.play();
            const int total = 137 * repeats + 600; const auto out = render(engine, total, block);
            for (int i = 0; i < total; ++i) {
                const int frame = i < 137 * repeats ? 1000 + i % 137 : 1137 + (i - 137 * repeats);
                if (std::fabs(out[static_cast<size_t>(i)] - sample(frame)) > 1e-5f) { expect(false, "repeats " + juce::String(repeats) + " block " + juce::String(block) + " frame " + juce::String(i)); break; }
            }
            expect(!engine.getLoopEnabled()); expectEquals(engine.getUnderrunCount(), uint64_t(0));
            expectWithinAbsoluteError(engine.getCurrentPositionSeconds(), (1137 + 600) / rate, 1.0 / rate);
        }

        beginTest("Loop pass counter: 1-based pass and the repeat count, also for infinite loops");
        {
            AudioEngine engine; engine.prepareToPlay(64, rate); expect(engine.loadTrack("counted", {file}));
            int pass = -1, repeats = -1; engine.getLoopPass(&pass, &repeats); expect(pass == 0 && repeats == 0);
            expect(engine.setLoop(1000 / rate, 1137 / rate, true, 3)); engine.seekToSeconds(1000 / rate); engine.play();
            engine.getLoopPass(&pass, &repeats); expect(pass == 1 && repeats == 3);
            render(engine, 137 + 10, 64); engine.getLoopPass(&pass, &repeats); expect(pass == 2 && repeats == 3);
            render(engine, 137 * 2, 64); engine.getLoopPass(&pass, &repeats); expect(pass == 0 && repeats == 0);  // released
            expect(engine.setLoop(1000 / rate, 1137 / rate, true)); engine.seekToSeconds(1000 / rate); render(engine, 137 * 4 + 10, 64);
            engine.getLoopPass(&pass, &repeats); expect(pass == 5 && repeats == 0);
        }

        beginTest("Infinite loops are unchanged; invalid counts are rejected without touching the loop");
        {
            AudioEngine engine; engine.prepareToPlay(256, rate); expect(engine.loadTrack("counted", {file}));
            expect(engine.setLoop(1000 / rate, 1137 / rate, true)); engine.play(); render(engine, 137 * 20, 256); expect(engine.getLoopEnabled());
            expect(!engine.setLoop(1000 / rate, 1137 / rate, true, -1)); expect(!engine.setLoop(1000 / rate, 1137 / rate, true, 1001)); expect(engine.getLoopEnabled());
            expect(!engine.enqueueLoop(2000 / rate, 2137 / rate, 5000)); expect(!engine.getQueuedLoopEnabled());
        }

        beginTest("Seeking inside a counted loop keeps the continuation parked at the loop end");
        {
            AudioEngine engine; engine.prepareToPlay(128, rate); expect(engine.loadTrack("counted", {file}));
            expect(engine.setLoop(1000 / rate, 1137 / rate, true, 2)); engine.play(); render(engine, 200, 128);
            engine.seekToSeconds(1100 / rate); expect(engine.waitForReadAhead(128, 2000)); engine.play();
            const auto out = render(engine, 37 + 137 + 300, 128);  // rest of the first pass, one more pass, then 300 frames after the end
            for (int i = 0; i < 37 + 137 + 300; ++i) {
                const int frame = i < 37 ? 1100 + i : (i < 37 + 137 ? 1000 + (i - 37) : 1137 + (i - 174));
                if (std::fabs(out[static_cast<size_t>(i)] - sample(frame)) > 1e-5f) { expect(false, "seek frame " + juce::String(i)); break; }
            }
        }

        beginTest("A queued counted loop takes over at the boundary with its own count");
        {
            AudioEngine engine; engine.prepareToPlay(256, rate); expect(engine.loadTrack("counted", {file}));
            expect(engine.setLoop(1000 / rate, 1137 / rate, true)); expect(engine.enqueueLoop(2000 / rate, 2050 / rate, 2));
            engine.play(); const auto out = render(engine, 137 + 50 * 2 + 80, 256);
            for (int i = 137; i < 137 + 100; ++i) expectWithinAbsoluteError(out[static_cast<size_t>(i)], sample(2000 + (i - 137) % 50), 1e-5f);
            for (int i = 237; i < 317; ++i) expectWithinAbsoluteError(out[static_cast<size_t>(i)], sample(2050 + (i - 237)), 1e-5f);  // the queued loop finished its two passes
            double state[6]; engine.getLoopState(state); expectEquals(state[0], 0.0);
        }
        dir.deleteRecursively();
    }
};
static CountedLoopTests countedLoopTests;

// Preset loops engage by themselves at a section start.
class PresetLoopTests : public juce::UnitTest {
public:
    PresetLoopTests() : juce::UnitTest("Preset section loops", "Audio") {}
    static float sample(int frame) { return frame % 13 == 0 ? 0.5f : (frame % 7 == 0 ? 0.25f : 0.f); }
    void runTest() override {
        constexpr double rate = 48000; constexpr int frames = 48000;
        auto dir = juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_preset", "", false); dir.createDirectory();
        auto file = dir.getChildFile("marks.wav");
        { juce::WavAudioFormat wav; auto stream = std::unique_ptr<juce::FileOutputStream>(file.createOutputStream());
          std::unique_ptr<juce::AudioFormatWriter> writer(wav.createWriterFor(stream.get(), rate, 2, 24, {}, 0)); stream.release();
          juce::AudioBuffer<float> data(2, frames); for (int i = 0; i < frames; ++i) { data.setSample(0, i, sample(i)); data.setSample(1, i, sample(i)); }
          writer->writeFromAudioSampleBuffer(data, 0, frames); }
        auto render = [&](AudioEngine& engine, int total, int block) {
            std::vector<float> out; juce::AudioBuffer<float> buffer(2, block);
            for (int done = 0; done < total; done += block) { const int n = std::min(block, total - done); juce::AudioSourceChannelInfo info(&buffer, 0, n); engine.getNextAudioBlock(info);
                for (int i = 0; i < n; ++i) out.push_back(buffer.getSample(0, i)); }
            return out;
        };
        auto check = [&](const std::vector<float>& out, int from, std::function<int(int)> frameFor, const juce::String& label) {
            for (size_t i = 0; i < out.size(); ++i) if (std::fabs(out[i] - sample(frameFor(static_cast<int>(i)))) > 1e-5f) { expect(false, label + " at " + juce::String(static_cast<int>(i)) + " from " + juce::String(from)); return; }
        };

        beginTest("An infinite preset loop engages exactly at the section start for any block size");
        for (int block : {64, 100, 1024}) {
            AudioEngine engine; engine.prepareToPlay(block, rate); expect(engine.loadTrack("preset", {file}));
            const double starts[1] = {1000 / rate}, ends[1] = {1137 / rate}; const int repeats[1] = {0};
            expect(engine.configurePresetLoops(starts, ends, repeats, 1)); expect(!engine.getLoopEnabled());
            engine.seekToSeconds(900 / rate); expect(engine.waitForReadAhead(block, 2000)); engine.play();
            const auto out = render(engine, 100 + 137 * 3 + 20, block);
            check(out, 900, [](int i) { return i < 100 ? 900 + i : 1000 + (i - 100) % 137; }, "block " + juce::String(block));
            expect(engine.getLoopEnabled()); expectEquals(engine.getUnderrunCount(), uint64_t(0));
            // Released mid-section: it plays on and does not engage again.
            expect(engine.setLoop(0, 0, false)); expect(engine.waitForReadAhead(block, 2000));
            const auto pos = static_cast<int>(std::llround(engine.getCurrentPositionSeconds() * rate)); const auto after = render(engine, 400, block);
            check(after, pos, [pos](int i) { return pos + i; }, "after release"); expect(!engine.getLoopEnabled());
        }

        beginTest("Counted preset loops continue after their passes; seeking back re-arms them");
        {
            AudioEngine engine; engine.prepareToPlay(256, rate); expect(engine.loadTrack("preset", {file}));
            const double starts[2] = {1000 / rate, 3000 / rate}, ends[2] = {1137 / rate, 3050 / rate}; const int repeats[2] = {2, 0};
            expect(engine.configurePresetLoops(starts, ends, repeats, 2));
            engine.seekToSeconds(950 / rate); expect(engine.waitForReadAhead(256, 2000)); engine.play();
            auto out = render(engine, 50 + 137 * 2 + 100, 256);
            check(out, 950, [](int i) { return i < 50 ? 950 + i : (i < 50 + 274 ? 1000 + (i - 50) % 137 : 1137 + (i - 324)); }, "counted preset");
            engine.seekToSeconds(990 / rate); expect(engine.waitForReadAhead(256, 2000));
            out = render(engine, 10 + 137, 256);
            check(out, 990, [](int i) { return i < 10 ? 990 + i : 1000 + (i - 10) % 137; }, "re-armed");
        }

        beginTest("Validation: overlap, count, bad values, and the song or time scale drop the presets");
        {
            AudioEngine engine; engine.prepareToPlay(256, rate); expect(engine.loadTrack("preset", {file}));
            const double s2[2] = {1000 / rate, 1100 / rate}, e2[2] = {1137 / rate, 1200 / rate}; const int r2[2] = {0, 0};
            expect(!engine.configurePresetLoops(s2, e2, r2, 2));
            const double nan[1] = {std::numeric_limits<double>::quiet_NaN()}, e1[1] = {0.1}; expect(!engine.configurePresetLoops(nan, e1, r2, 1));
            const int bad[1] = {-1}; const double s1[1] = {0.01}; expect(!engine.configurePresetLoops(s1, e1, bad, 1));
            expect(!engine.configurePresetLoops(nullptr, nullptr, nullptr, 3)); expect(!engine.configurePresetLoops(s1, e1, r2, 17));
            const double beyond[1] = {2.0}; expect(!engine.configurePresetLoops(s1, beyond, r2, 1));
            expect(engine.configurePresetLoops(s1, e1, r2, 1));
            expect(engine.setTimeScale(1.5)); engine.play(); render(engine, 5000, 256); expect(!engine.getLoopEnabled());  // dropped with the scale: caches were cut for the old one
            expect(engine.configurePresetLoops(s1, e1, r2, 1)); expect(engine.loadTrack("again", {file})); engine.play(); render(engine, 5000, 256); expect(!engine.getLoopEnabled());
            expect(engine.configurePresetLoops(nullptr, nullptr, nullptr, 0));
        }
        dir.deleteRecursively();
    }
};
static PresetLoopTests presetLoopTests;
