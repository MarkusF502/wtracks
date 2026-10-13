import 'dart:convert';
import 'dart:io';
import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/native/wtracks_bindings.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/screens/performance_screen.dart';
import 'harness/harness_support.dart';
import 'harness/screens_harness_test.dart' show pumpScreen, portrait, landscape, unmount, loadRealFonts;

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  setUpAll(loadRealFonts);
  setUp(mockBackgroundChannel);

  group('model', () {
    test('routes and master volume round-trip; legacy and unknown values are safe', () {
      final track = sampleTrack().copyWith(
        channels: [
          const ChannelInfo(label: 'Click', filePath: '/a.wav', route: ChannelRoute.left),
          const ChannelInfo(label: 'Band', filePath: '/b.wav', route: ChannelRoute.right),
        ],
        masterVolume: 0.5,
      );
      final back = Track.fromJson(jsonDecode(jsonEncode(track.toJson())) as Map<String, dynamic>);
      expect(back.channels.map((c) => c.route), [ChannelRoute.left, ChannelRoute.right]);
      expect(back.masterVolume, 0.5);
      final legacy = ChannelInfo.fromJson({'label': 'x', 'filePath': '/x.wav'});
      expect(legacy.route, ChannelRoute.stereo);
      expect(ChannelInfo.fromJson({'label': 'x', 'filePath': '/x', 'route': 'surround'}).route, ChannelRoute.stereo);
      expect(Track.fromJson({'id': 't', 'title': 'T', 'channels': <dynamic>[], 'masterVolume': 9}).masterVolume, 2.0);
      expect(Track.fromJson({'id': 't', 'title': 'T', 'channels': <dynamic>[]}).masterVolume, 1.0);
      expect([for (final r in ChannelRoute.values) (r.outputBase, r.mono)], [(0, false), (0, true), (1, true)]);
    });
  });

  group('CurrentTrackNotifier', () {
    test('route changes are published only when the engine accepts them', () {
      final engine = FakeEngine();
      final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine)]);
      addTearDown(c.dispose);
      final n = c.read(currentTrackProvider.notifier)..setLoadedTrack(sampleTrack());
      expect(n.setChannelRoute(1, ChannelRoute.right), true);
      expect(c.read(currentTrackProvider)!.channels[1].route, ChannelRoute.right);
      engine.failRoute = true;
      expect(n.setChannelRoute(1, ChannelRoute.left), false);
      expect(c.read(currentTrackProvider)!.channels[1].route, ChannelRoute.right);
      expect(n.setChannelRoute(99, ChannelRoute.left), false);
      expect(n.setChannelRoute(-1, ChannelRoute.left), false);
    });

    test('master volume is clamped, ignores NaN and reaches the engine', () {
      final engine = FakeEngine();
      final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine)]);
      addTearDown(c.dispose);
      final n = c.read(currentTrackProvider.notifier)..setLoadedTrack(sampleTrack());
      n.setMasterVolume(7);
      expect(engine.masterVolume, 2);
      n.setMasterVolume(double.nan);
      n.setMasterVolume(-1);
      expect(engine.masterVolume, 0);
      expect(c.read(currentTrackProvider)!.masterVolume, 0);
    });

    test('load applies saved routes and master volume to the engine', () async {
      final engine = FakeEngine();
      final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine)]);
      addTearDown(c.dispose);
      final base = sampleTrack(channels: 2);
      final track = base.copyWith(
        channels: [base.channels[0].copyWith(route: ChannelRoute.left), base.channels[1].copyWith(route: ChannelRoute.right)],
        masterVolume: 0.8,
      );
      expect(await c.read(currentTrackProvider.notifier).load(track), true);
      expect(engine.routes, {0: ChannelRoute.left, 1: ChannelRoute.right});
      expect(engine.masterVolume, 0.8);
    });
  });

  group('PerformanceScreen mixer', () {
    for (final (label, size) in [('retrato', portrait), ('paisagem', landscape)]) {
      testWidgets('route button cycles ST -> L -> R and the master slider reaches the engine ($label)', (tester) async {
        final engine = FakeEngine();
        final c = await pumpScreen(tester, const PerformanceScreen(), size: size, engine: engine, loaded: sampleTrack());
        await tester.ensureVisible(find.text('ST').first);
        await tester.tap(find.text('ST').first);
        await tester.pump(const Duration(milliseconds: 100));
        expect(engine.routes[0], ChannelRoute.left);
        await tester.tap(find.text('L').first);
        await tester.pump(const Duration(milliseconds: 100));
        expect(engine.routes[0], ChannelRoute.right);
        await tester.tap(find.text('R').first);
        await tester.pump(const Duration(milliseconds: 100));
        expect(engine.routes[0], ChannelRoute.stereo);
        await tester.drag(find.byKey(const Key('master-volume')), const Offset(-60, 0));
        await tester.pump(const Duration(milliseconds: 100));
        expect(engine.masterVolume, lessThan(1));
        expect(c.read(currentTrackProvider)!.masterVolume, engine.masterVolume);
        expect(tester.takeException(), isNull);
        await unmount(tester);
      });
    }
  });

  group('native FFI', () {
    test('real ABI rejects bad routes and accepts routes/master while a track is loaded', () async {
      final dir = await Directory.systemTemp.createTemp('mixer-ffi-');
      addTearDown(() => dir.delete(recursive: true));
      final song = writeSineWav('${dir.path}/song.wav');
      final engine = WTracksEngine()..initialise();
      addTearDown(engine.shutdown);
      expect(engine.setChannelRoute(0, ChannelRoute.left), false, reason: 'no track loaded');
      expect(await engine.loadTrackAsync('mixer-ffi', [song.path]), true, reason: engine.lastError);
      for (final route in ChannelRoute.values) {
        expect(engine.setChannelRoute(0, route), true, reason: engine.lastError);
      }
      expect(engine.setChannelRoute(1, ChannelRoute.left), false);
      engine.setMasterVolume(0.5);
      engine.setMasterVolume(double.nan);
    }, skip: !nativeEngineAvailable() ? 'Native library unavailable' : false);
  });
}
