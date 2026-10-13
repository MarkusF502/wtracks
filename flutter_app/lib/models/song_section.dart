import 'package:flutter/foundation.dart';

@immutable
class SongSection {
  final String id;
  final String name;
  final double startSeconds;
  final double endSeconds;
  const SongSection({
    required this.id,
    required this.name,
    required this.startSeconds,
    required this.endSeconds,
  });

  bool get isValid =>
      id.trim().isNotEmpty &&
      name.trim().isNotEmpty &&
      startSeconds.isFinite &&
      endSeconds.isFinite &&
      startSeconds >= 0 &&
      endSeconds > startSeconds;

  Map<String, dynamic> toJson() => {
    'id': id,
    'name': name,
    'startSeconds': startSeconds,
    'endSeconds': endSeconds,
  };

  factory SongSection.fromJson(Map<String, dynamic> json) {
    final section = SongSection(
      id: json['id'] as String,
      name: json['name'] as String,
      startSeconds: (json['startSeconds'] as num).toDouble(),
      endSeconds: (json['endSeconds'] as num).toDouble(),
    );
    if (!section.isValid) throw const FormatException('Seção inválida');
    return section;
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
