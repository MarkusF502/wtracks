import 'dart:math' as math;

import 'package:flutter/foundation.dart';

import 'tempo_change.dart';
import 'track.dart';
import '../services/dynamic_guides.dart' show TempoSegment;

/// Item de uma automação: o parâmetro ([automationID]) e o valor que ele atinge no ponto. Mapeia
/// AutomationItem{automationID, storedValue} do Playback. Os identificadores são nossos:
/// `channel:<índice>:volume` (0..1), `channel:<índice>:mute` (0/1) e `master:volume` (0..2).
@immutable
class AutomationItem {
  final String automationID;
  final double value;
  const AutomationItem(this.automationID, this.value);

  static String channelVolume(int channel) => 'channel:$channel:volume';
  static String channelMute(int channel) => 'channel:$channel:mute';
  static const masterVolume = 'master:volume';
  static const maxChannels = 64;

  /// Parâmetro nativo (MixerAutomation.h): volume c, mute 64+c, master 128; null se o id é inválido.
  int? get param {
    if (automationID == masterVolume) return 128;
    final match = RegExp(r'^channel:(\d{1,2}):(volume|mute)$').firstMatch(automationID);
    if (match == null) return null;
    final channel = int.parse(match[1]!);
    if (channel >= maxChannels) return null;
    return match[2] == 'mute' ? maxChannels + channel : channel;
  }

  bool get isMute => automationID.endsWith(':mute');
  int? get channel {
    final p = param;
    return p == null || p == 128 ? null : p % maxChannels;
  }

  bool get isValid {
    final p = param;
    if (p == null || !value.isFinite) return false;
    if (isMute) return value == 0 || value == 1;
    return value >= 0 && value <= (p == 128 ? 2 : 1);
  }

  Map<String, dynamic> toJson() => {'automationID': automationID, 'value': value};
  factory AutomationItem.fromJson(Map<String, dynamic> json) =>
      AutomationItem(json['automationID'] as String, (json['value'] as num).toDouble());

  @override
  bool operator ==(Object other) => other is AutomationItem && other.automationID == automationID && other.value == value;
  @override
  int get hashCode => Object.hash(automationID, value);
}

/// Ponto de automação do mixer na linha do tempo (tempo da música). Mapeia AutomationCue{name, details,
/// transitionBeats, sequenceTimecode, applyTransitionLengthCorrection, storedItems}: "Transition length is the length
/// of time (in beats) the faders will start leading to the Automation point. Mute or unmute changes are instant."
@immutable
class MixerAutomationCue {
  final String id, name, details;
  final double timeSeconds;
  final int transitionBeats;
  final bool applyTransitionLengthCorrection;
  final List<AutomationItem> items;

  static const maxTransitionBeats = 256;

  const MixerAutomationCue({
    required this.id,
    required this.name,
    this.details = '',
    required this.timeSeconds,
    this.transitionBeats = 0,
    this.applyTransitionLengthCorrection = false,
    this.items = const [],
  });

  MixerAutomationCue copyWith({String? id, String? name, String? details, double? timeSeconds, int? transitionBeats,
          bool? applyTransitionLengthCorrection, List<AutomationItem>? items}) =>
      MixerAutomationCue(
        id: id ?? this.id,
        name: name ?? this.name,
        details: details ?? this.details,
        timeSeconds: timeSeconds ?? this.timeSeconds,
        transitionBeats: transitionBeats ?? this.transitionBeats,
        applyTransitionLengthCorrection: applyTransitionLengthCorrection ?? this.applyTransitionLengthCorrection,
        items: items ?? this.items,
      );

  bool get isValid {
    final ids = <String>{};
    return id.isNotEmpty &&
        name.trim().isNotEmpty &&
        timeSeconds.isFinite &&
        timeSeconds >= 0 &&
        timeSeconds <= 86400 &&
        transitionBeats >= 0 &&
        transitionBeats <= maxTransitionBeats &&
        items.length <= 2 * AutomationItem.maxChannels + 1 &&
        items.every((i) => i.isValid && ids.add(i.automationID));
  }

  Map<String, dynamic> toJson() => {
        'id': id,
        'name': name,
        'details': details,
        'timeSeconds': timeSeconds,
        'transitionBeats': transitionBeats,
        'applyTransitionLengthCorrection': applyTransitionLengthCorrection,
        'items': items.map((i) => i.toJson()).toList(),
      };

  factory MixerAutomationCue.fromJson(Map<String, dynamic> json) {
    final cue = MixerAutomationCue(
      id: json['id'] as String,
      name: json['name'] as String,
      details: json['details'] as String? ?? '',
      timeSeconds: (json['timeSeconds'] as num).toDouble(),
      transitionBeats: (json['transitionBeats'] as num?)?.toInt() ?? 0,
      applyTransitionLengthCorrection: json['applyTransitionLengthCorrection'] as bool? ?? false,
      items: List.unmodifiable(((json['items'] as List?) ?? const []).map((v) => AutomationItem.fromJson(v as Map<String, dynamic>))),
    );
    if (!cue.isValid) throw const FormatException('Automação do mixer inválida');
    return cue;
  }

  static bool validSequence(List<MixerAutomationCue> cues) {
    if (cues.length > 4096) return false;
    double previous = 0;
    final ids = <String>{};
    for (final cue in cues) {
      if (!cue.isValid || cue.timeSeconds < previous || !ids.add(cue.id)) return false;
      previous = cue.timeSeconds;
    }
    return true;
  }

  static List<MixerAutomationCue> fromJsonList(List<dynamic> list) {
    final cues = list.map((v) => MixerAutomationCue.fromJson(v as Map<String, dynamic>)).toList();
    if (!validSequence(cues)) throw const FormatException('Agenda de automação do mixer inválida');
    return List.unmodifiable(cues);
  }

  /// Fotografia do mixer (Playback: "Set the Automation Snapshot"): volume e mute de cada canal e o master.
  static List<AutomationItem> snapshot(Track track) => [
        for (var i = 0; i < track.channels.length && i < AutomationItem.maxChannels; i++) ...[
          AutomationItem(AutomationItem.channelVolume(i), track.channels[i].volume.clamp(0.0, 1.0)),
          AutomationItem(AutomationItem.channelMute(i), track.channels[i].muted ? 1 : 0),
        ],
        AutomationItem(AutomationItem.masterVolume, track.masterVolume.clamp(0.0, 2.0)),
      ];

  @override
  bool operator ==(Object other) =>
      other is MixerAutomationCue &&
      other.id == id &&
      other.name == name &&
      other.details == details &&
      other.timeSeconds == timeSeconds &&
      other.transitionBeats == transitionBeats &&
      other.applyTransitionLengthCorrection == applyTransitionLengthCorrection &&
      listEquals(other.items, items);
  @override
  int get hashCode =>
      Object.hash(id, name, details, timeSeconds, transitionBeats, applyTransitionLengthCorrection, Object.hashAll(items));
}

/// Ponto nativo: [param] vai do valor que tem em [start] até [value] em [end] (segundos da música).
@immutable
class AutomationPoint {
  final double start, end, value;
  final int param;
  const AutomationPoint(this.start, this.end, this.param, this.value);
  @override
  bool operator ==(Object other) =>
      other is AutomationPoint && other.start == start && other.end == end && other.param == param && other.value == value;
  @override
  int get hashCode => Object.hash(start, end, param, value);
  @override
  String toString() => 'P($start..$end #$param=$value)';
}

/// Converte as automações em pontos nativos. Regras (escolha própria):
/// - a transição dura [MixerAutomationCue.transitionBeats] tempos do andamento vigente logo antes do ponto
///   (mapa de andamento + bpmUnit), sem começar antes de 0 s; mute/unmute é instantâneo no ponto;
/// - com `applyTransitionLengthCorrection`, a transição não começa antes do ponto anterior do mesmo parâmetro
///   (encurta); sem ela, pode começar no meio da transição anterior, que é cortada ali (o motor parte do valor
///   atingido), mas nunca antes do início dela;
/// - itens de canais que a música não tem são ignorados.
List<AutomationPoint> automationPoints(List<MixerAutomationCue> cues, ClickSettings click, List<TempoChange> tempoChanges,
    {int? channelCount}) {
  final points = <AutomationPoint>[];
  final lastStart = <int, double>{}, lastEnd = <int, double>{};
  for (final cue in cues) {
    final at = cue.timeSeconds;
    final beat = TempoSegment.at(math.max(0, at - 1e-6), click, tempoChanges).beatSeconds(click.bpmUnit);
    final ramp = math.max(0.0, at - cue.transitionBeats * beat);
    for (final item in cue.items) {
      final param = item.param;
      if (param == null || !item.isValid) continue;
      final channel = item.channel;
      if (channel != null && channelCount != null && channel >= channelCount) continue;
      var start = item.isMute ? at : ramp;
      if (cue.applyTransitionLengthCorrection) start = math.max(start, lastEnd[param] ?? 0);
      start = math.min(at, math.max(start, lastStart[param] ?? 0));
      points.add(AutomationPoint(start, at, param, item.value));
      lastStart[param] = start;
      lastEnd[param] = at;
    }
  }
  return points;
}
