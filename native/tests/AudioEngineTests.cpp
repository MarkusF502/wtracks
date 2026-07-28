#include "AudioEngine.h"

#include <juce_audio_formats/juce_audio_formats.h>
#include <cmath>

using namespace wtracks;

namespace
{
    constexpr double kTestSampleRate = 44100.0;
    constexpr int kTestBlockSize = 512;

    // Grava um arquivo WAV sintetico (seno) com o numero de canais pedido.
    // Usado para nao depender de assets reais do projeto: geramos exatamente
    // o cenario que queremos testar (mono, estereo, duracoes incompativeis...).
    juce::File writeSineWav(const juce::File& directory, const juce::String& fileName,
                             int numChannels, double lengthInSeconds, double frequencyHz)
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
        stream.release(); // o writer adota o stream a partir daqui

        const int numSamples = static_cast<int>(lengthInSeconds * kTestSampleRate);
        juce::AudioBuffer<float> buffer(numChannels, numSamples);

        for (int ch = 0; ch < numChannels; ++ch)
        {
            auto* data = buffer.getWritePointer(ch);
            for (int i = 0; i < numSamples; ++i)
                data[i] = 0.5f * std::sin(2.0 * juce::MathConstants<double>::pi * frequencyHz
                                           * static_cast<double>(i) / kTestSampleRate);
        }

        writer->writeFromAudioSampleBuffer(buffer, 0, numSamples);
        writer.reset(); // fecha e da flush no arquivo

        return file;
    }
}

class AudioEngineMixingTests : public juce::UnitTest
{
public:
    AudioEngineMixingTests() : juce::UnitTest("AudioEngine - mixagem multicanal", "wtracks") {}

    void runTest() override
    {
        auto tempDir = juce::File::getSpecialLocation(juce::File::tempDirectory)
                           .getChildFile("wtracks_engine_tests");
        tempDir.createDirectory();

        testMonoAndStereoTogether(tempDir);
        testMutedChannelIsSilent(tempDir);
        testStopResetsPosition(tempDir);
        testLoadTrackRejectsMismatchedLengths(tempDir);

        tempDir.deleteRecursively();
    }

private:
    void testMonoAndStereoTogether(const juce::File& tempDir)
    {
        beginTest("Canal mono e canal estereo tocam juntos, sem canal mudo na saida");

        auto monoFile = writeSineWav(tempDir, "mono_440.wav", 1, 1.0, 440.0);
        auto stereoFile = writeSineWav(tempDir, "stereo_220.wav", 2, 1.0, 220.0);

        AudioEngine engine;
        engine.prepareToPlay(kTestBlockSize, kTestSampleRate);

        expect(engine.loadTrack("teste-mono-estereo", { monoFile, stereoFile }),
               "loadTrack deveria aceitar canais com a mesma duracao/sample rate");
        expectEquals(engine.getChannelCount(), 2, "A engine deve reportar 2 canais carregados.");

        engine.play();
        expect(engine.isPlaying(), "isPlaying() deve ser verdadeiro após play().");

        juce::AudioBuffer<float> output(2, kTestBlockSize);
        double sumSquaresLeft = 0.0;
        double sumSquaresRight = 0.0;

        const int totalBlocks = static_cast<int>(kTestSampleRate / kTestBlockSize) + 2;

        for (int block = 0; block < totalBlocks; ++block)
        {
            output.clear();
            juce::AudioSourceChannelInfo info(&output, 0, kTestBlockSize);
            engine.getNextAudioBlock(info);

            const auto rmsLeft = output.getRMSLevel(0, 0, kTestBlockSize);
            const auto rmsRight = output.getRMSLevel(1, 0, kTestBlockSize);
            sumSquaresLeft += static_cast<double>(rmsLeft) * rmsLeft;
            sumSquaresRight += static_cast<double>(rmsRight) * rmsRight;
        }

        logMessage ("Verificando se ambos os canais de saída (L/R) contêm sinal de áudio.");
        expect(sumSquaresLeft > 0.0,
               "Canal esquerdo de saida deveria ter sinal (mono duplicado + estereo)");
        expect(sumSquaresRight > 0.0,
               "Canal direito de saida deveria ter sinal (mono duplicado + estereo)");

        engine.releaseResources();
        logMessage ("Teste concluído.");
    }

    void testMutedChannelIsSilent(const juce::File& tempDir)
    {
        beginTest("Canal mutado nao contribui para a saida");

        auto fileA = writeSineWav(tempDir, "mute_a.wav", 1, 0.5, 440.0);
        auto fileB = writeSineWav(tempDir, "mute_b.wav", 1, 0.5, 880.0);

        AudioEngine engine;
        engine.prepareToPlay(kTestBlockSize, kTestSampleRate);
        expect(engine.loadTrack("teste-mute", { fileA, fileB }));

        engine.setChannelMuted(1, true); // silencia o segundo canal
        engine.play();

        juce::AudioBuffer<float> soloOutput(2, kTestBlockSize);
        juce::AudioSourceChannelInfo soloInfo(&soloOutput, 0, kTestBlockSize);
        engine.getNextAudioBlock(soloInfo);
        const float soloRms = soloOutput.getRMSLevel(0, 0, kTestBlockSize);

        engine.stop();
        engine.setChannelMuted(1, false);
        engine.play();

        juce::AudioBuffer<float> bothOutput(2, kTestBlockSize);
        juce::AudioSourceChannelInfo bothInfo(&bothOutput, 0, kTestBlockSize);
        engine.getNextAudioBlock(bothInfo);
        const float bothRms = bothOutput.getRMSLevel(0, 0, kTestBlockSize);

        expect(bothRms > soloRms,
               "RMS com os dois canais ativos deveria ser maior que so com um (canal mutado nao pode vazar)");

        engine.releaseResources();
    }

    void testStopResetsPosition(const juce::File& tempDir)
    {
        beginTest("stop() zera a posicao e o proximo play() recomeca do inicio");

        auto monoFile = writeSineWav(tempDir, "position_test.wav", 1, 1.0, 440.0);

        AudioEngine engine;
        engine.prepareToPlay(kTestBlockSize, kTestSampleRate);
        expect(engine.loadTrack("teste-posicao", { monoFile }));

        engine.play();

        juce::AudioBuffer<float> output(2, kTestBlockSize);
        for (int i = 0; i < 10; ++i)
        {
            output.clear();
            juce::AudioSourceChannelInfo info(&output, 0, kTestBlockSize);
            engine.getNextAudioBlock(info);
        }

        expect(engine.getCurrentPositionSeconds() > 0.0,
               "Posicao deveria ter avancado depois de varios blocos tocando");

        engine.stop();

        expectWithinAbsoluteError(engine.getCurrentPositionSeconds(), 0.0, 1.0e-9);
        expect(! engine.isPlaying(), "isPlaying() deveria ser false depois de stop()");

        engine.releaseResources();
    }

    void testLoadTrackRejectsMismatchedLengths(const juce::File& tempDir)
    {
        beginTest("loadTrack rejeita canais com comprimentos incompativeis");

        auto shortFile = writeSineWav(tempDir, "short.wav", 1, 0.2, 440.0);
        auto longFile = writeSineWav(tempDir, "long.wav", 1, 2.0, 440.0);

        AudioEngine engine;
        engine.prepareToPlay(kTestBlockSize, kTestSampleRate);

        expect(! engine.loadTrack("teste-invalido", { shortFile, longFile }),
               "loadTrack deveria falhar quando os canais tem duracoes muito diferentes");
        expectEquals(engine.getChannelCount(), 0);

        engine.releaseResources();
    }
};

// Instancia estatica: o construtor de juce::UnitTest ja se auto-registra
// no juce::UnitTestRunner global, entao basta isso existir para o teste
// aparecer em runner.runAllTests().
static AudioEngineMixingTests audioEngineMixingTestsInstance;