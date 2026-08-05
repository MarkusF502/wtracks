#include "../include/ffi_bridge.h"
#include "../include/AudioEngine.h"
#include <memory>
#include <vector>

#if defined(__ANDROID__)
#include <jni.h>
#include <juce_core/juce_core.h>
// JNI helpers declaration (JNIClassBase) required by initialiseAllClasses
#include <juce_core/native/juce_JNIHelpers_android.h>

extern "C" JNIEXPORT void JNICALL
Java_com_example_flutter_1app_MainActivity_initJuceContext(JNIEnv *env, jobject thiz, jobject context) {
    // 1. O JUCE tenta carregar classes nativas de GUI internamente no Load da biblioteca.
    // Como estamos no Flutter, essas classes não existem, o que gera uma Exceção pendente.
    // Se não limparmos isso, a busca pela classe android.content.Context 
    // vai retornar NULL e derrubar o app com "IsInstanceOf received NULL jclass".
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }

    // 2. Agora o ambiente JNI está limpo e podemos inicializar o JUCE em segurança!
    // Inicializa as classes JNI internas do JUCE (resolves jclass/jmethodIDs)
    juce::JNIClassBase::initialiseAllClasses(env, context);
    juce::Thread::initialiseJUCE(env, context);
}
#endif

// Uma única instância global do motor. Simples e suficiente aqui --
// o app só precisa de um engine de áudio por vez.
static std::unique_ptr<wtracks::AudioEngine> engine;

extern "C" {

bool wtracks_initialise(int sampleRate, int bufferSize)
{
    engine = std::make_unique<wtracks::AudioEngine>();
    return engine->initialise(sampleRate, bufferSize);
}

void wtracks_shutdown()
{
    if (engine)
        engine->shutdown();
    engine.reset();
}

bool wtracks_load_track(const char* songId, const char** channelPaths, int channelCount)
{
    if (!engine)
        return false;

    std::vector<juce::File> files;
    DBG("wtracks_load_track: songId=" + juce::String(songId) + " count=" + juce::String(channelCount));
    for (int i = 0; i < channelCount; ++i) {
        const char* p = channelPaths[i];
        juce::String s = p != nullptr ? juce::String(juce::CharPointer_UTF8(p)) : juce::String("<null>");
        juce::File f(s);
        DBG("  channel[" + juce::String(i) + "] = " + s + " exists=" + (f.exists() ? "yes" : "no"));
        files.emplace_back(std::move(f));
    }

    return engine->loadTrack(juce::String(songId), files);
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

} // extern "C"
