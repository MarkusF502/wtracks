import 'dart:async';

import 'package:flutter/foundation.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/automation_cue.dart';
import '../models/control_mapping.dart';
import '../services/control_mapping_store.dart';
import 'engine_provider.dart';
import '../services/diagnostics_log.dart';
import 'transition_provider.dart';

final controlMappingStoreProvider = Provider<ControlMappingStore>((ref) => ControlMappingStore());

@immutable
class ControlState {
  final List<ControlMapping> mappings;
  final List<MidiDevice> inputs;
  final String? inputId;
  final bool inputOpen;
  final ControlAction? learning; // aguardando a próxima mensagem MIDI para esta ação
  final List<int>? lastMessage;
  const ControlState({this.mappings = defaultKeyboardMappings, this.inputs = const [], this.inputId, this.inputOpen = false,
      this.learning, this.lastMessage});
  ControlState copyWith({List<ControlMapping>? mappings, List<MidiDevice>? inputs, Object? inputId = _keep, bool? inputOpen,
          Object? learning = _keep, Object? lastMessage = _keep}) =>
      ControlState(
        mappings: mappings ?? this.mappings,
        inputs: inputs ?? this.inputs,
        inputId: identical(inputId, _keep) ? this.inputId : inputId as String?,
        inputOpen: inputOpen ?? this.inputOpen,
        learning: identical(learning, _keep) ? this.learning : learning as ControlAction?,
        lastMessage: identical(lastMessage, _keep) ? this.lastMessage : lastMessage as List<int>?,
      );
  static const _keep = Object();

  ControlMapping? midiFor(ControlAction action) =>
      mappings.where((m) => m.mappingID == action.name && !m.isKeyboard).firstOrNull;
  ControlMapping? keyFor(ControlAction action) => mappings.where((m) => m.mappingID == action.name && m.isKeyboard).firstOrNull;
}

/// Entrada MIDI e mapeamentos: lê a fila do motor (sem alocar no áudio) a cada [pollInterval] e executa as ações.
/// Leitura para a interface/controle; nenhum agendamento de áudio depende deste timer.
class ControlNotifier extends Notifier<ControlState> {
  static const pollInterval = Duration(milliseconds: 20);
  Timer? _timer;
  bool _disposed = false;

  @override
  ControlState build() {
    ref.onDispose(() {
      _disposed = true;
      _timer?.cancel();
    });
    _load(ref.read(controlMappingStoreProvider));
    _timer = Timer.periodic(pollInterval, (_) => _poll());
    return const ControlState();
  }

  Future<void> _load(ControlMappingStore store) async {
    final (mappings, inputId) = await store.load();
    final problem = store.lastProblem;
    if (problem != null && !_disposed) {
      try {
        ref.read(diagnosticsProvider.notifier).error(problem);
      } on StateError {
        debugPrint('Preferências: $problem');
      }
    }
    if (_disposed) return;
    state = state.copyWith(mappings: mappings, inputId: inputId);
    if (inputId != null) await selectInput(inputId, persist: false);
  }

  Future<void> _persist() async {
    try {
      await ref.read(controlMappingStoreProvider).save(state.mappings, state.inputId);
    } on Exception catch (e) {
      debugPrint('Não foi possível salvar os mapeamentos: $e');
    }
  }

  void refreshInputs() {
    final engine = ref.read(engineProvider);
    state = state.copyWith(inputs: engine.listMidiInputs(), inputOpen: engine.midiInputOpen);
  }

  Future<bool> selectInput(String? id, {bool persist = true}) async {
    final engine = ref.read(engineProvider);
    if (id == null) {
      engine.closeMidiInput();
    } else if (!engine.openMidiInput(id)) {
      state = state.copyWith(inputOpen: false, inputId: id);
      return false;
    }
    state = state.copyWith(inputId: id, inputOpen: id != null);
    if (persist) await _persist();
    return true;
  }

  /// A próxima mensagem MIDI recebida vira o mapeamento de [action] (null cancela).
  void learn(ControlAction? action) => state = state.copyWith(learning: action);

  Future<void> setMapping(ControlAction action, ControlMapping? mapping, {required bool keyboard}) async {
    final others = state.mappings.where((m) => !(m.mappingID == action.name && m.isKeyboard == keyboard));
    // A tecla/mensagem passa a valer só para esta ação.
    final clean = mapping == null
        ? others
        : others.where((m) => !(m.isKeyboard == mapping.isKeyboard &&
            (mapping.isKeyboard ? m.stringValue1 == mapping.stringValue1 : m.mappingTypeID == mapping.mappingTypeID && m.intValue1 == mapping.intValue1 && m.intValue2 == mapping.intValue2)));
    state = state.copyWith(mappings: [...clean, ?mapping]);
    await _persist();
  }

  void _poll() {
    if (_disposed) return;
    final messages = ref.read(engineProvider).pollMidiInput();
    for (final message in messages) {
      handleMidi(message);
    }
  }

  /// Uma mensagem recebida: completa o aprendizado ou dispara as ações mapeadas.
  void handleMidi(List<int> message) {
    state = state.copyWith(lastMessage: message);
    final learning = state.learning;
    if (learning != null) {
      final mapping = ControlMapping.learn(learning, message);
      if (mapping != null) {
        state = state.copyWith(learning: null);
        unawaited(setMapping(learning, mapping, keyboard: false));
      }
      return;
    }
    for (final mapping in state.mappings) {
      final action = mapping.action;
      if (action != null && mapping.matches(message)) unawaited(performControlAction(ref, action));
    }
  }

  Future<void> perform(ControlAction action) => performControlAction(ref, action);

  /// Tecla pressionada ([keyLabel] = LogicalKeyboardKey.keyLabel). true se havia ação para ela.
  bool handleKey(String keyLabel) {
    final mapping = state.mappings.where((m) => m.isKeyboard && m.stringValue1 == keyLabel).firstOrNull;
    final action = mapping?.action;
    if (action == null) return _handleSongNumber(keyLabel);
    unawaited(performControlAction(ref, action));
    return true;
  }

  /// Teclas 1..9 sem mapeamento: música N da setlist. Tocando, entra por crossfade ao vivo; parado, é carregada (Playback: "Keyboard
  /// Numbers: while playing = Live Crossfade to corresponding song in setlist").
  bool _handleSongNumber(String keyLabel) {
    final number = int.tryParse(keyLabel);
    final session = ref.read(setlistSessionProvider);
    if (number == null || number < 1 || number > 9 || session == null || number > session.setlist.tracks.length) return false;
    if (ref.read(engineProvider).isPlaying) {
      unawaited(ref.read(transitionProvider.notifier).liveCrossfade(number - 1));
    } else {
      unawaited(ref.read(setlistSessionProvider.notifier).go(number - 1));
    }
    return true;
  }
}

final controlProvider = NotifierProvider<ControlNotifier, ControlState>(ControlNotifier.new);

/// Executa uma ação de controle sobre o transporte e a música carregada.
Future<void> performControlAction(Ref ref, ControlAction action) async {
  final transport = ref.read(transportProvider.notifier);
  final engine = ref.read(engineProvider);
  final track = ref.read(currentTrackProvider);
  final notifier = ref.read(currentTrackProvider.notifier);
  switch (action) {
    case ControlAction.playPause:
      engine.isPlaying ? await transport.pause() : await transport.play();
    case ControlAction.stop:
      await transport.stop();
    case ControlAction.nextSong:
      await ref.read(setlistSessionProvider.notifier).next();
    case ControlAction.previousSong:
      await ref.read(setlistSessionProvider.notifier).previous();
    case ControlAction.fadeOut:
      transport.fadeToggle();
    case ControlAction.toggleClick:
      final enabled = !ref.read(clickEnabledProvider);
      ref.read(clickEnabledProvider.notifier).state = enabled;
      engine.setClickEnabled(enabled);
    case ControlAction.toggleGuides:
      if (track != null) await notifier.updateGuides(track.id, track.guideCues, !track.guidesEnabled);
    case ControlAction.toggleAutomation:
      if (track != null) notifier.setAutomationEnabled(!track.automationEnabled);
    case ControlAction.nextSection || ControlAction.previousSection:
      if (track == null || track.sections.isEmpty) return;
      final position = engine.currentPositionSeconds;
      final starts = [for (final s in track.sections) s.startSeconds];
      // Seção anterior: o início da seção atual se já passou 1 s dela (como "voltar" de faixa), senão a anterior.
      final target = action == ControlAction.nextSection
          ? starts.where((s) => s > position + 1e-3).firstOrNull
          : starts.reversed.where((s) => s < position - 1.0).firstOrNull ?? starts.first;
      if (target != null) transport.seekTo(target);
  }
}
