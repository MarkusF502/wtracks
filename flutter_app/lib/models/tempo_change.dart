import 'package:flutter/foundation.dart';

/// Mudança de andamento e/ou compasso a partir de [startSeconds] (tempo da música).
/// O segmento base é o do click (ClickSettings); cada mudança reinicia a contagem
/// de compassos, com acento no seu primeiro tempo. Mapeia SongTempo{storedBPM,
/// storedTimecode} e MetadataTimeSignature{beatsPerBar, beatUnit} do Playback.
@immutable
class TempoChange {
  final String id;
  final double startSeconds;
  final double bpm;
  final int numerator, denominator;
  const TempoChange({required this.id, required this.startSeconds, required this.bpm, this.numerator = 4, this.denominator = 4});

  static bool _unit(int n) => n >= 1 && n <= 64 && (n & (n - 1)) == 0;
  bool get isValid =>
      id.isNotEmpty &&
      startSeconds.isFinite &&
      startSeconds > 0 &&
      startSeconds <= 86400 &&
      bpm.isFinite &&
      bpm >= 1 &&
      bpm <= 1000 &&
      numerator >= 1 &&
      numerator <= 64 &&
      _unit(denominator);

  TempoChange copyWith({double? startSeconds, double? bpm, int? numerator, int? denominator}) => TempoChange(
        id: id,
        startSeconds: startSeconds ?? this.startSeconds,
        bpm: bpm ?? this.bpm,
        numerator: numerator ?? this.numerator,
        denominator: denominator ?? this.denominator,
      );

  Map<String, dynamic> toJson() => {'id': id, 'startSeconds': startSeconds, 'bpm': bpm, 'numerator': numerator, 'denominator': denominator};

  factory TempoChange.fromJson(Map<String, dynamic> json) {
    final change = TempoChange(
      id: json['id'] as String,
      startSeconds: (json['startSeconds'] as num).toDouble(),
      bpm: (json['bpm'] as num).toDouble(),
      numerator: (json['numerator'] as num?)?.toInt() ?? 4,
      denominator: (json['denominator'] as num?)?.toInt() ?? 4,
    );
    if (!change.isValid) throw const FormatException('Mudança de andamento inválida');
    return change;
  }

  /// Estritamente crescente, ids únicos, no máximo 512 e (se informado) depois de [baseOffset].
  static bool validSequence(List<TempoChange> changes, {double baseOffset = 0}) {
    if (changes.length > 512) return false;
    var previous = baseOffset;
    final ids = <String>{};
    for (final change in changes) {
      if (!change.isValid || change.startSeconds <= previous || !ids.add(change.id)) return false;
      previous = change.startSeconds;
    }
    return true;
  }

  static List<TempoChange> fromJsonList(List<dynamic> list) {
    final changes = list.map((v) => TempoChange.fromJson(v as Map<String, dynamic>)).toList();
    if (!validSequence(changes)) throw const FormatException('Mapa de andamento inválido');
    return List.unmodifiable(changes);
  }

  @override
  bool operator ==(Object other) =>
      other is TempoChange && other.id == id && other.startSeconds == startSeconds && other.bpm == bpm && other.numerator == numerator && other.denominator == denominator;
  @override
  int get hashCode => Object.hash(id, startSeconds, bpm, numerator, denominator);
}
