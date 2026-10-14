// Fase 0 do plano: o Android perdia músicas importadas, edições e setlists ao reabrir o app.
// Roda no emulador do CI (.github/workflows/android-tests.yml). Isola o SALVAMENTO do áudio: o motor é o FakeEngine,
// porque o JUCE pode nem abrir o dispositivo de áudio no emulador (isso é checado à parte em engine_init_test.dart).
// Importa os helpers do harness por caminho relativo (../test/harness/...), pois integration_test/ não tem pacote próprio.
import 'dart:io';

import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/providers/setlist_provider.dart';
import 'package:flutter_app/services/diagnostics_log.dart';
import 'package:flutter_app/services/persistence_service.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:integration_test/integration_test.dart';
import 'package:path_provider/path_provider.dart';

import '../test/harness/harness_support.dart';

void main() {
  IntegrationTestWidgetsFlutterBinding.ensureInitialized();

  // O serviço real, na pasta real do app (getApplicationSupportDirectory), como no aparelho do usuário.
  ProviderContainer open() {
    final c = ProviderContainer(overrides: [
      engineProvider.overrideWithValue(FakeEngine()),
      persistenceServiceProvider.overrideWithValue(PersistenceService()),
    ]);
    c.read(trackLibraryProvider);
    return c;
  }

  Future<void> settle(ProviderContainer c) async {
    for (var i = 0; i < 5; i++) {
      await c.read(trackLibraryProvider.notifier).autosaveIdle;
      await Future<void>.delayed(const Duration(milliseconds: 20));
    }
  }

  testWidgets('Android: música importada, edição e setlist sobrevivem a reabrir o app', (tester) async {
    final suffix = DateTime.now().microsecondsSinceEpoch;
    final songId = 'it-song-$suffix';
    final cache = await Directory('${(await getTemporaryDirectory()).path}/it-$suffix').create(recursive: true);
    final wav = writeSineWav('${cache.path}/Click.wav', seconds: 0.2);
    final imported = Track(id: songId, title: 'Importada $suffix', channels: [ChannelInfo(label: 'Click', filePath: wav.path)]);

    final first = open();
    addTearDown(() async {
      await PersistenceService().deleteTrack(songId);
      if (cache.existsSync()) cache.deleteSync(recursive: true);
    });
    expect(await first.read(currentTrackProvider.notifier).load(imported), true);
    await settle(first);
    first.read(currentTrackProvider.notifier).setMasterVolume(0.5);
    first.read(currentTrackProvider.notifier).renameCurrent('Renomeada $suffix');
    await settle(first);
    final setlist = await first.read(setlistLibraryProvider.notifier).createSetlist('Domingo $suffix');
    addTearDown(() => PersistenceService().deleteSetlist(setlist.id));
    first.read(setlistEditorProvider.notifier).setLoadedSetlist(setlist);
    await first.read(setlistEditorProvider.notifier).addTracks([first.read(currentTrackProvider)!]);
    final errors = first.read(diagnosticsProvider).where((e) => e.error).map((e) => e.message).toList();
    expect(errors, isEmpty, reason: errors.join('\n'));
    first.dispose();

    // "Reabrir o app": um container novo lê tudo do disco.
    expect(wav.existsSync(), false, reason: 'o áudio sai do cache para a pasta permanente');
    final second = open();
    await settle(second);
    final mine = second.read(trackLibraryProvider).where((t) => t.id == songId).toList();
    expect(mine.map((t) => t.title), ['Renomeada $suffix']);
    expect(mine.single.masterVolume, 0.5);
    final saved = File(mine.single.channels.single.filePath);
    expect(saved.existsSync(), true, reason: 'o áudio gravado precisa existir: ${saved.path}');
    expect(saved.path.contains(cache.path), false);
    await second.read(setlistLibraryProvider.notifier).refresh();
    final lists = second.read(setlistLibraryProvider).where((s) => s.id == setlist.id).toList();
    expect(lists.single.name, 'Domingo $suffix');
    expect(lists.single.tracks.map((t) => t.id), [songId]);
    second.dispose();
  });
}
