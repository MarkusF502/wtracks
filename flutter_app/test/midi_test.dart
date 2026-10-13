import 'dart:convert';
import 'dart:io';
import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/automation_cue.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/native/wtracks_bindings.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/screens/midi_screen.dart';
import 'package:flutter_app/services/midi_preferences_store.dart';
import 'harness/harness_support.dart';
import 'harness/screens_harness_test.dart' show loadRealFonts;

const _marker = AutomationCue(id: 'm', label: 'Refrão', timeSeconds: 1);
const _program = AutomationCue(id: 'p', label: 'Preset', timeSeconds: 2, kind: AutomationMessageKind.programChange, channel: 3, data1: 12);
const _cc = AutomationCue(id: 'c', label: 'Volume', timeSeconds: 3, kind: AutomationMessageKind.controlChange, channel: 16, data1: 7, data2: 100);
const _note = AutomationCue(id: 'n', label: 'Nota', timeSeconds: 4, kind: AutomationMessageKind.noteOn, data1: 60, data2: 90);

ProviderContainer _container(FakeEngine engine, Directory dir) {
  final c = ProviderContainer(overrides: [
    engineProvider.overrideWithValue(engine),
    midiPreferencesProvider.overrideWithValue(MidiPreferencesStore(directoryResolver: () async => dir)),
    persistenceServiceProvider.overrideWithValue(InMemoryPersistence()),
  ]);
  addTearDown(c.dispose);
  return c;
}

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  late Directory dir;
  setUpAll(loadRealFonts);
  setUp(() {
    mockBackgroundChannel();
    dir = Directory.systemTemp.createTempSync('midi-prefs-');
  });
  tearDown(() => dir.deleteSync(recursive: true));

  group('AutomationCue', () {
    test('builds channel voice messages and validates ranges', () {
      expect(_marker.midiBytes, isEmpty);
      expect(_program.midiBytes, [0xC2, 12]);
      expect(_cc.midiBytes, [0xBF, 7, 100]);
      expect(_note.midiBytes, [0x90, 60, 90]);
      for (final bad in [
        _cc.copyWith(channel: 0),
        _cc.copyWith(channel: 17),
        _cc.copyWith(data1: 128),
        _cc.copyWith(data2: -1),
        _cc.copyWith(timeSeconds: -0.1),
        _cc.copyWith(timeSeconds: double.nan),
        _cc.copyWith(label: '  '),
      ]) {
        expect(bad.isValid, false);
      }
      expect(AutomationCue.validSequence([_marker, _program, _cc]), true);
      expect(AutomationCue.validSequence([_program, _marker]), false);
      expect(AutomationCue.validSequence([_marker, _marker]), false);
    });

    test('round-trips through the track and rejects corrupt data', () {
      final track = const Track(id: 't', title: 'T', channels: []).copyWith(automationCues: [_marker, _program, _cc, _note], midiClockEnabled: true);
      final back = Track.fromJson(jsonDecode(jsonEncode(track.toJson())) as Map<String, dynamic>);
      expect(back.automationCues, [_marker, _program, _cc, _note]);
      expect(back.midiClockEnabled, true);
      final legacy = Track.fromJson({'id': 't', 'title': 'T', 'channels': <dynamic>[]});
      expect(legacy.automationCues, isEmpty);
      expect(legacy.midiClockEnabled, false);
      for (final json in [
        {..._cc.toJson(), 'data1': 200},
        {..._cc.toJson(), 'kind': 'sysex'},
        {..._cc.toJson(), 'timeSeconds': -1},
      ]) {
        expect(() => AutomationCue.fromJsonList([json]), throwsA(anything));
      }
    });
  });

  group('MidiController', () {
    test('lists devices, connects, remembers the choice and keeps the connection when a switch fails', () async {
      final engine = FakeEngine()..midiDevices = const [MidiDevice('a', 'Porta A'), MidiDevice('b', 'Porta B')];
      final c = _container(engine, dir);
      final midi = c.read(midiControllerProvider.notifier);
      await midi.refresh();
      expect(c.read(midiControllerProvider).devices.length, 2);
      expect(c.read(midiControllerProvider).connected, false);
      expect(await midi.select('a'), true);
      expect(engine.openedMidi, 'a');
      expect(await MidiPreferencesStore(directoryResolver: () async => dir).loadOutputId(), 'a');
      engine.failMidiOpen = true;
      expect(await midi.select('b'), false);
      expect(c.read(midiControllerProvider).selectedId, 'a');
      expect(c.read(midiControllerProvider).error, isNotNull);
      expect(engine.openedMidi, 'a');
      engine.failMidiOpen = false;
      midi.disconnect();
      expect(c.read(midiControllerProvider).connected, false);
      expect(midi.sendTest(const [0x90, 60, 100]), false);
      expect(await midi.ensureOpen(), true);  // reopens the remembered output
      expect(engine.openedMidi, 'a');
      expect(midi.sendTest(const [0x90, 60, 100]), true);
      expect(engine.sentMidi.single, [0x90, 60, 100]);
    });

    test('a fresh container recovers the remembered output and ignores corrupt preferences', () async {
      await MidiPreferencesStore(directoryResolver: () async => dir).saveOutputId('b');
      final engine = FakeEngine()..midiDevices = const [MidiDevice('b', 'Porta B')];
      final c = _container(engine, dir);
      await c.read(midiControllerProvider.notifier).refresh();
      expect(c.read(midiControllerProvider).selectedId, 'b');
      File('${dir.path}/wtracks_data/midi.json').writeAsStringSync('{broken');
      expect(await MidiPreferencesStore(directoryResolver: () async => dir).loadOutputId(), isNull);
      expect(await _container(FakeEngine(), dir).read(midiControllerProvider.notifier).ensureOpen(), false);
    });
  });

  group('CurrentTrackNotifier automation', () {
    test('updateAutomation applies to the engine first and keeps state on rejection', () {
      final engine = FakeEngine();
      final c = _container(engine, dir);
      final n = c.read(currentTrackProvider.notifier)..setLoadedTrack(sampleTrack(id: 'song'));
      expect(n.updateAutomation('song', [_marker, _program], true), true);
      expect(engine.configuredCues, [_marker, _program]);
      expect(engine.midiClock, true);
      expect(c.read(currentTrackProvider)!.automationCues, [_marker, _program]);
      engine.failCues = true;
      expect(n.updateAutomation('song', [_marker], false), false);
      engine.failCues = false;
      expect(n.updateAutomation('song', [_program, _marker], false), false);
      expect(n.updateAutomation('other', [_marker], false), false);
      expect(c.read(currentTrackProvider)!.automationCues, [_marker, _program]);
      expect(c.read(currentTrackProvider)!.midiClockEnabled, true);
      expect(engine.midiClock, true);
    });

    test('load applies cues and clock, opens the saved output only when MIDI is used, and fails if cues are rejected', () async {
      await MidiPreferencesStore(directoryResolver: () async => dir).saveOutputId('a');
      final engine = FakeEngine()..midiDevices = const [MidiDevice('a', 'Porta A')];
      final c = _container(engine, dir);
      final n = c.read(currentTrackProvider.notifier);
      expect(await n.load(sampleTrack(id: 'plain')), true);
      expect(engine.openedMidi, isNull);
      final withMidi = sampleTrack(id: 'midi').copyWith(automationCues: [_marker, _program], midiClockEnabled: true);
      expect(await n.load(withMidi), true);
      expect(engine.configuredCues, [_marker, _program]);
      expect(engine.midiClock, true);
      expect(engine.openedMidi, 'a');
      engine.failCues = true;
      expect(await n.load(withMidi.copyWith(title: 'again')), false);
      expect(c.read(currentTrackProvider), isNull);
    });

    test('fired cue indexes from the engine reach the interface', () async {
      final engine = FakeEngine();
      final c = _container(engine, dir);
      c.read(currentTrackProvider.notifier)
        ..setLoadedTrack(sampleTrack(id: 'song'))
        ..updateAutomation('song', [_marker, _program], false);
      c.read(transportProvider);
      engine.firedCues.addAll([0, 1]);
      await Future<void>.delayed(const Duration(milliseconds: 250));
      expect(c.read(firedAutomationProvider), _program);
      engine.firedCues.add(99);  // out of range: ignored
      await Future<void>.delayed(const Duration(milliseconds: 250));
      expect(c.read(firedAutomationProvider), _program);
    });
  });

  group('MidiScreen', () {
    testWidgets('adds a program change, toggles the clock, picks an output and deletes', (tester) async {
      tester.view.physicalSize = const Size(400, 900);
      tester.view.devicePixelRatio = 1;
      addTearDown(tester.view.resetPhysicalSize);
      addTearDown(tester.view.resetDevicePixelRatio);
      final engine = FakeEngine()..midiDevices = const [MidiDevice('a', 'Porta A')];
      final c = _container(engine, dir);
      c.read(currentTrackProvider.notifier).setLoadedTrack(sampleTrack(id: 'song'));
      await tester.pumpWidget(UncontrolledProviderScope(container: c, child: const MaterialApp(home: MidiScreen(trackId: 'song'))));
      await tester.runAsync(() => Future<void>.delayed(const Duration(milliseconds: 100)));
      await tester.pump();
      expect(find.text('Adicione automações à música.'), findsOneWidget);

      await tester.tap(find.byKey(const Key('midi-clock')));
      await tester.pump();
      expect(engine.midiClock, true);

      await tester.tap(find.byTooltip('Adicionar automação'));
      await tester.pumpAndSettle();
      await tester.enterText(find.byKey(const Key('cue-label')), 'Preset 5');
      await tester.enterText(find.byKey(const Key('cue-time')), '12,5');
      await tester.tap(find.byKey(const Key('cue-kind')));
      await tester.pumpAndSettle();
      await tester.tap(find.text('Program Change').last);
      await tester.pumpAndSettle();
      await tester.enterText(find.byKey(const Key('cue-data1')), '300');
      await tester.tap(find.text('Salvar'));
      await tester.pumpAndSettle();
      expect(find.text('Use 0 a 127'), findsOneWidget);
      await tester.enterText(find.byKey(const Key('cue-data1')), '5');
      await tester.tap(find.text('Salvar'));
      await tester.pumpAndSettle();
      expect(engine.configuredCues.single.midiBytes, [0xC0, 5]);
      expect(engine.configuredCues.single.timeSeconds, 12.5);
      expect(find.textContaining('Program Change 5'), findsOneWidget);

      engine.failCues = true;
      await tester.tap(find.byTooltip('Excluir automação'));
      await tester.pumpAndSettle();
      expect(find.text('Não foi possível aplicar as automações.'), findsOneWidget);
      expect(c.read(currentTrackProvider)!.automationCues.length, 1);
      engine.failCues = false;
      await tester.pump(const Duration(seconds: 5));
      await tester.tap(find.byTooltip('Excluir automação'));
      await tester.pumpAndSettle();
      expect(c.read(currentTrackProvider)!.automationCues, isEmpty);
      await tester.pumpWidget(const SizedBox.shrink());
      c.dispose();
    });
  });

  group('native FFI', () {
    test('real ABI validates cues, lists outputs without hardware and refuses MIDI while closed', () async {
      final tmp = await Directory.systemTemp.createTemp('midi-ffi-');
      addTearDown(() => tmp.delete(recursive: true));
      final song = writeSineWav('${tmp.path}/song.wav', seconds: 5);
      final engine = WTracksEngine()..initialise();
      addTearDown(engine.shutdown);
      expect(engine.configureCues([_marker]), false, reason: 'no track loaded');
      expect(await engine.loadTrackAsync('midi-ffi', [song.path]), true, reason: engine.lastError);
      expect(engine.configureCues([_marker, _program, _cc, _note]), true, reason: engine.lastError);
      expect(engine.configureCues([_program.copyWith(timeSeconds: 99)]), false);
      expect(engine.configureCues(const []), true);
      expect(engine.pollCues(), isEmpty);
      expect(engine.listMidiOutputs(), isA<List<MidiDevice>>());
      expect(engine.midiOutputOpen, false);
      expect(engine.sendMidi(const [0x90, 60, 100]), false);
      expect(engine.sendMidi(const [0xF8]), false);
      expect(engine.openMidiOutput('does-not-exist'), false);
      engine.setMidiClockEnabled(true);
      engine.setMidiClockEnabled(false);
      expect(engine.midiDroppedCount, 0);
    }, skip: !nativeEngineAvailable() ? 'Native library unavailable' : false);
  });
}
