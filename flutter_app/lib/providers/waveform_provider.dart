import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/track.dart';
import 'engine_provider.dart';

/// Estado da waveform da track atualmente aberta na performance_screen.
class WaveformState {
  final List<double>? peaks; // null = ainda não disponível
  final bool isGenerating;

  const WaveformState({this.peaks, this.isGenerating = false});
}

/// Gera/cacheia os picos de waveform (mixagem de todos os canais) usados
/// pela timeline visual da performance_screen. Não é um `family` -- segue o
/// mesmo estilo de Notifier comum já usado no projeto (ex:
/// [CurrentTrackNotifier]), com um método [loadFor] chamado explicitamente
/// quando a tela abre uma track.
class WaveformNotifier extends Notifier<WaveformState> {
  String? _loadedForTrackId;

  @override
  WaveformState build() => const WaveformState();

  /// Carrega a waveform de [track]: tenta o cache em disco primeiro: se
  /// achar, usa direto; senão gera via engine nativo (assíncrono) e salva
  /// o resultado no cache pra próxima abertura ser instantânea.
  Future<void> loadFor(Track track) async {
    // Evita mostrar a waveform da música anterior por um frame ao trocar
    // de track -- mas só reseta o estado se for troca de verdade.
    if (_loadedForTrackId != track.id) {
      state = const WaveformState(isGenerating: false, peaks: null);
    }
    _loadedForTrackId = track.id;

    final persistence = ref.read(persistenceServiceProvider);
    final cached = await persistence.loadWaveformPeaks(track.id);
    if (_loadedForTrackId != track.id) return; // trocou de track enquanto lia o cache

    if (cached != null) {
      state = WaveformState(peaks: cached, isGenerating: false);
      return;
    }

    state = const WaveformState(peaks: null, isGenerating: true);

    final engine = ref.read(engineProvider);
    final generated = await engine.generateWaveformPeaksAsync(track.channelFilePaths);
    if (_loadedForTrackId != track.id) return; // trocou de track enquanto gerava

    if (generated == null) {
      state = const WaveformState(peaks: null, isGenerating: false);
      return;
    }

    state = WaveformState(peaks: generated, isGenerating: false);
    // Cache é barato de recalcular se a track nunca for salva de verdade --
    // não depende do fluxo de "Salvar" da track.
    await persistence.saveWaveformPeaks(track.id, generated);
  }
}

final waveformProvider =
    NotifierProvider<WaveformNotifier, WaveformState>(WaveformNotifier.new);
