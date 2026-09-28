import 'package:flutter/foundation.dart';

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

  const ChannelInfo({
    required this.label,
    required this.filePath,
    this.volume = 1.0,
    this.muted = false,
    this.soloed = false,
  });

  ChannelInfo copyWith({
    String? label,
    String? filePath,
    double? volume,
    bool? muted,
    bool? soloed,
  }) {
    return ChannelInfo(
      label: label ?? this.label,
      filePath: filePath ?? this.filePath,
      volume: volume ?? this.volume,
      muted: muted ?? this.muted,
      soloed: soloed ?? this.soloed,
    );
  }

  Map<String, dynamic> toJson() => {
        'label': label,
        'filePath': filePath,
        'volume': volume,
        'muted': muted,
        'soloed': soloed,
      };

  factory ChannelInfo.fromJson(Map<String, dynamic> json) => ChannelInfo(
        label: json['label'] as String,
        filePath: json['filePath'] as String,
        volume: (json['volume'] as num?)?.toDouble() ?? 1.0,
        muted: json['muted'] as bool? ?? false,
        soloed: json['soloed'] as bool? ?? false,
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
  final double bpm;
  final double beatOffsetSeconds;
  final int timeSignatureNumerator;
  final bool calibrated;

  const ClickSettings({
    this.bpm = 120.0,
    this.beatOffsetSeconds = 0.0,
    this.timeSignatureNumerator = 4,
    this.calibrated = false,
  });

  ClickSettings copyWith({
    double? bpm,
    double? beatOffsetSeconds,
    int? timeSignatureNumerator,
    bool? calibrated,
  }) {
    return ClickSettings(
      bpm: bpm ?? this.bpm,
      beatOffsetSeconds: beatOffsetSeconds ?? this.beatOffsetSeconds,
      timeSignatureNumerator: timeSignatureNumerator ?? this.timeSignatureNumerator,
      calibrated: calibrated ?? this.calibrated,
    );
  }

  Map<String, dynamic> toJson() => {
        'bpm': bpm,
        'beatOffsetSeconds': beatOffsetSeconds,
        'timeSignatureNumerator': timeSignatureNumerator,
        'calibrated': calibrated,
      };

  factory ClickSettings.fromJson(Map<String, dynamic> json) => ClickSettings(
        bpm: (json['bpm'] as num?)?.toDouble() ?? 120.0,
        beatOffsetSeconds: (json['beatOffsetSeconds'] as num?)?.toDouble() ?? 0.0,
        timeSignatureNumerator: (json['timeSignatureNumerator'] as num?)?.toInt() ?? 4,
        calibrated: json['calibrated'] as bool? ?? false,
      );
}

/// Uma música com seus canais mapeados. [id] é o songId passado pro
/// AudioEngine nativo em loadTrack().
@immutable
class Track {
  final String id;
  final String title;
  final List<ChannelInfo> channels;
  final ClickSettings clickSettings;
  final String? artist;
  final String? key; // tom musical, ex: "E", "B♭" -- string livre, sem enum

  const Track({
    required this.id,
    required this.title,
    required this.channels,
    this.clickSettings = const ClickSettings(),
    this.artist,
    this.key,
  });

  Track copyWith({
    String? title,
    List<ChannelInfo>? channels,
    ClickSettings? clickSettings,
    String? artist,
    String? key,
  }) {
    return Track(
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