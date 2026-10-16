#pragma once
#include <algorithm>
#include <atomic>
#include <cmath>
#include <complex>
#include <functional>
#include <memory>
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

// One phase-vocoder step with identity phase locking. Shared by the whole-buffer [stretch] and the streaming [StretchStream] so
// both run the same arithmetic in the same order (their outputs are bit-identical).
class Vocoder {
public:
    Vocoder(int frameSize, double stretchFactor)
        : N(frameSize), bins(frameSize / 2 + 1), s(stretchFactor), fft(frameSize), windowTable(static_cast<size_t>(frameSize)),
          spectrum(static_cast<size_t>(frameSize)), mag(static_cast<size_t>(bins)), phase(static_cast<size_t>(bins)),
          prevPhase(static_cast<size_t>(bins)), synth(static_cast<size_t>(bins)), prevSynth(static_cast<size_t>(bins)), locked(static_cast<size_t>(bins)) {
        const int quarter = N / 4;
        hs = s >= 1.0 ? quarter : std::max<int64_t>(16, std::llround(quarter * s));
        for (int j = 0; j < N; ++j) windowTable[static_cast<size_t>(j)] = 0.5 - 0.5 * std::cos(2.0 * kPi * j / N);
    }
    int size() const noexcept { return N; }
    int64_t hop() const noexcept { return hs; }
    // Input sample at the centre of analysis frame k.
    int64_t centerOf(int64_t k) const noexcept { return static_cast<int64_t>(std::llround(static_cast<double>(k * hs) / s)); }
    double window(int j) const noexcept { return windowTable[static_cast<size_t>(j)]; }
    // Windowed synthesis sample j of the last frame (to be overlap-added at k * hop() + j, weighted by window(j)^2).
    double output(int j) const noexcept { return spectrum[static_cast<size_t>((j + N / 2) % N)].real() * windowTable[static_cast<size_t>(j)]; }

    // Analyses frame k. `sample(i)` returns input sample i as double, 0 outside the input.
    template <class Sample> void step(int64_t k, Sample&& sample) {
        const int64_t center = centerOf(k);
        // Zero-phase framing: the frame centre sits at index 0 so a stationary partial has coherent bin phases.
        for (int j = 0; j < N; ++j)
            spectrum[static_cast<size_t>((j + N / 2) % N)] = sample(center - N / 2 + j) * windowTable[static_cast<size_t>(j)];
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
    }

private:
    int N, bins; double s; int64_t hs = 0, previousCenter = 0;
    Fft fft;
    std::vector<double> windowTable;
    std::vector<std::complex<double>> spectrum;
    std::vector<double> mag, phase, prevPhase, synth, prevSynth, locked;
    std::vector<int> peaks;
};

// Number of analysis frames for an output of outLen samples (the last ones only add the tail of the window).
inline int64_t frameCount(int64_t outLen, int frameSize, int64_t hop) noexcept { return (outLen + frameSize) / hop + 2; }

// Phase-vocoder stretch to round(in.size() * s) samples, whole buffer in memory. Reference for [StretchStream]. Returns false when cancelled.
inline bool stretch(const std::vector<float>& in, double s, int frameSize, std::vector<float>& out, const std::atomic<bool>* cancel) {
    const int64_t n = static_cast<int64_t>(in.size());
    const int64_t outLen = static_cast<int64_t>(std::llround(static_cast<double>(n) * s));
    out.assign(static_cast<size_t>(outLen), 0.f);
    if (n == 0 || outLen == 0) return true;
    Vocoder vocoder(frameSize, s);
    const int N = frameSize;
    const int64_t hs = vocoder.hop(), frames = frameCount(outLen, N, hs);
    std::vector<double> acc(static_cast<size_t>(outLen + 2 * N)), norm(acc.size());
    for (int64_t k = 0; k < frames; ++k) {
        if (cancel && cancel->load(std::memory_order_relaxed)) return false;
        vocoder.step(k, [&](int64_t i) { return (i >= 0 && i < n) ? static_cast<double>(in[static_cast<size_t>(i)]) : 0.0; });
        // Output index t corresponds to acc[t + N/2]; synthesis frame k is centred on t = k * hs.
        const int64_t base = k * hs;  // acc index of the frame's first sample
        for (int j = 0; j < N; ++j) {
            const int64_t at = base + j;
            if (at < 0 || at >= static_cast<int64_t>(acc.size())) continue;
            const double w = vocoder.window(j);
            acc[static_cast<size_t>(at)] += vocoder.output(j);
            norm[static_cast<size_t>(at)] += w * w;
        }
    }
    for (int64_t t = 0; t < outLen; ++t) {
        const auto at = static_cast<size_t>(t + N / 2);
        out[static_cast<size_t>(t)] = norm[at] > 1e-3 ? static_cast<float>(acc[at] / norm[at]) : 0.f;
    }
    return true;
}

// Windowed-sinc kernel for reading at `ratio` input samples per output sample. Tabulated (kResolution points per input sample,
// linear interpolation) so no trigonometry runs per tap.
struct SincKernel {
    static constexpr int kZeroCrossings = 16, kResolution = 512;
    int half = 0;
    std::vector<double> table;
    explicit SincKernel(double ratio) {
        const double cutoff = std::min(1.0, 1.0 / ratio);
        half = static_cast<int>(std::ceil(kZeroCrossings / cutoff));
        table.resize(static_cast<size_t>(half * kResolution + 2));
        for (size_t i = 0; i < table.size(); ++i) {
            const double distance = static_cast<double>(i) / kResolution;  // input samples from the read position
            const double x = distance * cutoff;
            const double sinc = x < 1e-12 ? 1.0 : std::sin(kPi * x) / (kPi * x);
            const double u = distance / half;
            const double blackman = u >= 1.0 ? 0.0 : 0.42 + 0.5 * std::cos(kPi * u) + 0.08 * std::cos(2.0 * kPi * u);
            table[i] = sinc * cutoff * blackman;
        }
    }
    // Input range [first, last] read for output position `position` of a source with n samples.
    std::pair<int64_t, int64_t> span(double position, int64_t n) const noexcept {
        const int64_t centre = static_cast<int64_t>(std::floor(position));
        return {std::max<int64_t>(centre - half + 1, 0), std::min<int64_t>(centre + half, n - 1)};
    }
    template <class Sample> double read(double position, int64_t n, Sample&& sample) const {
        const auto [first, last] = span(position, n);
        double sum = 0;
        for (int64_t index = first; index <= last; ++index) {
            const double scaled = std::fabs(static_cast<double>(index) - position) * kResolution;
            const auto slot = static_cast<size_t>(scaled);
            const double fraction = scaled - static_cast<double>(slot);
            sum += sample(index) * (table[slot] + (table[slot + 1] - table[slot]) * fraction);
        }
        return sum;
    }
};

// Windowed-sinc read at `ratio` input samples per output sample, producing exactly `outLen` samples. Whole buffer in memory.
inline bool resample(const std::vector<float>& in, double ratio, int64_t outLen, std::vector<float>& out, const std::atomic<bool>* cancel) {
    const SincKernel kernel(ratio);
    const int64_t n = static_cast<int64_t>(in.size());
    out.assign(static_cast<size_t>(outLen), 0.f);
    for (int64_t i = 0; i < outLen; ++i) {
        if ((i & 0xFFFF) == 0 && cancel && cancel->load(std::memory_order_relaxed)) return false;
        out[static_cast<size_t>(i)] = static_cast<float>(kernel.read(static_cast<double>(i) * ratio, n,
            [&](int64_t index) { return static_cast<double>(in[static_cast<size_t>(index)]); }));
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

// ---- streaming (Fase C: memory no longer grows with the song) ----

namespace detail {
// Sliding window over a signal: samples [start, end()) are kept; older ones are dropped in amortized O(1).
struct Window {
    int64_t start = 0;
    std::vector<float> data;
    int64_t end() const noexcept { return start + static_cast<int64_t>(data.size()); }
    float operator[](int64_t i) const noexcept { return data[static_cast<size_t>(i - start)]; }
    void dropBefore(int64_t i) {
        const int64_t dead = std::clamp<int64_t>(i - start, 0, static_cast<int64_t>(data.size()));
        if (dead < 16384 || dead * 2 < static_cast<int64_t>(data.size())) return;
        data.erase(data.begin(), data.begin() + dead);
        start += dead;
    }
};

// [stretch] one frame at a time: the same frames and sums, keeping only the overlap-add region still open.
class StretchStream {
public:
    StretchStream(int64_t inputLength, double s, int frameSize)
        : n(inputLength), N(frameSize), vocoder(frameSize, s),
          outLen(static_cast<int64_t>(std::llround(static_cast<double>(inputLength) * s))),
          frames(frameCount(outLen, frameSize, vocoder.hop())) {}
    int64_t length() const noexcept { return outLen; }
    bool finished() const noexcept { return n == 0 || outLen == 0 || emitted >= outLen; }
    // Input range [inputFrom(), inputTo()) the next frame reads; everything before inputFrom() is no longer needed.
    int64_t inputFrom() const noexcept { return k < frames ? std::max<int64_t>(0, vocoder.centerOf(k) - N / 2) : n; }
    int64_t inputTo() const noexcept { return k < frames ? std::clamp<int64_t>(vocoder.centerOf(k) + N / 2, 0, n) : n; }

    // Runs the next frame and appends to `out` every output sample no later frame can change.
    template <class Sample> void step(Sample&& sample, Window& out) {
        if (finished()) return;
        if (k < frames) {
            vocoder.step(k, [&](int64_t i) { return (i >= 0 && i < n) ? sample(i) : 0.0; });
            const int64_t base = k * vocoder.hop(), limit = outLen + 2 * N;  // the whole-buffer version's acc size
            reserve(std::min(base + N, limit));
            for (int j = 0; j < N; ++j) {
                const int64_t at = base + j;
                if (at >= limit) continue;
                const double w = vocoder.window(j);
                acc[static_cast<size_t>(at - accStart)] += vocoder.output(j);
                norm[static_cast<size_t>(at - accStart)] += w * w;
            }
            ++k;
        }
        // Frames from k on start at acc index k * hop, so output t (acc t + N/2) below that is final.
        const int64_t ready = k < frames ? std::min(outLen, k * vocoder.hop() - N / 2) : outLen;
        if (ready > emitted) reserve(ready + N / 2);
        for (; emitted < ready; ++emitted) {
            const auto at = static_cast<size_t>(emitted + N / 2 - accStart);
            out.data.push_back(norm[at] > 1e-3 ? static_cast<float>(acc[at] / norm[at]) : 0.f);
        }
        const int64_t dead = emitted + N / 2 - accStart;
        if (dead >= 16384 && dead * 2 >= static_cast<int64_t>(acc.size())) {
            acc.erase(acc.begin(), acc.begin() + dead); norm.erase(norm.begin(), norm.begin() + dead); accStart += dead;
        }
    }

private:
    void reserve(int64_t end) {
        if (end - accStart > static_cast<int64_t>(acc.size())) { acc.resize(static_cast<size_t>(end - accStart)); norm.resize(acc.size()); }
    }
    int64_t n; int N; Vocoder vocoder; int64_t outLen, frames, k = 0, emitted = 0, accStart = 0;
    std::vector<double> acc, norm;
};
}  // namespace detail

// Reads frames [first, first + count) of every channel into channels[c][0..count). Calls are sequential and never overlap.
using ReadBlock = std::function<bool(int64_t first, int count, float* const* channels)>;
// Receives the next `count` output frames of every channel.
using WriteBlock = std::function<bool(const float* const* channels, int count)>;

// [process] for a file-sized input without holding it: all channels advance together, input is read on demand and the output is
// handed over in blocks. The samples are bit-identical to [process]. Memory is a few frames per channel, independent of the length.
// Returns false on invalid options, a failed read/write or cancellation.
inline bool processStream(int64_t frames, int channels, double sampleRate, const Options& options, const ReadBlock& read,
                          const WriteBlock& write, const std::atomic<bool>* cancel = nullptr, int blockSize = 16384) {
    using detail::Window;
    if (!valid(options) || !std::isfinite(sampleRate) || sampleRate < 8000 || sampleRate > 384000) return false;
    if (channels < 1 || frames < 0 || blockSize < 1) return false;
    const auto cancelled = [cancel] { return cancel && cancel->load(std::memory_order_relaxed); };
    const bool identity = isIdentity(options);
    const int64_t finalLength = identity ? frames : static_cast<int64_t>(std::llround(static_cast<double>(frames) * options.timeFactor));
    const double stretchFactor = options.timeFactor * options.pitchFactor;
    const bool needStretch = !identity && std::fabs(stretchFactor - 1.0) > 1e-12;
    const bool needResample = !identity && options.pitchFactor != 1.0;
    const int frameSize = detail::frameSizeFor(sampleRate, options.complex);

    std::vector<Window> input(static_cast<size_t>(channels)), mid(static_cast<size_t>(channels));
    std::vector<std::unique_ptr<detail::StretchStream>> stretchers;
    for (int c = 0; c < channels && needStretch; ++c) stretchers.push_back(std::make_unique<detail::StretchStream>(frames, stretchFactor, frameSize));
    std::unique_ptr<detail::SincKernel> kernel;
    if (needResample) kernel = std::make_unique<detail::SincKernel>(options.pitchFactor);
    const int64_t sourceLength = needStretch ? stretchers.front()->length() : frames;

    int64_t readTo = 0;
    std::vector<float*> pointers(static_cast<size_t>(channels));
    const auto ensureInput = [&](int64_t to) {
        to = std::min(to, frames);
        while (readTo < to) {
            const int count = static_cast<int>(std::min<int64_t>(std::max(blockSize, 16384), frames - readTo));
            for (int c = 0; c < channels; ++c) {
                auto& w = input[static_cast<size_t>(c)];
                w.data.resize(w.data.size() + static_cast<size_t>(count));
                pointers[static_cast<size_t>(c)] = w.data.data() + (readTo - w.start);
            }
            if (!read(readTo, count, pointers.data())) return false;
            readTo += count;
        }
        return true;
    };
    // Makes source samples [.., to) of channel c available (the stretched signal, or the input itself).
    const auto ensureSource = [&](int c, int64_t to) {
        if (!needStretch) return ensureInput(to);
        auto& stretcher = *stretchers[static_cast<size_t>(c)];
        auto& in = input[static_cast<size_t>(c)];
        auto& out = mid[static_cast<size_t>(c)];
        to = std::min(to, sourceLength);
        while (out.end() < to && !stretcher.finished()) {
            if (cancelled() || !ensureInput(stretcher.inputTo())) return false;
            stretcher.step([&](int64_t i) { return static_cast<double>(in[i]); }, out);
        }
        return true;
    };
    const auto source = [&](int c) -> const Window& { return needStretch ? mid[static_cast<size_t>(c)] : input[static_cast<size_t>(c)]; };

    std::vector<std::vector<float>> block(static_cast<size_t>(channels), std::vector<float>(static_cast<size_t>(blockSize)));
    std::vector<const float*> outPointers(static_cast<size_t>(channels));
    for (int64_t produced = 0; produced < finalLength;) {
        if (cancelled()) return false;
        const int count = static_cast<int>(std::min<int64_t>(blockSize, finalLength - produced));
        int64_t inputNeeded = frames;
        for (int c = 0; c < channels; ++c) {
            auto& dst = block[static_cast<size_t>(c)];
            for (int i = 0; i < count; ++i) {
                const int64_t t = produced + i;
                if (needResample) {
                    const double position = static_cast<double>(t) * options.pitchFactor;
                    if (!ensureSource(c, kernel->span(position, sourceLength).second + 1)) return false;
                    const auto& src = source(c);
                    dst[static_cast<size_t>(i)] = static_cast<float>(kernel->read(position, sourceLength, [&](int64_t index) { return static_cast<double>(src[index]); }));
                } else if (t < sourceLength) {
                    if (!ensureSource(c, t + 1)) return false;
                    dst[static_cast<size_t>(i)] = source(c)[t];
                } else {
                    dst[static_cast<size_t>(i)] = 0.f;  // [processChannel] pads to the final length
                }
            }
            // Oldest source sample the next output still reads.
            const int64_t next = produced + count;
            const int64_t keep = needResample ? kernel->span(static_cast<double>(next) * options.pitchFactor, sourceLength).first : next;
            if (needStretch) {
                mid[static_cast<size_t>(c)].dropBefore(keep);
                inputNeeded = std::min(inputNeeded, stretchers[static_cast<size_t>(c)]->inputFrom());
            } else {
                inputNeeded = std::min(inputNeeded, keep);
            }
            outPointers[static_cast<size_t>(c)] = dst.data();
        }
        for (auto& w : input) w.dropBefore(inputNeeded);
        if (!write(outPointers.data(), count)) return false;
        produced += count;
    }
    return !cancelled();
}
}  // namespace timepitch
}  // namespace wtracks
