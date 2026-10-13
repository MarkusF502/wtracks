import 'package:flutter/foundation.dart';

@immutable
class SongSection {
  final String id;
  final String name;
  final double startSeconds;
  final double endSeconds;

  /// Passagens do laço antes de a música seguir (0 = laço até o usuário soltar).
  /// Mapeia SongSection.loopCount / loopInfinite do modelo do Playback.
  final int loopCount;

  /// Ao chegar nesta seção tocando, o laço infinito liga sozinho (vamp).
  /// Mapeia SongSection.presetInfiniteLoop.
  final bool presetInfiniteLoop;

  /// Falar o nome da seção antes dela (guia dinâmico). Mapeia storedPlayGuideCue.
  final bool playGuideCue;

  /// Contagem falada ao entrar na seção. Mapeia storedPlayCountIn.
  final bool playCountIn;

  /// Trechos cortados no início e no fim (segundos); a reprodução pula por cima deles.
  /// Mapeia storedStartTimeTrimOffset / storedEndTimeTrimOffset.
  final double trimStartSeconds, trimEndSeconds;

  /// Trecho que toca de fato (sem os cortes): laços, pré-roll e "tocar a partir da seção" usam estes limites.
  double get playStart => startSeconds + trimStartSeconds;
  double get playEnd => endSeconds - trimEndSeconds;

  static const maxLoopCount = 1000;

  const SongSection({
    required this.id,
    required this.name,
    required this.startSeconds,
    required this.endSeconds,
    this.loopCount = 0,
    this.presetInfiniteLoop = false,
    this.playGuideCue = true,
    this.playCountIn = false,
    this.trimStartSeconds = 0,
    this.trimEndSeconds = 0,
  });

  SongSection copyWith({
    String? name,
    double? startSeconds,
    double? endSeconds,
    int? loopCount,
    bool? presetInfiniteLoop,
    bool? playGuideCue,
    bool? playCountIn,
    double? trimStartSeconds,
    double? trimEndSeconds,
  }) =>
      SongSection(
        id: id,
        name: name ?? this.name,
        startSeconds: startSeconds ?? this.startSeconds,
        endSeconds: endSeconds ?? this.endSeconds,
        loopCount: loopCount ?? this.loopCount,
        presetInfiniteLoop: presetInfiniteLoop ?? this.presetInfiniteLoop,
        playGuideCue: playGuideCue ?? this.playGuideCue,
        playCountIn: playCountIn ?? this.playCountIn,
        trimStartSeconds: trimStartSeconds ?? this.trimStartSeconds,
        trimEndSeconds: trimEndSeconds ?? this.trimEndSeconds,
      );

  bool get isValid =>
      id.trim().isNotEmpty &&
      name.trim().isNotEmpty &&
      startSeconds.isFinite &&
      endSeconds.isFinite &&
      startSeconds >= 0 &&
      endSeconds > startSeconds &&
      loopCount >= 0 &&
      loopCount <= maxLoopCount &&
      trimStartSeconds.isFinite &&
      trimEndSeconds.isFinite &&
      trimStartSeconds >= 0 &&
      trimEndSeconds >= 0 &&
      playEnd - playStart >= 0.01;

  Map<String, dynamic> toJson() => {
    'id': id,
    'name': name,
    'startSeconds': startSeconds,
    'endSeconds': endSeconds,
    'loopCount': loopCount,
    'presetInfiniteLoop': presetInfiniteLoop,
    'playGuideCue': playGuideCue,
    'playCountIn': playCountIn,
    if (trimStartSeconds > 0) 'trimStartSeconds': trimStartSeconds,
    if (trimEndSeconds > 0) 'trimEndSeconds': trimEndSeconds,
  };

  factory SongSection.fromJson(Map<String, dynamic> json) {
    final section = SongSection(
      id: json['id'] as String,
      name: json['name'] as String,
      startSeconds: (json['startSeconds'] as num).toDouble(),
      endSeconds: (json['endSeconds'] as num).toDouble(),
      loopCount: (json['loopCount'] as num?)?.toInt() ?? 0,
      presetInfiniteLoop: json['presetInfiniteLoop'] as bool? ?? false,
      playGuideCue: json['playGuideCue'] as bool? ?? true,
      playCountIn: json['playCountIn'] as bool? ?? false,
      trimStartSeconds: (json['trimStartSeconds'] as num?)?.toDouble() ?? 0,
      trimEndSeconds: (json['trimEndSeconds'] as num?)?.toDouble() ?? 0,
    );
    if (!section.isValid) throw const FormatException('Seção inválida');
    return section;
  }

  @override
  bool operator ==(Object other) =>
      other is SongSection &&
      other.id == id &&
      other.name == name &&
      other.startSeconds == startSeconds &&
      other.endSeconds == endSeconds &&
      other.loopCount == loopCount &&
      other.presetInfiniteLoop == presetInfiniteLoop &&
      other.playGuideCue == playGuideCue &&
      other.playCountIn == playCountIn &&
      other.trimStartSeconds == trimStartSeconds &&
      other.trimEndSeconds == trimEndSeconds;
  @override
  int get hashCode => Object.hash(id, name, startSeconds, endSeconds, loopCount, presetInfiniteLoop, playGuideCue, playCountIn,
      trimStartSeconds, trimEndSeconds);

  /// Áreas cortadas da música, em ordem, com cortes vizinhos (fim de uma seção + início da seguinte) unidos.
  static List<(double, double)> trimAreas(List<SongSection> sections) {
    final areas = <(double, double)>[
      for (final s in sections) ...[
        if (s.trimStartSeconds > 0) (s.startSeconds, s.playStart),
        if (s.trimEndSeconds > 0) (s.playEnd, s.endSeconds),
      ],
    ]..sort((a, b) => a.$1.compareTo(b.$1));
    final merged = <(double, double)>[];
    for (final area in areas) {
      if (merged.isNotEmpty && area.$1 <= merged.last.$2 + 1e-9) {
        merged[merged.length - 1] = (merged.last.$1, area.$2 > merged.last.$2 ? area.$2 : merged.last.$2);
      } else {
        merged.add(area);
      }
    }
    return merged;
  }

  static bool validSequence(List<SongSection> sections) {
    final ids = <String>{};
    double previousEnd = 0;
    for (final section in sections) {
      if (!section.isValid ||
          !ids.add(section.id) ||
          section.startSeconds < previousEnd) {
        return false;
      }
      previousEnd = section.endSeconds;
    }
    return true;
  }

  static List<SongSection> fromJsonList(List<dynamic> values) {
    final sections = values
        .map((v) => SongSection.fromJson(v as Map<String, dynamic>))
        .toList();
    if (!validSequence(sections)) {
      throw const FormatException('Seções sobrepostas ou fora de ordem');
    }
    return List.unmodifiable(sections);
  }
}
