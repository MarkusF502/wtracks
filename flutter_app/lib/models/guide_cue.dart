import 'package:flutter/foundation.dart';

@immutable
class GuideCue {
  final String id, label, resourceName;
  final double timeSeconds, gain;
  const GuideCue({
    required this.id,
    required this.label,
    required this.resourceName,
    required this.timeSeconds,
    this.gain = 1,
  });
  bool get isValid =>
      id.isNotEmpty &&
      label.trim().isNotEmpty &&
      resourceName.isNotEmpty &&
      timeSeconds.isFinite &&
      timeSeconds >= 0 &&
      gain.isFinite &&
      gain >= 0 &&
      gain <= 2;
  @override
  bool operator ==(Object other) =>
      other is GuideCue &&
      other.id == id &&
      other.label == label &&
      other.resourceName == resourceName &&
      other.timeSeconds == timeSeconds &&
      other.gain == gain;
  @override
  int get hashCode => Object.hash(id, label, resourceName, timeSeconds, gain);
  Map<String, dynamic> toJson() => {
    'id': id,
    'label': label,
    'resourceName': resourceName,
    'timeSeconds': timeSeconds,
    'gain': gain,
  };
  factory GuideCue.fromJson(Map<String, dynamic> json) {
    final cue = GuideCue(
      id: json['id'] as String,
      label: json['label'] as String,
      resourceName: json['resourceName'] as String,
      timeSeconds: (json['timeSeconds'] as num).toDouble(),
      gain: (json['gain'] as num?)?.toDouble() ?? 1,
    );
    if (!cue.isValid) throw const FormatException('Guia inválida');
    return cue;
  }
  static bool validSequence(List<GuideCue> cues) {
    if (cues.length > 4096) return false;
    double previous = 0;
    final ids = <String>{};
    for (final cue in cues) {
      if (!cue.isValid || cue.timeSeconds < previous || !ids.add(cue.id)) {
        return false;
      }
      previous = cue.timeSeconds;
    }
    return true;
  }

  static List<GuideCue> fromJsonList(List<dynamic> list) {
    final cues = list
        .map((v) => GuideCue.fromJson(v as Map<String, dynamic>))
        .toList();
    if (!validSequence(cues)) {
      throw const FormatException('Agenda de guias inválida');
    }
    return List.unmodifiable(cues);
  }
}
