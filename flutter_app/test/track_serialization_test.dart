import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/track.dart';

void main() {
  group('ChannelInfo (de)serialização', () {
    test('round-trip preserva todos os campos', () {
      const original = ChannelInfo(
        label: 'Bateria',
        filePath: '/data/audio/bateria.wav',
        volume: 0.75,
        muted: true,
        soloed: false,
      );

      final restored = ChannelInfo.fromJson(original.toJson());

      expect(restored.label, original.label);
      expect(restored.filePath, original.filePath);
      expect(restored.volume, original.volume);
      expect(restored.muted, original.muted);
      expect(restored.soloed, original.soloed);
    });
  });

  group('ClickSettings (de)serialização', () {
    test('round-trip preserva todos os campos', () {
      const original = ClickSettings(
        bpm: 128.5,
        beatOffsetSeconds: 0.42,
        timeSignatureNumerator: 3,
        calibrated: true,
      );

      final restored = ClickSettings.fromJson(original.toJson());

      expect(restored.bpm, original.bpm);
      expect(restored.beatOffsetSeconds, original.beatOffsetSeconds);
      expect(restored.timeSignatureNumerator, original.timeSignatureNumerator);
      expect(restored.calibrated, original.calibrated);
    });

    test('fromJson aplica defaults quando campos faltam', () {
      final restored = ClickSettings.fromJson(const {});

      expect(restored.bpm, 120.0);
      expect(restored.beatOffsetSeconds, 0.0);
      expect(restored.timeSignatureNumerator, 4);
      expect(restored.calibrated, false);
    });
  });

  group('Track (de)serialização', () {
    test('round-trip preserva id, título, canais, clickSettings, artist e key', () {
      const original = Track(
        id: 'track_123',
        title: 'Música de Teste',
        channels: [
          ChannelInfo(label: 'Click', filePath: '/audio/click.wav'),
          ChannelInfo(label: 'Guia', filePath: '/audio/guia.wav', volume: 0.5),
        ],
        clickSettings: ClickSettings(bpm: 96, calibrated: true),
        artist: 'Banda X',
        key: 'E',
      );

      final restored = Track.fromJson(original.toJson());

      expect(restored.id, original.id);
      expect(restored.title, original.title);
      expect(restored.channels.length, original.channels.length);
      for (var i = 0; i < original.channels.length; i++) {
        expect(restored.channels[i].label, original.channels[i].label);
        expect(restored.channels[i].filePath, original.channels[i].filePath);
        expect(restored.channels[i].volume, original.channels[i].volume);
      }
      expect(restored.clickSettings.bpm, original.clickSettings.bpm);
      expect(restored.clickSettings.calibrated, original.clickSettings.calibrated);
      expect(restored.artist, original.artist);
      expect(restored.key, original.key);
    });

    test('fromJson usa ClickSettings padrão quando ausente no JSON', () {
      final json = {
        'id': 'track_x',
        'title': 'Sem click settings',
        'channels': <Map<String, dynamic>>[],
      };

      final restored = Track.fromJson(json);

      expect(restored.clickSettings.bpm, 120.0);
    });

    test('fromJson aceita JSON sem as chaves artist/key (tracks salvas antes desta mudança)', () {
      final json = {
        'id': 'track_old',
        'title': 'Música Antiga',
        'channels': <Map<String, dynamic>>[],
        'clickSettings': const ClickSettings().toJson(),
      };

      final restored = Track.fromJson(json);

      expect(restored.artist, isNull);
      expect(restored.key, isNull);
    });
  });

  group('Setlist serialização', () {
    test('toJson grava trackIds em vez de embutir as Tracks inteiras', () {
      const trackA = Track(id: 'a', title: 'A', channels: []);
      const trackB = Track(id: 'b', title: 'B', channels: []);
      const setlist = Setlist(id: 'sl1', name: 'Culto de Domingo', tracks: [trackA, trackB]);

      final json = setlist.toJson();

      expect(json['id'], 'sl1');
      expect(json['name'], 'Culto de Domingo');
      expect(json['trackIds'], ['a', 'b']);
      expect(json.containsKey('tracks'), isFalse);
    });

    test('helpers estáticos leem id/name/trackIds de volta do JSON', () {
      final json = {
        'id': 'sl2',
        'name': 'Ensaio',
        'trackIds': ['x', 'y', 'z'],
      };

      expect(Setlist.idFromJson(json), 'sl2');
      expect(Setlist.nameFromJson(json), 'Ensaio');
      expect(Setlist.trackIdsFromJson(json), ['x', 'y', 'z']);
    });
  });

  group('Setlist.withTrackAdded/withTrackRemoved/withTracksReordered', () {
    const trackA = Track(id: 'a', title: 'A', channels: []);
    const trackB = Track(id: 'b', title: 'B', channels: []);
    const trackC = Track(id: 'c', title: 'C', channels: []);

    test('withTrackAdded adiciona no final', () {
      const setlist = Setlist(id: 'sl', name: 'S', tracks: [trackA]);
      final result = setlist.withTrackAdded(trackB);
      expect(result.tracks.map((t) => t.id), ['a', 'b']);
    });

    test('withTrackAdded é no-op se já contém o id', () {
      const setlist = Setlist(id: 'sl', name: 'S', tracks: [trackA, trackB]);
      final result = setlist.withTrackAdded(trackB);
      expect(result.tracks.map((t) => t.id), ['a', 'b']);
    });

    test('withTrackRemoved remove a track', () {
      const setlist = Setlist(id: 'sl', name: 'S', tracks: [trackA, trackB]);
      final result = setlist.withTrackRemoved('a');
      expect(result.tracks.map((t) => t.id), ['b']);
    });

    test('withTrackRemoved é no-op se o id não existe', () {
      const setlist = Setlist(id: 'sl', name: 'S', tracks: [trackA, trackB]);
      final result = setlist.withTrackRemoved('zzz');
      expect(result.tracks.map((t) => t.id), ['a', 'b']);
    });

    test('withTracksReordered move do índice 0 pro final', () {
      const setlist = Setlist(id: 'sl', name: 'S', tracks: [trackA, trackB, trackC]);
      final result = setlist.withTracksReordered(0, 3);
      expect(result.tracks.map((t) => t.id), ['b', 'c', 'a']);
    });

    test('withTracksReordered move do final pro índice 0', () {
      const setlist = Setlist(id: 'sl', name: 'S', tracks: [trackA, trackB, trackC]);
      final result = setlist.withTracksReordered(2, 0);
      expect(result.tracks.map((t) => t.id), ['c', 'a', 'b']);
    });
  });
}
