import 'dart:convert';
import 'dart:io';
import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/app_settings.dart';
import 'package:flutter_app/models/song_section.dart';
import 'package:flutter_app/native/wtracks_bindings.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/screens/performance_screen.dart';
import 'package:flutter_app/screens/settings_screen.dart';
import 'package:flutter_app/services/app_preferences_store.dart';
import 'package:flutter_app/services/click_resource_service.dart';
import 'package:flutter_app/services/guide_resource_service.dart';
import 'harness/harness_support.dart';

class _Prefs extends AppPreferencesStore {
  AppSettings saved = const AppSettings();
  @override
  Future<AppSettings> load() async => saved;
  @override
  Future<void> save(AppSettings settings) async => saved = settings;
}

const _a = SongSection(id: 'a', name: 'A', startSeconds: 0, endSeconds: 10, trimEndSeconds: 1);
const _b = SongSection(id: 'b', name: 'B', startSeconds: 10, endSeconds: 20, trimStartSeconds: 2, loopCount: 2);
const _c = SongSection(id: 'c', name: 'C', startSeconds: 25, endSeconds: 30, trimEndSeconds: 0.5);

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  mockBackgroundChannel();

  test('section trims: JSON, play bounds, validation and merged areas', () {
    final back = SongSection.fromJson(jsonDecode(jsonEncode(_b.toJson())) as Map<String, dynamic>);
    expect(back, _b);
    expect((_b.playStart, _b.playEnd), (12.0, 20.0));
    expect(SongSection.fromJson({'id': 'x', 'name': 'x', 'startSeconds': 0, 'endSeconds': 1}).trimStartSeconds, 0);
    expect(const SongSection(id: 'x', name: 'x', startSeconds: 0, endSeconds: 1, trimStartSeconds: 0.6, trimEndSeconds: 0.4).isValid, false);
    expect(const SongSection(id: 'x', name: 'x', startSeconds: 0, endSeconds: 1, trimStartSeconds: -1).isValid, false);
    expect(SongSection.trimAreas([_a, _b, _c]), [(9.0, 12.0), (29.5, 30.0)]);
    expect(SongSection.trimAreas(const []), isEmpty);
  });

  group('providers', () {
    test('load and section edits send the trimmed areas; loops use the played part', () async {
      final engine = FakeEngine();
      final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine)]);
      addTearDown(c.dispose);
      final n = c.read(currentTrackProvider.notifier);
      expect(await n.load(sampleTrack(id: 's').copyWith(sections: [_a, _b])), true);
      expect(engine.skipAreas, [(9.0, 12.0)]);
      expect(await n.setSectionLoop(_b), true);
      expect(engine.calls, contains('loop(12.0,20.0,true,x2)'));
      expect(n.updateSections('s', [_a, _b, _c]), true);
      await n.refreshGuides();
      expect(engine.skipAreas, [(9.0, 12.0), (29.5, 30.0)]);
    });

    test('the transport reports the loop pass', () async {
      final engine = FakeEngine()..pass = (2, 4);
      final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine)]);
      addTearDown(c.dispose);
      c.read(transportProvider.notifier).refresh();
      expect((c.read(transportProvider).loopPass, c.read(transportProvider).loopRepeats), (2, 4));
    });
  });

  testWidgets('performance header shows the loop pass', (tester) async {
    tester.view.physicalSize = const Size(390, 844);
    tester.view.devicePixelRatio = 1;
    addTearDown(tester.view.resetPhysicalSize);
    addTearDown(tester.view.resetDevicePixelRatio);
    final engine = FakeEngine()..pass = (3, 0);
    final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine), persistenceServiceProvider.overrideWithValue(InMemoryPersistence())]);
    addTearDown(c.dispose);
    c.read(currentTrackProvider.notifier).setLoadedTrack(sampleTrack(id: 'song'));
    await tester.pumpWidget(UncontrolledProviderScope(container: c, child: const MaterialApp(home: PerformanceScreen())));
    await tester.pump(const Duration(milliseconds: 150));
    expect(find.text('Laço 3'), findsOneWidget);
    engine.pass = (1, 2);
    await tester.pump(const Duration(milliseconds: 150));
    expect(find.text('Laço 1/2'), findsOneWidget);
    expect(tester.takeException(), isNull);
    await tester.pumpWidget(const SizedBox.shrink());
    c.dispose();
  });

  group('custom sound directories', () {
    test('click families need all four voices; guides add to and override the bundled catalog', () async {
      final dir = await Directory.systemTemp.createTemp('custom-sounds-');
      addTearDown(() => dir.delete(recursive: true));
      for (final v in ['accents', 'quarter', 'eighth', 'sixteenth']) {
        writeSineWav('${dir.path}/Wood-$v.wav', seconds: 0.05);
      }
      writeSineWav('${dir.path}/Half-accents.wav', seconds: 0.05);
      File('${dir.path}/notes.txt').writeAsStringSync('x');
      final clicks = ClickResourceService(directoryResolver: () async => dir)..customDirectory = dir.path;
      expect(clicks.customFamilies().keys, ['Wood']);
      final families = await clicks.families();
      expect(families.last, 'custom:Wood');
      expect(families, contains('Saw'));
      final paths = await clicks.prepare('custom:Wood');
      expect(paths.first, '${dir.path}/Wood-accents.wav');
      await expectLater(clicks.prepare('custom:Half'), throwsFormatException);

      writeSineWav('${dir.path}/guidecue-section-pt-male-Refrao.wav', seconds: 0.1);
      writeSineWav('${dir.path}/guidecue-count-en-female-1.wav', seconds: 0.1);
      final guides = GuideResourceService(directoryResolver: () async => dir)..customDirectory = dir.path;
      final catalog = await guides.resources();
      expect(catalog.length, 542, reason: '541 bundled, one replaced, one added');
      expect(catalog.where((r) => r['name'] == 'guidecue-count-en-female-1').single['path'], '${dir.path}/guidecue-count-en-female-1.wav');
      final prepared = await guides.prepare(['guidecue-section-pt-male-Refrao']);
      expect(prepared.single, '${dir.path}/guidecue-section-pt-male-Refrao.wav');
      guides.customDirectory = '${dir.path}/missing';
      expect((await guides.resources()).length, 541);
    });

    test('settings round-trip the directories and push them into the services', () async {
      const settings = AppSettings(customClicksDirectory: '/c', customGuidesDirectory: '/g');
      expect(AppSettings.fromJson(jsonDecode(jsonEncode(settings.toJson()))), settings);
      expect(AppSettings.fromJson({'customClicksDirectory': ''}).customClicksDirectory, isNull);
      expect(settings.copyWith(customGuidesDirectory: null).customGuidesDirectory, isNull);
      final prefs = _Prefs()..saved = settings;
      final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(FakeEngine()), appPreferencesProvider.overrideWithValue(prefs)]);
      addTearDown(c.dispose);
      c.read(appSettingsProvider);
      await Future<void>.delayed(Duration.zero);
      expect(c.read(clickResourceServiceProvider).customDirectory, '/c');
      expect(c.read(guideResourceServiceProvider).customDirectory, '/g');
      await c.read(appSettingsProvider.notifier).apply(const AppSettings());
      expect(c.read(guideResourceServiceProvider).customDirectory, isNull);
    });

    testWidgets('settings screen validates and saves a directory', (tester) async {
      final dir = Directory.systemTemp.createTempSync('custom-dir-ui-');
      addTearDown(() => dir.deleteSync(recursive: true));
      final prefs = _Prefs();
      final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(FakeEngine()), appPreferencesProvider.overrideWithValue(prefs)]);
      addTearDown(c.dispose);
      await tester.pumpWidget(UncontrolledProviderScope(container: c, child: const MaterialApp(home: SettingsScreen())));
      await tester.pumpAndSettle();
      await tester.tap(find.byKey(const Key('custom-guides')));
      await tester.pumpAndSettle();
      await tester.enterText(find.byKey(const Key('directory-path')), '${dir.path}/nope');
      await tester.tap(find.text('Salvar'));
      await tester.pumpAndSettle();
      expect(find.text('Pasta não encontrada.'), findsOneWidget);
      expect(prefs.saved.customGuidesDirectory, isNull);
      await tester.tap(find.byKey(const Key('custom-guides')));
      await tester.pumpAndSettle();
      await tester.enterText(find.byKey(const Key('directory-path')), dir.path);
      await tester.tap(find.text('Salvar'));
      await tester.pumpAndSettle();
      expect(prefs.saved.customGuidesDirectory, dir.path);
    });
  });

  test('native FFI: trimmed areas validate and the loop pass reads back', () async {
    final dir = await Directory.systemTemp.createTemp('trim-ffi-');
    addTearDown(() => dir.delete(recursive: true));
    final song = writeSineWav('${dir.path}/song.wav', seconds: 4);
    final engine = WTracksEngine()..initialise();
    addTearDown(engine.shutdown);
    expect(await engine.loadTrackAsync('trim-ffi', [song.path]), true, reason: engine.lastError);
    expect(await engine.configureSkipsAsync([(1.0, 1.5), (2.0, 2.5)]), true, reason: engine.lastError);
    expect(engine.configureSkips([(2.0, 1.0)]), false);
    expect(engine.configureSkips([(3.0, 9.0)]), false);
    engine.seekToSeconds(1.2);
    expect(engine.currentPositionSeconds, closeTo(1.5, 1e-6));
    expect(engine.loopPass, (0, 0));
    expect(await engine.setLoopAsync(0, 1, true, repeats: 3), true);
    expect(engine.loopPass, (1, 3));
  }, skip: !nativeEngineAvailable() ? 'Native library unavailable' : false);
}
