import 'dart:convert';
import 'dart:io';
import 'package:path_provider/path_provider.dart';
import '../models/guide_settings.dart';

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

  Future<GuideSettings> load() async {
    try {
      final file = await _file();
      if (!await file.exists()) return const GuideSettings();
      return GuideSettings.fromJson(jsonDecode(await file.readAsString()));
    } on Exception {
      return const GuideSettings(); // corrupt file or storage unavailable: defaults
    }
  }

  Future<void> save(GuideSettings settings) async {
    final file = await _file();
    final temporary = File('${file.path}.part');
    await temporary.writeAsString(jsonEncode(settings.toJson()), flush: true);
    await temporary.rename(file.path);
  }
}
