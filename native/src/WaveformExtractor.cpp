#include "../include/WaveformExtractor.h"

#include <algorithm>
#include <cmath>

namespace wtracks
{

namespace
{
    constexpr int kSubBlockSamples = 4096;
}

bool extractWaveformPeaks(const std::vector<juce::File>& channelFiles,
                           int numBuckets,
                           float* outPeaks)
{
    if (numBuckets <= 0 || outPeaks == nullptr)
        return false;

    // AudioFormatManager local -- não compartilha estado com o AudioEngine
    // singleton, então pode rodar enquanto uma música diferente já está
    // tocando no engine principal.
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    std::vector<std::unique_ptr<juce::AudioFormatReader>> readers;
    for (const auto& file : channelFiles)
    {
        auto* reader = formatManager.createReaderFor(file);
        if (reader == nullptr)
            return false;

        readers.emplace_back(reader);
    }

    for (int i = 0; i < numBuckets; ++i)
        outPeaks[i] = 0.0f;

    if (readers.empty())
        return true; // nada para mixar -- tudo zero, não é erro.

    const juce::int64 totalLength = readers[0]->lengthInSamples;

    if (totalLength <= 0)
        return true; // música vazia -- picos zero, não é erro.

    float globalPeak = 0.0f;

    for (int bucket = 0; bucket < numBuckets; ++bucket)
    {
        const juce::int64 bucketStart = (totalLength * bucket) / numBuckets;
        const juce::int64 bucketEnd = (bucket == numBuckets - 1)
                                           ? totalLength
                                           : (totalLength * (bucket + 1)) / numBuckets;
        const juce::int64 bucketLen = bucketEnd - bucketStart;

        float bucketPeak = 0.0f;

        for (juce::int64 subStart = bucketStart; subStart < bucketEnd; subStart += kSubBlockSamples)
        {
            const int subLen = static_cast<int>(
                std::min<juce::int64>(kSubBlockSamples, bucketEnd - subStart));

            if (subLen <= 0)
                continue;

            std::vector<float> mixAccum(static_cast<size_t>(subLen), 0.0f);

            for (auto& reader : readers)
            {
                const int numChannels = static_cast<int>(reader->numChannels);
                juce::AudioBuffer<float> readBuffer(std::max(1, numChannels), subLen);
                readBuffer.clear();

                reader->read(&readBuffer, 0, subLen, subStart, true, true);

                // Soma as amostras simultâneas de todos os canais deste
                // arquivo (ex: um arquivo estéreo) na mixagem geral antes
                // de tirar o valor absoluto -- mixagem real, não soma de
                // picos individuais.
                for (int ch = 0; ch < readBuffer.getNumChannels(); ++ch)
                {
                    const float* data = readBuffer.getReadPointer(ch);
                    for (int i = 0; i < subLen; ++i)
                        mixAccum[static_cast<size_t>(i)] += data[i];
                }
            }

            for (float sample : mixAccum)
                bucketPeak = std::max(bucketPeak, std::abs(sample));
        }

        outPeaks[bucket] = bucketPeak;
        globalPeak = std::max(globalPeak, bucketPeak);
    }

    if (globalPeak < 1e-6f)
    {
        // Silêncio total -- não é erro, só uma música/canal silenciosa de
        // verdade. outPeaks já está zerado.
        return true;
    }

    for (int i = 0; i < numBuckets; ++i)
        outPeaks[i] = outPeaks[i] / globalPeak;

    return true;
}

} // namespace wtracks
