#include "AudioEngine.h"

#include <juce_audio_formats/juce_audio_formats.h>
#include <cmath>

using namespace wtracks;

// Testes de regressao do harness (ver tool/harness/run_harness.sh). Cada
// teste descreve o comportamento CORRETO esperado -- enquanto o bug
// correspondente existir, o teste falha e aparece no relatorio.

namespace
{
    constexpr int kBlock = 512;

    juce::File writeSine(const juce::File& dir, const juce::String& name, double fileRate,
                         double seconds, double freqHz)
    {
        auto file = dir.getChildFile(name);
        file.deleteFile();

        juce::WavAudioFormat wav;
        std::unique_ptr<juce::FileOutputStream> stream(file.createOutputStream());
        std::unique_ptr<juce::AudioFormatWriter> writer(
            wav.createWriterFor(stream.get(), fileRate, 1, 16, {}, 0));
        stream.release();

        const int n = static_cast<int>(seconds * fileRate);
        juce::AudioBuffer<float> buf(1, n);
        for (int i = 0; i < n; ++i)
            buf.setSample(0, i, 0.5f * static_cast<float>(std::sin(
                2.0 * juce::MathConstants<double>::pi * freqHz * i / fileRate)));

        writer->writeFromAudioSampleBuffer(buf, 0, n);
        writer.reset();
        return file;
    }

    void renderBlocks(AudioEngine& engine, int numBlocks, juce::AudioBuffer<float>* last = nullptr)
    {
        juce::AudioBuffer<float> out(2, kBlock);
        for (int b = 0; b < numBlocks; ++b)
        {
            out.clear();
            juce::AudioSourceChannelInfo info(&out, 0, kBlock);
            engine.getNextAudioBlock(info);
        }
        if (last != nullptr)
            last->makeCopyOf(out);
    }
}

class HarnessRegressionTests : public juce::UnitTest
{
public:
    HarnessRegressionTests() : juce::UnitTest("Harness - regressoes do AudioEngine", "wtracks") {}

    void runTest() override
    {
        auto dir = juce::File::getSpecialLocation(juce::File::tempDirectory)
                       .getChildFile("wtracks_harness_tests");
        dir.createDirectory();

        testLengthWhenDeviceRateDiffersFromFile(dir);
        testPlaybackSpeedWhenDeviceRateDiffersFromFile(dir);
        testPlaybackStopsAtEnd(dir);
        testSeekOnExactDownbeatPlaysAccent(dir);

        dir.deleteRecursively();
    }

private:
    // BUG-N1: AudioFormatReaderSource nao faz resampling. Com o device a 48k
    // (comum no Android) e arquivo a 44.1k, a duracao reportada e a
    // velocidade de reproducao ficam erradas.
    void testLengthWhenDeviceRateDiffersFromFile(const juce::File& dir)
    {
        beginTest("[N1] duracao correta com device 48k e arquivo 44.1k");

        auto f = writeSine(dir, "len_44k.wav", 44100.0, 2.0, 440.0);
        AudioEngine engine;
        engine.prepareToPlay(kBlock, 48000.0);
        expect(engine.loadTrack("n1", { f }));

        const double len = engine.getTotalLengthSeconds();
        logMessage("getTotalLengthSeconds() = " + juce::String(len, 4) + " (esperado 2.0)");
        expectWithinAbsoluteError(len, 2.0, 0.01,
                                  "Duracao deveria ser a do arquivo (2.0s), independente do sample rate do device");
        engine.releaseResources();
    }

    void testPlaybackSpeedWhenDeviceRateDiffersFromFile(const juce::File& dir)
    {
        beginTest("[N1] 1s de audio do device consome 1s do arquivo (sem aceleracao)");

        // Arquivo de 2s a 44.1k; depois de ~1s de blocos a 48k, a musica
        // deveria estar em ~1.0s. Sem resampling, o reader avanca 48000
        // amostras do arquivo = 1.088s, e o arquivo termina antes da hora.
        auto f = writeSine(dir, "speed_44k.wav", 44100.0, 2.0, 440.0);
        AudioEngine engine;
        engine.prepareToPlay(kBlock, 48000.0);
        expect(engine.loadTrack("n1b", { f }));
        engine.play();

        // 1.9s de device: sem resampling o arquivo (2s a 44.1k = 1.8375s a
        // 48k) ja acabou e o ultimo bloco sai em silencio.
        const int blocks = static_cast<int>(1.9 * 48000.0 / kBlock);
        juce::AudioBuffer<float> last;
        renderBlocks(engine, blocks, &last);

        const float rms = last.getRMSLevel(0, 0, kBlock);
        logMessage("RMS do bloco em t=1.9s: " + juce::String(rms, 4) + " (esperado > 0: arquivo tem 2s)");
        expect(rms > 0.01f, "Em t=1.9s ainda deveria haver audio -- o arquivo tem 2.0s");
        engine.releaseResources();
    }

    // BUG-N2: getNextAudioBlock nunca detecta o fim da musica: `playing`
    // continua true e a posicao cresce indefinidamente (UI mostra 5:12 / 4:00).
    void testPlaybackStopsAtEnd(const juce::File& dir)
    {
        beginTest("[N2] reproducao para no fim da musica");

        auto f = writeSine(dir, "short.wav", 44100.0, 0.5, 440.0);
        AudioEngine engine;
        engine.prepareToPlay(kBlock, 44100.0);
        expect(engine.loadTrack("n2", { f }));
        engine.play();

        renderBlocks(engine, static_cast<int>(1.5 * 44100.0 / kBlock)); // 1.5s > 0.5s

        const double pos = engine.getCurrentPositionSeconds();
        logMessage("posicao apos 1.5s tocando um arquivo de 0.5s = " + juce::String(pos, 3)
                   + "s, isPlaying=" + juce::String(engine.isPlaying() ? "true" : "false"));
        expect(! engine.isPlaying(), "isPlaying() deveria virar false ao chegar no fim");
        expect(pos <= engine.getTotalLengthSeconds() + 0.02,
               "Posicao nao deveria passar da duracao da musica");
        engine.releaseResources();
    }

    // BUG-N3: seek exatamente em cima de um tempo forte: seekToSeconds ja
    // coloca currentBeatIndex no tempo certo, e getNextAudioBlock incrementa
    // de novo na primeira amostra -> o acento cai no tempo errado.
    void testSeekOnExactDownbeatPlaysAccent(const juce::File& dir)
    {
        beginTest("[N3] seek exato no 5o tempo (1o do compasso 2) toca o click acentuado");

        auto silent = writeSine(dir, "silent.wav", 44100.0, 10.0, 0.0);
        AudioEngine engine;
        engine.prepareToPlay(kBlock, 44100.0);
        expect(engine.loadTrack("n3", { silent }));
        engine.setClickEnabled(true);
        engine.setClickBpm(60.0); // 1 tempo por segundo
        engine.setClickTimeSignature(4, 4);

        engine.seekToSeconds(4.0); // tempo 4 (0-based) = 1o tempo do compasso 2
        engine.play();

        juce::AudioBuffer<float> out;
        renderBlocks(engine, 1, &out);

        // Click acentuado = 1760 Hz, normal = 880 Hz, ambos com amplitude 0.5.
        const double accentS1 = 0.5 * std::sin(2.0 * juce::MathConstants<double>::pi * 1760.0 / 44100.0);
        const double normalS1 = 0.5 * std::sin(2.0 * juce::MathConstants<double>::pi * 880.0 / 44100.0);
        const double s1 = out.getSample(0, 1);
        logMessage("amostra[1]=" + juce::String(s1, 4) + " acento~" + juce::String(accentS1, 4)
                   + " normal~" + juce::String(normalS1, 4));
        expect(std::abs(s1 - accentS1) < std::abs(s1 - normalS1),
               "Depois de seek para um tempo forte, o click deveria ser o acentuado");
        engine.releaseResources();
    }
};

static HarnessRegressionTests harnessRegressionTests;
