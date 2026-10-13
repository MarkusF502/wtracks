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
  /// Banco e bus MIDI (Playback MIDIEvent.bank/bus); null = banco padrão / sem bus (canal do próprio cue).
  final String? bankId, busId;
  /// Nota: duração até o note-off (0 = sem note-off). MIDIEvent.duration.
  final double durationSeconds;
  /// Não dispara de novo nas repetições de um laço (MIDIEvent.disableLoop).
  final bool disableLoop;

  const AutomationCue({
    required this.id,
    required this.label,
    required this.timeSeconds,
    this.kind = AutomationMessageKind.none,
    this.channel = 1,
    this.data1 = 0,
    this.data2 = 0,
    this.bankId,
    this.busId,
    this.durationSeconds = 0,
    this.disableLoop = false,
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
      data2 <= 127 &&
      durationSeconds.isFinite &&
      durationSeconds >= 0 &&
      durationSeconds <= 3600;

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

  AutomationCue copyWith({String? id, String? label, double? timeSeconds, AutomationMessageKind? kind, int? channel, int? data1,
          int? data2, Object? bankId = _keep, Object? busId = _keep, double? durationSeconds, bool? disableLoop}) =>
      AutomationCue(
        id: id ?? this.id,
        label: label ?? this.label,
        timeSeconds: timeSeconds ?? this.timeSeconds,
        kind: kind ?? this.kind,
        channel: channel ?? this.channel,
        data1: data1 ?? this.data1,
        data2: data2 ?? this.data2,
        bankId: identical(bankId, _keep) ? this.bankId : bankId as String?,
        busId: identical(busId, _keep) ? this.busId : busId as String?,
        durationSeconds: durationSeconds ?? this.durationSeconds,
        disableLoop: disableLoop ?? this.disableLoop,
      );
  static const _keep = Object();

  Map<String, dynamic> toJson() => {
        'id': id,
        'label': label,
        'timeSeconds': timeSeconds,
        'kind': kind.name,
        'channel': channel,
        'data1': data1,
        'data2': data2,
        if (bankId != null) 'bankId': bankId,
        if (busId != null) 'busId': busId,
        if (durationSeconds > 0) 'durationSeconds': durationSeconds,
        if (disableLoop) 'disableLoop': true,
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
      bankId: json['bankId'] as String?,
      busId: json['busId'] as String?,
      durationSeconds: (json['durationSeconds'] as num?)?.toDouble() ?? 0,
      disableLoop: json['disableLoop'] as bool? ?? false,
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
      other.data2 == data2 &&
      other.bankId == bankId &&
      other.busId == busId &&
      other.durationSeconds == durationSeconds &&
      other.disableLoop == disableLoop;
  @override
  int get hashCode => Object.hash(id, label, timeSeconds, kind, channel, data1, data2, bankId, busId, durationSeconds, disableLoop);
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

/// Banco MIDI (Playback MIDIBank{title, bankDescription}): conjunto de cues; a música toca o banco ativo.
@immutable
class MidiBank {
  final String id, title, description;
  const MidiBank({required this.id, required this.title, this.description = ''});
  bool get isValid => id.isNotEmpty && title.trim().isNotEmpty;
  Map<String, dynamic> toJson() => {'id': id, 'title': title, 'description': description};
  factory MidiBank.fromJson(Map<String, dynamic> json) {
    final bank = MidiBank(id: json['id'] as String, title: json['title'] as String, description: json['description'] as String? ?? '');
    if (!bank.isValid) throw const FormatException('Banco MIDI inválido');
    return bank;
  }
  @override
  bool operator ==(Object other) => other is MidiBank && other.id == id && other.title == title && other.description == description;
  @override
  int get hashCode => Object.hash(id, title, description);
}

/// Bus MIDI (Playback MIDIBus{title, channel, enabled, allChannels}): os cues do bus saem no canal dele, a menos que
/// [allChannels] mantenha o canal de cada cue; desligado, não envia. A porta por bus (storedPortID) não é reproduzida:
/// todos usam a saída MIDI escolhida.
@immutable
class MidiBus {
  final String id, title;
  final int channel; // 1..16
  final bool enabled, allChannels;
  const MidiBus({required this.id, required this.title, this.channel = 1, this.enabled = true, this.allChannels = false});
  bool get isValid => id.isNotEmpty && title.trim().isNotEmpty && channel >= 1 && channel <= 16;
  MidiBus copyWith({String? title, int? channel, bool? enabled, bool? allChannels}) => MidiBus(
      id: id,
      title: title ?? this.title,
      channel: channel ?? this.channel,
      enabled: enabled ?? this.enabled,
      allChannels: allChannels ?? this.allChannels);
  Map<String, dynamic> toJson() => {'id': id, 'title': title, 'channel': channel, 'enabled': enabled, 'allChannels': allChannels};
  factory MidiBus.fromJson(Map<String, dynamic> json) {
    final bus = MidiBus(
      id: json['id'] as String,
      title: json['title'] as String,
      channel: (json['channel'] as num?)?.toInt() ?? 1,
      enabled: json['enabled'] as bool? ?? true,
      allChannels: json['allChannels'] as bool? ?? false,
    );
    if (!bus.isValid) throw const FormatException('Bus MIDI inválido');
    return bus;
  }
  @override
  bool operator ==(Object other) =>
      other is MidiBus && other.id == id && other.title == title && other.channel == channel && other.enabled == enabled && other.allChannels == allChannels;
  @override
  int get hashCode => Object.hash(id, title, channel, enabled, allChannels);
}

/// Uma mensagem na agenda nativa, com o cue que a originou ([source] = índice em Track.automationCues).
@immutable
class ScheduledMidi {
  final double timeSeconds;
  final List<int> bytes;
  final bool disableLoop;
  final int source;
  const ScheduledMidi(this.timeSeconds, this.bytes, this.source, {this.disableLoop = false});
  @override
  bool operator ==(Object other) =>
      other is ScheduledMidi && other.timeSeconds == timeSeconds && listEquals(other.bytes, bytes) && other.disableLoop == disableLoop && other.source == source;
  @override
  int get hashCode => Object.hash(timeSeconds, Object.hashAll(bytes), disableLoop, source);
  @override
  String toString() => 'M($timeSeconds $bytes #$source)';
}

/// Agenda MIDI da música: só os cues do banco ativo (sem banco = banco padrão, que vale quando [activeBankId] é null);
/// o canal vem do bus (exceto "todos os canais"); bus desligado não envia; nota com duração ganha o note-off.
/// Marcadores sem mensagem continuam na agenda (a interface mostra a automação disparada).
List<ScheduledMidi> buildMidiSchedule(List<AutomationCue> cues, List<MidiBus> buses, String? activeBankId) {
  final out = <(int, ScheduledMidi)>[];
  var order = 0;
  for (var i = 0; i < cues.length; i++) {
    final cue = cues[i];
    if (cue.bankId != activeBankId) continue;
    final bus = cue.busId == null ? null : buses.where((b) => b.id == cue.busId).firstOrNull;
    if (cue.busId != null && (bus == null || !bus.enabled)) continue;
    final channel = bus == null || bus.allChannels ? cue.channel : bus.channel;
    final message = cue.copyWith(channel: channel).midiBytes;
    out.add((order++, ScheduledMidi(cue.timeSeconds, message, i, disableLoop: cue.disableLoop)));
    if (cue.kind == AutomationMessageKind.noteOn && cue.durationSeconds > 0 && message.isNotEmpty) {
      out.add((order++, ScheduledMidi(cue.timeSeconds + cue.durationSeconds, [0x80 | (channel - 1), cue.data1, 0], i,
          disableLoop: cue.disableLoop)));
    }
  }
  out.sort((a, b) {
    final t = a.$2.timeSeconds.compareTo(b.$2.timeSeconds);
    return t != 0 ? t : a.$1.compareTo(b.$1);
  });
  return [for (final e in out) e.$2];
}

/// Cues de uma seção com tempos relativos ao início dela (Playback: "Copy Section Cues").
List<AutomationCue> copySectionCues(List<AutomationCue> cues, double start, double end, {String? bankId}) => [
      for (final c in cues)
        if (c.bankId == bankId && c.timeSeconds >= start && c.timeSeconds < end) c.copyWith(timeSeconds: c.timeSeconds - start),
    ];

/// "Paste Section Cues": substitui os cues do banco [bankId] dentro de [start, end) pelos copiados, deslocados para a seção;
/// o que passar do fim da seção fica de fora. [newId] gera ids novos. Resultado em ordem de tempo.
List<AutomationCue> pasteSectionCues(List<AutomationCue> cues, List<AutomationCue> copied, double start, double end,
    String Function() newId, {String? bankId}) {
  final kept = [for (final c in cues) if (!(c.bankId == bankId && c.timeSeconds >= start && c.timeSeconds < end)) c];
  final pasted = [
    for (final c in copied)
      if (start + c.timeSeconds < end) c.copyWith(id: newId(), timeSeconds: start + c.timeSeconds, bankId: bankId),
  ];
  final all = [...kept, ...pasted];
  final indexed = [for (var i = 0; i < all.length; i++) (i, all[i])]
    ..sort((a, b) {
      final t = a.$2.timeSeconds.compareTo(b.$2.timeSeconds);
      return t != 0 ? t : a.$1.compareTo(b.$1);
    });
  return [for (final e in indexed) e.$2];
}
