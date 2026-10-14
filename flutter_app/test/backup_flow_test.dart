import 'dart:io';

import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/providers/backup_provider.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/screens/backup_screen.dart';
import 'package:flutter_app/services/backup_files.dart';
import 'package:flutter_app/services/diagnostics_log.dart';
import 'package:flutter_app/services/persistence_service.dart';
import 'harness/harness_support.dart';

class _FakeFiles implements BackupFiles {
  File? saved;
  bool cancelSave = false;
  File? toPick;
  @override
  Future<bool> saveBackup(File source, String suggestedName) async {
    if (cancelSave) return false;
    saved = await source.copy('${source.parent.path}/saved-$suggestedName');
    return true;
  }

  @override
  Future<File?> pickBackup() async => toPick;
}

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  mockBackgroundChannel();
  late Directory work;
  setUp(() async => work = await Directory.systemTemp.createTemp('backup-flow-'));
  tearDown(() => work.delete(recursive: true));

  ProviderContainer open(String name, _FakeFiles files) {
    final root = Directory('${work.path}/$name')..createSync(recursive: true);
    final c = ProviderContainer(overrides: [
      engineProvider.overrideWithValue(FakeEngine()),
      persistenceServiceProvider.overrideWithValue(PersistenceService(rootDirectoryResolver: () async => root)),
      backupFilesProvider.overrideWithValue(files),
      backupWorkDirectoryProvider.overrideWithValue(() async => Directory('${work.path}/tmp')..createSync(recursive: true)),
    ]);
    addTearDown(c.dispose);
    return c;
  }

  Future<void> addSong(ProviderContainer c, String id) async {
    final cache = Directory('${work.path}/cache')..createSync(recursive: true);
    await c.read(persistenceServiceProvider).saveTrack(
        Track(id: id, title: 'Música $id', channels: [ChannelInfo(label: 'A', filePath: writeSineWav('${cache.path}/$id.wav', seconds: 0.1).path)]));
  }

  test('create: builds, verifies, hands the file to the chosen place and cleans the work copy', () async {
    final files = _FakeFiles();
    final c = open('a', files);
    await addSong(c, 'one');
    await c.read(backupProvider.notifier).create();
    final state = c.read(backupProvider);
    expect(state.error, false, reason: state.message);
    expect(state.message, contains('1 música'));
    expect(files.saved, isNotNull);
    expect(await c.read(backupServiceProvider).verify(files.saved!), isNotNull);
    expect(Directory('${work.path}/tmp').listSync().whereType<File>().where((f) => !f.path.contains('saved-')), isEmpty);

    files.cancelSave = true;
    await c.read(backupProvider.notifier).create();
    expect(c.read(backupProvider).message, contains('cancelado'));
    expect(c.read(backupProvider).error, false);
  });

  test('restore: choose verifies and waits for the confirmation; confirming replaces the library and refreshes it', () async {
    final files = _FakeFiles();
    final a = open('a', files);
    await addSong(a, 'one');
    await a.read(backupProvider.notifier).create();

    final filesB = _FakeFiles()..toPick = files.saved;
    final b = open('b', filesB);
    await addSong(b, 'mine');
    await b.read(trackLibraryProvider.notifier).refresh();
    expect(b.read(trackLibraryProvider).map((t) => t.id), ['mine']);

    await b.read(backupProvider.notifier).choose();
    expect(b.read(backupProvider).pendingSummary!.tracks, 1);
    expect(b.read(backupProvider).message, isNull);
    await b.read(backupProvider.notifier).confirmRestore();
    final state = b.read(backupProvider);
    expect(state.error, false, reason: state.message);
    expect(state.message, contains('Backup restaurado'));
    expect(state.message, contains('anterior foi mantida'));
    expect(b.read(trackLibraryProvider).map((t) => t.id), ['one']);
  });

  test('a bad file is reported in the screen and in the diagnostics, and changes nothing', () async {
    final bad = File('${work.path}/bad.zip')..writeAsStringSync('this is not a backup');
    final files = _FakeFiles()..toPick = bad;
    final c = open('b', files);
    await addSong(c, 'mine');
    await c.read(backupProvider.notifier).choose();
    expect(c.read(backupProvider).error, true);
    expect(c.read(backupProvider).pendingSummary, isNull);
    expect(c.read(diagnosticsProvider).where((e) => e.error), isNotEmpty);
    expect((await c.read(persistenceServiceProvider).loadAllTracks()).map((t) => t.id), ['mine']);

    files.toPick = null; // the user closes the picker
    await c.read(backupProvider.notifier).choose();
    expect(c.read(backupProvider).message, isNull);
  });

  testWidgets('the screen asks before replacing the library', (tester) async {
    final files = _FakeFiles();
    final a = open('a', files);
    await tester.runAsync(() async {
      await addSong(a, 'one');
      await a.read(backupProvider.notifier).create();
    });
    final filesB = _FakeFiles()..toPick = files.saved;
    final b = open('b', filesB);
    await tester.pumpWidget(UncontrolledProviderScope(container: b, child: const MaterialApp(home: BackupScreen())));
    await tester.tap(find.byKey(const Key('backup-restore')));
    for (var i = 0; i < 60 && find.text('Restaurar este backup?').evaluate().isEmpty; i++) {
      await tester.runAsync(() => Future<void>.delayed(const Duration(milliseconds: 50)));
      await tester.pump(const Duration(milliseconds: 50));
    }
    expect(find.text('Restaurar este backup?'), findsOneWidget);
    expect(find.textContaining('1 música'), findsOneWidget);
    await tester.tap(find.byKey(const Key('restore-cancel')));
    await tester.pump(const Duration(milliseconds: 400));
    expect(b.read(backupProvider).pendingSummary, isNull);
  });
}
