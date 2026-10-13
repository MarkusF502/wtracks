import 'dart:convert';
import 'dart:io';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/automation_cue.dart';
import 'package:flutter_app/models/control_mapping.dart';
import 'package:flutter_app/models/song_section.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/native/wtracks_bindings.dart';
import 'package:flutter_app/providers/control_provider.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/screens/control_mapping_screen.dart';
import 'package:flutter_app/screens/midi_screen.dart';
import 'package:flutter_app/services/control_mapping_store.dart';
import 'harness/harness_support.dart';

class _Store extends ControlMappingStore {
  List<ControlMapping> mappings;
  String? inputId;
  _Store([this.mappings = defaultKeyboardMappings, this.inputId]);
  @override
  Future<(List<ControlMapping>, String?)> load() async => (mappings, inputId);
  @override
  Future<void> save(List<ControlMapping> mappings, String? inputId) async {
    this.mappings = mappings;
    this.inputId = inputId;
  }
}

const _bus = MidiBus(id: 'kb', title: 'Teclado', channel: 5);
const _pc = AutomationCue(id: 'pc', label: 'PC', timeSeconds: 1, kind: AutomationMessageKind.programChange, channel: 1, data1: 3, busId: 'kb');
const _note = AutomationCue(id: 'n', label: 'N', timeSeconds: 2, kind: AutomationMessageKind.noteOn, channel: 2, data1: 60, data2: 100,
    durationSeconds: 0.5, disableLoop: true);
const _other = AutomationCue(id: 'o', label: 'O', timeSeconds: 1.5, kind: AutomationMessageKind.controlChange, channel: 1, data1: 7, data2: 1,
    bankId: 'b2');

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  mockBackgroundChannel();

  group('models', () {
    test('cue, bank and bus JSON; legacy cues default; tracks keep banks, buses and the active bank', () {
      final back = AutomationCue.fromJson(jsonDecode(jsonEncode(_note.toJson())) as Map<String, dynamic>);
      expect(back, _note);
      expect(AutomationCue.fromJson({'id': 'x', 'label': 'x', 'timeSeconds': 1, 'kind': 'none'}).durationSeconds, 0);
      expect(() => AutomationCue.fromJson({..._note.toJson(), 'durationSeconds': -1}), throwsFormatException);
      final track = sampleTrack(id: 's').copyWith(
          midiBanks: const [MidiBank(id: 'b2', title: 'Banco 2')], midiBuses: const [_bus], activeMidiBankId: 'b2', automationCues: [_pc, _other]);
      final t = Track.fromJson(jsonDecode(jsonEncode(track.toJson())) as Map<String, dynamic>);
      expect(t.midiBanks.single.title, 'Banco 2');
      expect(t.midiBuses.single, _bus);
      expect(t.activeMidiBankId, 'b2');
      expect(t.copyWith(activeMidiBankId: null).activeMidiBankId, isNull);
      expect(() => MidiBus.fromJson({'id': 'a', 'title': 'a', 'channel': 17}), throwsFormatException);
    });

    test('schedule: active bank only, bus channel, disabled buses skip, notes get their note-off, sources point back', () {
      final schedule = buildMidiSchedule([_pc, _other, _note], [_bus], null);
      expect(schedule, const [
        ScheduledMidi(1, [0xC4, 3], 0),
        ScheduledMidi(2, [0x91, 60, 100], 2, disableLoop: true),
        ScheduledMidi(2.5, [0x81, 60, 0], 2, disableLoop: true),
      ]);
      expect(buildMidiSchedule([_pc, _other, _note], [_bus], 'b2'), const [ScheduledMidi(1.5, [0xB0, 7, 1], 1)]);
      expect(buildMidiSchedule([_pc], [_bus.copyWith(allChannels: true)], null).single.bytes, [0xC0, 3]);
      expect(buildMidiSchedule([_pc], [_bus.copyWith(enabled: false)], null), isEmpty);
      expect(buildMidiSchedule([_pc], const [], null), isEmpty, reason: 'unknown bus');
    });

    test('section cues copy relative and paste replacing the target section of the bank', () {
      const a = AutomationCue(id: 'a', label: 'a', timeSeconds: 11, kind: AutomationMessageKind.programChange, data1: 1);
      const b = AutomationCue(id: 'b', label: 'b', timeSeconds: 19.5, kind: AutomationMessageKind.programChange, data1: 2);
      const c = AutomationCue(id: 'c', label: 'c', timeSeconds: 31, kind: AutomationMessageKind.programChange, data1: 3);
      const otherBank = AutomationCue(id: 'x', label: 'x', timeSeconds: 32, bankId: 'z');
      final copied = copySectionCues([a, b, c, otherBank], 10, 20);
      expect(copied.map((e) => e.timeSeconds), [1, 9.5]);
      var n = 0;
      final pasted = pasteSectionCues([a, b, c, otherBank], copied, 30, 38, () => 'new${n++}');
      expect(pasted.map((e) => (e.id, e.timeSeconds)), [('a', 11.0), ('b', 19.5), ('new0', 31.0), ('x', 32.0)]);
    });

    test('control mappings: learn, match, JSON and defaults', () {
      final note = ControlMapping.learn(ControlAction.playPause, const [0x92, 36, 90])!;
      expect((note.type, note.intValue1, note.intValue2), (MappingType.midiNote, 3, 36));
      expect(note.matches(const [0x92, 36, 1]), true);
      expect(note.matches(const [0x92, 36, 0]), false, reason: 'note on with velocity 0 is a release');
      expect(note.matches(const [0x93, 36, 90]), false);
      expect(note.copyWithAnyChannel().matches(const [0x93, 36, 90]), true);
      final cc = ControlMapping.learn(ControlAction.fadeOut, const [0xB0, 64, 127])!;
      expect(cc.matches(const [0xB0, 64, 127]), true);
      expect(cc.matches(const [0xB0, 64, 10]), false);
      expect(ControlMapping.learn(ControlAction.stop, const [0xC5, 9])!.matches(const [0xC5, 9]), true);
      expect(ControlMapping.learn(ControlAction.stop, const [0x80, 9, 0]), isNull);
      expect(ControlMapping.fromJson(jsonDecode(jsonEncode(cc.toJson()))), cc);
      expect(ControlMapping.fromJson({'mappingID': 'fly', 'mappingTypeID': 0}), isNull);
      expect(defaultKeyboardMappings.every((m) => m.isValid && m.isKeyboard), true);
    });

    test('mapping store: defaults without a file, round trip, corrupt file', () async {
      final dir = await Directory.systemTemp.createTemp('mapping-store-');
      addTearDown(() => dir.delete(recursive: true));
      final store = ControlMappingStore(directoryResolver: () async => dir);
      expect((await store.load()).$1, defaultKeyboardMappings);
      final m = ControlMapping.learn(ControlAction.stop, const [0xC0, 1])!;
      await store.save([m], 'in-1');
      final (loaded, input) = await store.load();
      expect(loaded, [m]);
      expect(input, 'in-1');
      File('${dir.path}/wtracks_data/control_mappings.json').writeAsStringSync('[');
      expect((await store.load()).$1, defaultKeyboardMappings);
    });
  });

  group('providers', () {
    test('updateMidi validates banks, sends the schedule and fired cues map back through it', () async {
      final engine = FakeEngine();
      final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine)]);
      addTearDown(c.dispose);
      final n = c.read(currentTrackProvider.notifier);
      expect(await n.load(sampleTrack(id: 's').copyWith(automationCues: [_pc, _other, _note], midiBuses: const [_bus],
          midiBanks: const [MidiBank(id: 'b2', title: 'B')])), true);
      expect(engine.midiSchedule.length, 3);
      expect(n.updateMidi('s', activeBankId: 'missing'), false);
      expect(n.updateMidi('s', activeBankId: 'b2'), true);
      expect(engine.midiSchedule.single.bytes, [0xB0, 7, 1]);
      expect(n.midiSchedule.single.source, 1);
      expect(n.updateMidi('s', buses: const [_bus, _bus]), false, reason: 'duplicate bus ids');
    });

    test('MIDI input actions, learning, keyboard and section navigation', () async {
      final engine = FakeEngine()
        ..midiInputs = const [MidiDevice('in-1', 'Pedal')]
        ..position = 12;
      final store = _Store([...defaultKeyboardMappings, ControlMapping.learn(ControlAction.playPause, const [0x90, 36, 100])!], 'in-1');
      final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine), controlMappingStoreProvider.overrideWithValue(store)]);
      addTearDown(c.dispose);
      c.read(currentTrackProvider.notifier).setLoadedTrack(sampleTrack(id: 's').copyWith(sections: const [
        SongSection(id: 'a', name: 'A', startSeconds: 0, endSeconds: 10),
        SongSection(id: 'b', name: 'B', startSeconds: 10, endSeconds: 20),
        SongSection(id: 'c', name: 'C', startSeconds: 20, endSeconds: 30),
      ]));
      final control = c.read(controlProvider.notifier);
      await Future<void>.delayed(Duration.zero);
      expect(engine.openInput, 'in-1');
      engine.injectMidiInput(const [0x90, 36, 100]);
      await Future<void>.delayed(const Duration(milliseconds: 60));
      expect(engine.calls, contains('play'));
      control.learn(ControlAction.fadeOut);
      control.handleMidi(const [0xB0, 20, 127]);
      expect(c.read(controlProvider).learning, isNull);
      expect(c.read(controlProvider).midiFor(ControlAction.fadeOut)!.describe(), 'CC 20 · canal 1');
      expect(store.mappings.any((m) => m.mappingID == 'fadeOut' && !m.isKeyboard), true);
      expect(control.handleKey('Arrow Right'), true);
      await Future<void>.delayed(Duration.zero);
      expect(engine.calls.last, 'seek(20.0)');
      expect(control.handleKey('Arrow Left'), true);
      await Future<void>.delayed(Duration.zero);
      expect(engine.calls.last, 'seek(10.0)');
      expect(control.handleKey('Q'), false);
      await control.setMapping(ControlAction.stop, const ControlMapping(mappingID: 'stop', mappingTypeID: 3, stringValue1: 'Arrow Right'),
          keyboard: true);
      expect(c.read(controlProvider).keyFor(ControlAction.nextSection), isNull, reason: 'a key belongs to one action');
      expect(await control.selectInput('missing'), false);
      expect(await control.selectInput(null), true);
      expect(engine.openInput, isNull);
    });
  });

  testWidgets('mapping screen learns a MIDI message and captures a key', (tester) async {
    final engine = FakeEngine()..midiInputs = const [MidiDevice('in-1', 'Pedal')];
    final store = _Store();
    final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine), controlMappingStoreProvider.overrideWithValue(store)]);
    addTearDown(c.dispose);
    await tester.pumpWidget(UncontrolledProviderScope(container: c, child: const MaterialApp(home: ControlMappingScreen())));
    await tester.pump(const Duration(milliseconds: 50));
    await tester.tap(find.byTooltip('Aprender MIDI: ${ControlAction.stop.label}'));
    await tester.pump();
    expect(find.text('Aguardando MIDI… · Tecla: —'), findsOneWidget);
    engine.injectMidiInput(const [0xC1, 7]);
    await tester.pump(const Duration(milliseconds: 60));
    expect(find.text('PC 7 · canal 2 · Tecla: —'), findsOneWidget);
    await tester.tap(find.byTooltip('Definir tecla: ${ControlAction.stop.label}'));
    await tester.pumpAndSettle();
    await tester.sendKeyEvent(LogicalKeyboardKey.keyS);
    await tester.pumpAndSettle();
    expect(c.read(controlProvider).keyFor(ControlAction.stop)!.stringValue1, 'S');
    await tester.pumpWidget(const SizedBox.shrink());
    c.dispose();
  });

  testWidgets('MIDI screen creates a bank, adds a bus and copies section cues', (tester) async {
    tester.view.physicalSize = const Size(420, 1400);
    tester.view.devicePixelRatio = 1;
    addTearDown(tester.view.resetPhysicalSize);
    addTearDown(tester.view.resetDevicePixelRatio);
    final engine = FakeEngine();
    final persistence = InMemoryPersistence();
    final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine), persistenceServiceProvider.overrideWithValue(persistence)]);
    addTearDown(c.dispose);
    const pc = AutomationCue(id: 'p', label: 'Intro PC', timeSeconds: 1, kind: AutomationMessageKind.programChange, data1: 4);
    c.read(currentTrackProvider.notifier).setLoadedTrack(sampleTrack(id: 'song').copyWith(automationCues: const [pc], sections: const [
      SongSection(id: 'a', name: 'Intro', startSeconds: 0, endSeconds: 10),
      SongSection(id: 'b', name: 'Verso', startSeconds: 10, endSeconds: 20),
    ]));
    await c.read(trackLibraryProvider.notifier).saveCurrent();
    await tester.pumpWidget(UncontrolledProviderScope(container: c, child: const MaterialApp(home: MidiScreen(trackId: 'song'))));
    await tester.pumpAndSettle();

    await tester.tap(find.text('Cues por seção'));
    await tester.pumpAndSettle();
    await tester.tap(find.byTooltip('Copiar cues: Intro'));
    await tester.pumpAndSettle();
    await tester.tap(find.byTooltip('Colar cues: Verso'));
    await tester.pumpAndSettle();
    expect(persistence.tracks['song']!.automationCues.map((e) => e.timeSeconds), [1, 11]);

    await tester.tap(find.text('Buses MIDI (0)'));
    await tester.pumpAndSettle();
    await tester.tap(find.byKey(const Key('add-midi-bus')));
    await tester.pumpAndSettle();
    await tester.enterText(find.byKey(const Key('midi-name')), 'Luzes');
    await tester.tap(find.text('Salvar'));
    await tester.pumpAndSettle();
    expect(persistence.tracks['song']!.midiBuses.single.title, 'Luzes');

    await tester.tap(find.byTooltip('Novo banco MIDI'));
    await tester.pumpAndSettle();
    await tester.enterText(find.byKey(const Key('midi-name')), 'Domingo');
    await tester.tap(find.text('Salvar'));
    await tester.pumpAndSettle();
    final saved = persistence.tracks['song']!;
    expect(saved.midiBanks.single.title, 'Domingo');
    expect(saved.activeMidiBankId, saved.midiBanks.single.id);
    expect(engine.midiSchedule, isEmpty, reason: 'the new bank has no cues yet');
    expect(find.text('Adicione automações à música.'), findsOneWidget);
    await tester.pumpWidget(const SizedBox.shrink());
  });

  test('native FFI: schedule with flags and MIDI input injection', () async {
    final dir = await Directory.systemTemp.createTemp('midi-map-ffi-');
    addTearDown(() => dir.delete(recursive: true));
    final song = writeSineWav('${dir.path}/song.wav', seconds: 3);
    final engine = WTracksEngine()..initialise();
    addTearDown(engine.shutdown);
    expect(await engine.loadTrackAsync('midi-map-ffi', [song.path]), true, reason: engine.lastError);
    expect(engine.configureMidiSchedule(buildMidiSchedule([_pc, _note], [_bus], null)), true, reason: engine.lastError);
    expect(engine.configureMidiSchedule(const [ScheduledMidi(2, [0x90, 1, 1], 0), ScheduledMidi(1, [0x90, 1, 1], 0)]), false);
    expect(engine.injectMidiInput(const [0x90, 60, 100]), true);
    expect(engine.injectMidiInput(const [0xF8]), false);
    expect(engine.pollMidiInput(), [
      [0x90, 60, 100]
    ]);
    expect(engine.openMidiInput('no-such-input'), false);
    expect(engine.listMidiInputs(), isA<List<MidiDevice>>());
  }, skip: !nativeEngineAvailable() ? 'Native library unavailable' : false);
}
