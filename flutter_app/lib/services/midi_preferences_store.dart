import 'dart:convert';
import 'dart:io';
import 'package:path_provider/path_provider.dart';

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

  Future<String?> loadOutputId() async {
    try {
      final file = await _file();
      if (!await file.exists()) return null;
      final json = jsonDecode(await file.readAsString());
      final id = json is Map ? json['outputId'] : null;
      return id is String && id.isNotEmpty ? id : null;
    } on Exception {
      return null; // corrupt file or storage unavailable: behave as if nothing was saved
    }
  }

  Future<void> saveOutputId(String? id) async {
    final file = await _file();
    final temporary = File('${file.path}.part');
    await temporary.writeAsString(jsonEncode({'outputId': id}), flush: true);
    await temporary.rename(file.path);
  }
}
