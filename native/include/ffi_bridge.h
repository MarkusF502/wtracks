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
// Counted loops: `repeats` passes (1..1000) before playback continues after the loop end; 0 loops until disabled.
WTRACKS_API bool wtracks_set_loop_repeats(double startSeconds, double endSeconds, bool enabled, int repeats);
WTRACKS_API bool wtracks_enqueue_loop_repeats(double startSeconds, double endSeconds, int repeats);
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
WTRACKS_API void wtracks_set_midi_cues_muted(bool muted);   // console MUTE MIDI
WTRACKS_API bool wtracks_send_midi(const uint8_t* bytes, int size);
// Cues in song time; midiBytes holds 3 bytes per cue, midiSizes 0 (no message), 2 or 3. Cue indexes are polled.
WTRACKS_API bool wtracks_configure_cues(const double* times, const uint8_t* midiBytes, const uint8_t* midiSizes, int count);
WTRACKS_API int wtracks_poll_cues(uint32_t* out, int maxCount);
WTRACKS_API uint64_t wtracks_get_midi_dropped();

// Linear timecode (rateIndex 0..10 per the Playback rate table), written to one output channel after the master stage.
WTRACKS_API bool wtracks_configure_timecode(int rateIndex, int64_t startFrame, double onsetSeconds, int outputChannel, float gain);
WTRACKS_API void wtracks_set_timecode_enabled(bool enabled);

// Tempo/meter changes after the base click segment (song time, strictly increasing, past the click offset).
WTRACKS_API bool wtracks_set_click_tempo_changes(const double* starts, const double* bpms, const int* numerators, const int* denominators, int count);

// Sections that loop by themselves when the playhead reaches their start (ascending, non-overlapping, <= 16). 0 repeats = until released.
WTRACKS_API bool wtracks_configure_preset_loops(const double* starts, const double* ends, const int* repeats, int count);

// Atomic guide schedule: sorted cue seconds, source paths and gains. Zero clears.
WTRACKS_API bool wtracks_configure_guides(const double* times, const char** paths, const float* gains, int count);
WTRACKS_API void wtracks_set_guides_enabled(bool enabled);
// Dynamic guides: replacementPaths/targets may be null (no replacement, no target); paths[i] may be null/"" when
// replacementPaths[i] is set (silent unless the active loop wraps before targets[i]).
WTRACKS_API bool wtracks_configure_guides_ex(const double* times, const char** paths, const char** replacementPaths,
                                             const double* targets, const float* gains, int count);
// Song Section Pre-roll: one bar of click + spoken count before playing from one of `starts` (song time).
WTRACKS_API bool wtracks_configure_preroll(bool enabled, const double* starts, int startCount, const char** countPaths, int countCount);
WTRACKS_API bool wtracks_is_prerolling();
// Mixer automation: params = channel volume c (0..63), channel mute 64+c, master 128; song seconds.
WTRACKS_API bool wtracks_configure_mixer_automation(const double* starts, const double* ends, const int* params, const float* values, int count);
WTRACKS_API void wtracks_set_automation_enabled(bool enabled);
// Effective mixer state at the playhead; returns the channel count, fills up to `capacity` entries.
WTRACKS_API int wtracks_get_mix_state(float* volumes, uint8_t* mutes, int capacity, float* master);
WTRACKS_API void wtracks_set_channel_solo_muted(int channelIndex, bool muted);
// Fade out: manual (ends in a pause) and over the last seconds of the song; -1 gain = no manual fade running.
WTRACKS_API bool wtracks_start_fade_out(double seconds);
WTRACKS_API void wtracks_cancel_fade_out();
WTRACKS_API bool wtracks_set_end_fade(double seconds);
WTRACKS_API void wtracks_set_channel_excluded_from_fade(int channelIndex, bool excluded);
WTRACKS_API double wtracks_get_fade_gain();
// Bitmask since the last call: 1 = end of song reached, 2 = fade out finished.
WTRACKS_API uint32_t wtracks_poll_transport_events();
// Peaks since the previous call (then reset): post-fader per channel, per output after the master. Returns channels.
WTRACKS_API int wtracks_take_meters(float* channelPeaks, int capacity, float* outputPeaks, int outputCapacity);
// Buses (<= 16): channel -> bus -> output. bus -1 = none.
// MIDI cues with flags (bit 0 = disableLoop).
WTRACKS_API bool wtracks_configure_cues_ex(const double* times, const uint8_t* midiBytes, const uint8_t* midiSizes, const uint8_t* flags, int count);
// MIDI input for mappings: list as "identifier\tname" lines; messages packed byte0 | byte1<<8 | byte2<<16 | size<<24.
WTRACKS_API int wtracks_midi_list_inputs(char* buffer, int capacity);
WTRACKS_API bool wtracks_midi_open_input(const char* identifier);
WTRACKS_API void wtracks_midi_close_input();
WTRACKS_API bool wtracks_midi_input_open();
WTRACKS_API int wtracks_poll_midi_input(uint32_t* out, int maxCount);
WTRACKS_API bool wtracks_inject_midi_input(const uint8_t* bytes, int size);
WTRACKS_API void wtracks_get_loop_pass(int32_t* pass, int32_t* repeats);
// Trimmed areas [start, end) in song time (<= 32): playback jumps over them.
WTRACKS_API bool wtracks_configure_skips(const double* starts, const double* ends, int count);
WTRACKS_API bool wtracks_configure_buses(int count);
WTRACKS_API bool wtracks_set_bus(int index, float volume, bool muted, int outputBase, bool mono);
WTRACKS_API void wtracks_set_bus_solo_muted(int index, bool muted);
WTRACKS_API bool wtracks_set_channel_bus(int channelIndex, int bus);
WTRACKS_API void wtracks_set_stereo_split(bool enabled);
WTRACKS_API int wtracks_get_bus_state(float* volumes, uint8_t* mutes, int capacity);
WTRACKS_API int wtracks_take_bus_meters(float* peaks, int capacity);

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