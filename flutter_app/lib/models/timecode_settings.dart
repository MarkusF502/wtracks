import 'package:flutter/foundation.dart';

/// Taxas de quadro na ordem da tabela do TimecodeAUFramework do Playback
/// (rótulos inferidos da tabela e da máscara de drop-frame 0x324).
class TimecodeRate {
  final String label;
  final int nominal; // quadros por segundo contados no código
  final bool drop;
  const TimecodeRate(this.label, this.nominal, this.drop);

  /// Quadros de drop-frame removidos por minuto (exceto de dez em dez).
  int get dropPerMinute => !drop ? 0 : (nominal >= 50 ? 4 : 2);

  static const all = [
    TimecodeRate('24', 24, false),
    TimecodeRate('25', 25, false),
    TimecodeRate('30 (drop)', 30, true),
    TimecodeRate('30', 30, false),
    TimecodeRate('29,97', 30, false),
    TimecodeRate('29,97 drop', 30, true),
    TimecodeRate('60', 60, false),
    TimecodeRate('59,94', 60, false),
    TimecodeRate('60 (drop)', 60, true),
    TimecodeRate('59,94 drop', 60, true),
    TimecodeRate('50', 50, false),
  ];
}

/// Timecode linear (LTC) escrito em uma saída. Roda em tempo real na linha do
/// tempo processada, sem passar por mute, solo ou volume geral.
@immutable
class TimecodeSettings {
  final bool enabled;
  final int rateIndex;
  final int startFrame; // quadros desde 00:00:00:00
  final double onsetSeconds; // instante da música em que o primeiro quadro começa
  final int outputChannel; // 0 = esquerda, 1 = direita
  final double gain;

  const TimecodeSettings({
    this.enabled = false,
    this.rateIndex = 3,
    this.startFrame = 0,
    this.onsetSeconds = 0,
    this.outputChannel = 1,
    this.gain = 0.5,
  });

  TimecodeRate get rate => TimecodeRate.all[rateIndex.clamp(0, TimecodeRate.all.length - 1)];
  static int framesPerDay(int rateIndex) {
    final rate = TimecodeRate.all[rateIndex];
    return rate.drop ? (rate.nominal * 600 - 9 * rate.dropPerMinute) * 144 : rate.nominal * 86400;
  }

  bool get isValid =>
      rateIndex >= 0 &&
      rateIndex < TimecodeRate.all.length &&
      startFrame >= 0 &&
      startFrame < framesPerDay(rateIndex) &&
      onsetSeconds.isFinite &&
      onsetSeconds >= 0 &&
      onsetSeconds <= 86400 &&
      (outputChannel == 0 || outputChannel == 1) &&
      gain.isFinite &&
      gain >= 0 &&
      gain <= 1;

  /// "hh:mm:ss:ff" para a contagem de quadros (com a numeração de drop-frame).
  static String format(int rateIndex, int frames) {
    final rate = TimecodeRate.all[rateIndex];
    var n = frames % framesPerDay(rateIndex);
    if (rate.drop) {
      final d = rate.dropPerMinute, per10 = rate.nominal * 600 - 9 * d, perMinute = rate.nominal * 60 - d;
      final tens = n ~/ per10, rest = n % per10;
      n += 9 * d * tens + (rest > d ? d * ((rest - d) ~/ perMinute) : 0);
    }
    final f = n % rate.nominal;
    n ~/= rate.nominal;
    final s = n % 60;
    n ~/= 60;
    final m = n % 60, h = (n ~/ 60) % 24;
    String two(int v) => v.toString().padLeft(2, '0');
    return '${two(h)}:${two(m)}:${two(s)}${rate.drop ? ';' : ':'}${two(f)}';
  }

  /// Converte "hh:mm:ss:ff" (ou ';' antes dos quadros) em contagem de quadros; null se ilegal.
  static int? parse(int rateIndex, String text) {
    final match = RegExp(r'^(\d{1,2}):(\d{1,2}):(\d{1,2})[:;.](\d{1,2})$').firstMatch(text.trim());
    if (match == null) return null;
    final h = int.parse(match[1]!), m = int.parse(match[2]!), s = int.parse(match[3]!), f = int.parse(match[4]!);
    final rate = TimecodeRate.all[rateIndex];
    if (h > 23 || m > 59 || s > 59 || f >= rate.nominal) return null;
    if (rate.drop && s == 0 && f < rate.dropPerMinute && m % 10 != 0) return null; // numeração pulada
    final totalMinutes = 60 * h + m;
    final nominalFrames = ((totalMinutes * 60) + s) * rate.nominal + f;
    return rate.drop ? nominalFrames - rate.dropPerMinute * (totalMinutes - totalMinutes ~/ 10) : nominalFrames;
  }

  TimecodeSettings copyWith({bool? enabled, int? rateIndex, int? startFrame, double? onsetSeconds, int? outputChannel, double? gain}) =>
      TimecodeSettings(
        enabled: enabled ?? this.enabled,
        rateIndex: rateIndex ?? this.rateIndex,
        startFrame: startFrame ?? this.startFrame,
        onsetSeconds: onsetSeconds ?? this.onsetSeconds,
        outputChannel: outputChannel ?? this.outputChannel,
        gain: gain ?? this.gain,
      );

  Map<String, dynamic> toJson() => {
        'enabled': enabled,
        'rateIndex': rateIndex,
        'startFrame': startFrame,
        'onsetSeconds': onsetSeconds,
        'outputChannel': outputChannel,
        'gain': gain,
      };

  /// Dados ausentes ou inválidos desligam o timecode (nunca emitem um sinal incorreto).
  factory TimecodeSettings.fromJson(Object? json) {
    if (json is! Map) return const TimecodeSettings();
    final parsed = TimecodeSettings(
      enabled: json['enabled'] as bool? ?? false,
      rateIndex: (json['rateIndex'] as num?)?.toInt() ?? 3,
      startFrame: (json['startFrame'] as num?)?.toInt() ?? 0,
      onsetSeconds: (json['onsetSeconds'] as num?)?.toDouble() ?? 0,
      outputChannel: (json['outputChannel'] as num?)?.toInt() ?? 1,
      gain: (json['gain'] as num?)?.toDouble() ?? 0.5,
    );
    return parsed.isValid ? parsed : const TimecodeSettings();
  }

  @override
  bool operator ==(Object other) =>
      other is TimecodeSettings &&
      other.enabled == enabled &&
      other.rateIndex == rateIndex &&
      other.startFrame == startFrame &&
      other.onsetSeconds == onsetSeconds &&
      other.outputChannel == outputChannel &&
      other.gain == gain;
  @override
  int get hashCode => Object.hash(enabled, rateIndex, startFrame, onsetSeconds, outputChannel, gain);
}
