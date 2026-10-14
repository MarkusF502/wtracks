import 'dart:io';
import 'package:flutter/foundation.dart' show debugPrint;
import 'package:path_provider/path_provider.dart';
import '../models/app_settings.dart';
import 'safe_json.dart';

/// Guarda as preferências gerais do app.
class AppPreferencesStore {
  final Future<Directory> Function() directoryResolver;
  AppPreferencesStore({Future<Directory> Function()? directoryResolver})
      : directoryResolver = directoryResolver ?? getApplicationSupportDirectory;

  Future<File> _file() async {
    final dir = Directory('${(await directoryResolver()).path}/wtracks_data');
    await dir.create(recursive: true);
    return File('${dir.path}/settings.json');
  }

  /// O que deu errado na última leitura (arquivo ilegível, recuperado do .bak...), para o diagnóstico; null se nada.
  String? lastProblem;

  Future<AppSettings> load() async {
    try {
      final read = await SafeJson.read<AppSettings>(await _file(), (json) => AppSettings.fromJson(json));
      lastProblem = read.problem;
      return read.value ?? const AppSettings();
    } on Exception catch (e) {
      debugPrint('Não foi possível ler as preferências: $e'); // pasta indisponível: o app segue com os padrões
      return const AppSettings();
    }
  }

  Future<void> save(AppSettings settings) async => SafeJson.write(await _file(), settings.toJson());
}
