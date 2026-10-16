import 'dart:convert';
import 'dart:io';

import 'package:archive/archive_io.dart';
import 'package:crypto/crypto.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/app_settings.dart';
import 'package:flutter_app/models/multitracks_origin.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/services/app_preferences_store.dart';
import 'package:flutter_app/services/backup_service.dart';
import 'package:flutter_app/services/persistence_service.dart';
import 'harness/harness_support.dart';

/// Backup e restauração (Fase B): o backup é portátil, conferido por hash, e a restauração só troca a biblioteca depois de tudo conferir.
void main() {
  late Directory work, rootA, rootB;
  setUp(() async {
    work = await Directory.systemTemp.createTemp('backup-');
    rootA = await Directory('${work.path}/a').create();
    rootB = await Directory('${work.path}/b').create();
  });
  tearDown(() => work.delete(recursive: true));

  PersistenceService serviceFor(Directory root) => PersistenceService(rootDirectoryResolver: () async => root);

  /// Uma biblioteca com duas músicas (uma delas com dois canais), uma setlist e preferências.
  Future<(PersistenceService, List<Track>)> library(Directory root) async {
    final service = serviceFor(root);
    final cache = await Directory('${root.path}/cache').create();
    Future<Track> song(String id, List<String> labels, double freq) async => service.saveTrack(Track(id: id, title: 'Música $id', channels: [
          for (final label in labels) ChannelInfo(label: label, filePath: writeSineWav('${cache.path}/$id-$label.wav', seconds: 0.2, freq: freq + labels.indexOf(label)).path),
        ]));
    final one = await song('one', ['Click', 'Bateria'], 440);
    final two = await song('two', ['Click'], 880);
    await service.saveSetlist(Setlist(id: 'set', name: 'Domingo', tracks: [one, two]));
    final prefs = AppPreferencesStore(directoryResolver: () async => root);
    await prefs.save(const AppSettings(faderDefault80: true, customClicksDirectory: '/sdcard/MeusClicks'));
    // lixo que não deve entrar
    await service.saveWaveformPeaks('one', [0.1, 0.2]);
    File('${root.path}/wtracks_data/tracks/one.json.bak').writeAsStringSync('old');
    File('${root.path}/wtracks_data/audio/one/leftover.wav.part').writeAsStringSync('half');
    return (service, [one, two]);
  }

  test('backup → restore on a clean install brings back songs, audio, setlists and preferences with portable paths', () async {
    final (serviceA, tracks) = await library(rootA);
    final backup = File('${work.path}/wtracks.zip');
    final progress = <double>[];
    final summary = await BackupService(serviceA).create(backup, onProgress: progress.add);
    expect((summary.tracks, summary.setlists, summary.audioFiles), (2, 1, 3));
    expect(progress.last, closeTo(1.0, 1e-9));
    expect(backup.existsSync(), true);
    expect(File('${backup.path}.part').existsSync(), false);

    final archive = ZipDecoder().decodeBuffer(InputFileStream(backup.path));
    final names = archive.files.map((f) => f.name).toList();
    expect(names, contains('manifest.json'));
    expect(names.where((n) => n.startsWith('waveforms/') || n.endsWith('.bak') || n.endsWith('.part')), isEmpty);
    final trackJson = jsonDecode(utf8.decode(archive.files.firstWhere((f) => f.name == 'tracks/one.json').content as List<int>)) as Map<String, dynamic>;
    expect((trackJson['channels'] as List).first['filePath'], startsWith('audio/one/'), reason: 'relative to the data folder');
    final settingsJson = jsonDecode(utf8.decode(archive.files.firstWhere((f) => f.name == 'settings.json').content as List<int>)) as Map;
    expect(settingsJson.containsKey('customClicksDirectory'), false, reason: 'a folder that only exists on that device');
    expect(settingsJson['faderDefault80'], true);

    final serviceB = serviceFor(rootB);
    final previous = await BackupService(serviceB).restore(backup);
    expect(previous, isNull, reason: 'a clean install has nothing to keep aside');
    final restored = await serviceB.loadAllTracks();
    expect(restored.map((t) => t.id).toSet(), {'one', 'two'});
    for (final track in restored) {
      final original = tracks.firstWhere((t) => t.id == track.id);
      expect(track.title, original.title);
      expect(track.channels.length, original.channels.length);
      for (var i = 0; i < track.channels.length; i++) {
        expect(track.channels[i].filePath, startsWith('${rootB.path}/wtracks_data/audio/${track.id}/'));
        expect(File(track.channels[i].filePath).readAsBytesSync(), File(original.channels[i].filePath).readAsBytesSync());
      }
    }
    final setlist = (await serviceB.loadAllSetlists()).single;
    expect(setlist.tracks.map((t) => t.id), ['one', 'two']);
    expect(setlist.tracks.first.channels.first.filePath, startsWith(rootB.path));
    expect(File(setlist.tracks.first.channels.first.filePath).existsSync(), true);
    expect((await AppPreferencesStore(directoryResolver: () async => rootB).load()).faderDefault80, true);
  });

  test('MultiTracks songs go into the backup without their audio and come back pending a new download', () async {
    final (serviceA, _) = await library(rootA);
    final cache = Directory('${rootA.path}/cache');
    final origin = MultiTracksOrigin(
        contentId: 202, keyId: 3, contentType: 1, entitlementKind: MultiTracksEntitlementKind.weekly, lastValidatedAt: DateTime.utc(2026, 10, 16));
    final protected = await serviceA.saveTrack(Track(id: 'multitracks-202-3', title: 'Semanal', origin: origin, channels: [
      for (final label in ['Click', 'Voz']) ChannelInfo(label: label, filePath: writeSineWav('${cache.path}/mt-$label.wav', seconds: 0.2).path),
    ]));
    final backup = File('${work.path}/wtracks.zip');
    final summary = await BackupService(serviceA).create(backup);
    expect((summary.tracks, summary.audioFiles, summary.tracksWithoutAudio), (3, 3, 1), reason: 'only the 3 local audio files');

    final names = ZipDecoder().decodeBuffer(InputFileStream(backup.path)).files.map((f) => f.name).toList();
    expect(names, contains('tracks/multitracks-202-3.json'));
    expect(names.where((n) => n.startsWith('audio/multitracks-202-3/')), isEmpty, reason: 'protected audio never leaves the device');
    expect((await BackupService(serviceA).verify(backup)).tracksWithoutAudio, 1);

    final serviceB = serviceFor(rootB);
    await BackupService(serviceB).restore(backup);
    final restored = await serviceB.loadAllTracks();
    expect(restored.map((t) => t.id).toSet(), {'one', 'two', 'multitracks-202-3'});
    final song = restored.firstWhere((t) => t.id == protected.id);
    expect(song.origin, origin);
    expect(song.channels.map((c) => c.label), ['Click', 'Voz']);
    expect(song.channels.every((c) => c.filePath.startsWith('${rootB.path}/wtracks_data/audio/${song.id}/')), true);
    expect(song.channels.any((c) => File(c.filePath).existsSync()), false, reason: 'downloaded again after login');
    final local = restored.firstWhere((t) => t.id == 'one');
    expect(local.channels.every((c) => File(c.filePath).existsSync()), true);
  });

  test('restoring over an existing library keeps the old folder aside and replaces the library', () async {
    final (serviceA, _) = await library(rootA);
    final backup = File('${work.path}/wtracks.zip');
    await BackupService(serviceA).create(backup);
    final serviceB = serviceFor(rootB);
    final cache = await Directory('${rootB.path}/cache').create();
    await serviceB.saveTrack(Track(id: 'other', title: 'Outra', channels: [ChannelInfo(label: 'A', filePath: writeSineWav('${cache.path}/a.wav', seconds: 0.1).path)]));

    final previous = await BackupService(serviceB).restore(backup);
    expect(previous, isNotNull);
    expect(File('${previous!.path}/tracks/other.json').existsSync(), true, reason: 'the old library is still there to be recovered');
    expect((await serviceB.loadAllTracks()).map((t) => t.id).toSet(), {'one', 'two'});
  });

  test('a damaged backup is rejected and the current library is untouched', () async {
    final (serviceA, _) = await library(rootA);
    final backup = File('${work.path}/wtracks.zip');
    await BackupService(serviceA).create(backup);
    final bytes = backup.readAsBytesSync();
    // stored audio: flipping a byte inside the zip body changes content without breaking the structure
    final audioStart = utf8.decode(bytes, allowMalformed: true).indexOf('audio/one/');
    final damaged = [...bytes]..[audioStart + 200] ^= 0xff;
    final broken = File('${work.path}/broken.zip')..writeAsBytesSync(damaged);

    final service = BackupService(serviceFor(rootB));
    await expectLater(service.verify(broken), throwsA(isA<BackupException>()));
    final serviceB = serviceFor(rootB);
    final cache = await Directory('${rootB.path}/cache').create();
    await serviceB.saveTrack(Track(id: 'mine', title: 'Minha', channels: [ChannelInfo(label: 'A', filePath: writeSineWav('${cache.path}/a.wav', seconds: 0.1).path)]));
    await expectLater(BackupService(serviceB).restore(broken), throwsA(isA<BackupException>()));
    expect((await serviceB.loadAllTracks()).map((t) => t.id), ['mine']);
    expect(Directory('${rootB.path}/wtracks_data.restaurando').existsSync(), false);

    await expectLater(service.verify(File('${work.path}/not-a-zip.zip')..writeAsStringSync('hello')), throwsA(isA<BackupException>()));
    await expectLater(service.verify(File('${work.path}/missing.zip')), throwsA(isA<BackupException>()));
  });

  test('backups from a newer format or with paths outside the data folder are refused', () async {
    Future<File> craft(Map<String, dynamic> manifest, [Map<String, List<int>> files = const {}]) async {
      final path = '${work.path}/crafted-${manifest.hashCode}.zip';
      final encoder = ZipFileEncoder()..create(path);
      final bytes = utf8.encode(jsonEncode(manifest));
      encoder.addArchiveFile(ArchiveFile('manifest.json', bytes.length, bytes));
      for (final entry in files.entries) {
        encoder.addArchiveFile(ArchiveFile(entry.key, entry.value.length, entry.value));
      }
      await encoder.close();
      return File(path);
    }

    final service = BackupService(serviceFor(rootB));
    final newer = await craft({'format': 'wtracks-backup', 'version': 99, 'files': <dynamic>[]});
    await expectLater(service.verify(newer), throwsA(predicate((e) => e is BackupException && e.message.contains('mais nova'))));
    final newerSongs = await craft({'format': 'wtracks-backup', 'version': 1, 'trackSchemaVersion': Track.currentSchemaVersion + 1, 'files': <dynamic>[]});
    await expectLater(service.verify(newerSongs), throwsA(predicate((e) => e is BackupException && e.message.contains('formato mais novo'))));
    final content = utf8.encode('x');
    final slip = await craft({
      'format': 'wtracks-backup',
      'version': 1,
      'files': [{'path': '../escape.txt', 'size': 1, 'sha256': sha256.convert(content).toString()}],
    }, {'../escape.txt': content});
    await expectLater(service.verify(slip), throwsA(predicate((e) => e is BackupException && e.message.contains('Caminho inválido'))));
    final wrongFormat = await craft({'format': 'something-else', 'version': 1, 'files': <dynamic>[]});
    await expectLater(service.verify(wrongFormat), throwsA(isA<BackupException>()));
  });
}
