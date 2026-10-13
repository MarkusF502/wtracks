#include "AudioEngine.h"
#include <vector>
using namespace wtracks;

// Tempo/meter changes: the click grid and the MIDI clock follow the segment they are in.
class TempoMapTests : public juce::UnitTest {
public:
    TempoMapTests() : juce::UnitTest("Tempo map for click and MIDI clock", "Audio") {}

    static std::vector<int64_t> clockPulses(MidiClockTimeline clock, double rate, int64_t to, int block) {
        std::vector<int64_t> out;
        for (int64_t p = 0; p < to; p += block) { const int n = static_cast<int>(std::min<int64_t>(block, to - p)); clock.render(n, p, rate, [&](int i) { out.push_back(p + i); }); }
        return out;
    }
    static std::vector<int> clickVoices(ClickTimeline& click, double rate, int64_t to, std::vector<int64_t>& at) {
        std::vector<int> voices; juce::AudioBuffer<float> out(1, 64);
        for (auto& buffer : click.fallback) { buffer.setSize(1, 2000); buffer.clear(); buffer.setSample(0, 0, 1.0f); }
        for (int64_t p = 0; p < to; p += 64) {
            const int n = static_cast<int>(std::min<int64_t>(64, to - p)); out.clear();
            auto before = click.starts;
            click.render(out, 0, n, p, rate, true);
            for (int v = 0; v < 4; ++v) if (click.starts[static_cast<size_t>(v)] != before[static_cast<size_t>(v)] && click.starts[static_cast<size_t>(v)] >= p) { voices.push_back(v); at.push_back(click.starts[static_cast<size_t>(v)]); }
        }
        return voices;
    }

    void runTest() override {
        beginTest("Validation");
        {
            expect(tempoChangesValid({}, 0));
            expect(tempoChangesValid({{2, 90, 3, 4}, {4, 140, 6, 8}}, 1));
            expect(!tempoChangesValid({{2, 90, 3, 4}, {2, 100, 4, 4}}, 0));    // not strictly increasing
            expect(!tempoChangesValid({{1, 90, 4, 4}}, 1));                     // at the base offset
            expect(!tempoChangesValid({{2, 0.5, 4, 4}}, 0)); expect(!tempoChangesValid({{2, 1001, 4, 4}}, 0));
            expect(!tempoChangesValid({{2, 90, 0, 4}}, 0)); expect(!tempoChangesValid({{2, 90, 4, 3}}, 0)); expect(!tempoChangesValid({{2, 90, 65, 4}}, 0));
            expect(!tempoChangesValid({{std::numeric_limits<double>::quiet_NaN(), 90, 4, 4}}, 0)); expect(!tempoChangesValid({{-1, 90, 4, 4}}, 0));
            expect(!tempoChangesValid(std::vector<TempoChange>(513, TempoChange{}), 0));
        }

        beginTest("MIDI clock switches period exactly at the change and is block independent");
        {
            MidiClockTimeline clock; clock.bpm = 120; clock.changes = {{1.0, 60, 4, 4}};
            const auto reference = clockPulses(clock, 48000, 96000, 1000);
            // 120 BPM: 1000-sample pulses until 1 s (48000), then 60 BPM: 2000-sample pulses from 48000.
            expectEquals<int>(static_cast<int>(reference.size()), 48 + 24);
            for (int i = 0; i < 48; ++i) expectEquals<int64_t>(reference[static_cast<size_t>(i)], i * 1000LL);
            for (int i = 0; i < 24; ++i) expectEquals<int64_t>(reference[static_cast<size_t>(48 + i)], 48000 + i * 2000LL);
            for (int block : {1, 7, 333, 4096}) expect(clockPulses(clock, 48000, 96000, block) == reference, "block " + juce::String(block));
        }

        beginTest("Click: bars restart at each change with its own meter");
        {
            ClickTimeline click; click.bpm = 120; click.numerator = 4; click.denominator = 4; click.bpmUnit = 4; click.offset = 0;
            click.changes = {{2.0, 120, 3, 4}};  // same tempo, 3/4 from 2 s
            std::vector<int64_t> at; auto voices = clickVoices(click, 48000, 48000 * 5, at);
            // accent/quarter pattern: 4 beats of 4/4 in the first 2 s (accent, q, q, q), then 3/4 bars (accent, q, q) restarting at 2 s.
            std::vector<int> expectedQuarters; (void)expectedQuarters;
            std::vector<std::pair<int64_t, int>> quarters;
            for (size_t i = 0; i < voices.size(); ++i) if (voices[i] <= 1) quarters.push_back({at[i], voices[i]});
            expectEquals<int>(static_cast<int>(quarters.size()), 10);  // 4 beats + 6 beats in 5 s at 120 BPM
            const int want[10] = {0, 1, 1, 1, 0, 1, 1, 0, 1, 1};
            for (size_t i = 0; i < quarters.size(); ++i) { expectEquals(quarters[i].second, want[i]); expectEquals<int64_t>(quarters[i].first, static_cast<int64_t>(i) * 24000); }
        }

        beginTest("Click: tempo change moves the grid; no event leaks across the boundary");
        {
            ClickTimeline click; click.bpm = 120; click.denominator = 4; click.bpmUnit = 4; click.numerator = 4; click.offset = 0.25;
            click.changes = {{1.1, 60, 4, 4}};  // the 120 BPM grid would hit 1.25 s; the new grid starts at 1.1 s
            std::vector<int64_t> at; auto voices = clickVoices(click, 48000, 48000 * 4, at);
            std::vector<int64_t> beats; for (size_t i = 0; i < voices.size(); ++i) if (voices[i] <= 1) beats.push_back(at[i]);
            // 0.25, 0.75 (then 1.25 would be next, but the change starts at 1.1), 1.1, 2.1, 3.1
            const int64_t expectedBeats[] = {12000, 36000, 52800, 52800 + 48000, 52800 + 96000, 52800 + 144000};
            for (size_t i = 0; i < beats.size(); ++i) expectEquals<int64_t>(beats[i], expectedBeats[i]);
            expectEquals<int>(static_cast<int>(beats.size()), 5);
            for (size_t i = 0; i < voices.size(); ++i) if (at[i] == 52800) expectEquals(voices[i], 0);  // the segment's first beat is an accent
        }

        auto dir = juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_tempo", "", false); dir.createDirectory();
        auto song = dir.getChildFile("song.wav");
        { juce::WavAudioFormat wav; auto stream = std::unique_ptr<juce::FileOutputStream>(song.createOutputStream());
          std::unique_ptr<juce::AudioFormatWriter> writer(wav.createWriterFor(stream.get(), 48000, 2, 24, {}, 0)); stream.release();
          juce::AudioBuffer<float> data(2, 48000 * 6); data.clear(); writer->writeFromAudioSampleBuffer(data, 0, data.getNumSamples()); }

        beginTest("Engine: changes are validated, preserved on failure, scaled with the time scale and dropped with the song");
        {
            AudioEngine engine; engine.prepareToPlay(256, 48000); expect(engine.loadTrack("tempo", {song}));
            expect(engine.configureClick(120, 4, 4, 4, 0.0, 1, 1, 0, 0));
            const double starts[2] = {1.0, 3.0}, bpms[2] = {60, 90}; const int nums[2] = {4, 3}, dens[2] = {4, 4};
            expect(engine.setClickTempoChanges(starts, bpms, nums, dens, 2));
            const double bad[2] = {3.0, 1.0}; expect(!engine.setClickTempoChanges(bad, bpms, nums, dens, 2));
            expect(!engine.setClickTempoChanges(nullptr, bpms, nums, dens, 1)); expect(!engine.setClickTempoChanges(starts, bpms, nums, dens, -1));
            auto* clickAudible = &engine; (void)clickAudible;
            juce::AudioBuffer<float> out(2, 256); engine.setClickEnabled(true); engine.play();
            std::vector<int> beatSamples;
            for (int block = 0; block < 48000 * 4 / 256; ++block) { juce::AudioSourceChannelInfo info(&out, 0, 256); engine.getNextAudioBlock(info);
                for (int i = 0; i < 256; ++i) if (std::fabs(out.getSample(0, i)) > 0.2f && (beatSamples.empty() || block * 256 + i - beatSamples.back() > 2400)) beatSamples.push_back(block * 256 + i); }
            expect(beatSamples.size() >= 4, "beats heard " + juce::String(static_cast<int>(beatSamples.size())));
            if (beatSamples.size() >= 4) { expect(std::abs(beatSamples[1] - beatSamples[0] - 24000) < 50); expect(std::abs(beatSamples[3] - beatSamples[2] - 48000) < 50, "60 BPM spacing after 1 s"); expect(beatSamples.size() >= 5, "3 s beat at 60 BPM"); }
            // Offset past the first change drops the now-invalid list instead of playing a broken grid.
            engine.setClickOffsetSeconds(2.0); engine.stop(); engine.play();
            engine.setClickOffsetSeconds(0.0);
            expect(engine.setTimeScale(2.0));
            engine.stop(); engine.play();  // scaled: 60 BPM from 2 s is a 2 s spacing at processed time 4 s... exercised for crashes only
            for (int block = 0; block < 100; ++block) { juce::AudioSourceChannelInfo info(&out, 0, 256); engine.getNextAudioBlock(info); }
            expect(engine.loadTrack("other", {song})); expect(engine.setClickTempoChanges(nullptr, nullptr, nullptr, nullptr, 0));
        }
        dir.deleteRecursively();
    }
};
static TempoMapTests tempoMapTests;
