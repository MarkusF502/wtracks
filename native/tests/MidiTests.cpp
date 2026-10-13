#include "AudioEngine.h"
#include <map>
#include <vector>
using namespace wtracks;

namespace {
struct Sent { double hostMs; std::vector<uint8_t> bytes; };
class RecordingSink : public MidiSink {
public:
    std::mutex mutex; std::vector<Sent> sent; std::atomic<bool> blocked { false };
    void send(const uint8_t* bytes, int size, double hostMs) override {
        while (blocked.load()) juce::Thread::sleep(1);
        const std::lock_guard<std::mutex> lock(mutex); sent.push_back({hostMs, std::vector<uint8_t>(bytes, bytes + size)});
    }
    std::vector<Sent> snapshot() { const std::lock_guard<std::mutex> lock(mutex); return sent; }
};
}

class MidiTests : public juce::UnitTest {
public:
    MidiTests() : juce::UnitTest("MIDI clock, cues and router", "Audio") {}

    static juce::File silence(const juce::File& dir, const juce::String& name, int frames) {
        auto file = dir.getChildFile(name); juce::WavAudioFormat format;
        auto stream = std::unique_ptr<juce::FileOutputStream>(file.createOutputStream());
        std::unique_ptr<juce::AudioFormatWriter> writer(format.createWriterFor(stream.get(), 48000, 2, 24, {}, 0)); stream.release();
        juce::AudioBuffer<float> data(2, frames); data.clear(); writer->writeFromAudioSampleBuffer(data, 0, frames); writer.reset(); return file;
    }
    static void render(AudioEngine& engine, int total, int block) {
        juce::AudioBuffer<float> out(2, block); int offset = 0;
        while (offset < total) { const int count = juce::jmin(block, total - offset); juce::AudioSourceChannelInfo info(&out, 0, count); engine.getNextAudioBlock(info); offset += count; }
    }
    static std::vector<int64_t> pulses(const MidiClockTimeline& clock, double rate, int64_t from, int64_t to, int block) {
        std::vector<int64_t> result;
        for (int64_t position = from; position < to; position += block) {
            const int count = static_cast<int>(std::min<int64_t>(block, to - position));
            clock.render(count, position, rate, [&](int offset) { result.push_back(position + offset); });
        }
        return result;
    }

    void runTest() override {
        beginTest("Clock: 24 pulses per quarter, absolute and independent of block size");
        {
            MidiClockTimeline clock; clock.bpm = 120;
            const auto reference = pulses(clock, 48000, 0, 96000, 1000);
            expectEquals<int>(static_cast<int>(reference.size()), 96);
            for (size_t i = 0; i < reference.size(); ++i) expectEquals<int64_t>(reference[i], static_cast<int64_t>(i) * 1000);
            for (int block : {1, 7, 64, 480, 4096}) expect(pulses(clock, 48000, 0, 96000, block) == reference, "block " + juce::String(block));
            clock.bpm = 123.456;  // fractional tempo: every pulse is round(k * period), no accumulated truncation
            const double period = 48000.0 * 60.0 / (123.456 * 24.0);
            const auto fractional = pulses(clock, 44100 + 3900, 0, 480000, 333);
            for (size_t k = 0; k < fractional.size(); ++k) expectEquals<int64_t>(fractional[k], std::llround(static_cast<double>(k) * period));
            clock.bpm = 120; clock.offset = 0.25;
            const auto shifted = pulses(clock, 48000, 0, 24000, 100);
            expectEquals<int64_t>(shifted.front(), 12000); expectEquals<int>(static_cast<int>(shifted.size()), 12);
            clock.offset = 0; clock.bpmUnit = 8;  // BPM counts eighth notes: a quarter lasts twice as long
            expectEquals<int>(static_cast<int>(pulses(clock, 48000, 0, 96000, 256).size()), 48);
            // Seeking into the middle neither duplicates nor skips pulses.
            clock.bpmUnit = 4; auto tail = pulses(clock, 48000, 30500, 96000, 77);
            expectEquals<int64_t>(tail.front(), 31000);
            expectEquals(MidiClockTimeline::startMessageFor(0), MidiClockTimeline::kStart); expectEquals(MidiClockTimeline::startMessageFor(4), MidiClockTimeline::kStart);
            expectEquals(MidiClockTimeline::startMessageFor(5), MidiClockTimeline::kContinue);
            clock.bpm = 0; expect(pulses(clock, 48000, 0, 1000, 100).empty());
        }

        beginTest("Cues: simultaneous drain, seek, loop re-arm, validation and time scale");
        {
            auto make = [](double t, uint8_t size = 0, uint8_t a = 0, uint8_t b = 0, uint8_t c = 0) { CueTimeline::Cue cue; cue.timeSeconds = t; cue.midiSize = size; cue.midi[0] = a; cue.midi[1] = b; cue.midi[2] = c; return cue; };
            CueTimeline timeline; expect(timeline.configure({make(0.5), make(0.5), make(0.5), make(1.0)}, 2.0));
            std::vector<std::pair<size_t, int>> fired;
            auto run = [&](int64_t position, int count) { timeline.render(count, position, 1000, [&](size_t index, int offset) { fired.push_back({index, offset}); }); };
            run(0, 500); expect(fired.empty()); run(500, 10);
            expectEquals<int>(static_cast<int>(fired.size()), 3); expectEquals<int>(fired[0].second, 0); expect(fired[0].first == 0 && fired[1].first == 1 && fired[2].first == 2);
            fired.clear(); run(510, 490); expect(fired.empty()); run(1000, 1); expectEquals<int>(static_cast<int>(fired.size()), 1);
            fired.clear(); run(400, 200);  // rewind before the cues: they are armed again, but never fire twice for one pass
            expectEquals<int>(static_cast<int>(fired.size()), 3); fired.clear(); run(600, 100); expect(fired.empty());
            run(500, 1); expectEquals<int>(static_cast<int>(fired.size()), 3);  // seek exactly on the cue sample fires it
            fired.clear(); run(501, 1); expect(fired.empty()); run(900, 400); expectEquals<int>(static_cast<int>(fired.size()), 1);  // seek past the early cues skips them
            timeline.setTimeScale(2.0); fired.clear(); run(0, 1000); expect(fired.empty()); run(1000, 1); expectEquals<int>(static_cast<int>(fired.size()), 3); run(1001, 998); expectEquals<int>(static_cast<int>(fired.size()), 3); run(1999, 1); expectEquals<int>(static_cast<int>(fired.size()), 3); run(2000, 1); expectEquals<int>(static_cast<int>(fired.size()), 4);
            expect(!timeline.configure({make(1.0), make(0.5)}, 2.0)); expect(!timeline.configure({make(-1)}, 2.0)); expect(!timeline.configure({make(3.0)}, 2.0));
            expect(!timeline.configure({make(std::numeric_limits<double>::quiet_NaN())}, 2.0));
            expectEquals<int>(static_cast<int>(timeline.size()), 4);  // failures preserve the schedule
            expect(!timeline.configure(std::vector<CueTimeline::Cue>(CueTimeline::kMaxCues + 1), 2.0));
            expect(CueTimeline::midiValid(make(0, 2, 0xC3, 5))); expect(CueTimeline::midiValid(make(0, 3, 0xB0, 7, 100))); expect(CueTimeline::midiValid(make(0, 3, 0x90, 60, 0)));
            expect(!CueTimeline::midiValid(make(0, 3, 0xC3, 5, 1))); expect(!CueTimeline::midiValid(make(0, 2, 0xB0, 7))); expect(!CueTimeline::midiValid(make(0, 3, 0xB0, 0x80, 1)));
            expect(!CueTimeline::midiValid(make(0, 3, 0x30, 1, 1))); expect(!CueTimeline::midiValid(make(0, 1, 0xF8))); expect(!CueTimeline::midiValid(make(0, 3, 0xF0, 1, 1)));
            expect(!CueTimeline::midiValid(make(0, 2, 0xF2, 1)));
        }

        beginTest("Router: ordered timestamps with lead, control messages, overflow and shutdown");
        {
            MidiRouter router; auto* raw = new RecordingSink; router.open(std::unique_ptr<MidiSink>(raw));
            const uint8_t a = 0xF8, b = 0xFA; const double base = juce::Time::getMillisecondCounterHiRes() + 1000.0;
            expect(router.push(base, 0, 1000.0, &a, 1)); expect(router.push(base, 480, 48000.0, &b, 1)); expect(router.push(base, 48, 48000.0, &a, 1));
            expect(router.flush(1000)); auto sent = raw->snapshot();
            expectEquals<int>(static_cast<int>(sent.size()), 3);
            if (sent.size() == 3) {  // sorted by host time; the lead is added; offsets scale with the rate
                expectWithinAbsoluteError(sent[0].hostMs, base + MidiRouter::kLeadMs, 1e-9);
                expectWithinAbsoluteError(sent[1].hostMs, base + 1.0 + MidiRouter::kLeadMs, 1e-9);
                expectWithinAbsoluteError(sent[2].hostMs, base + 10.0 + MidiRouter::kLeadMs, 1e-9);
                expectEquals<int>(sent[1].bytes[0], 0xF8); expectEquals<int>(sent[2].bytes[0], 0xFA);  // 480/48000 s = 10 ms is the later event
            }
            const uint8_t stop = 0xFC; const double before = juce::Time::getMillisecondCounterHiRes();
            router.sendNow(&stop, 1); expect(router.flush(1000)); sent = raw->snapshot();
            expectEquals<int>(static_cast<int>(sent.size()), 4); expect(sent.back().bytes[0] == 0xFC && sent.back().hostMs >= before + MidiRouter::kLeadMs - 1.0);
            expect(!router.push(0, 0, 1000.0, &a, 0)); expect(!router.push(0, 0, 1000.0, &a, 4));

            raw->blocked = true; const uint8_t pc[2] = {0xC0, 1}; int accepted = 0;
            for (int i = 0; i < 3 * MidiRouter::kCapacity; ++i) if (router.push(5000.0 + i, 0, 1000.0, pc, 2)) ++accepted;
            expect(router.droppedEvents() > 0 || accepted > MidiRouter::kCapacity);  // the dispatcher may drain a little before blocking
            expectEquals<uint64_t>(router.droppedEvents(), static_cast<uint64_t>(3 * MidiRouter::kCapacity - accepted));
            raw->blocked = false; expect(router.flush(5000));
            router.close(); expect(!router.isOpen()); expect(!router.push(0, 0, 1000.0, &a, 1));
            router.sendNow(&a, 1);  // closed: ignored, no crash
            auto* second = new RecordingSink; router.open(std::unique_ptr<MidiSink>(second)); expectEquals<uint64_t>(router.droppedEvents(), uint64_t(0));
            expect(router.push(10, 0, 1000.0, &a, 1)); expect(router.flush(1000)); expectEquals<int>(static_cast<int>(second->snapshot().size()), 1);
            router.close();
        }

        auto dir = juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_midi", "", false); dir.createDirectory();
        auto song = silence(dir, "song.wav", 96000);
        auto countClocks = [](const std::vector<Sent>& sent) { int n = 0; for (auto& s : sent) if (s.bytes.size() == 1 && s.bytes[0] == 0xF8) ++n; return n; };

        beginTest("Engine: start/continue/stop around 0xF8 pulses and the tempo follows the time scale");
        {
            AudioEngine engine; engine.prepareToPlay(256, 48000); expect(engine.loadTrack("midi", {song}));
            expect(engine.configureClick(120, 4, 4, 4, 0.0, 1, 1, 0, 0));
            auto* raw = new RecordingSink; engine.attachMidiSink(std::unique_ptr<MidiSink>(raw)); expect(engine.isMidiOutputOpen());
            engine.setMidiClockEnabled(true);
            engine.play(); render(engine, 48000, 256); engine.pause(); expect(engine.getMidiDroppedCount() == 0);
            render(engine, 256, 256); expect(engine.getMidiDroppedCount() == 0);
            expect(engine.isMidiOutputOpen());
            // Let the dispatcher hand over everything, then inspect (a direct router flush is internal; poll the sink).
            for (int i = 0; i < 200 && raw->snapshot().size() < 50; ++i) juce::Thread::sleep(5);
            auto sent = raw->snapshot();
            expectEquals<int>(sent.front().bytes[0], 0xFA);
            expectEquals(countClocks(sent), 48); expectEquals<int>(sent.back().bytes[0], 0xFC);
            engine.seekToSeconds(0.5); engine.play(); render(engine, 24000, 256);  // resumes mid-song: continue (0xFB)
            engine.pause(); for (int i = 0; i < 200 && raw->snapshot().size() < 100; ++i) juce::Thread::sleep(5);
            sent = raw->snapshot(); size_t second = 0; for (size_t i = 1; i < sent.size(); ++i) if (sent[i].bytes[0] == 0xFB) second = i;
            expect(second > 0, "continue message");
            engine.setMidiClockEnabled(false); engine.seekToSeconds(0); engine.play(); render(engine, 4800, 256); engine.pause();
            juce::Thread::sleep(100); const auto afterDisable = raw->snapshot().size();
            engine.play(); render(engine, 2400, 256); engine.pause(); juce::Thread::sleep(100); expectEquals<size_t>(raw->snapshot().size(), afterDisable);  // disabled: silent
            engine.closeMidiOutput(); expect(!engine.isMidiOutputOpen());
        }
        {
            AudioEngine engine; engine.prepareToPlay(256, 48000); expect(engine.loadTrack("midi", {song}));
            expect(engine.configureClick(120, 4, 4, 4, 0.0, 1, 1, 0, 0)); expect(engine.setTimeScale(2.0));
            auto* raw = new RecordingSink; engine.attachMidiSink(std::unique_ptr<MidiSink>(raw)); engine.setMidiClockEnabled(true);
            engine.play(); render(engine, 48000, 256); engine.pause(); for (int i = 0; i < 200 && raw->snapshot().size() < 26; ++i) juce::Thread::sleep(5);
            expectEquals(countClocks(raw->snapshot()), 24);  // half the pulses per processed second
            engine.closeMidiOutput();
        }

        beginTest("Engine: end of file stops the clock, cues fire once, are polled, forwarded and validated");
        {
            AudioEngine engine; engine.prepareToPlay(256, 48000); expect(engine.loadTrack("midi", {song}));
            expect(engine.configureClick(120, 4, 4, 4, 0.0, 1, 1, 0, 0));
            const double times[3] = {0.5, 0.5, 1.5}; const uint8_t bytes[9] = {0xC1, 7, 0, 0xB0, 7, 100, 0, 0, 0}; const uint8_t sizes[3] = {2, 3, 0};
            expect(engine.configureCues(times, bytes, sizes, 3));
            const double bad[2] = {1.0, 0.5}; expect(!engine.configureCues(bad, bytes, sizes, 2)); const double beyond[1] = {5.0}; expect(!engine.configureCues(beyond, bytes, sizes, 1));
            const uint8_t badSize[1] = {4}; expect(!engine.configureCues(times, bytes, badSize, 1)); const uint8_t badMidi[3] = {0x90, 0xFF, 1}; expect(!engine.configureCues(times, badMidi, sizes + 1, 1));
            expect(!engine.configureCues(nullptr, bytes, sizes, 1));
            auto* raw = new RecordingSink; engine.attachMidiSink(std::unique_ptr<MidiSink>(raw)); engine.setMidiClockEnabled(true);
            engine.play(); render(engine, 200000, 256);  // beyond the end of the 2 s song
            expect(!engine.isPlaying());
            uint32_t polled[8] = {}; expectEquals(engine.pollCues(polled, 8), 3); expect(polled[0] == 0 && polled[1] == 1 && polled[2] == 2); expectEquals(engine.pollCues(polled, 8), 0);
            render(engine, 256, 256);  // the audio thread notices the stop
            for (int i = 0; i < 400 && raw->snapshot().size() < 100; ++i) juce::Thread::sleep(5);
            auto sent = raw->snapshot(); int program = 0, controller = 0, stops = 0;
            for (auto& s : sent) { if (s.bytes[0] == 0xC1) ++program; if (s.bytes[0] == 0xB0) ++controller; if (s.bytes[0] == 0xFC) ++stops; }
            expectEquals(program, 1); expectEquals(controller, 1); expectEquals(stops, 1);
            expectEquals(countClocks(sent), 96);
            // Loop wrap re-arms the cues each pass.
            engine.stop(); expect(engine.setLoop(0.25, 0.75, true)); engine.play(); render(engine, 48000, 256);
            expectEquals(engine.pollCues(polled, 8), 4);  // two passes x two cues at 0.5 s
            const uint8_t note[3] = {0x90, 60, 100}; expect(engine.sendMidiMessage(note, 3));
            const uint8_t invalid[3] = {0xF8, 0, 0}; expect(!engine.sendMidiMessage(invalid, 1)); expect(!engine.sendMidiMessage(invalid, 3));
            engine.closeMidiOutput(); expect(!engine.sendMidiMessage(note, 3));
            // A new song discards the schedule.
            expect(engine.loadTrack("other", {song})); render(engine, 256, 256); engine.play(); render(engine, 96000, 256); expectEquals(engine.pollCues(polled, 8), 0);
        }
        dir.deleteRecursively();
    }
};
static MidiTests midiTests;
