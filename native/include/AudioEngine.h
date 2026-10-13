#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_core/juce_core.h>
#include <atomic>
#include "ClickTimeline.h"
#include "GuideTimeline.h"
#include "MixerStage.h"
#include <memory>
#include <mutex>
#include <vector>

namespace wtracks
{

enum class EngineErrorCode { None = 0, FileUnreadable, FormatMismatch, DeviceInitFailed, Unknown };

struct Channel
{
    juce::String name;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    std::unique_ptr<juce::BufferingAudioSource> bufferedSource;
    int readAheadCapacity = 0;
    juce::File file;
    // Converte do sample rate do arquivo pro do device (AudioFormatReaderSource
    // sozinho nao faz resampling).
    std::unique_ptr<juce::ResamplingAudioSource> resampler;
    double fileSampleRate = 44100.0;
    float volume = 1.0f;
    bool muted = false;
    GainRamp ramp;
    ChannelRoute route;
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
    uint64_t getUnderrunCount() const;
    bool setLoop(double startSeconds, double endSeconds, bool enabled);
    bool enqueueLoop(double startSeconds, double endSeconds);
    void clearQueuedLoop();
    bool getLoopEnabled() const;
    void getLoopState(double* out6) const;
    bool getQueuedLoopEnabled() const;
    double getLoopStart() const;
    double getLoopEnd() const;
    double getQueuedLoopStart() const;
    double getQueuedLoopEnd() const;
    // Only control/offline threads may wait. The audio callback always uses timeout zero.
    bool waitForReadAhead(int outputSamples, uint32_t timeoutMs);

    void setChannelVolume(int channelIndex, float volume);
    void setChannelMuted(int channelIndex, bool muted);
    bool setChannelRoute(int channelIndex, int outputBase, bool mono);
    void setMasterVolume(float volume);
    int getChannelCount() const;
    // The loaded files are a time-stretched rendering of the song: processed length = song length * scale.
    // Every seconds-based API (position, length, seek, loops, click, guides) keeps using song time.
    // Clears loops; call right after loadTrack (loadTrack resets the scale to 1).
    bool setTimeScale(double scale);
    double getTimeScale() const;

    void setClickEnabled(bool enabled);
    void setClickBpm(double bpm);
    void setClickTimeSignature(int numerator, int denominator);
    void setClickOffsetSeconds(double offsetSeconds);

    bool configureClick(double bpm, int numerator, int denominator, int bpmUnit, double offset, double accent, double quarter, double eighth, double sixteenth);
    bool loadClickSound(int voice, const juce::String& path);
    bool loadClickBank(const std::array<juce::String,4>& paths);
    void setClickGain(float gain);
    bool configureGuides(const double* times, const char** paths, const float* gains, int count);
    void setGuidesEnabled(bool enabled);

    // Tratamento de Erros Blindado
    juce::String getLastError() const;
    EngineErrorCode getLastErrorCode() const;
    void setLastError(EngineErrorCode code, const juce::String& errorMessage);

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

private:
    juce::AudioDeviceManager deviceManager;
    juce::AudioFormatManager formatManager;
    juce::MixerAudioSource mixerSource;
    juce::AudioSourcePlayer audioSourcePlayer;
    juce::TimeSliceThread readAheadThread { "WTracks read ahead" };
    mutable std::recursive_mutex controlMutex;
    std::atomic<uint64_t> underrunCount { 0 };

    struct LoopCache {
        double start=0, end=0;
        std::vector<juce::AudioBuffer<float>> stems;
        std::vector<int64_t> firstFrames;
    };
    std::shared_ptr<LoopCache> activeLoop, queuedLoop;
    bool loopEnabled=false, queuedLoopEnabled=false;
    void normalizeLoopPosition();
    std::shared_ptr<LoopCache> prepareLoop(double startSeconds, double endSeconds);
    std::vector<Channel> channels;
    mutable juce::SpinLock channelsLock;

    std::atomic<bool> playing { false };
    std::atomic<int64_t> currentSamplePosition { 0 };

    juce::AudioBuffer<float> scratchBuffer;

    bool isPrepared = false;
    int preparedBlockSize = 0;
    double preparedSampleRate = 44100.0;

    double timeScale = 1.0;
    double userClickBpm = 120.0, userClickOffset = 0.0;
    void applyClickScale();
    void loopToFileTime(double& start, double& end);
    float masterVolume = 1.0f;
    GainRamp masterRamp;
    GuideTimeline guideTimeline;
    juce::AudioBuffer<float> guideScratch;
    std::atomic<bool> guidesEnabled { false };
    ClickTimeline clickTimeline;
    std::atomic<bool> clickEnabled { false };
    double currentSampleRate = 44100.0;

    // Guarda o ultimo erro para a interface Dart consultar com segurança
    juce::String lastError { "" };
    EngineErrorCode lastErrorCode = EngineErrorCode::None;
    mutable juce::SpinLock errorLock;

    bool channelsReady(int outputSamples, uint32_t timeoutMs);
    bool prefillChannels();
    bool decodeClickSound(const juce::String& path, juce::AudioBuffer<float>& decoded, double& rate);
    void generateClickBuffers(double sampleRate);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioEngine)
};

} // namespace wtracks