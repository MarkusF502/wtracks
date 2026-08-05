#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_core/juce_core.h>
#include <atomic>
#include <memory>
#include <vector>

namespace wtracks
{

// Representa uma unica trilha de audio dentro de uma musica (ex: "click",
// "guia", "bateria", "voz"). Cada Channel tem seu proprio volume/mute
// independente, mas todas tocam em sincronia perfeita via o mesmo clock.
struct Channel
{
    juce::String name;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    float volume = 1.0f;
    bool muted = false;
    int outputBus = 0; // qual saida fisica recebe este canal (P.A., monitor, fone)
};

// AudioEngine e o coracao do motor: carrega uma musica com N canais,
// mantem todos sincronizados sample-accurate, e expoe controles em
// tempo real de volume/mute por canal. Pensado para ser chamado pela
// ponte FFI, entao todos os metodos publicos devem ser thread-safe
// e nao-bloqueantes (chamados a partir da UI thread do Flutter).
class AudioEngine : public juce::AudioSource
{
public:
    AudioEngine();
    ~AudioEngine() override;

    // Ciclo de vida
    bool initialise(int sampleRate, int bufferSize);
    void shutdown();

    // Carregamento de musica
    bool loadTrack(const juce::String& songId, const std::vector<juce::File>& channelFiles);
    void unloadCurrentTrack();

    // Transporte
    void play();
    void pause();
    void stop();
    void seekToSeconds(double seconds);
    double getCurrentPositionSeconds() const;
    double getTotalLengthSeconds() const;
    bool isPlaying() const;

    // Controle por canal (chamado ao vivo durante a execucao)
    void setChannelVolume(int channelIndex, float volume);
    void setChannelMuted(int channelIndex, bool muted);
    int getChannelCount() const;

    // Click track
    void setClickEnabled(bool enabled);
    void setClickBpm(double bpm);
    void setClickTimeSignature(int numerator, int denominator);

    // juce::AudioSource
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

private:
    juce::AudioDeviceManager deviceManager;
    juce::AudioFormatManager formatManager;
    juce::MixerAudioSource mixerSource;

    // Faz a ponte entre o callback de audio do dispositivo (AudioIODeviceCallback)
    // e este AudioEngine, que e um juce::AudioSource. E ela quem efetivamente
    // liga/desliga a producao de audio via setSource(this) / setSource(nullptr).
    juce::AudioSourcePlayer audioSourcePlayer;

    std::vector<Channel> channels;
    mutable juce::SpinLock channelsLock;

    // Estado de transporte e sincronizacao blindados com atomics para FFI/UI Thread vs Audio Thread
    std::atomic<bool> playing { false };
    std::atomic<int64_t> currentSamplePosition { 0 };
    std::atomic<int64_t> samplesPerBeat { 0 };

    // Buffer temporario reutilizado a cada bloco para ler um canal por vez
    // antes de somar (com volume aplicado) no buffer de saida.
    juce::AudioBuffer<float> scratchBuffer;

    bool isPrepared = false;
    int preparedBlockSize = 0;
    double preparedSampleRate = 44100.0;

    std::atomic<bool> clickEnabled { false };
    double clickBpm = 120.0;
    double currentSampleRate = 44100.0;

    juce::AudioBuffer<float> clickBufferAccent; // Bipe mais agudo (Tempo 1)
    juce::AudioBuffer<float> clickBufferNormal; // Bipe padrão (Tempos 2, 3, 4...)

    std::atomic<int> timeSignatureNumerator { 4 }; // Padrão 4/4
    std::atomic<int> currentBeatIndex { 0 };       // Rastreador de qual tempo do compasso estamos
    std::atomic<int64_t> clickReadPosition { -1 }; // -1 significa que o click está mudo agora

    // Gera as senoides sintéticas para os buffers na memória
    void generateClickBuffers(double sampleRate);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioEngine)
};

} // namespace wtracks