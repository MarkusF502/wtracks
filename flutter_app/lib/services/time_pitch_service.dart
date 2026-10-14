import 'dart:async';
import 'dart:io';
import 'dart:typed_data';
import 'package:path_provider/path_provider.dart';
import '../models/track.dart';
import '../native/wtracks_bindings.dart';

class TimePitchCancelled implements Exception {
  const TimePitchCancelled();
  @override
  String toString() => 'Processamento cancelado';
}

class WavInfo {
  final int channels;
  final int sampleRate;
  final int frames;
  const WavInfo({required this.channels, required this.sampleRate, required this.frames});
}

class TimePitchFailure implements Exception {
  final String message;
  const TimePitchFailure(this.message);
  @override
  String toString() => message;
}

/// Renderiza (e guarda em cache) as faixas processadas de uma música. O
/// processamento é offline no motor nativo; o cache vive no diretório de
/// suporte do app e só mantém a versão atual de cada música.
class TimePitchService {
  static const _algorithmVersion = 1;
  static const _parallelism = 2;
  final Future<Directory> Function() directoryResolver;
  TimePitchService({Future<Directory> Function()? directoryResolver})
      : directoryResolver = directoryResolver ?? getApplicationSupportDirectory;

  int _nextToken = 1;
  final _active = <int>{};
  bool _cancelRequested = false;

  /// Cancela o processamento em andamento (se houver).
  void cancel(WTracksEngine engine) {
    _cancelRequested = true;
    for (final token in _active.toList()) {
      engine.cancelTimePitch(token);
    }
  }

  static String _fnv(String text) {
    var hash = 0xcbf29ce484222325;
    for (final unit in text.codeUnits) {
      hash = ((hash ^ unit) * 0x100000001b3) & 0x7fffffffffffffff;
    }
    return hash.toRadixString(16).padLeft(16, '0');
  }

  Future<List<String>> prepare(
    WTracksEngine engine,
    Track track, {
    void Function(double progress)? onProgress,
  }) async {
    final settings = track.timePitch;
    if (settings.isIdentity) return track.channelFilePaths;
    if (!settings.isValid) throw const TimePitchFailure('Ajuste de tom/andamento inválido');
    _cancelRequested = false;
    final directory = Directory('${(await directoryResolver()).path}/timepitch/${_fnv(track.id)}');
    await directory.create(recursive: true);
    final outputs = <String>[];
    for (var i = 0; i < track.channels.length; i++) {
      final source = File(track.channels[i].filePath);
      if (!await source.exists()) throw TimePitchFailure('Arquivo de origem ausente: ${track.channels[i].label}');
      final stat = await source.stat();
      final key = _fnv('$_algorithmVersion|${source.path}|${stat.size}|${stat.modified.microsecondsSinceEpoch}|'
          '${settings.semitones}|${settings.tempoRatio}|${settings.complex}');
      outputs.add('${directory.path}/$i-$key.wav');
    }
    var done = 0;
    onProgress?.call(0);
    final pending = <int>[
      for (var i = 0; i < outputs.length; i++)
        if (!await _usable(outputs[i], track.channels[i].filePath, settings.timeFactor)) i,
    ];
    done = outputs.length - pending.length;
    if (pending.isEmpty) onProgress?.call(1);
    var cursor = 0;
    Object? failure;
    Future<void> worker() async {
      while (failure == null && !_cancelRequested) {
        if (cursor >= pending.length) return;
        final index = pending[cursor++];
        final token = _nextToken++;
        _active.add(token);
        try {
          final ok = await engine.processTimePitchAsync(track.channels[index].filePath, outputs[index], settings.timeFactor,
              settings.pitchFactor, settings.complex, token);
          if (!ok) {
            failure = _cancelRequested ? const TimePitchCancelled() : TimePitchFailure(engine.lastError);
            return;
          }
          done++;
          onProgress?.call(done / outputs.length);
        } finally {
          _active.remove(token);
        }
      }
    }

    await Future.wait([for (var w = 0; w < _parallelism; w++) worker()]);
    if (_cancelRequested) throw const TimePitchCancelled();
    if (failure != null) throw failure!;
    // Keep only the current rendering of this song.
    final keep = outputs.toSet();
    await for (final entry in directory.list()) {
      if (entry is File && !keep.contains(entry.path)) {
        try {
          await entry.delete();
        } on FileSystemException {
          // A concurrent reader may still hold it; the next prepare retries.
        }
      }
    }
    return outputs;
  }

  /// Um rendering em cache só é reaproveitado se for um WAV inteiro: cabeçalho coerente com o tamanho do arquivo,
  /// quadros completos e, quando a origem também é WAV, duração compatível com o fator de tempo pedido.
  Future<bool> _usable(String path, String sourcePath, double timeFactor) async {
    final rendered = await readWavInfo(path);
    if (rendered == null || rendered.frames <= 0) return false;
    final source = await readWavInfo(sourcePath);
    if (source == null || source.sampleRate <= 0 || rendered.sampleRate <= 0) return true;
    final expected = source.frames / source.sampleRate * timeFactor;
    final actual = rendered.frames / rendered.sampleRate;
    return (actual - expected).abs() <= 0.05 + expected * 0.02;
  }

  /// Lê o cabeçalho de um WAV e confere que ele descreve o arquivo inteiro; devolve null se estiver truncado,
  /// inconsistente ou não for WAV.
  static Future<WavInfo?> readWavInfo(String path) async {
    RandomAccessFile? handle;
    try {
      final file = File(path);
      if (!await file.exists()) return null;
      handle = await file.open();
      final length = await handle.length();
      final head = await handle.read(length < 4096 ? length : 4096);
      if (head.length < 12) return null;
      final data = ByteData.sublistView(Uint8List.fromList(head));
      String tag(int at) => String.fromCharCodes(head.sublist(at, at + 4));
      if (tag(0) != 'RIFF' || tag(8) != 'WAVE') return null;
      // O tamanho do RIFF é gravado ao fechar o arquivo: diferente do real = truncado ou nunca finalizado.
      final riffEnd = data.getUint32(4, Endian.little) + 8;
      if (riffEnd > length || length - riffEnd > 1) return null;
      int? channels, sampleRate, blockAlign;
      var at = 12;
      while (at + 8 <= head.length) {
        final size = data.getUint32(at + 4, Endian.little);
        final body = at + 8;
        if (tag(at) == 'fmt ') {
          if (size < 16 || body + 16 > head.length) return null;
          channels = data.getUint16(body + 2, Endian.little);
          sampleRate = data.getUint32(body + 4, Endian.little);
          blockAlign = data.getUint16(body + 12, Endian.little);
        } else if (tag(at) == 'data') {
          if (channels == null || sampleRate == null || blockAlign == null || channels < 1 || blockAlign < 1) return null;
          if (body + size > length || size % blockAlign != 0) return null;
          return WavInfo(channels: channels, sampleRate: sampleRate, frames: size ~/ blockAlign);
        }
        at = body + size + (size & 1);
      }
      return null;
    } on FileSystemException {
      return null;
    } finally {
      await handle?.close();
    }
  }

  /// Apaga as versões processadas de uma música (ex.: ao excluí-la).
  Future<void> discard(String trackId) async {
    final directory = Directory('${(await directoryResolver()).path}/timepitch/${_fnv(trackId)}');
    if (await directory.exists()) await directory.delete(recursive: true);
  }
}
