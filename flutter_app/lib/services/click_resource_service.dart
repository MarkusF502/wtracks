import 'dart:convert';
import 'dart:io';
import 'package:flutter/services.dart';
import 'package:flutter/foundation.dart';
import 'package:path_provider/path_provider.dart';

/// Materializes bundled PCM outside the audio callback. Native owns decoded buffers.
class ClickResourceService {
  final AssetBundle bundle;
  final Future<Directory> Function() directoryResolver;
  ClickResourceService({
    AssetBundle? bundle,
    Future<Directory> Function()? directoryResolver,
  }) : bundle = bundle ?? rootBundle,
       directoryResolver = directoryResolver ?? getApplicationSupportDirectory;

  Future<List<String>> families() async {
    final manifest =
        jsonDecode(
              await bundle.loadString('assets/playback/click/manifest.json'),
            )
            as Map<String, dynamic>;
    return (manifest['resources'] as List)
        .map((r) => r['family'] as String)
        .toSet()
        .toList()
      ..sort();
  }

  Future<List<String?>> prepare(String family) async {
    if (family == 'synthetic') return List.filled(4, null);
    final manifest =
        jsonDecode(
              await bundle.loadString('assets/playback/click/manifest.json'),
            )
            as Map<String, dynamic>;
    final resources = (manifest['resources'] as List)
        .where((r) => r['family'] == family)
        .toList();
    const voices = ['accents', 'quarter', 'eighth', 'sixteenth'];
    if (resources.length != 4 ||
        voices.any(
          (v) => resources.where((r) => r['voice'] == v).length != 1,
        )) {
      throw FormatException('Família de click incompleta: $family');
    }
    final directory = Directory(
      '${(await directoryResolver()).path}/click-resources',
    );
    await directory.create(recursive: true);
    final result = <String?>[];
    for (final voice in voices) {
      final resource = resources.singleWhere((r) => r['voice'] == voice);
      final data = await bundle.load(resource['asset'] as String);
      // Content identity changes the filename; old files cannot silently replace new PCM.
      final file = File('${directory.path}/${resource['sha256']}.wav');
      final bytes = data.buffer.asUint8List(data.offsetInBytes, data.lengthInBytes);
      if (!await file.exists() || !listEquals(await file.readAsBytes(), bytes)) {
        await file.writeAsBytes(bytes, flush: true);
      }
      result.add(file.path);
    }
    return result;
  }
}
