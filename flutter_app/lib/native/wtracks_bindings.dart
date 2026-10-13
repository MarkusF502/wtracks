import 'dart:ffi';
import 'dart:io';
import 'dart:isolate';
import 'package:ffi/ffi.dart';
import 'package:flutter/foundation.dart';
import '../models/engine_error.dart';
import '../models/track.dart';

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

  WTracksEngine() {
    _lib = _openLibrary();

    _initialise = _lib
        .lookup<NativeFunction<_InitialiseNative>>('wtracks_initialise')
        .asFunction();
    _shutdown = _lib
        .lookup<NativeFunction<_VoidNative>>('wtracks_shutdown')
        .asFunction();
    _loadTrack = _lib
        .lookup<NativeFunction<_LoadTrackNative>>('wtracks_load_track')
        .asFunction();
    _getLastError = _lib
        .lookup<NativeFunction<_GetLastErrorNative>>('wtracks_get_last_error')
        .asFunction();
    _getLastErrorCode = _lib.lookupFunction<Int32 Function(), int Function()>(
      'wtracks_get_last_error_code',
    );
    _unloadTrack = _lib
        .lookup<NativeFunction<_VoidNative>>('wtracks_unload_track')
        .asFunction();
    _play = _lib
        .lookup<NativeFunction<_VoidNative>>('wtracks_play')
        .asFunction();
    _pause = _lib
        .lookup<NativeFunction<_VoidNative>>('wtracks_pause')
        .asFunction();
    _stop = _lib
        .lookup<NativeFunction<_VoidNative>>('wtracks_stop')
        .asFunction();
    _seek = _lib
        .lookup<NativeFunction<_SeekNative>>('wtracks_seek')
        .asFunction();
    _getPosition = _lib
        .lookup<NativeFunction<_GetPositionNative>>('wtracks_get_position')
        .asFunction();
    _getLength = _lib
        .lookup<NativeFunction<_GetPositionNative>>('wtracks_get_length')
        .asFunction();
    _isPlaying = _lib
        .lookup<NativeFunction<_IsPlayingNative>>('wtracks_is_playing')
        .asFunction();
    _setChannelVolume = _lib
        .lookup<NativeFunction<_SetChannelVolumeNative>>(
          'wtracks_set_channel_volume',
        )
        .asFunction();
    _setChannelMuted = _lib
        .lookup<NativeFunction<_SetChannelMutedNative>>(
          'wtracks_set_channel_muted',
        )
        .asFunction();
    _getChannelCount = _lib
        .lookup<NativeFunction<_GetChannelCountNative>>(
          'wtracks_get_channel_count',
        )
        .asFunction();
    _setClickEnabled = _lib
        .lookup<NativeFunction<_SetClickEnabledNative>>(
          'wtracks_set_click_enabled',
        )
        .asFunction();
    _setClickBpm = _lib
        .lookup<NativeFunction<_SetClickBpmNative>>('wtracks_set_click_bpm')
        .asFunction();
    _setClickTimeSignature = _lib
        .lookup<NativeFunction<_SetClickTimeSignatureNative>>(
          'wtracks_set_click_time_signature',
        )
        .asFunction();
    _setClickOffset = _lib
        .lookup<NativeFunction<_SetClickOffsetNative>>(
          'wtracks_set_click_offset',
        )
        .asFunction();
    _configureClick = _lib
        .lookupFunction<_ConfigureClickNative, _ConfigureClickDart>(
          'wtracks_configure_click',
        );
    _loadClickSound = _lib
        .lookupFunction<_LoadClickSoundNative, _LoadClickSoundDart>(
          'wtracks_load_click_sound',
        );
    _loadClickBank = _lib.lookupFunction<_LoadClickBankNative, _LoadClickBankDart>('wtracks_load_click_bank');
    _setClickGain = _lib.lookupFunction<_ClickGainNative, _ClickGainDart>(
      'wtracks_set_click_gain',
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
  Future<bool> loadTrackAsync(String songId, List<String> channelFilePaths) {
    return Isolate.run(() {
      final lib = _openLibrary();
      final loadFn = lib
          .lookup<NativeFunction<_LoadTrackNative>>('wtracks_load_track')
          .asFunction<_LoadTrackDart>();
      final getErrorFn = lib
          .lookup<NativeFunction<_GetLastErrorNative>>('wtracks_get_last_error')
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

  Future<bool> loadClickBankAsync(List<String?> paths) =>
      Isolate.run(() => WTracksEngine().loadClickBank(paths));

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
      Isolate.run(() => WTracksEngine().loadClickSound(voice, path));

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
