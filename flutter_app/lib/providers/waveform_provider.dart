import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter/foundation.dart';

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
  int _generation = 0;
  Future<void> _pending = Future.value();
  bool _disposed = false;

  @override
  WaveformState build() {
    ref.onDispose(() { _disposed = true; ++_generation; });
    return const WaveformState();
  }

  Future<void> forget(String id) async {
    if (_loadedForTrackId == id) {
      ++_generation;
      _loadedForTrackId = null;
      state = const WaveformState();
    }
    await _pending; // Finish any cache write before deletion removes it.
  }

  Future<void> loadFor(Track track) {
    final generation = ++_generation;
    _loadedForTrackId = track.id;
    final persistence = ref.read(persistenceServiceProvider);
    final engine = ref.read(engineProvider);
    state = const WaveformState(isGenerating: true);
    bool current() => !_disposed && generation == _generation;
    final operation = () async {
      try {
        final cached = await persistence.loadWaveformPeaks(track.id);
        if (!current()) return;
        if (cached != null) {
          state = WaveformState(peaks: cached);
          return;
        }
        final generated = await engine.generateWaveformPeaksAsync(track.channelFilePaths);
        if (!current()) return;
        state = WaveformState(peaks: generated);
        if (generated != null) await persistence.saveWaveformPeaks(track.id, generated);
      } catch (e) {
        debugPrint('Falha na waveform: $e');
        if (current()) state = const WaveformState();
      }
    }();
    _pending = Future.wait([_pending, operation]).then((_) {});
    return operation;
  }
}

final waveformProvider =
    NotifierProvider<WaveformNotifier, WaveformState>(WaveformNotifier.new);
