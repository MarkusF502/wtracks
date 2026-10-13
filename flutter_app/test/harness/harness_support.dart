// Infraestrutura compartilhada pelos testes do harness (test/harness/).
// Permite exercitar providers e telas sem celular: o engine nativo é
// substituído por [FakeEngine] e o disco por [InMemoryPersistence].

import 'dart:ffi';
import 'package:flutter_app/models/engine_error.dart';
import 'dart:io';
import 'dart:math' as math;
import 'dart:typed_data';

import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/native/wtracks_bindings.dart';
import 'package:flutter_app/services/persistence_service.dart';

/// Engine falso que grava cada chamada recebida, pra os testes conferirem
/// o que a UI/providers mandaram pro motor nativo.
class FakeEngine implements WTracksEngine {
  @override
  bool ready = true;
  @override
  EngineErrorCode get lastErrorCode => EngineErrorCode.unknown;
  final calls = <String>[];

  bool playing = false;
  double position = 0;
  double length = 180;
  String error = '';

  @override
  bool initialise({int sampleRate = 44100, int bufferSize = 256}) => true;
  @override
  void shutdown() {}
  @override
  bool loadTrack(String songId, List<String> channelFilePaths) => true;
  @override
  bool loadTrackSync(String songId, List<String> channelFilePaths) => true;
  @override
  Future<bool> loadTrackAsync(String songId, List<String> channelFilePaths) async => true;
  @override
  void unloadTrack() { calls.add('unload'); }
  @override
  void play() {
    calls.add('play');
    playing = true;
  }

  @override
  void pause() {
    calls.add('pause');
    playing = false;
  }

  @override
  void stop() {
    calls.add('stop');
    playing = false;
  }

  @override
  void seekToSeconds(double seconds) => calls.add('seek($seconds)');
  @override
  double get currentPositionSeconds => position;
  @override
  double get totalLengthSeconds => length;
  @override
  bool get isPlaying => playing;
  @override
  void setChannelVolume(int channelIndex, double volume) =>
      calls.add('volume($channelIndex,$volume)');
  @override
  void setChannelMuted(int channelIndex, bool muted) => calls.add('muted($channelIndex,$muted)');
  @override
  int get channelCount => 0;
  ClickSettings? configuredClick;
  @override
  bool configureClick(ClickSettings settings) {
    if (!settings.isValid) return false;
    configuredClick = settings;
    setClickBpm(settings.bpm);
    setClickTimeSignature(
      settings.timeSignatureNumerator,
      settings.timeSignatureDenominator,
    );
    setClickOffsetSeconds(settings.beatOffsetSeconds);
    return true;
  }

  @override
  Future<bool> loadClickBankAsync(List<String?> paths) async => loadClickBank(paths);
  @override
  bool loadClickBank(List<String?> paths) {
    if (paths.length != 4) return false;
    for (var voice = 0; voice < 4; voice++) { loadClickSound(voice, paths[voice]); }
    return true;
  }
  @override
  Future<bool> loadClickSoundAsync(int voice, String? path) async =>
      loadClickSound(voice, path);
  @override
  bool loadClickSound(int voice, String? path) {
    calls.add('clickSound($voice,$path)');
    return true;
  }

  @override
  void setClickEnabled(bool enabled) => calls.add('clickEnabled($enabled)');
  @override
  void setClickBpm(double bpm) => calls.add('bpm($bpm)');
  @override
  String get lastError => error;
  @override
  void setClickTimeSignature(int numerator, int denominator) =>
      calls.add('timeSig($numerator/$denominator)');
  @override
  void setClickOffsetSeconds(double offsetSeconds) => calls.add('offset($offsetSeconds)');
  @override
  List<double>? generateWaveformPeaksSync(List<String> channelPaths) => null;
  @override
  Future<List<double>?> generateWaveformPeaksAsync(List<String> channelPaths) async => null;
}

/// Persistência só em memória -- evita IO real dentro do FakeAsync do
/// testWidgets (onde futures de dart:io não completam sem runAsync).
class InMemoryPersistence extends PersistenceService {
  final tracks = <String, Track>{};
  final setlists = <String, Setlist>{};

  InMemoryPersistence({List<Track> initialTracks = const [], List<Setlist> initialSetlists = const []})
      : super(rootDirectoryResolver: () async => Directory.systemTemp) {
    for (final t in initialTracks) {
      tracks[t.id] = t;
    }
    for (final s in initialSetlists) {
      setlists[s.id] = s;
    }
  }

  @override
  Future<Track> saveTrack(Track track) async => tracks[track.id] = track;
  @override
  Future<List<Track>> loadAllTracks() async => tracks.values.toList();
  @override
  Future<Track?> loadTrack(String id) async => tracks[id];
  @override
  Future<void> deleteTrack(String id) async => tracks.remove(id);
  @override
  Future<void> saveSetlist(Setlist setlist) async => setlists[setlist.id] = setlist;
  @override
  Future<List<Setlist>> loadAllSetlists() async => setlists.values
      .map((s) => s.copyWith(tracks: s.tracks.where((t) => tracks.containsKey(t.id)).toList()))
      .toList();
  @override
  Future<Setlist?> loadSetlist(String id) async => setlists[id];
  @override
  Future<void> deleteSetlist(String id) async => setlists.remove(id);
  @override
  Future<void> saveWaveformPeaks(String trackId, List<double> peaks) async {}
  @override
  Future<List<double>?> loadWaveformPeaks(String trackId) async => null;
  @override
  Future<void> deleteWaveformPeaks(String trackId) async {}
}

Track sampleTrack({
  String id = 't1',
  String title = 'Grande é o Senhor',
  int channels = 4,
  ClickSettings click = const ClickSettings(bpm: 72),
}) {
  const labels = ['Click', 'Guia', 'Bateria', 'Baixo', 'Teclas', 'Guitarra', 'Pad', 'Voz Ref'];
  return Track(
    id: id,
    title: title,
    artist: 'Adhemar de Campos',
    key: 'G',
    clickSettings: click,
    channels: [
      for (var i = 0; i < channels; i++)
        ChannelInfo(label: labels[i % labels.length], filePath: '/fake/$id/$i.wav'),
    ],
  );
}

/// Silencia o MethodChannel do serviço de playback em segundo plano (só
/// existe no Android) e registra as chamadas.
List<MethodCall> mockBackgroundChannel() {
  final calls = <MethodCall>[];
  TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger.setMockMethodCallHandler(
    const MethodChannel('wtracks/background'),
    (call) async {
      calls.add(call);
      return null;
    },
  );
  return calls;
}

/// Grava um WAV PCM16 mono (seno) -- fixture para os testes que usam o
/// engine nativo de verdade via FFI.
File writeSineWav(String path, {double seconds = 1.0, int sampleRate = 44100, double freq = 440}) {
  final n = (seconds * sampleRate).round();
  final data = ByteData(44 + n * 2);
  void ascii(int offset, String s) {
    for (var i = 0; i < s.length; i++) {
      data.setUint8(offset + i, s.codeUnitAt(i));
    }
  }

  ascii(0, 'RIFF');
  data.setUint32(4, 36 + n * 2, Endian.little);
  ascii(8, 'WAVE');
  ascii(12, 'fmt ');
  data.setUint32(16, 16, Endian.little);
  data.setUint16(20, 1, Endian.little); // PCM
  data.setUint16(22, 1, Endian.little); // mono
  data.setUint32(24, sampleRate, Endian.little);
  data.setUint32(28, sampleRate * 2, Endian.little);
  data.setUint16(32, 2, Endian.little);
  data.setUint16(34, 16, Endian.little);
  ascii(36, 'data');
  data.setUint32(40, n * 2, Endian.little);
  for (var i = 0; i < n; i++) {
    final v = (0.5 * math.sin(2 * math.pi * freq * i / sampleRate) * 32767).round();
    data.setInt16(44 + i * 2, v, Endian.little);
  }
  return File(path)..writeAsBytesSync(data.buffer.asUint8List());
}

/// true se libwtracks_engine.so pode ser aberta (harness exporta
/// LD_LIBRARY_PATH apontando pro build Linux do engine).
bool nativeEngineAvailable() {
  try {
    DynamicLibrary.open('libwtracks_engine.so');
    return true;
  } catch (_) {
    return false;
  }
}
