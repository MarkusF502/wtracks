import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/screens/performance_screen.dart';
import 'package:flutter_app/screens/song_ending_sheet.dart';
import 'package:flutter_app/screens/song_range_sheet.dart';
import 'harness/harness_support.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  mockBackgroundChannel();

  Track roundTrip(Track t) => Track.fromJson(jsonDecode(jsonEncode(t.toJson())) as Map<String, dynamic>);

  test('custom start and end round-trip; legacy files and the defaults mean the whole file', () {
    final base = sampleTrack(id: 's', channels: 1);
    expect(base.startSeconds, isNull);
    expect(base.endSeconds, isNull);
    final track = base.copyWith(startSeconds: 4.5, endSeconds: 100);
    final back = roundTrip(track);
    expect(back.startSeconds, 4.5);
    expect(back.endSeconds, 100);
    expect(roundTrip(track.copyWith(startSeconds: null)).startSeconds, isNull);
    expect(roundTrip(track.copyWith(startSeconds: null)).endSeconds, 100);
    final legacy = Track.fromJson({'id': 't', 'title': 'T', 'channels': <dynamic>[]});
    expect(legacy.startSeconds, isNull);
    expect(legacy.endSeconds, isNull);
  });

  test('click and guide channels are inferred for old songs and stay out of the fade', () {
    final legacy = Track.fromJson({
      'id': 't',
      'title': 'T',
      'channels': [
        {'label': 'Click', 'filePath': '/a.wav'},
        {'label': 'Guia', 'filePath': '/b.wav'},
        {'label': 'Bateria', 'filePath': '/c.wav'},
      ],
    });
    expect(legacy.channels.map((c) => c.isClickOrGuide), [true, true, false]);
    expect(legacy.channels.map((c) => c.fadeExcluded), [true, true, false]);
    final saved = roundTrip(sampleTrack(id: 's', channels: 2).copyWith(
      channels: [const ChannelInfo(label: 'Pad', filePath: '/p.wav', isClickOrGuide: true), const ChannelInfo(label: 'Click', filePath: '/c.wav', isClickOrGuide: false)],
    ));
    expect(saved.channels.map((c) => c.isClickOrGuide), [true, false]); // the stored flag wins over the label
  });

  group('providers', () {
    ProviderContainer container(FakeEngine engine) {
      final c = ProviderContainer(overrides: [
        engineProvider.overrideWithValue(engine),
        persistenceServiceProvider.overrideWithValue(InMemoryPersistence()),
      ]);
      addTearDown(c.dispose);
      return c;
    }

    test('load applies the range and click/guide exclusions; setSongRange validates and updates the song', () async {
      final engine = FakeEngine();
      final c = container(engine);
      final base = sampleTrack(id: 's', channels: 3);
      final channels = [
        base.channels[0].copyWith(isClickOrGuide: true),
        base.channels[1],
        base.channels[2].copyWith(excludeFromFade: true),
      ];
      expect(await c.read(currentTrackProvider.notifier).load(base.copyWith(channels: channels, startSeconds: 3, endSeconds: 60)), true);
      expect(engine.playRange, (3.0, 60.0));
      expect(engine.excludedFromFade, {0, 2});
      final n = c.read(currentTrackProvider.notifier);
      expect(n.setSongRange(5, 4), false);
      expect(c.read(currentTrackProvider)!.startSeconds, 3);
      expect(n.setSongRange(null, null), true);
      expect(c.read(currentTrackProvider)!.startSeconds, isNull);
      expect(engine.playRange, (0.0, 0.0));
      expect(n.setSongRange(1, null), true);
      expect(c.read(currentTrackProvider)!.endSeconds, isNull);
      expect(engine.playRange, (1.0, 0.0));
      n.setChannelExcludedFromFade(0, false); // a click channel cannot be taken out of the exclusion
      expect(engine.excludedFromFade.contains(0), true);
    });

    test('a range the engine refuses falls back to the whole file instead of failing the load', () async {
      final engine = FakeEngine();
      final c = container(engine);
      expect(await c.read(currentTrackProvider.notifier).load(sampleTrack(id: 's').copyWith(startSeconds: 50, endSeconds: 10)), true);
      expect(engine.playRange, (0.0, 0.0));
    });
  });

  testWidgets('tapping the clock opens the start/end sheet and saves the position as a limit', (tester) async {
    tester.view.physicalSize = const Size(390, 844);
    tester.view.devicePixelRatio = 1;
    addTearDown(tester.view.resetPhysicalSize);
    addTearDown(tester.view.resetDevicePixelRatio);
    final engine = FakeEngine()..position = 12.34;
    final c = ProviderContainer(overrides: [
      engineProvider.overrideWithValue(engine),
      persistenceServiceProvider.overrideWithValue(InMemoryPersistence()),
    ]);
    addTearDown(c.dispose);
    expect(await c.read(currentTrackProvider.notifier).load(sampleTrack(id: 's', title: 'Solo')), true);
    await tester.pumpWidget(UncontrolledProviderScope(container: c, child: const MaterialApp(home: PerformanceScreen())));
    await tester.pump(const Duration(milliseconds: 250));
    await tester.tap(find.byTooltip('Início e fim da música'));
    await tester.pumpAndSettle();
    expect(find.byType(SongRangeSheet), findsOneWidget);
    await tester.tap(find.byKey(const Key('range-start-here')));
    await tester.pump(const Duration(milliseconds: 250));
    expect(c.read(currentTrackProvider)!.startSeconds, closeTo(12.34, 1e-9));
    expect(engine.playRange.$1, closeTo(12.34, 1e-9));
    await tester.tap(find.byKey(const Key('range-end-here'))); // the end cannot be before the start
    await tester.pump(const Duration(milliseconds: 250));
    expect(c.read(currentTrackProvider)!.endSeconds, isNull);
    expect(find.text('O fim precisa ser depois do início.'), findsOneWidget);
    await tester.tap(find.byKey(const Key('range-start-clear')));
    await tester.pump(const Duration(milliseconds: 250));
    expect(c.read(currentTrackProvider)!.startSeconds, isNull);
    await tester.pumpWidget(const SizedBox.shrink());
    c.dispose();
  });

  testWidgets('the fade sheet shows click and guide channels as always outside the fade', (tester) async {
    final engine = FakeEngine();
    final c = ProviderContainer(overrides: [
      engineProvider.overrideWithValue(engine),
      persistenceServiceProvider.overrideWithValue(InMemoryPersistence()),
    ]);
    addTearDown(c.dispose);
    final base = sampleTrack(id: 's', channels: 2);
    expect(await c.read(currentTrackProvider.notifier).load(base.copyWith(channels: [base.channels[0].copyWith(isClickOrGuide: true), base.channels[1]])), true);
    await tester.pumpWidget(UncontrolledProviderScope(container: c, child: const MaterialApp(home: Scaffold(body: SongEndingSheet()))));
    await tester.pump();
    expect(tester.widget<CheckboxListTile>(find.byKey(const Key('exclude-fade-0'))).value, true);
    expect(tester.widget<CheckboxListTile>(find.byKey(const Key('exclude-fade-0'))).onChanged, isNull);
    expect(tester.widget<CheckboxListTile>(find.byKey(const Key('exclude-fade-1'))).value, false);
    await tester.pumpWidget(const SizedBox.shrink());
    c.dispose();
  });
}
