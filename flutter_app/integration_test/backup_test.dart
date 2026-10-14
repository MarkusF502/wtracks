// Backup e restauração no sistema de arquivos real do Android, numa pasta de dados isolada (não mexe na biblioteca do app).
import 'dart:io';

import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/services/backup_service.dart';
import 'package:flutter_app/services/persistence_service.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:integration_test/integration_test.dart';
import 'package:path_provider/path_provider.dart';

import '../test/harness/harness_support.dart';

void main() {
  IntegrationTestWidgetsFlutterBinding.ensureInitialized();

  testWidgets('Android: backup conferido e restauração numa instalação limpa', (tester) async {
    final base = await Directory('${(await getTemporaryDirectory()).path}/backup-it-${DateTime.now().microsecondsSinceEpoch}').create(recursive: true);
    addTearDown(() => base.deleteSync(recursive: true));
    final rootA = await Directory('${base.path}/a').create();
    final rootB = await Directory('${base.path}/b').create();
    final a = PersistenceService(rootDirectoryResolver: () async => rootA);
    final cache = await Directory('${base.path}/cache').create();
    final saved = await a.saveTrack(Track(id: 'it', title: 'Música', channels: [
      ChannelInfo(label: 'Click', filePath: writeSineWav('${cache.path}/click.wav', seconds: 1).path),
      ChannelInfo(label: 'Bateria', filePath: writeSineWav('${cache.path}/bateria.wav', seconds: 1, freq: 220).path),
    ]));
    final zip = File('${base.path}/backup.zip');
    final summary = await BackupService(a).create(zip);
    expect((summary.tracks, summary.audioFiles), (1, 2));

    final b = PersistenceService(rootDirectoryResolver: () async => rootB);
    expect(await BackupService(b).restore(zip), isNull);
    final restored = (await b.loadAllTracks()).single;
    expect(restored.channels.map((c) => c.filePath), everyElement(startsWith('${rootB.path}/wtracks_data/audio/it/')));
    for (var i = 0; i < 2; i++) {
      expect(File(restored.channels[i].filePath).readAsBytesSync(), File(saved.channels[i].filePath).readAsBytesSync());
    }
  });
}
