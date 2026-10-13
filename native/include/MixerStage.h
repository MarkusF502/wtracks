#pragma once
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>

namespace wtracks {
// Reconstructed from MixerAUFramework / BusChannelAUFramework (subsystem-contracts.md, pseudocode/frameworks): a ramped
// gain, a mute gate, an output base channel and a mono/stereo flag. ParameterRamper::dezipperCheck ramps linearly from
// the current value to a new target over a fixed number of frames, set at allocation to sampleRate * 0.02 (20 ms) in both
// BusChannelAudioUnit and MixerAudioUnit. Own additions: a target that moves no faster than one ramp's worth per frame
// (automation, fades) is followed exactly, and a new target during a running ramp keeps its end time.
// No pan law and no clipping are applied, matching the observed kernels.
struct GainRamp {
    static constexpr double kSeconds = 0.020;
    float value = 1, target = 1, step = 0;
    int remaining = 0;
    bool primed = false;
    static int framesFor(double sampleRate) noexcept { return std::max(1, static_cast<int>(sampleRate * kSeconds)); }
    // The first target after creation is adopted immediately so a loaded track does not fade in.
    void set(float t, int frames) noexcept {
        if (!primed) { value = target = t; primed = true; return; }
        if (t == target) return;
        target = t;
        if (remaining > 0) { step = (t - value) / static_cast<float>(remaining); return; }
        if (std::abs(t - value) <= 1.0f / static_cast<float>(frames)) { value = t; step = 0; return; }
        remaining = frames; step = (t - value) / static_cast<float>(frames);
    }
    bool silent() const noexcept { return value == 0 && target == 0 && remaining == 0; }
    float next() noexcept {
        if (remaining > 0) { value += step; if (--remaining == 0) value = target; }
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
// Returns the peak of what the channel contributed (post-fader; 0 when the route is invalid) for the meters.
inline float mixStem(const float* left, const float* right, float* const* out, int outputs, int start, int count,
                     ChannelRoute route, GainRamp& ramp) noexcept {
    const bool routed = route.valid(outputs);
    float peak = 0;
    for (int i = 0; i < count; ++i) {
        const float gain = ramp.next();
        if (!routed) continue;
        if (route.mono) {
            const float v = gain * (left[i] + right[i]) * 0.5f;
            out[route.base][start + i] += v; peak = std::max(peak, std::abs(v));
        } else {
            const float l = gain * left[i], r = gain * right[i];
            out[route.base][start + i] += l; out[route.base + 1][start + i] += r;
            peak = std::max(peak, std::max(std::abs(l), std::abs(r)));
        }
    }
    return peak;
}

inline void applyGain(float* const* out, int outputs, int start, int count, GainRamp& ramp) noexcept {
    for (int i = 0; i < count; ++i) {
        const float gain = ramp.next();
        if (gain != 1.0f) for (int c = 0; c < outputs; ++c) out[c][start + i] *= gain;
    }
}
}

namespace wtracks {
// Automated variants: target(i) gives the gain target of frame i; the de-zipper ramp follows it (a target moving no
// faster than one ramp per frame is reproduced exactly, jumps take the 20 ms ramp).
template <class Target>
inline float mixStemTargets(const float* left, const float* right, float* const* out, int outputs, int start, int count,
                            ChannelRoute route, GainRamp& ramp, int frames, Target&& target) noexcept {
    const bool routed = route.valid(outputs);
    float peak = 0;
    for (int i = 0; i < count; ++i) {
        ramp.set(target(i), frames);
        const float gain = ramp.next();
        if (!routed) continue;
        if (route.mono) {
            const float v = gain * (left[i] + right[i]) * 0.5f;
            out[route.base][start + i] += v; peak = std::max(peak, std::abs(v));
        } else {
            const float l = gain * left[i], r = gain * right[i];
            out[route.base][start + i] += l; out[route.base + 1][start + i] += r;
            peak = std::max(peak, std::max(std::abs(l), std::abs(r)));
        }
    }
    return peak;
}

template <class Target>
inline void applyGainTargets(float* const* out, int outputs, int start, int count, GainRamp& ramp, int frames, Target&& target) noexcept {
    for (int i = 0; i < count; ++i) {
        ramp.set(target(i), frames);
        const float gain = ramp.next();
        if (gain != 1.0f) for (int c = 0; c < outputs; ++c) out[c][start + i] *= gain;
    }
}
}

namespace wtracks {
// Fade out (Playback: transport "5 Second Fade Out"; SongTrack fades default to 5.0 s, `currentFadeVolume`,
// `fadeWorkItem` — pseudocode/fade.c FUN_10002a5fc). The per-track volume stepping curve was not recovered; ours is
// linear in amplitude, counted in real (device) samples, and playback pauses when it reaches silence.
struct FadeOut {
    int64_t total = 0, remaining = 0;
    bool active() const noexcept { return remaining > 0; }
    void start(int64_t samples) noexcept { total = remaining = samples > 0 ? samples : 0; }
    void cancel() noexcept { total = remaining = 0; }
    // Gain of frame i of the next chunk (1 when idle); reaches 1/total on the last fading frame.
    float gain(int i) const noexcept { return active() ? static_cast<float>(remaining - i) / static_cast<float>(total) : 1.0f; }
};
}

namespace wtracks {
// Peak meters (Playback: MixerVUMeterView; ballistics not recovered). The audio thread raises a held peak with a
// lock-free max; the reader takes it and resets it, so each read covers everything since the previous one.
struct PeakMeter {
    std::atomic<float> held { 0.0f };
    void raise(float peak) noexcept {
        float current = held.load(std::memory_order_relaxed);
        while (peak > current && !held.compare_exchange_weak(current, peak, std::memory_order_relaxed)) {}
    }
    float take() noexcept { return held.exchange(0.0f, std::memory_order_relaxed); }
};
}
