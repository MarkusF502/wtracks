import 'dart:convert';
import 'dart:io';
import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/song_section.dart';
import 'package:flutter_app/models/tempo_change.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/native/wtracks_bindings.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/screens/tempo_map_screen.dart';
import 'harness/harness_support.dart';
import 'harness/screens_harness_test.dart' show loadRealFonts;

const _a = TempoChange(id: 'a', startSeconds: 10, bpm: 90, numerator: 3, denominator: 4);
const _b = TempoChange(id: 'b', startSeconds: 20, bpm: 140, numerator: 6, denominator: 8);

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  setUpAll(loadRealFonts);
  setUp(mockBackgroundChannel);

  group('SongSection options', () {
    test('legacy sections load with defaults and the new fields round-trip', () {
      final legacy = SongSection.fromJson({'id': 'a', 'name': 'A', 'startSeconds': 0, 'endSeconds': 5});
      expect(legacy.loopCount, 0);
      expect(legacy.presetInfiniteLoop, false);
      expect(legacy.playGuideCue, true);
      expect(legacy.playCountIn, false);
      const section = SongSection(id: 'v', name: 'Verse', startSeconds: 1, endSeconds: 9, loopCount: 4, presetInfiniteLoop: true, playGuideCue: false, playCountIn: true);
      expect(SongSection.fromJson(jsonDecode(jsonEncode(section.toJson())) as Map<String, dynamic>), section);
      expect(const SongSection(id: 'v', name: 'V', startSeconds: 0, endSeconds: 1, loopCount: -1).isValid, false);
      expect(const SongSection(id: 'v', name: 'V', startSeconds: 0, endSeconds: 1, loopCount: 1001).isValid, false);
      expect(() => SongSection.fromJson({'id': 'a', 'name': 'A', 'startSeconds': 0, 'endSeconds': 5, 'loopCount': 5000}), throwsA(anything));
    });
  });

  group('TempoChange', () {
    test('validation, ordering and persistence', () {
      expect(TempoChange.validSequence([_a, _b]), true);
      expect(TempoChange.validSequence([_b, _a]), false);
      expect(TempoChange.validSequence([_a, _a.copyWith(bpm: 100)]), false); // same id and time
      expect(TempoChange.validSequence([_a], baseOffset: 10), false); // not after the click offset
      expect(TempoChange.validSequence([_a], baseOffset: 9.9), true);
      for (final bad in [_a.copyWith(bpm: 0.5), _a.copyWith(bpm: 1001), _a.copyWith(numerator: 0), _a.copyWith(denominator: 3), _a.copyWith(startSeconds: 0), _a.copyWith(startSeconds: double.nan)]) {
        expect(bad.isValid, false);
      }
      final track = const Track(id: 't', title: 'T', channels: []).copyWith(tempoChanges: [_a, _b]);
      expect(Track.fromJson(jsonDecode(jsonEncode(track.toJson())) as Map<String, dynamic>).tempoChanges, [_a, _b]);
      expect(Track.fromJson({'id': 't', 'title': 'T', 'channels': <dynamic>[]}).tempoChanges, isEmpty);
      expect(() => TempoChange.fromJsonList([_b.toJson(), _a.toJson()]), throwsA(anything));
    });
  });

  group('CurrentTrackNotifier', () {
    ProviderContainer container(FakeEngine engine) {
      final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine)]);
      addTearDown(c.dispose);
      return c;
    }

    test('tempo changes go to the engine first and are re-validated against the click offset', () {
      final engine = FakeEngine();
      final c = container(engine);
      final n = c.read(currentTrackProvider.notifier)..setLoadedTrack(sampleTrack(id: 'song'));
      expect(n.updateTempoChanges('song', [_a, _b]), true);
      expect(engine.configuredTempoChanges, [_a, _b]);
      engine.failTempoChanges = true;
      expect(n.updateTempoChanges('song', [_a]), false);
      engine.failTempoChanges = false;
      expect(n.updateTempoChanges('song', [_b, _a]), false);
      expect(n.updateTempoChanges('other', [_a]), false);
      expect(c.read(currentTrackProvider)!.tempoChanges, [_a, _b]);
      // Moving the click offset past the first change drops it in the engine, and the state follows.
      n.applyClickOffset(15);
      expect(c.read(currentTrackProvider)!.tempoChanges, isEmpty);
      expect(engine.configuredTempoChanges, isEmpty);
    });

    test('load applies tempo changes and fails when the engine rejects them', () async {
      final engine = FakeEngine();
      final c = container(engine);
      final n = c.read(currentTrackProvider.notifier);
      expect(await n.load(sampleTrack(id: 'm').copyWith(tempoChanges: [_a])), true);
      expect(engine.configuredTempoChanges, [_a]);
      engine.failTempoChanges = true;
      expect(await n.load(sampleTrack(id: 'm2').copyWith(tempoChanges: [_a])), false);
    });

    test('section loops carry their repeat count; preset sections are prepared on load and when they change', () async {
      final engine = FakeEngine();
      final c = container(engine);
      final n = c.read(currentTrackProvider.notifier);
      const verse = SongSection(id: 'v', name: 'Verse', startSeconds: 10, endSeconds: 20, loopCount: 3);
      const vamp = SongSection(id: 'p', name: 'Vamp', startSeconds: 20, endSeconds: 30, presetInfiniteLoop: true);
      expect(await n.load(sampleTrack(id: 's').copyWith(sections: [verse, vamp])), true);
      expect(engine.presetSections.map((s) => s.id), ['p']);
      expect(await n.setSectionLoop(verse), true);
      expect(engine.calls, contains('loop(10.0,20.0,true,x3)'));
      expect(await n.setSectionLoop(vamp, queue: true), true);
      expect(engine.calls.any((call) => call.startsWith('enqueueLoop(20.0,30.0')), true);
      // Editing the flags re-prepares; an unrelated edit does not.
      engine.presetCalls.clear();
      expect(n.updateSections('s', [verse, vamp.copyWith(presetInfiniteLoop: false)]), true);
      await Future<void>.delayed(const Duration(milliseconds: 20));
      expect(engine.presetCalls.single, isEmpty);
      engine.presetCalls.clear();
      expect(n.updateSections('s', [verse.copyWith(name: 'Verso'), vamp.copyWith(presetInfiniteLoop: false)]), true);
      await Future<void>.delayed(const Duration(milliseconds: 20));
      expect(engine.presetCalls, isEmpty);
    });

    test('a failing preset preparation does not fail the load', () async {
      final engine = FakeEngine()..failPresets = true;
      final c = container(engine);
      const vamp = SongSection(id: 'p', name: 'Vamp', startSeconds: 20, endSeconds: 30, presetInfiniteLoop: true);
      expect(await c.read(currentTrackProvider.notifier).load(sampleTrack(id: 's').copyWith(sections: [vamp])), true);
    });
  });

  testWidgets('TempoMapScreen adds, edits and deletes changes with validation', (tester) async {
    tester.view.physicalSize = const Size(400, 900);
    tester.view.devicePixelRatio = 1;
    addTearDown(tester.view.resetPhysicalSize);
    addTearDown(tester.view.resetDevicePixelRatio);
    final engine = FakeEngine();
    final persistence = InMemoryPersistence();
    final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine), persistenceServiceProvider.overrideWithValue(persistence)]);
    addTearDown(c.dispose);
    c.read(currentTrackProvider.notifier).setLoadedTrack(sampleTrack(id: 'song'));
    await c.read(trackLibraryProvider.notifier).saveCurrent();
    await tester.pumpWidget(UncontrolledProviderScope(container: c, child: const MaterialApp(home: TempoMapScreen(trackId: 'song'))));
    expect(find.text('Sem mudanças de andamento.'), findsOneWidget);
    await tester.tap(find.byTooltip('Adicionar mudança'));
    await tester.pumpAndSettle();
    await tester.enterText(find.byKey(const Key('tempo-bpm')), '5000');
    await tester.tap(find.text('Salvar'));
    await tester.pumpAndSettle();
    expect(find.text('Use 1 a 1000'), findsOneWidget);
    await tester.enterText(find.byKey(const Key('tempo-bpm')), '96,5');
    await tester.enterText(find.byKey(const Key('tempo-start')), '30');
    await tester.tap(find.text('Salvar'));
    await tester.runAsync(() => Future<void>.delayed(const Duration(milliseconds: 100)));
    await tester.pumpAndSettle();
    expect(engine.configuredTempoChanges.single.bpm, 96.5);
    expect(engine.configuredTempoChanges.single.startSeconds, 30);
    expect(persistence.tracks['song']!.tempoChanges.single.bpm, 96.5);
    expect(find.textContaining('96.50 BPM'), findsOneWidget);
    await tester.tap(find.byTooltip('Excluir mudança'));
    await tester.runAsync(() => Future<void>.delayed(const Duration(milliseconds: 100)));
    await tester.pumpAndSettle();
    expect(c.read(currentTrackProvider)!.tempoChanges, isEmpty);
    await tester.pumpWidget(const SizedBox.shrink());
    c.dispose();
  });

  group('native FFI', () {
    test('real ABI validates tempo changes, counted loops and preset loops', () async {
      final dir = await Directory.systemTemp.createTemp('map-ffi-');
      addTearDown(() => dir.delete(recursive: true));
      final song = writeSineWav('${dir.path}/song.wav', seconds: 6);
      final engine = WTracksEngine()..initialise();
      addTearDown(engine.shutdown);
      expect(await engine.loadTrackAsync('map-ffi', [song.path]), true, reason: engine.lastError);
      expect(engine.configureClick(const ClickSettings(bpm: 120)), true);
      expect(engine.setClickTempoChanges([_a.copyWith(startSeconds: 1), _b.copyWith(startSeconds: 2)]), true, reason: engine.lastError);
      expect(engine.setClickTempoChanges([_b, _a]), false);
      expect(engine.setClickTempoChanges(const []), true);
      expect(engine.setLoop(1, 2, true, repeats: 3), true, reason: engine.lastError);
      expect(engine.loopEnabled, true);
      expect(await engine.setLoopAsync(1, 2, true, repeats: 5000), false);
      expect(engine.loopEnabled, true);
      expect(engine.setLoop(0, 0, false), true);
      const presets = [SongSection(id: 'p', name: 'Vamp', startSeconds: 2, endSeconds: 3, presetInfiniteLoop: true)];
      expect(await engine.configurePresetLoopsAsync(presets), true, reason: engine.lastError);
      expect(engine.configurePresetLoops([const SongSection(id: 'x', name: 'X', startSeconds: 5, endSeconds: 9)]), false);
      expect(engine.configurePresetLoops(const []), true);
    }, skip: !nativeEngineAvailable() ? 'Native library unavailable' : false);
  });
}
