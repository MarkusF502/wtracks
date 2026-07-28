import 'dart:ffi';
import 'dart:io';
import 'package:ffi/ffi.dart';

// ---- Assinaturas das funções nativas (espelham ffi_bridge.h) ----

typedef _InitialiseNative = Bool Function(Int32 sampleRate, Int32 bufferSize);
typedef _InitialiseDart = bool Function(int sampleRate, int bufferSize);

typedef _ShutdownNative = Void Function();
typedef _ShutdownDart = void Function();

typedef _LoadTrackNative = Bool Function(
    Pointer<Utf8> songId, Pointer<Pointer<Utf8>> channelPaths, Int32 channelCount);
typedef _LoadTrackDart = bool Function(
    Pointer<Utf8> songId, Pointer<Pointer<Utf8>> channelPaths, int channelCount);

typedef _PlayNative = Void Function();
typedef _PlayDart = void Function();

typedef _SetChannelVolumeNative = Void Function(Int32 channelIndex, Float volume);
typedef _SetChannelVolumeDart = void Function(int channelIndex, double volume);

typedef _GetPositionNative = Double Function();
typedef _GetPositionDart = double Function();

/// Wrapper de alto nível em torno da biblioteca nativa wtracks_engine.
/// Esta é a ÚNICA classe do app que sabe que FFI existe -- todo o
/// resto do Flutter conversa com [WTracksEngine], nunca com ponteiros
/// crus. Isso mantém o resto da UI limpo e testável.
class WTracksEngine {
  late final DynamicLibrary _lib;

  late final _InitialiseDart _initialise;
  late final _ShutdownDart _shutdown;
  late final _LoadTrackDart _loadTrack;
  late final _PlayDart _play;
  late final _PlayDart _pause;
  late final _PlayDart _stop;
  late final _SetChannelVolumeDart _setChannelVolume;
  late final _GetPositionDart _getPosition;
  late final _GetPositionDart _getLength;

  WTracksEngine() {
    _lib = _openLibrary();

    _initialise = _lib
        .lookup<NativeFunction<_InitialiseNative>>('wtracks_initialise')
        .asFunction();
    _shutdown = _lib
        .lookup<NativeFunction<_ShutdownNative>>('wtracks_shutdown')
        .asFunction();
    _loadTrack = _lib
        .lookup<NativeFunction<_LoadTrackNative>>('wtracks_load_track')
        .asFunction();
    _play = _lib.lookup<NativeFunction<_PlayNative>>('wtracks_play').asFunction();
    _pause =
        _lib.lookup<NativeFunction<_PlayNative>>('wtracks_pause').asFunction();
    _stop = _lib.lookup<NativeFunction<_PlayNative>>('wtracks_stop').asFunction();
    _setChannelVolume = _lib
        .lookup<NativeFunction<_SetChannelVolumeNative>>('wtracks_set_channel_volume')
        .asFunction();
    _getPosition = _lib
        .lookup<NativeFunction<_GetPositionNative>>('wtracks_get_position')
        .asFunction();
    _getLength = _lib
        .lookup<NativeFunction<_GetPositionNative>>('wtracks_get_length')
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
  /// [channelFilePaths] deve ter um caminho de arquivo por canal
  /// (ex: ['guia.wav', 'click.wav', 'bateria.wav']).
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
      calloc.free(songIdPtr);
      for (final p in pathPointers) {
        calloc.free(p);
      }
      calloc.free(pathsArray);
    }
  }

  void play() => _play();
  void pause() => _pause();
  void stop() => _stop();

  void setChannelVolume(int channelIndex, double volume) =>
      _setChannelVolume(channelIndex, volume);

  double get currentPositionSeconds => _getPosition();
  double get totalLengthSeconds => _getLength();
}