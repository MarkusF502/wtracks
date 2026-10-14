import 'dart:io';
import 'package:flutter/foundation.dart' show debugPrint;
import 'package:path_provider/path_provider.dart';
import '../models/control_mapping.dart';
import 'safe_json.dart';

/// Mapeamentos de controle e a entrada MIDI escolhida (valem para o app todo).
class ControlMappingStore {
  final Future<Directory> Function() directoryResolver;
  ControlMappingStore({Future<Directory> Function()? directoryResolver})
      : directoryResolver = directoryResolver ?? getApplicationSupportDirectory;

  Future<File> _file() async {
    final dir = Directory('${(await directoryResolver()).path}/wtracks_data');
    await dir.create(recursive: true);
    return File('${dir.path}/control_mappings.json');
  }

  /// Sem arquivo: as teclas padrão. Entradas inválidas são ignoradas.
  /// O que deu errado na última leitura (ver [AppPreferencesStore.lastProblem]); null se nada.
  String? lastProblem;

  Future<(List<ControlMapping>, String?)> load() async {
    try {
      final read = await SafeJson.read<(List<ControlMapping>, String?)>(await _file(), (json) {
        if (json is! Map) throw const FormatException('formato inesperado');
        final list = json['mappings'] is List ? json['mappings'] as List : const [];
        final input = json['inputId'];
        return (<ControlMapping>[for (final m in list) ?ControlMapping.fromJson(m)], input is String && input.isNotEmpty ? input : null);
      });
      lastProblem = read.problem;
      return read.value ?? (defaultKeyboardMappings, null);
    } on Exception catch (e) {
      debugPrint('Não foi possível ler os mapeamentos de controle: $e'); // pasta indisponível: o app segue com os padrões
      return (defaultKeyboardMappings, null);
    }
  }

  Future<void> save(List<ControlMapping> mappings, String? inputId) async =>
      SafeJson.write(await _file(), {'mappings': mappings.map((m) => m.toJson()).toList(), 'inputId': inputId});
}
