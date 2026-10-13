#pragma once
#include <juce_audio_formats/juce_audio_formats.h>
#include <array>
#include <cmath>
#include <vector>
#include "TempoMap.h"

namespace wtracks {
// Scheduling is derived from the master sample position, never from rounded periods.
// Control-thread operations are protected by AudioEngine's channelsLock.
class ClickTimeline {
public:
    double bpm = 120.0, offset = 0.0;
    std::vector<TempoChange> changes;  // after the base segment; see TempoMap.h
    int numerator = 4, denominator = 4, bpmUnit = 4;
    std::array<double, 4> gains {{1.0, 1.0, 0.0, 0.0}};
    float masterGain = 1.0f;
    std::array<juce::AudioBuffer<float>, 4> sounds;
    std::array<juce::AudioBuffer<float>, 4> fallback;
    double fallbackRate = 44100;
    std::array<double, 4> soundRates {{44100,44100,44100,44100}};
    std::array<int64_t, 4> starts {{-1,-1,-1,-1}};
    static bool unitValid(int value) { return value > 0 && value <= 64 && (value & (value-1)) == 0; }
    static bool valid(double tempo, int n, int d, int unit, double off, const std::array<double,4>& levels) {
        if (!std::isfinite(tempo) || tempo < 1 || tempo > 1000 || n < 1 || n > 64 || !unitValid(d) || !unitValid(unit)
            || !std::isfinite(off) || off < 0 || off > 86400) return false;
        for (auto level : levels) if (!std::isfinite(level) || level < 0 || level > 2) return false;
        return true;
    }
    void reset() { starts.fill(-1); }
    void render(juce::AudioBuffer<float>& output, int destination, int count, int64_t position, double rate, bool audible) {
        for (int i=0; i<count; ++i) {
            const int64_t sample = position+i;
            const auto where = locateTempo(bpm, numerator, denominator, offset, changes, sample, rate);
            const long double tick = (60.0L / where.bpm) * rate * bpmUnit / where.denominator / 4.0L;
            const auto index = static_cast<int64_t>(std::floor((sample-where.origin+0.5L) / tick));
            if (index >= 0 && sample < where.limit && static_cast<int64_t>(std::llround(where.origin+index*tick)) == sample) {
                const int sub = static_cast<int>(index % 4);
                const int voice = sub == 0 ? ((index/4)%where.numerator == 0 ? 0 : 1) : (sub == 2 ? 2 : 3);
                starts[voice] = sample;
            }
            float sum = 0;
            for (int voice=0; voice<4; ++voice) {
                if (starts[voice] < 0) continue;
                const int64_t age = sample-starts[voice];
                if (age < 0) { starts[voice]=-1; continue; }
                const bool sampled = sounds[voice].getNumSamples() > 0;
                const auto& sound = sampled ? sounds[voice] : fallback[voice];
                const double source = age * (sampled ? soundRates[voice] : fallbackRate) / rate;
                if (source >= sound.getNumSamples()) { starts[voice]=-1; continue; }
                const int a = static_cast<int>(source), b = juce::jmin(a+1,sound.getNumSamples()-1);
                const float value = sound.getSample(0,a) + static_cast<float>(source-a)*(sound.getSample(0,b)-sound.getSample(0,a));
                sum += value * static_cast<float>(gains[voice]);
            }
            if (audible) for (int ch=0;ch<output.getNumChannels();++ch) output.addSample(ch,destination+i,sum*masterGain);
        }
    }
};
}
