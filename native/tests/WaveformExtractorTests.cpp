#include "WaveformExtractor.h"

#include <juce_audio_formats/juce_audio_formats.h>
#include <cmath>

using namespace wtracks;

namespace
{
    constexpr double kTestSampleRate = 44100.0;

    // Grava um arquivo WAV sintetico (seno, ou silencio se frequencyHz == 0).
    // Duplicado de AudioEngineTests.cpp -- cada arquivo de teste roda como
    // uma unidade independente, não vale a pena criar um header de teste só
    // pra isso.
    juce::File writeSineWav(const juce::File& directory, const juce::String& fileName,
                             int numChannels, double lengthInSeconds, double frequencyHz,
                             float amplitude = 0.5f)
    {
        auto file = directory.getChildFile(fileName);
        file.deleteFile();

        juce::WavAudioFormat wavFormat;
        std::unique_ptr<juce::FileOutputStream> stream(file.createOutputStream());
        jassert(stream != nullptr);

        std::unique_ptr<juce::AudioFormatWriter> writer(
            wavFormat.createWriterFor(stream.get(), kTestSampleRate,
                                       static_cast<unsigned int>(numChannels), 16,
                                       juce::StringPairArray(), 0));
        jassert(writer != nullptr);
        stream.release();

        const int numSamples = static_cast<int>(lengthInSeconds * kTestSampleRate);
        juce::AudioBuffer<float> buffer(numChannels, numSamples);

        for (int ch = 0; ch < numChannels; ++ch)
        {
            auto* data = buffer.getWritePointer(ch);
            for (int i = 0; i < numSamples; ++i)
                data[i] = frequencyHz <= 0.0
                              ? 0.0f
                              : amplitude * std::sin(2.0 * juce::MathConstants<double>::pi * frequencyHz
                                                      * static_cast<double>(i) / kTestSampleRate);
        }

        writer->writeFromAudioSampleBuffer(buffer, 0, numSamples);
        writer.reset();

        return file;
    }
}

class WaveformExtractorTests : public juce::UnitTest
{
public:
    WaveformExtractorTests() : juce::UnitTest("WaveformExtractor - extracao de picos", "wtracks") {}

    void runTest() override
    {
        auto tempDir = juce::File::getSpecialLocation(juce::File::tempDirectory)
                           .getChildFile("wtracks_waveform_tests");
        tempDir.createDirectory();

        testSilenceProducesAllZeroPeaks(tempDir);
        testKnownToneNormalizesToOne(tempDir);
        testInvalidFileReturnsFalse(tempDir);

        tempDir.deleteRecursively();
    }

private:
    void testSilenceProducesAllZeroPeaks(const juce::File& tempDir)
    {
        beginTest("Cadeia silenciosa gera todos os buckets em zero");

        auto silentFile = writeSineWav(tempDir, "waveform_silence.wav", 1, 1.0, 0.0);

        constexpr int numBuckets = 50;
        std::vector<float> peaks(numBuckets, -1.0f);

        expect(extractWaveformPeaks({ silentFile }, numBuckets, peaks.data()),
               "extractWaveformPeaks deveria ter sucesso com um arquivo valido silencioso");

        for (float p : peaks)
            expectWithinAbsoluteError(p, 0.0f, 1.0e-6f);
    }

    void testKnownToneNormalizesToOne(const juce::File& tempDir)
    {
        beginTest("Tom conhecido normaliza o pico mais alto para 1.0");

        // Amplitude constante ao longo de toda a musica -- todos os buckets
        // deveriam ficar proximos de 1.0 apos a normalizacao pelo pico global.
        auto toneFile = writeSineWav(tempDir, "waveform_tone.wav", 1, 1.0, 440.0);

        constexpr int numBuckets = 20;
        std::vector<float> peaks(numBuckets, -1.0f);

        expect(extractWaveformPeaks({ toneFile }, numBuckets, peaks.data()),
               "extractWaveformPeaks deveria ter sucesso com um tom valido");

        float maxPeak = 0.0f;
        for (float p : peaks)
            maxPeak = std::max(maxPeak, p);

        expectWithinAbsoluteError(maxPeak, 1.0f, 1.0e-4f);

        for (float p : peaks)
            expect(p > 0.0f, "Bucket de um tom continuo nao deveria ficar em zero");
    }

    void testInvalidFileReturnsFalse(const juce::File& tempDir)
    {
        beginTest("Arquivo invalido/inexistente faz extractWaveformPeaks retornar false");

        auto missingFile = tempDir.getChildFile("nao_existe.wav");

        constexpr int numBuckets = 10;
        std::vector<float> peaks(numBuckets, -1.0f);

        expect(! extractWaveformPeaks({ missingFile }, numBuckets, peaks.data()),
               "extractWaveformPeaks deveria falhar para um arquivo que nao pode ser lido");
    }
};

static WaveformExtractorTests waveformExtractorTestsInstance;
