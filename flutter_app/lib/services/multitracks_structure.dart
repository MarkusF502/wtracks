import 'dart:math' as math;

import '../models/fixed_clicks.dart';
import '../models/song_section.dart';
import '../models/tempo_change.dart';
import '../models/track.dart';

/// Estrutura musical de uma música MultiTracks (resposta de `content/download`): seções, mapa de andamento/compasso e instantes do
/// click. Contrato observado em 2026-10-16 (Playback 8.6.2, conteúdo 48052) e conferido contra o áudio do pacote:
/// - `timeCode` é texto `MM:SS:mmm` (minutos, segundos, milissegundos); compassos podem trazer um espaço no fim.
/// - `time` de andamentos e compassos é a posição em **tempos** (arredondada); `beats` é a mesma posição sem arredondar.
/// - Andamentos vêm em pares no mesmo ponto (fecha o trecho anterior, abre o novo): o mapa é por degraus, e uma mudança pode cair no
///   meio de um tempo (ritardando).
/// - `clicks.*` são instantes em segundos do arquivo de áudio; o último de cada lista é sentinela (duração + 1 s).
/// - Seções têm só o início (`timeCode`); o fim é o início da seguinte, e a última vai até `duration`. O nome vem do catálogo
///   [multiTracksSectionNames] pelo `sectionID`.
///
/// Nada aqui inventa dados: o que não confere (segundos calculados contra `timeCode`, ordem, limites) é descartado com um aviso, e a
/// música entra com o que restou (no pior caso só o BPM base, como antes).
class MultiTracksStructure {
  /// Diferença tolerada entre os segundos calculados pelos tempos e o `timeCode` (que tem resolução de 1 ms).
  static const timeCodeTolerance = 0.005;

  final List<SongSection> sections;
  final ClickSettings click;
  final List<TempoChange> tempoChanges;
  final FixedClicks? fixedClicks;
  final List<String> warnings;

  const MultiTracksStructure({
    this.sections = const [],
    this.click = const ClickSettings(),
    this.tempoChanges = const [],
    this.fixedClicks,
    this.warnings = const [],
  });

  /// [raw] é o item da resposta. [hasGuideStem]: o pacote traz um stem de guia, então o guia falado do WTracks fica desligado nas
  /// seções (senão o palco ouviria dois guias; escolha própria).
  factory MultiTracksStructure.parse(Map<String, Object?> raw, {ClickSettings base = const ClickSettings(), bool hasGuideStem = false}) {
    final warnings = <String>[];
    final duration = _number(raw['duration']);
    final validDuration = duration != null && duration > 0 && duration <= 86400 ? duration.toDouble() : null;
    if (validDuration == null) warnings.add('duração ausente ou inválida');

    final map = _TempoMap.parse(raw, warnings);
    var click = base;
    var changes = const <TempoChange>[];
    if (map != null) {
      click = base.copyWith(
        bpm: map.bpmAt(0),
        timeSignatureNumerator: map.signatureAt(0).$1,
        timeSignatureDenominator: map.signatureAt(0).$2,
        beatOffsetSeconds: 0,
        bpmUnit: 4,
      );
      changes = map.changes();
      if (!TempoChange.validSequence(changes)) {
        warnings.add('mapa de andamento fora dos limites do WTracks; ficou só o BPM inicial');
        changes = const [];
      }
      if (!click.isValid) {
        warnings.add('BPM/compasso inicial inválido');
        click = base;
        changes = const [];
      }
    } else {
      final bpm = _number(raw['bpm']);
      if (bpm != null && bpm >= 1 && bpm <= 1000) click = base.copyWith(bpm: bpm.toDouble());
    }

    return MultiTracksStructure(
      sections: validDuration == null ? const [] : _sections(raw['sections'], validDuration, hasGuideStem, warnings),
      click: click,
      tempoChanges: List.unmodifiable(changes),
      fixedClicks: _clicks(raw['clicks'], validDuration, warnings),
      warnings: List.unmodifiable(warnings),
    );
  }

  /// `MM:SS:mmm` em segundos; `null` se o formato não for esse.
  static double? parseTimeCode(Object? value) {
    if (value is! String) return null;
    final match = RegExp(r'^(\d{1,3}):(\d{2}):(\d{3})$').firstMatch(value.trim());
    if (match == null) return null;
    final minutes = int.parse(match[1]!), seconds = int.parse(match[2]!), millis = int.parse(match[3]!);
    if (seconds >= 60) return null;
    return minutes * 60 + seconds + millis / 1000;
  }

  static List<SongSection> _sections(Object? value, double duration, bool hasGuideStem, List<String> warnings) {
    if (value is! List || value.isEmpty) return const [];
    final items = [for (final v in value) if (v is Map) v]..sort((a, b) => (_int(a['order']) ?? 0).compareTo(_int(b['order']) ?? 0));
    final starts = <(Map, double)>[];
    for (final item in items) {
      final start = parseTimeCode(item['timeCode']);
      if (start == null || start >= duration || (starts.isNotEmpty && start <= starts.last.$2)) {
        warnings.add('seções descartadas: início inválido ou fora de ordem');
        return const [];
      }
      starts.add((item, start));
    }
    final sections = <SongSection>[
      for (var i = 0; i < starts.length; i++)
        SongSection(
          id: 'mt-${_int(starts[i].$1['contentSectionID']) ?? i}',
          name: multiTracksSectionName(_int(starts[i].$1['sectionID'])),
          startSeconds: starts[i].$2,
          endSeconds: i + 1 < starts.length ? starts[i + 1].$2 : duration,
          playGuideCue: !hasGuideStem,
        ),
    ];
    if (!SongSection.validSequence(sections)) {
      warnings.add('seções descartadas: não formam uma sequência válida');
      return const [];
    }
    return List.unmodifiable(sections);
  }

  static FixedClicks? _clicks(Object? value, double? duration, List<String> warnings) {
    if (value is! Map) return null;
    // A sentinela (duração + 1 s) sai; uma folga de 50 ms mantém o acento que cai 0,1 ms depois do fim.
    final limit = (duration ?? 86400) + 0.05;
    List<double>? list(String key) {
      final raw = value[key];
      if (raw == null) return const [];
      if (raw is! List) return null;
      final out = <double>[];
      for (final v in raw) {
        final t = _number(v);
        if (t == null || !t.isFinite || t < 0) return null;
        if (t <= limit) out.add(t.toDouble());
      }
      return List.unmodifiable(out);
    }

    final accents = list('accents'), quarters = list('quarters'), eighths = list('eighths'), sixteenths = list('sixteenths');
    if (accents == null || quarters == null || eighths == null || sixteenths == null) {
      warnings.add('clicks descartados: valores inválidos');
      return null;
    }
    final clicks = FixedClicks(accents: accents, quarters: quarters, eighths: eighths, sixteenths: sixteenths);
    if (!clicks.isValid) {
      warnings.add('clicks descartados: fora de ordem ou demais');
      return null;
    }
    return clicks.isEmpty ? null : clicks;
  }
}

/// Mapa por degraus em tempos: em cada ponto (posição em tempos) vale o último andamento/compasso daquele ponto.
class _TempoMap {
  final List<(double, double)> tempos; // (tempos, bpm), posições estritamente crescentes, começando em 0
  final List<(double, int, int)> signatures; // (tempos, numerador, denominador)
  _TempoMap(this.tempos, this.signatures);

  static _TempoMap? parse(Map<String, Object?> raw, List<String> warnings) {
    final tempoItems = _ordered(raw['tempos']);
    if (tempoItems.isEmpty) return null;
    final points = <(double, double, double?)>[]; // (tempos, bpm, segundos do timeCode)
    for (final item in tempoItems) {
      final beats = _number(item['beats']) ?? _number(item['time']);
      final bpm = _number(item['bpm']);
      if (beats == null || bpm == null || !beats.isFinite || beats < 0 || bpm < 1 || bpm > 1000) {
        warnings.add('andamentos descartados: valor inválido');
        return null;
      }
      if (points.isNotEmpty && beats < points.last.$1 - 1e-6) {
        warnings.add('andamentos descartados: fora de ordem');
        return null;
      }
      points.add((beats.toDouble(), bpm.toDouble(), MultiTracksStructure.parseTimeCode(item['timeCode'])));
    }
    if (points.first.$1 > 1e-6) {
      warnings.add('andamentos descartados: o primeiro não começa no início');
      return null;
    }
    // Degraus: no mesmo ponto vale o último.
    final tempos = <(double, double)>[];
    for (final (beats, bpm, _) in points) {
      if (tempos.isNotEmpty && (beats - tempos.last.$1).abs() < 1e-6) {
        tempos[tempos.length - 1] = (tempos.last.$1, bpm);
      } else {
        tempos.add((tempos.isEmpty ? 0.0 : beats, bpm));
      }
    }

    final signatures = <(double, int, int)>[];
    for (final item in _ordered(raw['timeSignatures'])) {
      final beats = _number(item['beats']) ?? _number(item['time']);
      final numerator = _int(item['beatsPerBar']), denominator = _int(item['beatUnit']);
      if (beats == null || numerator == null || denominator == null || beats < 0 || numerator < 1 || numerator > 64 ||
          denominator < 1 || denominator > 64 || (denominator & (denominator - 1)) != 0 ||
          (signatures.isNotEmpty && beats < signatures.last.$1 - 1e-6)) {
        warnings.add('compassos descartados: valor inválido ou fora de ordem');
        signatures.clear();
        break;
      }
      if (signatures.isNotEmpty && (beats - signatures.last.$1).abs() < 1e-6) {
        signatures[signatures.length - 1] = (signatures.last.$1, numerator, denominator);
      } else {
        signatures.add((signatures.isEmpty ? 0.0 : beats.toDouble(), numerator, denominator));
      }
    }
    if (signatures.any((s) => s.$3 != 4)) {
      warnings.add('compasso com unidade diferente de 4: a unidade do BPM da MultiTracks não foi confirmada para ele');
    }
    final map = _TempoMap(tempos, signatures);

    // Conferência: os segundos calculados pelos tempos precisam bater com o timeCode de cada ponto.
    for (final (beats, _, timeCode) in points) {
      if (timeCode != null && (map.secondsAt(beats) - timeCode).abs() > MultiTracksStructure.timeCodeTolerance) {
        warnings.add('mapa de andamento descartado: ${map.secondsAt(beats).toStringAsFixed(3)} s calculados contra '
            '${timeCode.toStringAsFixed(3)} s do timeCode');
        return null;
      }
    }
    for (final item in _ordered(raw['timeSignatures'])) {
      final beats = _number(item['beats']) ?? _number(item['time']);
      final timeCode = MultiTracksStructure.parseTimeCode(item['timeCode']);
      if (beats != null && timeCode != null && (map.secondsAt(beats.toDouble()) - timeCode).abs() > MultiTracksStructure.timeCodeTolerance) {
        warnings.add('compassos não conferem com o timeCode; ficou só o compasso inicial');
        return _TempoMap(tempos, signatures.isEmpty ? const [] : [signatures.first]);
      }
    }
    return map;
  }

  double bpmAt(double beats) {
    var bpm = tempos.first.$2;
    for (final (at, value) in tempos) {
      if (at <= beats + 1e-9) bpm = value;
    }
    return bpm;
  }

  (int, int) signatureAt(double beats) {
    var signature = (4, 4);
    for (final (at, n, d) in signatures) {
      if (at <= beats + 1e-9) signature = (n, d);
    }
    return signature;
  }

  /// Segundos de uma posição em tempos, somando cada degrau do andamento.
  double secondsAt(double beats) {
    var seconds = 0.0;
    for (var i = 0; i < tempos.length; i++) {
      final from = tempos[i].$1;
      if (from >= beats) break;
      final to = i + 1 < tempos.length ? math.min(tempos[i + 1].$1, beats) : beats;
      seconds += (to - from) * 60 / tempos[i].$2;
    }
    return seconds;
  }

  /// Uma mudança por ponto onde o andamento ou o compasso muda, com o estado completo daquele ponto. Uma mudança no meio de um
  /// tempo reinicia ali a grade do WTracks (relógio MIDI, crossfade ao vivo); o click toca pelos instantes da MultiTracks.
  List<TempoChange> changes() {
    final positions = <double>{
      for (final (at, _) in tempos) if (at > 0) at,
      for (final (at, _, _) in signatures) if (at > 0) at,
    }.toList()
      ..sort();
    final result = <TempoChange>[];
    var bpm = bpmAt(0);
    var signature = signatureAt(0);
    for (final at in positions) {
      final nextBpm = bpmAt(at), nextSignature = signatureAt(at);
      if (nextBpm == bpm && nextSignature == signature) continue;
      bpm = nextBpm;
      signature = nextSignature;
      result.add(TempoChange(
        id: 'mt-${result.length + 1}',
        startSeconds: secondsAt(at),
        bpm: bpm,
        numerator: signature.$1,
        denominator: signature.$2,
      ));
    }
    return result;
  }
}

List<Map> _ordered(Object? value) {
  if (value is! List) return const [];
  return [for (final v in value) if (v is Map) v]..sort((a, b) => (_int(a['order']) ?? 0).compareTo(_int(b['order']) ?? 0));
}

num? _number(Object? value) => value is num && value.isFinite ? value : null;
int? _int(Object? value) => value is int ? value : (value is num && value == value.roundToDouble() ? value.toInt() : null);

/// Nome em português de um `sectionID` da MultiTracks; desconhecido = "Seção".
String multiTracksSectionName(int? id) {
  final name = multiTracksSectionNames[id]?.trim();
  return name == null || name.isEmpty ? 'Seção' : name;
}

/// Catálogo de tipos de seção da MultiTracks (`sectionID`), com nomes em português. Os ids vêm do catálogo que acompanha o Playback
/// (`sections-*.json`); os nomes são termos musicais comuns, escritos aqui.
const multiTracksSectionNames = <int, String>{
  1: 'A cappella',
  2: 'Breakdown',
  3: 'Ponte',
  4: 'Canal',
  5: 'Refrão',
  6: 'Refrão 2',
  7: 'Contagem',
  8: 'Final',
  9: 'Instrumental',
  10: 'Interlúdio',
  11: 'Introdução',
  12: 'Saída',
  13: 'Pré-refrão',
  14: 'Coro',
  15: 'Solo',
  16: 'Tag',
  17: 'Vamp',
  18: 'Verso',
  19: 'Verso 1',
  20: 'Verso 2',
  21: 'Verso 3',
  53: 'Exortação',
  55: 'Pad',
  56: 'Verso 4',
  57: 'Verso 5',
  58: 'Ponte 2',
  59: 'Ponte 3',
  60: 'Ponte 4',
  61: 'Click',
  62: 'Turnaround',
  63: 'Pós-refrão',
  64: 'Refrão 1',
  65: 'Ponte 1',
  66: 'Rap',
  67: 'Pré-refrão 1',
  68: 'Pré-refrão 2',
  69: 'Pré-refrão 3',
  70: 'Pré-refrão 4',
  71: 'Refrão 3',
  72: 'Refrão 4',
  73: 'Verso 6',
  74: 'Refrão 5',
  75: 'Refrão 6',
  76: 'Refrão 7',
  77: 'Refrão 8',
  78: 'Verso 7',
  79: 'Verso 8',
  80: 'Ponte 5',
  81: 'Ponte 6',
  82: 'Ponte 7',
  83: 'Ponte 8',
  84: 'Pós-refrão 1',
  85: 'Pós-refrão 2',
  86: 'Pós-refrão 3',
  87: 'Pós-refrão 4',
  88: 'Coro 1',
  89: 'Coro 2',
  90: 'Coro 3',
  91: 'Coro 4',
  92: 'Tag 1',
  93: 'Tag 2',
  94: 'Tag 3',
  95: 'Tag 4',
  96: 'Vamp no 1',
  97: 'Vamp no 1 e 1sus',
  98: 'Vamp no 4',
  99: 'Vamp do refrão',
  100: 'Vamp da ponte',
  101: 'Final em vamp no 1',
  102: 'Final em vamp no 4',
  103: 'Vamp do verso',
  104: 'Vamp do pré-refrão',
};
