#pragma once
#include <algorithm>
#include <atomic>
#include <cmath>
#include <complex>
#include <cstdint>
#include <vector>

namespace wtracks {
// Own offline time-stretch / pitch-shift. Playback renders processed copies with the proprietary zplane
// Elastique engine (see analysis/timepitch-contract.md); this is NOT equivalent to it. Method: phase vocoder with
// identity phase locking stretches by timeFactor*pitchFactor, then a windowed-sinc resampler reads it at pitchFactor.
namespace timepitch {

inline constexpr double kMinTime = 0.25, kMaxTime = 4.0, kMinPitch = 0.5, kMaxPitch = 2.0;

struct Options {
    double timeFactor = 1.0;   // output length / input length
    double pitchFactor = 1.0;  // frequency ratio (2.0 = octave up)
    bool complex = true;       // longer analysis window: finer pitch resolution, more transient smearing
};

inline bool valid(const Options& o) noexcept {
    return std::isfinite(o.timeFactor) && std::isfinite(o.pitchFactor) && o.timeFactor >= kMinTime && o.timeFactor <= kMaxTime
        && o.pitchFactor >= kMinPitch && o.pitchFactor <= kMaxPitch;
}
inline bool isIdentity(const Options& o) noexcept { return o.timeFactor == 1.0 && o.pitchFactor == 1.0; }
inline double semitonesToFactor(double semitones) noexcept { return std::pow(2.0, semitones / 12.0); }

namespace detail {
inline constexpr double kPi = 3.14159265358979323846;

class Fft {
public:
    explicit Fft(int size) : n(size), reversed(static_cast<size_t>(size)), twiddle(static_cast<size_t>(size / 2)) {
        int bits = 0; while ((1 << bits) < n) ++bits;
        for (int i = 0; i < n; ++i) { int r = 0; for (int b = 0; b < bits; ++b) if (i & (1 << b)) r |= 1 << (bits - 1 - b); reversed[static_cast<size_t>(i)] = r; }
        for (int i = 0; i < n / 2; ++i) twiddle[static_cast<size_t>(i)] = std::polar(1.0, -2.0 * kPi * i / n);
    }
    // In-place; inverse is unscaled-then-divided by n.
    void run(std::vector<std::complex<double>>& x, bool inverse) const {
        for (int i = 0; i < n; ++i) { const int j = reversed[static_cast<size_t>(i)]; if (j > i) std::swap(x[static_cast<size_t>(i)], x[static_cast<size_t>(j)]); }
        for (int len = 2; len <= n; len <<= 1) {
            const int half = len / 2, stride = n / len;
            for (int start = 0; start < n; start += len)
                for (int k = 0; k < half; ++k) {
                    auto w = twiddle[static_cast<size_t>(k * stride)]; if (inverse) w = std::conj(w);
                    const auto a = x[static_cast<size_t>(start + k)], b = x[static_cast<size_t>(start + k + half)] * w;
                    x[static_cast<size_t>(start + k)] = a + b; x[static_cast<size_t>(start + k + half)] = a - b;
                }
        }
        if (inverse) for (auto& v : x) v /= n;
    }
    int size() const noexcept { return n; }
private:
    int n; std::vector<int> reversed; std::vector<std::complex<double>> twiddle;
};

inline double wrap(double phase) noexcept { return phase - 2.0 * kPi * std::floor((phase + kPi) / (2.0 * kPi)); }

// Phase-vocoder stretch to round(in.size() * s) samples. Returns false when cancelled.
inline bool stretch(const std::vector<float>& in, double s, int frameSize, std::vector<float>& out, const std::atomic<bool>* cancel) {
    const int64_t n = static_cast<int64_t>(in.size());
    const int64_t outLen = static_cast<int64_t>(std::llround(static_cast<double>(n) * s));
    out.assign(static_cast<size_t>(outLen), 0.f);
    if (n == 0 || outLen == 0) return true;
    const int N = frameSize, bins = N / 2 + 1, quarter = N / 4;
    const int64_t hs = s >= 1.0 ? quarter : std::max<int64_t>(16, std::llround(quarter * s));
    const int64_t frames = (outLen + N) / hs + 2;
    Fft fft(N);
    std::vector<double> window(static_cast<size_t>(N));
    for (int j = 0; j < N; ++j) window[static_cast<size_t>(j)] = 0.5 - 0.5 * std::cos(2.0 * kPi * j / N);
    std::vector<double> acc(static_cast<size_t>(outLen + 2 * N)), norm(acc.size());
    std::vector<std::complex<double>> spectrum(static_cast<size_t>(N));
    std::vector<double> mag(static_cast<size_t>(bins)), phase(static_cast<size_t>(bins)), prevPhase(static_cast<size_t>(bins)),
        synth(static_cast<size_t>(bins)), prevSynth(static_cast<size_t>(bins)), locked(static_cast<size_t>(bins));
    std::vector<int> peaks;
    int64_t previousCenter = 0;
    for (int64_t k = 0; k < frames; ++k) {
        if (cancel && cancel->load(std::memory_order_relaxed)) return false;
        const int64_t center = static_cast<int64_t>(std::llround(static_cast<double>(k * hs) / s));
        // Zero-phase framing: the frame centre sits at index 0 so a stationary partial has coherent bin phases.
        for (int j = 0; j < N; ++j) {
            const int64_t i = center - N / 2 + j;
            const double v = (i >= 0 && i < n) ? static_cast<double>(in[static_cast<size_t>(i)]) * window[static_cast<size_t>(j)] : 0.0;
            spectrum[static_cast<size_t>((j + N / 2) % N)] = v;
        }
        fft.run(spectrum, false);
        for (int b = 0; b < bins; ++b) { mag[static_cast<size_t>(b)] = std::abs(spectrum[static_cast<size_t>(b)]); phase[static_cast<size_t>(b)] = std::arg(spectrum[static_cast<size_t>(b)]); }
        if (k == 0) synth = phase;
        else {
            const double da = static_cast<double>(center - previousCenter);
            for (int b = 0; b < bins; ++b) {
                const double omega = 2.0 * kPi * b / N;
                const double deviation = wrap(phase[static_cast<size_t>(b)] - prevPhase[static_cast<size_t>(b)] - omega * da);
                const double bin = omega + (da > 0 ? deviation / da : 0.0);
                synth[static_cast<size_t>(b)] = prevSynth[static_cast<size_t>(b)] + static_cast<double>(hs) * bin;
            }
            // Identity phase locking (Laroche & Dolson): bins of a peak's region keep their analysis phase offsets to it.
            peaks.clear();
            for (int b = 0; b < bins; ++b) {
                bool top = mag[static_cast<size_t>(b)] > 0;
                for (int d = 1; d <= 2 && top; ++d) {
                    if (b - d >= 0 && mag[static_cast<size_t>(b - d)] >= mag[static_cast<size_t>(b)]) top = false;
                    if (b + d < bins && mag[static_cast<size_t>(b + d)] > mag[static_cast<size_t>(b)]) top = false;
                }
                if (top) peaks.push_back(b);
            }
            if (!peaks.empty()) {
                locked = synth;
                for (size_t p = 0; p < peaks.size(); ++p) {
                    const int peak = peaks[p];
                    const int lo = p == 0 ? 0 : (peaks[p - 1] + peak + 1) / 2, hi = p + 1 == peaks.size() ? bins - 1 : (peak + peaks[p + 1]) / 2;
                    for (int b = lo; b <= hi; ++b)
                        locked[static_cast<size_t>(b)] = synth[static_cast<size_t>(peak)] + (phase[static_cast<size_t>(b)] - phase[static_cast<size_t>(peak)]);
                }
                synth = locked;
            }
        }
        prevPhase = phase; prevSynth = synth; previousCenter = center;
        for (int b = 0; b < bins; ++b) spectrum[static_cast<size_t>(b)] = std::polar(mag[static_cast<size_t>(b)], synth[static_cast<size_t>(b)]);
        for (int b = 1; b < N / 2; ++b) spectrum[static_cast<size_t>(N - b)] = std::conj(spectrum[static_cast<size_t>(b)]);
        spectrum[0].imag(0); spectrum[static_cast<size_t>(N / 2)].imag(0);
        fft.run(spectrum, true);
        // Output index t corresponds to acc[t + N/2]; synthesis frame k is centred on t = k * hs.
        const int64_t base = k * hs;  // acc index of the frame's first sample
        for (int j = 0; j < N; ++j) {
            const int64_t at = base + j;
            if (at < 0 || at >= static_cast<int64_t>(acc.size())) continue;
            const double w = window[static_cast<size_t>(j)];
            acc[static_cast<size_t>(at)] += spectrum[static_cast<size_t>((j + N / 2) % N)].real() * w;
            norm[static_cast<size_t>(at)] += w * w;
        }
    }
    for (int64_t t = 0; t < outLen; ++t) {
        const auto at = static_cast<size_t>(t + N / 2);
        out[static_cast<size_t>(t)] = norm[at] > 1e-3 ? static_cast<float>(acc[at] / norm[at]) : 0.f;
    }
    return true;
}

// Windowed-sinc read at `ratio` input samples per output sample, producing exactly `outLen` samples.
// The kernel is tabulated (kResolution points per input sample, linear interpolation) so no trigonometry runs per tap.
inline bool resample(const std::vector<float>& in, double ratio, int64_t outLen, std::vector<float>& out, const std::atomic<bool>* cancel) {
    constexpr int kZeroCrossings = 16, kResolution = 512;
    const double cutoff = std::min(1.0, 1.0 / ratio);
    const int half = static_cast<int>(std::ceil(kZeroCrossings / cutoff));
    const int64_t n = static_cast<int64_t>(in.size());
    std::vector<double> table(static_cast<size_t>(half * kResolution + 2));
    for (size_t i = 0; i < table.size(); ++i) {
        const double distance = static_cast<double>(i) / kResolution;  // input samples from the read position
        const double x = distance * cutoff;
        const double sinc = x < 1e-12 ? 1.0 : std::sin(kPi * x) / (kPi * x);
        const double u = distance / half;
        const double blackman = u >= 1.0 ? 0.0 : 0.42 + 0.5 * std::cos(kPi * u) + 0.08 * std::cos(2.0 * kPi * u);
        table[i] = sinc * cutoff * blackman;
    }
    out.assign(static_cast<size_t>(outLen), 0.f);
    for (int64_t i = 0; i < outLen; ++i) {
        if ((i & 0xFFFF) == 0 && cancel && cancel->load(std::memory_order_relaxed)) return false;
        const double position = static_cast<double>(i) * ratio;
        const int64_t centre = static_cast<int64_t>(std::floor(position));
        const int64_t first = std::max<int64_t>(centre - half + 1, 0), last = std::min<int64_t>(centre + half, n - 1);
        double sum = 0;
        for (int64_t index = first; index <= last; ++index) {
            const double scaled = std::fabs(static_cast<double>(index) - position) * kResolution;
            const auto slot = static_cast<size_t>(scaled);
            const double fraction = scaled - static_cast<double>(slot);
            sum += static_cast<double>(in[static_cast<size_t>(index)]) * (table[slot] + (table[slot + 1] - table[slot]) * fraction);
        }
        out[static_cast<size_t>(i)] = static_cast<float>(sum);
    }
    return true;
}

inline int frameSizeFor(double sampleRate, bool complex) {
    const double seconds = complex ? 0.0929 : 0.0464;
    return 1 << static_cast<int>(std::lround(std::log2(std::max(256.0, sampleRate * seconds))));
}
}  // namespace detail

// One channel. `finalLength` = round(input.size() * timeFactor). Returns false on invalid options or cancellation.
inline bool processChannel(const std::vector<float>& channel, double sampleRate, const Options& options,
                           std::vector<float>& result, const std::atomic<bool>* cancel = nullptr) {
    result.clear();
    if (!valid(options) || !std::isfinite(sampleRate) || sampleRate < 8000 || sampleRate > 384000) return false;
    if (isIdentity(options)) { result = channel; return true; }
    const int64_t finalLength = static_cast<int64_t>(std::llround(static_cast<double>(channel.size()) * options.timeFactor));
    const double stretchFactor = options.timeFactor * options.pitchFactor;
    const bool needStretch = std::fabs(stretchFactor - 1.0) > 1e-12;
    std::vector<float> stretched;
    if (needStretch && !detail::stretch(channel, stretchFactor, detail::frameSizeFor(sampleRate, options.complex), stretched, cancel)) return false;
    const std::vector<float>& source = needStretch ? stretched : channel;
    if (options.pitchFactor == 1.0) result = source;
    else if (!detail::resample(source, options.pitchFactor, finalLength, result, cancel)) { result.clear(); return false; }
    result.resize(static_cast<size_t>(finalLength), 0.f);
    return true;
}

// Processes every channel independently (stereo phase relations are not locked between channels).
// Returns false on invalid options or cancellation; `output` is then left empty.
inline bool process(const std::vector<std::vector<float>>& input, double sampleRate, const Options& options,
                    std::vector<std::vector<float>>& output, const std::atomic<bool>* cancel = nullptr) {
    output.clear();
    if (input.empty()) return false;
    for (const auto& channel : input) if (channel.size() != input.front().size()) return false;
    for (const auto& channel : input) {
        std::vector<float> result;
        if (!processChannel(channel, sampleRate, options, result, cancel)) { output.clear(); return false; }
        output.push_back(std::move(result));
    }
    return true;
}
}  // namespace timepitch
}  // namespace wtracks
