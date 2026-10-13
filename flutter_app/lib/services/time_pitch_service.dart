import 'dart:async';
import 'dart:io';
import 'package:path_provider/path_provider.dart';
import '../models/track.dart';
import '../native/wtracks_bindings.dart';

class TimePitchCancelled implements Exception {
  const TimePitchCancelled();
  @override
  String toString() => 'Processamento cancelado';
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
        if (!await _usable(outputs[i])) i,
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

  Future<bool> _usable(String path) async {
    final file = File(path);
    return await file.exists() && await file.length() > 44;
  }

  /// Apaga as versões processadas de uma música (ex.: ao excluí-la).
  Future<void> discard(String trackId) async {
    final directory = Directory('${(await directoryResolver()).path}/timepitch/${_fnv(trackId)}');
    if (await directory.exists()) await directory.delete(recursive: true);
  }
}
