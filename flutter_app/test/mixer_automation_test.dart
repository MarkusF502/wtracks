import 'dart:convert';
import 'dart:io';
import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/mixer_automation.dart';
import 'package:flutter_app/models/tempo_change.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/native/wtracks_bindings.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/screens/mixer_automation_screen.dart';
import 'package:flutter_app/screens/performance_screen.dart';
import 'harness/harness_support.dart';

const _click = ClickSettings(bpm: 120);
MixerAutomationCue _cue(String id, double t, List<AutomationItem> items, {int beats = 0, bool correction = false}) =>
    MixerAutomationCue(id: id, name: id, timeSeconds: t, transitionBeats: beats, applyTransitionLengthCorrection: correction, items: items);

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  mockBackgroundChannel();

  group('model', () {
    test('ids map to native params; values are range-checked', () {
      expect(AutomationItem(AutomationItem.channelVolume(3), 0.5).param, 3);
      expect(AutomationItem(AutomationItem.channelMute(3), 1).param, 67);
      expect(const AutomationItem(AutomationItem.masterVolume, 2).param, 128);
      for (final bad in [
        const AutomationItem('channel:64:volume', 0.5),
        const AutomationItem('channel:x:volume', 0.5),
        const AutomationItem('bus:1:volume', 0.5),
        AutomationItem(AutomationItem.channelMute(0), 0.5),
        AutomationItem(AutomationItem.channelVolume(0), 1.5),
        const AutomationItem(AutomationItem.masterVolume, 2.5),
        AutomationItem(AutomationItem.channelVolume(0), double.nan),
      ]) {
        expect(bad.isValid, false, reason: bad.automationID);
      }
      final dup = _cue('a', 1, [AutomationItem(AutomationItem.channelVolume(0), 1), AutomationItem(AutomationItem.channelVolume(0), 0)]);
      expect(dup.isValid, false);
      expect(MixerAutomationCue.validSequence([_cue('a', 2, const []), _cue('b', 1, const [])]), false);
      expect(_cue('a', 1, const [], beats: 257).isValid, false);
    });

    test('tracks round-trip automation; legacy files load empty and enabled', () {
      final track = sampleTrack(id: 's').copyWith(automationEnabled: false, mixerAutomation: [
        _cue('a', 1.5, [AutomationItem(AutomationItem.channelVolume(1), 0.25), const AutomationItem(AutomationItem.masterVolume, 1.5)],
            beats: 4, correction: true),
      ]);
      final back = Track.fromJson(jsonDecode(jsonEncode(track.toJson())) as Map<String, dynamic>);
      expect(back.mixerAutomation, track.mixerAutomation);
      expect(back.automationEnabled, false);
      final legacy = Track.fromJson({'id': 't', 'title': 'T', 'channels': <dynamic>[]});
      expect(legacy.mixerAutomation, isEmpty);
      expect(legacy.automationEnabled, true);
      expect(() => MixerAutomationCue.fromJsonList([
            {'id': 'a', 'name': 'a', 'timeSeconds': 1, 'items': [{'automationID': 'channel:0:mute', 'value': 0.3}]}
          ]), throwsFormatException);
    });

    test('snapshot captures every channel volume and mute and the master', () {
      final track = sampleTrack(channels: 2).copyWith(masterVolume: 1.2);
      final items = MixerAutomationCue.snapshot(track.copyWith(channels: [
        track.channels[0].copyWith(volume: 0.3, muted: true),
        track.channels[1],
      ]));
      expect(items, [
        AutomationItem(AutomationItem.channelVolume(0), 0.3),
        AutomationItem(AutomationItem.channelMute(0), 1),
        AutomationItem(AutomationItem.channelVolume(1), 1),
        AutomationItem(AutomationItem.channelMute(1), 0),
        const AutomationItem(AutomationItem.masterVolume, 1.2),
      ]);
    });
  });

  group('points', () {
    final v0 = AutomationItem.channelVolume(0), m0 = AutomationItem.channelMute(0);
    test('transitions are measured in beats before the point; mutes are instant', () {
      final points = automationPoints([
        _cue('a', 10, [AutomationItem(v0, 0.5), AutomationItem(m0, 1)], beats: 4),
      ], _click, const []);
      expect(points, const [AutomationPoint(8, 10, 0, 0.5), AutomationPoint(10, 10, 64, 1)]);
      // A change at 6 s to 60 BPM makes the four beats four seconds; the start never goes below zero.
      expect(automationPoints([_cue('a', 10, [AutomationItem(v0, 0)], beats: 4)], _click,
          const [TempoChange(id: 't', startSeconds: 6, bpm: 60)]), const [AutomationPoint(6, 10, 0, 0)]);
      expect(automationPoints([_cue('a', 1, [AutomationItem(v0, 0)], beats: 8)], _click, const []), const [AutomationPoint(0, 1, 0, 0)]);
      expect(automationPoints([_cue('a', 1, [AutomationItem(AutomationItem.channelVolume(5), 0)])], _click, const [], channelCount: 2),
          isEmpty);
    });

    test('correction shortens overlapping transitions; without it the new ramp cuts the previous one', () {
      final cues = [
        _cue('a', 10, [AutomationItem(v0, 0)], beats: 4),
        _cue('b', 11, [AutomationItem(v0, 1)], beats: 4, correction: true),
      ];
      expect(automationPoints(cues, _click, const []), const [AutomationPoint(8, 10, 0, 0), AutomationPoint(10, 11, 0, 1)]);
      final cut = [cues[0], cues[1].copyWith(applyTransitionLengthCorrection: false)];
      expect(automationPoints(cut, _click, const []), const [AutomationPoint(8, 10, 0, 0), AutomationPoint(9, 11, 0, 1)]);
      final early = [cues[0], _cue('c', 10.5, [AutomationItem(v0, 1)], beats: 16)];
      expect(automationPoints(early, _click, const [])[1], const AutomationPoint(8, 10.5, 0, 1), reason: 'never before the previous start');
    });
  });

  group('CurrentTrackNotifier', () {
    test('load configures points and the switch; edits, tempo changes and the switch reach the engine', () async {
      final engine = FakeEngine();
      final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine)]);
      addTearDown(c.dispose);
      final n = c.read(currentTrackProvider.notifier);
      final cue = _cue('a', 10, [AutomationItem(AutomationItem.channelVolume(1), 0.5)], beats: 2);
      expect(await n.load(sampleTrack(id: 's', click: _click).copyWith(mixerAutomation: [cue], automationEnabled: false)), true);
      expect(engine.automationPoints, const [AutomationPoint(9, 10, 1, 0.5)]);
      expect(engine.automationEnabled, false);
      n.setAutomationEnabled(true);
      expect(engine.automationEnabled, true);
      expect(c.read(currentTrackProvider)!.automationEnabled, true);
      expect(n.updateMixerAutomation('s', [cue.copyWith(transitionBeats: 4)]), true);
      expect(engine.automationPoints.single.start, 8);
      expect(n.updateClickSettings(_click.copyWith(bpm: 60)), true);
      expect(engine.automationPoints.single.start, 6);
      engine.failMixerAutomation = true;
      expect(n.updateMixerAutomation('s', const []), false);
      expect(c.read(currentTrackProvider)!.mixerAutomation.single.transitionBeats, 4);
      expect(n.updateMixerAutomation('other', const []), false);
      expect(await n.load(sampleTrack(id: 'x')), false, reason: 'engine refusal fails the load');
    });
  });

  testWidgets('screen adds a snapshot point, copies, pastes, edits and deletes; faders follow the engine', (tester) async {
    tester.view.physicalSize = const Size(420, 900);
    tester.view.devicePixelRatio = 1;
    addTearDown(tester.view.resetPhysicalSize);
    addTearDown(tester.view.resetDevicePixelRatio);
    final engine = FakeEngine()..position = 12.5;
    final persistence = InMemoryPersistence();
    final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine), persistenceServiceProvider.overrideWithValue(persistence)]);
    addTearDown(c.dispose);
    c.read(currentTrackProvider.notifier).setLoadedTrack(sampleTrack(id: 'song', channels: 2, click: _click));
    await c.read(trackLibraryProvider.notifier).saveCurrent();
    await tester.pumpWidget(UncontrolledProviderScope(container: c, child: const MaterialApp(home: MixerAutomationScreen(trackId: 'song'))));
    await tester.pump(const Duration(milliseconds: 150));

    await tester.tap(find.byTooltip('Adicionar ponto de automação'));
    await tester.pumpAndSettle();
    expect(find.text('Adicionar ponto de automação'), findsWidgets);
    await tester.enterText(find.byKey(const Key('automation-beats')), '4');
    await tester.tap(find.byKey(Key('include-${AutomationItem.channelMute(1)}')));
    await tester.tap(find.text('Salvar'));
    await tester.pumpAndSettle();
    final saved = persistence.tracks['song']!.mixerAutomation.single;
    expect(saved.timeSeconds, 12.5);
    expect(saved.transitionBeats, 4);
    expect(saved.items.length, 4, reason: 'two volumes, one mute and the master');
    expect(engine.automationPoints.where((p) => p.param == 0).single, const AutomationPoint(10.5, 12.5, 0, 1));

    await tester.tap(find.byTooltip('Ações do ponto'));
    await tester.pumpAndSettle();
    await tester.tap(find.text('Copiar'));
    await tester.pumpAndSettle();
    expect(c.read(automationClipboardProvider), saved.items);

    c.read(currentTrackProvider.notifier).setChannelVolume(0, 0.2);
    await tester.tap(find.byTooltip('Ações do ponto'));
    await tester.pumpAndSettle();
    await tester.tap(find.text('Definir com o mixer atual'));
    await tester.pumpAndSettle();
    expect(persistence.tracks['song']!.mixerAutomation.single.items.first.value, closeTo(0.2, 1e-9));
    await tester.tap(find.byTooltip('Ações do ponto'));
    await tester.pumpAndSettle();
    await tester.tap(find.text('Colar (substitui os itens)'));
    await tester.pumpAndSettle();
    expect(persistence.tracks['song']!.mixerAutomation.single.items, saved.items);

    await tester.tap(find.byKey(const Key('automation-enabled')));
    await tester.pumpAndSettle();
    expect(engine.automationEnabled, false);
    expect(persistence.tracks['song']!.automationEnabled, false);

    await tester.tap(find.byTooltip('Ações do ponto'));
    await tester.pumpAndSettle();
    await tester.tap(find.text('Excluir'));
    await tester.pumpAndSettle();
    expect(persistence.tracks['song']!.mixerAutomation, isEmpty);
    expect(engine.automationPoints, isEmpty);
    await tester.pumpWidget(const SizedBox.shrink());
  });

  testWidgets('performance mixer shows the automated values and the AUTO switch', (tester) async {
    tester.view.physicalSize = const Size(844, 600);
    tester.view.devicePixelRatio = 1;
    addTearDown(tester.view.resetPhysicalSize);
    addTearDown(tester.view.resetDevicePixelRatio);
    final engine = FakeEngine()..mix = const MixState([0.25, 1, 1, 1], [false, true, false, false], 1.5);
    final c = ProviderContainer(overrides: [
      engineProvider.overrideWithValue(engine),
      persistenceServiceProvider.overrideWithValue(InMemoryPersistence()),
    ]);
    addTearDown(c.dispose);
    c.read(currentTrackProvider.notifier).setLoadedTrack(sampleTrack(id: 'song').copyWith(mixerAutomation: [
      _cue('a', 1, [AutomationItem(AutomationItem.channelVolume(0), 0.25)]),
    ]));
    await tester.pumpWidget(UncontrolledProviderScope(container: c, child: const MaterialApp(home: PerformanceScreen())));
    for (var i = 0; i < 3; i++) {
      await tester.pump(const Duration(milliseconds: 100));
    }
    expect(c.read(automatedMixProvider), engine.mix);
    expect(find.text('150%'), findsOneWidget);
    await tester.tap(find.byKey(const Key('transport-automation')));
    await tester.pump(const Duration(milliseconds: 200));
    expect(engine.automationEnabled, false);
    expect(c.read(automatedMixProvider), isNull);
    expect(find.text('100%'), findsOneWidget);
    await tester.pumpWidget(const SizedBox.shrink());
    c.dispose();
  });

  group('native FFI', () {
    test('real ABI validates points and reports the automated mix at the playhead', () async {
      final dir = await Directory.systemTemp.createTemp('automation-ffi-');
      addTearDown(() => dir.delete(recursive: true));
      final song = writeSineWav('${dir.path}/song.wav', seconds: 3);
      final engine = WTracksEngine()..initialise();
      addTearDown(engine.shutdown);
      expect(await engine.loadTrackAsync('automation-ffi', [song.path, song.path]), true, reason: engine.lastError);
      expect(engine.configureMixerAutomation(const [AutomationPoint(1, 2, 0, 0), AutomationPoint(1, 1, 65, 1), AutomationPoint(0, 0, 128, 2)]),
          true, reason: engine.lastError);
      expect(engine.configureMixerAutomation(const [AutomationPoint(2, 1, 0, 0)]), false);
      expect(engine.configureMixerAutomation(const [AutomationPoint(1, 2, 64, 1)]), false, reason: 'mutes are instant');
      engine.seekToSeconds(1.5);
      var mix = engine.mixState();
      expect(mix.volumes.length, 2);
      expect(mix.volumes[0], closeTo(0.5, 1e-3));
      expect(mix.mutes, [false, true]);
      expect(mix.master, 2);
      engine.setAutomationEnabled(false);
      mix = engine.mixState();
      expect(mix.volumes[0], 1);
      expect(mix.mutes, [false, false]);
      expect(mix.master, 1);
      engine.setAutomationEnabled(true);
      expect(engine.configureMixerAutomation(const []), true);
    }, skip: !nativeEngineAvailable() ? 'Native library unavailable' : false);
  });
}
