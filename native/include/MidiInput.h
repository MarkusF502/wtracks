#pragma once
#include <juce_audio_devices/juce_audio_devices.h>
#include <array>
#include <atomic>
#include <cstdint>
#include <memory>

namespace wtracks {
// MIDI input for control mappings (Playback: MIDIDevice.selectedMIDIInEndpointIDs, ControlMapping, "MIDI Mapping 2.0").
// Channel-voice messages (1..3 bytes, no SysEx, no realtime/clock) land in a lock-free single-producer queue that the UI
// polls; the mapping itself lives in Dart. inject() feeds the same queue (tests, no hardware here).
class MidiInputQueue {
public:
    static constexpr int kCapacity = 1024;
    // Packed: byte0 | byte1 << 8 | byte2 << 16 | size << 24.
    bool push(const uint8_t* bytes, int size) noexcept {
        if (!bytes || size < 1 || size > 3 || bytes[0] < 0x80 || bytes[0] >= 0xF0) return false;
        uint32_t packed = static_cast<uint32_t>(size) << 24;
        for (int i = 0; i < size; ++i) packed |= static_cast<uint32_t>(bytes[i] & (i ? 0x7F : 0xFF)) << (8 * i);
        const auto write = head.load(std::memory_order_relaxed);
        if (write - tail.load(std::memory_order_acquire) >= kCapacity) { dropped.fetch_add(1); return false; }
        ring[write % kCapacity].store(packed, std::memory_order_relaxed);
        head.store(write + 1, std::memory_order_release);
        return true;
    }
    int poll(uint32_t* out, int maxCount) noexcept {
        if (!out || maxCount <= 0) return 0;
        int n = 0; auto read = tail.load(std::memory_order_relaxed); const auto write = head.load(std::memory_order_acquire);
        while (read != write && n < maxCount) out[n++] = ring[(read++) % kCapacity].load(std::memory_order_relaxed);
        tail.store(read, std::memory_order_release); return n;
    }
    void clear() noexcept { tail.store(head.load(std::memory_order_acquire), std::memory_order_release); }
    uint64_t droppedCount() const noexcept { return dropped.load(); }
private:
    std::array<std::atomic<uint32_t>, kCapacity> ring {};
    std::atomic<uint64_t> head { 0 }, tail { 0 }, dropped { 0 };
};

// One input device. JUCE calls back on its MIDI thread; the callback only pushes into the queue.
class MidiInputPort : private juce::MidiInputCallback {
public:
    explicit MidiInputPort(MidiInputQueue& target) : queue(target) {}
    ~MidiInputPort() override { close(); }
    bool open(const juce::String& identifier) {
        close();
        device = juce::MidiInput::openDevice(identifier, this);
        if (!device) return false;
        device->start(); return true;
    }
    void close() { if (device) { device->stop(); device.reset(); } }
    bool isOpen() const noexcept { return device != nullptr; }
private:
    void handleIncomingMidiMessage(juce::MidiInput*, const juce::MidiMessage& message) override {
        const auto size = message.getRawDataSize();
        if (size >= 1 && size <= 3) queue.push(message.getRawData(), size);
    }
    MidiInputQueue& queue;
    std::unique_ptr<juce::MidiInput> device;
};
}
