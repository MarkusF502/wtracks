import 'dart:convert';
import 'dart:io';
import 'package:path_provider/path_provider.dart';
import '../models/control_mapping.dart';

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
  Future<(List<ControlMapping>, String?)> load() async {
    try {
      final file = await _file();
      if (!await file.exists()) return (defaultKeyboardMappings, null);
      final json = jsonDecode(await file.readAsString());
      if (json is! Map) return (defaultKeyboardMappings, null);
      final list = json['mappings'] is List ? json['mappings'] as List : const [];
      final input = json['inputId'];
      return (<ControlMapping>[for (final m in list) ?ControlMapping.fromJson(m)], input is String && input.isNotEmpty ? input : null);
    } on Exception {
      return (defaultKeyboardMappings, null);
    }
  }

  Future<void> save(List<ControlMapping> mappings, String? inputId) async {
    final file = await _file();
    final temporary = File('${file.path}.part');
    await temporary.writeAsString(jsonEncode({'mappings': mappings.map((m) => m.toJson()).toList(), 'inputId': inputId}), flush: true);
    await temporary.rename(file.path);
  }
}
