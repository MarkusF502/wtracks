import 'dart:io';
import 'package:flutter/foundation.dart' show debugPrint;
import 'package:path_provider/path_provider.dart';
import '../models/guide_settings.dart';
import 'safe_json.dart';

/// Guarda as preferências de guia (idioma, voz, contagem, pré-roll) do app todo.
class GuidePreferencesStore {
  final Future<Directory> Function() directoryResolver;
  GuidePreferencesStore({Future<Directory> Function()? directoryResolver})
      : directoryResolver = directoryResolver ?? getApplicationSupportDirectory;

  Future<File> _file() async {
    final dir = Directory('${(await directoryResolver()).path}/wtracks_data');
    await dir.create(recursive: true);
    return File('${dir.path}/guides.json');
  }

  /// O que deu errado na última leitura (ver [AppPreferencesStore.lastProblem]); null se nada.
  String? lastProblem;

  Future<GuideSettings> load() async {
    try {
      final read = await SafeJson.read<GuideSettings>(await _file(), (json) => GuideSettings.fromJson(json));
      lastProblem = read.problem;
      return read.value ?? const GuideSettings();
    } on Exception catch (e) {
      debugPrint('Não foi possível ler as preferências de guia: $e'); // pasta indisponível: o app segue com os padrões
      return const GuideSettings();
    }
  }

  Future<void> save(GuideSettings settings) async => SafeJson.write(await _file(), settings.toJson());
}
