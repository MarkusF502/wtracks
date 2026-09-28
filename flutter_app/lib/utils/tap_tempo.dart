/// Calculadora de tap tempo -- pura, sem dependência de Flutter/Riverpod
/// (facilita teste de unidade). O usuário registra toques no ritmo da
/// música e a classe estima o BPM a partir dos intervalos entre eles.
class TapTempoCalculator {
  final List<DateTime> _taps = [];

  /// Descarta os toques acumulados se o intervalo desde o último toque
  /// for maior que isso -- evita calcular BPM absurdo a partir de dois
  /// toques sem relação (ex: usuário parou, pensou, tocou de novo).
  static const _resetGap = Duration(seconds: 2);

  /// Mantém só os últimos N toques -- suficiente pra estabilizar a média
  /// sem deixar toques muito antigos (de um tempo diferente) influenciar
  /// pra sempre.
  static const _maxTaps = 8;

  /// Mesmo range aceito pelo slider manual (ver `_showBpmDialog`).
  static const _minBpm = 40.0;
  static const _maxBpm = 240.0;

  /// Registra um toque em [now] (injetável para teste -- default
  /// DateTime.now()). Retorna o BPM calculado, ou null se ainda não há
  /// toques suficientes (mínimo 2) para estimar um intervalo.
  double? registerTap([DateTime? now]) {
    final tapTime = now ?? DateTime.now();

    if (_taps.isNotEmpty && tapTime.difference(_taps.last) > _resetGap) {
      _taps.clear();
    }

    _taps.add(tapTime);
    if (_taps.length > _maxTaps) {
      _taps.removeAt(0);
    }

    if (_taps.length < 2) return null;

    final intervals = <Duration>[];
    for (var i = 1; i < _taps.length; i++) {
      intervals.add(_taps[i].difference(_taps[i - 1]));
    }

    final avgMs =
        intervals.map((d) => d.inMicroseconds).reduce((a, b) => a + b) /
            intervals.length /
            1000;

    final bpm = 60000 / avgMs;
    return bpm.clamp(_minBpm, _maxBpm);
  }

  /// Quantos toques válidos (na janela atual, sem reset) já foram
  /// registrados -- útil pra UI mostrar "continue tocando..." vs BPM.
  int get tapCount => _taps.length;

  void reset() => _taps.clear();
}
