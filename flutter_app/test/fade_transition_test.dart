import 'dart:convert';
import 'dart:io';
import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/native/wtracks_bindings.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/screens/performance_screen.dart';
import 'package:flutter_app/screens/song_ending_sheet.dart';
import 'harness/harness_support.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  mockBackgroundChannel();

  test('tracks round-trip transition, end fade and fade exclusions; legacy files use the defaults', () {
    final base = sampleTrack(id: 's', channels: 2);
    final track = base.copyWith(
      transition: SongTransition.stayInSong,
      endFade: true,
      channels: [base.channels[0].copyWith(excludeFromFade: true), base.channels[1]],
    );
    final back = Track.fromJson(jsonDecode(jsonEncode(track.toJson())) as Map<String, dynamic>);
    expect(back.transition, SongTransition.stayInSong);
    expect(back.endFade, true);
    expect(back.channels.map((c) => c.excludeFromFade), [true, false]);
    final legacy = Track.fromJson({'id': 't', 'title': 'T', 'channels': <dynamic>[], 'transition': 'segue'});
    expect(legacy.transition, SongTransition.cueNextSong);
    expect(legacy.endFade, false);
  });

  group('providers', () {
    ProviderContainer container(FakeEngine engine, InMemoryPersistence persistence) {
      final c = ProviderContainer(overrides: [
        engineProvider.overrideWithValue(engine),
        persistenceServiceProvider.overrideWithValue(persistence),
      ]);
      addTearDown(c.dispose);
      return c;
    }

    test('load applies the end fade and exclusions; the setters reach the engine', () async {
      final engine = FakeEngine();
      final c = container(engine, InMemoryPersistence());
      final n = c.read(currentTrackProvider.notifier);
      final base = sampleTrack(id: 's', channels: 2);
      expect(await n.load(base.copyWith(endFade: true, channels: [base.channels[0], base.channels[1].copyWith(excludeFromFade: true)])), true);
      expect(engine.endFadeSeconds, 5);
      expect(engine.excludedFromFade, {1});
      n.setEndFade(false);
      n.setChannelExcludedFromFade(0, true);
      expect(engine.endFadeSeconds, 0);
      expect(engine.excludedFromFade, {0, 1});
      expect(c.read(currentTrackProvider)!.channels[0].excludeFromFade, true);
      n.setTransition(SongTransition.stayInSong);
      expect(c.read(currentTrackProvider)!.transition, SongTransition.stayInSong);
    });

    test('fade button needs playback; the transport reports the running fade', () async {
      final engine = FakeEngine();
      final c = container(engine, InMemoryPersistence());
      c.read(currentTrackProvider.notifier).setLoadedTrack(sampleTrack(id: 's'));
      final transport = c.read(transportProvider.notifier);
      expect(transport.fadeOut(), false);
      engine.playing = true;
      expect(transport.fadeOut(), true);
      expect(engine.calls, contains('fadeOut(5.0)'));
      expect(c.read(transportProvider).fading, true);
    });

    test('song end follows the transition: cue the next song, stay, or stop at the last one', () async {
      final engine = FakeEngine();
      final tracks = [
        sampleTrack(id: 'a', title: 'A'),
        sampleTrack(id: 'b', title: 'B').copyWith(transition: SongTransition.stayInSong),
        sampleTrack(id: 'c', title: 'C'),
      ];
      final setlist = Setlist(id: 'set', name: 'Culto', tracks: tracks);
      final persistence = InMemoryPersistence(initialTracks: tracks, initialSetlists: [setlist]);
      final c = container(engine, persistence);
      await c.read(trackLibraryProvider.notifier).refresh();
      final session = c.read(setlistSessionProvider.notifier);
      expect(await c.read(currentTrackProvider.notifier).load(tracks[0]), true);
      session.begin(setlist, 0);

      // The audio thread reports the end; the 100 ms transport tick picks it up.
      c.read(transportProvider);
      engine.pendingEvents = WTracksEngine.transportEventEndReached;
      await Future<void>.delayed(const Duration(milliseconds: 250));
      expect(c.read(currentTrackProvider)!.id, 'b');
      expect(c.read(setlistSessionProvider)!.index, 1);

      await session.songFinished(); // B stays
      expect(c.read(currentTrackProvider)!.id, 'b');

      // The library version wins over the copy held by the setlist.
      await c.read(trackLibraryProvider.notifier).setTransition('b', SongTransition.cueNextSong);
      expect(c.read(currentTrackProvider)!.transition, SongTransition.cueNextSong);
      expect((await persistence.loadTrack('b'))!.transition, SongTransition.cueNextSong);
      await session.songFinished();
      expect(c.read(currentTrackProvider)!.id, 'c');
      await session.songFinished(); // last song
      expect(c.read(currentTrackProvider)!.id, 'c');
      expect(await session.previous(), true);
      expect(c.read(currentTrackProvider)!.id, 'b');

      // A song opened outside the setlist does not move the setlist.
      expect(await c.read(currentTrackProvider.notifier).load(sampleTrack(id: 'z')), true);
      await session.songFinished();
      expect(c.read(currentTrackProvider)!.id, 'z');
    });
  });

  testWidgets('performance screen: setlist bar, fade button and the song-ending sheet', (tester) async {
    tester.view.physicalSize = const Size(390, 844);
    tester.view.devicePixelRatio = 1;
    addTearDown(tester.view.resetPhysicalSize);
    addTearDown(tester.view.resetDevicePixelRatio);
    final engine = FakeEngine()..playing = true;
    final tracks = [sampleTrack(id: 'a', title: 'Primeira'), sampleTrack(id: 'b', title: 'Segunda')];
    final persistence = InMemoryPersistence(initialTracks: tracks);
    final c = ProviderContainer(overrides: [
      engineProvider.overrideWithValue(engine),
      persistenceServiceProvider.overrideWithValue(persistence),
    ]);
    addTearDown(c.dispose);
    await c.read(trackLibraryProvider.notifier).refresh();
    c.read(currentTrackProvider.notifier).setLoadedTrack(tracks[0]);
    c.read(setlistSessionProvider.notifier).begin(Setlist(id: 's', name: 'S', tracks: tracks), 0);
    await tester.pumpWidget(UncontrolledProviderScope(container: c, child: const MaterialApp(home: PerformanceScreen())));
    await tester.pump(const Duration(milliseconds: 150));
    expect(find.text('Primeira (G)'), findsOneWidget); // a faixa da setlist mostra as duas músicas
    expect(find.text('Segunda (G)'), findsOneWidget);

    await tester.tap(find.byTooltip('Fade de 5 segundos'));
    await tester.pump(const Duration(milliseconds: 150));
    expect(engine.calls, contains('fadeOut(5.0)'));

    await tester.tap(find.byTooltip('Mais'));
    await tester.pumpAndSettle();
    await tester.tap(find.text('Editar música…'));
    await tester.pumpAndSettle();
    await tester.tap(find.text('Fim da música e fade'));
    for (var i = 0; i < 10; i++) {
      await tester.pump(const Duration(milliseconds: 100));
    }
    expect(find.byType(SongEndingSheet), findsOneWidget);
    await tester.tap(find.byKey(const Key('transition-stay')));
    await tester.tap(find.byKey(const Key('end-fade')));
    await tester.tap(find.byKey(const Key('exclude-fade-0')));
    await tester.pump(const Duration(milliseconds: 200));
    final track = c.read(currentTrackProvider)!;
    expect(track.transition, SongTransition.stayInSong);
    expect(track.endFade, true);
    expect(track.channels[0].excludeFromFade, true);
    expect(engine.endFadeSeconds, 5);
    expect(engine.excludedFromFade, {0});
    expect((await persistence.loadTrack('a'))!.endFade, true);
    await tester.pumpWidget(const SizedBox.shrink());
    c.dispose();
  });

  group('native FFI', () {
    test('real ABI: fade needs playback, end fade is validated, events start empty', () async {
      final dir = await Directory.systemTemp.createTemp('fade-ffi-');
      addTearDown(() => dir.delete(recursive: true));
      final song = writeSineWav('${dir.path}/song.wav', seconds: 2);
      final engine = WTracksEngine()..initialise();
      addTearDown(engine.shutdown);
      expect(await engine.loadTrackAsync('fade-ffi', [song.path]), true, reason: engine.lastError);
      expect(engine.startFadeOut(5), false);
      expect(engine.fadeGain, -1);
      expect(engine.setEndFade(5), true);
      expect(engine.setEndFade(-1), false);
      expect(engine.startFadeOut(0), false);
      engine.setChannelExcludedFromFade(0, true);
      expect(engine.pollTransportEvents(), 0);
      engine.cancelFadeOut();
    }, skip: !nativeEngineAvailable() ? 'Native library unavailable' : false);
  });
}
