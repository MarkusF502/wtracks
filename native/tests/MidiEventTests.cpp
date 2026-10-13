#include "AudioEngine.h"
#include <vector>
using namespace wtracks;

namespace {
class Recorder : public MidiSink {
public:
    std::mutex mutex; std::vector<std::vector<uint8_t>> sent;
    void send(const uint8_t* bytes, int size, double) override { const std::lock_guard<std::mutex> lock(mutex); sent.emplace_back(bytes, bytes + size); }
    std::vector<std::vector<uint8_t>> take() { const std::lock_guard<std::mutex> lock(mutex); auto copy=sent; sent.clear(); return copy; }
};
}

// MIDI events (Playback MIDIOutAVAudioUnit: note on/off with currentNoteOnEvents, CC, PC, prerolled/rewound requests,
// MIDIEvent.disableLoop) and MIDI input for mappings.
class MidiEventTests : public juce::UnitTest {
public:
    MidiEventTests() : juce::UnitTest("MIDI events and input", "Audio") {}

    static juce::File silence(const juce::File& dir, int frames) {
        auto file = dir.getChildFile("silence.wav"); juce::WavAudioFormat format;
        auto stream = std::unique_ptr<juce::FileOutputStream>(file.createOutputStream());
        std::unique_ptr<juce::AudioFormatWriter> writer(format.createWriterFor(stream.get(), 48000, 2, 24, {}, 0)); stream.release();
        juce::AudioBuffer<float> data(2, frames); data.clear(); writer->writeFromAudioSampleBuffer(data, 0, frames); writer.reset(); return file;
    }
    static void render(AudioEngine& engine, int total, int block = 64) {
        juce::AudioBuffer<float> out(2, block); int offset = 0;
        while (offset < total) { const int count = juce::jmin(block, total - offset); juce::AudioSourceChannelInfo info(&out, 0, count); engine.getNextAudioBlock(info); offset += count; }
    }
    struct Cues {
        std::vector<double> times; std::vector<uint8_t> bytes, sizes, flags;
        void add(double t, std::initializer_list<uint8_t> msg, bool disableLoop = false) {
            times.push_back(t); uint8_t b[3]={0,0,0}; int i=0; for (auto v : msg) b[i++]=v;
            bytes.insert(bytes.end(), b, b+3); sizes.push_back(static_cast<uint8_t>(msg.size())); flags.push_back(disableLoop ? 1 : 0);
        }
        bool apply(AudioEngine& e) { return e.configureCues(times.data(), bytes.data(), sizes.data(), flags.data(), static_cast<int>(times.size())); }
    };

    void runTest() override {
        auto dir = juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_midievents", "", false); dir.createDirectory();
        auto song = silence(dir, 4 * 48000);
        auto start = [&](AudioEngine& engine, Recorder*& raw) {
            engine.prepareToPlay(64, 48000); expect(engine.loadTrack("midi", {song}));
            auto sink = std::make_unique<Recorder>(); raw = sink.get(); engine.attachMidiSink(std::move(sink));
        };
        using Msg = std::vector<uint8_t>;

        beginTest("Held notes get note-offs on pause, seek, loop jumps and the end of the song");
        {
            AudioEngine engine; Recorder* raw = nullptr; start(engine, raw);
            Cues c; c.add(0.1, {0x91, 60, 100}); c.add(0.2, {0x91, 62, 100}); c.add(0.3, {0x81, 62, 0}); expect(c.apply(engine));
            engine.play(); render(engine, 24000); engine.pause(); expect(engine.isPlaying() == false);
            juce::Thread::sleep(50); auto sent = raw->take();
            expect(std::find(sent.begin(), sent.end(), Msg{0x81, 60, 0}) != sent.end());       // released by the pause
            expect(std::count(sent.begin(), sent.end(), Msg{0x81, 62, 0}) == 1);               // its own note-off only
            engine.seekToSeconds(0); engine.play(); render(engine, 6000); engine.seekToSeconds(3.0);
            juce::Thread::sleep(50); sent = raw->take();
            expect(std::find(sent.begin(), sent.end(), Msg{0x81, 60, 0}) != sent.end());
            expect(engine.setLoop(0, 0.15, true)); engine.seekToSeconds(0); engine.play(); render(engine, 8000);  // wraps at 7200
            juce::Thread::sleep(50); sent = raw->take();
            expect(std::count(sent.begin(), sent.end(), Msg{0x81, 60, 0}) >= 1);
            expect(engine.setLoop(0, 0, false)); engine.seekToSeconds(3.9); engine.pause(); raw->take();
            Cues d; d.add(3.95, {0x90, 40, 1}); expect(d.apply(engine)); engine.play(); render(engine, 10000);
            juce::Thread::sleep(50); sent = raw->take();
            expect(!engine.isPlaying()); expect(std::find(sent.begin(), sent.end(), Msg{0x80, 40, 0}) != sent.end());
        }

        beginTest("disableLoop cues fire on the loop's first pass only; plain cues every pass");
        {
            AudioEngine engine; Recorder* raw = nullptr; start(engine, raw);
            Cues c; c.add(0.05, {0xC0, 5}, true); c.add(0.06, {0xC0, 6}); expect(c.apply(engine));
            expect(engine.setLoop(0, 0.1, true)); engine.play(); render(engine, 4800 * 3 + 100); engine.pause();
            juce::Thread::sleep(50); auto sent = raw->take();
            expectEquals(static_cast<int>(std::count(sent.begin(), sent.end(), Msg{0xC0, 5})), 1);
            expectEquals(static_cast<int>(std::count(sent.begin(), sent.end(), Msg{0xC0, 6})), 3);  // passes 1-3 (the 4th stops at 100 frames)
            int queued[8]; expectEquals(engine.pollCues(reinterpret_cast<uint32_t*>(queued), 8), 4);
        }

        beginTest("Starting mid-song chases the last program and controller values before the playhead");
        {
            AudioEngine engine; Recorder* raw = nullptr; start(engine, raw);
            Cues c; c.add(0.1, {0xC2, 7}); c.add(0.2, {0xC2, 9}); c.add(0.3, {0xB2, 7, 100}); c.add(0.4, {0xB2, 7, 90});
            c.add(0.5, {0x92, 60, 100}); c.add(2.0, {0xC2, 11}); expect(c.apply(engine));
            engine.seekToSeconds(1.0); engine.play(); juce::Thread::sleep(50); auto sent = raw->take();
            expect(sent.size() >= 2 && sent[0] == Msg{0xC2, 9} && sent[1] == Msg{0xB2, 7, 90});
            expect(std::find(sent.begin(), sent.end(), Msg{0xC2, 7}) == sent.end());
            expect(std::find(sent.begin(), sent.end(), Msg{0x92, 60, 100}) == sent.end());   // notes are not chased
            engine.pause(); engine.seekToSeconds(0); engine.play(); juce::Thread::sleep(50); sent = raw->take();
            expect(std::find(sent.begin(), sent.end(), Msg{0xC2, 9}) == sent.end());
        }

        beginTest("MUTE MIDI stops cues and the chase; held notes are released and later note-offs still pass");
        {
            AudioEngine engine; Recorder* raw = nullptr; start(engine, raw);
            Cues c; c.add(0.05, {0x93, 50, 100}); c.add(0.1, {0xC3, 4}); c.add(0.2, {0x93, 52, 100}); c.add(0.3, {0x83, 52, 0});
            c.add(0.4, {0x93, 53, 100}); c.add(0.6, {0x83, 53, 0}); expect(c.apply(engine));
            engine.play(); render(engine, 7200); // 0.15 s: note 50 on, program 4
            engine.setMidiCuesMuted(true); expect(engine.areMidiCuesMuted());
            render(engine, 14400);               // to 0.45 s: 52 on/off and 53 on are muted
            juce::Thread::sleep(50); auto sent = raw->take();
            expect(std::find(sent.begin(), sent.end(), Msg{0x83, 50, 0}) != sent.end());   // released by muting
            expect(std::find(sent.begin(), sent.end(), Msg{0x93, 52, 100}) == sent.end());
            expect(std::find(sent.begin(), sent.end(), Msg{0x93, 53, 100}) == sent.end());
            expect(std::find(sent.begin(), sent.end(), Msg{0x83, 52, 0}) == sent.end());    // not held: dropped
            engine.setMidiCuesMuted(false); render(engine, 9600);  // to 0.65 s: 53 off passes (53 never sounded)
            engine.pause(); engine.seekToSeconds(0.5); juce::Thread::sleep(50); raw->take();
            engine.setMidiCuesMuted(true); engine.play(); juce::Thread::sleep(50);
            expect(raw->take().empty());   // no chase of program 4 while muted
            engine.pause();
        }

        beginTest("MIDI input queue: channel voice messages only, packed, bounded");
        {
            AudioEngine engine;
            const uint8_t note[3] = {0x93, 64, 127}, pc[2] = {0xC1, 4}, clock[1] = {0xF8}, bad[3] = {0x40, 1, 2};
            expect(engine.injectMidiInput(note, 3)); expect(engine.injectMidiInput(pc, 2));
            expect(!engine.injectMidiInput(clock, 1)); expect(!engine.injectMidiInput(bad, 3)); expect(!engine.injectMidiInput(note, 4));
            uint32_t out[4] = {}; expectEquals(engine.pollMidiInput(out, 4), 2);
            expect(out[0] == (0x93u | 64u << 8 | 127u << 16 | 3u << 24)); expect(out[1] == (0xC1u | 4u << 8 | 2u << 24));
            expectEquals(engine.pollMidiInput(out, 4), 0);
            for (int i = 0; i < MidiInputQueue::kCapacity + 5; ++i) engine.injectMidiInput(note, 3);
            int total = 0; uint32_t many[256]; for (int n; (n = engine.pollMidiInput(many, 256)) > 0;) total += n;
            expectEquals(total, MidiInputQueue::kCapacity);
            expect(!engine.openMidiInput("no-such-device")); expect(!engine.isMidiInputOpen());
        }
        dir.deleteRecursively();
    }
} midiEventTests;
