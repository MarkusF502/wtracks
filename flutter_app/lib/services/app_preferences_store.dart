import 'dart:convert';
import 'dart:io';
import 'package:path_provider/path_provider.dart';
import '../models/app_settings.dart';

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

  Future<AppSettings> load() async {
    try {
      final file = await _file();
      if (!await file.exists()) return const AppSettings();
      return AppSettings.fromJson(jsonDecode(await file.readAsString()));
    } on Exception {
      return const AppSettings();
    }
  }

  Future<void> save(AppSettings settings) async {
    final file = await _file();
    final temporary = File('${file.path}.part');
    await temporary.writeAsString(jsonEncode(settings.toJson()), flush: true);
    await temporary.rename(file.path);
  }
}
