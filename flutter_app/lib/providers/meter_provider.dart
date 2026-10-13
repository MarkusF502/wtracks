import 'dart:async';
import 'dart:math' as math;

import 'package:flutter/foundation.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import 'engine_provider.dart';

/// Níveis exibidos pelos medidores (0..1 na escala de -60 dB a 0 dB).
@immutable
class MeterLevels {
  final List<double> channels;
  final List<double> outputs;
  const MeterLevels(this.channels, this.outputs);
  static const silent = MeterLevels([], []);
  @override
  bool operator ==(Object other) => other is MeterLevels && listEquals(other.channels, channels) && listEquals(other.outputs, outputs);
  @override
  int get hashCode => Object.hash(Object.hashAll(channels), Object.hashAll(outputs));
}

/// Converte um pico linear para a escala do medidor: -60 dB..0 dB -> 0..1 (acima de 0 dB fica em 1).
double meterFraction(double peak) {
  if (!(peak > 0)) return 0;
  final db = 20 * math.log(peak) / math.ln10;
  return ((db + meterFloorDb.abs()) / meterFloorDb.abs()).clamp(0.0, 1.0);
}

const meterFloorDb = -60.0;

/// Queda dos medidores em dB/s (escolha própria; a balística do MixerVUMeterView não foi recuperada).
const meterFallDbPerSecond = 24.0;

/// Lê os picos do motor (que acumula entre leituras, sem alocar no callback) só enquanto alguém observa;
/// sobe na hora e cai [meterFallDbPerSecond]. Leitura para a interface, não agenda áudio.
class MeterNotifier extends AutoDisposeNotifier<MeterLevels> {
  static const interval = Duration(milliseconds: 50);
  Timer? _timer;

  @override
  MeterLevels build() {
    final engine = ref.watch(engineProvider);
    _timer = Timer.periodic(interval, (_) {
      final (channels, outputs) = engine.takeMeters();
      final fall = meterFallDbPerSecond * interval.inMilliseconds / 1000 / meterFloorDb.abs();
      List<double> decay(List<double> peaks, List<double> previous) => [
            for (var i = 0; i < peaks.length; i++)
              math.max(meterFraction(peaks[i]), (i < previous.length ? previous[i] : 0) - fall).clamp(0.0, 1.0),
          ];
      final next = MeterLevels(decay(channels, state.channels), decay(outputs, state.outputs));
      if (next != state) state = next;
    });
    ref.onDispose(() => _timer?.cancel());
    return MeterLevels.silent;
  }
}

final meterProvider = NotifierProvider.autoDispose<MeterNotifier, MeterLevels>(MeterNotifier.new);
