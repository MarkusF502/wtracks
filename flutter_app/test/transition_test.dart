import 'dart:async';
import 'dart:convert';
import 'dart:io';

import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/song_section.dart';
import 'package:flutter_app/models/tempo_change.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/native/wtracks_bindings.dart';
import 'package:flutter_app/providers/control_provider.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/providers/transition_provider.dart';
import 'package:flutter_app/screens/performance_screen.dart';
import 'package:flutter_app/services/click_grid.dart';
import 'package:flutter_app/services/diagnostics_log.dart';
import 'harness/harness_support.dart';

/// Transições entre músicas (Fase 2): modelo, janela, ciclo de pré-carga/agendamento/hand-off e o crossfade ao vivo.
void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  mockBackgroundChannel();

  group('model', () {
    test('six transitions in the Playback order; pad only follows 0, 4 and 5; legacy files read as before', () {
      expect(SongTransition.values.map((t) => t.name),
          ['cueNextSong', 'autoLink', 'overlap', 'crossfade', 'stayInSong', 'cueFirstSong']);
      expect(SongTransition.values.where((t) => t.continuesPad), [SongTransition.cueNextSong, SongTransition.stayInSong, SongTransition.cueFirstSong]);
      expect(SongTransition.values.where((t) => t.isMixed), [SongTransition.autoLink, SongTransition.overlap, SongTransition.crossfade]);
      expect(SongTransition.values.where((t) => t.hasWindow), [SongTransition.overlap, SongTransition.crossfade]);
      expect(SongTransition.parse('stayInSong'), SongTransition.stayInSong);
      expect(SongTransition.parse('segue'), SongTransition.cueNextSong);
      for (final t in SongTransition.values) {
        final track = sampleTrack(id: 'x').copyWith(transition: t);
        expect(Track.fromJson(jsonDecode(jsonEncode(track.toJson())) as Map<String, dynamic>).transition, t);
      }
    });

    test('the end fade is not sent to the engine when the song crosses into the next', () async {
      final engine = FakeEngine();
      final c = _container(engine, FakeEngine(deck: 1), []);
      final n = c.read(currentTrackProvider.notifier);
      expect(await n.load(sampleTrack(id: 's').copyWith(endFade: true)), true);
      expect(engine.endFadeSeconds, 5);
      n.setTransition(SongTransition.crossfade);
      expect(engine.endFadeSeconds, 0);
      n.setTransition(SongTransition.overlap);
      expect(engine.endFadeSeconds, 5);
    });
  });

  group('window and click grid', () {
    Track next(List<SongSection> sections) => sampleTrack(id: 'n').copyWith(sections: sections);
    SongSection section(double start, double end) => SongSection(id: 's$start', name: 'S', startSeconds: start, endSeconds: end);
    final controller = ProviderContainer().read(transitionProvider.notifier);

    test('AutoLink starts the next song 64 ms before the end; Overlap and Crossfade use 5 s unless the next first section is shorter', () {
      var w = controller.windowFor(SongTransition.autoLink, 100, next([]));
      expect((w.start, w.duration, w.kind), (100 - 0.064, 0.064, 0));
      w = controller.windowFor(SongTransition.overlap, 100, next([section(0, 30)]));
      expect((w.start, w.duration, w.kind), (95.0, 5.0, 0));
      w = controller.windowFor(SongTransition.crossfade, 100, next([section(0, 3), section(3, 40)]));
      expect((w.start, w.duration, w.kind), (97.0, 3.0, 1));
      w = controller.windowFor(SongTransition.crossfade, 100, next([]));
      expect((w.start, w.duration), (95.0, 5.0));
    });

    test('the click grid follows the base segment and the tempo changes', () {
      final grid = ClickGrid.of(const ClickSettings(bpm: 120, beatOffsetSeconds: 0.5),
          [const TempoChange(id: 'a', startSeconds: 10.2, bpm: 60)]);
      expect(grid.nextBeatAtOrAfter(0), 0.5);
      expect(grid.nextBeatAtOrAfter(0.5), 0.5);
      expect(grid.nextBeatAtOrAfter(0.51), 1.0);
      expect(grid.nextBeatAtOrAfter(10.0), 10.0);
      expect(grid.nextBeatAtOrAfter(10.1), 10.2); // the next segment begins before the next beat of the old one
      expect(grid.nextBeatAtOrAfter(10.21), 11.2);
    });

    test('live crossfade: 2 bars of the next song, starting a sixteenth before the next click at least 0.15 s ahead', () {
      expect(TransitionController.liveDuration(sampleTrack(id: 'n', click: const ClickSettings(bpm: 120))), 4.0);
      expect(TransitionController.liveDuration(sampleTrack(id: 'n', click: const ClickSettings(bpm: 90, timeSignatureNumerator: 3))), closeTo(4.0, 1e-9));
      final current = sampleTrack(id: 'c', click: const ClickSettings(bpm: 120));
      expect(TransitionController.liveStart(current, 10.03), closeTo(10.5 - 0.125, 1e-9));
      expect(TransitionController.liveStart(current, 10.4), closeTo(11.0 - 0.125, 1e-9));
    });
  });

  group('controller', () {
    late FakeEngine main, deck1;
    late ProviderContainer c;
    late List<Track> tracks;

    Future<void> start(SongTransition transition, {int count = 3, Map<int, SongTransition> overrides = const {}}) async {
      main = FakeEngine()..playing = true..length = 100;
      deck1 = FakeEngine(deck: 1);
      tracks = [
        for (var i = 0; i < count; i++)
          sampleTrack(id: 't$i', title: 'T$i').copyWith(transition: overrides[i] ?? (i == 0 ? transition : SongTransition.cueNextSong)),
      ];
      c = _container(main, deck1, tracks);
      await c.read(trackLibraryProvider.notifier).refresh();
      final setlist = Setlist(id: 'set', name: 'Culto', tracks: tracks);
      expect(await c.read(currentTrackProvider.notifier).load(tracks[0]), true);
      c.read(setlistSessionProvider.notifier).begin(setlist, 0);
      main.playing = true; // loading a song stops the transport; the test plays it
      main.calls.clear();
    }

    Future<void> settle() async {
      await Future<void>.delayed(const Duration(milliseconds: 30));
      for (var i = 0; i < 300 && c.read(transitionProvider).phase == TransitionPhase.preparing; i++) {
        await Future<void>.delayed(const Duration(milliseconds: 10));
      }
      await Future<void>.delayed(const Duration(milliseconds: 30));
    }

    test('nothing is preloaded early; the next song loads on deck 1 and the window is armed', () async {
      await start(SongTransition.overlap);
      final controller = c.read(transitionProvider.notifier);
      main.position = 50;
      controller.tick();
      expect(c.read(transitionProvider).phase, TransitionPhase.idle);
      expect(deck1.loadedPaths, isEmpty);

      main.position = 76; // 100 - 5 - 20 = 75
      controller.tick();
      expect(c.read(transitionProvider).phase, TransitionPhase.preparing);
      await settle();
      expect(c.read(transitionProvider).phase, TransitionPhase.armed);
      expect(deck1.loadedPaths.single.first, contains('t1'));
      expect(c.read(nextTrackProvider)!.id, 't1');
      expect(main.calls, contains('schedule(0,95.000,5.000)'));
      expect(main.calls.contains('stop'), false, reason: 'preloading never stops the song that plays');
      expect(deck1.calls.contains('play'), false);
      controller.tick(); // armed: nothing else happens
      expect(main.calls.where((e) => e.startsWith('schedule')).length, 1);
    });

    test('Crossfade schedules kind 1 and AutoLink a 64 ms Overlap', () async {
      await start(SongTransition.crossfade);
      main.position = 80;
      c.read(transitionProvider.notifier).tick();
      await settle();
      expect(main.calls, contains('schedule(1,95.000,5.000)'));

      await start(SongTransition.autoLink);
      main.position = 80;
      c.read(transitionProvider.notifier).tick();
      await settle();
      expect(main.calls, contains('schedule(0,99.936,0.064)'));
    });

    test('started, finished, then the hand-off: the next song becomes the current one', () async {
      await start(SongTransition.crossfade);
      final controller = c.read(transitionProvider.notifier);
      main.position = 80;
      controller.tick();
      await settle();
      expect(controller.handleEvents(WTracksEngine.transportEventTransitionStarted), false);
      expect(c.read(transitionProvider).phase, TransitionPhase.running);
      // the outgoing song reaching its end while the mix runs is not a song end
      expect(controller.handleEvents(WTracksEngine.transportEventEndReached), true);
      expect(c.read(currentTrackProvider)!.id, 't0');

      expect(controller.handleEvents(WTracksEngine.transportEventTransitionFinished), true);
      await settle();
      expect(main.calls, contains('handoff'));
      expect(c.read(currentTrackProvider)!.id, 't1');
      expect(c.read(setlistSessionProvider)!.index, 1);
      expect(c.read(transitionProvider).phase, TransitionPhase.idle);
      expect(c.read(nextTrackProvider), isNull);
      expect(deck1.calls, contains('unload'), reason: 'the song that left is released from deck 1');
    });

    test('started and finished in the same poll still hand off once', () async {
      await start(SongTransition.overlap);
      final controller = c.read(transitionProvider.notifier);
      main.position = 80;
      controller.tick();
      await settle();
      expect(controller.handleEvents(WTracksEngine.transportEventTransitionStarted | WTracksEngine.transportEventTransitionFinished | WTracksEngine.transportEventEndReached), true);
      await settle();
      expect(main.calls.where((e) => e == 'handoff').length, 1);
      expect(c.read(setlistSessionProvider)!.index, 1);
    });

    test('a failed preload is reported once and the song end falls back to playing the next one', () async {
      await start(SongTransition.autoLink);
      deck1.failNextLoad = true;
      main.position = 80;
      final controller = c.read(transitionProvider.notifier);
      controller.tick();
      await settle();
      expect(c.read(transitionProvider).phase, TransitionPhase.idle);
      expect(c.read(diagnosticsProvider).where((e) => e.error).single.message, contains('pré-carregar'));
      controller.tick();
      await settle();
      expect(deck1.loadedPaths.length, 1, reason: 'no retry loop for the same plan');

      final warned = c.read(transitionProvider).notice!;
      expect(warned.kind, TransitionNoticeKind.preloadFailed, reason: 'visible on stage, not only in the diagnostics');
      expect(warned.message, contains('T1'));

      // the song ends with no second deck ready: the next song is loaded and plays
      expect(controller.handleEvents(WTracksEngine.transportEventEndReached), false);
      await c.read(setlistSessionProvider.notifier).songFinished();
      expect(c.read(currentTrackProvider)!.id, 't1');
      expect(main.calls, contains('play'));
      final cut = c.read(transitionProvider).notice!;
      expect(cut.kind, TransitionNoticeKind.cutIn);
      expect(cut.message, allOf(contains('T1'), contains('não pôde ser preparada'), contains('corte')));
      controller.tick();
      expect(c.read(transitionProvider).notice, cut, reason: 'stays while the song it is about plays');
      controller.dismissNotice();
      expect(c.read(transitionProvider).notice, isNull);
    });

    test('a preload still loading when the song ends: the next one cuts in and the stage says so', () async {
      await start(SongTransition.crossfade);
      deck1.loadGate = Completer<void>();
      main.position = 80;
      final controller = c.read(transitionProvider.notifier);
      controller.tick();
      await Future<void>.delayed(const Duration(milliseconds: 30));
      expect(c.read(transitionProvider).phase, TransitionPhase.preparing);

      expect(controller.handleEvents(WTracksEngine.transportEventEndReached), false);
      await c.read(setlistSessionProvider.notifier).songFinished();
      deck1.loadGate!.complete();
      await settle();
      expect(c.read(currentTrackProvider)!.id, 't1');
      expect(main.calls, contains('play'));
      expect(main.calls.where((e) => e.startsWith('schedule')), isEmpty, reason: 'the late preload never arms');
      expect(c.read(nextTrackProvider), isNull);
      expect(c.read(transitionProvider).phase, TransitionPhase.idle);
      expect(c.read(transitionProvider).notice!.message, contains('não ficou pronta a tempo'));
    });

    test('the next song that does not load even with a cut leaves the setlist stopped with a red notice', () async {
      await start(SongTransition.overlap);
      deck1.failNextLoad = true;
      main.position = 80;
      final controller = c.read(transitionProvider.notifier);
      controller.tick();
      await settle();
      main.failNextLoad = true;
      main.calls.clear();
      await c.read(setlistSessionProvider.notifier).songFinished();
      expect(main.calls.contains('play'), false);
      expect(c.read(setlistSessionProvider)!.index, 0);
      expect(c.read(transitionProvider).notice!.kind, TransitionNoticeKind.nextFailed);
      expect(c.read(diagnosticsProvider).last.message, contains('setlist ficou parada'));

      // Preparar próxima música: a next song that fails is reported too; one that loads (stopped) says nothing
      await start(SongTransition.cueNextSong);
      main.failNextLoad = true;
      await c.read(setlistSessionProvider.notifier).songFinished();
      expect(c.read(transitionProvider).notice!.kind, TransitionNoticeKind.nextFailed);
      await start(SongTransition.cueNextSong);
      await c.read(setlistSessionProvider.notifier).songFinished();
      expect(c.read(currentTrackProvider)!.id, 't1');
      expect(c.read(transitionProvider).notice, isNull);
    });

    test('a failed hand-off does not leave the stage silent: the next song cuts in', () async {
      await start(SongTransition.overlap);
      final controller = c.read(transitionProvider.notifier);
      main.position = 80;
      controller.tick();
      await settle();
      main.handoffFails = true;
      expect(controller.handleEvents(WTracksEngine.transportEventTransitionStarted | WTracksEngine.transportEventTransitionFinished), true);
      await settle();
      expect(c.read(currentTrackProvider)!.id, 't1');
      expect(c.read(setlistSessionProvider)!.index, 1);
      expect(main.calls, contains('play'));
      expect(c.read(transitionProvider).notice!.message, contains('não completou a transição'));

      // the next transition that arms clears the old notice
      c.read(currentTrackProvider.notifier).setTransition(SongTransition.overlap);
      main.playing = true;
      main.position = 80;
      controller.tick();
      await settle();
      expect(c.read(transitionProvider).phase, TransitionPhase.armed);
      expect(c.read(transitionProvider).notice, isNull);
    });

    test('an active loop holds the preload; stopping or editing the setlist cancels an armed transition', () async {
      await start(SongTransition.overlap);
      final controller = c.read(transitionProvider.notifier);
      main.position = 80;
      main.loopEnabled = true;
      controller.tick();
      expect(c.read(transitionProvider).phase, TransitionPhase.idle);
      main.loopEnabled = false;
      controller.tick();
      await settle();
      expect(c.read(transitionProvider).phase, TransitionPhase.armed);

      main.scheduled = false; // the engine dropped it (stop); the transport's own 100 ms tick must not prepare it again meanwhile
      main.playing = false;
      controller.tick();
      await settle();
      expect(c.read(transitionProvider).phase, TransitionPhase.idle);
      expect(c.read(nextTrackProvider), isNull);

      main.playing = true; // playing again at 80: prepared again
      controller.tick();
      await settle();
      expect(c.read(transitionProvider).phase, TransitionPhase.armed);
      await c.read(setlistSessionProvider.notifier).removeAt(1); // the song after the current one changes
      controller.tick();
      await settle();
      expect(main.calls.where((e) => e == 'cancelTransition'), isNotEmpty);
      controller.tick();
      await settle();
      expect(deck1.loadedPaths.last.first, contains('t2'));
    });

    test('loading another song cancels the preparation', () async {
      await start(SongTransition.overlap);
      main.position = 80;
      c.read(transitionProvider.notifier).tick();
      await settle();
      expect(c.read(transitionProvider).phase, TransitionPhase.armed);
      expect(await c.read(currentTrackProvider.notifier).load(sampleTrack(id: 'z')), true);
      await settle();
      expect(c.read(transitionProvider).phase, TransitionPhase.idle);
      expect(main.calls, contains('cancelTransition'));
    });

    test('Cue First Song returns to the first song (stopped); on the first song it only rewinds; the last song stays when it has no next', () async {
      await start(SongTransition.cueNextSong, overrides: {2: SongTransition.cueFirstSong});
      await c.read(setlistSessionProvider.notifier).go(2);
      main.calls.clear();
      await c.read(setlistSessionProvider.notifier).songFinished();
      expect(c.read(currentTrackProvider)!.id, 't0');
      expect(c.read(setlistSessionProvider)!.index, 0);

      await start(SongTransition.cueFirstSong);
      await c.read(setlistSessionProvider.notifier).songFinished();
      expect(c.read(currentTrackProvider)!.id, 't0');
      expect(main.calls, contains('stop'));

      await start(SongTransition.crossfade, count: 1);
      main.position = 90;
      c.read(transitionProvider.notifier).tick();
      await settle();
      expect(c.read(transitionProvider).phase, TransitionPhase.idle, reason: 'nothing follows the last song');
    });

    test('live crossfade: loads the target on deck 1 and starts on the click grid', () async {
      await start(SongTransition.stayInSong);
      main.position = 10.03;
      expect(await c.read(transitionProvider.notifier).liveCrossfade(2), true);
      expect(c.read(transitionProvider), const TransitionState(phase: TransitionPhase.armed, nextIndex: 2, live: true));
      // sampleTrack: 72 bpm click -> the next beat at or after 10.18 s is 10.833 s; a sixteenth earlier
      final beat = 60 / 72;
      final expectedStart = (10.18 / beat).ceil() * beat - beat / 4;
      expect(main.scheduledKind, 1);
      expect(main.scheduledStart, closeTo(expectedStart, 1e-3));
      expect(main.scheduledDuration, closeTo(2 * 4 * beat, 1e-3));
      expect(deck1.loadedPaths.single.first, contains('t2'));

      c.read(transitionProvider.notifier).tick(); // stays armed
      expect(c.read(transitionProvider).phase, TransitionPhase.armed);
      c.read(transitionProvider.notifier).handleEvents(WTracksEngine.transportEventTransitionStarted);
      c.read(transitionProvider.notifier).handleEvents(WTracksEngine.transportEventTransitionFinished);
      await settle();
      expect(c.read(currentTrackProvider)!.id, 't2');
      expect(c.read(setlistSessionProvider)!.index, 2);
    });

    test('live crossfade needs playback, a different song and no mix already running', () async {
      await start(SongTransition.stayInSong);
      final controller = c.read(transitionProvider.notifier);
      expect(await controller.liveCrossfade(0), false);
      expect(await controller.liveCrossfade(7), false);
      main.playing = false;
      expect(await controller.liveCrossfade(1), false);
      main.playing = true;
      expect(await controller.liveCrossfade(1), true);
      controller.handleEvents(WTracksEngine.transportEventTransitionStarted);
      expect(await controller.liveCrossfade(2), false);
    });

    test('keys 1..9 without a mapping: crossfade to that song while playing, load it when stopped', () async {
      await start(SongTransition.stayInSong);
      expect(c.read(controlProvider.notifier).handleKey('2'), true);
      await settle();
      await settle();
      expect(main.scheduledKind, 1);
      expect(c.read(transitionProvider).nextIndex, 1);
      expect(c.read(controlProvider.notifier).handleKey('9'), false);
      c.read(transitionProvider.notifier).cancel();
      await settle();
      main.playing = false;
      expect(c.read(controlProvider.notifier).handleKey('3'), true);
      await settle();
      await settle();
      expect(c.read(currentTrackProvider)!.id, 't2');
    });
  });

  testWidgets('the stage shows the transition notice until it is closed', (tester) async {
    tester.view.physicalSize = const Size(390, 844);
    tester.view.devicePixelRatio = 1;
    addTearDown(tester.view.resetPhysicalSize);
    addTearDown(tester.view.resetDevicePixelRatio);
    final c = _container(FakeEngine(), FakeEngine(deck: 1), []);
    expect(await c.read(currentTrackProvider.notifier).load(sampleTrack(id: 's', title: 'Solo')), true);
    await tester.pumpWidget(UncontrolledProviderScope(container: c, child: const MaterialApp(home: PerformanceScreen())));
    await tester.pump(const Duration(milliseconds: 250));
    expect(find.byKey(const Key('transition-notice')), findsNothing);

    c.read(transitionProvider.notifier).reportFallback(sampleTrack(id: 'n', title: 'Próxima'), loaded: false, mixed: true);
    await tester.pump(const Duration(milliseconds: 250));
    expect(find.byKey(const Key('transition-notice')), findsOneWidget);
    expect(find.textContaining('"Próxima" não carregou'), findsOneWidget);
    await tester.tap(find.byTooltip('Fechar aviso'));
    await tester.pump(const Duration(milliseconds: 250));
    expect(find.byKey(const Key('transition-notice')), findsNothing);
    await tester.pumpWidget(const SizedBox.shrink());
    c.dispose();
  });

  group('native FFI', () {
    test('real ABI: two independent decks, validated windows and a hand-off that needs a playing incoming song', () async {
      final dir = await Directory.systemTemp.createTemp('transition-ffi-');
      addTearDown(() => dir.delete(recursive: true));
      final songA = writeSineWav('${dir.path}/a.wav', seconds: 2);
      final songB = writeSineWav('${dir.path}/b.wav', seconds: 1);
      final engine = WTracksEngine()..initialise();
      addTearDown(engine.shutdown);
      expect(engine.prepareNextDeck(), true);
      final next = WTracksEngine(deck: 1);
      expect(await engine.loadTrackAsync('a', [songA.path]), true, reason: engine.lastError);
      expect(await next.loadTrackAsync('b', [songB.path]), true, reason: next.lastError);
      expect(engine.totalLengthSeconds, closeTo(2, 0.01));
      expect(next.totalLengthSeconds, closeTo(1, 0.01));
      // The isolate-based calls address the deck of the object they are called on (an area past the 1 s of deck 1 is refused there,
      // while deck 0 with 2 s accepts it).
      expect(await next.configureSkipsAsync([(1.2, 1.8)]), false);
      expect(await engine.configureSkipsAsync([(1.2, 1.8)]), true);
      expect(await engine.configureSkipsAsync([]), true);
      expect(engine.scheduleTransition(1, 0.5, 0), false);
      expect(engine.scheduleTransition(1, 0.5, 61), false);
      expect(engine.scheduleTransition(1, 1.5, 0.5), true);
      expect(engine.transitionScheduled, true);
      expect(engine.transitionProgress, -1);
      expect(engine.handoff(), false); // the incoming song is not playing yet
      engine.cancelTransition();
      expect(engine.transitionScheduled, false);
      next.unloadTrack();
      expect(next.totalLengthSeconds, 0);
      expect(engine.totalLengthSeconds, closeTo(2, 0.01), reason: 'deck 0 is untouched by deck 1');
      engine.releaseNextDeck();
    }, skip: !nativeEngineAvailable() ? 'Native library unavailable' : false);
  });
}

ProviderContainer _container(FakeEngine main, FakeEngine deck1, List<Track> tracks) {
  final c = ProviderContainer(overrides: [
    engineProvider.overrideWithValue(main),
    nextEngineProvider.overrideWithValue(deck1),
    persistenceServiceProvider.overrideWithValue(InMemoryPersistence(initialTracks: tracks)),
  ]);
  addTearDown(c.dispose);
  return c;
}
