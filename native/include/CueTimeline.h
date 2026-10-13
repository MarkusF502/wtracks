#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <vector>

namespace wtracks {
// Timed cues shared by the MIDIOut and Automation reconstructions: each cue fires once when the playhead reaches its
// rounded sample; simultaneous cues drain in order (MIDIOut behavior; Automation emits one cue per frame, which this
// timeline does not reproduce). Seek skips cues before the playhead and does not replay; a loop wrap or explicit
// reset() re-arms from the playhead. Playback's literal 1764-sample pre-transition adjustment is not reproduced.
// Cues may carry a MIDI channel-voice message that the engine forwards to the MIDI output.
class CueTimeline {
public:
    struct Cue {
        double timeSeconds = 0;
        uint8_t midiSize = 0;       // 0 = no message
        uint8_t midi[3] = {0, 0, 0};
    };
    static constexpr size_t kMaxCues = 4096;

    // Channel voice messages only; data bytes below 0x80; program change / channel pressure carry one data byte.
    static bool midiValid(const Cue& cue) noexcept {
        if (cue.midiSize == 0) return true;
        const uint8_t status = cue.midi[0];
        if (status < 0x80 || status > 0xEF) return false;
        const uint8_t kind = status & 0xF0;
        const uint8_t expected = (kind == 0xC0 || kind == 0xD0) ? 2 : 3;
        if (cue.midiSize != expected) return false;
        for (int i = 1; i < expected; ++i) if (cue.midi[i] > 0x7F) return false;
        return true;
    }

    bool configure(std::vector<Cue> proposed, double maxSeconds) {
        if (proposed.size() > kMaxCues) return false;
        double previous = 0;
        for (const auto& cue : proposed) {
            if (!std::isfinite(cue.timeSeconds) || cue.timeSeconds < 0 || cue.timeSeconds > maxSeconds || cue.timeSeconds < previous || !midiValid(cue)) return false;
            previous = cue.timeSeconds;
        }
        cues = std::move(proposed); reset(); return true;
    }
    void setTimeScale(double scale) noexcept { timeScale = scale; reset(); }
    void reset() noexcept { initialized = false; }
    size_t size() const noexcept { return cues.size(); }
    const Cue& at(size_t index) const { return cues[index]; }

    // emit(cueIndex, sampleOffsetInBlock) for every cue reached in [position, position + count).
    template <class Emit>
    void render(int count, int64_t position, double rate, Emit&& emit) {
        if (count <= 0 || position < 0 || !std::isfinite(rate) || rate <= 0) return;
        if (!initialized || rate != cachedRate || position != expectedPosition) {
            cachedRate = rate; next = 0;
            while (next < cues.size() && eventSample(cues[next]) < position) ++next;
            initialized = true;
        }
        const int64_t end = position + count;
        while (next < cues.size()) {
            const int64_t sample = eventSample(cues[next]);
            if (sample >= end) break;
            emit(next, static_cast<int>(std::max<int64_t>(sample - position, 0)));
            ++next;
        }
        expectedPosition = end;
    }

private:
    int64_t eventSample(const Cue& c) const noexcept { return static_cast<int64_t>(std::llround(c.timeSeconds * timeScale * cachedRate)); }
    std::vector<Cue> cues;
    size_t next = 0;
    double cachedRate = 44100, timeScale = 1;
    int64_t expectedPosition = 0;
    bool initialized = false;
};
}
