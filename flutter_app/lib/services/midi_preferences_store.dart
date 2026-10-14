import 'dart:io';
import 'package:flutter/foundation.dart' show debugPrint;
import 'package:path_provider/path_provider.dart';
import 'safe_json.dart';

/// Guarda a saída MIDI escolhida pelo usuário (vale para o app todo).
class MidiPreferencesStore {
  final Future<Directory> Function() directoryResolver;
  MidiPreferencesStore({Future<Directory> Function()? directoryResolver})
      : directoryResolver = directoryResolver ?? getApplicationSupportDirectory;

  Future<File> _file() async {
    final dir = Directory('${(await directoryResolver()).path}/wtracks_data');
    await dir.create(recursive: true);
    return File('${dir.path}/midi.json');
  }

  /// O que deu errado na última leitura (ver [AppPreferencesStore.lastProblem]); null se nada.
  String? lastProblem;

  Future<String?> loadOutputId() async {
    try {
      final read = await SafeJson.read<String?>(await _file(), (json) {
        final id = json is Map ? json['outputId'] : null;
        return id is String && id.isNotEmpty ? id : null;
      });
      lastProblem = read.problem;
      return read.value;
    } on Exception catch (e) {
      debugPrint('Não foi possível ler a saída MIDI: $e'); // pasta indisponível: o app segue com os padrões
      return null;
    }
  }

  Future<void> saveOutputId(String? id) async => SafeJson.write(await _file(), {'outputId': id});
}
