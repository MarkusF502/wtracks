#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_core/juce_core.h>
#include <array>
#include <atomic>
#include "ClickTimeline.h"
#include "GuideTimeline.h"
#include "Preroll.h"
#include "MixerStage.h"
#include "MixerAutomation.h"
#include "MidiClock.h"
#include "CueTimeline.h"
#include "MidiRouter.h"
#include "Timecode.h"
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
    bool soloMuted = false;  // silenced by another channel's solo; independent of the (automatable) mute
    bool excludedFromFade = false;
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
    // repeats: number of passes before playback continues past the loop end (0 = loop until disabled).
    bool setLoop(double startSeconds, double endSeconds, bool enabled, int repeats = 0);
    bool enqueueLoop(double startSeconds, double endSeconds, int repeats = 0);
    // Sections that start looping by themselves when playback reaches their start (Playback's "preset infinite loop").
    // Prepared like any loop cache (<= 16 sections, 128 MiB in total); replaces the previous set, kept across stop/seek,
    // dropped with the song. Disabling the loop mid-section does not re-trigger it until the playhead reaches the start again.
    bool configurePresetLoops(const double* starts, const double* ends, const int* repeats, int count);
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
    void setChannelSoloMuted(int channelIndex, bool muted);
    // Fade out (see FadeOut in MixerStage.h). startFadeOut needs playback running (0.05..60 s); it ends in a pause and a
    // FadeFinished event. Seek, pause, stop, play and new songs cancel it. During a pre-roll count-in it pauses at once.
    bool startFadeOut(double seconds);
    void cancelFadeOut();
    // Fade over the last `seconds` of the song (playhead based); 0 disables.
    bool setEndFade(double seconds);
    void setChannelExcludedFromFade(int channelIndex, bool excluded);
    // Current manual fade gain (1..0) or -1 when no fade runs.
    double getFadeGain() const;
    enum TransportEvent : uint32_t { EndReached = 1, FadeFinished = 2 };
    // Events raised by the audio thread since the last poll (bitmask of TransportEvent).
    uint32_t pollTransportEvents();
    // Peak meters since the previous call (and reset): post-fader per channel (<= 64) and per output after the master
    // (<= 8; timecode excluded). Fills `capacity` / `outputCapacity` entries (0 past the song's channels or the
    // device's outputs). Returns the song's channel count. Lock-free on the audio side.
    int takeMeters(float* channelPeaks, int capacity, float* outputPeaks, int outputCapacity);
    // Mixer automation (own design, see MixerAutomation.h). Params: channel volume c, channel mute 64+c, master 128.
    // Replaces the previous points; invalid input changes nothing. Points for channels the song lacks are ignored.
    bool configureMixerAutomation(const double* starts, const double* ends, const int* params, const float* values, int count);
    void setAutomationEnabled(bool enabled);
    bool getAutomationEnabled() const;
    // Effective mixer state at the playhead (automation when enabled, else the manual values). Returns the channel count;
    // fills up to `capacity` channels. `master` may be null.
    int getMixState(float* volumes, uint8_t* mutes, int capacity, float* master) const;
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
    // Tempo/meter changes after the base segment (song time). Replaces the previous list; invalid lists change nothing.
    bool setClickTempoChanges(const double* starts, const double* bpms, const int* numerators, const int* denominators, int count);
    void setClickGain(float gain);
    // MIDI output. The sink receives realtime clock (0xF8 at 24 ppqn on the click grid), start/continue/stop and cue messages.
    static juce::StringArray listMidiOutputs();  // "identifier\tname" per device
    bool openMidiOutput(const juce::String& deviceIdentifier);
    void attachMidiSink(std::unique_ptr<MidiSink> sink);
    void closeMidiOutput();
    bool isMidiOutputOpen() const;
    void setMidiClockEnabled(bool enabled);
    bool sendMidiMessage(const uint8_t* bytes, int size);
    // Automation / MIDI cues in song time. Message bytes: midiSizes[i] (0 = none, else 2 or 3) bytes at midiBytes[3*i].
    bool configureCues(const double* times, const uint8_t* midiBytes, const uint8_t* midiSizes, int count);
    int pollCues(uint32_t* out, int maxCount);
    uint64_t getMidiDroppedCount() const;
    // Linear timecode on one output channel (0 = first). Runs in real time on the processed timeline at the nominal rate;
    // `onsetSeconds` is song time. Independent of mute, solo and master volume. See Timecode.h.
    bool configureTimecode(int rateIndex, int64_t startFrame, double onsetSeconds, int outputChannel, float gain);
    void setTimecodeEnabled(bool enabled);
    bool configureGuides(const double* times, const char** paths, const float* gains, int count);
    // Dynamic guides: per cue an optional normal path (nullptr/"" = silent unless replaced), an optional replacement path
    // and the start (song time, -1 = none) of the section it announces. See GuideTimeline.h for the replacement rule.
    bool configureGuides(const double* times, const char** paths, const char** replacementPaths, const double* targets,
                         const float* gains, int count);
    // Song Section Pre-roll (own design, see Preroll.h): when enabled, play() from a stopped/paused playhead lying on one
    // of `starts` (song time, within 1 ms) first plays one bar of click + spoken count while the stems wait. countPaths[k]
    // speaks "k+1" (<= 16, empty entries are silent). Kept across seeks; dropped with the song.
    bool configurePreroll(bool enabled, const double* starts, int startCount, const char** countPaths, int countCount);
    bool isPrerolling() const;
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
        int repeats=0;
        std::vector<juce::AudioBuffer<float>> stems;
        std::vector<int64_t> firstFrames;
    };
    std::shared_ptr<LoopCache> activeLoop, queuedLoop;
    bool loopEnabled=false, queuedLoopEnabled=false;
    void normalizeLoopPosition();
    std::shared_ptr<LoopCache> prepareLoop(double startSeconds, double endSeconds);
    int loopPasses=0;
    std::vector<std::shared_ptr<LoopCache>> presetLoops;
    void parkStreamsAt(double seconds);
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
    std::vector<TempoChange> userTempoChanges;
    void applyClickScale();
    void loopToFileTime(double& start, double& end);
    float masterVolume = 1.0f;
    MixerAutomation mixerAutomation;
    FadeOut fadeOut;
    double endFadeSeconds = 0;
    std::atomic<uint32_t> transportEvents { 0 };
    std::vector<float> fadeGains;
    std::array<PeakMeter, 64> channelMeters;
    std::array<PeakMeter, 8> outputMeters;
    void meterOutputs(const juce::AudioBuffer<float>& buffer, int start, int count) noexcept;
    std::atomic<bool> automationEnabled { true };
    void resetAutomationBases();
    GainRamp masterRamp;
    TimecodeGenerator timecode;
    juce::AudioBuffer<float> timecodeScratch;
    std::atomic<bool> timecodeEnabled { false };
    int timecodeOutput = 1;
    double userTimecodeOnset = 0.0;
    MidiClockTimeline midiClock;
    CueTimeline cueTimeline;
    MidiRouter midiRouter;
    std::atomic<bool> midiClockEnabled { false }, midiClockRunning { false };
    std::array<std::atomic<uint32_t>, 1024> cueQueue {};
    std::atomic<uint64_t> cueHead { 0 }, cueTail { 0 }, cueDropped { 0 };
    std::mutex cuePollMutex;
    void stopMidiClock();
    void clearCueQueue();
    GuideTimeline guideTimeline;
    Preroll preroll;
    bool prerollEnabled = false;
    std::vector<double> prerollStarts;
    bool beginPreroll();
    int64_t guideWrapSample() const;
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