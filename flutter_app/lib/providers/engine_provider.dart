import 'dart:async';

import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/track.dart';
import '../models/song_section.dart';
import 'setlist_provider.dart';
import 'waveform_provider.dart';
import '../native/wtracks_bindings.dart';
import '../services/persistence_service.dart';
import '../services/click_resource_service.dart';

final clickResourceServiceProvider = Provider<ClickResourceService>(
  (ref) => ClickResourceService(),
);
final clickFamiliesProvider = FutureProvider<List<String>>(
  (ref) => ref.read(clickResourceServiceProvider).families(),
);

/// Instância única do engine nativo -- todo o app depende deste provider.
/// keepAlive porque o engine precisa sobreviver enquanto o app estiver
/// rodando, não só enquanto uma tela específica estiver montada.
final engineProvider = Provider<WTracksEngine>((ref) {
  final engine = WTracksEngine();
  final ready = engine.initialise();

  ref.onDispose(engine.shutdown);

  if (!ready) {
    // A tela que consome isso decide como avisar o usuário -- aqui só
    // deixamos registrado pra depuração via wtracks_get_last_error().
    debugPrint('WTracksEngine.initialise() falhou.');
  }

  return engine;
});

/// A música atualmente carregada no engine (ou null se nenhuma).
/// Widgets de mixer/canal leem daqui em vez de perguntar pro engine
/// canal por canal.
class CurrentTrackNotifier extends Notifier<Track?> {
  int _generation = 0;
  bool _disposed = false;
  Future<void> _pending = Future.value();
  int get loadGeneration => _generation;
  String? loadingTrackId;

  @override
  Track? build() {
    ref.onDispose(() { _disposed = true; _generation++; });
    return null;
  }

  /// Serialize native loads: every isolate addresses the same C++ engine.
  /// A superseded result must not publish UI state or mixer settings.
  Future<bool> load(Track track) {
    final generation = ++_generation;
    loadingTrackId = track.id;
    final engine = ref.read(engineProvider);
    final transport = ref.read(transportProvider.notifier);
    final operation = _pending.then((_) async {
      if (_disposed || generation != _generation) return false;
      await transport.stop();
      if (_disposed || generation != _generation) return false;
      try {
        final clickPaths = await ref
            .read(clickResourceServiceProvider)
            .prepare(track.clickSettings.timbreFamily);
        if (_disposed || generation != _generation) return false;
        final loaded = await engine.loadTrackAsync(track.id, track.channelFilePaths,
        );
        if (_disposed || generation != _generation) {
          if (!_disposed && loaded) {
            engine.unloadTrack();
            state = null;
          }
          return false;
        }
        if (!loaded) {
          debugPrint('Falha ao carregar música: ${engine.lastError}');
          return false;
        }
        final bankLoaded = await engine.loadClickBankAsync(clickPaths);
        if (_disposed || generation != _generation) {
          if (!_disposed) engine.unloadTrack();
          return false;
        }
        if (!bankLoaded) {
          engine.unloadTrack();
          state = null;
          return false;
        }
        if (!engine.configureClick(track.clickSettings)) {
          engine.unloadTrack();
          state = null;
          return false;
        }
        state = track;
        for (var i = 0; i < track.channels.length; i++) {
          engine.setChannelVolume(i, track.channels[i].volume);
        }
        _syncEffectiveMutes();
        return true;
      } catch (e) {
        debugPrint('Exceção ao carregar música: $e');
        return false;
      } finally {
        if (generation == _generation) loadingTrackId = null;
      }
    });
    _pending = operation.then((_) {});
    return operation;
  }

  Future<void> unload() {
    final generation = ++_generation;
    loadingTrackId = null;
    final engine = ref.read(engineProvider);
    final stopping = ref.read(transportProvider.notifier).stop();
    final operation = _pending.then((_) async {
      await stopping;
      engine.unloadTrack();
      if (!_disposed && generation == _generation) state = null;
    });
    _pending = operation;
    return operation;
  }

  void setChannelVolume(int index, double volume) {
    final track = state;
    if (track == null) return;

    ref.read(engineProvider).setChannelVolume(index, volume);

    final updatedChannels = [...track.channels];
    updatedChannels[index] = updatedChannels[index].copyWith(volume: volume);
    state = track.copyWith(channels: updatedChannels);
  }

  void setChannelMuted(int index, bool muted) {
    final track = state;
    if (track == null) return;

    final updatedChannels = [...track.channels];
    updatedChannels[index] = updatedChannels[index].copyWith(muted: muted);
    state = track.copyWith(channels: updatedChannels);

    _syncEffectiveMutes();
  }

  /// Alterna solo no canal [index]. Solo não existe no AudioEngine nativo --
  /// é resolvido aqui: quando 1+ canais estão solados, todo canal NÃO
  /// solado recebe mute efetivo no engine, preservando o mute manual do
  /// usuário para quando o solo for desligado.
  void toggleChannelSolo(int index) {
    final track = state;
    if (track == null) return;

    final updatedChannels = [...track.channels];
    updatedChannels[index] =
        updatedChannels[index].copyWith(soloed: !updatedChannels[index].soloed);
    state = track.copyWith(channels: updatedChannels);

    _syncEffectiveMutes();
  }

  /// Recalcula, para cada canal, se ele deve estar mutado de fato no
  /// engine (mute manual OU existe solo ativo e este canal não é ele) e
  /// aplica via setChannelMuted -- sem alterar o campo `muted` do modelo,
  /// que continua refletindo só a intenção manual do usuário.
  void _syncEffectiveMutes() {
    final track = state;
    if (track == null) return;

    final engine = ref.read(engineProvider);
    final anySoloed = track.channels.any((c) => c.soloed);

    for (var i = 0; i < track.channels.length; i++) {
      final channel = track.channels[i];
      final effectiveMuted = channel.muted || (anySoloed && !channel.soloed);
      engine.setChannelMuted(i, effectiveMuted);
    }
  }

  /// Substitui a track atual por [track] sem tocar no engine nativo --
  /// usado pelo [TrackLibraryNotifier.saveCurrent] pra refletir os
  /// `filePath`s atualizados depois que os arquivos de áudio são movidos
  /// pro diretório permanente pelo PersistenceService.
  void setLoadedTrack(Track track) {
    state = track;
  }

  /// Renomeia a track atual (só o estado em memória -- não persiste
  /// sozinho; quem chamar decide se quer também salvar em disco, ex: via
  /// [TrackLibraryNotifier.saveCurrent]).
  void renameCurrent(String title) {
    final track = state;
    if (track == null) return;
    state = track.copyWith(title: title);
  }

  int _loopRequest = 0;
  void cancelLoopPreparation() { ++_loopRequest; }
  bool _loopBusy = false;
  bool get loopBusy => _loopBusy;

  Future<bool> setSectionLoop(SongSection section, {bool queue = false}) {
    final track = state;
    if (track == null || loadingTrackId != null || _loopBusy ||
        !track.sections.any((s) => s.id == section.id && s.startSeconds == section.startSeconds && s.endSeconds == section.endSeconds)) {
      return Future.value(false);
    }
    final generation = _generation;
    final request = _loopRequest;
    _loopBusy = true;
    final operation = _pending.then((_) async {
      try {
        if (_disposed || generation != _generation) return false;
        final engine = ref.read(engineProvider);
        final ok = queue ? await engine.enqueueLoopAsync(section.startSeconds, section.endSeconds)
          : await engine.setLoopAsync(section.startSeconds, section.endSeconds, true);
        if (_disposed || generation != _generation || request != _loopRequest) {
          if (!_disposed) {
            engine.setLoop(0, 0, false);
            ref.read(transportProvider.notifier).refresh();
          }
          return false;
        }
        ref.read(transportProvider.notifier).refresh();
        return ok;
      } catch (e) {
        debugPrint('Falha ao preparar loop: $e');
        return false;
      } finally { _loopBusy = false; }
    });
    _pending = operation.then((_) {});
    return operation;
  }

  bool updateSections(String trackId, List<SongSection> sections) {
    final track = state;
    if (track == null || track.id != trackId || loadingTrackId != null || _loopBusy || !SongSection.validSequence(sections)) return false;
    final engine = ref.read(engineProvider);
    final loop = engine.loopState;
    bool matches(SongSection s, double start, double end) =>
      (s.startSeconds - start).abs() <= 0.001 && (s.endSeconds - end).abs() <= 0.001;
    bool removed(double start, double end) => track.sections.any((s) => matches(s, start, end)) && !sections.any((s) => matches(s, start, end));
    if (loop[0] == 1 && removed(loop[1], loop[2])) {
      if (!engine.setLoop(0, 0, false)) return false;
    } else if (loop[3] == 1 && removed(loop[4], loop[5])) {
      engine.clearQueuedLoop();
    }
    ref.read(transportProvider.notifier).refresh();
    state = track.copyWith(sections: List.unmodifiable(sections));
    return true;
  }

  Future<bool> updateClickTimbre(String family) {
    final track = state;
    if (track == null || loadingTrackId != null) return Future.value(false);
    final generation = _generation;
    final operation = _pending.then((_) async {
      try {
        final paths = await ref
            .read(clickResourceServiceProvider)
            .prepare(family);
        if (_disposed || generation != _generation || state?.id != track.id) {
          return false;
        }
        final engine = ref.read(engineProvider);
        final bankLoaded = await engine.loadClickBankAsync(paths);
        if (_disposed || generation != _generation || !bankLoaded) return false;
        return updateClickSettings(
          state!.clickSettings.copyWith(timbreFamily: family),
        );
      } catch (e) {
        debugPrint('Falha no timbre: $e');
        return false;
      }
    });
    _pending = operation.then((_) {});
    return operation;
  }

  bool updateClickSettings(ClickSettings settings) {
    final track = state;
    if (track == null || loadingTrackId != null || !settings.isValid) {
      return false;
    }
    if (!ref.read(engineProvider).configureClick(settings)) return false;
    state = track.copyWith(
      clickSettings: settings);
    return true;
  }

  void updateBpm(double bpm) {
    final settings = state?.clickSettings;
    if (settings != null) updateClickSettings(settings.copyWith(bpm: bpm));
  }

  void applyCalibratedBpm(double bpm) {
    final settings = state?.clickSettings;
    if (settings != null) {
      updateClickSettings(settings.copyWith(bpm: bpm, calibrated: true));
  }
  }

  void applyClickOffset(double offsetSeconds) {
    final settings = state?.clickSettings;
    if (settings != null) {
      updateClickSettings(settings.copyWith(beatOffsetSeconds: offsetSeconds));
    }
  }
}

final currentTrackProvider =
    NotifierProvider<CurrentTrackNotifier, Track?>(CurrentTrackNotifier.new);

/// Instância única do serviço de persistência em disco (JSON local).
final persistenceServiceProvider = Provider<PersistenceService>((ref) => PersistenceService());

/// Lista de tracks salvas, carregada do disco via [PersistenceService].
/// Alimenta a tela de biblioteca.
class TrackLibraryNotifier extends Notifier<List<Track>> {
  @override
  List<Track> build() {
    _load();
    return [];
  }

  Future<void> _load() async {
    final tracks = await ref.read(persistenceServiceProvider).loadAllTracks();
    state = tracks;
  }

  Future<void> refresh() => _load();

  /// Salva a track atualmente carregada no engine (via [currentTrackProvider])
  /// em disco -- move os arquivos de áudio pro diretório permanente e grava
  /// o JSON. Atualiza tanto [currentTrackProvider] (com os paths novos)
  /// quanto esta lista, sem precisar reler tudo do disco.
  Future<void> saveCurrent() async {
    final track = ref.read(currentTrackProvider);
    if (track == null) return;

    final saved = await ref.read(persistenceServiceProvider).saveTrack(track);

    if (ref.read(currentTrackProvider)?.id == saved.id) {
      ref.read(currentTrackProvider.notifier).setLoadedTrack(saved);
    }

    final index = state.indexWhere((t) => t.id == saved.id);
    if (index >= 0) {
      final updated = [...state];
      updated[index] = saved;
      state = updated;
    } else {
      state = [...state, saved];
    }
  }

  Future<void> deleteTrack(String id) async {
    final persistence = ref.read(persistenceServiceProvider);
    final current = ref.read(currentTrackProvider.notifier);
    if (ref.read(currentTrackProvider)?.id == id || current.loadingTrackId == id) {
      await current.unload();
    }
    await ref.read(waveformProvider.notifier).forget(id);
    for (final setlist in await persistence.loadAllSetlists()) {
      if (setlist.tracks.any((track) => track.id == id)) {
        await persistence.saveSetlist(setlist.withTrackRemoved(id));
      }
    }
    await persistence.deleteTrack(id);
    await ref.read(setlistLibraryProvider.notifier).refresh();
    final editor = ref.read(setlistEditorProvider);
    if (editor != null) {
      ref.read(setlistEditorProvider.notifier).setLoadedSetlist(editor.withTrackRemoved(id));
    }
    state = state.where((t) => t.id != id).toList();
  }

  /// Renomeia a track [id] direto na biblioteca (não precisa estar
  /// carregada no engine). Se for a track atualmente carregada, atualiza
  /// também o [currentTrackProvider] pra UI de performance refletir na
  /// hora.
  Future<void> renameTrack(String id, String newTitle) async {
    final index = state.indexWhere((t) => t.id == id);
    if (index < 0) return;

    final renamed = state[index].copyWith(title: newTitle);
    final saved = await ref.read(persistenceServiceProvider).saveTrack(renamed);

    final updated = [...state];
    updated[index] = saved;
    state = updated;

    if (ref.read(currentTrackProvider)?.id == id) {
      ref.read(currentTrackProvider.notifier).setLoadedTrack(saved);
    }
  }
}

final trackLibraryProvider =
    NotifierProvider<TrackLibraryNotifier, List<Track>>(TrackLibraryNotifier.new);

/// Estado de transporte (posição/duração/tocando) atualizado por polling a
/// cada 100ms -- mesmo princípio do Timer do app de teste JUCE, só que
/// centralizado aqui em vez de espalhado pela UI.
class TransportState {
  final double positionSeconds;
  final double lengthSeconds;
  final bool isPlaying;
  final bool loopEnabled;
  final double loopStart, loopEnd;
  final bool queuedLoopEnabled;
  final double queuedLoopStart, queuedLoopEnd;
  final int underrunCount;
  const TransportState({this.positionSeconds = 0, this.lengthSeconds = 0, this.isPlaying = false,
    this.loopEnabled = false, this.loopStart = 0, this.loopEnd = 0,
    this.queuedLoopEnabled = false, this.queuedLoopStart = 0, this.queuedLoopEnd = 0, this.underrunCount = 0});
  bool activeSection(SongSection section) => loopEnabled &&
      (loopStart - section.startSeconds).abs() <= 0.001 && (loopEnd - section.endSeconds).abs() <= 0.001;
  bool queuedSection(SongSection section) => queuedLoopEnabled &&
      (queuedLoopStart - section.startSeconds).abs() <= 0.001 && (queuedLoopEnd - section.endSeconds).abs() <= 0.001;
  @override
  bool operator ==(Object other) => other is TransportState &&
      other.positionSeconds == positionSeconds && other.lengthSeconds == lengthSeconds && other.isPlaying == isPlaying &&
      other.loopEnabled == loopEnabled && other.loopStart == loopStart && other.loopEnd == loopEnd &&
      other.queuedLoopEnabled == queuedLoopEnabled && other.queuedLoopStart == queuedLoopStart && other.queuedLoopEnd == queuedLoopEnd && other.underrunCount == underrunCount;
  @override
  int get hashCode => Object.hash(positionSeconds, lengthSeconds, isPlaying, loopEnabled, loopStart, loopEnd,
      queuedLoopEnabled, queuedLoopStart, queuedLoopEnd, underrunCount);
}

class TransportNotifier extends Notifier<TransportState> {
  Timer? _timer;
  static const _bgChannel = MethodChannel('wtracks/background');

  @override
  TransportState build() {
    final engine = ref.watch(engineProvider);
    _timer = Timer.periodic(const Duration(milliseconds: 100), (_) {
      final next = _snapshot(engine);
      // Parado, nada muda entre ticks -- evita rebuild 10x/s à toa.
      if (_backgroundActive && !next.isPlaying) {
        _backgroundActive = false;
        unawaited(_background('stop'));
      }
      if (next != state) state = next;
    });
    ref.onDispose(() {
      _timer?.cancel();
      ++_playGeneration;
    });
    return const TransportState();
  }

  TransportState _snapshot(WTracksEngine engine) {
    final loop = engine.loopState;
    return TransportState(positionSeconds: engine.currentPositionSeconds,
      lengthSeconds: engine.totalLengthSeconds, isPlaying: engine.isPlaying,
      loopEnabled: loop[0] == 1, loopStart: loop[1], loopEnd: loop[2],
      queuedLoopEnabled: loop[3] == 1, queuedLoopStart: loop[4], queuedLoopEnd: loop[5],
      underrunCount: engine.underrunCount);
  }
  void refresh() { final next = _snapshot(ref.read(engineProvider)); if (next != state) state = next; }
  bool disableLoop() { final ok = ref.read(engineProvider).setLoop(0, 0, false); if (ok) refresh(); return ok; }
  void clearQueuedLoop() { ref.read(engineProvider).clearQueuedLoop(); refresh(); }

  bool _backgroundActive = false;
  int _playGeneration = 0;
  Future<void> _backgroundQueue = Future.value();

  Future<void> _background(String method, [Map<String, Object>? arguments]) {
    final operation = _backgroundQueue.then((_) async {
      try {
        await _bgChannel.invokeMethod<void>(method, arguments);
      } on MissingPluginException catch (e) {
        debugPrint('Background indisponível: $e');
      } on PlatformException catch (e) {
        debugPrint('Falha no background: $e');
      }
    });
    _backgroundQueue = operation;
    return operation;
  }

  Future<void> play() async {
    final generation = ++_playGeneration;
    final engine = ref.read(engineProvider);
    final title = ref.read(currentTrackProvider)?.title ?? 'WTracks';
    await _background('requestNotificationPermission');
    if (generation != _playGeneration) return;
    engine.play();
    if (!engine.isPlaying) return;
    _backgroundActive = true;
    await _background('start', {'title': title});
  }

  Future<void> pause() async {
    ++_playGeneration;
    ref.read(engineProvider).pause();
    _backgroundActive = false;
    await _background('stop');
  }

  Future<void> stop() async {
    ++_playGeneration;
    ref.read(currentTrackProvider.notifier).cancelLoopPreparation();
    ref.read(engineProvider).stop();
    refresh();
    _backgroundActive = false;
    await _background('stop');
  }

  void seekTo(double seconds) => ref.read(engineProvider).seekToSeconds(seconds);
}

final transportProvider =
    NotifierProvider<TransportNotifier, TransportState>(TransportNotifier.new);