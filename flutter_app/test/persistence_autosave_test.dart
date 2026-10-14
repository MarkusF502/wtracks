import 'dart:io';

import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/providers/setlist_provider.dart';
import 'package:flutter_app/services/diagnostics_log.dart';
import 'package:flutter_app/services/persistence_service.dart';
import 'harness/harness_support.dart';

/// Relato do Android: músicas importadas, edições e setlists sumiam ao reabrir o app. A importação só carregava a
/// música (o "Salvar" ficava escondido) e as falhas passavam caladas. Estes testes usam a gravação real em disco.
void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  setUp(mockBackgroundChannel);
  late Directory root;
  setUp(() async => root = await Directory.systemTemp.createTemp('autosave-'));
  tearDown(() => root.delete(recursive: true));

  ProviderContainer open() {
    final c = ProviderContainer(overrides: [
      engineProvider.overrideWithValue(FakeEngine()),
      persistenceServiceProvider.overrideWithValue(PersistenceService(rootDirectoryResolver: () async => root)),
    ]);
    c.read(trackLibraryProvider); // a tela de performance mantém a biblioteca (e o salvamento automático) ativa
    return c;
  }

  Future<void> settle(ProviderContainer c) async {
    for (var i = 0; i < 5; i++) {
      await c.read(trackLibraryProvider.notifier).autosaveIdle;
      await Future<void>.delayed(const Duration(milliseconds: 10));
    }
  }

  test('an imported song, its edits and a setlist survive reopening the app', () async {
    final cache = await Directory('${root.path}/cache').create();
    final wav = writeSineWav('${cache.path}/Click.wav', seconds: 0.2);
    final imported = Track(id: 'song', title: 'Importada', channels: [ChannelInfo(label: 'Click', filePath: wav.path)]);

    final first = open();
    expect(await first.read(currentTrackProvider.notifier).load(imported), true);
    await settle(first);
    first.read(currentTrackProvider.notifier).setMasterVolume(0.5);
    first.read(currentTrackProvider.notifier).renameCurrent('Renomeada');
    await settle(first);
    final setlist = await first.read(setlistLibraryProvider.notifier).createSetlist('Domingo');
    first.read(setlistEditorProvider.notifier).setLoadedSetlist(setlist);
    await first.read(setlistEditorProvider.notifier).addTracks([first.read(currentTrackProvider)!]);
    expect(first.read(diagnosticsProvider).where((e) => e.error), isEmpty);
    first.dispose();

    expect(wav.existsSync(), false, reason: 'o áudio sai do cache para a pasta permanente');
    final second = open();
    await settle(second);
    final library = second.read(trackLibraryProvider);
    expect(library.map((t) => t.title), ['Renomeada']);
    expect(library.single.masterVolume, 0.5);
    expect(File(library.single.channels.single.filePath).existsSync(), true);
    await second.read(setlistLibraryProvider.notifier).refresh();
    final setlists = second.read(setlistLibraryProvider);
    expect(setlists.single.name, 'Domingo');
    expect(setlists.single.tracks.single.id, 'song');
    second.dispose();
  });

  test('a save failure is reported, not swallowed', () async {
    final c = open();
    final missing = Track(id: 'gone', title: 'Sem áudio', channels: [ChannelInfo(label: 'Click', filePath: '${root.path}/nada.wav')]);
    c.read(currentTrackProvider.notifier).setLoadedTrack(missing);
    await settle(c);
    expect(c.read(diagnosticsProvider).where((e) => e.error).single.message, contains('Falha ao salvar "Sem áudio"'));
    expect(c.read(persistenceAlertProvider), contains('não encontrado'));
    c.dispose();
  });

  test('an unreadable song file is reported when the library loads', () async {
    await Directory('${root.path}/wtracks_data/tracks').create(recursive: true);
    File('${root.path}/wtracks_data/tracks/broken.json').writeAsStringSync('{ not json');
    final c = open();
    await settle(c);
    expect(c.read(diagnosticsProvider).single.message, contains('Música ilegível ignorada'));
    c.dispose();
  });
}
