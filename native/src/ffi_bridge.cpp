#include "ffi_bridge.h"
#include "AudioEngine.h"
#include <memory>
#include <vector>

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
    for (int i = 0; i < channelCount; ++i)
        files.emplace_back(juce::String(channelPaths[i]));

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

} // extern "C"