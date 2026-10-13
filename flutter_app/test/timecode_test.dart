import 'dart:convert';
import 'dart:io';
import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/timecode_settings.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/native/wtracks_bindings.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/screens/midi_screen.dart';
import 'package:flutter_app/services/midi_preferences_store.dart';
import 'harness/harness_support.dart';
import 'harness/screens_harness_test.dart' show loadRealFonts;

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  setUpAll(loadRealFonts);
  setUp(mockBackgroundChannel);

  group('TimecodeSettings', () {
    test('formats and parses labels with drop-frame numbering', () {
      expect(TimecodeSettings.format(3, 30 * 3600 + 29), '01:00:00:29');
      expect(TimecodeSettings.format(5, 1799), '00:00:59;29');
      expect(TimecodeSettings.format(5, 1800), '00:01:00;02');
      expect(TimecodeSettings.format(5, 17982), '00:10:00;00');
      expect(TimecodeSettings.format(9, 3600), '00:01:00;04');
      for (final rate in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) {
        for (final frames in [0, 1, 1799, 1800, 17981, 17982, 100000, 1234567]) {
          final text = TimecodeSettings.format(rate, frames);
          expect(TimecodeSettings.parse(rate, text), frames, reason: 'rate $rate frames $frames ($text)');
        }
      }
      expect(TimecodeSettings.parse(5, '00:01:00:00'), isNull); // numbers skipped at minute 1
      expect(TimecodeSettings.parse(5, '00:01:00:01'), isNull);
      expect(TimecodeSettings.parse(5, '00:10:00:00'), 17982);
      expect(TimecodeSettings.parse(9, '00:01:00:03'), isNull);
      expect(TimecodeSettings.parse(3, '00:00:00:30'), isNull);
      expect(TimecodeSettings.parse(1, '24:00:00:00'), isNull);
      expect(TimecodeSettings.parse(1, 'abc'), isNull);
      expect(TimecodeSettings.parse(1, '1:2:3:4'), 25 * 3723 + 4);
    });

    test('validation and persistence never produce a bad signal', () {
      expect(const TimecodeSettings().isValid, true);
      for (final bad in [
        const TimecodeSettings(rateIndex: 11),
        const TimecodeSettings(rateIndex: -1),
        const TimecodeSettings(startFrame: -1),
        TimecodeSettings(startFrame: TimecodeSettings.framesPerDay(3)),
        const TimecodeSettings(onsetSeconds: -1),
        const TimecodeSettings(onsetSeconds: double.nan),
        const TimecodeSettings(outputChannel: 2),
        const TimecodeSettings(gain: 1.5),
      ]) {
        expect(bad.isValid, false);
      }
      const settings = TimecodeSettings(enabled: true, rateIndex: 5, startFrame: 1800, onsetSeconds: 2.5, outputChannel: 0, gain: 0.25);
      final track = const Track(id: 't', title: 'T', channels: []).copyWith(timecode: settings);
      expect(Track.fromJson(jsonDecode(jsonEncode(track.toJson())) as Map<String, dynamic>).timecode, settings);
      expect(Track.fromJson({'id': 't', 'title': 'T', 'channels': <dynamic>[]}).timecode, const TimecodeSettings());
      expect(TimecodeSettings.fromJson({'enabled': true, 'rateIndex': 99}), const TimecodeSettings());
      expect(TimecodeSettings.fromJson('x'), const TimecodeSettings());
    });
  });

  group('CurrentTrackNotifier timecode', () {
    test('updateTimecode asks the engine first; load applies it and fails when rejected', () async {
      final engine = FakeEngine();
      final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine)]);
      addTearDown(c.dispose);
      final n = c.read(currentTrackProvider.notifier)..setLoadedTrack(sampleTrack(id: 'song'));
      const settings = TimecodeSettings(enabled: true, rateIndex: 1);
      expect(n.updateTimecode('song', settings), true);
      expect(engine.configuredTimecode, settings);
      engine.failTimecode = true;
      expect(n.updateTimecode('song', const TimecodeSettings(rateIndex: 2)), false);
      expect(n.updateTimecode('other', settings), false);
      expect(n.updateTimecode('song', const TimecodeSettings(rateIndex: 40)), false);
      expect(c.read(currentTrackProvider)!.timecode, settings);
      engine.failTimecode = false;
      expect(await n.load(sampleTrack(id: 'next').copyWith(timecode: settings)), true);
      expect(engine.configuredTimecode, settings);
      engine.failTimecode = true;
      expect(await n.load(sampleTrack(id: 'bad').copyWith(timecode: settings)), false);
      expect(c.read(currentTrackProvider), isNull);
    });
  });

  testWidgets('MidiScreen edits the timecode with validation', (tester) async {
    tester.view.physicalSize = const Size(400, 1000);
    tester.view.devicePixelRatio = 1;
    addTearDown(tester.view.resetPhysicalSize);
    addTearDown(tester.view.resetDevicePixelRatio);
    final engine = FakeEngine();
    final persistence = InMemoryPersistence();
    final prefs = Directory.systemTemp.createTempSync('tc-prefs-');
    addTearDown(() => prefs.deleteSync(recursive: true));
    final c = ProviderContainer(overrides: [
      engineProvider.overrideWithValue(engine),
      persistenceServiceProvider.overrideWithValue(persistence),
      midiPreferencesProvider.overrideWithValue(MidiPreferencesStore(directoryResolver: () async => prefs)),
    ]);
    addTearDown(c.dispose);
    c.read(currentTrackProvider.notifier).setLoadedTrack(sampleTrack(id: 'song'));
    await c.read(trackLibraryProvider.notifier).saveCurrent();
    await tester.pumpWidget(UncontrolledProviderScope(container: c, child: const MaterialApp(home: MidiScreen(trackId: 'song'))));
    await tester.runAsync(() => Future<void>.delayed(const Duration(milliseconds: 100)));
    await tester.pump();
    await tester.tap(find.byKey(const Key('timecode-enabled')));
    await tester.runAsync(() => Future<void>.delayed(const Duration(milliseconds: 100)));
    await tester.pump();
    expect(engine.configuredTimecode?.enabled, true);

    await tester.tap(find.byKey(const Key('timecode-edit')));
    await tester.pumpAndSettle();
    await tester.enterText(find.byKey(const Key('timecode-start')), '99:00:00:00');
    await tester.tap(find.text('Salvar'));
    await tester.pumpAndSettle();
    expect(find.text('Timecode inválido para esta taxa'), findsOneWidget);
    await tester.enterText(find.byKey(const Key('timecode-start')), '01:00:00:00');
    await tester.enterText(find.byKey(const Key('timecode-onset')), '2,5');
    await tester.tap(find.text('Salvar'));
    await tester.runAsync(() => Future<void>.delayed(const Duration(milliseconds: 100)));
    await tester.pumpAndSettle();
    expect(engine.configuredTimecode!.startFrame, 30 * 3600);
    expect(engine.configuredTimecode!.onsetSeconds, 2.5);
    expect(persistence.tracks['song']!.timecode.startFrame, 30 * 3600);
    await tester.pumpWidget(const SizedBox.shrink());
    c.dispose();
  });

  test('real ABI validates timecode settings', () async {
    final dir = await Directory.systemTemp.createTemp('tc-ffi-');
    addTearDown(() => dir.delete(recursive: true));
    final song = writeSineWav('${dir.path}/song.wav', seconds: 2);
    final engine = WTracksEngine()..initialise();
    addTearDown(engine.shutdown);
    expect(await engine.loadTrackAsync('tc-ffi', [song.path]), true, reason: engine.lastError);
    expect(engine.configureTimecode(const TimecodeSettings(enabled: true, rateIndex: 5, startFrame: 1800, onsetSeconds: 0.5)), true, reason: engine.lastError);
    expect(engine.configureTimecode(const TimecodeSettings(rateIndex: 12)), false);
    expect(engine.configureTimecode(const TimecodeSettings(gain: 2)), false);
    expect(engine.configureTimecode(const TimecodeSettings()), true);
  }, skip: !nativeEngineAvailable() ? 'Native library unavailable' : false);
}
