import 'dart:io';

import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/services/persistence_service.dart';

void main() {
  late Directory tempRoot;
  late PersistenceService service;

  setUp(() {
    tempRoot = Directory.systemTemp.createTempSync('wtracks_persistence_test_');
    service = PersistenceService(rootDirectoryResolver: () async => tempRoot);
  });

  tearDown(() {
    if (tempRoot.existsSync()) tempRoot.deleteSync(recursive: true);
  });

  Future<File> createFakeAudioFile(String name, {String content = 'fake-wav-bytes'}) async {
    final dir = Directory('${tempRoot.path}/import_cache')..createSync(recursive: true);
    final file = File('${dir.path}/$name');
    await file.writeAsString(content);
    return file;
  }

  group('PersistenceService.saveTrack', () {
    test('move os arquivos de áudio para audio/<trackId>/ e atualiza os paths', () async {
      final clickFile = await createFakeAudioFile('click.wav');
      final drumsFile = await createFakeAudioFile('bateria.wav');

      final track = Track(
        id: 'track_1',
        title: 'Música de Teste',
        channels: [
          ChannelInfo(label: 'Click', filePath: clickFile.path),
          ChannelInfo(label: 'Bateria', filePath: drumsFile.path),
        ],
      );

      final saved = await service.saveTrack(track);

      // Os arquivos de origem não existem mais (foram movidos, não copiados).
      expect(await clickFile.exists(), isFalse);
      expect(await drumsFile.exists(), isFalse);

      // Os novos paths apontam pro diretório permanente de áudio da track.
      final expectedAudioDir = '${tempRoot.path}/wtracks_data/audio/track_1';
      expect(saved.channels[0].filePath, '$expectedAudioDir/click.wav');
      expect(saved.channels[1].filePath, '$expectedAudioDir/bateria.wav');
      expect(await File(saved.channels[0].filePath).exists(), isTrue);
      expect(await File(saved.channels[1].filePath).exists(), isTrue);
    });

    test('grava o JSON refletindo os novos paths', () async {
      final clickFile = await createFakeAudioFile('click.wav');
      final track = Track(
        id: 'track_2',
        title: 'Outra Música',
        channels: [ChannelInfo(label: 'Click', filePath: clickFile.path)],
        clickSettings: const ClickSettings(bpm: 140, calibrated: true),
      );

      await service.saveTrack(track);

      final jsonFile = File('${tempRoot.path}/wtracks_data/tracks/track_2.json');
      expect(await jsonFile.exists(), isTrue);

      final loaded = await service.loadTrack('track_2');
      expect(loaded, isNotNull);
      expect(loaded!.title, 'Outra Música');
      expect(loaded.channels.single.filePath, contains('audio/track_2/click.wav'));
      expect(loaded.clickSettings.bpm, 140);
      expect(loaded.clickSettings.calibrated, isTrue);
    });

    test('colisão de nome entre canais diferentes prefixa com o índice do canal', () async {
      final fileA = await createFakeAudioFile('click.wav', content: 'A');
      // Simula dois arquivos de nome igual vindos de imports/diretórios
      // diferentes.
      final otherDir = Directory('${tempRoot.path}/import_cache_2')..createSync(recursive: true);
      final fileB = File('${otherDir.path}/click.wav');
      await fileB.writeAsString('B');

      final track = Track(
        id: 'track_3',
        title: 'Colisão',
        channels: [
          ChannelInfo(label: 'Canal A', filePath: fileA.path),
          ChannelInfo(label: 'Canal B', filePath: fileB.path),
        ],
      );

      final saved = await service.saveTrack(track);

      expect(saved.channels[0].filePath, isNot(equals(saved.channels[1].filePath)));
      expect(await File(saved.channels[0].filePath).readAsString(), 'A');
      expect(await File(saved.channels[1].filePath).readAsString(), 'B');
    });

    test('salvar a mesma track duas vezes não duplica nem falha (idempotente)', () async {
      final clickFile = await createFakeAudioFile('click.wav');
      final track = Track(
        id: 'track_4',
        title: 'Repetida',
        channels: [ChannelInfo(label: 'Click', filePath: clickFile.path)],
      );

      final firstSave = await service.saveTrack(track);
      final secondSave = await service.saveTrack(firstSave);

      expect(secondSave.channels.single.filePath, firstSave.channels.single.filePath);
      expect(await File(secondSave.channels.single.filePath).exists(), isTrue);
    });
  });

  group('PersistenceService.loadAllTracks', () {
    test('retorna lista vazia num diretório recém-criado', () async {
      final tracks = await service.loadAllTracks();
      expect(tracks, isEmpty);
    });

    test('pula arquivo JSON corrompido sem derrubar o carregamento dos demais', () async {
      final clickFile = await createFakeAudioFile('click.wav');
      final goodTrack = Track(
        id: 'track_good',
        title: 'Boa',
        channels: [ChannelInfo(label: 'Click', filePath: clickFile.path)],
      );
      await service.saveTrack(goodTrack);

      final tracksDir = Directory('${tempRoot.path}/wtracks_data/tracks');
      final corruptFile = File('${tracksDir.path}/track_bad.json');
      await corruptFile.writeAsString('{ isso não é json válido ][');

      final tracks = await service.loadAllTracks();

      expect(tracks.length, 1);
      expect(tracks.single.id, 'track_good');
    });
  });

  group('PersistenceService.deleteTrack', () {
    test('remove o JSON e o diretório de áudio da track', () async {
      final clickFile = await createFakeAudioFile('click.wav');
      final track = Track(
        id: 'track_5',
        title: 'Pra Deletar',
        channels: [ChannelInfo(label: 'Click', filePath: clickFile.path)],
      );
      final saved = await service.saveTrack(track);

      await service.deleteTrack('track_5');

      expect(await service.loadTrack('track_5'), isNull);
      expect(await File(saved.channels.single.filePath).exists(), isFalse);
      expect(await Directory('${tempRoot.path}/wtracks_data/audio/track_5').exists(), isFalse);
    });
  });

  group('PersistenceService waveform cache', () {
    test('salva e recarrega os picos (round-trip)', () async {
      final peaks = [0.0, 0.12, 0.87, 1.0, 0.5];

      await service.saveWaveformPeaks('track_wave_1', peaks);
      final loaded = await service.loadWaveformPeaks('track_wave_1');

      expect(loaded, peaks);
    });

    test('loadWaveformPeaks retorna null se não houver cache', () async {
      final loaded = await service.loadWaveformPeaks('track_sem_cache');
      expect(loaded, isNull);
    });

    test('loadWaveformPeaks retorna null (sem lançar) se o JSON estiver corrompido', () async {
      final dir = Directory('${tempRoot.path}/wtracks_data/waveforms')
        ..createSync(recursive: true);
      await File('${dir.path}/track_corrompida.json').writeAsString('{ não é json ][');

      final loaded = await service.loadWaveformPeaks('track_corrompida');
      expect(loaded, isNull);
    });

    test('deleteWaveformPeaks remove o arquivo de cache', () async {
      await service.saveWaveformPeaks('track_wave_2', [0.1, 0.2]);

      await service.deleteWaveformPeaks('track_wave_2');

      expect(await service.loadWaveformPeaks('track_wave_2'), isNull);
    });

    test('deleteTrack também remove o cache de waveform da track', () async {
      final clickFile = await createFakeAudioFile('click.wav');
      final track = Track(
        id: 'track_6',
        title: 'Com waveform',
        channels: [ChannelInfo(label: 'Click', filePath: clickFile.path)],
      );
      await service.saveTrack(track);
      await service.saveWaveformPeaks('track_6', [0.3, 0.4]);

      await service.deleteTrack('track_6');

      expect(await service.loadWaveformPeaks('track_6'), isNull);
    });
  });
}
