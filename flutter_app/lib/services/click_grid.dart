import '../models/tempo_change.dart';
import '../models/track.dart';

/// A grade de tempos do click de uma música em tempo de música, igual à do motor (`ClickTimeline`): o segmento base começa em
/// `beatOffsetSeconds` e cada mudança de andamento reinicia a contagem na sua posição. Um tempo dura `60 / bpm * bpmUnit / denominador`.
class ClickGrid {
  final List<_Segment> _segments;
  ClickGrid._(this._segments);

  factory ClickGrid.of(ClickSettings click, List<TempoChange> changes) {
    return ClickGrid._([
      _Segment(click.beatOffsetSeconds, 60.0 / click.bpm * click.bpmUnit / click.timeSignatureDenominator),
      for (final c in changes) _Segment(c.startSeconds, 60.0 / c.bpm * click.bpmUnit / c.denominator),
    ]);
  }

  /// O primeiro tempo em `t` ou depois (no segmento seguinte se o atual acabar antes).
  double nextBeatAtOrAfter(double t) {
    var index = 0;
    for (var i = 0; i < _segments.length; i++) {
      if (_segments[i].start <= t) index = i;
    }
    final segment = _segments[index];
    if (t <= segment.start) return segment.start;
    final candidate = segment.start + ((t - segment.start) / segment.beat).ceil() * segment.beat;
    if (index + 1 < _segments.length && candidate >= _segments[index + 1].start) return _segments[index + 1].start;
    return candidate;
  }
}

class _Segment {
  final double start, beat;
  const _Segment(this.start, this.beat);
}
