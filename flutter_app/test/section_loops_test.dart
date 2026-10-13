import 'dart:async';
import 'dart:io';
import 'package:flutter_app/native/wtracks_bindings.dart';
import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_app/models/song_section.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/screens/section_editor_screen.dart';
import 'harness/harness_support.dart';

class DelayedLoopEngine extends FakeEngine {
  final entered = Completer<void>();
  final release = Completer<void>();
  @override
  Future<bool> setLoopAsync(double start, double end, bool enabled) async {
    entered.complete(); await release.future;
    return super.setLoopAsync(start, end, enabled);
  }
}

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  const intro = SongSection(id: 'intro', name: 'Intro', startSeconds: 2, endSeconds: 5);
  const verse = SongSection(id: 'verse', name: 'Verse', startSeconds: 5, endSeconds: 10);
  test('failed activation/queue preserves native selection and never auto plays', () async {
    final engine = FakeEngine();
    final container = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine)]);
    addTearDown(container.dispose);
    final current = container.read(currentTrackProvider.notifier);
    current.setLoadedTrack(const Track(id: 'song', title: 'Song', channels: [], sections: [intro, verse]));
    expect(await current.setSectionLoop(intro), true);
    expect(container.read(transportProvider).activeSection(intro), true);
    expect(engine.position, 2);
    expect(engine.playing, false);
    expect(await current.setSectionLoop(verse, queue: true), true);
    expect(container.read(transportProvider).queuedSection(verse), true);
    engine.failLoop = true;
    expect(await current.setSectionLoop(verse), false);
    expect(container.read(transportProvider).activeSection(intro), true);
    expect(container.read(transportProvider).queuedSection(verse), true);
    expect(await current.setSectionLoop(intro, queue: true), false);
    expect(container.read(transportProvider).queuedSection(verse), true);
    expect(engine.calls, isNot(contains('play')));
    await container.read(transportProvider.notifier).stop();
    expect(container.read(transportProvider).loopEnabled, false);
    expect(container.read(transportProvider).queuedLoopEnabled, false);
  });
  test('shared snapshot promotion updates active section and mutation clears stale caches', () async {
    final engine = FakeEngine();
    final container = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine)]);
    addTearDown(container.dispose);
    final current = container.read(currentTrackProvider.notifier);
    current.setLoadedTrack(const Track(id: 'song', title: 'Song', channels: [], sections: [intro, verse]));
    await current.setSectionLoop(intro);
    await current.setSectionLoop(verse, queue: true);
    expect(current.updateSections('song', [intro]), true);
    expect(engine.loopEnabled, true);
    expect(engine.queuedLoopEnabled, false);
    current.updateSections('song', [intro, verse]);
    await current.setSectionLoop(verse, queue: true);
    engine.loopStart = 5; engine.loopEnd = 10; engine.clearQueuedLoop();
    container.read(transportProvider.notifier).refresh();
    expect(container.read(transportProvider).activeSection(verse), true);
    expect(current.updateSections('song', [intro]), true);
    expect(engine.loopEnabled, false);
    expect(container.read(transportProvider).loopEnabled, false);
  });
  testWidgets('loop failure displays message and section controls fit compact screen', (tester) async {
    tester.view.physicalSize = const Size(360, 640);
    tester.view.devicePixelRatio = 1;
    addTearDown(tester.view.resetPhysicalSize); addTearDown(tester.view.resetDevicePixelRatio);
    final engine = FakeEngine();
    final container = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine)]);
    container.read(currentTrackProvider.notifier).setLoadedTrack(const Track(id: 'song', title: 'Song', channels: [], sections: [intro, verse]));
    await tester.pumpWidget(UncontrolledProviderScope(container: container,
      child: const MaterialApp(home: SectionEditorScreen(trackId: 'song'))));
    await tester.tap(find.byTooltip('Repetir Intro'));
    await tester.pumpAndSettle();
    expect(container.read(transportProvider).activeSection(intro), true);
    engine.failLoop = true;
    await tester.tap(find.byTooltip('Repetir Verse'));
    await tester.pumpAndSettle();
    expect(find.text('Não foi possível preparar o loop desta seção.'), findsOneWidget);
    expect(container.read(transportProvider).activeSection(intro), true);
    expect(engine.calls, isNot(contains('play')));
    expect(tester.takeException(), null);
    await tester.pumpWidget(const SizedBox.shrink()); container.dispose();
  });
  test('real loop ABI retains failed bounds and clears shared snapshot on stop', () async {
    final directory = await Directory.systemTemp.createTemp('loop-ffi-');
    addTearDown(() => directory.delete(recursive: true));
    final audio = writeSineWav('${directory.path}/song.wav', seconds: 2);
    final engine = WTracksEngine();
    engine.initialise();
    addTearDown(engine.shutdown);
    expect(await engine.loadTrackAsync('loop-ffi', [audio.path]), true, reason: engine.lastError);
    expect(await engine.setLoopAsync(0.25, 0.5, true), true, reason: engine.lastError);
    final active = engine.loopState;
    expect(active[0], 1);
    expect(active[1], closeTo(0.25, 0.001));
    expect(active[2], closeTo(0.5, 0.001));
    expect(engine.isPlaying, false);
    expect(await engine.enqueueLoopAsync(0.75, 1), true);
    final queued = engine.loopState;
    expect(queued[3], 1);
    expect(await engine.enqueueLoopAsync(1.5, 3), false);
    expect(engine.loopState, queued);
    expect(await engine.setLoopAsync(0.5, 3, true), false);
    expect(engine.loopState, queued);
    engine.stop();
    expect(engine.loopState, [0, 0, 0, 0, 0, 0]);
    expect(engine.underrunCount, greaterThanOrEqualTo(0));
  }, skip: !nativeEngineAvailable() ? 'Native library unavailable' : false);

  test('stop during preparation discards late loop selection', () async {
    final engine = DelayedLoopEngine();
    final container = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine)]);
    addTearDown(container.dispose);
    final current = container.read(currentTrackProvider.notifier);
    current.setLoadedTrack(const Track(id: 'song', title: 'Song', channels: [], sections: [intro]));
    final preparing = current.setSectionLoop(intro);
    await engine.entered.future;
    await container.read(transportProvider.notifier).stop();
    engine.release.complete();
    expect(await preparing, false);
    expect(engine.loopEnabled, false);
    expect(container.read(transportProvider).loopEnabled, false);
    expect(engine.calls, isNot(contains('play')));
  });

}
