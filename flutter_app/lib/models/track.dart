import 'package:flutter/foundation.dart';
import 'song_section.dart';
import 'guide_cue.dart';
import 'automation_cue.dart';
import 'timecode_settings.dart';
import 'tempo_change.dart';
import 'time_pitch_settings.dart';

/// Saída do canal no mixer nativo (contrato BusChannelAU): estéreo usa a base
/// e a seguinte; mono mistura (L+R)/2 numa única saída. Em um dispositivo
/// estéreo, [left] e [right] permitem, por exemplo, click e banda separados.
enum ChannelRoute {
  stereo(0, false),
  left(0, true),
  right(1, true);

  final int outputBase;
  final bool mono;
  const ChannelRoute(this.outputBase, this.mono);

  /// Valores desconhecidos (arquivos de versões futuras) voltam ao estéreo.
  static ChannelRoute parse(Object? name) =>
      ChannelRoute.values.firstWhere((r) => r.name == name, orElse: () => ChannelRoute.stereo);
}

/// Representa um canal dentro de uma [Track] -- ex: "Click", "Bateria".
/// [filePath] é sempre um caminho LOCAL (já copiado do content:// original
/// pelo FileImportService) -- é isso que vai direto pro loadTrack() nativo.
@immutable
class ChannelInfo {
  final String label; // nome de exibição, ex: "Bateria"
  final String filePath; // caminho local real (não content://)
  final double volume; // 0.0 - 1.0, espelha o estado no AudioEngine
  final bool muted; // intenção manual do usuário (botão M)
  final bool soloed; // conceito só do Dart -- o AudioEngine não tem solo nativo
  final ChannelRoute route;

  const ChannelInfo({
    required this.label,
    required this.filePath,
    this.volume = 1.0,
    this.muted = false,
    this.soloed = false,
    this.route = ChannelRoute.stereo,
  });

  ChannelInfo copyWith({
    String? label,
    String? filePath,
    double? volume,
    bool? muted,
    bool? soloed,
    ChannelRoute? route,
  }) {
    return ChannelInfo(
      label: label ?? this.label,
      filePath: filePath ?? this.filePath,
      volume: volume ?? this.volume,
      muted: muted ?? this.muted,
      soloed: soloed ?? this.soloed,
      route: route ?? this.route,
    );
  }

  Map<String, dynamic> toJson() => {
        'label': label,
        'filePath': filePath,
        'volume': volume,
        'muted': muted,
        'soloed': soloed,
        'route': route.name,
      };

  factory ChannelInfo.fromJson(Map<String, dynamic> json) => ChannelInfo(
        label: json['label'] as String,
        filePath: json['filePath'] as String,
        volume: (json['volume'] as num?)?.toDouble() ?? 1.0,
        muted: json['muted'] as bool? ?? false,
        soloed: json['soloed'] as bool? ?? false,
        route: ChannelRoute.parse(json['route']),
      );
}

/// Metadados de click por música: BPM real da gravação e o instante exato
/// (em segundos) do primeiro tempo do compasso. Calibrado uma vez (manual
/// via tap tempo, ou futuramente detectado automaticamente a partir de uma
/// faixa de referência) e persistido junto com a música -- é isso que
/// resolve o desalinhamento de fase do click sintetizado, sem precisar
/// recalcular nada toda vez que a música é carregada.
///
/// [calibrated] indica se esses valores vieram de uma calibração de verdade
/// (tap tempo ou detecção automática) ou são só o palpite padrão -- útil
/// pra UI decidir se avisa "esta música ainda não foi calibrada".
@immutable
class ClickSettings {
  static const currentSchemaVersion = 2;
  final int schemaVersion;
  final double bpm;
  final double beatOffsetSeconds;
  final int timeSignatureNumerator;
  final int timeSignatureDenominator;
  final int bpmUnit;
  final double accentGain;
  final double quarterGain;
  final double eighthGain;
  final double sixteenthGain;
  final double volume;
  final String timbreFamily;
  final bool calibrated;

  const ClickSettings({
    this.schemaVersion = currentSchemaVersion,
    this.bpm = 120.0,
    this.beatOffsetSeconds = 0.0,
    this.timeSignatureNumerator = 4,
    this.timeSignatureDenominator = 4,
    this.bpmUnit = 4,
    this.accentGain = 1.0,
    this.quarterGain = 1.0,
    this.eighthGain = 0.0,
    this.sixteenthGain = 0.0,
    this.volume = 1.0,
    this.timbreFamily = 'synthetic',
    this.calibrated = false,
  });

  bool get isValid {
    bool unit(int n) => n >= 1 && n <= 64 && (n & (n - 1)) == 0;
    bool gain(double n) => n.isFinite && n >= 0 && n <= 2;
    return bpm.isFinite &&
        bpm >= 1 &&
        bpm <= 1000 &&
        beatOffsetSeconds.isFinite &&
        beatOffsetSeconds >= 0 && beatOffsetSeconds <= 86400 &&
        timeSignatureNumerator >= 1 &&
        timeSignatureNumerator <= 64 &&
        unit(timeSignatureDenominator) &&
        unit(bpmUnit) &&
        [
          accentGain,
          quarterGain,
          eighthGain,
          sixteenthGain,
          volume,
        ].every(gain) &&
        timbreFamily.isNotEmpty;
  }

  ClickSettings copyWith({
    double? bpm,
    double? beatOffsetSeconds,
    int? timeSignatureNumerator,
    int? timeSignatureDenominator,
    int? bpmUnit,
    double? accentGain,
    double? quarterGain,
    double? eighthGain,
    double? sixteenthGain,
    double? volume,
    String? timbreFamily,
    bool? calibrated,
  }) => ClickSettings(
      bpm: bpm ?? this.bpm,
      beatOffsetSeconds: beatOffsetSeconds ?? this.beatOffsetSeconds,
      timeSignatureNumerator: timeSignatureNumerator ?? this.timeSignatureNumerator,
    timeSignatureDenominator:
        timeSignatureDenominator ?? this.timeSignatureDenominator,
    bpmUnit: bpmUnit ?? this.bpmUnit,
    accentGain: accentGain ?? this.accentGain,
    quarterGain: quarterGain ?? this.quarterGain,
    eighthGain: eighthGain ?? this.eighthGain,
    sixteenthGain: sixteenthGain ?? this.sixteenthGain,
    volume: volume ?? this.volume,
    timbreFamily: timbreFamily ?? this.timbreFamily,
    calibrated: calibrated ?? this.calibrated,
    );

  Map<String, dynamic> toJson() => {
    'schemaVersion': currentSchemaVersion,
    'bpm': bpm,
        'beatOffsetSeconds': beatOffsetSeconds,
        'timeSignatureNumerator': timeSignatureNumerator,
    'timeSignatureDenominator': timeSignatureDenominator,
    'bpmUnit': bpmUnit,
    'accentGain': accentGain,
    'quarterGain': quarterGain,
    'eighthGain': eighthGain,
    'sixteenthGain': sixteenthGain,
    'volume': volume,
    'timbreFamily': timbreFamily,
        'calibrated': calibrated,
      };

  factory ClickSettings.fromJson(Map<String, dynamic> json) {
    final value = ClickSettings(
      schemaVersion: (json['schemaVersion'] as num?)?.toInt() ?? 1,
      bpm: (json['bpm'] as num?)?.toDouble() ?? 120,
        beatOffsetSeconds: (json['beatOffsetSeconds'] as num?)?.toDouble() ?? 0,
        timeSignatureNumerator: (json['timeSignatureNumerator'] as num?)?.toInt() ?? 4,
      timeSignatureDenominator:
          (json['timeSignatureDenominator'] as num?)?.toInt() ?? 4,
      bpmUnit: (json['bpmUnit'] as num?)?.toInt() ?? 4,
      accentGain: (json['accentGain'] as num?)?.toDouble() ?? 1,
      quarterGain: (json['quarterGain'] as num?)?.toDouble() ?? 1,
      eighthGain: (json['eighthGain'] as num?)?.toDouble() ?? 0,
      sixteenthGain: (json['sixteenthGain'] as num?)?.toDouble() ?? 0,
      volume: (json['volume'] as num?)?.toDouble() ?? 1,
      timbreFamily: json['timbreFamily'] as String? ?? 'synthetic',
      calibrated: json['calibrated'] as bool? ?? false,
      );
    if (!value.isValid) {
      throw const FormatException('Configuração de click inválida');
    }
    return value;
  }
}

/// Uma música com seus canais mapeados. [id] é o songId passado pro
/// AudioEngine nativo em loadTrack().
@immutable
class Track {
  static const currentSchemaVersion = 3;
  final List<GuideCue> guideCues;
  final bool guidesEnabled;
  final double masterVolume; // 0.0 - 2.0, ganho comum do mixer
  final TimePitchSettings timePitch;
  final List<AutomationCue> automationCues;
  final bool midiClockEnabled;
  final TimecodeSettings timecode;
  final List<TempoChange> tempoChanges;
  final int schemaVersion;
  final List<SongSection> sections;
  final String id;
  final String title;
  final List<ChannelInfo> channels;
  final ClickSettings clickSettings;
  final String? artist;
  final String? key; // tom musical, ex: "E", "B♭" -- string livre, sem enum

  const Track({
    this.guideCues = const [],
    this.guidesEnabled = true,
    this.masterVolume = 1.0,
    this.timePitch = const TimePitchSettings(),
    this.automationCues = const [],
    this.midiClockEnabled = false,
    this.timecode = const TimecodeSettings(),
    this.tempoChanges = const [],
    this.schemaVersion = currentSchemaVersion,
    this.sections = const [],
    required this.id,
    required this.title,
    required this.channels,
    this.clickSettings = const ClickSettings(),
    this.artist,
    this.key,
  });

  Track copyWith({
    List<GuideCue>? guideCues,
    bool? guidesEnabled,
    double? masterVolume,
    TimePitchSettings? timePitch,
    List<AutomationCue>? automationCues,
    bool? midiClockEnabled,
    TimecodeSettings? timecode,
    List<TempoChange>? tempoChanges,
    List<SongSection>? sections,
    String? title,
    List<ChannelInfo>? channels,
    ClickSettings? clickSettings,
    String? artist,
    String? key,
  }) {
    return Track(
      guideCues: guideCues ?? this.guideCues,
      guidesEnabled: guidesEnabled ?? this.guidesEnabled,
      masterVolume: masterVolume ?? this.masterVolume,
      timePitch: timePitch ?? this.timePitch,
      automationCues: automationCues ?? this.automationCues,
      midiClockEnabled: midiClockEnabled ?? this.midiClockEnabled,
      timecode: timecode ?? this.timecode,
      tempoChanges: tempoChanges ?? this.tempoChanges,
      sections: sections ?? this.sections,
      id: id,
      title: title ?? this.title,
      channels: channels ?? this.channels,
      clickSettings: clickSettings ?? this.clickSettings,
      artist: artist ?? this.artist,
      key: key ?? this.key,
    );
  }

  List<String> get channelFilePaths => channels.map((c) => c.filePath).toList();

  Map<String, dynamic> toJson() => {
        'schemaVersion': currentSchemaVersion,
        'sections': sections.map((s) => s.toJson()).toList(),
        'guideCues': guideCues.map((c) => c.toJson()).toList(),
        'guidesEnabled': guidesEnabled,
        'masterVolume': masterVolume,
        'timePitch': timePitch.toJson(),
        'automationCues': automationCues.map((c) => c.toJson()).toList(),
        'midiClockEnabled': midiClockEnabled,
        'timecode': timecode.toJson(),
        'tempoChanges': tempoChanges.map((c) => c.toJson()).toList(),
        'id': id,
        'title': title,
        'channels': channels.map((c) => c.toJson()).toList(),
        'clickSettings': clickSettings.toJson(),
        'artist': artist,
        'key': key,
      };

  // Campos ausentes no JSON (tracks salvas antes desta mudança) desserializam
  // como null sem quebrar -- não há chave 'artist'/'key' nesses arquivos.
  factory Track.fromJson(Map<String, dynamic> json) => Track(
        guideCues: GuideCue.fromJsonList(json['guideCues'] as List? ?? const []),
        guidesEnabled: json['guidesEnabled'] as bool? ?? true,
        timePitch: TimePitchSettings.fromJson(json['timePitch']),
        automationCues: AutomationCue.fromJsonList(json['automationCues'] as List? ?? const []),
        midiClockEnabled: json['midiClockEnabled'] as bool? ?? false,
        timecode: TimecodeSettings.fromJson(json['timecode']),
        tempoChanges: TempoChange.fromJsonList(json['tempoChanges'] as List? ?? const []),
        masterVolume: ((json['masterVolume'] as num?)?.toDouble() ?? 1.0).clamp(0.0, 2.0),
        schemaVersion: (json['schemaVersion'] as num?)?.toInt() ?? 1,
        sections: SongSection.fromJsonList(json['sections'] as List? ?? const []),
        id: json['id'] as String,
        title: json['title'] as String,
        channels: (json['channels'] as List)
            .map((c) => ChannelInfo.fromJson(c as Map<String, dynamic>))
            .toList(),
        clickSettings: json['clickSettings'] != null
            ? ClickSettings.fromJson(json['clickSettings'] as Map<String, dynamic>)
            : const ClickSettings(),
        artist: json['artist'] as String?,
        key: json['key'] as String?,
      );
}

/// Uma lista ordenada de músicas para um culto/ensaio.
@immutable
class Setlist {
  final String id;
  final String name;
  final List<Track> tracks;

  const Setlist({
    required this.id,
    required this.name,
    required this.tracks,
  });

  Setlist copyWith({String? name, List<Track>? tracks}) {
    return Setlist(
      id: id,
      name: name ?? this.name,
      tracks: tracks ?? this.tracks,
    );
  }

  /// Adiciona [track] ao final da lista -- no-op se já contém o id.
  Setlist withTrackAdded(Track track) {
    if (tracks.any((t) => t.id == track.id)) return this;
    return copyWith(tracks: [...tracks, track]);
  }

  /// Remove a track de id [trackId] -- no-op se não estiver presente.
  Setlist withTrackRemoved(String trackId) {
    if (!tracks.any((t) => t.id == trackId)) return this;
    return copyWith(tracks: tracks.where((t) => t.id != trackId).toList());
  }

  /// Reordena a lista de [oldIndex] para [newIndex], mesma semântica de
  /// índice usada por [ReorderableListView] (newIndex já considera o item
  /// removido de oldIndex).
  Setlist withTracksReordered(int oldIndex, int newIndex) {
    final updated = [...tracks];
    final item = updated.removeAt(oldIndex);
    var insertIndex = newIndex;
    if (oldIndex < newIndex) insertIndex -= 1;
    updated.insert(insertIndex, item);
    return copyWith(tracks: updated);
  }

  /// Serializa referenciando as tracks só por id (`trackIds`) -- não embute
  /// os objetos [Track] inteiros, pra evitar duplicação/dessincronia com o
  /// que está salvo em `tracks/<id>.json`. Resolver [trackIds] de volta pra
  /// [Track]s completas é responsabilidade do PersistenceService, não deste
  /// model -- por isso não existe um `Setlist.fromJson` que devolve um
  /// [Setlist] pronto com [tracks] populado.
  Map<String, dynamic> toJson() => {
        'id': id,
        'name': name,
        'trackIds': tracks.map((t) => t.id).toList(),
      };

  static String idFromJson(Map<String, dynamic> json) => json['id'] as String;
  static String nameFromJson(Map<String, dynamic> json) => json['name'] as String;
  static List<String> trackIdsFromJson(Map<String, dynamic> json) =>
      (json['trackIds'] as List).cast<String>();
}