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

  /// Pasta de clicks personalizados (Playback: "Custom Clicks Directory Path"); null = só os do pacote.
  String? customDirectory;
  static const customPrefix = 'custom:';
  static const _voices = ['accents', 'quarter', 'eighth', 'sixteenth'];
  static final _audio = RegExp(r'\.(wav|aif|aiff|flac)$', caseSensitive: false);

  /// Famílias completas (as quatro vozes) da pasta personalizada: `<Família>-<voz>.<ext>`.
  Map<String, Map<String, String>> customFamilies() {
    final dir = customDirectory;
    final result = <String, Map<String, String>>{};
    if (dir == null || !Directory(dir).existsSync()) return result;
    for (final entity in Directory(dir).listSync().whereType<File>()) {
      final name = entity.uri.pathSegments.last;
      if (!_audio.hasMatch(name)) continue;
      final base = name.substring(0, name.lastIndexOf('.'));
      final dash = base.lastIndexOf('-');
      if (dash <= 0) continue;
      final voice = base.substring(dash + 1);
      if (!_voices.contains(voice)) continue;
      (result[base.substring(0, dash)] ??= {})[voice] = entity.path;
    }
    result.removeWhere((_, voices) => voices.length != 4);
    return result;
  }

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
      ..sort()
      ..addAll([for (final f in customFamilies().keys.toList()..sort()) '$customPrefix$f']);
  }

  Future<List<String?>> prepare(String family) async {
    if (family == 'synthetic') return List.filled(4, null);
    if (family.startsWith(customPrefix)) {
      final voices = customFamilies()[family.substring(customPrefix.length)];
      if (voices == null) throw FormatException('Família personalizada indisponível: $family');
      return [for (final v in _voices) voices[v]];
    }
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
