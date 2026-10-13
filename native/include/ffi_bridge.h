#pragma once
#include <stdint.h>

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

// Cache misses are cumulative; the master clock holds while audio output is silent.
WTRACKS_API uint64_t wtracks_get_underrun_count();

// Prepared loop banks; invalid/oversize requests preserve the previous state.
WTRACKS_API bool wtracks_set_loop(double startSeconds, double endSeconds, bool enabled);
WTRACKS_API bool wtracks_enqueue_loop(double startSeconds, double endSeconds);
WTRACKS_API void wtracks_clear_queued_loop();
WTRACKS_API bool wtracks_get_loop_enabled();
// Atomic snapshot: enabled,start,end,queued,queuedStart,queuedEnd. Caller owns six doubles.
WTRACKS_API void wtracks_get_loop_state(double* out6);
WTRACKS_API bool wtracks_get_queued_loop_enabled();
WTRACKS_API double wtracks_get_loop_start();
WTRACKS_API double wtracks_get_loop_end();
WTRACKS_API double wtracks_get_queued_loop_start();
WTRACKS_API double wtracks_get_queued_loop_end();

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
// Output base channel and mono flag (BusChannel contract): stereo = base, base+1; mono = (L+R)/2 -> base.
WTRACKS_API bool wtracks_set_channel_route(int channelIndex, int outputBase, bool mono);
WTRACKS_API void wtracks_set_master_volume(float volume);

// Processed (time-stretched) stems: positions, loops, click and guides stay in song time.
WTRACKS_API bool wtracks_set_time_scale(double scale);
WTRACKS_API double wtracks_get_time_scale();
// Offline render of one file (see TimePitchFile.h). Independent of the engine; call from a worker isolate.
// token identifies the call for wtracks_cancel_time_pitch. Failure reasons are in wtracks_get_last_error.
WTRACKS_API bool wtracks_process_time_pitch(const char* inputPath, const char* outputPath, double timeFactor, double pitchFactor, bool complexAlgorithm, int64_t token);
WTRACKS_API void wtracks_cancel_time_pitch(int64_t token);

// MIDI output (clock 0xF8 on the click grid, 0xFA/0xFB/0xFC, cue messages). Devices are listed as "id\tname\n" lines;
// the return value is the byte size needed including the terminating NUL (buffer is filled only when large enough).
WTRACKS_API int wtracks_midi_list_outputs(char* buffer, int capacity);
WTRACKS_API bool wtracks_midi_open_output(const char* identifier);
WTRACKS_API void wtracks_midi_close_output();
WTRACKS_API bool wtracks_midi_output_open();
WTRACKS_API void wtracks_set_midi_clock_enabled(bool enabled);
WTRACKS_API bool wtracks_send_midi(const uint8_t* bytes, int size);
// Cues in song time; midiBytes holds 3 bytes per cue, midiSizes 0 (no message), 2 or 3. Cue indexes are polled.
WTRACKS_API bool wtracks_configure_cues(const double* times, const uint8_t* midiBytes, const uint8_t* midiSizes, int count);
WTRACKS_API int wtracks_poll_cues(uint32_t* out, int maxCount);
WTRACKS_API uint64_t wtracks_get_midi_dropped();

// Linear timecode (rateIndex 0..10 per the Playback rate table), written to one output channel after the master stage.
WTRACKS_API bool wtracks_configure_timecode(int rateIndex, int64_t startFrame, double onsetSeconds, int outputChannel, float gain);
WTRACKS_API void wtracks_set_timecode_enabled(bool enabled);

// Atomic guide schedule: sorted cue seconds, source paths and gains. Zero clears.
WTRACKS_API bool wtracks_configure_guides(const double* times, const char** paths, const float* gains, int count);
WTRACKS_API void wtracks_set_guides_enabled(bool enabled);

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