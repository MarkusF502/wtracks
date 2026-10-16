import 'package:flutter/foundation.dart';

/// Instantes explícitos do click de uma música, em segundos da música (MultiTracks: `clicks.accents/quarters/eighths/sixteenths`;
/// Playback guarda o mesmo em `SongClicks` e passa `clickTimes` ao kernel do click). Enquanto existem, o motor toca o click por eles
/// em vez da grade de andamento, o que mantém exatas as mudanças de andamento que caem no meio de um tempo. Editar a grade
/// (andamento, compasso, deslocamento) descarta estes instantes.
@immutable
class FixedClicks {
  static const maxEvents = 1 << 17;

  /// Dois instantes a menos que isto são o mesmo tempo (a MultiTracks põe o acento 0,1 ms depois do quarto do mesmo tempo).
  static const sameBeatSeconds = 0.002;

  final List<double> accents, quarters, eighths, sixteenths;
  const FixedClicks({this.accents = const [], this.quarters = const [], this.eighths = const [], this.sixteenths = const []});

  bool get isEmpty => accents.isEmpty && quarters.isEmpty && eighths.isEmpty && sixteenths.isEmpty;

  static bool _validList(List<double> values) {
    for (var i = 0; i < values.length; i++) {
      final v = values[i];
      if (!v.isFinite || v < 0 || v > 86400 || (i > 0 && v < values[i - 1])) return false;
    }
    return true;
  }

  bool get isValid =>
      accents.length + quarters.length + eighths.length + sixteenths.length <= maxEvents &&
      _validList(accents) &&
      _validList(quarters) &&
      _validList(eighths) &&
      _validList(sixteenths);

  /// Eventos (instante, voz) em ordem, como o motor toca: voz 0 acento, 1 quarto, 2 colcheia, 3 semicolcheia. O WTracks toca uma
  /// voz por tempo, então o quarto que coincide com um acento sai.
  List<(double, int)> events() {
    final result = <(double, int)>[
      for (final t in accents) (t, 0),
      for (final t in quarters)
        if (!_near(accents, t)) (t, 1),
      for (final t in eighths) (t, 2),
      for (final t in sixteenths) (t, 3),
    ]..sort((a, b) => a.$1 != b.$1 ? a.$1.compareTo(b.$1) : a.$2.compareTo(b.$2));
    return result;
  }

  static bool _near(List<double> sorted, double t) {
    var lo = 0, hi = sorted.length;
    while (lo < hi) {
      final mid = (lo + hi) >> 1;
      if (sorted[mid] < t - sameBeatSeconds) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }
    return lo < sorted.length && (sorted[lo] - t).abs() <= sameBeatSeconds;
  }

  Map<String, dynamic> toJson() => {'accents': accents, 'quarters': quarters, 'eighths': eighths, 'sixteenths': sixteenths};

  /// `null` quando ausente ou vazio; lança [FormatException] se os dados não fazem sentido (a música não abre com um click errado).
  static FixedClicks? fromJson(Object? json) {
    if (json == null) return null;
    if (json is! Map) throw const FormatException('Clicks fixos inválidos');
    List<double> list(String key) => List.unmodifiable([for (final v in (json[key] as List? ?? const [])) (v as num).toDouble()]);
    final clicks = FixedClicks(accents: list('accents'), quarters: list('quarters'), eighths: list('eighths'), sixteenths: list('sixteenths'));
    if (!clicks.isValid) throw const FormatException('Clicks fixos inválidos');
    return clicks.isEmpty ? null : clicks;
  }

  @override
  bool operator ==(Object other) =>
      other is FixedClicks &&
      listEquals(other.accents, accents) &&
      listEquals(other.quarters, quarters) &&
      listEquals(other.eighths, eighths) &&
      listEquals(other.sixteenths, sixteenths);

  @override
  int get hashCode => Object.hash(Object.hashAll(accents), Object.hashAll(quarters), Object.hashAll(eighths), Object.hashAll(sixteenths));
}
