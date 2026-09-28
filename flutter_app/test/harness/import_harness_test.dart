import 'dart:io';

import 'package:file_selector_platform_interface/file_selector_platform_interface.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/file_import_service.dart';
import 'package:path_provider_platform_interface/path_provider_platform_interface.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class _FakeFileSelector extends FileSelectorPlatform with MockPlatformInterfaceMixin {
  List<XFile> next = [];

  @override
  Future<List<XFile>> openFiles({
    List<XTypeGroup>? acceptedTypeGroups,
    String? initialDirectory,
    String? confirmButtonText,
  }) async =>
      next;
}

class _FakePathProvider extends PathProviderPlatform with MockPlatformInterfaceMixin {
  final String tmp;
  _FakePathProvider(this.tmp);

  @override
  Future<String?> getTemporaryPath() async => tmp;
}

void main() {
  late Directory root;
  late _FakeFileSelector picker;

  setUp(() {
    root = Directory.systemTemp.createTempSync('wtracks_import_harness_');
    picker = _FakeFileSelector();
    FileSelectorPlatform.instance = picker;
    PathProviderPlatform.instance = _FakePathProvider('${root.path}/cache');
  });
  tearDown(() => root.deleteSync(recursive: true));

  File source(String dir, String name, String content) {
    final f = File('${root.path}/$dir/$name')..createSync(recursive: true);
    return f..writeAsStringSync(content);
  }

  test('importa e devolve caminhos locais no cache de import', () async {
    picker.next = [XFile(source('pen', 'Guia.wav', 'guia').path)];

    final paths = await FileImportService().pickAndImportChannelFiles();

    expect(paths, hasLength(1));
    expect(File(paths.single).readAsStringSync(), 'guia');
  });

  test('[D4] importar 2ª música com arquivos de mesmo nome não sobrescreve a 1ª (ainda não salva)',
      () async {
    // Multitracks exportados costumam ter os mesmos nomes (Click.wav, Guia.wav...).
    picker.next = [XFile(source('musicaA', 'Click.wav', 'click da musica A').path)];
    final first = await FileImportService().pickAndImportChannelFiles();

    picker.next = [XFile(source('musicaB', 'Click.wav', 'click da musica B').path)];
    final second = await FileImportService().pickAndImportChannelFiles();

    expect(second.single, isNot(first.single),
        reason: 'as duas importações foram gravadas no MESMO caminho: ${first.single}');
    expect(File(first.single).readAsStringSync(), 'click da musica A',
        reason: 'a música A (carregada, ainda não salva) teve o áudio trocado pelo da B');
  });
}
