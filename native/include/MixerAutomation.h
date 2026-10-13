#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <vector>

namespace wtracks {
// Mixer automation (Playback: AutomationCue{transitionBeats, sequenceTimecode, applyTransitionLengthCorrection,
// storedItems} / AutomationItem{automationID, storedValue}; "Transition length is the length of time (in beats) the
// faders will start leading to the Automation point. Mute or unmute changes are instant."). The kernel that applies the
// items was not recovered; this is our own design:
//  - a point moves one parameter linearly from its value at `start` to `value` at `end` (the automation point); a mute
//    point has start == end and switches at the point;
//  - per parameter, points are ordered by start and end; a point that starts inside the previous ramp cuts it there and
//    starts from the value reached (callers apply Playback's "transition length correction" by clamping starts);
//  - before a parameter's first point its manual value (the "base") applies; the value is a pure function of the
//    playhead, so seeks and loop wraps land on the automated state.
// Times are song seconds; evaluation maps them to processed samples (time scale) at the device rate.
// Control-thread configure/setBase and render must be externally synchronized (AudioEngine's channelsLock).
class MixerAutomation {
public:
    static constexpr int kChannels = 64;
    static constexpr int kMaster = 2 * kChannels;  // params: [0,64) channel volume, [64,128) channel mute, 128 master
    static constexpr int kParams = kMaster + 1;
    static constexpr size_t kMaxPoints = 16384;
    static int volume(int channel) noexcept { return channel; }
    static int mute(int channel) noexcept { return kChannels + channel; }
    static bool isMute(int param) noexcept { return param >= kChannels && param < kMaster; }

    struct Point { double start = 0, end = 0; int param = 0; float value = 0; };

    static bool valueValid(int param, float value) noexcept {
        if (!std::isfinite(value)) return false;
        if (isMute(param)) return value == 0.0f || value == 1.0f;
        return value >= 0.0f && value <= (param == kMaster ? 2.0f : 1.0f);
    }

    // Points of one parameter must appear with non-decreasing start and end; mute points must be instant.
    bool configure(const std::vector<Point>& points) {
        if (points.size() > kMaxPoints) return false;
        std::array<std::vector<Segment>, kParams> proposed;
        for (const auto& p : points) {
            if (p.param < 0 || p.param >= kParams || !std::isfinite(p.start) || !std::isfinite(p.end) || p.start < 0
                || p.end > 86400 || p.start > p.end || (isMute(p.param) && p.start != p.end) || !valueValid(p.param, p.value)) return false;
            auto& list = proposed[static_cast<size_t>(p.param)];
            if (!list.empty() && (p.start < list.back().start || p.end < list.back().end)) return false;
            list.push_back({p.start, p.end, 0, p.value});
        }
        segments.swap(proposed);
        for (int param = 0; param < kParams; ++param) chain(param);
        return true;
    }
    void clear() { for (auto& list : segments) list.clear(); }
    size_t size() const noexcept { size_t n = 0; for (const auto& list : segments) n += list.size(); return n; }
    bool has(int param) const noexcept { return param >= 0 && param < kParams && !segments[static_cast<size_t>(param)].empty(); }
    void setTimeScale(double scale) noexcept { timeScale = scale; }

    // Manual value of the parameter; recomputes where its automation chain starts from. No allocation.
    void setBase(int param, float value) noexcept {
        if (param < 0 || param >= kParams || base[static_cast<size_t>(param)] == value) return;
        base[static_cast<size_t>(param)] = value; chain(param);
    }
    float baseOf(int param) const noexcept { return param >= 0 && param < kParams ? base[static_cast<size_t>(param)] : 0.0f; }

    // Value at `sample` of the processed timeline. No allocation, locking or I/O.
    float value(int param, int64_t sample, double rate) const noexcept {
        if (param < 0 || param >= kParams) return 0;
        const auto& list = segments[static_cast<size_t>(param)];
        size_t lo = 0, hi = list.size();  // first segment whose start lies beyond the sample
        while (lo < hi) { const size_t mid = (lo + hi) / 2; if (toSample(list[mid].start, rate) <= sample) lo = mid + 1; else hi = mid; }
        if (lo == 0) return base[static_cast<size_t>(param)];
        return evaluate(list[lo - 1], sample, rate);
    }

private:
    struct Segment { double start, end; float from, to; };
    int64_t toSample(double seconds, double rate) const noexcept { return static_cast<int64_t>(std::llround(seconds * timeScale * rate)); }
    float evaluate(const Segment& s, int64_t sample, double rate) const noexcept {
        const int64_t a = toSample(s.start, rate), b = toSample(s.end, rate);
        if (sample >= b || b <= a) return s.to;
        const double t = static_cast<double>(sample - a) / static_cast<double>(b - a);
        return static_cast<float>(s.from + (s.to - s.from) * t);
    }
    // Each segment starts from the value its predecessor reached at its start (cut ramps), the first from the base.
    void chain(int param) noexcept {
        auto& list = segments[static_cast<size_t>(param)];
        for (size_t i = 0; i < list.size(); ++i) {
            if (i == 0) { list[i].from = base[static_cast<size_t>(param)]; continue; }
            const auto& p = list[i - 1];
            if (list[i].start >= p.end || p.end <= p.start) list[i].from = p.to;
            else list[i].from = static_cast<float>(p.from + (p.to - p.from) * (list[i].start - p.start) / (p.end - p.start));
        }
    }
    std::array<std::vector<Segment>, kParams> segments;
    std::array<float, kParams> base {};
    double timeScale = 1;
};
}
