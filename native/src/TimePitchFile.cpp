#include "../include/TimePitchFile.h"
#include <map>
#include <memory>
#include <mutex>
#include <set>

namespace wtracks {
namespace {
std::mutex registryMutex;
std::map<int64_t, std::shared_ptr<std::atomic<bool>>> running;
std::set<int64_t> cancelledEarly;

TimePitchResult fail(const juce::String& message) { TimePitchResult r; r.error = message; return r; }

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
    constexpr uint64_t kInputLimit = 512ULL * 1024 * 1024, kOutputLimit = 768ULL * 1024 * 1024;
    if (!std::isfinite(rate) || rate < 8000 || rate > 192000 || channels < 1 || channels > 8 || frames <= 0)
        return fail("Unsupported audio stream");
    const auto outFrames = static_cast<uint64_t>(std::llround(static_cast<double>(frames) * options.timeFactor));
    if (static_cast<uint64_t>(frames) * static_cast<uint64_t>(channels) * sizeof(float) > kInputLimit
        || outFrames * static_cast<uint64_t>(channels) * sizeof(float) > kOutputLimit || outFrames == 0)
        return fail("Audio too long for time/pitch processing");

    std::vector<std::vector<float>> planar(static_cast<size_t>(channels), std::vector<float>(static_cast<size_t>(frames)));
    {
        juce::AudioBuffer<float> block(channels, 16384);
        for (int64_t offset = 0; offset < frames; offset += 16384) {
            if (cancel->load()) { TimePitchResult r; r.cancelled = true; r.error = "Cancelled"; return r; }
            const int n = static_cast<int>(juce::jmin<int64_t>(16384, frames - offset));
            if (!reader->read(block.getArrayOfWritePointers(), channels, offset, n)) return fail("Input decoding failed");
            for (int ch = 0; ch < channels; ++ch)
                std::copy(block.getReadPointer(ch), block.getReadPointer(ch) + n, planar[static_cast<size_t>(ch)].begin() + offset);
        }
    }
    reader.reset();

    std::vector<std::vector<float>> processed;
    for (auto& channel : planar) {
        std::vector<float> result;
        if (!timepitch::processChannel(channel, rate, options, result, cancel)) {
            TimePitchResult r; r.cancelled = cancel->load(); r.error = r.cancelled ? "Cancelled" : "Processing failed"; return r;
        }
        channel = std::vector<float>();  // release input as we go
        processed.push_back(std::move(result));
    }

    const auto temporary = output.getSiblingFile(output.getFileName() + ".part");
    temporary.deleteFile();
    {
        auto stream = std::unique_ptr<juce::FileOutputStream>(temporary.createOutputStream());
        if (!stream || stream->failedToOpen()) return fail("Cannot create output file");
        juce::WavAudioFormat wav;
        std::unique_ptr<juce::AudioFormatWriter> writer(wav.createWriterFor(stream.get(), rate, static_cast<unsigned>(channels), 32, {}, 0));
        if (!writer) return fail("Cannot create WAV writer");
        stream.release();
        std::vector<const float*> pointers; for (auto& channel : processed) pointers.push_back(channel.data());
        const bool wrote = writer->writeFromFloatArrays(pointers.data(), channels, static_cast<int>(processed.front().size()));
        writer.reset();
        if (!wrote) { temporary.deleteFile(); return fail("Writing output failed"); }
    }
    if (cancel->load()) { temporary.deleteFile(); TimePitchResult r; r.cancelled = true; r.error = "Cancelled"; return r; }
    output.deleteFile();
    if (!temporary.moveFileTo(output)) { temporary.deleteFile(); return fail("Cannot publish output file"); }
    TimePitchResult ok; ok.ok = true; return ok;
}
}
