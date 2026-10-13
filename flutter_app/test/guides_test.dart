import 'dart:async';
import 'dart:convert';
import 'dart:io';
import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/guide_cue.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/native/wtracks_bindings.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/screens/guide_editor_screen.dart';
import 'package:flutter_app/services/guide_resource_service.dart';
import 'package:flutter_app/services/dynamic_guides.dart';
import 'harness/harness_support.dart';

const _cueA = GuideCue(id: 'a', label: 'Intro', resourceName: 'r1', timeSeconds: 1, gain: 0.5);
const _cueB = GuideCue(id: 'b', label: 'Verso', resourceName: 'r2', timeSeconds: 1.5);
List<ScheduledGuide> _schedule(List<GuideCue> cues) => buildGuideSchedule(cues, const []);

class FakeGuideResources extends GuideResourceService {
  final prepared = <List<String>>[];
  bool fail = false;
  Completer<void>? gate;
  FakeGuideResources() : super(directoryResolver: () async => Directory.systemTemp);
  @override
  Future<List<Map<String, dynamic>>> resources() async => [
        {'name': 'r1', 'label': 'r1', 'asset': 'x', 'sha256': 'x'},
        {'name': 'r2', 'label': 'r2', 'asset': 'x', 'sha256': 'x'},
      ];
  @override
  Future<List<String>> prepare(List<String> names) async {
    prepared.add(names);
    if (gate != null) await gate!.future;
    if (fail) throw StateError('missing resource');
    return names.map((n) => '/guides/$n.wav').toList();
  }
}

class GateEngine extends FakeEngine {
  Completer<void>? gate;
  @override
  Future<bool> configureGuideScheduleAsync(List<ScheduledGuide> guides, Map<String, String> paths) async {
    if (gate != null) await gate!.future;
    return configureGuideSchedule(guides, paths);
  }
}

ProviderContainer _container(FakeEngine engine, FakeGuideResources resources, {InMemoryPersistence? persistence}) {
  final c = ProviderContainer(overrides: [
    engineProvider.overrideWithValue(engine),
    guideResourceServiceProvider.overrideWithValue(resources),
    if (persistence != null) persistenceServiceProvider.overrideWithValue(persistence),
  ]);
  addTearDown(c.dispose);
  return c;
}

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  group('model and schema', () {
    test('legacy tracks without guides load as an empty enabled schedule', () {
      final legacy = Track.fromJson({'schemaVersion': 2, 'id': 't', 'title': 'T', 'channels': <dynamic>[]});
      expect(legacy.guideCues, isEmpty);
      expect(legacy.guidesEnabled, true);
      expect(Track.fromJson({'id': 't', 'title': 'T', 'channels': <dynamic>[]}).guideCues, isEmpty);
    });

    test('schema 3 round-trips guides and the enabled flag', () {
      const track = Track(id: 't', title: 'T', channels: [], guideCues: [_cueA, _cueB], guidesEnabled: false);
      final json = jsonDecode(jsonEncode(track.toJson())) as Map<String, dynamic>;
      expect(json['schemaVersion'], 3);
      final back = Track.fromJson(json);
      expect(back.guideCues, [_cueA, _cueB]);
      expect(back.guidesEnabled, false);
      expect(Track.currentSchemaVersion, 3);
    });

    test('invalid persisted guides are rejected instead of silently repaired', () {
      Map<String, dynamic> cue(String id, num time, [num gain = 1]) =>
          {'id': id, 'label': 'L', 'resourceName': 'r1', 'timeSeconds': time, 'gain': gain};
      for (final list in [
        [cue('a', -1)],
        [cue('a', 1, 3)],
        [cue('a', 1, -0.1)],
        [cue('a', 2), cue('b', 1)],
        [cue('a', 1), cue('a', 2)],
        [{...cue('a', 1), 'label': '  '}],
        [{...cue('a', 1), 'resourceName': ''}],
        [{...cue('a', 1), 'timeSeconds': double.nan}],
      ]) {
        expect(() => GuideCue.fromJsonList(list), throwsA(anything), reason: '$list');
      }
      expect(GuideCue.validSequence(List.generate(4097, (i) => GuideCue(id: '$i', label: 'x', resourceName: 'r', timeSeconds: 0))), false);
    });
  });

  group('GuideResourceService', () {
    test('copies each bundled WAV once to a hash-named file and repairs a tampered cache', () async {
      final dir = await Directory.systemTemp.createTemp('guide-res-');
      addTearDown(() => dir.delete(recursive: true));
      final service = GuideResourceService(directoryResolver: () async => dir);
      final catalog = await service.resources();
      expect(catalog.length, 541);
      final names = [catalog[0]['name'] as String, catalog[1]['name'] as String];
      final paths = await service.prepare([names[0], names[1], names[0]]);
      expect(paths[0], paths[2]);
      expect(paths[0], isNot(paths[1]));
      expect(paths[0], endsWith('${catalog[0]['sha256']}.wav'));
      expect(File(paths[0]).lengthSync(), catalog[0]['outputBytes']);
      File(paths[0]).writeAsBytesSync([1, 2, 3]);
      await service.prepare([names[0]]);
      expect(File(paths[0]).lengthSync(), catalog[0]['outputBytes']);
      expect(await service.prepare([]), isEmpty);
      await expectLater(service.prepare(['does-not-exist']), throwsA(anything));
    });
  });

  group('CurrentTrackNotifier guides', () {
    const base = Track(id: 'song', title: 'Song', channels: []);
    test('success publishes engine configuration, state and switch', () async {
      final engine = FakeEngine();
      final resources = FakeGuideResources();
      final c = _container(engine, resources);
      final n = c.read(currentTrackProvider.notifier)..setLoadedTrack(base);
      expect(await n.updateGuides('song', [_cueA, _cueB], false), true);
      expect(engine.configuredSchedule, _schedule([_cueA, _cueB]));
      expect(engine.guidesEnabled, false);
      expect(c.read(currentTrackProvider)!.guideCues, [_cueA, _cueB]);
      expect(c.read(currentTrackProvider)!.guidesEnabled, false);
      expect(resources.prepared.single, ['r1', 'r2']);
    });

    test('switch-only change does not re-prepare or re-decode the schedule', () async {
      final engine = FakeEngine();
      final resources = FakeGuideResources();
      final c = _container(engine, resources);
      final n = c.read(currentTrackProvider.notifier)..setLoadedTrack(base);
      await n.updateGuides('song', [_cueA], true);
      engine.configuredSchedule = [];
      expect(await n.updateGuides('song', [_cueA], false), true);
      expect(resources.prepared.length, 1);
      expect(engine.configuredSchedule, isEmpty);
      expect(engine.guidesEnabled, false);
      expect(c.read(currentTrackProvider)!.guidesEnabled, false);
    });

    test('native or resource failure and invalid input keep the previous schedule', () async {
      final engine = FakeEngine();
      final resources = FakeGuideResources();
      final c = _container(engine, resources);
      final n = c.read(currentTrackProvider.notifier)..setLoadedTrack(base);
      await n.updateGuides('song', [_cueA], true);
      engine.failGuides = true;
      expect(await n.updateGuides('song', [_cueA, _cueB], true), false);
      engine.failGuides = false;
      resources.fail = true;
      expect(await n.updateGuides('song', [_cueB], true), false);
      resources.fail = false;
      expect(await n.updateGuides('song', [_cueB, _cueA], true), false); // unsorted
      expect(await n.updateGuides('other', [_cueB], true), false); // wrong track
      expect(c.read(currentTrackProvider)!.guideCues, [_cueA]);
      expect(engine.configuredSchedule, _schedule([_cueA]));
    });

    test('a track replaced while configuring discards the late result', () async {
      final engine = GateEngine()..gate = Completer<void>();
      final resources = FakeGuideResources();
      final c = _container(engine, resources);
      final n = c.read(currentTrackProvider.notifier)..setLoadedTrack(base);
      final pending = n.updateGuides('song', [_cueA], true);
      await Future<void>.delayed(Duration.zero);
      final loading = n.load(sampleTrack(id: 'next'));
      engine.gate!.complete();
      expect(await pending, false);
      await loading;
      expect(c.read(currentTrackProvider)?.id, isNot('song'));
      expect(c.read(currentTrackProvider)?.guideCues ?? const <GuideCue>[], isEmpty);
    });

    test('load configures saved guides after the audio and unloads when they fail', () async {
      final engine = FakeEngine();
      final resources = FakeGuideResources();
      final c = _container(engine, resources);
      final n = c.read(currentTrackProvider.notifier);
      final track = sampleTrack().copyWith(guideCues: [_cueA, _cueB], guidesEnabled: false);
      expect(await n.load(track), true);
      expect(engine.configuredSchedule, _schedule([_cueA, _cueB]));
      expect(engine.guidesEnabled, false);
      engine.failGuides = true;
      expect(await n.load(track.copyWith(title: 'Again')), false);
      expect(c.read(currentTrackProvider), isNull);
    });
  });

  group('GuideEditorScreen', () {
    testWidgets('adds, edits, toggles and deletes cues and persists each change', (tester) async {
      tester.view.physicalSize = const Size(400, 800);
      tester.view.devicePixelRatio = 1;
      addTearDown(tester.view.resetPhysicalSize);
      addTearDown(tester.view.resetDevicePixelRatio);
      final engine = FakeEngine();
      final resources = FakeGuideResources();
      final persistence = InMemoryPersistence();
      final c = _container(engine, resources, persistence: persistence);
      c.read(currentTrackProvider.notifier).setLoadedTrack(sampleTrack(id: 'song'));
      await c.read(trackLibraryProvider.notifier).saveCurrent();
      await tester.pumpWidget(UncontrolledProviderScope(
          container: c, child: const MaterialApp(home: GuideEditorScreen(trackId: 'song'))));
      await tester.pumpAndSettle();
      expect(find.text('Adicione as guias da música.'), findsOneWidget);

      await tester.tap(find.byTooltip('Adicionar guia'));
      await tester.pumpAndSettle();
      await tester.enterText(find.byKey(const Key('guide-label')), 'Refrão');
      await tester.enterText(find.byKey(const Key('guide-time')), '3,5');
      await tester.tap(find.text('Salvar'));
      await tester.pumpAndSettle();
      expect(find.text('Refrão'), findsOneWidget);
      expect(engine.configuredSchedule.single.timeSeconds, 3.5);
      expect(persistence.tracks['song']!.guideCues.single.label, 'Refrão');

      await tester.tap(find.byTooltip('Editar guia'));
      await tester.pumpAndSettle();
      await tester.enterText(find.byKey(const Key('guide-time')), '-1');
      await tester.tap(find.text('Salvar'));
      await tester.pumpAndSettle();
      expect(find.text('Informe um instante válido'), findsOneWidget);
      await tester.tap(find.text('Cancelar'));
      await tester.pumpAndSettle();
      expect(c.read(currentTrackProvider)!.guideCues.single.timeSeconds, 3.5);

      await tester.tap(find.byType(Switch));
      await tester.pumpAndSettle();
      expect(engine.guidesEnabled, false);
      expect(persistence.tracks['song']!.guidesEnabled, false);

      engine.failGuides = true;
      await tester.tap(find.byTooltip('Excluir guia'));
      await tester.pumpAndSettle();
      expect(find.text('Não foi possível preparar as guias.'), findsOneWidget);
      expect(c.read(currentTrackProvider)!.guideCues.length, 1);
      engine.failGuides = false;
      await tester.pump(const Duration(seconds: 5));
      await tester.tap(find.byTooltip('Excluir guia'));
      await tester.pumpAndSettle();
      expect(c.read(currentTrackProvider)!.guideCues, isEmpty);
      expect(persistence.tracks['song']!.guideCues, isEmpty);
      expect(tester.takeException(), isNull);
      await tester.pumpWidget(const SizedBox.shrink());
    });
  });

  group('native FFI', () {
    test('real ABI validates, preserves the previous schedule on failure and accepts an empty clear', () async {
      final dir = await Directory.systemTemp.createTemp('guide-ffi-');
      addTearDown(() => dir.delete(recursive: true));
      final song = writeSineWav('${dir.path}/song.wav', seconds: 2);
      final cue = writeSineWav('${dir.path}/cue.wav', seconds: 0.2, freq: 880);
      final engine = WTracksEngine()..initialise();
      addTearDown(engine.shutdown);
      expect(engine.configureGuides([_cueA], [cue.path]), false, reason: 'no track loaded');
      expect(await engine.loadTrackAsync('guide-ffi', [song.path]), true, reason: engine.lastError);
      expect(await engine.configureGuidesAsync([_cueA, _cueB], [cue.path, cue.path]), true, reason: engine.lastError);
      engine.setGuidesEnabled(true);
      final errors = <Object>[];
      for (final attempt in <(List<GuideCue>, List<String>)>[
        ([_cueA], ['${dir.path}/missing.wav']),
        ([const GuideCue(id: 'z', label: 'z', resourceName: 'r', timeSeconds: 9)], [cue.path]), // past the song
        ([_cueB, _cueA], [cue.path, cue.path]),
        ([_cueA], [cue.path, cue.path]),
      ]) {
        if (engine.configureGuides(attempt.$1, attempt.$2)) errors.add(attempt);
      }
      expect(errors, isEmpty);
      expect(engine.configureGuides(const [], const []), true, reason: engine.lastError);
      engine.setGuidesEnabled(false);
    }, skip: !nativeEngineAvailable() ? 'Native library unavailable' : false);
  });
}
