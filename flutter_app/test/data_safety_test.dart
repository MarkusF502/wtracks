import 'dart:async';
import 'dart:convert';
import 'dart:io';

import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/file_import_service.dart';
import 'package:flutter_app/models/app_settings.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/services/app_preferences_store.dart';
import 'package:flutter_app/services/control_mapping_store.dart';
import 'package:flutter_app/services/persistence_service.dart';
import 'package:flutter_app/services/safe_json.dart';
import 'harness/harness_support.dart';

/// Fase B do plano de consolidação: importação e gravação que não perdem dados (WT-02, WT-04, WT-05, WT-14) e nomes de importação
/// que não se sobrescrevem (WT-03, parte Dart).
void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  mockBackgroundChannel();
  late Directory root, cache;
  setUp(() async {
    root = await Directory.systemTemp.createTemp('safety-');
    cache = await Directory('${root.path}/cache').create();
  });
  tearDown(() => root.delete(recursive: true));

  PersistenceService service() => PersistenceService(rootDirectoryResolver: () async => root);
  File wav(String name, {double seconds = 0.1, double freq = 440}) => writeSineWav('${cache.path}/$name', seconds: seconds, freq: freq);

  group('saving a song (WT-02)', () {
    test('audio is copied, the JSON is written last and only then are the sources deleted', () async {
      final a = wav('a.wav'), b = wav('b.wav', freq: 880);
      final sizes = [a.lengthSync(), b.lengthSync()];
      final saved = await service().saveTrack(Track(id: 's', title: 'S', channels: [
        ChannelInfo(label: 'A', filePath: a.path),
        ChannelInfo(label: 'B', filePath: b.path),
      ]));
      expect(saved.channels.map((c) => File(c.filePath).lengthSync()), sizes);
      expect(a.existsSync() || b.existsSync(), false);
      expect(File('${root.path}/wtracks_data/tracks/s.json').existsSync(), true);
      expect(Directory('${root.path}/wtracks_data/audio/s').listSync().whereType<File>().where((f) => f.path.endsWith('.part')), isEmpty);
    });

    test('a missing source fails the save without touching the other sources or leaving copies or a JSON', () async {
      final a = wav('a.wav');
      final before = a.readAsBytesSync();
      await expectLater(
        service().saveTrack(Track(id: 's', title: 'S', channels: [
          ChannelInfo(label: 'A', filePath: a.path),
          ChannelInfo(label: 'B', filePath: '${cache.path}/gone.wav'),
        ])),
        throwsA(isA<FileSystemException>()),
      );
      expect(a.readAsBytesSync(), before, reason: 'the original stays where it was');
      expect(File('${root.path}/wtracks_data/tracks/s.json').existsSync(), false);
      expect(Directory('${root.path}/wtracks_data/audio/s').listSync(), isEmpty, reason: 'no half-published copy');
    });

    test('a failure while publishing the JSON undoes the copies and keeps the originals', () async {
      final a = wav('a.wav');
      final tracksDir = Directory('${root.path}/wtracks_data/tracks')..createSync(recursive: true);
      Directory('${tracksDir.path}/s.json').createSync(); // the JSON target is a directory: the final rename fails
      await expectLater(service().saveTrack(Track(id: 's', title: 'S', channels: [ChannelInfo(label: 'A', filePath: a.path)])), throwsA(anything));
      expect(a.existsSync(), true);
      expect(Directory('${root.path}/wtracks_data/audio/s').listSync(), isEmpty);
    });

    test('files with the same name keep their own content, also against channels already in place', () async {
      final first = await Directory('${cache.path}/1').create(), second = await Directory('${cache.path}/2').create();
      final one = writeSineWav('${first.path}/click.wav', seconds: 0.1, freq: 440);
      final two = writeSineWav('${second.path}/click.wav', seconds: 0.2, freq: 880);
      final bytesOne = one.readAsBytesSync(), bytesTwo = two.readAsBytesSync();
      final svc = service();
      final saved = await svc.saveTrack(Track(id: 's', title: 'S', channels: [ChannelInfo(label: 'A', filePath: one.path)]));
      // a later import adds a second "click.wav" while the first is already in place
      final again = await svc.saveTrack(saved.copyWith(channels: [ChannelInfo(label: 'N', filePath: two.path), ...saved.channels]));
      expect(again.channels.map((c) => File(c.filePath).readAsBytesSync().length), [bytesTwo.length, bytesOne.length]);
      expect(again.channels[0].filePath, isNot(again.channels[1].filePath));
      expect(File(again.channels[1].filePath).readAsBytesSync(), bytesOne);
      expect(File(again.channels[0].filePath).readAsBytesSync(), bytesTwo);
    });

    test('leftover partial copies are cleaned when the library is read', () async {
      final svc = service();
      final saved = await svc.saveTrack(Track(id: 's', title: 'S', channels: [ChannelInfo(label: 'A', filePath: wav('a.wav').path)]));
      final partial = File('${File(saved.channels.single.filePath).parent.path}/b.wav.part')..writeAsStringSync('half');
      expect((await svc.loadAllTracks()).single.id, 's');
      expect(partial.existsSync(), false);
    });
  });

  group('reading songs (WT-05, WT-14)', () {
    test('an unreadable song file is restored from the previous copy (.bak) and reported', () async {
      final svc = service();
      final saved = await svc.saveTrack(Track(id: 's', title: 'Primeira', channels: [ChannelInfo(label: 'A', filePath: wav('a.wav').path)]));
      await svc.saveTrack(saved.copyWith(title: 'Segunda'));
      final json = File('${root.path}/wtracks_data/tracks/s.json');
      json.writeAsStringSync('{ truncated');
      final loaded = await svc.loadAllTracks();
      expect(loaded.single.title, 'Primeira', reason: 'the copy before the last save');
      expect(svc.lastRecoveries.keys.single, json.path);
    });

    test('a song from a newer format is neither opened nor changed', () async {
      final svc = service();
      final saved = await svc.saveTrack(Track(id: 's', title: 'S', channels: [ChannelInfo(label: 'A', filePath: wav('a.wav').path)]));
      final json = File('${root.path}/wtracks_data/tracks/s.json');
      final future = jsonDecode(json.readAsStringSync()) as Map<String, dynamic>
        ..['schemaVersion'] = Track.currentSchemaVersion + 1
        ..['somethingNew'] = {'x': 1};
      json.writeAsStringSync(jsonEncode(future));
      final bytes = json.readAsBytesSync();
      expect(await svc.loadAllTracks(), isEmpty);
      expect(svc.lastLoadFailures[json.path], contains('mais nova'));
      expect(await svc.loadTrack(saved.id), isNull);
      expect(json.readAsBytesSync(), bytes, reason: 'the unknown fields are still there');
      expect(() => Track.fromJson(future), throwsA(isA<UnsupportedSchemaException>()));
    });
  });

  group('preference files (WT-05)', () {
    test('rapid concurrent writes all land and leave a valid file with the last value', () async {
      final file = File('${root.path}/p.json');
      await Future.wait([for (var i = 0; i < 30; i++) SafeJson.write(file, {'n': i})]);
      expect(jsonDecode(file.readAsStringSync()), {'n': 29});
      expect(File('${file.path}.tmp').existsSync(), false);
    });

    test('corrupt file: the previous copy is used and the bad file is kept aside', () async {
      final file = File('${root.path}/p.json');
      await SafeJson.write(file, {'n': 1});
      await SafeJson.write(file, {'n': 2});
      file.writeAsStringSync('{ broken');
      final read = await SafeJson.read<int>(file, (json) => (json as Map)['n'] as int);
      expect(read.value, 1);
      expect(read.problem, contains('cópia anterior'));
      expect(File('${file.path}.corrupt').readAsStringSync(), '{ broken');
      expect(file.existsSync(), false, reason: 'a later write must not copy the bad file into .bak');
    });

    test('corrupt file and no usable copy: defaults, with the problem reported and the file kept', () async {
      final file = File('${root.path}/p.json')..writeAsStringSync('nope');
      final read = await SafeJson.read<int>(file, (json) => (json as Map)['n'] as int);
      expect(read.value, isNull);
      expect(read.problem, contains('valores padrão'));
      expect(File('${file.path}.corrupt').existsSync(), true);
      expect((await SafeJson.read<int>(File('${root.path}/absent.json'), (j) => 0)).problem, isNull);
    });

    test('the settings store reports a corrupt file instead of looking like a factory reset', () async {
      final store = AppPreferencesStore(directoryResolver: () async => root);
      await store.save(const AppSettings(faderDefault80: true));
      await store.save(const AppSettings(faderDefault80: true, stereoSplit: true));
      File('${root.path}/wtracks_data/settings.json').writeAsStringSync('###');
      final restored = await store.load();
      expect(restored.faderDefault80, true, reason: 'from the .bak: the save before the last one');
      expect(restored.stereoSplit, false);
      expect(store.lastProblem, contains('cópia anterior'));

      File('${root.path}/wtracks_data/settings.json').writeAsStringSync('###');
      File('${root.path}/wtracks_data/settings.json.bak').deleteSync();
      final reset = await store.load();
      expect(reset.faderDefault80, false);
      expect(store.lastProblem, contains('valores padrão'));
    });

    test('the control mappings store survives a corrupt file with the defaults and a message', () async {
      final store = ControlMappingStore(directoryResolver: () async => root);
      Directory('${root.path}/wtracks_data').createSync(recursive: true);
      File('${root.path}/wtracks_data/control_mappings.json').writeAsStringSync('[');
      final (mappings, input) = await store.load();
      expect(input, isNull);
      expect(mappings, isNotEmpty);
      expect(store.lastProblem, isNotNull);
    });
  });

  group('autosave while editing (WT-04)', () {
    test('an edit made while the save is in flight survives and is saved next; only the audio paths come from the result', () async {
      final persistence = _SlowPersistence();
      final c = ProviderContainer(overrides: [
        engineProvider.overrideWithValue(FakeEngine()),
        persistenceServiceProvider.overrideWithValue(persistence),
      ]);
      addTearDown(c.dispose);
      c.read(trackLibraryProvider);
      final notifier = c.read(currentTrackProvider.notifier);
      expect(await notifier.load(sampleTrack(id: 's', channels: 1)), true);
      for (var i = 0; i < 5; i++) {
        await c.read(trackLibraryProvider.notifier).autosaveIdle;
        await Future<void>.delayed(const Duration(milliseconds: 10));
      }
      persistence.saved.clear();
      persistence.gate = _Gate();

      notifier.setMasterVolume(0.4); // triggers an autosave that parks inside saveTrack
      await persistence.gate!.entered.future;
      notifier.setMasterVolume(0.9); // the newer edit, while the first save is still running
      persistence.gate!.release.complete();
      for (var i = 0; i < 10; i++) {
        await c.read(trackLibraryProvider.notifier).autosaveIdle;
        await Future<void>.delayed(const Duration(milliseconds: 10));
      }
      expect(c.read(currentTrackProvider)!.masterVolume, 0.9, reason: 'the stale snapshot must not come back');
      expect(c.read(currentTrackProvider)!.channels.single.filePath, startsWith('/permanent/'));
      expect(persistence.saved.map((t) => t.masterVolume), [0.4, 0.9], reason: 'the newer edit was saved right after');
    });
  });

  group('import names (WT-03)', () {
    test('the provider name never becomes a path', () {
      expect(safeImportName('Click.wav'), 'Click.wav');
      expect(safeImportName('../../etc/passwd'), 'passwd');
      expect(safeImportName(r'..\..\x\Guia.wav'), 'Guia.wav');
      expect(safeImportName('  ..hidden. '), 'hidden');
      expect(safeImportName('a\u0000b.wav'), 'ab.wav');
      expect(safeImportName('..'), startsWith('file_'));
      expect(safeImportName('x' * 300).length, 120);
    });
  });
}

class _Gate {
  final entered = Completer<void>(), release = Completer<void>();
}

/// Persistence that parks the first save inside saveTrack and moves the audio to a "permanent" place, like the real one.
class _SlowPersistence extends InMemoryPersistence {
  _Gate? gate;
  final saved = <Track>[];
  @override
  Future<Track> saveTrack(Track track) async {
    final gate = this.gate;
    if (gate != null && !gate.entered.isCompleted) {
      gate.entered.complete();
      await gate.release.future;
    }
    saved.add(track);
    final moved = track.copyWith(channels: [for (final c in track.channels) c.copyWith(filePath: '/permanent/${c.filePath.split('/').last}')]);
    tracks[track.id] = moved;
    return moved;
  }
}
