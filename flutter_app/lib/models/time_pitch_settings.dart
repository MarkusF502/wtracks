import 'dart:math' as math;
import 'package:flutter/foundation.dart';

/// Tom (semitons) e andamento (razão da velocidade) aplicados às faixas por
/// renderização offline, como no Playback (TimePitchProcessingManager).
/// O algoritmo é próprio, não o Élastique do app original.
@immutable
class TimePitchSettings {
  static const minSemitones = -12;
  static const maxSemitones = 12;
  static const minTempo = 0.5;
  static const maxTempo = 2.0;

  final int semitones;
  final double tempoRatio; // 1.0 = velocidade original; 0.9 = 90% da velocidade
  final bool complex; // janela maior: melhor afinação, transientes mais suaves

  const TimePitchSettings({this.semitones = 0, this.tempoRatio = 1.0, this.complex = true});

  bool get isValid =>
      semitones >= minSemitones &&
      semitones <= maxSemitones &&
      tempoRatio.isFinite &&
      tempoRatio >= minTempo &&
      tempoRatio <= maxTempo;
  bool get isIdentity => semitones == 0 && tempoRatio == 1.0;

  /// Comprimento de saída / comprimento de entrada (o inverso da velocidade).
  double get timeFactor => 1 / tempoRatio;
  double get pitchFactor => math.pow(2, semitones / 12).toDouble();

  TimePitchSettings copyWith({int? semitones, double? tempoRatio, bool? complex}) => TimePitchSettings(
        semitones: semitones ?? this.semitones,
        tempoRatio: tempoRatio ?? this.tempoRatio,
        complex: complex ?? this.complex,
      );

  Map<String, dynamic> toJson() => {'semitones': semitones, 'tempoRatio': tempoRatio, 'complex': complex};

  /// Valores ausentes ou inválidos voltam ao original: o áudio de origem sempre existe.
  factory TimePitchSettings.fromJson(Object? json) {
    if (json is! Map) return const TimePitchSettings();
    final parsed = TimePitchSettings(
      semitones: (json['semitones'] as num?)?.toInt() ?? 0,
      tempoRatio: (json['tempoRatio'] as num?)?.toDouble() ?? 1.0,
      complex: json['complex'] as bool? ?? true,
    );
    return parsed.isValid ? parsed : const TimePitchSettings();
  }

  @override
  bool operator ==(Object other) =>
      other is TimePitchSettings && other.semitones == semitones && other.tempoRatio == tempoRatio && other.complex == complex;
  @override
  int get hashCode => Object.hash(semitones, tempoRatio, complex);
}
