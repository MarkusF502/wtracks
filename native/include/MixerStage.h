#pragma once
#include <algorithm>
#include <cmath>

namespace wtracks {
// Reconstructed from MixerAUFramework / BusChannelAUFramework static contracts (see
// analysis/subsystem-contracts.md): a ramped gain, a mute gate, an output base channel and a
// mono/stereo flag. The ramp duration is NOT recovered from the binary; 10 ms is our own choice.
// No pan law and no clipping are applied, matching the observed kernels.
struct GainRamp {
    static constexpr double kSeconds = 0.010;
    float value = 1, target = 1;
    bool primed = false;
    static float stepFor(double sampleRate) noexcept { return static_cast<float>(1.0 / (kSeconds * sampleRate)); }
    // The first target after creation is adopted immediately so a loaded track does not fade in.
    void set(float t) noexcept { target = t; if (!primed) { value = t; primed = true; } }
    bool silent() const noexcept { return value == 0 && target == 0; }
    float next(float step) noexcept {
        if (value < target) value = std::min(target, value + step);
        else if (value > target) value = std::max(target, value - step);
        return value;
    }
};

// Stereo: left -> base, right -> base + 1. Mono: (left + right) / 2 -> base.
// A route outside the device output range produces silence.
struct ChannelRoute {
    int base = 0;
    bool mono = false;
    bool valid(int outputs) const noexcept { return base >= 0 && (mono ? base < outputs : base + 2 <= outputs); }
};

// Adds `source` (two channels) scaled by the per-sample ramp into out[...][start, start + count).
// The ramp advances even when the route is invalid, so state is independent of host block size.
inline void mixStem(const float* left, const float* right, float* const* out, int outputs, int start, int count,
                    ChannelRoute route, GainRamp& ramp, float step) noexcept {
    const bool routed = route.valid(outputs);
    for (int i = 0; i < count; ++i) {
        const float gain = ramp.next(step);
        if (!routed) continue;
        if (route.mono) out[route.base][start + i] += gain * (left[i] + right[i]) * 0.5f;
        else { out[route.base][start + i] += gain * left[i]; out[route.base + 1][start + i] += gain * right[i]; }
    }
}

inline void applyGain(float* const* out, int outputs, int start, int count, GainRamp& ramp, float step) noexcept {
    for (int i = 0; i < count; ++i) {
        const float gain = ramp.next(step);
        if (gain != 1.0f) for (int c = 0; c < outputs; ++c) out[c][start + i] *= gain;
    }
}
}

namespace wtracks {
// Automated variants: target(i) gives the gain target of frame i; the de-click ramp follows it (a target moving slower
// than the ramp step is reproduced exactly, faster changes take the 10 ms ramp).
template <class Target>
inline void mixStemTargets(const float* left, const float* right, float* const* out, int outputs, int start, int count,
                           ChannelRoute route, GainRamp& ramp, float step, Target&& target) noexcept {
    const bool routed = route.valid(outputs);
    for (int i = 0; i < count; ++i) {
        ramp.set(target(i));
        const float gain = ramp.next(step);
        if (!routed) continue;
        if (route.mono) out[route.base][start + i] += gain * (left[i] + right[i]) * 0.5f;
        else { out[route.base][start + i] += gain * left[i]; out[route.base + 1][start + i] += gain * right[i]; }
    }
}

template <class Target>
inline void applyGainTargets(float* const* out, int outputs, int start, int count, GainRamp& ramp, float step, Target&& target) noexcept {
    for (int i = 0; i < count; ++i) {
        ramp.set(target(i));
        const float gain = ramp.next(step);
        if (gain != 1.0f) for (int c = 0; c < outputs; ++c) out[c][start + i] *= gain;
    }
}
}

namespace wtracks {
// Fade out (Playback: transport "5 Second Fade Out", SongArrangement.endFade, excludeFromFade). The curve and what
// happens afterwards were not recovered; ours: linear in amplitude, counted in real (device) samples, and playback pauses
// when it reaches silence. The end fade is a function of the playhead: gain = (end - position) / length, clamped.
struct FadeOut {
    int64_t total = 0, remaining = 0;
    bool active() const noexcept { return remaining > 0; }
    void start(int64_t samples) noexcept { total = remaining = samples > 0 ? samples : 0; }
    void cancel() noexcept { total = remaining = 0; }
    // Gain of frame i of the next chunk (1 when idle); reaches 1/total on the last fading frame.
    float gain(int i) const noexcept { return active() ? static_cast<float>(remaining - i) / static_cast<float>(total) : 1.0f; }
    static float endGain(int64_t position, int64_t end, int64_t length) noexcept {
        if (length <= 0 || position <= end - length) return 1.0f;
        return position >= end ? 0.0f : static_cast<float>(end - position) / static_cast<float>(length);
    }
};
}
