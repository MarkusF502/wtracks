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
            engine.play(); const auto out = render(engine, 137 + 50 * 2, 256);
            for (int i = 137; i < 137 + 100; ++i) expectWithinAbsoluteError(out[static_cast<size_t>(i)], sample(2000 + (i - 137) % 50), 1e-5f);
            double state[6]; engine.getLoopState(state); expectEquals(state[0], 1.0); expectWithinAbsoluteError(state[1], 2000 / rate, 1e-9);
        }
        dir.deleteRecursively();
    }
};
static CountedLoopTests countedLoopTests;
