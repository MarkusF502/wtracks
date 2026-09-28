import 'dart:async';
import 'dart:isolate';

import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/track.dart';
import '../native/wtracks_bindings.dart';
import '../services/persistence_service.dart';

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
    // ignore: avoid_print
    print('WTracksEngine.initialise() falhou.');
  }

  return engine;
});

/// A música atualmente carregada no engine (ou null se nenhuma).
/// Widgets de mixer/canal leem daqui em vez de perguntar pro engine
/// canal por canal.
class CurrentTrackNotifier extends Notifier<Track?> {
  @override
  Track? build() => null;

  /// Carrega [track] no engine nativo. Retorna false se o engine recusar
  /// (ex: canais com sample rate/duração incompatíveis) -- nesse caso
  /// [state] não muda, e o chamador pode consultar wtracks_get_last_error()
  /// através do engineProvider para mostrar o motivo ao usuário.
  Future<bool> load(Track track) async {
    final engine = ref.read(engineProvider);
    engine.stop();

    debugPrint('>>> [DEBUG] 1. Iniciando load() no Provider para a track: ${track.id}');
    debugPrint('>>> [DEBUG] Caminhos dos arquivos: ${track.channelFilePaths}');

    try {
      debugPrint('>>> [DEBUG] 2. Entrando no Isolate.run()...');

      final loaded = await Isolate.run(() {
        debugPrint('>>> [ISOLATE] 3. Isolate rodando em background. Abrindo engine secundária...');
        final backgroundEngine = WTracksEngine();
        debugPrint('>>> [ISOLATE] 4. Chamando backgroundEngine.loadTrack()...');
        final success = backgroundEngine.loadTrack(track.id, track.channelFilePaths);
        debugPrint('>>> [ISOLATE] 5. loadTrack() terminou com sucesso = $success');
        return success;
      });

      debugPrint('>>> [DEBUG] 6. Isolate.run() finalizou com loaded = $loaded');

      if (!loaded) {
        debugPrint('>>> [DEBUG] ERRO: O engine recusou o carregamento.');
        return false;
      }

      debugPrint('>>> [DEBUG] 7. Configurando BPM e tempo...');
      engine.setClickBpm(track.clickSettings.bpm);
      engine.setClickTimeSignature(track.clickSettings.timeSignatureNumerator, 4);
      engine.setClickOffsetSeconds(track.clickSettings.beatOffsetSeconds);

      debugPrint('>>> [DEBUG] 8. Atualizando state com a nova track...');
      state = track;

      debugPrint('>>> [DEBUG] 9. Tudo concluído com sucesso! Retornando true.');
      return true;
    } catch (e, stack) {
      debugPrint('>>> [DEBUG] CRITICAL EXCEPTION capturada no catch: $e\n$stack');
      return false;
    }
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

  void updateBpm(double bpm) {
    final track = state;
    if (track == null) return;

    // Atualiza o motor C++ em tempo real
    ref.read(engineProvider).setClickBpm(bpm);

    // Atualiza o estado da interface (Riverpod)
    state = track.copyWith(
      clickSettings: track.clickSettings.copyWith(bpm: bpm),
    );
  }

  /// Aplica [bpm] vindo de uma calibração real (tap tempo), marcando
  /// clickSettings.calibrated = true -- diferente de updateBpm, que é
  /// usado pelo slider manual e não implica que o valor foi calibrado de
  /// verdade. Nota: se o usuário depois ajustar o BPM manualmente via
  /// updateBpm, `calibrated` permanece true (não "descalibra"
  /// automaticamente) -- é aceitável, não precisa mudar updateBpm pra
  /// isso.
  void applyCalibratedBpm(double bpm) {
    final track = state;
    if (track == null) return;

    ref.read(engineProvider).setClickBpm(bpm);
    state = track.copyWith(
      clickSettings: track.clickSettings.copyWith(bpm: bpm, calibrated: true),
    );
  }

  /// Marca o offset de fase do click a partir da posição de playback atual
  /// -- usado pelo botão "marcar 1º tempo" durante a reprodução (ver
  /// PerformanceScreen). Diferente de applyCalibratedBpm, aqui não existe
  /// um "calibrated" separado por offset -- clickSettings.calibrated
  /// continua representando só a calibração de BPM.
  void applyClickOffset(double offsetSeconds) {
    final track = state;
    if (track == null) return;

    ref.read(engineProvider).setClickOffsetSeconds(offsetSeconds);
    state = track.copyWith(
      clickSettings: track.clickSettings.copyWith(beatOffsetSeconds: offsetSeconds),
    );
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

    ref.read(currentTrackProvider.notifier).setLoadedTrack(saved);

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
    await ref.read(persistenceServiceProvider).deleteTrack(id);
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

  const TransportState({
    this.positionSeconds = 0,
    this.lengthSeconds = 0,
    this.isPlaying = false,
  });
}

class TransportNotifier extends Notifier<TransportState> {
  Timer? _timer;
  static const _bgChannel = MethodChannel('wtracks/background');

  @override
  TransportState build() {
    final engine = ref.watch(engineProvider);
    _timer = Timer.periodic(const Duration(milliseconds: 100), (_) {
      state = TransportState(
        positionSeconds: engine.currentPositionSeconds,
        lengthSeconds: engine.totalLengthSeconds,
        isPlaying: engine.isPlaying,
      );
    });
    ref.onDispose(() => _timer?.cancel());
    return const TransportState();
  }

  void play() {
    ref.read(engineProvider).play();
    final trackTitle = ref.read(currentTrackProvider)?.title ?? 'WTracks';
    _bgChannel.invokeMethod('start', {'title': trackTitle});
  }

  void pause() {
    ref.read(engineProvider).pause();
  }

  void stop() {
    ref.read(engineProvider).stop();
    _bgChannel.invokeMethod('stop');
  }

  void seekTo(double seconds) => ref.read(engineProvider).seekToSeconds(seconds);
}

final transportProvider =
    NotifierProvider<TransportNotifier, TransportState>(TransportNotifier.new);