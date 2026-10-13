#pragma once
#include <array>
#include <cmath>
#include <cstdint>

namespace wtracks {
// Linear timecode (SMPTE LTC, biphase mark) generator reconstructed from TimecodeAUFramework (see
// analysis/subsystem-contracts.md): rate table read from the Mach-O (24, 25, 30, 30, 30000/1001, 30000/1001, 60,
// 60000/1001, 60, 60000/1001, 50), drop-frame enum mask 0x324 (indices 2, 5, 8, 9), BCD fields, 80 bits per frame, the
// 0xBFFC sync word, bipolar +-1 output, a transition at every bit boundary plus one mid-bit for a 1, and fractional
// samples-per-bit accumulation.
// Differences we chose: every sample is derived from the absolute position (so seeks and loops are exact and no state
// has to be carried), the biphase-mark correction bit keeps the frame start polarity constant, and 60-frame drop-frame
// counts four frames per minute (the binary body sets two; unverified, see the contract's unknowns).
// Configuration changes and render() must be externally synchronized.
class TimecodeGenerator {
public:
    static constexpr int kRateCount = 11;
    struct Rate { int nominal; int64_t numerator, denominator; bool drop; };
    static constexpr std::array<Rate, kRateCount> kRates {{
        {24, 24, 1, false}, {25, 25, 1, false}, {30, 30, 1, true}, {30, 30, 1, false},
        {30, 30000, 1001, false}, {30, 30000, 1001, true}, {60, 60, 1, false}, {60, 60000, 1001, false},
        {60, 60, 1, true}, {60, 60000, 1001, true}, {50, 50, 1, false}}};
    static constexpr int kBitsPerFrame = 80;
    static constexpr uint16_t kSyncWord = 0xBFFC;  // bits 64..79 as stored LSB first (SMPTE 0x3FFD transmitted order)

    struct Fields { int hours = 0, minutes = 0, seconds = 0, frames = 0; bool drop = false; };

    int rateIndex = 3;
    int64_t startFrame = 0;     // timecode label of the first frame, in frames of the selected rate
    double onsetSeconds = 0;    // processed-timeline instant where the first frame begins; silent before it
    float gain = 0.5f;

    static bool valid(int index, int64_t start, double onset, float level) noexcept {
        return index >= 0 && index < kRateCount && start >= 0 && start < framesPerDay(index) && std::isfinite(onset) && onset >= 0
            && onset <= 86400 && std::isfinite(level) && level >= 0 && level <= 1;
    }
    static int dropFramesPerMinute(int index) noexcept { return kRates[static_cast<size_t>(index)].drop ? (kRates[static_cast<size_t>(index)].nominal >= 50 ? 4 : 2) : 0; }
    static int64_t framesPerDay(int index) noexcept {
        const auto& rate = kRates[static_cast<size_t>(index)];
        if (!rate.drop) return static_cast<int64_t>(rate.nominal) * 86400;
        const int d = dropFramesPerMinute(index);
        return (static_cast<int64_t>(rate.nominal) * 600 - 9 * d) * 144;
    }
    static long double framesPerSecond(int index) noexcept {
        const auto& rate = kRates[static_cast<size_t>(index)]; return static_cast<long double>(rate.numerator) / rate.denominator;
    }

    // Frame count (0-based, modulo 24 h) to the fields written into the word.
    static Fields fieldsFor(int index, int64_t count) noexcept {
        const auto& rate = kRates[static_cast<size_t>(index)];
        count %= framesPerDay(index);
        if (rate.drop) {
            const int64_t d = dropFramesPerMinute(index), per10 = rate.nominal * 600LL - 9 * d, perMinute = rate.nominal * 60LL - d;
            const int64_t tens = count / per10, rest = count % per10;
            count += 9 * d * tens + (rest > d ? d * ((rest - d) / perMinute) : 0);
        }
        Fields f; f.drop = rate.drop;
        f.frames = static_cast<int>(count % rate.nominal); count /= rate.nominal;
        f.seconds = static_cast<int>(count % 60); count /= 60;
        f.minutes = static_cast<int>(count % 60); f.hours = static_cast<int>((count / 60) % 24);
        return f;
    }

    // The 80-bit word, bit i at index i. `bits[i]` is 0 or 1.
    static std::array<uint8_t, kBitsPerFrame> wordFor(int index, int64_t count) noexcept {
        const auto f = fieldsFor(index, count);
        std::array<uint8_t, kBitsPerFrame> bits {};
        auto put = [&](int first, int width, int value) { for (int b = 0; b < width; ++b) bits[static_cast<size_t>(first + b)] = (value >> b) & 1; };
        put(0, 4, f.frames % 10); put(8, 2, f.frames / 10); bits[10] = f.drop ? 1 : 0;
        put(16, 4, f.seconds % 10); put(24, 3, f.seconds / 10);
        put(32, 4, f.minutes % 10); put(40, 3, f.minutes / 10);
        put(48, 4, f.hours % 10); put(56, 2, f.hours / 10);
        for (int b = 0; b < 16; ++b) bits[static_cast<size_t>(64 + b)] = (kSyncWord >> b) & 1;
        // Biphase-mark correction: an even number of zeros keeps the polarity at the start of every frame identical.
        const int correction = kRates[static_cast<size_t>(index)].nominal == 25 || kRates[static_cast<size_t>(index)].nominal == 50 ? 59 : 27;
        int zeros = 0; for (auto bit : bits) zeros += bit == 0;
        if (zeros % 2) bits[static_cast<size_t>(correction)] = 1;
        return bits;
    }

    void reset() noexcept { cachedFrame = -1; }

    // Adds the signal to out[0, count) for the samples [position, position + count) of the processed timeline.
    void render(float* out, int count, int64_t position, double rate) noexcept {
        if (!out || count <= 0 || position < 0 || !std::isfinite(rate) || rate < 8000 || rate > 384000 || !valid(rateIndex, startFrame, onsetSeconds, gain)) return;
        const long double samplesPerFrame = static_cast<long double>(rate) / framesPerSecond(rateIndex);
        const long double onset = static_cast<long double>(onsetSeconds) * rate;
        auto frameBegin = [&](int64_t f) { return static_cast<int64_t>(std::llround(onset + static_cast<long double>(f) * samplesPerFrame)); };
        for (int i = 0; i < count; ++i) {
            const int64_t sample = position + i;
            const long double relative = static_cast<long double>(sample) - onset;
            if (relative < 0) continue;
            auto frame = static_cast<int64_t>(std::floor(relative / samplesPerFrame));
            if (sample < frameBegin(frame)) --frame; else if (sample >= frameBegin(frame + 1)) ++frame;
            if (frame < 0) continue;
            if (frame != cachedFrame || rate != cachedRate) { buildFrame(frame, rate, samplesPerFrame, onset); lastBit = 0; }
            if (!(sample >= bitStart[static_cast<size_t>(lastBit)] && (lastBit == kBitsPerFrame - 1 || sample < bitStart[static_cast<size_t>(lastBit + 1)]))) {
                lastBit = kBitsPerFrame - 1;
                while (lastBit > 0 && sample < bitStart[static_cast<size_t>(lastBit)]) --lastBit;
            }
            float level = startLevel[static_cast<size_t>(lastBit)];
            if (bits[static_cast<size_t>(lastBit)] && sample >= bitMid[static_cast<size_t>(lastBit)]) level = -level;
            out[i] += level * gain;
        }
    }

private:
    void buildFrame(int64_t frame, double rate, long double samplesPerFrame, long double onset) noexcept {
        cachedFrame = frame; cachedRate = rate;
        bits = wordFor(rateIndex, startFrame + frame);
        const long double begin = onset + static_cast<long double>(frame) * samplesPerFrame, perBit = samplesPerFrame / kBitsPerFrame;
        frameStart = static_cast<int64_t>(std::llround(begin));
        float level = 1.0f;  // polarity before the first boundary transition (identical at every frame start)
        for (int b = 0; b < kBitsPerFrame; ++b) {
            bitStart[static_cast<size_t>(b)] = static_cast<int64_t>(std::llround(begin + b * perBit));
            bitMid[static_cast<size_t>(b)] = static_cast<int64_t>(std::llround(begin + (b + 0.5L) * perBit));
            level = -level;  // transition at every bit boundary
            startLevel[static_cast<size_t>(b)] = level;
            if (bits[static_cast<size_t>(b)]) level = -level;  // extra transition in the middle of a 1
        }
    }
    int64_t cachedFrame = -1, frameStart = 0;
    int lastBit = 0;
    double cachedRate = 0;
    std::array<uint8_t, kBitsPerFrame> bits {};
    std::array<int64_t, kBitsPerFrame> bitStart {}, bitMid {};
    std::array<float, kBitsPerFrame> startLevel {};
};
}
