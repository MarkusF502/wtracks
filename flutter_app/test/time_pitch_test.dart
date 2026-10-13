import 'dart:async';
import 'dart:convert';
import 'dart:io';
import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/time_pitch_settings.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/native/wtracks_bindings.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/screens/time_pitch_sheet.dart';
import 'package:flutter_app/services/time_pitch_service.dart';
import 'harness/harness_support.dart';

class FakeTimePitchService extends TimePitchService {
  FakeTimePitchService() : super(directoryResolver: () async => Directory.systemTemp);
  bool fail = false;
  final prepared = <TimePitchSettings>[];
  @override
  Future<List<String>> prepare(WTracksEngine engine, Track track, {void Function(double progress)? onProgress}) async {
    if (fail) throw const TimePitchFailure('boom');
    prepared.add(track.timePitch);
    onProgress?.call(0.5);
    return [for (var i = 0; i < track.channels.length; i++) '/processed/$i.wav'];
  }
}

Track _trackWith(Directory dir, {int channels = 2}) {
  final files = [
    for (var i = 0; i < channels; i++) File('${dir.path}/stem$i.wav')..writeAsBytesSync(List.filled(200, i)),
  ];
  return Track(id: 'song', title: 'Song', channels: [
    for (var i = 0; i < channels; i++) ChannelInfo(label: 'C$i', filePath: files[i].path),
  ]);
}

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  group('TimePitchSettings', () {
    test('factors, validation and persistence', () {
      const s = TimePitchSettings(semitones: 12, tempoRatio: 0.5);
      expect(s.pitchFactor, closeTo(2, 1e-12));
      expect(s.timeFactor, 2);
      expect(const TimePitchSettings().isIdentity, true);
      expect(const TimePitchSettings(semitones: -12).pitchFactor, closeTo(0.5, 1e-12));
      for (final bad in [
        const TimePitchSettings(semitones: 13),
        const TimePitchSettings(semitones: -13),
        const TimePitchSettings(tempoRatio: 0.49),
        const TimePitchSettings(tempoRatio: 2.01),
        const TimePitchSettings(tempoRatio: double.nan),
      ]) {
        expect(bad.isValid, false);
      }
      final track = const Track(id: 't', title: 'T', channels: []).copyWith(timePitch: const TimePitchSettings(semitones: -2, tempoRatio: 0.9, complex: false));
      final back = Track.fromJson(jsonDecode(jsonEncode(track.toJson())) as Map<String, dynamic>);
      expect(back.timePitch, const TimePitchSettings(semitones: -2, tempoRatio: 0.9, complex: false));
      expect(Track.fromJson({'id': 't', 'title': 'T', 'channels': <dynamic>[]}).timePitch.isIdentity, true);
      expect(Track.fromJson({'id': 't', 'title': 'T', 'channels': <dynamic>[], 'timePitch': {'semitones': 99}}).timePitch.isIdentity, true);
      expect(Track.fromJson({'id': 't', 'title': 'T', 'channels': <dynamic>[], 'timePitch': 'x'}).timePitch.isIdentity, true);
    });
  });

  group('TimePitchService', () {
    late Directory dir;
    late Directory cache;
    setUp(() {
      dir = Directory.systemTemp.createTempSync('tp-src-');
      cache = Directory.systemTemp.createTempSync('tp-cache-');
    });
    tearDown(() {
      dir.deleteSync(recursive: true);
      cache.deleteSync(recursive: true);
    });

    test('identity returns the originals without touching the engine', () async {
      final engine = FakeEngine();
      final track = _trackWith(dir);
      final paths = await TimePitchService(directoryResolver: () async => cache).prepare(engine, track);
      expect(paths, track.channelFilePaths);
      expect(engine.processedRequests, isEmpty);
    });

    test('renders every stem with the right factors, caches, and keeps only the current rendering', () async {
      final engine = FakeEngine();
      final service = TimePitchService(directoryResolver: () async => cache);
      final base = _trackWith(dir, channels: 3);
      final slow = base.copyWith(timePitch: const TimePitchSettings(semitones: 2, tempoRatio: 0.8));
      final progress = <double>[];
      final paths = await service.prepare(engine, slow, onProgress: progress.add);
      expect(paths.length, 3);
      expect(paths.every((p) => File(p).existsSync()), true);
      expect(engine.processedRequests.length, 3);
      expect(engine.processedRequests.first.timeFactor, closeTo(1.25, 1e-12));
      expect(engine.processedRequests.first.pitchFactor, closeTo(1.122462048309373, 1e-9));
      expect(engine.processedRequests.map((r) => r.token).toSet().length, 3);
      expect(progress.first, 0);
      expect(progress.last, 1);
      // Cached: no new work and identical paths.
      expect(await service.prepare(engine, slow), paths);
      expect(engine.processedRequests.length, 3);
      // New settings render again and delete the previous cache entries.
      final other = await service.prepare(engine, base.copyWith(timePitch: const TimePitchSettings(semitones: -3)));
      expect(engine.processedRequests.length, 6);
      expect(other.toSet().intersection(paths.toSet()), isEmpty);
      expect(paths.any((p) => File(p).existsSync()), false);
      expect(other.every((p) => File(p).existsSync()), true);
      // Replacing a source invalidates only the changed stem.
      File(base.channels[1].filePath).writeAsBytesSync(List.filled(300, 9));
      final again = await service.prepare(engine, base.copyWith(timePitch: const TimePitchSettings(semitones: -3)));
      expect(engine.processedRequests.length, 7);
      expect(again[0], other[0]);
      expect(again[1], isNot(other[1]));
      await service.discard('song');
      expect(again.any((p) => File(p).existsSync()), false);
    });

    test('native failure, missing source and invalid settings throw without publishing', () async {
      final engine = FakeEngine()..failProcessing = true;
      final service = TimePitchService(directoryResolver: () async => cache);
      final track = _trackWith(dir).copyWith(timePitch: const TimePitchSettings(semitones: 1));
      await expectLater(service.prepare(engine, track), throwsA(isA<TimePitchFailure>()));
      engine.failProcessing = false;
      File(track.channels[0].filePath).deleteSync();
      await expectLater(service.prepare(engine, track), throwsA(isA<TimePitchFailure>()));
      await expectLater(
          service.prepare(engine, _trackWith(dir).copyWith(timePitch: const TimePitchSettings(semitones: 40))), throwsA(isA<TimePitchFailure>()));
    });

    test('cancel stops in-flight renders and queued stems', () async {
      final engine = FakeEngine()..processingGate = Completer<void>();
      final service = TimePitchService(directoryResolver: () async => cache);
      final track = _trackWith(dir, channels: 5).copyWith(timePitch: const TimePitchSettings(semitones: 1));
      final run = service.prepare(engine, track);
      final outcome = expectLater(run, throwsA(isA<TimePitchCancelled>()));
      await Future<void>.delayed(const Duration(milliseconds: 50));
      service.cancel(engine);
      expect(engine.cancelledTokens.length, 2);
      engine.processingGate!.complete();
      await outcome;
      expect(engine.processedRequests.length, 2); // the other three never started
    });
  });

  group('CurrentTrackNotifier.setTimePitch', () {
    ProviderContainer container(FakeEngine engine, FakeTimePitchService service) {
      final c = ProviderContainer(overrides: [
        engineProvider.overrideWithValue(engine),
        timePitchServiceProvider.overrideWithValue(service),
      ]);
      addTearDown(c.dispose);
      return c;
    }

    test('success reloads processed stems, sets the scale and returns to the same song position', () async {
      final engine = FakeEngine()..position = 12.5;
      final service = FakeTimePitchService();
      final c = container(engine, service);
      final n = c.read(currentTrackProvider.notifier)..setLoadedTrack(sampleTrack(channels: 2));
      const settings = TimePitchSettings(semitones: 3, tempoRatio: 0.75);
      expect(await n.setTimePitch('t1', settings), true);
      expect(engine.loadedPaths.last, ['/processed/0.wav', '/processed/1.wav']);
      expect(engine.timeScale, closeTo(1 / 0.75, 1e-12));
      expect(engine.calls, contains('seek(12.5)'));
      expect(c.read(currentTrackProvider)!.timePitch, settings);
      expect(c.read(currentTrackProvider.notifier).timePitchProgress, isNull);
    });

    test('returning to the original reloads the source files at scale 1', () async {
      final engine = FakeEngine();
      final c = container(engine, FakeTimePitchService());
      final n = c.read(currentTrackProvider.notifier)..setLoadedTrack(sampleTrack(channels: 2));
      await n.setTimePitch('t1', const TimePitchSettings(semitones: 1));
      engine.calls.clear();
      expect(await n.setTimePitch('t1', const TimePitchSettings()), true);
      expect(engine.loadedPaths.last, sampleTrack(channels: 2).channelFilePaths);
      expect(engine.calls.where((call) => call.startsWith('timeScale')), isEmpty);
      expect(await n.setTimePitch('t1', const TimePitchSettings()), true); // unchanged: no reload
    });

    test('render failure and invalid input leave the loaded song and engine untouched', () async {
      final engine = FakeEngine();
      final service = FakeTimePitchService()..fail = true;
      final c = container(engine, service);
      final n = c.read(currentTrackProvider.notifier)..setLoadedTrack(sampleTrack(channels: 2));
      final loads = engine.loadedPaths.length;
      expect(await n.setTimePitch('t1', const TimePitchSettings(semitones: 1)), false);
      expect(await n.setTimePitch('t1', const TimePitchSettings(semitones: 20)), false);
      expect(await n.setTimePitch('other', const TimePitchSettings(semitones: 1)), false);
      expect(engine.loadedPaths.length, loads);
      expect(c.read(currentTrackProvider)!.timePitch.isIdentity, true);
      expect(c.read(currentTrackProvider.notifier).timePitchProgress, isNull);
    });

    test('a failed reload restores the previous rendering', () async {
      final engine = FakeEngine();
      final service = FakeTimePitchService();
      final c = container(engine, service);
      final n = c.read(currentTrackProvider.notifier)..setLoadedTrack(sampleTrack(channels: 2));
      engine.failNextLoad = true;
      expect(await n.setTimePitch('t1', const TimePitchSettings(semitones: 1)), false);
      expect(c.read(currentTrackProvider)?.timePitch.isIdentity, true);
      expect(engine.loadedPaths.last, sampleTrack(channels: 2).channelFilePaths);
    });

    test('a scale rejected by the engine fails the load', () async {
      final engine = FakeEngine()..failTimeScale = true;
      final c = container(engine, FakeTimePitchService());
      final n = c.read(currentTrackProvider.notifier)..setLoadedTrack(sampleTrack(channels: 2));
      expect(await n.setTimePitch('t1', const TimePitchSettings(tempoRatio: 0.9)), false);
      expect(c.read(currentTrackProvider)?.timePitch.isIdentity ?? true, true);
    });
  });

  group('TimePitchSheet', () {
    testWidgets('adjusts semitones and tempo, applies and persists', (tester) async {
      tester.view.physicalSize = const Size(400, 900);
      tester.view.devicePixelRatio = 1;
      addTearDown(tester.view.resetPhysicalSize);
      addTearDown(tester.view.resetDevicePixelRatio);
      final engine = FakeEngine();
      final persistence = InMemoryPersistence();
      final c = ProviderContainer(overrides: [
        engineProvider.overrideWithValue(engine),
        timePitchServiceProvider.overrideWithValue(FakeTimePitchService()),
        persistenceServiceProvider.overrideWithValue(persistence),
      ]);
      addTearDown(c.dispose);
      c.read(currentTrackProvider.notifier).setLoadedTrack(sampleTrack(id: 'song', channels: 2));
      await c.read(trackLibraryProvider.notifier).saveCurrent();
      await tester.pumpWidget(UncontrolledProviderScope(
          container: c, child: const MaterialApp(home: Scaffold(body: TimePitchSheet(trackId: 'song')))));
      await tester.tap(find.byTooltip('Subir meio tom'));
      await tester.tap(find.byTooltip('Subir meio tom'));
      await tester.pump();
      expect(find.text('+2'), findsOneWidget);
      await tester.tap(find.byTooltip('Descer meio tom'));
      await tester.pump();
      expect(find.text('+1'), findsOneWidget);
      await tester.drag(find.byKey(const Key('tempo-slider')), const Offset(-60, 0));
      await tester.pump();
      expect(find.textContaining('Andamento: '), findsOneWidget);
      expect(find.text('Andamento: 100%'), findsNothing);
      await tester.tap(find.text('Aplicar'));
      await tester.runAsync(() => Future<void>.delayed(const Duration(milliseconds: 300)));
      await tester.pump(const Duration(milliseconds: 100));
      final saved = persistence.tracks['song']!.timePitch;
      expect(saved.semitones, 1);
      expect(saved.tempoRatio, lessThan(1));
      expect(engine.timeScale, saved.timeFactor);
      await tester.pumpWidget(const SizedBox.shrink());
      c.dispose();
    });
  });

  group('native FFI', () {
    test('real renderer produces a file of the scaled length and the engine reports song time', () async {
      final dir = await Directory.systemTemp.createTemp('tp-ffi-');
      addTearDown(() => dir.delete(recursive: true));
      final song = writeSineWav('${dir.path}/song.wav', seconds: 2);
      final out = '${dir.path}/slow.wav';
      final engine = WTracksEngine()..initialise();
      addTearDown(engine.shutdown);
      expect(await engine.processTimePitchAsync(song.path, out, 1.5, 1.0, true, 1001), true, reason: engine.lastError);
      expect(File(out).existsSync(), true);
      expect(File('$out.part').existsSync(), false);
      expect(await engine.processTimePitchAsync(song.path, '${dir.path}/bad.wav', 9, 1, true, 1002), false);
      expect(File('${dir.path}/bad.wav').existsSync(), false);
      engine.cancelTimePitch(1003);
      expect(await engine.processTimePitchAsync(song.path, '${dir.path}/cancelled.wav', 1.2, 1.1, true, 1003), false);
      expect(File('${dir.path}/cancelled.wav').existsSync(), false);
    }, skip: !nativeEngineAvailable() ? 'Native library unavailable' : false);

    test('scaled playback reports song length and rejects invalid scales', () async {
      final dir = await Directory.systemTemp.createTemp('tp-scale-');
      addTearDown(() => dir.delete(recursive: true));
      final song = writeSineWav('${dir.path}/song.wav', seconds: 3);
      final engine = WTracksEngine()..initialise();
      addTearDown(engine.shutdown);
      expect(await engine.loadTrackAsync('scale', [song.path]), true, reason: engine.lastError);
      expect(engine.setTimeScale(1.5), true);
      expect(engine.timeScale, 1.5);
      expect(engine.totalLengthSeconds, closeTo(2.0, 0.001));
      expect(engine.setTimeScale(0.1), false);
      expect(engine.setTimeScale(double.nan), false);
      expect(engine.timeScale, 1.5);
    }, skip: !nativeEngineAvailable() ? 'Native library unavailable' : false);
  });
}
