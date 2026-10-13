import 'package:flutter/foundation.dart';

/// Ações que um controlador MIDI ou o teclado podem disparar. A lista do Playback (MIDI Mapping 2.0, mapeamentos de
/// transporte) não foi recuperada; estas são as ações do nosso transporte (escolha própria).
enum ControlAction {
  playPause('Tocar / pausar'),
  stop('Parar'),
  nextSong('Próxima música'),
  previousSong('Música anterior'),
  nextSection('Próxima seção'),
  previousSection('Seção anterior'),
  fadeOut('Fade de 5 segundos'),
  toggleClick('Liga/desliga click'),
  toggleGuides('Liga/desliga guias'),
  toggleAutomation('Liga/desliga automação');

  final String label;
  const ControlAction(this.label);
  static ControlAction? parse(Object? name) => ControlAction.values.where((a) => a.name == name).firstOrNull;
}

/// Tipo do mapeamento (`mappingTypeID`; numeração nossa).
enum MappingType { midiNote, midiControlChange, midiProgramChange, keyboard }

/// Mapeamento de controle (Playback ControlMapping{mappingID, mappingTypeID, intValue1..3, stringValue1}): [mappingID] é a
/// ação; MIDI usa [intValue1] = canal 1..16 (0 = qualquer) e [intValue2] = nota/controlador/programa; teclado usa
/// [stringValue1] = rótulo da tecla. [intValue3] fica reservado (0).
@immutable
class ControlMapping {
  final String mappingID;
  final int mappingTypeID;
  final int intValue1, intValue2, intValue3;
  final String? stringValue1;
  const ControlMapping({
    required this.mappingID,
    required this.mappingTypeID,
    this.intValue1 = 0,
    this.intValue2 = 0,
    this.intValue3 = 0,
    this.stringValue1,
  });

  ControlAction? get action => ControlAction.parse(mappingID);
  MappingType? get type => mappingTypeID >= 0 && mappingTypeID < MappingType.values.length ? MappingType.values[mappingTypeID] : null;
  bool get isKeyboard => type == MappingType.keyboard;

  bool get isValid {
    if (action == null || type == null) return false;
    if (isKeyboard) return (stringValue1 ?? '').isNotEmpty;
    return intValue1 >= 0 && intValue1 <= 16 && intValue2 >= 0 && intValue2 <= 127;
  }

  /// Mapeamento MIDI a partir de uma mensagem recebida (aprendizado): note on, control change ou program change.
  static ControlMapping? learn(ControlAction action, List<int> bytes) {
    if (bytes.length < 2) return null;
    final kind = bytes[0] & 0xF0, channel = (bytes[0] & 0x0F) + 1;
    final type = switch (kind) {
      0x90 when bytes.length == 3 && bytes[2] > 0 => MappingType.midiNote,
      0xB0 when bytes.length == 3 => MappingType.midiControlChange,
      0xC0 => MappingType.midiProgramChange,
      _ => null,
    };
    if (type == null) return null;
    return ControlMapping(mappingID: action.name, mappingTypeID: type.index, intValue1: channel, intValue2: bytes[1]);
  }

  /// A mensagem dispara este mapeamento? Nota: note on com velocidade > 0; CC: valor >= 64 (pedal/botão apertado —
  /// escolha própria); PC: o número.
  bool matches(List<int> bytes) {
    if (isKeyboard || bytes.length < 2) return false;
    final kind = bytes[0] & 0xF0, channel = (bytes[0] & 0x0F) + 1;
    if (intValue1 != 0 && intValue1 != channel) return false;
    return switch (type) {
      MappingType.midiNote => kind == 0x90 && bytes.length == 3 && bytes[2] > 0 && bytes[1] == intValue2,
      MappingType.midiControlChange => kind == 0xB0 && bytes.length == 3 && bytes[1] == intValue2 && bytes[2] >= 64,
      MappingType.midiProgramChange => kind == 0xC0 && bytes[1] == intValue2,
      _ => false,
    };
  }

  /// Mesmo mapeamento valendo para qualquer canal.
  ControlMapping copyWithAnyChannel() => ControlMapping(
      mappingID: mappingID, mappingTypeID: mappingTypeID, intValue2: intValue2, intValue3: intValue3, stringValue1: stringValue1);

  String describe() => switch (type) {
        MappingType.midiNote => 'Nota $intValue2 · ${intValue1 == 0 ? 'qualquer canal' : 'canal $intValue1'}',
        MappingType.midiControlChange => 'CC $intValue2 · ${intValue1 == 0 ? 'qualquer canal' : 'canal $intValue1'}',
        MappingType.midiProgramChange => 'PC $intValue2 · ${intValue1 == 0 ? 'qualquer canal' : 'canal $intValue1'}',
        MappingType.keyboard => 'Tecla $stringValue1',
        null => '?',
      };

  Map<String, dynamic> toJson() => {
        'mappingID': mappingID,
        'mappingTypeID': mappingTypeID,
        'intValue1': intValue1,
        'intValue2': intValue2,
        'intValue3': intValue3,
        if (stringValue1 != null) 'stringValue1': stringValue1,
      };

  static ControlMapping? fromJson(Object? json) {
    if (json is! Map) return null;
    final mapping = ControlMapping(
      mappingID: json['mappingID'] is String ? json['mappingID'] as String : '',
      mappingTypeID: json['mappingTypeID'] is int ? json['mappingTypeID'] as int : -1,
      intValue1: json['intValue1'] is int ? json['intValue1'] as int : 0,
      intValue2: json['intValue2'] is int ? json['intValue2'] as int : 0,
      intValue3: json['intValue3'] is int ? json['intValue3'] as int : 0,
      stringValue1: json['stringValue1'] as String?,
    );
    return mapping.isValid ? mapping : null;
  }

  @override
  bool operator ==(Object other) =>
      other is ControlMapping &&
      other.mappingID == mappingID &&
      other.mappingTypeID == mappingTypeID &&
      other.intValue1 == intValue1 &&
      other.intValue2 == intValue2 &&
      other.intValue3 == intValue3 &&
      other.stringValue1 == stringValue1;
  @override
  int get hashCode => Object.hash(mappingID, mappingTypeID, intValue1, intValue2, intValue3, stringValue1);
}

/// Teclas padrão (escolha própria).
const defaultKeyboardMappings = [
  ControlMapping(mappingID: 'playPause', mappingTypeID: 3, stringValue1: ' '),
  ControlMapping(mappingID: 'nextSection', mappingTypeID: 3, stringValue1: 'Arrow Right'),
  ControlMapping(mappingID: 'previousSection', mappingTypeID: 3, stringValue1: 'Arrow Left'),
  ControlMapping(mappingID: 'nextSong', mappingTypeID: 3, stringValue1: 'Page Down'),
  ControlMapping(mappingID: 'previousSong', mappingTypeID: 3, stringValue1: 'Page Up'),
  ControlMapping(mappingID: 'fadeOut', mappingTypeID: 3, stringValue1: 'F'),
  ControlMapping(mappingID: 'toggleClick', mappingTypeID: 3, stringValue1: 'C'),
];
