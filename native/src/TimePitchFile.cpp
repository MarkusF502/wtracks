#include "../include/TimePitchFile.h"
#include <condition_variable>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <algorithm>
#include <chrono>

namespace wtracks {
namespace {
std::mutex registryMutex;
std::map<int64_t, std::shared_ptr<std::atomic<bool>>> running;
std::set<int64_t> cancelledEarly;

TimePitchResult fail(const juce::String& message) { TimePitchResult r; r.error = message; return r; }

constexpr uint64_t kDefaultBudget = 1ULL << 30;
std::mutex budgetMutex;
std::condition_variable budgetChanged;
uint64_t budgetBytes = kDefaultBudget, reservedBytes = 0, peakReserved = 0;
int activeJobs = 0;

// Reserva `bytes` do orçamento; espera enquanto outros trabalhos ocupam memória que não deixa espaço. Devolve false se cancelado.
struct Reservation {
    Reservation(uint64_t wanted, const std::atomic<bool>* cancel) : bytes(wanted) {
        std::unique_lock<std::mutex> lock(budgetMutex);
        while (!(activeJobs == 0 || reservedBytes + bytes <= budgetBytes)) {
            if (cancel->load()) return;
            budgetChanged.wait_for(lock, std::chrono::milliseconds(50));
        }
        if (cancel->load()) return;
        ++activeJobs; reservedBytes += bytes; peakReserved = std::max(peakReserved, reservedBytes); held = true;
    }
    ~Reservation() {
        if (!held) return;
        { std::lock_guard<std::mutex> lock(budgetMutex); --activeJobs; reservedBytes -= bytes; }
        budgetChanged.notify_all();
    }
    uint64_t bytes; bool held = false;
};

struct Registration {
    explicit Registration(int64_t id) : token(id), flag(std::make_shared<std::atomic<bool>>(false)) {
        std::lock_guard<std::mutex> lock(registryMutex);
        if (cancelledEarly.erase(token)) flag->store(true);
        running[token] = flag;
    }
    ~Registration() { std::lock_guard<std::mutex> lock(registryMutex); running.erase(token); }
    int64_t token; std::shared_ptr<std::atomic<bool>> flag;
};
}

constexpr int kBlock = 16384;

uint64_t estimateTimePitchBytes(int64_t frames, int channels, const timepitch::Options& options, double sampleRate)
{
    const auto c = static_cast<uint64_t>(std::max(channels, 0));
    if (c == 0 || frames <= 0) return 0;
    const auto n = static_cast<uint64_t>(timepitch::detail::frameSizeFor(sampleRate, options.complex));
    const auto half = static_cast<uint64_t>(std::ceil(timepitch::detail::SincKernel::kZeroCrossings / std::min(1.0, 1.0 / options.pitchFactor)));
    const auto inputSpan = static_cast<uint64_t>(std::ceil(kBlock / options.timeFactor)) + n + 2 * half + 16384;
    const auto midSpan = static_cast<uint64_t>(std::ceil(kBlock * options.pitchFactor)) + n + 2 * half + 16384;
    // vocoder (FFT, janela, 6 vetores de bins) + acumuladores em double + janelas (dobram antes de compactar) + bloco de saída
    const uint64_t perChannel = 64 * n + 16 * (4 * n + 65536) + 4 * 2 * (inputSpan + midSpan) + 4 * kBlock;
    return c * perChannel + 8 * (half * timepitch::detail::SincKernel::kResolution + 2);
}

void setTimePitchMemoryBudget(uint64_t bytes)
{
    { std::lock_guard<std::mutex> lock(budgetMutex); budgetBytes = bytes == 0 ? kDefaultBudget : bytes; }
    budgetChanged.notify_all();
}

uint64_t timePitchReservedBytes() { std::lock_guard<std::mutex> lock(budgetMutex); return reservedBytes; }

uint64_t timePitchPeakReservedBytes(bool reset)
{
    std::lock_guard<std::mutex> lock(budgetMutex);
    const auto peak = peakReserved;
    if (reset) peakReserved = reservedBytes;
    return peak;
}

void cancelTimePitch(int64_t token)
{
    std::lock_guard<std::mutex> lock(registryMutex);
    auto it = running.find(token);
    if (it != running.end()) { it->second->store(true); return; }
    if (cancelledEarly.size() > 256) cancelledEarly.clear();
    cancelledEarly.insert(token);
}

TimePitchResult processTimePitchFile(const juce::File& input, const juce::File& output, const timepitch::Options& options, int64_t token)
{
    Registration registration(token);
    const std::atomic<bool>* cancel = registration.flag.get();
    if (!timepitch::valid(options)) return fail("Invalid time/pitch factors");
    if (!input.existsAsFile()) return fail("Input file not found");
    if (output.getFullPathName().isEmpty() || output == input) return fail("Invalid output file");
    juce::AudioFormatManager formats; formats.registerBasicFormats();
    std::unique_ptr<juce::AudioFormatReader> reader(formats.createReaderFor(input));
    if (!reader) return fail("Input format not supported");
    const double rate = reader->sampleRate;
    const int channels = static_cast<int>(reader->numChannels);
    const int64_t frames = reader->lengthInSamples;
    // O WAV de 32 bits precisa caber no RIFF de 32 bits (escolha própria: 2 GiB de dados, com folga); a memória não depende mais disso.
    constexpr uint64_t kOutputLimit = 2ULL * 1024 * 1024 * 1024;
    if (!std::isfinite(rate) || rate < 8000 || rate > 192000 || channels < 1 || channels > 8 || frames <= 0)
        return fail("Unsupported audio stream");
    const auto outFrames = static_cast<uint64_t>(std::llround(static_cast<double>(frames) * options.timeFactor));
    if (outFrames * static_cast<uint64_t>(channels) * sizeof(float) > kOutputLimit || outFrames == 0)
        return fail("Audio too long for time/pitch processing");

    Reservation memory(estimateTimePitchBytes(frames, channels, options, rate), cancel);
    if (!memory.held) { TimePitchResult r; r.cancelled = true; r.error = "Cancelled"; return r; }

    const auto temporary = output.getSiblingFile(output.getFileName() + ".part");
    temporary.deleteFile();
    juce::String failure;
    bool rendered = false;
    {
        auto stream = std::unique_ptr<juce::FileOutputStream>(temporary.createOutputStream());
        if (!stream || stream->failedToOpen()) return fail("Cannot create output file");
        juce::WavAudioFormat wav;
        std::unique_ptr<juce::AudioFormatWriter> writer(wav.createWriterFor(stream.get(), rate, static_cast<unsigned>(channels), 32, {}, 0));
        if (!writer) { stream.reset(); temporary.deleteFile(); return fail("Cannot create WAV writer"); }
        stream.release();
        // Entrada lida sob demanda e saída gravada por blocos: a música nunca fica inteira na memória (Fase C).
        rendered = timepitch::processStream(frames, channels, rate, options,
            [&](int64_t first, int count, float* const* dst) {
                if (reader->read(dst, channels, first, count)) return true;
                failure = "Input decoding failed"; return false;
            },
            [&](const float* const* src, int count) {
                if (writer->writeFromFloatArrays(src, channels, count)) return true;
                failure = "Writing output failed"; return false;
            },
            cancel, kBlock);
        writer.reset();
    }
    reader.reset();
    if (!rendered || cancel->load()) {
        temporary.deleteFile();
        TimePitchResult r; r.cancelled = cancel->load();
        r.error = r.cancelled ? "Cancelled" : (failure.isNotEmpty() ? failure : juce::String("Processing failed"));
        return r;
    }
    output.deleteFile();
    if (!temporary.moveFileTo(output)) { temporary.deleteFile(); return fail("Cannot publish output file"); }
    TimePitchResult ok; ok.ok = true; return ok;
}
}
