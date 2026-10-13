import 'dart:convert';
import 'dart:io';
import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/app_settings.dart';
import 'package:flutter_app/models/mixer_automation.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/native/wtracks_bindings.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/providers/meter_provider.dart';
import 'package:flutter_app/screens/buses_screen.dart';
import 'package:flutter_app/screens/performance_screen.dart';
import 'package:flutter_app/screens/settings_screen.dart';
import 'package:flutter_app/services/app_preferences_store.dart';
import 'harness/harness_support.dart';

class _Prefs extends AppPreferencesStore {
  AppSettings saved = const AppSettings();
  @override
  Future<AppSettings> load() async => saved;
  @override
  Future<void> save(AppSettings settings) async => saved = settings;
}

const _band = SongBus(id: 'band', name: 'Banda', volume: 0.8, route: ChannelRoute.right);
const _cg = SongBus(id: 'cg', name: 'Click & Guia');

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  mockBackgroundChannel();

  test('buses and channel assignments round-trip; legacy tracks have none; invalid lists are rejected', () {
    final base = sampleTrack(id: 's', channels: 2);
    final track = base.copyWith(buses: [_band, _cg], channels: [base.channels[0].copyWith(busId: 'band'), base.channels[1]]);
    final back = Track.fromJson(jsonDecode(jsonEncode(track.toJson())) as Map<String, dynamic>);
    expect(back.buses, [_band, _cg]);
    expect(back.channels.map((c) => c.busId), ['band', null]);
    expect(back.busIndex('cg'), 1);
    expect(back.busIndex('x'), -1);
    expect(back.channels[0].copyWith(busId: null).busId, isNull);
    expect(back.channels[0].copyWith(volume: 0.5).busId, 'band');
    expect(Track.fromJson({'id': 't', 'title': 'T', 'channels': <dynamic>[]}).buses, isEmpty);
    expect(() => SongBus.fromJsonList([_band.toJson(), _band.toJson()]), throwsFormatException);
    expect(() => SongBus.fromJsonList([{'id': 'a', 'name': ' '}]), throwsFormatException);
  });

  test('bus automation ids, snapshot and points', () {
    expect(AutomationItem(AutomationItem.busVolume(2), 0.5).param, 131);
    expect(AutomationItem(AutomationItem.busMute(2), 1).param, 147);
    expect(AutomationItem(AutomationItem.busVolume(2), 0.5).bus, 2);
    expect(AutomationItem(AutomationItem.busVolume(2), 0.5).channel, isNull);
    expect(AutomationItem(AutomationItem.busMute(0), 0.5).isValid, false);
    final track = sampleTrack(id: 's', channels: 1).copyWith(buses: [_band]);
    final items = MixerAutomationCue.snapshot(track);
    expect(items.sublist(items.length - 2), [AutomationItem(AutomationItem.busVolume(0), 0.8), AutomationItem(AutomationItem.busMute(0), 0)]);
    final cue = MixerAutomationCue(id: 'a', name: 'a', timeSeconds: 2, items: [
      AutomationItem(AutomationItem.busVolume(0), 0.2),
      AutomationItem(AutomationItem.busVolume(3), 0.2),
    ]);
    expect(automationPoints([cue], const ClickSettings(), const [], busCount: 1), const [AutomationPoint(2, 2, 129, 0.2)]);
  });

  group('CurrentTrackNotifier', () {
    ProviderContainer container(FakeEngine engine) {
      final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine), appPreferencesProvider.overrideWithValue(_Prefs())]);
      addTearDown(c.dispose);
      return c;
    }

    test('load sends buses and assignments; edits keep the engine in step; removing a bus releases its tracks', () async {
      final engine = FakeEngine();
      final c = container(engine);
      final n = c.read(currentTrackProvider.notifier);
      final base = sampleTrack(id: 's', channels: 3);
      expect(await n.load(base.copyWith(buses: [_band], channels: [base.channels[0], base.channels[1].copyWith(busId: 'band'), base.channels[2]])), true);
      expect(engine.busCount, 1);
      expect(engine.busSettings[0], _band);
      expect(engine.channelBuses, {0: -1, 1: 0, 2: -1});
      expect(n.addBus(_cg), true);
      expect(n.assignChannelToBus(0, 'cg'), true);
      expect(engine.channelBuses[0], 1);
      expect(n.assignChannelToBus(0, 'missing'), false);
      expect(n.updateBus(_band.copyWith(volume: 0.3, muted: true)), true);
      expect(engine.busSettings[0]!.volume, 0.3);
      expect(n.removeBus('band'), true);
      expect(engine.busCount, 1);
      expect(engine.busSettings[0], _cg);
      expect(engine.channelBuses, {0: 0, 1: -1, 2: -1});
      expect(c.read(currentTrackProvider)!.channels[1].busId, isNull);
      expect(n.addBus(const SongBus(id: 'cg', name: 'dup')), false);
      engine.failBuses = true;
      expect(n.addBus(const SongBus(id: 'x', name: 'X')), false);
      expect(c.read(currentTrackProvider)!.buses.length, 1);
      expect(await n.load(base.copyWith(title: 'again')), false);
    });

    test('solo across tracks and buses: soloed bus keeps its tracks; a soloed track keeps its bus', () async {
      final engine = FakeEngine();
      final c = container(engine);
      final n = c.read(currentTrackProvider.notifier);
      final base = sampleTrack(id: 's', channels: 3);
      expect(await n.load(base.copyWith(buses: [_band, _cg], channels: [
        base.channels[0].copyWith(busId: 'band'),
        base.channels[1].copyWith(busId: 'cg'),
        base.channels[2],
      ])), true);
      n.toggleBusSolo('band');
      expect(engine.calls.where((c) => c.startsWith('solo(')).toList().reversed.take(3).toList().reversed, ['solo(0,false)', 'solo(1,true)', 'solo(2,true)']);
      expect(engine.busSoloMuted, {0: false, 1: true});
      n.toggleBusSolo('band');
      n.toggleChannelSolo(1);
      expect(engine.busSoloMuted, {0: true, 1: false});
      expect(engine.calls.where((c) => c.startsWith('solo(')).toList().reversed.take(3).toList().reversed, ['solo(0,true)', 'solo(1,false)', 'solo(2,true)']);
    });

    test('stereo split follows the saved preference and the setting', () async {
      final engine = FakeEngine();
      final prefs = _Prefs()..saved = const AppSettings(stereoSplit: true);
      final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine), appPreferencesProvider.overrideWithValue(prefs)]);
      addTearDown(c.dispose);
      c.read(appSettingsProvider);
      await Future<void>.delayed(Duration.zero);
      expect(engine.stereoSplit, true);
      await c.read(appSettingsProvider.notifier).apply(const AppSettings());
      expect(engine.stereoSplit, false);
      expect(prefs.saved.stereoSplit, false);
    });
  });

  testWidgets('buses screen adds, routes, assigns, renames and deletes; the mixer shows bus strips with meters', (tester) async {
    tester.view.physicalSize = const Size(420, 900);
    tester.view.devicePixelRatio = 1;
    addTearDown(tester.view.resetPhysicalSize);
    addTearDown(tester.view.resetDevicePixelRatio);
    final engine = FakeEngine();
    final persistence = InMemoryPersistence();
    final c = ProviderContainer(overrides: [
      engineProvider.overrideWithValue(engine),
      persistenceServiceProvider.overrideWithValue(persistence),
      appPreferencesProvider.overrideWithValue(_Prefs()),
    ]);
    addTearDown(c.dispose);
    c.read(currentTrackProvider.notifier).setLoadedTrack(sampleTrack(id: 'song', channels: 2));
    await c.read(trackLibraryProvider.notifier).saveCurrent();
    await tester.pumpWidget(UncontrolledProviderScope(container: c, child: const MaterialApp(home: BusesScreen(trackId: 'song'))));
    await tester.pumpAndSettle();

    await tester.tap(find.byTooltip('Adicionar bus'));
    await tester.pumpAndSettle();
    await tester.enterText(find.byKey(const Key('bus-name')), 'Banda');
    await tester.tap(find.text('Salvar'));
    await tester.pumpAndSettle();
    expect(engine.busCount, 1);
    final busId = c.read(currentTrackProvider)!.buses.single.id;

    await tester.tap(find.byKey(const Key('channel-bus-1')));
    await tester.pumpAndSettle();
    await tester.tap(find.text('Banda').last);
    await tester.pumpAndSettle();
    expect(engine.channelBuses[1], 0);
    expect(persistence.tracks['song']!.channels[1].busId, busId);

    await tester.tap(find.byKey(Key('bus-route-$busId')));
    await tester.pumpAndSettle();
    await tester.tap(find.text('Direita (mono)').last);
    await tester.pumpAndSettle();
    expect(engine.busSettings[0]!.route, ChannelRoute.right);

    await tester.tap(find.byTooltip('Renomear bus'));
    await tester.pumpAndSettle();
    await tester.enterText(find.byKey(const Key('bus-name')), 'Vozes');
    await tester.tap(find.text('Salvar'));
    await tester.pumpAndSettle();
    expect(persistence.tracks['song']!.buses.single.name, 'Vozes');

    await tester.tap(find.byKey(const Key('reset-track-routings')));
    await tester.pumpAndSettle();
    expect(engine.channelBuses[1], -1);

    await tester.tap(find.byTooltip('Excluir bus'));
    await tester.pumpAndSettle();
    expect(persistence.tracks['song']!.buses, isEmpty);
    expect(engine.busCount, 0);
    await tester.pumpWidget(const SizedBox.shrink());
  });

  testWidgets('performance mixer shows bus strips that reach the engine', (tester) async {
    tester.view.physicalSize = const Size(844, 600);
    tester.view.devicePixelRatio = 1;
    addTearDown(tester.view.resetPhysicalSize);
    addTearDown(tester.view.resetDevicePixelRatio);
    final engine = FakeEngine();
    final c = ProviderContainer(overrides: [
      engineProvider.overrideWithValue(engine),
      persistenceServiceProvider.overrideWithValue(InMemoryPersistence()),
      appPreferencesProvider.overrideWithValue(_Prefs()),
    ]);
    addTearDown(c.dispose);
    expect(await c.read(currentTrackProvider.notifier).load(sampleTrack(id: 'song', channels: 2).copyWith(buses: [_band])), true);
    await tester.pumpWidget(UncontrolledProviderScope(container: c, child: const MaterialApp(home: PerformanceScreen())));
    await tester.pump(const Duration(milliseconds: 100));
    expect(find.text('BUS BANDA'), findsOneWidget);
    expect(find.byKey(const Key('meter-bus-0')), findsOneWidget);
    await tester.tap(find.text('M').last);
    await tester.pump(const Duration(milliseconds: 100));
    expect(engine.busSettings[0]!.muted, true);
    expect(tester.takeException(), isNull);
    await tester.pumpWidget(const SizedBox.shrink());
    c.dispose();
  });

  testWidgets('settings screen toggles the stereo split', (tester) async {
    final engine = FakeEngine();
    final prefs = _Prefs();
    final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine), appPreferencesProvider.overrideWithValue(prefs)]);
    addTearDown(c.dispose);
    await tester.pumpWidget(UncontrolledProviderScope(container: c, child: const MaterialApp(home: SettingsScreen())));
    await tester.pumpAndSettle();
    await tester.tap(find.byKey(const Key('stereo-split')));
    await tester.pumpAndSettle();
    expect(engine.stereoSplit, true);
    expect(prefs.saved.stereoSplit, true);
  });

  testWidgets('meters include buses', (tester) async {
    final engine = FakeEngine()..busPeaks = [1.0];
    final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine)]);
    addTearDown(c.dispose);
    final sub = c.listen(meterProvider, (_, _) {});
    await tester.pump(const Duration(milliseconds: 50));
    expect(c.read(meterProvider).buses, [1.0]);
    sub.close();
    await tester.pump(const Duration(milliseconds: 100));
  });

  test('native FFI: buses validate indices and report state', () async {
    final dir = await Directory.systemTemp.createTemp('bus-ffi-');
    addTearDown(() => dir.delete(recursive: true));
    final song = writeSineWav('${dir.path}/song.wav', seconds: 1);
    final engine = WTracksEngine()..initialise();
    addTearDown(engine.shutdown);
    expect(await engine.loadTrackAsync('bus-ffi', [song.path, song.path]), true, reason: engine.lastError);
    expect(engine.configureBuses(17), false);
    expect(engine.configureBuses(2), true);
    expect(engine.setBus(1, _band), true);
    expect(engine.setBus(2, _band), false);
    expect(engine.setChannelBus(1, 1), true);
    expect(engine.setChannelBus(1, 2), false);
    final mix = engine.mixState();
    expect(mix.busVolumes, [1.0, closeTo(0.8, 1e-6)]);
    expect(mix.busMutes, [false, false]);
    expect(engine.takeBusMeters(), [0, 0]);
    engine.setStereoSplit(false);
  }, skip: !nativeEngineAvailable() ? 'Native library unavailable' : false);
}
