import 'package:flutter/foundation.dart';

/// Tipos de mensagem MIDI que uma automação pode enviar (canal de voz).
enum AutomationMessageKind { none, programChange, controlChange, noteOn }

/// Marcação temporal da música (tempo da música) que o motor entrega no
/// instante exato e, opcionalmente, envia como mensagem MIDI. O conteúdo das
/// mensagens do Playback original vive no app principal e não foi recuperado;
/// os tipos acima são escolha própria.
@immutable
class AutomationCue {
  final String id, label;
  final double timeSeconds;
  final AutomationMessageKind kind;
  final int channel; // 1..16
  final int data1; // programa / controlador / nota (0..127)
  final int data2; // valor / velocidade (0..127)

  const AutomationCue({
    required this.id,
    required this.label,
    required this.timeSeconds,
    this.kind = AutomationMessageKind.none,
    this.channel = 1,
    this.data1 = 0,
    this.data2 = 0,
  });

  bool get isValid =>
      id.isNotEmpty &&
      label.trim().isNotEmpty &&
      timeSeconds.isFinite &&
      timeSeconds >= 0 &&
      channel >= 1 &&
      channel <= 16 &&
      data1 >= 0 &&
      data1 <= 127 &&
      data2 >= 0 &&
      data2 <= 127;

  /// Bytes da mensagem (vazio = só marcador).
  List<int> get midiBytes {
    final status = channel - 1;
    return switch (kind) {
      AutomationMessageKind.none => const [],
      AutomationMessageKind.programChange => [0xC0 | status, data1],
      AutomationMessageKind.controlChange => [0xB0 | status, data1, data2],
      AutomationMessageKind.noteOn => [0x90 | status, data1, data2],
    };
  }

  AutomationCue copyWith({String? label, double? timeSeconds, AutomationMessageKind? kind, int? channel, int? data1, int? data2}) =>
      AutomationCue(
        id: id,
        label: label ?? this.label,
        timeSeconds: timeSeconds ?? this.timeSeconds,
        kind: kind ?? this.kind,
        channel: channel ?? this.channel,
        data1: data1 ?? this.data1,
        data2: data2 ?? this.data2,
      );

  Map<String, dynamic> toJson() => {
        'id': id,
        'label': label,
        'timeSeconds': timeSeconds,
        'kind': kind.name,
        'channel': channel,
        'data1': data1,
        'data2': data2,
      };

  factory AutomationCue.fromJson(Map<String, dynamic> json) {
    final cue = AutomationCue(
      id: json['id'] as String,
      label: json['label'] as String,
      timeSeconds: (json['timeSeconds'] as num).toDouble(),
      kind: AutomationMessageKind.values.firstWhere((k) => k.name == json['kind'], orElse: () => throw const FormatException('Tipo de automação inválido')),
      channel: (json['channel'] as num?)?.toInt() ?? 1,
      data1: (json['data1'] as num?)?.toInt() ?? 0,
      data2: (json['data2'] as num?)?.toInt() ?? 0,
    );
    if (!cue.isValid) throw const FormatException('Automação inválida');
    return cue;
  }

  static bool validSequence(List<AutomationCue> cues) {
    if (cues.length > 4096) return false;
    double previous = 0;
    final ids = <String>{};
    for (final cue in cues) {
      if (!cue.isValid || cue.timeSeconds < previous || !ids.add(cue.id)) return false;
      previous = cue.timeSeconds;
    }
    return true;
  }

  static List<AutomationCue> fromJsonList(List<dynamic> list) {
    final cues = list.map((v) => AutomationCue.fromJson(v as Map<String, dynamic>)).toList();
    if (!validSequence(cues)) throw const FormatException('Agenda de automação inválida');
    return List.unmodifiable(cues);
  }

  @override
  bool operator ==(Object other) =>
      other is AutomationCue &&
      other.id == id &&
      other.label == label &&
      other.timeSeconds == timeSeconds &&
      other.kind == kind &&
      other.channel == channel &&
      other.data1 == data1 &&
      other.data2 == data2;
  @override
  int get hashCode => Object.hash(id, label, timeSeconds, kind, channel, data1, data2);
}

@immutable
class MidiDevice {
  final String id, name;
  const MidiDevice(this.id, this.name);
  @override
  bool operator ==(Object other) => other is MidiDevice && other.id == id && other.name == name;
  @override
  int get hashCode => Object.hash(id, name);
}
