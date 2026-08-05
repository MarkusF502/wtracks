#pragma once

// Esta é a API pública exposta para o Dart via FFI.
// Regra de ouro: tudo aqui é extern "C" e usa apenas tipos simples
// (int, double, char*, bool) -- nada de C++ (classes, std::string,
// templates) atravessa essa fronteira. O Dart não sabe nada sobre
// AudioEngine, só chama estas funções.

extern "C" {

#ifdef _WIN32
    #define WTRACKS_API __declspec(dllexport)
#else
    #define WTRACKS_API __attribute__((visibility("default")))
#endif

// Ciclo de vida do engine (chamado uma vez quando o app inicia)
WTRACKS_API bool wtracks_initialise(int sampleRate, int bufferSize);
WTRACKS_API void wtracks_shutdown();

// Carregamento de música: channelPaths é um array de strings C
// (caminhos de arquivo), um por canal. channelCount informa quantos.
WTRACKS_API bool wtracks_load_track(const char* songId, const char** channelPaths, int channelCount);
WTRACKS_API void wtracks_unload_track();

// Transporte
WTRACKS_API void wtracks_play();
WTRACKS_API void wtracks_pause();
WTRACKS_API void wtracks_stop();
WTRACKS_API void wtracks_seek(double seconds);
WTRACKS_API double wtracks_get_position();
WTRACKS_API double wtracks_get_length();
WTRACKS_API bool wtracks_is_playing();

// Controle por canal
WTRACKS_API void wtracks_set_channel_volume(int channelIndex, float volume);
WTRACKS_API void wtracks_set_channel_muted(int channelIndex, bool muted);
WTRACKS_API int wtracks_get_channel_count();

// Click track
WTRACKS_API void wtracks_set_click_enabled(bool enabled);
WTRACKS_API void wtracks_set_click_bpm(double bpm);
WTRACKS_API void wtracks_set_click_time_signature(int numerator, int denominator);

} // extern "C"