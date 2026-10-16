import 'dart:convert';
import 'dart:io';

import 'package:flutter_app/models/fixed_clicks.dart';
import 'package:flutter_app/models/multitracks_origin.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/services/multitracks_structure.dart';
import 'package:flutter_test/flutter_test.dart';

import 'harness/harness_support.dart';

/// Estrutura musical da MultiTracks (seções, andamento, compasso e clicks) a partir da resposta de content/download.
void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  mockBackgroundChannel();
  Map<String, Object?> fixture() =>
      jsonDecode(File('test/fixtures/multitracks/content_structure.json').readAsStringSync()) as Map<String, Object?>;

  test('timeCode is MM:SS:mmm (a trailing space is tolerated); anything else is refused', () {
    expect(MultiTracksStructure.parseTimeCode('04:08:823'), closeTo(248.823, 1e-9));
    expect(MultiTracksStructure.parseTimeCode('04:00:000 '), 240.0);
    for (final bad in ['4:08.823', '00:61:000', '', '1:2:3', null, 12.0]) {
      expect(MultiTracksStructure.parseTimeCode(bad), isNull, reason: '$bad');
    }
  });

  test('tempo map: positions in beats become seconds by the stepwise tempo, cross-checked against timeCode', () {
    final s = MultiTracksStructure.parse(fixture());
    expect(s.warnings, isEmpty);
    expect((s.click.bpm, s.click.timeSignatureNumerator, s.click.timeSignatureDenominator, s.click.beatOffsetSeconds), (120.0, 4, 4, 0.0));
    // (início em s arredondado a 1 µs, bpm, compasso): o par em 16 tempos vale pelo último; 17,5 tempos cai no meio de um tempo.
    expect([for (final c in s.tempoChanges) ((c.startSeconds * 1e6).round() / 1e6, c.bpm, c.numerator, c.denominator)], [
      (4.0, 120.0, 3, 4),
      (5.5, 120.0, 4, 4),
      (8.0, 60.0, 4, 4),
      (9.5, 90.0, 4, 4),
    ]);
  });

  test('sections: start from timeCode, end at the next one (last at duration), names from the catalog, guide stem silences the spoken guide', () {
    final s = MultiTracksStructure.parse(fixture(), hasGuideStem: true);
    expect([for (final x in s.sections) (x.id, x.name, x.startSeconds, x.endSeconds)], [
      ('mt-501', 'Contagem', 0.0, 2.0),
      ('mt-502', 'Introdução', 2.0, 8.0),
      ('mt-503', 'Refrão', 8.0, 15.0),
      ('mt-504', 'Seção', 15.0, 20.0),
    ]);
    expect(s.sections.every((x) => !x.playGuideCue), true);
    expect(MultiTracksStructure.parse(fixture()).sections.every((x) => x.playGuideCue), true);
  });

  test('clicks: sentinels dropped, one voice per beat, sorted events', () {
    final clicks = MultiTracksStructure.parse(fixture()).fixedClicks!;
    expect(clicks.accents, [0.0001, 2.0001, 4.0001]);
    expect(clicks.quarters.last, 2.0);
    expect(clicks.events(), [
      (0.0001, 0), (0.125, 3), (0.25, 2), (0.5, 1), (0.75, 2), (1.0, 1), (1.5, 1), (2.0001, 0), (4.0001, 0),
    ]);
  });

  test('what does not check out is dropped with a warning, never guessed', () {
    final shifted = fixture();
    (shifted['tempos'] as List)[3] = {...(shifted['tempos'] as List)[3] as Map, 'timeCode': '00:09:700'};
    var s = MultiTracksStructure.parse(shifted);
    expect(s.tempoChanges, isEmpty);
    expect(s.click.bpm, 120, reason: 'the song keeps the base BPM');
    expect(s.warnings.single, contains('timeCode'));

    final unordered = fixture();
    (unordered['sections'] as List)[0] = {...(unordered['sections'] as List)[0] as Map, 'timeCode': '00:01:000'};
    s = MultiTracksStructure.parse(unordered);
    expect(s.sections, isEmpty);
    expect(s.warnings.single, contains('seções'));

    final noDuration = fixture()..remove('duration');
    s = MultiTracksStructure.parse(noDuration);
    expect(s.sections, isEmpty);
    expect(s.fixedClicks, isNotNull);

    final badClicks = fixture();
    (badClicks['clicks'] as Map)['quarters'] = [1.0, 0.5];
    expect(MultiTracksStructure.parse(badClicks).fixedClicks, isNull);

    final empty = MultiTracksStructure.parse({'bpm': 96.5});
    expect(empty.click.bpm, 96.5);
    expect(empty.sections, isEmpty);
    expect(empty.tempoChanges, isEmpty);
    expect(empty.fixedClicks, isNull);
  });

  test('fixed clicks survive the song file round trip; invalid data does not open', () {
    final s = MultiTracksStructure.parse(fixture());
    final track = Track(id: 't', title: 'T', channels: const [], fixedClicks: s.fixedClicks, sections: s.sections, tempoChanges: s.tempoChanges);
    final back = Track.fromJson(jsonDecode(jsonEncode(track.toJson())) as Map<String, dynamic>);
    expect(back.fixedClicks, s.fixedClicks);
    expect(back.sections, s.sections);
    expect(Track.fromJson({'id': 'x', 'title': 'X', 'channels': <dynamic>[]}).fixedClicks, isNull);
    expect(() => FixedClicks.fromJson({'quarters': [2.0, 1.0]}), throwsFormatException);
    expect(track.copyWith(fixedClicks: null).fixedClicks, isNull);
    expect(track.copyWith(title: 'U').fixedClicks, s.fixedClicks);
  });

  group('in the app', () {
    late FakeEngine engine;
    late ProviderContainer c;
    late Directory dir;
    setUp(() async {
      dir = await Directory.systemTemp.createTemp('mt-structure-');
      engine = FakeEngine();
      c = ProviderContainer(overrides: [
        engineProvider.overrideWithValue(engine),
        nextEngineProvider.overrideWithValue(FakeEngine(deck: 1)),
        persistenceServiceProvider.overrideWithValue(InMemoryPersistence()),
      ]);
    });
    tearDown(() async {
      c.dispose();
      await dir.delete(recursive: true);
    });

    Track song() {
      final s = MultiTracksStructure.parse(fixture(), hasGuideStem: true);
      return sampleTrack(id: 'multitracks-1-2').copyWith(
          sections: s.sections, clickSettings: s.click, tempoChanges: s.tempoChanges, fixedClicks: s.fixedClicks);
    }

    test('loading sends the fixed clicks to the engine; editing the grid drops them, volume and levels keep them', () async {
      final n = c.read(currentTrackProvider.notifier);
      expect(await n.load(song()), true);
      expect(engine.configuredClickTimes.length, 9);
      expect(engine.configuredTempoChanges.length, 4);

      expect(n.updateClickSettings(c.read(currentTrackProvider)!.clickSettings.copyWith(volume: 0.5, eighthGain: 1)), true);
      expect(c.read(currentTrackProvider)!.fixedClicks, isNotNull);
      expect(engine.configuredClickTimes, isNotEmpty);

      expect(n.updateClickSettings(c.read(currentTrackProvider)!.clickSettings.copyWith(bpm: 100)), true);
      expect(c.read(currentTrackProvider)!.fixedClicks, isNull);
      expect(engine.configuredClickTimes, isEmpty, reason: 'the edited grid now drives the click');

      expect(await n.load(song()), true);
      expect(n.updateTempoChanges('multitracks-1-2', const []), true);
      expect(c.read(currentTrackProvider)!.fixedClicks, isNull);
      expect(engine.configuredClickTimes, isEmpty);

      expect(await n.load(sampleTrack(id: 'plain')), true);
      expect(engine.configuredClickTimes, isEmpty, reason: 'a song without fixed clicks is on the grid');
    });

    test('a new download gives the structure to a song imported before it existed, and keeps the user edits after', () async {
      Future<Track> imported(Track structure, String tag) async {
        final file = writeSineWav('${dir.path}/$tag-click.wav', seconds: 0.1);
        return structure.copyWith(
          channels: [ChannelInfo(label: 'Click', filePath: file.path, isClickOrGuide: true)],
          origin: MultiTracksOrigin(contentId: 1, keyId: 2, contentType: 26, lastValidatedAt: DateTime.utc(2026, 10, 16)),
        );
      }

      final library = c.read(trackLibraryProvider.notifier);
      await library.refresh();
      final old = await library.publishImported(await imported(Track(id: 'multitracks-1-2', title: 'Semanal', channels: const []), 'a'));
      expect(old.sections, isEmpty);
      final edited = old.copyWith(clickSettings: old.clickSettings.copyWith(volume: 0.4));
      await c.read(persistenceServiceProvider).saveTrack(edited);
      await library.refresh();

      final again = await library.publishImported(await imported(song(), 'b'));
      expect(again.sections.length, 4);
      expect(again.fixedClicks, isNotNull);
      expect(again.tempoChanges.length, 4);
      expect((again.clickSettings.bpm, again.clickSettings.volume), (120.0, 0.4), reason: 'grid from MultiTracks, volume from the user');

      final renamed = again.copyWith(sections: [again.sections.first.copyWith(name: 'Minha contagem'), ...again.sections.skip(1)]);
      await c.read(persistenceServiceProvider).saveTrack(renamed);
      await library.refresh();
      final third = await library.publishImported(await imported(song(), 'c'));
      expect(third.sections.first.name, 'Minha contagem', reason: 'sections the song already has are the user\'s');
    });
  });
}
