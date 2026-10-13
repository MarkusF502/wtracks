#pragma once
#include <cmath>
#include <cstdint>

namespace wtracks {
// MIDI realtime clock (0xF8) at 24 pulses per quarter note, laid on the same beat grid as the click.
// Reconstructed from MIDIClockAUFramework (see analysis/subsystem-contracts.md): 24 pulses per beat and start
// (0xFA at sample <= 4, otherwise 0xFB continue) / stop (0xFC) messages. Playback accumulates truncated periods
// (nextPulse = int(prev + sr*60/(tempo*24))); this timeline derives every pulse from the absolute sample position
// instead, so fractional tempos do not drift. Playback's choice is NOT reproduced.
// Control-thread configuration must be externally synchronized with render().
class MidiClockTimeline {
public:
    static constexpr uint8_t kClock = 0xF8, kStart = 0xFA, kContinue = 0xFB, kStop = 0xFC;
    static constexpr int kPulsesPerQuarter = 24;
    static constexpr int64_t kStartWindowSamples = 4;

    double bpm = 120.0, offset = 0.0;
    int bpmUnit = 4;

    // Calls emit(sampleOffsetInBlock) for every pulse whose rounded sample lies in [position, position + count).
    template <class Emit>
    void render(int count, int64_t position, double rate, Emit&& emit) const {
        if (count <= 0 || !(bpm > 0) || !std::isfinite(rate) || rate <= 0) return;
        const long double pulse = (60.0L / bpm) * rate * bpmUnit / 4.0L / kPulsesPerQuarter;
        const long double origin = static_cast<long double>(offset) * rate;
        for (int i = 0; i < count; ++i) {
            const int64_t sample = position + i;
            const auto index = static_cast<int64_t>(std::floor((sample - origin + 0.5L) / pulse));
            if (index >= 0 && static_cast<int64_t>(std::llround(origin + index * pulse)) == sample) emit(i);
        }
    }

    static uint8_t startMessageFor(int64_t position) noexcept { return position <= kStartWindowSamples ? kStart : kContinue; }
};
}
