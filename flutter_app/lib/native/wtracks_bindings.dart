import 'dart:ffi';
import 'dart:io';
import 'dart:isolate';
import 'package:ffi/ffi.dart';
import 'package:flutter/foundation.dart';
import '../models/engine_error.dart';
import '../models/track.dart';
import '../models/guide_cue.dart';
import '../services/dynamic_guides.dart';
import '../models/automation_cue.dart';
import '../models/mixer_automation.dart';
import '../models/timecode_settings.dart';
import '../models/tempo_change.dart';
import '../models/song_section.dart';

// ---- Assinaturas das funções nativas (espelham ffi_bridge.h) ----

typedef _InitialiseNative = Bool Function(Int32 sampleRate, Int32 bufferSize);
typedef _InitialiseDart = bool Function(int sampleRate, int bufferSize);

typedef _VoidNative = Void Function();
typedef _VoidDart = void Function();

typedef _LoadTrackNative =
    Bool Function(
      Pointer<Utf8> songId,
      Pointer<Pointer<Utf8>> channelPaths,
      Int32 channelCount,
    );
typedef _LoadTrackDart =
    bool Function(
      Pointer<Utf8> songId,
      Pointer<Pointer<Utf8>> channelPaths,
      int channelCount,
    );

typedef _GetLastErrorNative = Pointer<Utf8> Function();
typedef _GetLastErrorDart = Pointer<Utf8> Function();

typedef _SeekNative = Void Function(Double seconds);
typedef _SeekDart = void Function(double seconds);

typedef _GetPositionNative = Double Function();
typedef _GetPositionDart = double Function();

typedef _IsPlayingNative = Bool Function();
typedef _IsPlayingDart = bool Function();

typedef _SetChannelVolumeNative =
    Void Function(Int32 channelIndex, Float volume);
typedef _SetChannelVolumeDart = void Function(int channelIndex, double volume);

typedef _SetChannelMutedNative = Void Function(Int32 channelIndex, Bool muted);
typedef _SetChannelMutedDart = void Function(int channelIndex, bool muted);

typedef _GetChannelCountNative = Int32 Function();
typedef _GetChannelCountDart = int Function();

typedef _SetClickEnabledNative = Void Function(Bool enabled);
typedef _SetClickEnabledDart = void Function(bool enabled);

typedef _SetClickBpmNative = Void Function(Double bpm);
typedef _SetClickBpmDart = void Function(double bpm);

typedef _SetClickTimeSignatureNative =
    Void Function(Int32 numerator, Int32 denominator);
typedef _SetClickTimeSignatureDart =
    void Function(int numerator, int denominator);

typedef _SetClickOffsetNative = Void Function(Double offsetSeconds);
typedef _SetClickOffsetDart = void Function(double offsetSeconds);

typedef _ConfigureClickNative =
    Bool Function(
      Double,
      Int32,
      Int32,
      Int32,
      Double,
      Double,
      Double,
      Double,
      Double,
    );
typedef _ConfigureClickDart =
    bool Function(
      double,
      int,
      int,
      int,
      double,
      double,
      double,
      double,
      double,
    );
typedef _LoadClickSoundNative = Bool Function(Int32, Pointer<Utf8>);
typedef _LoadClickSoundDart = bool Function(int, Pointer<Utf8>);
typedef _LoadClickBankNative = Bool Function(Pointer<Pointer<Utf8>>, Int32);
typedef _LoadClickBankDart = bool Function(Pointer<Pointer<Utf8>>, int);
typedef _SetLoopNative = Bool Function(Double, Double, Bool);
typedef _SetLoopDart = bool Function(double, double, bool);
typedef _EnqueueLoopNative = Bool Function(Double, Double);
typedef _EnqueueLoopDart = bool Function(double, double);
typedef _LoopSnapshotNative = Void Function(Pointer<Double>);
typedef _LoopSnapshotDart = void Function(Pointer<Double>);
typedef _ConfigureGuidesNative = Bool Function(Pointer<Double>, Pointer<Pointer<Utf8>>, Pointer<Float>, Int32);
typedef _ConfigureGuidesDart = bool Function(Pointer<Double>, Pointer<Pointer<Utf8>>, Pointer<Float>, int);
typedef _ConfigureGuidesExNative = Bool Function(Pointer<Double>, Pointer<Pointer<Utf8>>, Pointer<Pointer<Utf8>>, Pointer<Double>, Pointer<Float>, Int32);
typedef _ConfigureGuidesExDart = bool Function(Pointer<Double>, Pointer<Pointer<Utf8>>, Pointer<Pointer<Utf8>>, Pointer<Double>, Pointer<Float>, int);
typedef _MixerAutomationNative = Bool Function(Pointer<Double>, Pointer<Double>, Pointer<Int32>, Pointer<Float>, Int32);
typedef _MixerAutomationDart = bool Function(Pointer<Double>, Pointer<Double>, Pointer<Int32>, Pointer<Float>, int);
typedef _MixStateNative = Int32 Function(Pointer<Float>, Pointer<Uint8>, Int32, Pointer<Float>);
typedef _MixStateDart = int Function(Pointer<Float>, Pointer<Uint8>, int, Pointer<Float>);
typedef _ChannelFlagNative = Void Function(Int32, Bool);
typedef _ChannelFlagDart = void Function(int, bool);
typedef _DoubleBoolNative = Bool Function(Double);
typedef _DoubleBoolDart = bool Function(double);
typedef _ScheduleTransitionNative = Bool Function(Int32, Double, Double);
typedef _ScheduleTransitionDart = bool Function(int, double, double);
typedef _SetFadeNative = Bool Function(Bool, Double);
typedef _SetFadeDart = bool Function(bool, double);
typedef _EventsNative = Uint32 Function();
typedef _EventsDart = int Function();
typedef _TakeMetersNative = Int32 Function(Pointer<Float>, Int32, Pointer<Float>, Int32);
typedef _TakeMetersDart = int Function(Pointer<Float>, int, Pointer<Float>, int);
typedef _IntBoolNative = Bool Function(Int32);
typedef _IntBoolDart = bool Function(int);
typedef _SetBusNative = Bool Function(Int32, Float, Bool, Int32, Bool);
typedef _SetBusDart = bool Function(int, double, bool, int, bool);
typedef _ChannelBusNative = Bool Function(Int32, Int32);
typedef _ChannelBusDart = bool Function(int, int);
typedef _BusStateNative = Int32 Function(Pointer<Float>, Pointer<Uint8>, Int32);
typedef _BusStateDart = int Function(Pointer<Float>, Pointer<Uint8>, int);
typedef _BusMetersNative = Int32 Function(Pointer<Float>, Int32);
typedef _BusMetersDart = int Function(Pointer<Float>, int);
typedef _CuesExNative = Bool Function(Pointer<Double>, Pointer<Uint8>, Pointer<Uint8>, Pointer<Uint8>, Int32);
typedef _CuesExDart = bool Function(Pointer<Double>, Pointer<Uint8>, Pointer<Uint8>, Pointer<Uint8>, int);
typedef _PollInputNative = Int32 Function(Pointer<Uint32>, Int32);
typedef _PollInputDart = int Function(Pointer<Uint32>, int);
typedef _InjectNative = Bool Function(Pointer<Uint8>, Int32);
typedef _InjectDart = bool Function(Pointer<Uint8>, int);
typedef _SkipsNative = Bool Function(Pointer<Double>, Pointer<Double>, Int32);
typedef _SkipsDart = bool Function(Pointer<Double>, Pointer<Double>, int);
typedef _LoopPassNative = Void Function(Pointer<Int32>, Pointer<Int32>);
typedef _LoopPassDart = void Function(Pointer<Int32>, Pointer<Int32>);
typedef _ConfigurePrerollNative = Bool Function(Bool, Pointer<Double>, Int32, Pointer<Pointer<Utf8>>, Int32);
typedef _ConfigurePrerollDart = bool Function(bool, Pointer<Double>, int, Pointer<Pointer<Utf8>>, int);
typedef _SetRouteNative = Bool Function(Int32, Int32, Bool);
typedef _SetRouteDart = bool Function(int, int, bool);
typedef _ProcessTimePitchNative = Bool Function(Pointer<Utf8>, Pointer<Utf8>, Double, Double, Bool, Int64);
typedef _ProcessTimePitchDart = bool Function(Pointer<Utf8>, Pointer<Utf8>, double, double, bool, int);
typedef _SetTimeScaleNative = Bool Function(Double);
typedef _SetTimeScaleDart = bool Function(double);
typedef _GetTimeScaleNative = Double Function();
typedef _GetTimeScaleDart = double Function();
typedef _CancelTimePitchNative = Void Function(Int64);
typedef _CancelTimePitchDart = void Function(int);
typedef _MidiListNative = Int32 Function(Pointer<Utf8>, Int32);
typedef _MidiListDart = int Function(Pointer<Utf8>, int);
typedef _MidiOpenNative = Bool Function(Pointer<Utf8>);
typedef _MidiOpenDart = bool Function(Pointer<Utf8>);
typedef _VoidFnNative = Void Function();
typedef _VoidFnDart = void Function();
typedef _BoolFnNative = Bool Function();
typedef _BoolFnDart = bool Function();
typedef _SendMidiNative = Bool Function(Pointer<Uint8>, Int32);
typedef _SendMidiDart = bool Function(Pointer<Uint8>, int);
typedef _ConfigureCuesNative = Bool Function(Pointer<Double>, Pointer<Uint8>, Pointer<Uint8>, Int32);
typedef _ConfigureCuesDart = bool Function(Pointer<Double>, Pointer<Uint8>, Pointer<Uint8>, int);
typedef _PollCuesNative = Int32 Function(Pointer<Uint32>, Int32);
typedef _PollCuesDart = int Function(Pointer<Uint32>, int);
typedef _ConfigureTimecodeNative = Bool Function(Int32, Int64, Double, Int32, Float);
typedef _ConfigureTimecodeDart = bool Function(int, int, double, int, double);
typedef _SetLoopRepeatsNative = Bool Function(Double, Double, Bool, Int32);
typedef _SetLoopRepeatsDart = bool Function(double, double, bool, int);
typedef _EnqueueLoopRepeatsNative = Bool Function(Double, Double, Int32);
typedef _EnqueueLoopRepeatsDart = bool Function(double, double, int);
typedef _PresetLoopsNative = Bool Function(Pointer<Double>, Pointer<Double>, Pointer<Int32>, Int32);
typedef _PresetLoopsDart = bool Function(Pointer<Double>, Pointer<Double>, Pointer<Int32>, int);
typedef _TempoChangesNative = Bool Function(Pointer<Double>, Pointer<Double>, Pointer<Int32>, Pointer<Int32>, Int32);
typedef _TempoChangesDart = bool Function(Pointer<Double>, Pointer<Double>, Pointer<Int32>, Pointer<Int32>, int);
typedef _GetCounterNative = Uint64 Function();
typedef _GetCounterDart = int Function();
typedef _ClickGainNative = Void Function(Float);
typedef _ClickGainDart = void Function(double);

typedef _GenerateWaveformNative = Bool Function(
  Pointer<Pointer<Utf8>> channelPaths,
  Int32 channelCount,
  Int32 numBuckets,
  Pointer<Float> outPeaks,
);
typedef _GenerateWaveformDart = bool Function(
  Pointer<Pointer<Utf8>> channelPaths,
  int channelCount,
  int numBuckets,
  Pointer<Float> outPeaks,
);

/// Wrapper de alto nível em torno da biblioteca nativa wtracks_engine.
/// Esta é a ÚNICA classe do app que sabe que FFI existe -- todo o
/// resto do Flutter conversa com [WTracksEngine], nunca com ponteiros
/// crus. Isso mantém o resto da UI limpo e testável.
/// Valores efetivos do mixer lidos do motor.
@immutable
class MixState {
  final List<double> volumes;
  final List<bool> mutes;
  final double master;
  final List<double> busVolumes;
  final List<bool> busMutes;
  const MixState(this.volumes, this.mutes, this.master, {this.busVolumes = const [], this.busMutes = const []});
  @override
  bool operator ==(Object other) =>
      other is MixState &&
      listEquals(other.volumes, volumes) &&
      listEquals(other.mutes, mutes) &&
      other.master == master &&
      listEquals(other.busVolumes, busVolumes) &&
      listEquals(other.busMutes, busMutes);
  @override
  int get hashCode =>
      Object.hash(Object.hashAll(volumes), Object.hashAll(mutes), master, Object.hashAll(busVolumes), Object.hashAll(busMutes));
}

class WTracksEngine {
  /// Número de buckets de amplitude gerados por [generateWaveformPeaksAsync]
  /// -- grande o suficiente para preencher telas largas em landscape sem
  /// esticar demais as barras, pequeno o suficiente pra manter o cache leve.
  static const int waveformBucketCount = 500;

  late final DynamicLibrary _lib;

  late final _InitialiseDart _initialise;
  late final _VoidDart _shutdown;
  late final _LoadTrackDart _loadTrack;
  late final _GetLastErrorDart _getLastError;
  late final _GetChannelCountDart _getLastErrorCode;
  bool ready = false;
  late final _VoidDart _unloadTrack;
  late final _VoidDart _play;
  late final _VoidDart _pause;
  late final _VoidDart _stop;
  late final _SeekDart _seek;
  late final _GetPositionDart _getPosition;
  late final _GetPositionDart _getLength;
  late final _IsPlayingDart _isPlaying;
  late final _SetChannelVolumeDart _setChannelVolume;
  late final _SetChannelMutedDart _setChannelMuted;
  late final _GetChannelCountDart _getChannelCount;
  late final _SetClickEnabledDart _setClickEnabled;
  late final _SetClickBpmDart _setClickBpm;
  late final _SetClickTimeSignatureDart _setClickTimeSignature;
  late final _SetClickOffsetDart _setClickOffset;
  late final _ConfigureClickDart _configureClick;
  late final _LoadClickSoundDart _loadClickSound;
  late final _LoadClickBankDart _loadClickBank;
  late final _ClickGainDart _setClickGain;
  late final _GenerateWaveformDart _generateWaveformPeaks;

  late final _SetLoopDart _setLoop;
  late final _EnqueueLoopDart _enqueueLoop;
  late final _VoidDart _clearQueuedLoop;
  late final _IsPlayingDart _getLoopEnabled;
  late final _IsPlayingDart _getQueuedLoopEnabled;
  late final _GetPositionDart _getLoopStart, _getLoopEnd, _getQueuedLoopStart, _getQueuedLoopEnd;
  late final _GetCounterDart _getUnderrunCount;
  late final _LoopSnapshotDart _getLoopState;

  late final _ProcessTimePitchDart _processTimePitch;
  late final _SetTimeScaleDart _setTimeScale;
  late final _GetTimeScaleDart _getTimeScale;
  late final _CancelTimePitchDart _cancelTimePitch;
  late final _SetLoopRepeatsDart _setLoopRepeats;
  late final _EnqueueLoopRepeatsDart _enqueueLoopRepeats;
  late final _TempoChangesDart _setClickTempoChanges;
  late final _PresetLoopsDart _configurePresetLoops;
  late final _ConfigureTimecodeDart _configureTimecode;
  late final _SetClickEnabledDart _setTimecodeEnabled;
  late final _MidiListDart _midiList;
  late final _MidiOpenDart _midiOpen;
  late final _VoidFnDart _midiClose;
  late final _BoolFnDart _midiIsOpen;
  late final _SetClickEnabledDart _setMidiClockEnabled;
  late final _SetClickEnabledDart _setMidiCuesMuted;
  late final _SendMidiDart _sendMidi;
  late final _ConfigureCuesDart _configureCues;
  late final _PollCuesDart _pollCues;
  late final _GetCounterDart _midiDropped;
  late final _SetRouteDart _setChannelRoute;
  late final _ClickGainDart _setMasterVolume;
  late final _ConfigureGuidesDart _configureGuides;
  late final _ConfigureGuidesExDart _configureGuidesEx;
  late final _ConfigurePrerollDart _configurePreroll;
  late final _IsPlayingDart _isPrerolling;
  late final _MixerAutomationDart _configureMixerAutomation;
  late final _SetClickEnabledDart _setAutomationEnabled;
  late final _MixStateDart _getMixState;
  late final _ChannelFlagDart _setChannelSoloMuted;
  late final _SetFadeDart _setFade;
  late final _IsPlayingDart _getFadeDown;
  late final _EnqueueLoopDart _setPlayRange;
  late final _LoopSnapshotDart _getPlayRange;
  late final _VoidDart _resetTransportState;
  late final _BoolFnDart _prepareNextDeck, _handoff, _transitionScheduled;
  late final _VoidFnDart _releaseNextDeck, _cancelTransition;
  late final _ScheduleTransitionDart _scheduleTransition;
  late final _GetPositionDart _transitionProgress;
  late final _DoubleBoolDart _setEndFade;
  late final _ChannelFlagDart _setChannelExcludedFromFade;
  late final _GetPositionDart _getFadeGain;
  late final _EventsDart _pollTransportEvents;
  late final _TakeMetersDart _takeMeters;
  late final _IntBoolDart _configureBuses;
  late final _SetBusDart _setBus;
  late final _ChannelFlagDart _setBusSoloMuted;
  late final _ChannelBusDart _setChannelBus;
  late final _SetClickEnabledDart _setStereoSplit;
  late final _BusStateDart _getBusState;
  late final _BusMetersDart _takeBusMeters;
  late final _CuesExDart _configureCuesEx;
  late final _SkipsDart _configureSkips;
  late final _LoopPassDart _getLoopPass;
  late final _MidiListDart _midiListInputs;
  late final _MidiOpenDart _midiOpenInput;
  late final _VoidFnDart _midiCloseInput;
  late final _BoolFnDart _midiInputOpen;
  late final _PollInputDart _pollMidiInput;
  late final _InjectDart _injectMidiInput;
  late final _SetClickEnabledDart _setGuidesEnabled;
  /// [deck] 0 é a música que toca (o dispositivo de áudio a chama); 1 é a próxima música pré-carregada durante uma transição.
  /// Depois de [handoff] os decks se trocam no nativo: o objeto do deck 0 passa a falar com a música que entrou.
  final int deck;
  final String _p;
  WTracksEngine({this.deck = 0}) : _p = deck == 0 ? 'wtracks_' : 'wtracks_n_' {
    _lib = _openLibrary();

    _initialise = _lib
        .lookup<NativeFunction<_InitialiseNative>>('wtracks_initialise')
        .asFunction();
    _shutdown = _lib
        .lookup<NativeFunction<_VoidNative>>('wtracks_shutdown')
        .asFunction();
    _loadTrack = _lib
        .lookup<NativeFunction<_LoadTrackNative>>('${_p}load_track')
        .asFunction();
    _getLastError = _lib
        .lookup<NativeFunction<_GetLastErrorNative>>('${_p}get_last_error')
        .asFunction();
    _getLastErrorCode = _lib.lookupFunction<Int32 Function(), int Function()>(
      '${_p}get_last_error_code',
    );
    _unloadTrack = _lib
        .lookup<NativeFunction<_VoidNative>>('${_p}unload_track')
        .asFunction();
    _play = _lib
        .lookup<NativeFunction<_VoidNative>>('${_p}play')
        .asFunction();
    _pause = _lib
        .lookup<NativeFunction<_VoidNative>>('${_p}pause')
        .asFunction();
    _stop = _lib
        .lookup<NativeFunction<_VoidNative>>('${_p}stop')
        .asFunction();
    _seek = _lib
        .lookup<NativeFunction<_SeekNative>>('${_p}seek')
        .asFunction();
    _getPosition = _lib
        .lookup<NativeFunction<_GetPositionNative>>('${_p}get_position')
        .asFunction();
    _getLength = _lib
        .lookup<NativeFunction<_GetPositionNative>>('${_p}get_length')
        .asFunction();
    _isPlaying = _lib
        .lookup<NativeFunction<_IsPlayingNative>>('${_p}is_playing')
        .asFunction();
    _setChannelVolume = _lib
        .lookup<NativeFunction<_SetChannelVolumeNative>>(
          '${_p}set_channel_volume',
        )
        .asFunction();
    _setChannelMuted = _lib
        .lookup<NativeFunction<_SetChannelMutedNative>>(
          '${_p}set_channel_muted',
        )
        .asFunction();
    _getChannelCount = _lib
        .lookup<NativeFunction<_GetChannelCountNative>>(
          '${_p}get_channel_count',
        )
        .asFunction();
    _setClickEnabled = _lib
        .lookup<NativeFunction<_SetClickEnabledNative>>(
          '${_p}set_click_enabled',
        )
        .asFunction();
    _setClickBpm = _lib
        .lookup<NativeFunction<_SetClickBpmNative>>('${_p}set_click_bpm')
        .asFunction();
    _setClickTimeSignature = _lib
        .lookup<NativeFunction<_SetClickTimeSignatureNative>>(
          '${_p}set_click_time_signature',
        )
        .asFunction();
    _setClickOffset = _lib
        .lookup<NativeFunction<_SetClickOffsetNative>>(
          '${_p}set_click_offset',
        )
        .asFunction();
    _configureClick = _lib
        .lookupFunction<_ConfigureClickNative, _ConfigureClickDart>(
          '${_p}configure_click',
        );
    _loadClickSound = _lib
        .lookupFunction<_LoadClickSoundNative, _LoadClickSoundDart>(
          '${_p}load_click_sound',
        );
    _loadClickBank = _lib.lookupFunction<_LoadClickBankNative, _LoadClickBankDart>('${_p}load_click_bank');
    _setLoop = _lib.lookupFunction<_SetLoopNative, _SetLoopDart>('${_p}set_loop');
    _enqueueLoop = _lib.lookupFunction<_EnqueueLoopNative, _EnqueueLoopDart>('${_p}enqueue_loop');
    _clearQueuedLoop = _lib.lookupFunction<_VoidNative, _VoidDart>('${_p}clear_queued_loop');
    _getLoopEnabled = _lib.lookupFunction<_IsPlayingNative, _IsPlayingDart>('${_p}get_loop_enabled');
    _getQueuedLoopEnabled = _lib.lookupFunction<_IsPlayingNative, _IsPlayingDart>('${_p}get_queued_loop_enabled');
    _getLoopStart = _lib.lookupFunction<_GetPositionNative, _GetPositionDart>('${_p}get_loop_start');
    _getLoopEnd = _lib.lookupFunction<_GetPositionNative, _GetPositionDart>('${_p}get_loop_end');
    _getQueuedLoopStart = _lib.lookupFunction<_GetPositionNative, _GetPositionDart>('${_p}get_queued_loop_start');
    _getQueuedLoopEnd = _lib.lookupFunction<_GetPositionNative, _GetPositionDart>('${_p}get_queued_loop_end');
    _getLoopState = _lib.lookupFunction<_LoopSnapshotNative, _LoopSnapshotDart>('${_p}get_loop_state');
    _processTimePitch = _lib.lookupFunction<_ProcessTimePitchNative, _ProcessTimePitchDart>('wtracks_process_time_pitch');
    _setTimeScale = _lib.lookupFunction<_SetTimeScaleNative, _SetTimeScaleDart>('${_p}set_time_scale');
    _getTimeScale = _lib.lookupFunction<_GetTimeScaleNative, _GetTimeScaleDart>('${_p}get_time_scale');
    _cancelTimePitch = _lib.lookupFunction<_CancelTimePitchNative, _CancelTimePitchDart>('wtracks_cancel_time_pitch');
    _setLoopRepeats = _lib.lookupFunction<_SetLoopRepeatsNative, _SetLoopRepeatsDart>('${_p}set_loop_repeats');
    _enqueueLoopRepeats = _lib.lookupFunction<_EnqueueLoopRepeatsNative, _EnqueueLoopRepeatsDart>('${_p}enqueue_loop_repeats');
    _configurePresetLoops = _lib.lookupFunction<_PresetLoopsNative, _PresetLoopsDart>('${_p}configure_preset_loops');
    _setClickTempoChanges = _lib.lookupFunction<_TempoChangesNative, _TempoChangesDart>('${_p}set_click_tempo_changes');
    _configureTimecode = _lib.lookupFunction<_ConfigureTimecodeNative, _ConfigureTimecodeDart>('${_p}configure_timecode');
    _setTimecodeEnabled = _lib.lookupFunction<_SetClickEnabledNative, _SetClickEnabledDart>('${_p}set_timecode_enabled');
    _midiList = _lib.lookupFunction<_MidiListNative, _MidiListDart>('wtracks_midi_list_outputs');
    _midiOpen = _lib.lookupFunction<_MidiOpenNative, _MidiOpenDart>('${_p}midi_open_output');
    _midiClose = _lib.lookupFunction<_VoidFnNative, _VoidFnDart>('${_p}midi_close_output');
    _midiIsOpen = _lib.lookupFunction<_BoolFnNative, _BoolFnDart>('${_p}midi_output_open');
    _setMidiClockEnabled = _lib.lookupFunction<_SetClickEnabledNative, _SetClickEnabledDart>('${_p}set_midi_clock_enabled');
    _setMidiCuesMuted = _lib.lookupFunction<_SetClickEnabledNative, _SetClickEnabledDart>('${_p}set_midi_cues_muted');
    _sendMidi = _lib.lookupFunction<_SendMidiNative, _SendMidiDart>('${_p}send_midi');
    _configureCues = _lib.lookupFunction<_ConfigureCuesNative, _ConfigureCuesDart>('${_p}configure_cues');
    _pollCues = _lib.lookupFunction<_PollCuesNative, _PollCuesDart>('${_p}poll_cues');
    _midiDropped = _lib.lookupFunction<_GetCounterNative, _GetCounterDart>('${_p}get_midi_dropped');
    _setChannelRoute = _lib.lookupFunction<_SetRouteNative, _SetRouteDart>('${_p}set_channel_route');
    _setMasterVolume = _lib.lookupFunction<_ClickGainNative, _ClickGainDart>('${_p}set_master_volume');
    _configureGuides = _lib.lookupFunction<_ConfigureGuidesNative, _ConfigureGuidesDart>('${_p}configure_guides');
    _configureGuidesEx = _lib.lookupFunction<_ConfigureGuidesExNative, _ConfigureGuidesExDart>('${_p}configure_guides_ex');
    _configurePreroll = _lib.lookupFunction<_ConfigurePrerollNative, _ConfigurePrerollDart>('${_p}configure_preroll');
    _isPrerolling = _lib.lookupFunction<_IsPlayingNative, _IsPlayingDart>('${_p}is_prerolling');
    _configureMixerAutomation = _lib.lookupFunction<_MixerAutomationNative, _MixerAutomationDart>('${_p}configure_mixer_automation');
    _setAutomationEnabled = _lib.lookupFunction<_SetClickEnabledNative, _SetClickEnabledDart>('${_p}set_automation_enabled');
    _getMixState = _lib.lookupFunction<_MixStateNative, _MixStateDart>('${_p}get_mix_state');
    _setChannelSoloMuted = _lib.lookupFunction<_ChannelFlagNative, _ChannelFlagDart>('${_p}set_channel_solo_muted');
    _setFade = _lib.lookupFunction<_SetFadeNative, _SetFadeDart>('${_p}set_fade');
    _getFadeDown = _lib.lookupFunction<_IsPlayingNative, _IsPlayingDart>('${_p}get_fade_down');
    _setPlayRange = _lib.lookupFunction<_EnqueueLoopNative, _EnqueueLoopDart>('${_p}set_play_range');
    _getPlayRange = _lib.lookupFunction<_LoopSnapshotNative, _LoopSnapshotDart>('${_p}get_play_range');
    _resetTransportState = _lib.lookupFunction<_VoidNative, _VoidDart>('${_p}reset_transport_state');
    // Transições entre músicas: sempre agem pelo deck 0 (a música que toca) sobre o deck 1.
    _prepareNextDeck = _lib.lookupFunction<_BoolFnNative, _BoolFnDart>('wtracks_prepare_next_deck');
    _releaseNextDeck = _lib.lookupFunction<_VoidFnNative, _VoidFnDart>('wtracks_release_next_deck');
    _scheduleTransition = _lib.lookupFunction<_ScheduleTransitionNative, _ScheduleTransitionDart>('wtracks_schedule_transition');
    _cancelTransition = _lib.lookupFunction<_VoidFnNative, _VoidFnDart>('wtracks_cancel_transition');
    _transitionProgress = _lib.lookupFunction<_GetPositionNative, _GetPositionDart>('wtracks_get_transition_progress');
    _transitionScheduled = _lib.lookupFunction<_BoolFnNative, _BoolFnDart>('wtracks_is_transition_scheduled');
    _handoff = _lib.lookupFunction<_BoolFnNative, _BoolFnDart>('wtracks_handoff');
    _setEndFade = _lib.lookupFunction<_DoubleBoolNative, _DoubleBoolDart>('${_p}set_end_fade');
    _setChannelExcludedFromFade = _lib.lookupFunction<_ChannelFlagNative, _ChannelFlagDart>('${_p}set_channel_excluded_from_fade');
    _getFadeGain = _lib.lookupFunction<_GetPositionNative, _GetPositionDart>('${_p}get_fade_gain');
    _pollTransportEvents = _lib.lookupFunction<_EventsNative, _EventsDart>('${_p}poll_transport_events');
    _takeMeters = _lib.lookupFunction<_TakeMetersNative, _TakeMetersDart>('${_p}take_meters');
    _configureBuses = _lib.lookupFunction<_IntBoolNative, _IntBoolDart>('${_p}configure_buses');
    _setBus = _lib.lookupFunction<_SetBusNative, _SetBusDart>('${_p}set_bus');
    _setBusSoloMuted = _lib.lookupFunction<_ChannelFlagNative, _ChannelFlagDart>('${_p}set_bus_solo_muted');
    _setChannelBus = _lib.lookupFunction<_ChannelBusNative, _ChannelBusDart>('${_p}set_channel_bus');
    _setStereoSplit = _lib.lookupFunction<_SetClickEnabledNative, _SetClickEnabledDart>('${_p}set_stereo_split');
    _getBusState = _lib.lookupFunction<_BusStateNative, _BusStateDart>('${_p}get_bus_state');
    _takeBusMeters = _lib.lookupFunction<_BusMetersNative, _BusMetersDart>('${_p}take_bus_meters');
    _configureCuesEx = _lib.lookupFunction<_CuesExNative, _CuesExDart>('${_p}configure_cues_ex');
    _configureSkips = _lib.lookupFunction<_SkipsNative, _SkipsDart>('${_p}configure_skips');
    _getLoopPass = _lib.lookupFunction<_LoopPassNative, _LoopPassDart>('${_p}get_loop_pass');
    _midiListInputs = _lib.lookupFunction<_MidiListNative, _MidiListDart>('wtracks_midi_list_inputs');
    _midiOpenInput = _lib.lookupFunction<_MidiOpenNative, _MidiOpenDart>('${_p}midi_open_input');
    _midiCloseInput = _lib.lookupFunction<_VoidFnNative, _VoidFnDart>('${_p}midi_close_input');
    _midiInputOpen = _lib.lookupFunction<_BoolFnNative, _BoolFnDart>('${_p}midi_input_open');
    _pollMidiInput = _lib.lookupFunction<_PollInputNative, _PollInputDart>('${_p}poll_midi_input');
    _injectMidiInput = _lib.lookupFunction<_InjectNative, _InjectDart>('${_p}inject_midi_input');
    _setGuidesEnabled = _lib.lookupFunction<_SetClickEnabledNative, _SetClickEnabledDart>('${_p}set_guides_enabled');
    _getUnderrunCount = _lib.lookupFunction<_GetCounterNative, _GetCounterDart>('${_p}get_underrun_count');
    _setClickGain = _lib.lookupFunction<_ClickGainNative, _ClickGainDart>(
      '${_p}set_click_gain',
    );
    _generateWaveformPeaks = _lib
        .lookup<NativeFunction<_GenerateWaveformNative>>(
          'wtracks_generate_waveform_peaks',
        )
        .asFunction();
  }

  static DynamicLibrary _openLibrary() {
    if (Platform.isAndroid) return DynamicLibrary.open('libwtracks_engine.so');
    if (Platform.isWindows) return DynamicLibrary.open('wtracks_engine.dll');
    if (Platform.isLinux) return DynamicLibrary.open('libwtracks_engine.so');
    throw UnsupportedError('Plataforma não suportada ainda');
  }

  bool initialise({int sampleRate = 44100, int bufferSize = 256}) =>
      ready = _initialise(sampleRate, bufferSize);

  void shutdown() => _shutdown();

  bool loadTrack(String songId, List<String> channelFilePaths) =>
      loadTrackSync(songId, channelFilePaths);

  /// Carrega uma música com múltiplos canais de áudio.
  /// [channelFilePaths] deve ter um caminho de arquivo LOCAL por canal
  /// (ex: ['guia.wav', 'click.wav', 'bateria.wav']) -- não URIs content://.
  /// A cópia de content:// para caminho local é responsabilidade do
  /// FileImportService, chamada antes disso.
  bool loadTrackSync(String songId, List<String> channelFilePaths) {
    final songIdPtr = songId.toNativeUtf8();
    final pathPointers = channelFilePaths.map((p) => p.toNativeUtf8()).toList();

    final pathsArray = calloc<Pointer<Utf8>>(pathPointers.length);
    for (var i = 0; i < pathPointers.length; i++) {
      pathsArray[i] = pathPointers[i];
    }

    try {
      final success = _loadTrack(songIdPtr, pathsArray, pathPointers.length);
      if (!success) {
        debugPrint('WTracksEngine.loadTrack failed: $lastError');
      }
      return success;
    } finally {
      // Sempre liberar a memória alocada manualmente, ou vaza memória nativa
      malloc.free(songIdPtr);
      for (final p in pathPointers) {
        malloc.free(p);
      }
      calloc.free(pathsArray);
    }
  }

  /// Carrega uma música de forma assíncrona em um isolate separado.
  /// Útil quando a chamada síncrona puder bloquear a UI.
  /// Roda [body] num isolate sobre o mesmo deck deste objeto (as chamadas longas não podem travar a interface).
  static Future<R> _isolateOnDeck<R>(int deck, R Function(WTracksEngine engine) body) => Isolate.run(() => body(WTracksEngine(deck: deck)));

  Future<bool> loadTrackAsync(String songId, List<String> channelFilePaths) {
    final prefix = _p; // o isolate não pode capturar `this`
    return Isolate.run(() {
      final lib = _openLibrary();
      final loadFn = lib
          .lookup<NativeFunction<_LoadTrackNative>>('${prefix}load_track')
          .asFunction<_LoadTrackDart>();
      final getErrorFn = lib
          .lookup<NativeFunction<_GetLastErrorNative>>('${prefix}get_last_error')
          .asFunction<_GetLastErrorDart>();

      final songIdPtr = songId.toNativeUtf8();
      final pathPointers = channelFilePaths
          .map((p) => p.toNativeUtf8())
          .toList();
      final pathsArray = calloc<Pointer<Utf8>>(pathPointers.length);

      for (var i = 0; i < pathPointers.length; i++) {
        pathsArray[i] = pathPointers[i];
      }

      try {
        final success = loadFn(songIdPtr, pathsArray, pathPointers.length);
        if (!success) {
            debugPrint(
            'WTracksEngine.loadTrackAsync failed: ${getErrorFn().toDartString()}',
          );
        }
        return success;
      } finally {
        malloc.free(songIdPtr);
        for (final p in pathPointers) {
          malloc.free(p);
        }
        calloc.free(pathsArray);
      }
    });
  }

  void unloadTrack() => _unloadTrack();

  void play() => _play();
  void pause() => _pause();
  void stop() => _stop();
  void seekToSeconds(double seconds) => _seek(seconds);

  double get currentPositionSeconds => _getPosition();
  double get totalLengthSeconds => _getLength();
  bool get isPlaying => _isPlaying();

  void setChannelVolume(int channelIndex, double volume) =>
      _setChannelVolume(channelIndex, volume);
  void setChannelMuted(int channelIndex, bool muted) =>
      _setChannelMuted(channelIndex, muted);
  int get channelCount => _getChannelCount();

  bool configureClick(ClickSettings settings) {
    if (!settings.isValid) return false;
    final ok = _configureClick(
      settings.bpm,
      settings.timeSignatureNumerator,
      settings.timeSignatureDenominator,
      settings.bpmUnit,
      settings.beatOffsetSeconds,
      settings.accentGain,
      settings.quarterGain,
      settings.eighthGain,
      settings.sixteenthGain,
    );
    if (ok) _setClickGain(settings.volume);
    return ok;
  }

  /// As posições, laços, click e guias continuam em tempo da música quando os
  /// arquivos carregados são uma versão processada ([timeFactor] = saída / entrada).
  bool setTimeScale(double timeFactor) => _setTimeScale(timeFactor);
  double get timeScale => _getTimeScale();

  /// Renderiza um arquivo (síncrono; use [processTimePitchAsync] fora da UI).
  bool processTimePitch(String input, String output, double timeFactor, double pitchFactor, bool complex, int token) {
    final inPtr = input.toNativeUtf8(), outPtr = output.toNativeUtf8();
    try {
      return _processTimePitch(inPtr, outPtr, timeFactor, pitchFactor, complex, token);
    } finally {
      malloc.free(inPtr);
      malloc.free(outPtr);
    }
  }

  Future<bool> processTimePitchAsync(String input, String output, double timeFactor, double pitchFactor, bool complex, int token) =>
      Isolate.run(() => WTracksEngine().processTimePitch(input, output, timeFactor, pitchFactor, complex, token));
  void cancelTimePitch(int token) => _cancelTimePitch(token);

  /// Configura e liga/desliga o timecode linear (a saída é validada no motor).
  bool configureTimecode(TimecodeSettings settings) {
    if (!settings.isValid) return false;
    final ok = _configureTimecode(settings.rateIndex, settings.startFrame, settings.onsetSeconds, settings.outputChannel, settings.gain);
    if (ok) _setTimecodeEnabled(settings.enabled);
    return ok;
  }

  /// Saídas MIDI do sistema (vazia sem hardware/ALSA).
  List<MidiDevice> listMidiOutputs() => _parseDevices(_midiList);

  static List<MidiDevice> _parseDevices(int Function(Pointer<Utf8>, int) list) {
    var capacity = 1024;
    for (var attempt = 0; attempt < 3; attempt++) {
      final buffer = calloc<Uint8>(capacity);
      try {
        final needed = list(buffer.cast<Utf8>(), capacity);
        if (needed > capacity) {
          capacity = needed;
          continue;
        }
        final text = buffer.cast<Utf8>().toDartString();
        return [
          for (final line in text.split('\n'))
            if (line.contains('\t')) MidiDevice(line.substring(0, line.indexOf('\t')), line.substring(line.indexOf('\t') + 1)),
        ];
      } finally {
        calloc.free(buffer);
      }
    }
    return const [];
  }

  bool openMidiOutput(String id) {
    final ptr = id.toNativeUtf8();
    try {
      return _midiOpen(ptr);
    } finally {
      malloc.free(ptr);
    }
  }

  void closeMidiOutput() => _midiClose();
  bool get midiOutputOpen => _midiIsOpen();
  void setMidiClockEnabled(bool enabled) => _setMidiClockEnabled(enabled);

  /// Console MUTE MIDI: suspende os gatilhos MIDI (notas presas são soltas).
  void setMidiCuesMuted(bool muted) => _setMidiCuesMuted(muted);
  int get midiDroppedCount => _midiDropped();

  bool sendMidi(List<int> bytes) {
    final ptr = calloc<Uint8>(bytes.isEmpty ? 1 : bytes.length);
    try {
      for (var i = 0; i < bytes.length; i++) {
        ptr[i] = bytes[i];
      }
      return _sendMidi(ptr, bytes.length);
    } finally {
      calloc.free(ptr);
    }
  }

  bool configureCues(List<AutomationCue> cues) {
    if (!AutomationCue.validSequence(cues)) return false;
    final slots = cues.isEmpty ? 1 : cues.length;
    final times = calloc<Double>(slots), bytes = calloc<Uint8>(3 * slots), sizes = calloc<Uint8>(slots);
    try {
      for (var i = 0; i < cues.length; i++) {
        times[i] = cues[i].timeSeconds;
        final message = cues[i].midiBytes;
        sizes[i] = message.length;
        for (var b = 0; b < message.length; b++) {
          bytes[3 * i + b] = message[b];
        }
      }
      return _configureCues(times, bytes, sizes, cues.length);
    } finally {
      calloc.free(times);
      calloc.free(bytes);
      calloc.free(sizes);
    }
  }

  /// Índices das automações disparadas desde a última consulta.
  List<int> pollCues({int max = 64}) {
    final out = calloc<Uint32>(max);
    try {
      final n = _pollCues(out, max);
      return [for (var i = 0; i < n; i++) out[i]];
    } finally {
      calloc.free(out);
    }
  }

  bool setChannelRoute(int channelIndex, ChannelRoute route) =>
      _setChannelRoute(channelIndex, route.outputBase, route.mono);
  void setMasterVolume(double volume) => _setMasterVolume(volume);
  void setGuidesEnabled(bool enabled) => _setGuidesEnabled(enabled);
  Future<bool> configureGuidesAsync(List<GuideCue> cues, List<String> paths) => _isolateOnDeck(deck, (engine) => engine.configureGuides(cues, paths));
  bool configureGuides(List<GuideCue> cues, List<String> paths) {
    if (!GuideCue.validSequence(cues) || paths.length != cues.length) return false;
    final count=cues.length;
    final slots=count == 0 ? 1 : count;
    final times=calloc<Double>(slots), gains=calloc<Float>(slots);
    final strings=paths.map((p)=>p.toNativeUtf8()).toList();
    final nativePaths=calloc<Pointer<Utf8>>(slots);
    try {
      for(var i=0;i<count;i++) { times[i]=cues[i].timeSeconds; gains[i]=cues[i].gain; nativePaths[i]=strings[i]; }
      return _configureGuides(times,nativePaths,gains,count);
    } finally { for(final p in strings) { malloc.free(p); } calloc.free(times); calloc.free(gains); calloc.free(nativePaths); }
  }
  /// Agenda de guias manuais + dinâmicas. [paths] leva cada nome de recurso ao WAV preparado.
  bool configureGuideSchedule(List<ScheduledGuide> guides, Map<String, String> paths) {
    if (guides.length > 4096) return false;
    final count = guides.length, slots = count == 0 ? 1 : count;
    final times = calloc<Double>(slots), targets = calloc<Double>(slots), gains = calloc<Float>(slots);
    final normal = calloc<Pointer<Utf8>>(slots), replacement = calloc<Pointer<Utf8>>(slots);
    final strings = <Pointer<Utf8>>[];
    Pointer<Utf8> path(String? name) {
      if (name == null) return nullptr;
      final file = paths[name];
      if (file == null) throw ArgumentError('Recurso de guia não preparado: $name');
      final value = file.toNativeUtf8();
      strings.add(value);
      return value;
    }
    try {
      for (var i = 0; i < count; i++) {
        final g = guides[i];
        times[i] = g.timeSeconds;
        targets[i] = g.targetSeconds;
        gains[i] = g.gain;
        normal[i] = path(g.resource);
        replacement[i] = path(g.replacement);
      }
      return _configureGuidesEx(times, normal, replacement, targets, gains, count);
    } on ArgumentError {
      return false;
    } finally {
      for (final p in strings) {
        malloc.free(p);
      }
      calloc.free(times);
      calloc.free(targets);
      calloc.free(gains);
      calloc.free(normal);
      calloc.free(replacement);
    }
  }

  Future<bool> configureGuideScheduleAsync(List<ScheduledGuide> guides, Map<String, String> paths) =>
      _isolateOnDeck(deck, (engine) => engine.configureGuideSchedule(guides, paths));

  /// Pré-roll de seção: um compasso de click e contagem antes de tocar a partir de [starts] (segundos da música).
  /// [countPaths][k] fala "k+1" (null = silêncio).
  bool configurePreroll(bool enabled, List<double> starts, List<String?> countPaths) {
    if (starts.length > 4096 || countPaths.length > 16) return false;
    final startSlots = starts.isEmpty ? 1 : starts.length, countSlots = countPaths.isEmpty ? 1 : countPaths.length;
    final nativeStarts = calloc<Double>(startSlots);
    final nativeCounts = calloc<Pointer<Utf8>>(countSlots);
    final strings = <Pointer<Utf8>>[];
    try {
      for (var i = 0; i < starts.length; i++) {
        nativeStarts[i] = starts[i];
      }
      for (var i = 0; i < countPaths.length; i++) {
        final path = countPaths[i];
        if (path == null) continue;
        final value = path.toNativeUtf8();
        strings.add(value);
        nativeCounts[i] = value;
      }
      return _configurePreroll(enabled, nativeStarts, starts.length, nativeCounts, countPaths.length);
    } finally {
      for (final p in strings) {
        malloc.free(p);
      }
      calloc.free(nativeStarts);
      calloc.free(nativeCounts);
    }
  }

  Future<bool> configurePrerollAsync(bool enabled, List<double> starts, List<String?> countPaths) =>
      _isolateOnDeck(deck, (engine) => engine.configurePreroll(enabled, starts, countPaths));

  bool get isPrerolling => _isPrerolling();

  /// Pontos da automação do mixer (ver [automationPoints]). O motor valida antes de trocar.
  bool configureMixerAutomation(List<AutomationPoint> points) {
    if (points.length > 16384) return false;
    final slots = points.isEmpty ? 1 : points.length;
    final starts = calloc<Double>(slots), ends = calloc<Double>(slots), values = calloc<Float>(slots);
    final params = calloc<Int32>(slots);
    try {
      for (var i = 0; i < points.length; i++) {
        starts[i] = points[i].start;
        ends[i] = points[i].end;
        params[i] = points[i].param;
        values[i] = points[i].value;
      }
      return _configureMixerAutomation(starts, ends, params, values, points.length);
    } finally {
      calloc.free(starts);
      calloc.free(ends);
      calloc.free(values);
      calloc.free(params);
    }
  }

  void setAutomationEnabled(bool enabled) => _setAutomationEnabled(enabled);

  /// Botão de fade (liga/desliga): [down] leva o som a zero em [seconds] a partir do nível atual, senão volta ao cheio.
  /// Não pausa nem gera evento; parado, vale na hora. Pausa e seek mantêm o nível; parar, RTZ e música nova o devolvem.
  bool setFade(bool down, double seconds) => _setFade(down, seconds);
  /// O botão de fade está ligado (o alvo é o silêncio).
  bool get fadeDown => _getFadeDown();
  /// Início e fim personalizados da música em segundos de música (0/0 = arquivo inteiro).
  bool setPlayRange(double startSeconds, double endSeconds) => _setPlayRange(startSeconds, endSeconds);
  (double, double) get playRange {
    final out = calloc<Double>(2);
    try {
      _getPlayRange(out);
      return (out[0], out[1]);
    } finally {
      calloc.free(out);
    }
  }
  /// Cria (se preciso) o deck da próxima música; use `WTracksEngine(deck: 1)` para carregá-lo e configurá-lo.
  bool prepareNextDeck() => _prepareNextDeck();
  void releaseNextDeck() => _releaseNextDeck();
  /// Agenda a entrada da próxima música (deck 1): [kind] 0 = Overlap, 1 = Crossfade; [startSeconds] em tempo da música que toca
  /// (< 0 = agora); sem laço ativo. Gera [transportEventTransitionStarted] e [transportEventTransitionFinished].
  bool scheduleTransition(int kind, double startSeconds, double durationSeconds) => _scheduleTransition(kind, startSeconds, durationSeconds);
  void cancelTransition() => _cancelTransition();
  /// -1 = não começou, 0..1 = em curso, 1 = terminou e espera o [handoff].
  double get transitionProgress => _transitionProgress();
  bool get transitionScheduled => _transitionScheduled();
  /// A próxima música assume o dispositivo e passa a responder pelo deck 0; a antiga vira deck 1, parada (descarregue-a).
  bool handoff() => _handoff();
  /// RTZ: descarta laço ao vivo e enfileirado e devolve o fade; não mexe em play/pause, posição, MUTE MIDI nem nos laços predefinidos.
  void resetTransportState() => _resetTransportState();
  /// Fade nos últimos [seconds] da música (0 desliga).
  bool setEndFade(double seconds) => _setEndFade(seconds);
  void setChannelExcludedFromFade(int channelIndex, bool excluded) => _setChannelExcludedFromFade(channelIndex, excluded);
  /// Ganho atual do fade (1 = cheio).
  double get fadeGain => _getFadeGain();
  /// Eventos desde a última leitura: [transportEventEndReached].
  int pollTransportEvents() => _pollTransportEvents();
  static const transportEventEndReached = 1, transportEventTransitionStarted = 2, transportEventTransitionFinished = 4;

  /// Áreas cortadas (segundos da música) que a reprodução pula; decodifica pontes de áudio — use a versão async.
  bool configureSkips(List<(double, double)> areas) {
    if (areas.length > 32) return false;
    final slots = areas.isEmpty ? 1 : areas.length;
    final starts = calloc<Double>(slots), ends = calloc<Double>(slots);
    try {
      for (var i = 0; i < areas.length; i++) {
        starts[i] = areas[i].$1;
        ends[i] = areas[i].$2;
      }
      return _configureSkips(starts, ends, areas.length);
    } finally {
      calloc.free(starts);
      calloc.free(ends);
    }
  }

  Future<bool> configureSkipsAsync(List<(double, double)> areas) => _isolateOnDeck(deck, (engine) => engine.configureSkips(areas));

  /// Volta atual do laço ativo (1..) e o total de repetições (0 = até soltar); (0, 0) sem laço.
  (int, int) get loopPass {
    final pass = calloc<Int32>(), repeats = calloc<Int32>();
    try {
      _getLoopPass(pass, repeats);
      return (pass.value, repeats.value);
    } finally {
      calloc.free(pass);
      calloc.free(repeats);
    }
  }

  /// Agenda MIDI (ver [buildMidiSchedule]); o índice que pollCues devolve é a posição em [schedule].
  bool configureMidiSchedule(List<ScheduledMidi> schedule) {
    if (schedule.length > 4096) return false;
    final slots = schedule.isEmpty ? 1 : schedule.length;
    final times = calloc<Double>(slots), bytes = calloc<Uint8>(3 * slots), sizes = calloc<Uint8>(slots), flags = calloc<Uint8>(slots);
    try {
      for (var i = 0; i < schedule.length; i++) {
        final m = schedule[i];
        times[i] = m.timeSeconds;
        sizes[i] = m.bytes.length;
        flags[i] = m.disableLoop ? 1 : 0;
        for (var b = 0; b < m.bytes.length && b < 3; b++) {
          bytes[3 * i + b] = m.bytes[b];
        }
      }
      return _configureCuesEx(times, bytes, sizes, flags, schedule.length);
    } finally {
      calloc.free(times);
      calloc.free(bytes);
      calloc.free(sizes);
      calloc.free(flags);
    }
  }

  /// Entradas MIDI para mapeamentos ("id\tnome").
  List<MidiDevice> listMidiInputs() => _parseDevices(_midiListInputs);
  bool openMidiInput(String id) {
    final native = id.toNativeUtf8();
    try {
      return _midiOpenInput(native);
    } finally {
      malloc.free(native);
    }
  }

  void closeMidiInput() => _midiCloseInput();
  bool get midiInputOpen => _midiInputOpen();

  /// Mensagens recebidas desde a última leitura, cada uma como lista de 1..3 bytes.
  List<List<int>> pollMidiInput({int max = 128}) {
    final out = calloc<Uint32>(max);
    try {
      final n = _pollMidiInput(out, max);
      return [
        for (var i = 0; i < n; i++) [for (var b = 0; b < (out[i] >> 24); b++) (out[i] >> (8 * b)) & 0xFF],
      ];
    } finally {
      calloc.free(out);
    }
  }

  /// Entrada simulada (testes; não há hardware MIDI aqui).
  bool injectMidiInput(List<int> bytes) {
    final native = calloc<Uint8>(bytes.isEmpty ? 1 : bytes.length);
    try {
      for (var i = 0; i < bytes.length; i++) {
        native[i] = bytes[i];
      }
      return _injectMidiInput(native, bytes.length);
    } finally {
      calloc.free(native);
    }
  }

  /// Buses da música (até 16), na ordem de [Track.buses].
  bool configureBuses(int count) => _configureBuses(count);
  bool setBus(int index, SongBus bus) => _setBus(index, bus.volume, bus.muted, bus.route.outputBase, bus.route.mono);
  void setBusSoloMuted(int index, bool muted) => _setBusSoloMuted(index, muted);
  /// [bus] -1 = direto para a saída do canal.
  bool setChannelBus(int channelIndex, int bus) => _setChannelBus(channelIndex, bus);
  /// "Enviar click e guia para a esquerda e faixas para a direita".
  void setStereoSplit(bool enabled) => _setStereoSplit(enabled);
  /// Picos dos buses desde a leitura anterior (e zera).
  List<double> takeBusMeters() {
    const capacity = 16;
    final peaks = calloc<Float>(capacity);
    try {
      final count = _takeBusMeters(peaks, capacity).clamp(0, capacity);
      return [for (var i = 0; i < count; i++) peaks[i]];
    } finally {
      calloc.free(peaks);
    }
  }

  /// Picos lineares desde a leitura anterior (e zera): por canal (pós-fader) e por saída (pós-master, L/R).
  (List<double>, List<double>) takeMeters() {
    const capacity = 64, outputs = 2;
    final channels = calloc<Float>(capacity), out = calloc<Float>(outputs);
    try {
      final count = _takeMeters(channels, capacity, out, outputs).clamp(0, capacity);
      return ([for (var i = 0; i < count; i++) channels[i]], [for (var i = 0; i < outputs; i++) out[i]]);
    } finally {
      calloc.free(channels);
      calloc.free(out);
    }
  }
  void setChannelSoloMuted(int channelIndex, bool muted) => _setChannelSoloMuted(channelIndex, muted);

  /// Estado efetivo do mixer na posição atual (automação ligada) ou os valores manuais.
  MixState mixState() {
    const capacity = 64;
    final volumes = calloc<Float>(capacity), master = calloc<Float>(1);
    final mutes = calloc<Uint8>(capacity);
    try {
      final count = _getMixState(volumes, mutes, capacity, master).clamp(0, capacity);
      final channelVolumes = [for (var i = 0; i < count; i++) volumes[i]];
      final channelMutes = [for (var i = 0; i < count; i++) mutes[i] != 0];
      final buses = _getBusState(volumes, mutes, 16).clamp(0, 16);
      return MixState(channelVolumes, channelMutes, master.value,
          busVolumes: [for (var i = 0; i < buses; i++) volumes[i]], busMutes: [for (var i = 0; i < buses; i++) mutes[i] != 0]);
    } finally {
      calloc.free(volumes);
      calloc.free(master);
      calloc.free(mutes);
    }
  }

  List<double> get loopState {
    final values = calloc<Double>(6);
    try { _getLoopState(values); return List.generate(6, (i) => values[i]); }
    finally { calloc.free(values); }
  }

  /// [repeats] passagens antes de a música seguir após o fim do laço (0 = laço contínuo).
  bool setLoop(double start, double end, bool enabled, {int repeats = 0}) =>
      repeats == 0 ? _setLoop(start, end, enabled) : _setLoopRepeats(start, end, enabled, repeats);
  Future<bool> setLoopAsync(double start, double end, bool enabled, {int repeats = 0}) =>
      _isolateOnDeck(deck, (engine) => engine.setLoop(start, end, enabled, repeats: repeats));
  bool enqueueLoop(double start, double end, {int repeats = 0}) =>
      repeats == 0 ? _enqueueLoop(start, end) : _enqueueLoopRepeats(start, end, repeats);
  Future<bool> enqueueLoopAsync(double start, double end, {int repeats = 0}) =>
      _isolateOnDeck(deck, (engine) => engine.enqueueLoop(start, end, repeats: repeats));

  /// Seções que entram em laço sozinhas ao chegar ao início (até 16, sem sobreposição). Decodifica o áudio:
  /// use [configurePresetLoopsAsync] fora da interface.
  bool configurePresetLoops(List<SongSection> sections) {
    if (sections.length > 16 || !SongSection.validSequence(sections)) return false;
    final slots = sections.isEmpty ? 1 : sections.length;
    final starts = calloc<Double>(slots), ends = calloc<Double>(slots), repeats = calloc<Int32>(slots);
    try {
      for (var i = 0; i < sections.length; i++) {
        starts[i] = sections[i].playStart;
        ends[i] = sections[i].playEnd;
        repeats[i] = 0; // preset = loop until released
      }
      return _configurePresetLoops(starts, ends, repeats, sections.length);
    } finally {
      calloc.free(starts);
      calloc.free(ends);
      calloc.free(repeats);
    }
  }

  Future<bool> configurePresetLoopsAsync(List<SongSection> sections) => _isolateOnDeck(deck, (engine) => engine.configurePresetLoops(sections));

  /// Mudanças de andamento/compasso depois do segmento base do click (tempo da música).
  bool setClickTempoChanges(List<TempoChange> changes) {
    if (!TempoChange.validSequence(changes)) return false;
    final slots = changes.isEmpty ? 1 : changes.length;
    final starts = calloc<Double>(slots), bpms = calloc<Double>(slots), nums = calloc<Int32>(slots), dens = calloc<Int32>(slots);
    try {
      for (var i = 0; i < changes.length; i++) {
        starts[i] = changes[i].startSeconds;
        bpms[i] = changes[i].bpm;
        nums[i] = changes[i].numerator;
        dens[i] = changes[i].denominator;
      }
      return _setClickTempoChanges(starts, bpms, nums, dens, changes.length);
    } finally {
      calloc.free(starts);
      calloc.free(bpms);
      calloc.free(nums);
      calloc.free(dens);
    }
  }
  void clearQueuedLoop() => _clearQueuedLoop();
  bool get loopEnabled => _getLoopEnabled();
  bool get queuedLoopEnabled => _getQueuedLoopEnabled();
  double get loopStart => _getLoopStart();
  double get loopEnd => _getLoopEnd();
  double get queuedLoopStart => _getQueuedLoopStart();
  double get queuedLoopEnd => _getQueuedLoopEnd();
  int get underrunCount => _getUnderrunCount();

  Future<bool> loadClickBankAsync(List<String?> paths) =>
      _isolateOnDeck(deck, (engine) => engine.loadClickBank(paths));

  bool loadClickBank(List<String?> paths) {
    if (paths.length != 4) return false;
    final pointers = paths.map((path) => path?.toNativeUtf8() ?? nullptr).toList();
    final bank = calloc<Pointer<Utf8>>(4);
    try {
      for (var voice = 0; voice < 4; voice++) { bank[voice] = pointers[voice]; }
      return _loadClickBank(bank, 4);
    } finally {
      for (final pointer in pointers) { if (pointer != nullptr) malloc.free(pointer); }
      calloc.free(bank);
    }
  }

  Future<bool> loadClickSoundAsync(int voice, String? path) =>
      _isolateOnDeck(deck, (engine) => engine.loadClickSound(voice, path));

  bool loadClickSound(int voice, String? path) {
    final pointer = path?.toNativeUtf8() ?? nullptr;
    try {
      return _loadClickSound(voice, pointer);
    } finally {
      if (pointer != nullptr) malloc.free(pointer);
    }
  }

  void setClickEnabled(bool enabled) => _setClickEnabled(enabled);
  void setClickBpm(double bpm) => _setClickBpm(bpm);

  EngineErrorCode get lastErrorCode => engineErrorCodeFromInt(_getLastErrorCode());

  String get lastError => _getLastError().toDartString();

  void setClickTimeSignature(int numerator, int denominator) =>
      _setClickTimeSignature(numerator, denominator);

  void setClickOffsetSeconds(double offsetSeconds) =>
      _setClickOffset(offsetSeconds);

  /// Versão síncrona de [generateWaveformPeaksAsync] -- bloqueia a thread
  /// chamadora. Preferir a versão assíncrona a partir da UI; esta existe
  /// para uso em testes/scripts e para espelhar o padrão de
  /// loadTrack/loadTrackSync já usado nesta classe.
  List<double>? generateWaveformPeaksSync(List<String> channelPaths) {
    final pathPointers = channelPaths.map((p) => p.toNativeUtf8()).toList();
    final pathsArray = calloc<Pointer<Utf8>>(pathPointers.length);
    for (var i = 0; i < pathPointers.length; i++) {
      pathsArray[i] = pathPointers[i];
    }
    final outPeaks = calloc<Float>(waveformBucketCount);

    try {
      final success = _generateWaveformPeaks(
        pathsArray,
        pathPointers.length,
        waveformBucketCount,
        outPeaks,
      );
      if (!success) return null;
      return List<double>.generate(
        waveformBucketCount,
        (i) => outPeaks[i].toDouble(),
        growable: false,
      );
    } finally {
      for (final p in pathPointers) {
        malloc.free(p);
      }
      calloc.free(pathsArray);
      calloc.free(outPeaks);
    }
  }

  /// Gera os picos de waveform (mixagem de todos os canais) para
  /// [channelPaths], rodando em um isolate separado -- arquivos de música
  /// podem ser grandes, então isso não pode bloquear a UI. Retorna `null`
  /// se a extração falhar (arquivo inválido/corrompido).
  Future<List<double>?> generateWaveformPeaksAsync(List<String> channelPaths) {
    return Isolate.run(() {
      final lib = _openLibrary();
      final fn = lib
          .lookup<NativeFunction<_GenerateWaveformNative>>(
            'wtracks_generate_waveform_peaks',
          )
          .asFunction<_GenerateWaveformDart>();

      final pathPointers = channelPaths.map((p) => p.toNativeUtf8()).toList();
      final pathsArray = calloc<Pointer<Utf8>>(pathPointers.length);
      for (var i = 0; i < pathPointers.length; i++) {
        pathsArray[i] = pathPointers[i];
      }
      final outPeaks = calloc<Float>(waveformBucketCount);

      try {
        final success =
            fn(pathsArray, pathPointers.length, waveformBucketCount, outPeaks,
        );
        if (!success) return null;
        return List<double>.generate(
          waveformBucketCount,
          (i) => outPeaks[i].toDouble(),
          growable: false,
        );
      } finally {
        for (final p in pathPointers) {
          malloc.free(p);
        }
        calloc.free(pathsArray);
        calloc.free(outPeaks);
      }
    });
  }
}
