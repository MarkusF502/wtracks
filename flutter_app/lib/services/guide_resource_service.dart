import 'dart:convert';
import 'dart:io';
import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';
import 'package:path_provider/path_provider.dart';

class GuideResourceService {
  final AssetBundle bundle;
  final Future<Directory> Function() directoryResolver;
  GuideResourceService({
    AssetBundle? bundle,
    Future<Directory> Function()? directoryResolver,
  }) : bundle = bundle ?? rootBundle,
       directoryResolver = directoryResolver ?? getApplicationSupportDirectory;
  /// Pasta de guias personalizadas (Playback: "Custom Guides Directory Path"): arquivos com o nome dos recursos do pacote
  /// (`guidecue-{count,section}-<idioma>-<gênero>-<nome>.wav`) somam ao catálogo e têm precedência sobre ele.
  String? customDirectory;
  static final _audio = RegExp(r'\.(wav|aif|aiff|flac)$', caseSensitive: false);

  Map<String, String> customResources() {
    final dir = customDirectory;
    if (dir == null || !Directory(dir).existsSync()) return const {};
    return {
      for (final f in Directory(dir).listSync().whereType<File>())
        if (_audio.hasMatch(f.uri.pathSegments.last) && f.uri.pathSegments.last.startsWith('guidecue-'))
          f.uri.pathSegments.last.substring(0, f.uri.pathSegments.last.lastIndexOf('.')): f.path,
    };
  }

  Future<List<Map<String, dynamic>>> resources() async {
    final manifest =
        jsonDecode(
              await bundle.loadString('assets/playback/guide/manifest.json'),
            )
            as Map<String, dynamic>;
    final bundled = (manifest['resources'] as List).cast<Map<String, dynamic>>();
    final custom = customResources();
    if (custom.isEmpty) return bundled;
    return [
      for (final r in bundled) if (!custom.containsKey(r['name'])) r,
      for (final e in custom.entries) {'name': e.key, 'label': e.key, 'path': e.value, 'custom': true},
    ];
  }

  Future<List<String>> prepare(List<String> names) async {
    if (names.isEmpty) return [];
    final catalog = await resources();
    final prepared = <String, String>{};
    final directory = Directory(
      '${(await directoryResolver()).path}/guide-resources',
    );
    await directory.create(recursive: true);
    for (final name in names.toSet()) {
      final resource = catalog.where((r) => r['name'] == name).single;
      if (resource['path'] is String) {  // custom file: used in place
        prepared[name] = resource['path'] as String;
        continue;
      }
      final data = await bundle.load(resource['asset'] as String);
      final bytes = data.buffer.asUint8List(
        data.offsetInBytes,
        data.lengthInBytes,
      );
      final file = File('${directory.path}/${resource['sha256']}.wav');
      if (!await file.exists() || !listEquals(await file.readAsBytes(), bytes)) {
        await file.writeAsBytes(bytes, flush: true);
      }
      prepared[name] = file.path;
    }
    return names.map((name) => prepared[name]!).toList();
  }
}
