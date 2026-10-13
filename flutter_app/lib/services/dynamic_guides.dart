import 'dart:math' as math;

import 'package:flutter/foundation.dart';

import '../models/guide_cue.dart';
import '../models/guide_settings.dart';
import '../models/song_section.dart';
import '../models/tempo_change.dart';
import '../models/track.dart';

/// Segmento do mapa de andamento no instante pedido (mesma regra do motor, `TempoMap.h`):
/// o segmento base é o do click; cada mudança vale a partir do seu início.
@immutable
class TempoSegment {
  final double bpm;
  final int numerator, denominator;
  const TempoSegment(this.bpm, this.numerator, this.denominator);

  /// Duração de um tempo em segundos: 60/bpm medido em [bpmUnit] (ClickTimeline: tick*4).
  double beatSeconds(int bpmUnit) => 60 / bpm * bpmUnit / denominator;

  static TempoSegment at(double seconds, ClickSettings click, List<TempoChange> changes) {
    var segment = TempoSegment(click.bpm, click.timeSignatureNumerator, click.timeSignatureDenominator);
    for (final change in changes) {
      if (change.startSeconds > seconds) break;
      segment = TempoSegment(change.bpm, change.numerator, change.denominator);
    }
    return segment;
  }
}

/// Voz das guias, tirada do nome dos arquivos do pacote: `guidecue-{count,section}-<idioma>-<gênero>-<nome>`.
@immutable
class GuideVoice {
  final String language, gender;
  const GuideVoice(this.language, this.gender);
  @override
  bool operator ==(Object other) => other is GuideVoice && other.language == language && other.gender == gender;
  @override
  int get hashCode => Object.hash(language, gender);
  @override
  String toString() => '$language-$gender';
}

const guideLanguageNames = {
  'en': 'English',
  'es': 'Español',
  'fr': 'Français',
  'id': 'Bahasa Indonesia',
  'ko': '한국어',
  'ph': 'Filipino',
  'pt': 'Português',
};

/// Recursos de guia por voz. O manifesto registra só o nome cru dos arquivos ("No inferred language or
/// semantic cue mapping"); a leitura de idioma/gênero/nome a partir do nome é nossa.
class GuideCatalog {
  final Map<GuideVoice, Map<String, String>> _sections = {};
  final Map<GuideVoice, Map<int, String>> _counts = {};

  GuideCatalog(Iterable<String> resourceNames) {
    final pattern = RegExp(r'^guidecue-(count|section)-([a-z]{2})-(female|male)-(.+)$');
    for (final name in resourceNames) {
      final match = pattern.firstMatch(name);
      if (match == null) continue;
      final voice = GuideVoice(match[2]!, match[3]!);
      if (match[1] == 'count') {
        final n = int.tryParse(match[4]!);
        if (n != null && n > 0) (_counts[voice] ??= {})[n] = name;
      } else {
        (_sections[voice] ??= {})[normalizeSectionName(match[4]!)] = name;
      }
    }
  }

  List<GuideVoice> get voices {
    final all = {..._sections.keys, ..._counts.keys}.toList()
      ..sort((a, b) => a.toString().compareTo(b.toString()));
    return all;
  }

  /// Recurso falado para o nome da seção, ou null se a voz não tem esse nome.
  String? section(GuideVoice voice, String sectionName) => _sections[voice]?[normalizeSectionName(sectionName)];

  /// Recurso que fala o número [n] (1..), ou null.
  String? count(GuideVoice voice, int n) => _counts[voice]?[n];

  int maxCount(GuideVoice voice) => _counts[voice]?.keys.fold<int>(0, math.max) ?? 0;

  bool has(GuideVoice voice) => _sections.containsKey(voice) || _counts.containsKey(voice);
}

// Nomes de seção em português/espanhol para o nome em inglês dos arquivos (escolha própria; os arquivos de todos os
// idiomas usam o rótulo em inglês, ex.: guidecue-section-pt-female-Chorus).
const _sectionAliases = {
  'verso': 'verse',
  'estrofe': 'verse',
  'refrao': 'chorus',
  'coro': 'chorus',
  'estribillo': 'chorus',
  'ponte': 'bridge',
  'puente': 'bridge',
  'pre refrao': 'pre chorus',
  'pre coro': 'pre chorus',
  'pos refrao': 'post chorus',
  'introducao': 'intro',
  'introduccion': 'intro',
  'final': 'ending',
  'interludio': 'interlude',
  'virada': 'turnaround',
  'a capella': 'acapella',
  'a cappella': 'acapella',
  'exortacao': 'exhortation',
};

/// Chave de comparação: minúsculas, sem acentos, hífens/sublinhados como espaço, espaços simples, "prechorus" =
/// "pre chorus", aliases em português/espanhol, número final preservado ("Refrão 2" -> "chorus 2").
String normalizeSectionName(String name) {
  const accents = {'á': 'a', 'à': 'a', 'â': 'a', 'ã': 'a', 'é': 'e', 'ê': 'e', 'í': 'i', 'ó': 'o', 'ô': 'o', 'õ': 'o', 'ú': 'u', 'ü': 'u', 'ç': 'c', 'ñ': 'n'};
  var key = name.toLowerCase().split('').map((c) => accents[c] ?? c).join();
  key = key.replaceAll(RegExp(r'[-_/.]'), ' ').replaceAll(RegExp(r'\s+'), ' ').trim();
  key = key.replaceAllMapped(RegExp(r'\b(pre|post|pos)(chorus|refrao|coro)\b'), (m) => '${m[1]} ${m[2]}');
  final number = RegExp(r'^(.*?)\s*(\d+)$').firstMatch(key);
  var base = number == null ? key : number[1]!;
  base = _sectionAliases[base] ?? base;
  return number == null ? base : '$base ${number[2]}';
}

/// Tipo do GuideCue do Playback (`cueType`): a evidência mostra os tipos 0 e 1 sem nome; a atribuição é nossa.
enum GuideCueType { section, count }

/// Guia derivada de uma seção, com os campos do GuideCue do Playback (cueType, sectionTypeID,
/// cueSequenceTimecode, songMapElementStartTimecode, cueEnabled, cueFilePath, replacementCountCueFilePath).
/// Caminhos são nomes de recurso do manifesto. [sectionId] ocupa o lugar de sectionTypeID (não temos tipos).
@immutable
class DynamicGuideCue {
  final GuideCueType cueType;
  final String sectionId;
  final double cueSequenceTimecode;
  final double songMapElementStartTimecode;
  final bool cueEnabled;
  final String? cueFilePath;
  final String? replacementCountCueFilePath;
  const DynamicGuideCue({
    required this.cueType,
    required this.sectionId,
    required this.cueSequenceTimecode,
    required this.songMapElementStartTimecode,
    this.cueEnabled = true,
    this.cueFilePath,
    this.replacementCountCueFilePath,
  });
  @override
  bool operator ==(Object other) =>
      other is DynamicGuideCue &&
      other.cueType == cueType &&
      other.sectionId == sectionId &&
      other.cueSequenceTimecode == cueSequenceTimecode &&
      other.songMapElementStartTimecode == songMapElementStartTimecode &&
      other.cueEnabled == cueEnabled &&
      other.cueFilePath == cueFilePath &&
      other.replacementCountCueFilePath == replacementCountCueFilePath;
  @override
  int get hashCode => Object.hash(cueType, sectionId, cueSequenceTimecode, songMapElementStartTimecode, cueEnabled, cueFilePath,
      replacementCountCueFilePath);
  @override
  String toString() => '${cueType.name}@${cueSequenceTimecode.toStringAsFixed(3)}:$cueFilePath/$replacementCountCueFilePath';
}

/// Resultado da geração: as guias e as seções cujo nome não tem áudio na voz escolhida.
@immutable
class DynamicGuidePlan {
  final List<DynamicGuideCue> cues;
  final List<String> missingSectionNames;
  const DynamicGuidePlan(this.cues, this.missingSectionNames);
}

/// Gera as guias das seções. Regras (escolha própria; o Playback não foi observado em execução):
/// - as guias de uma seção ocupam o compasso anterior ao seu início, contado para trás a partir do início com o
///   andamento/compasso vigente logo antes dele; tempos antes de 0 s são descartados;
/// - nome da seção (se `playGuideCue` e houver áudio) no 1º tempo; ele ocupa a primeira metade do compasso
///   (arredondada para cima) e a contagem (se `playCountIn` ou "Contar ao entrar em cada seção") fala os tempos
///   restantes ("Refrão... 3, 4"); sem nome, a contagem fala todos os tempos;
/// - com o laço ativo voltando antes da seção anunciada, o motor troca o nome pela contagem do mesmo tempo
///   (replacementCountCueFilePath) e os tempos cobertos pelo nome também contam; sem contagem pedida, fica em silêncio.
DynamicGuidePlan generateDynamicGuides({
  required List<SongSection> sections,
  required ClickSettings click,
  required List<TempoChange> tempoChanges,
  required GuideSettings settings,
  required GuideCatalog catalog,
}) {
  if (!settings.dynamicEnabled) return const DynamicGuidePlan([], []);
  final voice = GuideVoice(settings.language, settings.gender);
  final cues = <DynamicGuideCue>[];
  final missing = <String>[];
  for (final section in sections) {
    final wantCount = section.playCountIn || settings.countIntoEachSection;
    if (!section.playGuideCue && !wantCount) continue;
    final start = section.startSeconds;
    final segment = TempoSegment.at(math.max(0, start - 1e-6), click, tempoChanges);
    final beat = segment.beatSeconds(click.bpmUnit);
    final beats = segment.numerator;
    String? name;
    if (section.playGuideCue) {
      name = catalog.section(voice, section.name);
      if (name == null && !missing.contains(section.name)) missing.add(section.name);
    }
    final nameBeats = name == null ? 0 : (beats + 1) ~/ 2;
    for (var k = 0; k < beats; k++) {
      final time = start - (beats - k) * beat;
      if (time < -1e-9) continue;
      final at = math.max(0.0, time);
      final count = wantCount ? catalog.count(voice, k + 1) : null;
      if (k == 0 && name != null) {
        cues.add(DynamicGuideCue(cueType: GuideCueType.section, sectionId: section.id, cueSequenceTimecode: at,
            songMapElementStartTimecode: start, cueFilePath: name, replacementCountCueFilePath: count));
      } else if (count != null) {
        final covered = k < nameBeats;
        cues.add(DynamicGuideCue(cueType: GuideCueType.count, sectionId: section.id, cueSequenceTimecode: at,
            songMapElementStartTimecode: start, cueFilePath: covered ? null : count,
            replacementCountCueFilePath: covered ? count : null));
      }
    }
  }
  cues.sort((a, b) => a.cueSequenceTimecode.compareTo(b.cueSequenceTimecode));
  return DynamicGuidePlan(List.unmodifiable(cues), List.unmodifiable(missing));
}

/// Uma entrada da agenda nativa de guias (manuais + dinâmicas), com nomes de recurso.
@immutable
class ScheduledGuide {
  final double timeSeconds, gain, targetSeconds;
  final String? resource, replacement;
  const ScheduledGuide({required this.timeSeconds, this.resource, this.replacement, this.targetSeconds = -1, this.gain = 1});
  @override
  bool operator ==(Object other) =>
      other is ScheduledGuide &&
      other.timeSeconds == timeSeconds &&
      other.gain == gain &&
      other.targetSeconds == targetSeconds &&
      other.resource == resource &&
      other.replacement == replacement;
  @override
  int get hashCode => Object.hash(timeSeconds, gain, targetSeconds, resource, replacement);
}

/// Junta as guias manuais e as dinâmicas, em ordem de tempo (as manuais primeiro em empate).
/// Desativadas (`cueEnabled == false`) ficam de fora.
List<ScheduledGuide> buildGuideSchedule(List<GuideCue> manual, List<DynamicGuideCue> dynamic) {
  final entries = <ScheduledGuide>[
    for (final cue in manual) ScheduledGuide(timeSeconds: cue.timeSeconds, resource: cue.resourceName, gain: cue.gain),
    for (final cue in dynamic)
      if (cue.cueEnabled && (cue.cueFilePath != null || cue.replacementCountCueFilePath != null))
        ScheduledGuide(timeSeconds: cue.cueSequenceTimecode, resource: cue.cueFilePath,
            replacement: cue.replacementCountCueFilePath, targetSeconds: cue.songMapElementStartTimecode),
  ];
  return List.unmodifiable(_stableByTime(entries));
}

List<ScheduledGuide> _stableByTime(List<ScheduledGuide> entries) {
  // List.sort is not guaranteed stable.
  final indexed = [for (var i = 0; i < entries.length; i++) (i, entries[i])];
  indexed.sort((a, b) {
    final byTime = a.$2.timeSeconds.compareTo(b.$2.timeSeconds);
    return byTime != 0 ? byTime : a.$1.compareTo(b.$1);
  });
  return [for (final e in indexed) e.$2];
}

/// Recursos de contagem 1..16 da voz para o pré-roll (null onde faltar).
List<String?> prerollCounts(GuideCatalog catalog, GuideSettings settings) {
  final voice = GuideVoice(settings.language, settings.gender);
  return [for (var n = 1; n <= 16; n++) catalog.count(voice, n)];
}
