import 'dart:io';
import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/app_settings.dart';
import 'package:flutter_app/models/mixer_automation.dart';
import 'package:flutter_app/native/wtracks_bindings.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/providers/meter_provider.dart';
import 'package:flutter_app/screens/performance_screen.dart';
import 'package:flutter_app/screens/settings_screen.dart';
import 'package:flutter_app/services/app_preferences_store.dart';
import 'harness/harness_support.dart';

class _MemoryAppPrefs extends AppPreferencesStore {
  AppSettings saved = const AppSettings();
  @override
  Future<AppSettings> load() async => saved;
  @override
  Future<void> save(AppSettings settings) async => saved = settings;
}

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  mockBackgroundChannel();

  test('meter scale: -60..0 dB onto 0..1', () {
    expect(meterFraction(0), 0);
    expect(meterFraction(double.nan), 0);
    expect(meterFraction(1), 1);
    expect(meterFraction(2), 1);
    expect(meterFraction(0.1), closeTo(40 / 60, 1e-9));
    expect(meterFraction(0.001), closeTo(0, 1e-9));
  });

  testWidgets('meter levels rise at once and fall 24 dB/s; polling stops without listeners', (tester) async {
    final engine = FakeEngine()..channelPeaks = [1.0, 0.1];
    final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine)]);
    addTearDown(c.dispose);
    final sub = c.listen(meterProvider, (_, _) {});
    await tester.pump(const Duration(milliseconds: 50));
    expect(c.read(meterProvider).channels[0], 1);
    expect(c.read(meterProvider).channels[1], closeTo(40 / 60, 1e-9));
    await tester.pump(const Duration(milliseconds: 500)); // ten reads of silence: -12 dB
    expect(c.read(meterProvider).channels[0], closeTo(1 - 12 / 60, 1e-9));
    engine.outputPeaks = [0.5, 0.25];
    await tester.pump(const Duration(milliseconds: 50));
    expect(c.read(meterProvider).outputs[0], closeTo(meterFraction(0.5), 1e-9));
    sub.close();
    await tester.pump(const Duration(milliseconds: 100));
    engine.channelPeaks = [1.0];
    await tester.pump(const Duration(milliseconds: 100));
    expect(engine.channelPeaks, [1.0], reason: 'no reads after the last listener left');
  });

  test('app settings: JSON defaults, store round trip, default channel volume', () async {
    expect(AppSettings.fromJson({'faderDefault80': 'yes'}), const AppSettings());
    expect(const AppSettings(faderDefault80: true).defaultChannelVolume, 0.8);
    expect(const AppSettings().defaultChannelVolume, 1.0);
    final dir = await Directory.systemTemp.createTemp('app-prefs-');
    addTearDown(() => dir.delete(recursive: true));
    final store = AppPreferencesStore(directoryResolver: () async => dir);
    expect(await store.load(), const AppSettings());
    await store.save(const AppSettings(faderDefault80: true));
    expect(await store.load(), const AppSettings(faderDefault80: true));
  });

  testWidgets('settings screen toggles the 80% fader default', (tester) async {
    final prefs = _MemoryAppPrefs();
    final c = ProviderContainer(overrides: [appPreferencesProvider.overrideWithValue(prefs)]);
    addTearDown(c.dispose);
    await tester.pumpWidget(UncontrolledProviderScope(container: c, child: const MaterialApp(home: SettingsScreen())));
    await tester.pumpAndSettle();
    await tester.tap(find.byKey(const Key('fader-default-80')));
    await tester.pumpAndSettle();
    expect(prefs.saved.faderDefault80, true);
    expect(c.read(appSettingsProvider).defaultChannelVolume, 0.8);
  });

  testWidgets('phone-width mixer shows channel and master meters next to the AUTO switch', (tester) async {
    tester.view.physicalSize = const Size(390, 844);
    tester.view.devicePixelRatio = 1;
    addTearDown(tester.view.resetPhysicalSize);
    addTearDown(tester.view.resetDevicePixelRatio);
    final engine = FakeEngine()..channelPeaks = [1.0, 0.0, 0.0, 0.0];
    final c = ProviderContainer(overrides: [
      engineProvider.overrideWithValue(engine),
      persistenceServiceProvider.overrideWithValue(InMemoryPersistence()),
    ]);
    addTearDown(c.dispose);
    c.read(currentTrackProvider.notifier).setLoadedTrack(sampleTrack(id: 'song').copyWith(mixerAutomation: const [
      MixerAutomationCue(id: 'a', name: 'a', timeSeconds: 1),
    ]));
    await tester.pumpWidget(UncontrolledProviderScope(container: c, child: const MaterialApp(home: PerformanceScreen())));
    await tester.pump(const Duration(milliseconds: 100));
    expect(find.byKey(const Key('meter-0')), findsOneWidget);
    expect(find.byKey(const Key('meter-master-l')), findsOneWidget);
    expect(find.byKey(const Key('transport-automation')), findsOneWidget);
    expect(c.read(meterProvider).channels.first, greaterThan(0.9)); // one fall step may have passed
    expect(tester.takeException(), isNull);
    await tester.pumpWidget(const SizedBox.shrink());
    c.dispose();
  });

  test('native FFI: meters read and reset; idle engine reports silence', () async {
    final dir = await Directory.systemTemp.createTemp('meter-ffi-');
    addTearDown(() => dir.delete(recursive: true));
    final song = writeSineWav('${dir.path}/song.wav', seconds: 1);
    final engine = WTracksEngine()..initialise();
    addTearDown(engine.shutdown);
    expect(await engine.loadTrackAsync('meter-ffi', [song.path, song.path]), true, reason: engine.lastError);
    final (channels, outputs) = engine.takeMeters();
    expect(channels, [0, 0]);
    expect(outputs, [0, 0]);
  }, skip: !nativeEngineAvailable() ? 'Native library unavailable' : false);
}
