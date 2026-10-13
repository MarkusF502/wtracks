#include "TimePitch.h"
#include <juce_core/juce_core.h>

using namespace wtracks;

class TimePitchTests : public juce::UnitTest {
public:
    TimePitchTests() : juce::UnitTest("Offline time stretch and pitch shift", "Audio") {}

    static std::vector<float> sines(double rate, double seconds, std::initializer_list<std::pair<double,double>> partials) {
        std::vector<float> x(static_cast<size_t>(std::llround(rate * seconds)));
        for (size_t i = 0; i < x.size(); ++i) {
            double v = 0; for (auto [f, a] : partials) v += a * std::sin(2 * timepitch::detail::kPi * f * static_cast<double>(i) / rate);
            x[i] = static_cast<float>(v);
        }
        return x;
    }
    // Dominant frequency near `expected` (Hz) using a Hann FFT of the middle of the signal and parabolic interpolation.
    static double peakNear(const std::vector<float>& x, double rate, double expected) {
        const int N = 16384; if (x.size() < static_cast<size_t>(N) * 2) return -1;
        const size_t start = x.size() / 2 - N / 2;
        timepitch::detail::Fft fft(N); std::vector<std::complex<double>> s(N);
        for (int i = 0; i < N; ++i) s[static_cast<size_t>(i)] = x[start + static_cast<size_t>(i)] * (0.5 - 0.5 * std::cos(2 * timepitch::detail::kPi * i / N));
        fft.run(s, false);
        const int lo = std::max(2, static_cast<int>(expected * 0.8 * N / rate)), hi = static_cast<int>(expected * 1.2 * N / rate);
        int best = lo; for (int b = lo; b <= hi; ++b) if (std::abs(s[static_cast<size_t>(b)]) > std::abs(s[static_cast<size_t>(best)])) best = b;
        const double a = std::log(std::abs(s[static_cast<size_t>(best - 1)]) + 1e-12), b0 = std::log(std::abs(s[static_cast<size_t>(best)]) + 1e-12), c = std::log(std::abs(s[static_cast<size_t>(best + 1)]) + 1e-12);
        const double shift = 0.5 * (a - c) / (a - 2 * b0 + c);
        return (best + shift) * rate / N;
    }
    static double rms(const std::vector<float>& x) {
        const size_t from = x.size() / 4, to = x.size() * 3 / 4; double sum = 0;
        for (size_t i = from; i < to; ++i) sum += static_cast<double>(x[i]) * x[i];
        return std::sqrt(sum / static_cast<double>(to - from));
    }

    void runTest() override {
        constexpr double rate = 44100;
        using timepitch::Options;
        std::vector<std::vector<float>> out;

        beginTest("Identity copies exactly and invalid input is rejected");
        {
            const std::vector<std::vector<float>> in { sines(rate, 0.2, {{440, 0.5}}) };
            expect(timepitch::process(in, rate, Options{}, out)); expect(out == in);
            const double nan = std::numeric_limits<double>::quiet_NaN();
            for (auto o : {Options{nan, 1, true}, Options{1, nan, true}, Options{0.2, 1, true}, Options{4.1, 1, true}, Options{1, 0.4, true}, Options{1, 2.1, true}, Options{-1, 1, true}})
                { expect(!timepitch::process(in, rate, o, out)); expect(out.empty()); }
            expect(!timepitch::process({}, rate, Options{1.2, 1, true}, out));
            expect(!timepitch::process({{0.f, 0.f}, {0.f}}, rate, Options{1.2, 1, true}, out));
            expect(!timepitch::process(in, 100, Options{1.2, 1, true}, out));
            expectEquals(timepitch::semitonesToFactor(12), 2.0); expectWithinAbsoluteError(timepitch::semitonesToFactor(-12), 0.5, 1e-12);
        }

        const auto tone = sines(rate, 3.0, {{440, 0.5}});
        const double reference = rms(tone);
        struct Case { double time, semitones; bool complex; };
        beginTest("Length, pitch and level for tempo-only, pitch-only and combined changes");
        for (auto c : {Case{1.5, 0, true}, Case{0.7, 0, true}, Case{1.0, 2, true}, Case{1.0, -5, true}, Case{1.2, -5, false}, Case{0.8, 7, true}, Case{2.0, 12, false}, Case{4.0, 0, true}, Case{0.25, 0, true}}) {
            const double pitch = timepitch::semitonesToFactor(c.semitones);
            expect(timepitch::process({tone}, rate, Options{c.time, pitch, c.complex}, out));
            const auto label = juce::String("time ") + juce::String(c.time) + " semitones " + juce::String(c.semitones);
            expectEquals<int64_t>(static_cast<int64_t>(out[0].size()), std::llround(static_cast<double>(tone.size()) * c.time), label);
            const double expected = 440 * pitch;
            if (out[0].size() > 40000) {
                const double measured = peakNear(out[0], rate, expected);
                expect(std::fabs(measured / expected - 1) < 0.005, label + " measured " + juce::String(measured) + " expected " + juce::String(expected));
                expect(std::fabs(20 * std::log10(rms(out[0]) / reference)) < 1.5, label + " level");
            }
            bool finite = true; float peak = 0; for (float v : out[0]) { finite = finite && std::isfinite(v); peak = std::max(peak, std::fabs(v)); }
            expect(finite && peak < 0.5f * 1.15f, label + " finite and no large overshoot");
        }

        beginTest("Several partials and stereo channels keep their own frequencies");
        {
            const auto left = sines(rate, 3.0, {{220, 0.3}, {660, 0.3}}), right = sines(rate, 3.0, {{330, 0.5}});
            expect(timepitch::process({left, right}, rate, Options{1.25, timepitch::semitonesToFactor(3), true}, out));
            expectEquals<int>(static_cast<int>(out.size()), 2);
            const double p = timepitch::semitonesToFactor(3);
            expect(std::fabs(peakNear(out[0], rate, 220 * p) / (220 * p) - 1) < 0.005, "low partial");
            expect(std::fabs(peakNear(out[0], rate, 660 * p) / (660 * p) - 1) < 0.005, "high partial");
            expect(std::fabs(peakNear(out[1], rate, 330 * p) / (330 * p) - 1) < 0.005, "right channel");
        }

        beginTest("48 kHz material scales the analysis window and stays accurate");
        {
            const auto t48 = sines(48000, 3.0, {{1000, 0.4}});
            expect(timepitch::process({t48}, 48000, Options{1.1, timepitch::semitonesToFactor(-3), true}, out));
            const double p = timepitch::semitonesToFactor(-3);
            expect(std::fabs(peakNear(out[0], 48000, 1000 * p) / (1000 * p) - 1) < 0.005);
        }

        beginTest("A click keeps its place in the stretched timeline within one analysis window");
        {
            std::vector<float> click(static_cast<size_t>(rate * 3)); click[static_cast<size_t>(rate)] = 1.f;
            expect(timepitch::process({click}, rate, Options{1.5, 1, false}, out));
            size_t at = 0; for (size_t i = 0; i < out[0].size(); ++i) if (std::fabs(out[0][i]) > std::fabs(out[0][at])) at = i;
            expect(std::llabs(static_cast<int64_t>(at) - static_cast<int64_t>(rate * 1.5)) < 2048, "peak at " + juce::String(static_cast<int64_t>(at)));
        }

        beginTest("Cancellation stops processing and leaves no output; tiny inputs do not crash");
        {
            std::atomic<bool> cancel { true };
            expect(!timepitch::process({tone}, rate, Options{1.5, 1.1, true}, out, &cancel)); expect(out.empty());
            for (size_t n : {size_t(0), size_t(1), size_t(7), size_t(100), size_t(5000)}) {
                expect(timepitch::process({std::vector<float>(n, 0.25f)}, rate, Options{1.3, 0.9, true}, out));
                expectEquals<int64_t>(static_cast<int64_t>(out[0].size()), std::llround(static_cast<double>(n) * 1.3));
            }
        }
    }
};
static TimePitchTests timePitchTests;
