import 'dart:ffi';
import 'dart:io';
import 'package:ffi/ffi.dart';

// ---- Assinaturas das funções nativas (espelham ffi_bridge.h) ----

typedef _InitialiseNative = Bool Function(Int32 sampleRate, Int32 bufferSize);
typedef _InitialiseDart = bool Function(int sampleRate, int bufferSize);

typedef _VoidNative = Void Function();
typedef _VoidDart = void Function();

typedef _LoadTrackNative = Bool Function(
    Pointer<Utf8> songId, Pointer<Pointer<Utf8>> channelPaths, Int32 channelCount);
typedef _LoadTrackDart = bool Function(
    Pointer<Utf8> songId, Pointer<Pointer<Utf8>> channelPaths, int channelCount);

typedef _SeekNative = Void Function(Double seconds);
typedef _SeekDart = void Function(double seconds);

typedef _GetPositionNative = Double Function();
typedef _GetPositionDart = double Function();

typedef _IsPlayingNative = Bool Function();
typedef _IsPlayingDart = bool Function();

typedef _SetChannelVolumeNative = Void Function(Int32 channelIndex, Float volume);
typedef _SetChannelVolumeDart = void Function(int channelIndex, double volume);

typedef _SetChannelMutedNative = Void Function(Int32 channelIndex, Bool muted);
typedef _SetChannelMutedDart = void Function(int channelIndex, bool muted);

typedef _GetChannelCountNative = Int32 Function();
typedef _GetChannelCountDart = int Function();

typedef _SetClickEnabledNative = Void Function(Bool enabled);
typedef _SetClickEnabledDart = void Function(bool enabled);

typedef _SetClickBpmNative = Void Function(Double bpm);
typedef _SetClickBpmDart = void Function(double bpm);

typedef _SetClickTimeSignatureNative = Void Function(Int32 numerator, Int32 denominator);
typedef _SetClickTimeSignatureDart = void Function(int numerator, int denominator);

/// Wrapper de alto nível em torno da biblioteca nativa wtracks_engine.
/// Esta é a ÚNICA classe do app que sabe que FFI existe -- todo o
/// resto do Flutter conversa com [WTracksEngine], nunca com ponteiros
/// crus. Isso mantém o resto da UI limpo e testável.
class WTracksEngine {
  late final DynamicLibrary _lib;

  late final _InitialiseDart _initialise;
  late final _VoidDart _shutdown;
  late final _LoadTrackDart _loadTrack;
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
    _unloadTrack = _lib
        .lookup<NativeFunction<_VoidNative>>('wtracks_unload_track')
        .asFunction();
    _play = _lib.lookup<NativeFunction<_VoidNative>>('wtracks_play').asFunction();
    _pause =
        _lib.lookup<NativeFunction<_VoidNative>>('wtracks_pause').asFunction();
    _stop = _lib.lookup<NativeFunction<_VoidNative>>('wtracks_stop').asFunction();
    _seek = _lib.lookup<NativeFunction<_SeekNative>>('wtracks_seek').asFunction();
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
        .lookup<NativeFunction<_SetChannelVolumeNative>>('wtracks_set_channel_volume')
        .asFunction();
    _setChannelMuted = _lib
        .lookup<NativeFunction<_SetChannelMutedNative>>('wtracks_set_channel_muted')
        .asFunction();
    _getChannelCount = _lib
        .lookup<NativeFunction<_GetChannelCountNative>>('wtracks_get_channel_count')
        .asFunction();
    _setClickEnabled = _lib
        .lookup<NativeFunction<_SetClickEnabledNative>>('wtracks_set_click_enabled')
        .asFunction();
    _setClickBpm = _lib
        .lookup<NativeFunction<_SetClickBpmNative>>('wtracks_set_click_bpm')
        .asFunction();
    _setClickTimeSignature = _lib
        .lookup<NativeFunction<_SetClickTimeSignatureNative>>(
            'wtracks_set_click_time_signature')
        .asFunction();
  }

  static DynamicLibrary _openLibrary() {
    if (Platform.isAndroid) return DynamicLibrary.open('libwtracks_engine.so');
    if (Platform.isWindows) return DynamicLibrary.open('wtracks_engine.dll');
    if (Platform.isLinux) return DynamicLibrary.open('libwtracks_engine.so');
    throw UnsupportedError('Plataforma não suportada ainda');
  }

  bool initialise({int sampleRate = 44100, int bufferSize = 256}) =>
      _initialise(sampleRate, bufferSize);

  void shutdown() => _shutdown();

  /// Carrega uma música com múltiplos canais de áudio.
  /// [channelFilePaths] deve ter um caminho de arquivo LOCAL por canal
  /// (ex: ['guia.wav', 'click.wav', 'bateria.wav']) -- não URIs content://.
  /// A cópia de content:// para caminho local é responsabilidade do
  /// FileImportService, chamada antes disso.
  bool loadTrack(String songId, List<String> channelFilePaths) {
    final songIdPtr = songId.toNativeUtf8();
    final pathPointers = channelFilePaths.map((p) => p.toNativeUtf8()).toList();

    final pathsArray = calloc<Pointer<Utf8>>(pathPointers.length);
    for (var i = 0; i < pathPointers.length; i++) {
      pathsArray[i] = pathPointers[i];
    }

    try {
      return _loadTrack(songIdPtr, pathsArray, pathPointers.length);
    } finally {
      // Sempre liberar a memória alocada manualmente, ou vaza memória nativa
            malloc.free(songIdPtr);
      for (final p in pathPointers) {
                malloc.free(p);
      }
      calloc.free(pathsArray);
    }
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

  void setClickEnabled(bool enabled) => _setClickEnabled(enabled);
  void setClickBpm(double bpm) => _setClickBpm(bpm);
    void setClickTimeSignature(int numerator, int denominator) =>
            _setClickTimeSignature(numerator, denominator);
}