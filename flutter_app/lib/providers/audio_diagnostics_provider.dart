import 'dart:async';

import 'package:flutter/foundation.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../native/wtracks_bindings.dart';
import 'engine_provider.dart';

/// Leitura da saúde do áudio em tempo real: configuração real do dispositivo, carga do callback e falhas desde o início da
/// medição atual. Os contadores nativos são históricos; a medição guarda uma base e mostra só os deltas.
enum AudioHealth { idle, stable, deviceXruns, underruns, overruns }

/// Base da medição atual. Sobrevive ao fechamento da tela para que se possa medir com Tracks/Waveform visíveis e voltar.
@immutable
class AudioMeasurementBase {
  final DateTime startedAt;
  final int underruns;
  final int deviceXruns;  // -1 = o dispositivo não informa
  const AudioMeasurementBase(this.startedAt, this.underruns, this.deviceXruns);
}

@immutable
class AudioDiagnostics {
  final AudioConfigSnapshot config;
  final RenderStatsSnapshot stats;
  final AudioMeasurementBase? base;
  final int underruns;    // desde [base]
  final int deviceXruns;  // desde [base]; -1 = não informado
  final Duration elapsed;
  const AudioDiagnostics({this.config = const AudioConfigSnapshot(), this.stats = const RenderStatsSnapshot(), this.base,
      this.underruns = 0, this.deviceXruns = -1, this.elapsed = Duration.zero});

  /// A pior falha vence: callback acima do prazo, depois falta de dados do read-ahead, depois xrun só do dispositivo.
  AudioHealth get health {
    if (base == null || stats.callbacks == 0) return AudioHealth.idle;
    if (stats.overruns > 0) return AudioHealth.overruns;
    if (underruns > 0) return AudioHealth.underruns;
    if (deviceXruns > 0) return AudioHealth.deviceXruns;
    return AudioHealth.stable;
  }

  static AudioDiagnostics read(WTracksEngine engine, AudioMeasurementBase? base, DateTime now) {
    final config = engine.audioConfig;
    final underruns = engine.underrunCount;
    return AudioDiagnostics(
      config: config,
      stats: engine.renderStats,
      base: base,
      underruns: base == null ? 0 : underruns - base.underruns,
      deviceXruns: base == null || base.deviceXruns < 0 || config.deviceXruns < 0 ? -1 : config.deviceXruns - base.deviceXruns,
      elapsed: base == null ? Duration.zero : now.difference(base.startedAt),
    );
  }

  /// Texto para copiar: só números da configuração e da medição -- sem caminhos, nomes de música, conta ou sessão.
  String export() {
    String pct(double v) => '${(v * 100).toStringAsFixed(1)}%';
    final c = config, s = stats;
    final lines = <String>[
      'WTracks — Áudio em tempo real',
      'Estado: ${healthLabel(health)}',
      'Duração da medição: ${_duration(elapsed)}',
      'Pedido: ${c.requestedRate} Hz / ${c.requestedBuffer} frames',
      'Dispositivo: ${c.deviceRate} Hz / buffer ${c.deviceBuffer} frames / latência de saída ${c.outputLatencyFrames} frames',
      'Preparado: ${c.preparedRate} Hz / bloco ${c.preparedBlock} frames / prazo ${c.deadlineMs.toStringAsFixed(2)} ms',
      'Canais carregados: ${c.channels}; arquivos ${c.fileRate.round()} Hz; razão de resampling ${c.resampleRatio.toStringAsFixed(5)}',
      'Underruns do read-ahead: $underruns',
      'Xruns do dispositivo: ${deviceXruns < 0 ? 'não informado' : deviceXruns}',
      'Callbacks: ${s.callbacks}; prazo por callback ${s.deadlineMs.toStringAsFixed(2)} ms; acima do prazo: ${s.overruns}',
      'Carga P50/P95/P99: ${pct(s.p50Load)} / ${pct(s.p95Load)} / ${pct(s.p99Load)}; máximo ${s.maxMs.toStringAsFixed(2)} ms (${pct(s.maxLoad)})',
    ];
    return lines.join('\n');
  }

  static String healthLabel(AudioHealth health) => switch (health) {
        AudioHealth.idle => 'sem medição',
        AudioHealth.stable => 'estável',
        AudioHealth.deviceXruns => 'falhas no dispositivo (xrun) com callback dentro do prazo',
        AudioHealth.underruns => 'underruns detectados (read-ahead)',
        AudioHealth.overruns => 'callback acima do prazo',
      };

  static String _duration(Duration d) =>
      '${d.inMinutes}:${(d.inSeconds % 60).toString().padLeft(2, '0')}';
}

final audioMeasurementBaseProvider = StateProvider<AudioMeasurementBase?>((ref) => null);

/// Atualiza a cada [interval] só enquanto alguém observa (a tela Diagnóstico); nada roda com a tela fechada.
class AudioDiagnosticsNotifier extends AutoDisposeNotifier<AudioDiagnostics> {
  static const interval = Duration(milliseconds: 500);
  Timer? _timer;

  @override
  AudioDiagnostics build() {
    final engine = ref.watch(engineProvider);
    final base = ref.watch(audioMeasurementBaseProvider);
    _timer?.cancel();
    _timer = Timer.periodic(interval, (_) => state = AudioDiagnostics.read(engine, base, DateTime.now()));
    ref.onDispose(() => _timer?.cancel());
    return AudioDiagnostics.read(engine, base, DateTime.now());
  }

  /// Zera a carga do callback e marca a base dos contadores históricos (underruns e xruns não são zerados no motor).
  void startMeasurement() {
    final engine = ref.read(engineProvider);
    engine.resetRenderStats();
    ref.read(audioMeasurementBaseProvider.notifier).state =
        AudioMeasurementBase(DateTime.now(), engine.underrunCount, engine.audioConfig.deviceXruns);
  }

  /// Troca o buffer do dispositivo (só parado) e começa uma nova medição, já que a anterior media outro buffer.
  bool setBufferSize(int frames) {
    final engine = ref.read(engineProvider);
    if (engine.isPlaying || !engine.setBufferSize(frames)) return false;
    startMeasurement();
    return true;
  }
}

final audioDiagnosticsProvider =
    NotifierProvider.autoDispose<AudioDiagnosticsNotifier, AudioDiagnostics>(AudioDiagnosticsNotifier.new);
