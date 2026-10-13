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
WTRACKS_API const char* wtracks_get_last_error();
WTRACKS_API int wtracks_get_last_error_code();
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
// Voice: 0 accent, 1 quarter, 2 eighth, 3 sixteenth. Empty path restores synthesis.
WTRACKS_API bool wtracks_configure_click(double bpm, int numerator, int denominator, int bpmUnit, double offset, double accent, double quarter, double eighth, double sixteenth);
WTRACKS_API bool wtracks_load_click_sound(int voice, const char* path);
// Atomic four-voice publication. Failure preserves the previous complete bank.
WTRACKS_API bool wtracks_load_click_bank(const char** paths, int voiceCount);
WTRACKS_API void wtracks_set_click_gain(float gain);
WTRACKS_API void wtracks_set_click_enabled(bool enabled);
WTRACKS_API void wtracks_set_click_bpm(double bpm);
WTRACKS_API void wtracks_set_click_time_signature(int numerator, int denominator);
WTRACKS_API void wtracks_set_click_offset(double offsetSeconds);

// Waveform: extrai numBuckets picos de amplitude (0.0..1.0) a partir da
// mixagem de todos os canais em channelPaths. outPeaks já deve estar
// alocado pelo chamador com numBuckets floats. Não depende do engine
// global -- pode rodar mesmo com uma música diferente carregada/tocando.
WTRACKS_API bool wtracks_generate_waveform_peaks(const char** channelPaths, int channelCount, int numBuckets, float* outPeaks);

} // extern "C"