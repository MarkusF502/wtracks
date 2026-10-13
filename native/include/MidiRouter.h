#pragma once
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_core/juce_core.h>
#include <algorithm>
#include <array>
#include <atomic>
#include <memory>
#include <mutex>
#include <vector>

namespace wtracks {
// Where scheduled MIDI bytes finally go. The real sink wraps juce::MidiOutput; tests install a recording sink.
class MidiSink {
public:
    virtual ~MidiSink() = default;
    // Deliver `size` bytes at `hostTimeMs` (juce::Time::getMillisecondCounterHiRes() clock); a time in the past means "now".
    virtual void send(const uint8_t* bytes, int size, double hostTimeMs) = 0;
};

// Audio-thread producers push events into a fixed lock-free ring (no allocation, no I/O); a dispatcher thread
// timestamps them with a fixed lead and hands them to the sink. Control-thread messages (stop, panic) take a mutex path.
// Exactly one audio thread may call push().
class MidiRouter : private juce::Thread {
public:
    static constexpr int kCapacity = 4096;
    static constexpr double kLeadMs = 20.0;  // Playback's legacy path used now + 10 ms; ours leaves room for the dispatcher wake-up.

    MidiRouter() : juce::Thread("WTracks MIDI dispatcher") {}
    ~MidiRouter() override { close(); }

    // Installs a sink and starts the dispatcher. Replaces any previous sink.
    void open(std::unique_ptr<MidiSink> newSink) {
        close();
        { const std::lock_guard<std::mutex> lock(sinkMutex); sink = std::move(newSink); }
        head.store(0); tail.store(0); dropped.store(0); latest.store(0.0);
        active.store(true, std::memory_order_release);
        startThread();
    }
    void close() {
        active.store(false, std::memory_order_release);
        wake.signal();
        stopThread(2000);
        const std::lock_guard<std::mutex> lock(sinkMutex);
        sink.reset();
    }
    bool isOpen() const noexcept { return active.load(std::memory_order_acquire); }
    uint64_t droppedEvents() const noexcept { return dropped.load(); }

    // Audio thread: realtime safe. `blockHostMs` is the host clock at the start of the audio block.
    bool push(double blockHostMs, int sampleOffset, double rate, const uint8_t* bytes, int size) noexcept {
        if (!active.load(std::memory_order_acquire) || size < 1 || size > 3) return false;
        const auto write = head.load(std::memory_order_relaxed);
        if (write - tail.load(std::memory_order_acquire) >= kCapacity) { dropped.fetch_add(1); return false; }
        auto& slot = ring[write % kCapacity];
        slot.hostMs = blockHostMs + 1000.0 * sampleOffset / rate; slot.size = static_cast<uint8_t>(size);
        for (int i = 0; i < size; ++i) slot.data[i] = bytes[i];
        if (slot.hostMs > latest.load(std::memory_order_relaxed)) latest.store(slot.hostMs, std::memory_order_relaxed);
        head.store(write + 1, std::memory_order_release);
        return true;
    }

    // Control thread: delivered after every event already pushed (never overtakes the tail of a block), otherwise as soon as possible.
    void sendNow(const uint8_t* bytes, int size) {
        if (!isOpen() || size < 1 || size > 3) return;
        { const std::lock_guard<std::mutex> lock(controlMutex);
          Event event; event.hostMs = std::max(juce::Time::getMillisecondCounterHiRes(), latest.load(std::memory_order_relaxed)); event.size = static_cast<uint8_t>(size);
          for (int i = 0; i < size; ++i) event.data[i] = bytes[i];
          control.push_back(event); }
        wake.signal();
    }

    // Blocks until everything queued so far has been handed to the sink (tests and shutdown).
    bool flush(int timeoutMs) {
        const auto deadline = juce::Time::getMillisecondCounter() + static_cast<uint32_t>(timeoutMs);
        while (juce::Time::getMillisecondCounter() < deadline) {
            wake.signal();
            { const std::lock_guard<std::mutex> lock(controlMutex); if (control.empty() && tail.load() == head.load() && !busy.load(std::memory_order_acquire)) return true; }
            juce::Thread::sleep(1);
        }
        return false;
    }

private:
    struct Event { double hostMs = 0; uint8_t size = 0; uint8_t data[3] = {0, 0, 0}; };
    void run() override {
        std::vector<Event> pending;
        while (!threadShouldExit() && active.load(std::memory_order_acquire)) {
            wake.wait(2);
            busy.store(true, std::memory_order_release);  // flush() must not report empty while events are in hand
            pending.clear();
            { const std::lock_guard<std::mutex> lock(controlMutex); pending.swap(control); }
            auto read = tail.load(std::memory_order_relaxed);
            const auto write = head.load(std::memory_order_acquire);
            std::vector<Event> scheduled;
            for (; read != write; ++read) scheduled.push_back(ring[read % kCapacity]);
            // Control messages carry "now"; they keep their place among ring events by timestamp.
            scheduled.insert(scheduled.end(), pending.begin(), pending.end());
            std::stable_sort(scheduled.begin(), scheduled.end(), [](const Event& a, const Event& b) { return a.hostMs < b.hostMs; });
            {
                const std::lock_guard<std::mutex> lock(sinkMutex);
                const double now = juce::Time::getMillisecondCounterHiRes();
                for (const auto& event : scheduled) if (sink) sink->send(event.data, event.size, std::max(event.hostMs + kLeadMs, now));
            }
            tail.store(read, std::memory_order_release);
            busy.store(false, std::memory_order_release);
        }
        busy.store(false, std::memory_order_release);
    }

    std::array<Event, kCapacity> ring {};
    std::atomic<uint64_t> head { 0 }, tail { 0 }, dropped { 0 };
    std::atomic<double> latest { 0.0 };
    std::atomic<bool> active { false }, busy { false };
    juce::WaitableEvent wake;
    std::mutex sinkMutex, controlMutex;
    std::unique_ptr<MidiSink> sink;
    std::vector<Event> control;
};

// Real output through juce::MidiOutput (its own background thread honors the timestamps).
class JuceMidiSink : public MidiSink {
public:
    explicit JuceMidiSink(std::unique_ptr<juce::MidiOutput> device) : output(std::move(device)) { if (output) output->startBackgroundThread(); }
    ~JuceMidiSink() override { if (output) output->stopBackgroundThread(); }
    void send(const uint8_t* bytes, int size, double hostTimeMs) override {
        if (!output) return;
        juce::MidiBuffer buffer; buffer.addEvent(juce::MidiMessage(bytes, size, 0.0), 0);
        output->sendBlockOfMessages(buffer, hostTimeMs, 1000.0);
    }
private:
    std::unique_ptr<juce::MidiOutput> output;
};
}
