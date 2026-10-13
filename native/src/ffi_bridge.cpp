#include "../include/ffi_bridge.h"
#include "../include/AudioEngine.h"
#include "../include/WaveformExtractor.h"
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

int wtracks_get_channel_count()
{
    return engine ? engine->getChannelCount() : 0;
}

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