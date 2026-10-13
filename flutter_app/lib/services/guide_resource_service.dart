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
  Future<List<Map<String, dynamic>>> resources() async {
    final manifest =
        jsonDecode(
              await bundle.loadString('assets/playback/guide/manifest.json'),
            )
            as Map<String, dynamic>;
    return (manifest['resources'] as List).cast<Map<String, dynamic>>();
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
