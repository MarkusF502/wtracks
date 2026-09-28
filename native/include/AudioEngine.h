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

struct Channel
{
    juce::String name;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    // Converte do sample rate do arquivo pro do device (AudioFormatReaderSource
    // sozinho nao faz resampling).
    std::unique_ptr<juce::ResamplingAudioSource> resampler;
    double fileSampleRate = 44100.0;
    float volume = 1.0f;
    bool muted = false;
    int outputBus = 0;
};

class AudioEngine : public juce::AudioSource
{
public:
    AudioEngine();
    ~AudioEngine() override;

    bool initialise(int sampleRate, int bufferSize);
    void shutdown();

    bool loadTrack(const juce::String& songId, const std::vector<juce::File>& channelFiles);
    void unloadCurrentTrack();

    void play();
    void pause();
    void stop();
    void seekToSeconds(double seconds);
    double getCurrentPositionSeconds() const;
    double getTotalLengthSeconds() const;
    bool isPlaying() const;

    void setChannelVolume(int channelIndex, float volume);
    void setChannelMuted(int channelIndex, bool muted);
    int getChannelCount() const;

    void setClickEnabled(bool enabled);
    void setClickBpm(double bpm);
    void setClickTimeSignature(int numerator, int denominator);
    void setClickOffsetSeconds(double offsetSeconds);

    // Tratamento de Erros Blindado
    juce::String getLastError() const;
    void setLastError(const juce::String& errorMessage);

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

private:
    juce::AudioDeviceManager deviceManager;
    juce::AudioFormatManager formatManager;
    juce::MixerAudioSource mixerSource;
    juce::AudioSourcePlayer audioSourcePlayer;

    std::vector<Channel> channels;
    mutable juce::SpinLock channelsLock;

    std::atomic<bool> playing { false };
    std::atomic<int64_t> currentSamplePosition { 0 };
    std::atomic<int64_t> samplesPerBeat { 0 };

    juce::AudioBuffer<float> scratchBuffer;

    bool isPrepared = false;
    int preparedBlockSize = 0;
    double preparedSampleRate = 44100.0;

    std::atomic<bool> clickEnabled { false };
    double clickBpm = 120.0;
    double currentSampleRate = 44100.0;

    juce::AudioBuffer<float> clickBufferAccent; 
    juce::AudioBuffer<float> clickBufferNormal; 

    std::atomic<int> timeSignatureNumerator { 4 };
    std::atomic<int> currentBeatIndex { 0 };
    std::atomic<int64_t> clickReadPosition { -1 };

    std::atomic<int64_t> clickOffsetSamples { 0 };
    double clickOffsetSecondsValue = 0.0; // guardado só pra recalcular clickOffsetSamples se o sample rate mudar

    // Guarda o ultimo erro para a interface Dart consultar com segurança
    juce::String lastError { "" };
    mutable juce::SpinLock errorLock;

    void generateClickBuffers(double sampleRate);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioEngine)
};

} // namespace wtracks