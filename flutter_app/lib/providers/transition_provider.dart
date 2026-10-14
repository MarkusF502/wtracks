import 'dart:async';
import 'dart:math' as math;

import 'package:flutter/foundation.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/track.dart';
import '../services/click_grid.dart';
import '../services/diagnostics_log.dart';
import '../native/wtracks_bindings.dart';
import 'engine_provider.dart';

enum TransitionPhase {
  /// Nada preparado.
  idle,

  /// A próxima música está sendo carregada no deck 1.
  preparing,

  /// Carregada e agendada no motor; a mistura começa quando a música atual chega à janela (ou quando um laço ativo é solto).
  armed,

  /// As duas músicas tocam juntas; o hand-off acontece quando a janela termina.
  running,
}

@immutable
class TransitionState {
  final TransitionPhase phase;

  /// Posição da próxima música na setlist.
  final int? nextIndex;

  /// Crossfade ao vivo (toque duplo num cartão) em vez da transição da música.
  final bool live;
  const TransitionState({this.phase = TransitionPhase.idle, this.nextIndex, this.live = false});
  @override
  bool operator ==(Object other) => other is TransitionState && other.phase == phase && other.nextIndex == nextIndex && other.live == live;
  @override
  int get hashCode => Object.hash(phase, nextIndex, live);
}

/// Transições entre músicas com o segundo deck (AutoLink, Sobreposição, Transição Cruzada e o crossfade ao vivo). Playback: a próxima
/// música é um segundo `Sequencer` pré-carregado perto do fim (FUN_1004f25d4); aqui a próxima é carregada com antecedência no deck 1 do
/// motor, agendada para a janela e, quando a janela termina, o motor troca os decks (hand-off) e o Dart adota a música que entrou.
///
/// Constantes do Playback (transition.c, FUN_1004f25d4): `songTransitionBufferOffset` 0,064 s, duração 5 s limitada pelo que falta
/// da atual e pela primeira seção da próxima. Escolhas próprias: pré-carregar [preloadLeadSeconds] antes da janela (o iOS pré-carrega na
/// hora; aqui o carregamento é lento), não pré-carregar com laço ativo, e a janela segue o motor em amostras (o original anda em
/// passos de 0,2 s).
class TransitionController extends Notifier<TransitionState> {
  static const preloadLeadSeconds = 20.0;
  static const maxWindowSeconds = 5.0;
  static const bufferOffsetSeconds = 0.064;
  static const minLiveStartAhead = 0.15;

  int _epoch = 0;
  String? _failedKey, _armedKey;

  @override
  TransitionState build() => const TransitionState();

  // ---- plano ----

  /// Início e duração da janela, em tempo da música que toca.
  ({double start, double duration, int kind}) windowFor(SongTransition kind, double end, Track next) {
    if (kind == SongTransition.autoLink) return (start: end - bufferOffsetSeconds, duration: bufferOffsetSeconds, kind: 0);
    // Sobreposição e Transição Cruzada: 5 s, ou menos se a primeira seção da próxima for mais curta.
    final first = next.sections.isEmpty ? null : next.sections.first;
    final firstLength = first == null ? maxWindowSeconds : first.playEnd - first.playStart;
    final duration = math.max(0.05, math.min(maxWindowSeconds, firstLength));
    return (start: end - duration, duration: duration, kind: kind == SongTransition.crossfade ? 1 : 0);
  }

  double _endOf(Track track, WTracksEngine engine) => track.endSeconds ?? engine.totalLengthSeconds;

  ({SongTransition kind, int next})? _plan(SetlistSession session, Track track) {
    if (!track.transition.isMixed) return null;
    final next = session.index + 1;
    if (next >= session.setlist.tracks.length) return null; // a última música não tem para onde ir
    return (kind: track.transition, next: next);
  }

  Track _library(Track listed) => ref.read(trackLibraryProvider).where((t) => t.id == listed.id).firstOrNull ?? listed;

  // ---- ciclo ----

  /// Chamado a cada tick do transporte (100 ms).
  void tick() {
    final session = ref.read(setlistSessionProvider);
    final track = ref.read(currentTrackProvider);
    if (state.phase == TransitionPhase.running || state.phase == TransitionPhase.preparing) return;
    if (session == null || track == null || session.current.id != track.id) {
      if (state.phase != TransitionPhase.idle) cancel();
      return;
    }
    final engine = ref.read(engineProvider);
    final plan = _plan(session, track);
    final key = plan == null ? null : _keyOf(track, session.setlist.tracks[plan.next], plan.kind);
    if (state.phase == TransitionPhase.armed) {
      // Um crossfade ao vivo começa sozinho no motor; só se o agendamento sumiu (parar, carregar outra música) é que se desiste.
      final stale = state.live ? !engine.transitionScheduled : (plan == null || !engine.transitionScheduled || _armedKey != key);
      if (stale) cancel();
      return;
    }
    if (plan == null || key == null || !engine.isPlaying) return;
    if (_failedKey == key) return;
    if (engine.loopState[0] == 1) return; // sem pré-carga com laço ativo (Playback)
    final nextTrack = _library(session.setlist.tracks[plan.next]);
    final window = windowFor(plan.kind, _endOf(track, engine), nextTrack);
    if (engine.currentPositionSeconds < math.max(1.0, window.start - preloadLeadSeconds)) return;
    unawaited(_prepare(session, track, plan.next, plan.kind));
  }

  String _keyOf(Track track, Track next, SongTransition kind) => '${track.id}>${next.id}:${kind.name}:${track.endSeconds}';

  Future<void> _prepare(SetlistSession session, Track track, int nextIndex, SongTransition kind) async {
    final epoch = ++_epoch;
    final nextTrack = _library(session.setlist.tracks[nextIndex]);
    final key = _keyOf(track, session.setlist.tracks[nextIndex], kind);
    state = TransitionState(phase: TransitionPhase.preparing, nextIndex: nextIndex);
    final loaded = await ref.read(nextTrackProvider.notifier).load(nextTrack);
    if (epoch != _epoch) return; // cancelado enquanto carregava (cancel() já descarregou)
    final engine = ref.read(engineProvider);
    if (!loaded) {
      _failedKey = key;
      ref.read(diagnosticsProvider.notifier).error('Transição: não foi possível pré-carregar "${nextTrack.title}".');
      await _discard();
      return;
    }
    final window = windowFor(kind, _endOf(track, engine), nextTrack);
    if (!engine.scheduleTransition(window.kind, window.start, window.duration)) {
      _failedKey = key;
      ref.read(diagnosticsProvider.notifier).error('Transição: o motor recusou a janela (${engine.lastError}).');
      await _discard();
      return;
    }
    _armedKey = key;
    state = TransitionState(phase: TransitionPhase.armed, nextIndex: nextIndex);
  }

  /// Eventos do motor (lidos pelo transporte): devolve true se a transição assumiu o fim da música.
  bool handleEvents(int events) {
    final started = events & WTracksEngine.transportEventTransitionStarted != 0;
    final finished = events & WTracksEngine.transportEventTransitionFinished != 0;
    final ended = events & WTracksEngine.transportEventEndReached != 0;
    if (started && state.phase == TransitionPhase.armed) {
      state = TransitionState(phase: TransitionPhase.running, nextIndex: state.nextIndex, live: state.live);
    }
    if (finished && (state.phase == TransitionPhase.armed || state.phase == TransitionPhase.running)) {
      unawaited(_handoff());
      return true;
    }
    if (ended) {
      if (state.phase == TransitionPhase.armed || state.phase == TransitionPhase.running) return true;
      if (state.phase == TransitionPhase.preparing) cancel(); // acabou antes de a próxima carregar: segue a transição simples
    }
    return false;
  }

  Future<void> _handoff() async {
    ++_epoch;
    final index = state.nextIndex;
    final engine = ref.read(engineProvider);
    final session = ref.read(setlistSessionProvider);
    final nextNotifier = ref.read(nextTrackProvider.notifier);
    if (index == null || session == null || nextNotifier.state == null || !engine.handoff()) {
      ref.read(diagnosticsProvider.notifier).error('Transição: o hand-off falhou (${engine.lastError}).');
      await _discard();
      return;
    }
    ref.read(currentTrackProvider.notifier).adoptFrom(nextNotifier);
    ref.read(setlistSessionProvider.notifier).moveTo(index);
    // A música que saiu agora está no deck 1, parada: libera a memória.
    ref.read(nextEngineProvider).unloadTrack();
    nextNotifier.forget();
    ref.read(transportProvider.notifier).refresh();
    _armedKey = null;
    state = const TransitionState();
  }

  /// Desiste da transição preparada ou em curso (troca de música, nova edição da setlist...).
  void cancel() {
    ++_epoch;
    _armedKey = null;
    if (state.phase == TransitionPhase.idle) return;
    unawaited(_discard());
  }

  Future<void> _discard() async {
    ref.read(engineProvider).cancelTransition();
    state = const TransitionState();
    await ref.read(nextTrackProvider.notifier).unload();
  }

  // ---- crossfade ao vivo ----

  /// Duração do crossfade ao vivo (Playback FUN_1004f9cd8): 2 compassos no andamento inicial da próxima música; 2 s se ela não tem
  /// andamento. (Os casos de 5 s para o tipo de conteúdo 0xd e de "1 compasso mais a contagem" ficam de fora: não temos esses tipos.)
  static double liveDuration(Track next) {
    final click = next.clickSettings;
    if (!click.isValid) return 2.0;
    final beat = 60.0 / click.bpm * click.bpmUnit / click.timeSignatureDenominator;
    return (2 * click.timeSignatureNumerator * beat).clamp(0.5, 30.0);
  }

  /// Início do crossfade ao vivo: o próximo tempo do click a pelo menos 0,15 s, menos uma semicolcheia (Playback FUN_1004f9cd8).
  static double liveStart(Track current, double position) {
    final grid = ClickGrid.of(current.clickSettings, current.tempoChanges);
    final beat = grid.nextBeatAtOrAfter(position + minLiveStartAhead);
    return math.max(position, beat - 60.0 / current.clickSettings.bpm / 4);
  }

  /// Toque duplo no cartão de outra música enquanto toca: entra por crossfade (teclas numéricas fazem o mesmo).
  Future<bool> liveCrossfade(int index) async {
    final session = ref.read(setlistSessionProvider);
    final track = ref.read(currentTrackProvider);
    final engine = ref.read(engineProvider);
    if (session == null || track == null || !engine.isPlaying) return false;
    if (index < 0 || index >= session.setlist.tracks.length || index == session.index) return false;
    if (state.phase == TransitionPhase.running) return false;
    cancel();
    final epoch = ++_epoch;
    state = TransitionState(phase: TransitionPhase.preparing, nextIndex: index, live: true);
    final nextTrack = _library(session.setlist.tracks[index]);
    final loaded = await ref.read(nextTrackProvider.notifier).load(nextTrack);
    if (epoch != _epoch) return false;
    if (!loaded || !engine.isPlaying) {
      await _discard();
      return false;
    }
    final start = liveStart(track, engine.currentPositionSeconds);
    if (!engine.scheduleTransition(1, start, liveDuration(nextTrack))) {
      await _discard();
      return false;
    }
    _armedKey = null;
    state = TransitionState(phase: TransitionPhase.armed, nextIndex: index, live: true);
    return true;
  }
}

final transitionProvider = NotifierProvider<TransitionController, TransitionState>(TransitionController.new);
