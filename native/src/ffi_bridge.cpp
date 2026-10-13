#include "../include/TimePitchFile.h"
#include "../include/ffi_bridge.h"
#include "../include/AudioEngine.h"
#include "../include/WaveformExtractor.h"
#include <cstring>
#include <memory>
#include <mutex>
#include <vector>

#if defined(__ANDROID__)
#include <jni.h>
#include <juce_core/juce_core.h>
#include <juce_core/native/juce_JNIHelpers_android.h>

extern "C" JNIEXPORT void JNICALL
Java_com_example_flutter_1app_MainActivity_initJuceContext(JNIEnv *env, jobject thiz, jobject context) {
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }
    juce::JNIClassBase::initialiseAllClasses(env, context);
    juce::Thread::initialiseJUCE(env, context);
}
#endif

static std::unique_ptr<wtracks::AudioEngine> engine;
// An isolated click decoder must finish before its owning engine is destroyed.
static std::mutex engineLifetimeMutex;
static juce::String globalLastErrorBuffer; // Variável mágica que evita falhas de ponteiro no Dart

extern "C" {

bool wtracks_initialise(int sampleRate, int bufferSize)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    engine = std::make_unique<wtracks::AudioEngine>();
    return engine->initialise(sampleRate, bufferSize);
}

void wtracks_shutdown()
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (engine)
        engine->shutdown();
    engine.reset();
}

bool wtracks_load_track(const char* songId, const char** channelPaths, int channelCount)
{
    if (!engine)
        return false;

    try {
        std::vector<juce::File> files;
        for (int i = 0; i < channelCount; ++i) {
            const char* p = channelPaths[i];
            juce::String s = p != nullptr ? juce::String(juce::CharPointer_UTF8(p)) : juce::String("<null>");
            juce::File f(s);
            files.emplace_back(std::move(f));
        }

        return engine->loadTrack(juce::String(songId), files);
    } catch (...) {
        // Se explodir qualquer limite de RAM no C++, captura aqui e não derruba o Dart.
        engine->setLastError(wtracks::EngineErrorCode::Unknown, "C++ Exception catastrófica ao carregar arquivos");
        return false;
    }
}

// Expõe a string de erro com segurança de memória
const char* wtracks_get_last_error()
{
    if (!engine) return "";
    globalLastErrorBuffer = engine->getLastError();
    return globalLastErrorBuffer.toRawUTF8();
}

int wtracks_get_last_error_code()
{
    return static_cast<int>(engine ? engine->getLastErrorCode() : wtracks::EngineErrorCode::DeviceInitFailed);
}

void wtracks_unload_track()
{
    if (engine) engine->unloadCurrentTrack();
}

void wtracks_play()  { if (engine) engine->play();  }
void wtracks_pause() { if (engine) engine->pause(); }
void wtracks_stop()  { if (engine) engine->stop();  }

void wtracks_seek(double seconds)
{
    if (engine) engine->seekToSeconds(seconds);
}

double wtracks_get_position()
{
    return engine ? engine->getCurrentPositionSeconds() : 0.0;
}

double wtracks_get_length()
{
    return engine ? engine->getTotalLengthSeconds() : 0.0;
}

bool wtracks_is_playing()
{
    return engine && engine->isPlaying();
}

void wtracks_set_channel_volume(int channelIndex, float volume)
{
    if (engine) engine->setChannelVolume(channelIndex, volume);
}

void wtracks_set_channel_muted(int channelIndex, bool muted)
{
    if (engine) engine->setChannelMuted(channelIndex, muted);
}

bool wtracks_set_channel_route(int channelIndex, int outputBase, bool mono)
{
    return engine ? engine->setChannelRoute(channelIndex, outputBase, mono) : false;
}

void wtracks_set_master_volume(float volume)
{
    if (engine) engine->setMasterVolume(volume);
}

int wtracks_get_channel_count()
{
    return engine ? engine->getChannelCount() : 0;
}

bool wtracks_set_time_scale(double scale)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    return engine ? engine->setTimeScale(scale) : false;
}

double wtracks_get_time_scale() { return engine ? engine->getTimeScale() : 1.0; }

bool wtracks_process_time_pitch(const char* inputPath, const char* outputPath, double timeFactor, double pitchFactor, bool complexAlgorithm, int64_t token)
{
    if (!inputPath || !outputPath) return false;
    wtracks::TimePitchResult result;
    try {
        result = wtracks::processTimePitchFile(juce::File(juce::String::fromUTF8(inputPath)), juce::File(juce::String::fromUTF8(outputPath)),
                                               {timeFactor, pitchFactor, complexAlgorithm}, token);
    } catch (...) { result.error = "Time/pitch processing failed"; }
    if (!result.ok) {
        const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
        if (engine) engine->setLastError(wtracks::EngineErrorCode::Unknown, result.error);
    }
    return result.ok;
}

void wtracks_cancel_time_pitch(int64_t token) { wtracks::cancelTimePitch(token); }

int wtracks_midi_list_outputs(char* buffer, int capacity)
{
    const auto text = wtracks::AudioEngine::listMidiOutputs().joinIntoString("\n") + "\n";
    const auto utf8 = text.toStdString();
    const int needed = static_cast<int>(utf8.size()) + 1;
    if (buffer && capacity >= needed) std::memcpy(buffer, utf8.c_str(), static_cast<size_t>(needed));
    return needed;
}

bool wtracks_midi_open_output(const char* identifier)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    return engine && identifier ? engine->openMidiOutput(juce::String::fromUTF8(identifier)) : false;
}

void wtracks_midi_close_output()
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (engine) engine->closeMidiOutput();
}

bool wtracks_midi_output_open() { return engine && engine->isMidiOutputOpen(); }
void wtracks_set_midi_clock_enabled(bool enabled) { if (engine) engine->setMidiClockEnabled(enabled); }

bool wtracks_send_midi(const uint8_t* bytes, int size)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    return engine ? engine->sendMidiMessage(bytes, size) : false;
}

bool wtracks_configure_cues(const double* times, const uint8_t* midiBytes, const uint8_t* midiSizes, int count)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!engine) return false;
    try { return engine->configureCues(times, midiBytes, midiSizes, count); }
    catch (...) { engine->setLastError(wtracks::EngineErrorCode::Unknown, "Cue preparation failed"); return false; }
}

int wtracks_poll_cues(uint32_t* out, int maxCount) { return engine ? engine->pollCues(out, maxCount) : 0; }
uint64_t wtracks_get_midi_dropped() { return engine ? engine->getMidiDroppedCount() : 0; }

bool wtracks_configure_timecode(int rateIndex, int64_t startFrame, double onsetSeconds, int outputChannel, float gain)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    return engine ? engine->configureTimecode(rateIndex, startFrame, onsetSeconds, outputChannel, gain) : false;
}

void wtracks_set_timecode_enabled(bool enabled) { if (engine) engine->setTimecodeEnabled(enabled); }

bool wtracks_set_click_tempo_changes(const double* starts, const double* bpms, const int* numerators, const int* denominators, int count)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    return engine ? engine->setClickTempoChanges(starts, bpms, numerators, denominators, count) : false;
}

bool wtracks_configure_guides(const double* times, const char** paths, const float* gains, int count)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!engine) return false;
    try { return engine->configureGuides(times,paths,gains,count); }
    catch (...) { engine->setLastError(wtracks::EngineErrorCode::Unknown,"Guide preparation failed"); return false; }
}
void wtracks_set_guides_enabled(bool enabled) { if (engine) engine->setGuidesEnabled(enabled); }

bool wtracks_set_loop(double start, double end, bool enabled)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!engine) return false;
    try { return engine->setLoop(start,end,enabled); }
    catch (...) { engine->setLastError(wtracks::EngineErrorCode::Unknown,"Loop preparation failed"); return false; }
}
bool wtracks_enqueue_loop(double start, double end)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!engine) return false;
    try { return engine->enqueueLoop(start,end); }
    catch (...) { engine->setLastError(wtracks::EngineErrorCode::Unknown,"Queued loop preparation failed"); return false; }
}
void wtracks_clear_queued_loop() { if (engine) engine->clearQueuedLoop(); }
void wtracks_get_loop_state(double* out6) { if (!out6) return; if (engine) engine->getLoopState(out6); else for (int i=0;i<6;++i) out6[i]=0; }
bool wtracks_get_loop_enabled() { return engine && engine->getLoopEnabled(); }
bool wtracks_get_queued_loop_enabled() { return engine && engine->getQueuedLoopEnabled(); }
double wtracks_get_loop_start() { return engine ? engine->getLoopStart() : 0; }
double wtracks_get_loop_end() { return engine ? engine->getLoopEnd() : 0; }
double wtracks_get_queued_loop_start() { return engine ? engine->getQueuedLoopStart() : 0; }
double wtracks_get_queued_loop_end() { return engine ? engine->getQueuedLoopEnd() : 0; }
uint64_t wtracks_get_underrun_count() { return engine ? engine->getUnderrunCount() : 0; }

bool wtracks_configure_click(double bpm, int numerator, int denominator, int unit, double offset, double accent, double quarter, double eighth, double sixteenth)
{
    return engine && engine->configureClick(bpm,numerator,denominator,unit,offset,accent,quarter,eighth,sixteenth);
}
bool wtracks_load_click_sound(int voice, const char* path)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!engine) return false;
    try { return engine->loadClickSound(voice, path ? juce::String::fromUTF8(path) : juce::String()); }
    catch (...) { engine->setLastError(wtracks::EngineErrorCode::Unknown,"Click sound loading failed"); return false; }
}
bool wtracks_load_click_bank(const char** paths, int voiceCount)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!engine) return false;
    if (!paths || voiceCount != 4) { engine->setLastError(wtracks::EngineErrorCode::FormatMismatch,"Click bank requires four voices"); return false; }
    try {
        std::array<juce::String,4> names;
        for (int voice=0;voice<4;++voice) names[voice]=paths[voice] ? juce::String::fromUTF8(paths[voice]) : juce::String();
        return engine->loadClickBank(names);
    } catch (...) { engine->setLastError(wtracks::EngineErrorCode::Unknown,"Click bank loading failed"); return false; }
}
void wtracks_set_click_gain(float gain) { if (engine) engine->setClickGain(gain); }

void wtracks_set_click_enabled(bool enabled)
{
    if (engine) engine->setClickEnabled(enabled);
}

void wtracks_set_click_bpm(double bpm)
{
    if (engine) engine->setClickBpm(bpm);
}

void wtracks_set_click_time_signature(int numerator, int denominator)
{
    if (engine) engine->setClickTimeSignature(numerator, denominator);
}

void wtracks_set_click_offset(double offsetSeconds)
{
    if (engine) engine->setClickOffsetSeconds(offsetSeconds);
}

bool wtracks_generate_waveform_peaks(const char** channelPaths, int channelCount, int numBuckets, float* outPeaks)
{
    try {
        std::vector<juce::File> files;
        for (int i = 0; i < channelCount; ++i) {
            const char* p = channelPaths[i];
            juce::String s = p != nullptr ? juce::String(juce::CharPointer_UTF8(p)) : juce::String();
            files.emplace_back(s);
        }
        return wtracks::extractWaveformPeaks(files, numBuckets, outPeaks);
    } catch (...) {
        return false;
    }
}

} // extern "C"