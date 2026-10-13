#pragma once
#include <array>
#include <cmath>
#include <cstdint>
#include <memory>
#include "ClickTimeline.h"
#include "GuideTimeline.h"

namespace wtracks {
// "Song Section Pre-roll" — Playback: "Provides a count-in when playing from the beginning of a section"
// (main-ui-strings.txt). The binary's implementation was not recovered; this one is our own design:
// one bar of the tempo segment that starts at the section (numerator beats of 60/bpm * bpmUnit/denominator),
// accent click on the first beat, quarter click on the others, spoken count "1".."N" on each beat while the
// stems wait. Tails (a spoken "4" is longer than a beat) keep playing after the count-in hands over to the song.
// Control-thread start/cancel and render must be externally synchronized (AudioEngine's channelsLock).
class Preroll {
public:
    static constexpr int kMaxCounts = 16;
    std::array<std::shared_ptr<const GuideTimeline::Sound>, kMaxCounts> counts;  // counts[k-1] speaks "k"

    static bool valid(long double beatSamples, int beats) noexcept {
        return std::isfinite(static_cast<double>(beatSamples)) && beatSamples >= 1 && beats >= 1 && beats <= 64
            && beatSamples * beats <= 86400.0L * 384000.0L;
    }
    bool start(long double beatSamples, int beats) noexcept {
        if (!valid(beatSamples, beats)) return false;
        beat = beatSamples; beatCount = beats; elapsed = 0;
        length = static_cast<int64_t>(std::llround(beatSamples * beats)); nextBeat = 0;
        return true;
    }
    // Drops the count-in and every tail (song replaced, seek, pause, sounds swapped).
    void cancel() noexcept { length = 0; elapsed = 0; nextBeat = 0; for (auto& v : voices) v = {}; }
    int64_t remaining() const noexcept { return length - elapsed; }
    bool active() const noexcept { return remaining() > 0; }

    // Adds `count` frames to every output channel. While the count-in runs it advances by `count` (callers pass at most
    // remaining()); afterwards only tails sound. No allocation, locking or I/O.
    void render(float* const* out, int channels, int destination, int count, const ClickTimeline& click, double rate,
                bool clickAudible, bool guideAudible) noexcept {
        if (!out || channels <= 0 || count <= 0 || !std::isfinite(rate) || rate < 1) return;
        for (int i = 0; i < count; ++i) {
            if (active()) {
                while (nextBeat < beatCount && static_cast<int64_t>(std::llround(beat * nextBeat)) <= elapsed) {
                    trigger(nextBeat == 0 ? 0 : 1, nullptr);
                    if (nextBeat < kMaxCounts && counts[static_cast<size_t>(nextBeat)]) trigger(-1, counts[static_cast<size_t>(nextBeat)].get());
                    ++nextBeat;
                }
                ++elapsed;
            }
            float clickSum = 0, guideSum = 0;
            for (auto& v : voices) {
                if (v.clickVoice < 0 && !v.sound) continue;
                if (v.clickVoice >= 0) {
                    const bool sampled = click.sounds[v.clickVoice].getNumSamples() > 0;
                    const auto& pcm = sampled ? click.sounds[v.clickVoice] : click.fallback[v.clickVoice];
                    const double source = v.age * (sampled ? click.soundRates[v.clickVoice] : click.fallbackRate) / rate;
                    if (pcm.getNumSamples() == 0 || source >= pcm.getNumSamples()) { v = {}; continue; }
                    const int a = static_cast<int>(source), b = std::min(a + 1, pcm.getNumSamples() - 1);
                    const float value = pcm.getSample(0, a) + static_cast<float>(source - a) * (pcm.getSample(0, b) - pcm.getSample(0, a));
                    clickSum += value * static_cast<float>(click.gains[v.clickVoice]);
                } else {
                    const long double cursor = static_cast<long double>(v.age) * v.sound->sourceRate / rate;
                    if (cursor >= v.sound->mono.size()) { v = {}; continue; }
                    const auto frame = static_cast<size_t>(cursor); const float fraction = static_cast<float>(cursor - frame);
                    const float right = frame + 1 < v.sound->mono.size() ? v.sound->mono[frame + 1] : 0;
                    guideSum += v.sound->mono[frame] + (right - v.sound->mono[frame]) * fraction;
                }
                ++v.age;
            }
            const float mixed = (clickAudible ? clickSum * click.masterGain : 0) + (guideAudible ? guideSum : 0);
            if (mixed != 0) for (int ch = 0; ch < channels; ++ch) out[ch][destination + i] += mixed;
        }
    }

private:
    struct Voice { int clickVoice = -1; const GuideTimeline::Sound* sound = nullptr; int64_t age = 0; uint64_t serial = 0; };
    void trigger(int clickVoice, const GuideTimeline::Sound* sound) noexcept {
        auto* slot = &voices[0];
        for (auto& v : voices) {
            if (v.clickVoice < 0 && !v.sound) { slot = &v; break; }
            if (v.serial < slot->serial) slot = &v;
        }
        *slot = {clickVoice, sound, 0, ++serial};
    }
    std::array<Voice, 6> voices {};
    long double beat = 0; int beatCount = 0, nextBeat = 0;
    int64_t length = 0, elapsed = 0; uint64_t serial = 0;
};
}
