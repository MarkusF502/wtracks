import 'dart:convert';
import 'dart:io';
import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/guide_cue.dart';
import 'package:flutter_app/models/guide_settings.dart';
import 'package:flutter_app/models/song_section.dart';
import 'package:flutter_app/models/tempo_change.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/native/wtracks_bindings.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/screens/guide_editor_screen.dart';
import 'package:flutter_app/services/dynamic_guides.dart';
import 'package:flutter_app/services/guide_preferences_store.dart';
import 'package:flutter_app/services/guide_resource_service.dart';
import 'harness/harness_support.dart';

final _names = [
  'guidecue-section-en-female-Chorus',
  'guidecue-section-en-female-Chorus 2',
  'guidecue-section-en-female-Pre Chorus',
  'guidecue-section-en-female-Verse 1',
  'guidecue-section-en-male-Chorus',
  'guidecue-section-pt-female-Chorus',
  for (var n = 1; n <= 7; n++) 'guidecue-count-en-female-$n',
  for (var n = 1; n <= 6; n++) 'guidecue-count-en-male-$n',
  'not-a-guide',
];

class _Resources extends GuideResourceService {
  final prepared = <List<String>>[];
  final failing = <String>{};
  _Resources() : super(directoryResolver: () async => Directory.systemTemp);
  @override
  Future<List<Map<String, dynamic>>> resources() async => [for (final n in _names) {'name': n, 'label': n, 'asset': 'x', 'sha256': 'x'}];
  @override
  Future<List<String>> prepare(List<String> names) async {
    prepared.add(names);
    if (names.any(failing.contains)) throw StateError('missing');
    return [for (final n in names) '/g/$n.wav'];
  }
}

class _MemoryPrefs extends GuidePreferencesStore {
  GuideSettings saved;
  _MemoryPrefs([this.saved = const GuideSettings()]);
  @override
  Future<GuideSettings> load() async => saved;
  @override
  Future<void> save(GuideSettings settings) async => saved = settings;
}

const _click = ClickSettings(bpm: 120);
SongSection _section(String id, String name, double start, double end, {bool guide = true, bool count = false}) =>
    SongSection(id: id, name: name, startSeconds: start, endSeconds: end, playGuideCue: guide, playCountIn: count);

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  final catalog = GuideCatalog(_names);
  const en = GuideSettings();

  group('catalog and names', () {
    test('voices, counts and section names come from the file names', () {
      expect(catalog.voices.map((v) => '$v'), ['en-female', 'en-male', 'pt-female']);
      expect(catalog.maxCount(const GuideVoice('en', 'female')), 7);
      expect(catalog.maxCount(const GuideVoice('pt', 'female')), 0);
      expect(catalog.count(const GuideVoice('en', 'male'), 6), 'guidecue-count-en-male-6');
      expect(catalog.count(const GuideVoice('en', 'male'), 7), isNull);
      const voice = GuideVoice('en', 'female');
      expect(catalog.section(voice, '  chorus '), 'guidecue-section-en-female-Chorus');
      expect(catalog.section(voice, 'Refrão 2'), 'guidecue-section-en-female-Chorus 2');
      expect(catalog.section(voice, 'Pré-Refrão'), 'guidecue-section-en-female-Pre Chorus');
      expect(catalog.section(voice, 'PreChorus'), 'guidecue-section-en-female-Pre Chorus');
      expect(catalog.section(voice, 'pre_chorus'), 'guidecue-section-en-female-Pre Chorus');
      expect(catalog.section(voice, 'Verso 1'), 'guidecue-section-en-female-Verse 1');
      expect(catalog.section(voice, 'Verse1'), 'guidecue-section-en-female-Verse 1');
      expect(catalog.section(voice, 'Bridge'), isNull);
    });

    test('the bundled manifest yields eight voices with counts', () async {
      final service = GuideResourceService(directoryResolver: () async => Directory.systemTemp);
      final real = GuideCatalog((await service.resources()).map((r) => r['name'] as String));
      expect(real.voices.length, 8);
      for (final voice in real.voices) {
        expect(real.maxCount(voice), greaterThanOrEqualTo(6), reason: '$voice');
        expect(real.section(voice, 'Refrão'), isNotNull, reason: '$voice');
      }
      expect(real.section(const GuideVoice('pt', 'female'), 'Vamp Verse'), isNull);
    });
  });

  group('generation', () {
    test('name on the first beat of the bar before the section, counts on the rest', () {
      final plan = generateDynamicGuides(
          sections: [_section('c', 'Chorus', 10, 20, count: true)], click: _click, tempoChanges: const [], settings: en, catalog: catalog);
      String c(int n) => 'guidecue-count-en-female-$n';
      expect(plan.cues, [
        DynamicGuideCue(cueType: GuideCueType.section, sectionId: 'c', cueSequenceTimecode: 8, songMapElementStartTimecode: 10,
            cueFilePath: 'guidecue-section-en-female-Chorus', replacementCountCueFilePath: c(1)),
        DynamicGuideCue(cueType: GuideCueType.count, sectionId: 'c', cueSequenceTimecode: 8.5, songMapElementStartTimecode: 10,
            replacementCountCueFilePath: c(2)),
        DynamicGuideCue(cueType: GuideCueType.count, sectionId: 'c', cueSequenceTimecode: 9, songMapElementStartTimecode: 10, cueFilePath: c(3)),
        DynamicGuideCue(cueType: GuideCueType.count, sectionId: 'c', cueSequenceTimecode: 9.5, songMapElementStartTimecode: 10, cueFilePath: c(4)),
      ]);
      expect(plan.missingSectionNames, isEmpty);
    });

    test('name only, count only, global count, disabled and missing names', () {
      final nameOnly = generateDynamicGuides(
          sections: [_section('c', 'Chorus', 10, 20)], click: _click, tempoChanges: const [], settings: en, catalog: catalog);
      expect(nameOnly.cues.single.cueFilePath, 'guidecue-section-en-female-Chorus');
      expect(nameOnly.cues.single.replacementCountCueFilePath, isNull);

      final countOnly = generateDynamicGuides(sections: [_section('c', 'Chorus', 10, 20, guide: false)], click: _click,
          tempoChanges: const [], settings: en.copyWith(countIntoEachSection: true), catalog: catalog);
      expect(countOnly.cues.map((c) => c.cueFilePath), [for (var n = 1; n <= 4; n++) 'guidecue-count-en-female-$n']);
      expect(countOnly.cues.map((c) => c.cueSequenceTimecode), [8, 8.5, 9, 9.5]);

      final missing = generateDynamicGuides(sections: [_section('x', 'Solo de gaita', 10, 20, count: true)], click: _click,
          tempoChanges: const [], settings: en, catalog: catalog);
      expect(missing.missingSectionNames, ['Solo de gaita']);
      expect(missing.cues.length, 4, reason: 'counts still play without the name');

      expect(generateDynamicGuides(sections: [_section('c', 'Chorus', 10, 20, count: true)], click: _click, tempoChanges: const [],
          settings: en.copyWith(dynamicEnabled: false), catalog: catalog).cues, isEmpty);
      expect(generateDynamicGuides(sections: [_section('c', 'Chorus', 10, 20, guide: false)], click: _click, tempoChanges: const [],
          settings: en, catalog: catalog).cues, isEmpty);
    });

    test('beats before the song start are dropped; the bar follows the tempo map and the bpm unit', () {
      final early = generateDynamicGuides(sections: [_section('c', 'Chorus', 1, 20, count: true)], click: _click,
          tempoChanges: const [], settings: en, catalog: catalog);
      expect(early.cues.map((c) => (c.cueSequenceTimecode, c.cueFilePath, c.replacementCountCueFilePath)), [
        (0.0, 'guidecue-count-en-female-3', null), // name and beat 2 fall before 0 s
        (0.5, 'guidecue-count-en-female-4', null),
      ]);
      expect(generateDynamicGuides(sections: [_section('c', 'Chorus', 0, 20, count: true)], click: _click, tempoChanges: const [],
          settings: en, catalog: catalog).cues, isEmpty);

      final waltz = generateDynamicGuides(sections: [_section('c', 'Chorus', 10, 20, count: true)], click: _click,
          tempoChanges: const [TempoChange(id: 't', startSeconds: 5, bpm: 60, numerator: 3)], settings: en, catalog: catalog);
      expect(waltz.cues.map((c) => (c.cueSequenceTimecode, c.cueFilePath)), [
        (7.0, 'guidecue-section-en-female-Chorus'),
        (8.0, null),
        (9.0, 'guidecue-count-en-female-3'),
      ]);
      // A change exactly at the section start does not move the bar before it.
      final atStart = generateDynamicGuides(sections: [_section('c', 'Chorus', 10, 20, guide: false, count: true)], click: _click,
          tempoChanges: const [TempoChange(id: 't', startSeconds: 10, bpm: 60, numerator: 3)], settings: en, catalog: catalog);
      expect(atStart.cues.map((c) => c.cueSequenceTimecode), [8, 8.5, 9, 9.5]);

      // 6/8 with the BPM in quarters (bpmUnit 4): six eighths of 0.25 s at 120.
      final sixEight = generateDynamicGuides(sections: [_section('c', 'Chorus', 10, 20, guide: false, count: true)],
          click: const ClickSettings(bpm: 120, timeSignatureNumerator: 6, timeSignatureDenominator: 8, bpmUnit: 4),
          tempoChanges: const [], settings: en, catalog: catalog);
      expect(sixEight.cues.map((c) => c.cueSequenceTimecode), [8.5, 8.75, 9, 9.25, 9.5, 9.75]);
      // The male voice has six numbers: a seventh beat stays silent.
      final seven = generateDynamicGuides(sections: [_section('c', 'Chorus', 10, 20, guide: false, count: true)],
          click: const ClickSettings(bpm: 120, timeSignatureNumerator: 7), tempoChanges: const [],
          settings: en.copyWith(gender: 'male'), catalog: catalog);
      expect(seven.cues.length, 6);
    });

    test('schedule merges manual and dynamic cues stably and skips disabled ones', () {
      const manual = GuideCue(id: 'm', label: 'M', resourceName: 'r', timeSeconds: 8, gain: 0.5);
      const a = DynamicGuideCue(cueType: GuideCueType.count, sectionId: 's', cueSequenceTimecode: 8, songMapElementStartTimecode: 10, cueFilePath: 'c1');
      const b = DynamicGuideCue(cueType: GuideCueType.count, sectionId: 's', cueSequenceTimecode: 7, songMapElementStartTimecode: 10,
          replacementCountCueFilePath: 'c2');
      const off = DynamicGuideCue(cueType: GuideCueType.count, sectionId: 's', cueSequenceTimecode: 1, songMapElementStartTimecode: 10,
          cueFilePath: 'c3', cueEnabled: false);
      expect(buildGuideSchedule([manual], [a, b, off]), const [
        ScheduledGuide(timeSeconds: 7, replacement: 'c2', targetSeconds: 10),
        ScheduledGuide(timeSeconds: 8, resource: 'r', gain: 0.5),
        ScheduledGuide(timeSeconds: 8, resource: 'c1', targetSeconds: 10),
      ]);
      expect(prerollCounts(catalog, en).whereType<String>().length, 7);
      expect(prerollCounts(catalog, en).length, 16);
    });
  });

  group('settings', () {
    test('round-trip and defaults for corrupt values', () async {
      const s = GuideSettings(dynamicEnabled: false, language: 'pt', gender: 'male', countIntoEachSection: true, sectionPreroll: true);
      expect(GuideSettings.fromJson(jsonDecode(jsonEncode(s.toJson()))), s);
      expect(GuideSettings.fromJson('x'), const GuideSettings());
      expect(GuideSettings.fromJson({'language': 'portuguese', 'gender': 'x', 'sectionPreroll': 1}), const GuideSettings());
      final dir = await Directory.systemTemp.createTemp('guide-prefs-');
      addTearDown(() => dir.delete(recursive: true));
      final store = GuidePreferencesStore(directoryResolver: () async => dir);
      expect(await store.load(), const GuideSettings());
      await store.save(s);
      expect(await store.load(), s);
      File('${dir.path}/wtracks_data/guides.json').writeAsStringSync('{broken');
      expect(await store.load(), const GuideSettings());
    });
  });

  group('CurrentTrackNotifier', () {
    ProviderContainer container(FakeEngine engine, _Resources resources, _MemoryPrefs prefs) {
      final c = ProviderContainer(overrides: [
        engineProvider.overrideWithValue(engine),
        guideResourceServiceProvider.overrideWithValue(resources),
        guidePreferencesProvider.overrideWithValue(prefs),
      ]);
      addTearDown(c.dispose);
      return c;
    }

    test('load sends section guides with targets and replacements; edits and settings re-sync', () async {
      final engine = FakeEngine();
      final resources = _Resources();
      final c = container(engine, resources, _MemoryPrefs());
      final n = c.read(currentTrackProvider.notifier);
      final track = sampleTrack(id: 's').copyWith(clickSettings: _click, sections: [_section('c', 'Chorus', 10, 20, count: true)]);
      expect(await n.load(track), true);
      expect(engine.configuredSchedule.map((g) => (g.timeSeconds, g.resource, g.replacement, g.targetSeconds)), [
        (8.0, 'guidecue-section-en-female-Chorus', 'guidecue-count-en-female-1', 10.0),
        (8.5, null, 'guidecue-count-en-female-2', 10.0),
        (9.0, 'guidecue-count-en-female-3', null, 10.0),
        (9.5, 'guidecue-count-en-female-4', null, 10.0),
      ]);
      expect(engine.configuredSchedulePaths['guidecue-count-en-female-2'], '/g/guidecue-count-en-female-2.wav');
      expect(engine.prerollEnabled, false);

      expect(n.updateSections('s', [_section('c', 'Chorus', 12, 20)]), true);
      await n.refreshGuides();
      expect(engine.configuredSchedule.single.timeSeconds, 10);

      expect(await c.read(guideSettingsProvider.notifier).apply(const GuideSettings(sectionPreroll: true, gender: 'male')), true);
      expect(engine.configuredSchedule.single.resource, 'guidecue-section-en-male-Chorus');
      expect(engine.prerollEnabled, true);
      expect(engine.prerollStarts, [12.0]);
      expect(engine.prerollCountPaths.take(7), [for (var k = 1; k <= 6; k++) '/g/guidecue-count-en-male-$k.wav', null]);

      // Unchanged schedule: nothing is prepared again.
      final before = resources.prepared.length;
      expect(await n.refreshGuides(), true);
      expect(resources.prepared.length, before);

      expect(await c.read(guideSettingsProvider.notifier).apply(const GuideSettings(dynamicEnabled: false)), true);
      expect(engine.configuredSchedule, isEmpty);
      expect(engine.prerollEnabled, false);
    });

    test('saved preferences are applied once read; tempo edits move the guides', () async {
      final engine = FakeEngine();
      final c = container(engine, _Resources(), _MemoryPrefs(const GuideSettings(countIntoEachSection: true)));
      final n = c.read(currentTrackProvider.notifier);
      c.read(guideSettingsProvider);
      await Future<void>.delayed(Duration.zero);
      expect(await n.load(sampleTrack(id: 's').copyWith(clickSettings: _click, sections: [_section('c', 'Chorus', 10, 20, guide: false)])), true);
      expect(engine.configuredSchedule.length, 4);
      expect(n.updateClickSettings(_click.copyWith(bpm: 60)), true);
      await n.refreshGuides();
      expect(engine.configuredSchedule.map((g) => g.timeSeconds), [6, 7, 8, 9]);
    });

    test('dynamic guide failures fall back to the manual guides; the song still loads', () async {
      final engine = FakeEngine();
      final resources = _Resources()..failing.add('guidecue-section-en-female-Chorus');
      final c = container(engine, resources, _MemoryPrefs());
      const manual = GuideCue(id: 'm', label: 'M', resourceName: 'guidecue-count-en-female-1', timeSeconds: 1);
      final track = sampleTrack(id: 's').copyWith(guideCues: [manual], sections: [_section('c', 'Chorus', 10, 20)]);
      expect(await c.read(currentTrackProvider.notifier).load(track), true);
      expect(engine.configuredSchedule, [const ScheduledGuide(timeSeconds: 1, resource: 'guidecue-count-en-female-1')]);
      engine.failGuides = true;
      expect(await c.read(currentTrackProvider.notifier).load(track.copyWith(title: 'again')), false);
    });
  });

  testWidgets('GuideEditorScreen lists section guides and the settings sheet applies the preferences', (tester) async {
    tester.view.physicalSize = const Size(400, 900);
    tester.view.devicePixelRatio = 1;
    addTearDown(tester.view.resetPhysicalSize);
    addTearDown(tester.view.resetDevicePixelRatio);
    final engine = FakeEngine();
    final prefs = _MemoryPrefs();
    final c = ProviderContainer(overrides: [
      engineProvider.overrideWithValue(engine),
      guideResourceServiceProvider.overrideWithValue(_Resources()),
      guidePreferencesProvider.overrideWithValue(prefs),
    ]);
    addTearDown(c.dispose);
    c.read(currentTrackProvider.notifier).setLoadedTrack(
        sampleTrack(id: 'song').copyWith(clickSettings: _click, sections: [_section('c', 'Refrão', 10, 20, count: true), _section('x', 'Gaita', 30, 40)]));
    await tester.pumpWidget(UncontrolledProviderScope(container: c, child: const MaterialApp(home: GuideEditorScreen(trackId: 'song'))));
    await tester.pumpAndSettle();
    expect(find.text('Refrão'), findsOneWidget);
    expect(find.text('8.00s · nome, 3, 4'), findsOneWidget);
    expect(find.text('Sem áudio nesta voz: Gaita'), findsOneWidget);

    await tester.tap(find.byTooltip('Configurar guias'));
    await tester.pumpAndSettle();
    await tester.tap(find.byKey(const Key('guide-preroll')));
    await tester.pumpAndSettle();
    expect(prefs.saved.sectionPreroll, true);
    expect(engine.prerollEnabled, true);
    expect(engine.prerollStarts, [10.0, 30.0]);
    await tester.tap(find.byKey(const Key('guide-language')));
    await tester.pumpAndSettle();
    await tester.tap(find.text('Português').last);
    await tester.pumpAndSettle();
    expect(prefs.saved.language, 'pt');
    expect(engine.configuredSchedule.first.resource, 'guidecue-section-pt-female-Chorus');
    expect(tester.takeException(), isNull);
    await tester.pumpWidget(const SizedBox.shrink());
  });

  group('native FFI', () {
    test('real ABI accepts replacements and targets, validates the pre-roll and reports it', () async {
      final dir = await Directory.systemTemp.createTemp('dyn-guide-ffi-');
      addTearDown(() => dir.delete(recursive: true));
      final song = writeSineWav('${dir.path}/song.wav', seconds: 3);
      final cue = writeSineWav('${dir.path}/cue.wav', seconds: 0.2, freq: 880);
      final engine = WTracksEngine()..initialise();
      addTearDown(engine.shutdown);
      expect(await engine.loadTrackAsync('dyn-ffi', [song.path]), true, reason: engine.lastError);
      final paths = {'a': cue.path, 'b': cue.path, 'missing': '${dir.path}/missing.wav'};
      expect(await engine.configureGuideScheduleAsync(const [
        ScheduledGuide(timeSeconds: 0.5, resource: 'a', replacement: 'b', targetSeconds: 1),
        ScheduledGuide(timeSeconds: 0.75, replacement: 'b', targetSeconds: 1),
        ScheduledGuide(timeSeconds: 1, resource: 'a'),
      ], paths), true, reason: engine.lastError);
      expect(engine.configureGuideSchedule(const [ScheduledGuide(timeSeconds: 0.5)], paths), false, reason: 'no sound at all');
      expect(engine.configureGuideSchedule(const [ScheduledGuide(timeSeconds: 0.5, resource: 'missing')], paths), false);
      expect(engine.configureGuideSchedule(const [ScheduledGuide(timeSeconds: 0.5, resource: 'unknown')], paths), false);
      expect(engine.configureGuideSchedule(const [ScheduledGuide(timeSeconds: 0.5, resource: 'a', targetSeconds: -3)], paths), false);
      expect(await engine.configurePrerollAsync(true, [0.0, 1.0], [cue.path, null, cue.path]), true, reason: engine.lastError);
      expect(engine.configurePreroll(true, [double.nan], const []), false);
      expect(engine.configurePreroll(true, const [], ['${dir.path}/missing.wav']), false);
      expect(engine.configurePreroll(true, const [], List.filled(17, null)), false);
      engine.seekToSeconds(1.0);
      engine.play();
      expect(engine.isPrerolling, true);
      engine.pause();
      expect(engine.isPrerolling, false);
    }, skip: !nativeEngineAvailable() ? 'Native library unavailable' : false);
  });
}
