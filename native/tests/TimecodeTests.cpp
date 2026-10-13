#include "AudioEngine.h"
#include "Timecode.h"
#include <juce_core/juce_core.h>
#include <vector>

using namespace wtracks;

class TimecodeTests : public juce::UnitTest {
public:
    TimecodeTests() : juce::UnitTest("Linear timecode generator", "Audio") {}

    struct Decoded { bool ok = false; int h = 0, m = 0, s = 0, f = 0; bool drop = false; int64_t startSample = 0; };

    // Independent decoder: edge intervals -> bits (short pair = 1, long = 0) -> sync search -> BCD.
    static std::vector<Decoded> decode(const std::vector<float>& x, double rate, int index) {
        std::vector<int64_t> edges;
        for (size_t i = 1; i < x.size(); ++i) if ((x[i - 1] > 0) != (x[i] > 0)) edges.push_back(static_cast<int64_t>(i));
        const double bit = rate / (80.0 * static_cast<double>(TimecodeGenerator::framesPerSecond(index)));
        std::vector<int> bits; std::vector<int64_t> starts;
        for (size_t i = 0; i + 1 < edges.size();) {
            const double gap = static_cast<double>(edges[i + 1] - edges[i]);
            if (gap < 0.75 * bit) { bits.push_back(1); starts.push_back(edges[i]); i += 2; }
            else { bits.push_back(0); starts.push_back(edges[i]); i += 1; }
        }
        std::vector<Decoded> frames;
        for (size_t i = 0; i + 80 <= bits.size();) {
            uint16_t sync = 0; for (int b = 0; b < 16; ++b) sync |= static_cast<uint16_t>(bits[i + 64 + static_cast<size_t>(b)] << b);
            if (sync != TimecodeGenerator::kSyncWord) { ++i; continue; }
            auto field = [&](int first, int width) { int v = 0; for (int b = 0; b < width; ++b) v |= bits[i + static_cast<size_t>(first + b)] << b; return v; };
            Decoded d; d.ok = true; d.f = field(0, 4) + 10 * field(8, 2); d.drop = bits[i + 10]; d.s = field(16, 4) + 10 * field(24, 3);
            d.m = field(32, 4) + 10 * field(40, 3); d.h = field(48, 4) + 10 * field(56, 2); d.startSample = starts[i];
            frames.push_back(d); i += 80;
        }
        return frames;
    }

    void runTest() override {
        using G = TimecodeGenerator;
        beginTest("Rate table, frame counts per day and field conversion (drop and non-drop)");
        {
            const int expectedNominal[11] = {24, 25, 30, 30, 30, 30, 60, 60, 60, 60, 50};
            for (int i = 0; i < G::kRateCount; ++i) expectEquals(G::kRates[static_cast<size_t>(i)].nominal, expectedNominal[i]);
            for (int i : {2, 5, 8, 9}) expect(G::kRates[static_cast<size_t>(i)].drop);
            for (int i : {0, 1, 3, 4, 6, 7, 10}) expect(!G::kRates[static_cast<size_t>(i)].drop);
            expectEquals<int64_t>(G::framesPerDay(0), 24 * 86400); expectEquals<int64_t>(G::framesPerDay(5), 2589408);  // 24 h of 29.97 DF
            expectEquals<int64_t>(G::framesPerDay(9), 5178816);
            auto f = G::fieldsFor(5, 0); expect(f.hours == 0 && f.minutes == 0 && f.seconds == 0 && f.frames == 0 && f.drop);
            f = G::fieldsFor(5, 1799); expect(f.minutes == 0 && f.seconds == 59 && f.frames == 29);
            f = G::fieldsFor(5, 1800); expect(f.minutes == 1 && f.seconds == 0 && f.frames == 2);  // frames 00 and 01 are skipped at minute 1
            f = G::fieldsFor(5, 17981); expect(f.minutes == 9 && f.seconds == 59 && f.frames == 29);
            f = G::fieldsFor(5, 17982); expect(f.minutes == 10 && f.seconds == 0 && f.frames == 0);  // minute 10 keeps its frames
            f = G::fieldsFor(5, G::framesPerDay(5) - 1); expect(f.hours == 23 && f.minutes == 59 && f.seconds == 59 && f.frames == 29);
            f = G::fieldsFor(5, G::framesPerDay(5)); expect(f.hours == 0 && f.minutes == 0 && f.seconds == 0 && f.frames == 0);
            f = G::fieldsFor(9, 3600); expect(f.minutes == 1 && f.seconds == 0 && f.frames == 2);  // 59.94 drop: labels count at 30, so two labels (four words) are skipped
            f = G::fieldsFor(7, 61); expect(f.seconds == 1 && f.frames == 0);  // 60 fps pairs share a label
            expect(G::wordFor(7, 60)[11] == 0 && G::wordFor(7, 61)[11] == 1 && G::wordFor(3, 61)[11] == 0);
            expectEquals<int>(G::labelRate(7), 30); expectEquals<int>(G::labelRate(10), 25); expectEquals<int>(G::labelRate(4), 30);
            f = G::fieldsFor(3, 30 * 3600 + 29); expect(f.hours == 1 && f.frames == 29 && !f.drop);
            f = G::fieldsFor(10, 50 * 61); expect(f.minutes == 1 && f.seconds == 1 && f.frames == 0);
        }

        beginTest("The frame word: BCD fields, sync word and even zero count");
        {
            for (int index = 0; index < G::kRateCount; ++index)
                for (int64_t frame : {int64_t(0), int64_t(1), int64_t(29), int64_t(1799), int64_t(12345), G::framesPerDay(index) - 1}) {
                    const auto bits = G::wordFor(index, frame); int zeros = 0; for (auto b : bits) zeros += b == 0;
                    expect(zeros % 2 == 0, "even zeros at rate " + juce::String(index));
                    uint16_t sync = 0; for (int b = 0; b < 16; ++b) sync |= static_cast<uint16_t>(bits[static_cast<size_t>(64 + b)] << b);
                    expectEquals<int>(sync, G::kSyncWord);
                    expect(bits[11] == ((G::halfRate(index) && frame % 2) ? 1 : 0) && !bits[43] && !bits[58], "unused flag bits stay clear");
                }
            const auto word = G::wordFor(3, 3600 * 30 * 2 + 30 * 61 + 7);  // 02:01:01:07
            auto field = [&](int first, int width) { int v = 0; for (int b = 0; b < width; ++b) v |= word[static_cast<size_t>(first + b)] << b; return v; };
            expect(field(0, 4) == 7 && field(8, 2) == 0 && field(16, 4) == 1 && field(24, 3) == 0 && field(32, 4) == 1 && field(40, 3) == 0 && field(48, 4) == 2 && field(56, 2) == 0 && word[10] == 0);
            expect(G::wordFor(2, 5)[10] == 1);
        }

        beginTest("Generated audio decodes to the right timecode for every rate and sample rate");
        for (double rate : {44100.0, 48000.0}) for (int index = 0; index < G::kRateCount; ++index) {
            G g; g.rateIndex = index; g.startFrame = 3 * 3600 * G::kRates[static_cast<size_t>(index)].nominal + 59 * 60 * G::kRates[static_cast<size_t>(index)].nominal;
            g.startFrame = std::min<int64_t>(g.startFrame, G::framesPerDay(index) - 100); g.gain = 1.0f;
            const int total = static_cast<int>(rate * 2.5); std::vector<float> out(static_cast<size_t>(total), 0.f);
            for (int p = 0; p < total; p += 333) g.render(out.data() + p, std::min(333, total - p), p, rate);
            bool bipolar = true; for (float v : out) bipolar = bipolar && (v == 1.0f || v == -1.0f); expect(bipolar, "bipolar unit amplitude");
            const auto frames = decode(out, rate, index);
            const double fps = static_cast<double>(G::framesPerSecond(index));
            expect(static_cast<double>(frames.size()) >= 2.5 * fps - 3, "decoded frame count at rate " + juce::String(index) + " got " + juce::String(static_cast<int>(frames.size())));
            // Every decoded word carries the label of the frame whose slot it occupies in time.
            for (const auto& d : frames) {
                const auto slot = static_cast<int64_t>(std::llround(static_cast<double>(d.startSample) / (rate / fps)));
                const auto want = G::fieldsFor(index, g.startFrame + slot);
                expect(d.h == want.hours && d.m == want.minutes && d.s == want.seconds && d.f == want.frames && d.drop == want.drop,
                       "label at slot " + juce::String(slot) + " rate " + juce::String(index));
            }
            // Consecutive decoded frames must be consecutive timecodes, ordered and spaced by the exact frame length.
            for (size_t k = 1; k < frames.size(); ++k) {
                const auto previous = frames[k - 1], current = frames[k];
                auto key = [&](const Decoded& d) { int64_t v = ((d.h * 60 + d.m) * 60 + d.s) * G::kRates[static_cast<size_t>(index)].nominal + d.f; return v; };
                const auto delta = key(current) - key(previous);
                const bool rollover = current.f == 0 || (G::kRates[static_cast<size_t>(index)].drop && current.f <= 4);
                expect(delta == 1 || rollover || (G::halfRate(index) && delta == 0), "consecutive frames at rate " + juce::String(index));
                expectWithinAbsoluteError(static_cast<double>(current.startSample - previous.startSample), rate / fps, 1.5);
            }
        }

        beginTest("Drop-frame minute boundaries decode with skipped frame numbers");
        for (auto [index, start] : {std::pair<int, int64_t>{5, 1790}, {9, 3590}, {5, 17975}, {2, 1790}}) {
            G g; g.rateIndex = index; g.startFrame = start; g.gain = 1.0f; const double rate = 48000;
            std::vector<float> out(96000, 0.f); g.render(out.data(), 96000, 0, rate);
            const auto frames = decode(out, rate, index); bool crossed = false;
            for (const auto& d : frames) {
                const auto slot = static_cast<int64_t>(std::llround(static_cast<double>(d.startSample) / (rate / static_cast<double>(G::framesPerSecond(index)))));
                const auto want = G::fieldsFor(index, start + slot);
                expect(d.m == want.minutes && d.s == want.seconds && d.f == want.frames, "drop label rate " + juce::String(index));
                crossed = crossed || (d.s == 0 && d.f == (d.m % 10 == 0 ? 0 : 2));
            }
            expect(crossed, "minute boundary reached at rate " + juce::String(index));
        }

        beginTest("Seeks, block sizes, onset and loops are sample exact and stateless");
        {
            G g; g.rateIndex = 1; g.gain = 1.0f; g.startFrame = 25 * 10; g.onsetSeconds = 0.5;
            const int total = 96000; std::vector<float> reference(static_cast<size_t>(total), 0.f);
            g.render(reference.data(), total, 0, 48000);
            for (int i = 0; i < 24000; ++i) expectEquals(reference[static_cast<size_t>(i)], 0.f);  // silent before the onset
            expect(reference[24000] != 0.f);
            for (int block : {1, 64, 1000, 4096}) {
                G h = g; std::vector<float> out(static_cast<size_t>(total), 0.f);
                for (int p = 0; p < total; p += block) h.render(out.data() + p, std::min(block, total - p), p, 48000);
                expect(out == reference, "block " + juce::String(block));
            }
            G jumper = g; std::vector<float> piece(5000, 0.f);  // arbitrary seek: identical to the continuous signal
            jumper.render(piece.data(), 5000, 61234, 48000); for (int i = 0; i < 5000; ++i) expectEquals(piece[static_cast<size_t>(i)], reference[static_cast<size_t>(61234 + i)]);
            jumper.render(piece.data(), 5000, 30000, 48000);  // backwards (loop) too
            std::vector<float> back(5000, 0.f); G fresh = g; fresh.render(back.data(), 5000, 30000, 48000);
            std::vector<float> again(5000, 0.f); jumper.reset(); jumper.render(again.data(), 5000, 30000, 48000); expect(again == back);
            G other = g; other.gain = 0.25f; std::vector<float> quiet(2000, 0.f); other.render(quiet.data(), 2000, 30000, 48000);
            for (int i = 0; i < 2000; ++i) expectWithinAbsoluteError(quiet[static_cast<size_t>(i)], reference[static_cast<size_t>(30000 + i)] * 0.25f, 1e-7f);
            // Adding to existing audio, not replacing it.
            std::vector<float> mixed(100, 0.1f); g.render(mixed.data(), 100, 30000, 48000); for (int i = 0; i < 100; ++i) expectWithinAbsoluteError(mixed[static_cast<size_t>(i)], 0.1f + reference[static_cast<size_t>(30000 + i)], 1e-6f);
        }

        beginTest("Engine: timecode on one output, after the master stage, unaffected by mute and time scale");
        {
            auto dir = juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_tc", "", false); dir.createDirectory();
            auto file = dir.getChildFile("song.wav"); { juce::WavAudioFormat wav; auto stream = std::unique_ptr<juce::FileOutputStream>(file.createOutputStream());
              std::unique_ptr<juce::AudioFormatWriter> writer(wav.createWriterFor(stream.get(), 48000, 2, 24, {}, 0)); stream.release();
              juce::AudioBuffer<float> data(2, 96000); for (int i = 0; i < 96000; ++i) { data.setSample(0, i, 0.25f); data.setSample(1, i, 0.25f); } writer->writeFromAudioSampleBuffer(data, 0, 96000); }
            AudioEngine engine; engine.prepareToPlay(256, 48000); expect(engine.loadTrack("tc", {file}));
            expect(!engine.configureTimecode(11, 0, 0, 1, 0.5f)); expect(!engine.configureTimecode(0, -1, 0, 1, 0.5f)); expect(!engine.configureTimecode(0, 0, 0, 64, 0.5f)); expect(!engine.configureTimecode(0, 0, 0, 1, 2.f));
            expect(engine.configureTimecode(1, 25 * 60, 0.25, 1, 0.5f)); engine.setTimecodeEnabled(true); engine.setMasterVolume(0.f); engine.setChannelMuted(0, true);
            engine.play(); juce::AudioBuffer<float> out(2, 256); std::vector<float> left, right;
            for (int block = 0; block < 400; ++block) { juce::AudioSourceChannelInfo info(&out, 0, 256); engine.getNextAudioBlock(info);
                for (int i = 0; i < 256; ++i) { left.push_back(out.getSample(0, i)); right.push_back(out.getSample(1, i)); } }
            // Master at zero and the stem muted: the left channel is silent once the 20 ms ramps finish; timecode only on the right.
            float leftPeak = 0; for (size_t i = 2000; i < left.size(); ++i) leftPeak = std::max(leftPeak, std::fabs(left[i]));
            expectEquals(leftPeak, 0.f);
            for (size_t i = 0; i < 12000; ++i) expectEquals(right[i], 0.f);  // silent until the 0.25 s onset
            const auto decoded = decode(std::vector<float>(right.begin() + 12000, right.end()), 48000, 1);
            expect(decoded.size() > 40); if (!decoded.empty()) { expect(decoded.front().h == 0 && decoded.front().m == 1); }
            // Time scale 2: onset moves to 0.5 s of the processed timeline; the frame rate stays 25 fps.
            engine.stop(); expect(engine.setTimeScale(2.0)); engine.setTimecodeEnabled(true); engine.play(); right.clear();
            for (int block = 0; block < 400; ++block) { juce::AudioSourceChannelInfo info(&out, 0, 256); engine.getNextAudioBlock(info); for (int i = 0; i < 256; ++i) right.push_back(out.getSample(1, i)); }
            for (size_t i = 0; i < 24000; ++i) expectEquals(right[i], 0.f);
            expect(right[24001] != 0.f || right[24000] != 0.f);
            engine.setTimecodeEnabled(false); engine.stop(); engine.play(); right.clear();
            for (int block = 0; block < 20; ++block) { juce::AudioSourceChannelInfo info(&out, 0, 256); engine.getNextAudioBlock(info); for (int i = 0; i < 256; ++i) right.push_back(out.getSample(1, i)); }
            for (float v : right) expectEquals(v, 0.f);
            dir.deleteRecursively();
        }

        beginTest("Invalid settings are rejected and render nothing");
        {
            const float nan = std::numeric_limits<float>::quiet_NaN(); const double dnan = std::numeric_limits<double>::quiet_NaN();
            expect(G::valid(0, 0, 0, 0.5f)); expect(!G::valid(-1, 0, 0, 0.5f)); expect(!G::valid(11, 0, 0, 0.5f)); expect(!G::valid(0, -1, 0, 0.5f));
            expect(!G::valid(0, G::framesPerDay(0), 0, 0.5f)); expect(!G::valid(0, 0, -1, 0.5f)); expect(!G::valid(0, 0, dnan, 0.5f)); expect(!G::valid(0, 0, 0, nan)); expect(!G::valid(0, 0, 0, 1.5f));
            G g; g.rateIndex = 99; std::vector<float> out(100, 0.f); g.render(out.data(), 100, 0, 48000); for (float v : out) expectEquals(v, 0.f);
            g.rateIndex = 0; g.render(nullptr, 100, 0, 48000); g.render(out.data(), 0, 0, 48000); g.render(out.data(), 100, -5, 48000); g.render(out.data(), 100, 0, 0.0);
            for (float v : out) expectEquals(v, 0.f);
        }
    }
};
static TimecodeTests timecodeTests;
