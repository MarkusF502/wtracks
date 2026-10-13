import 'package:flutter/foundation.dart';

/// Preferências gerais do app. [faderDefault80]: Playback "Fader Default Level 80%" — músicas importadas começam
/// com os faders dos canais em 80% em vez de 100% (o que o Playback faz além disso não foi recuperado).
/// [stereoSplit]: "Send Click & Guide to left and tracks to right (Stereo output only)".
@immutable
class AppSettings {
  final bool faderDefault80;
  final bool stereoSplit;
  /// Pastas de sons personalizados (click e guias); null = só os do pacote.
  final String? customClicksDirectory, customGuidesDirectory;
  const AppSettings({this.faderDefault80 = false, this.stereoSplit = false, this.customClicksDirectory, this.customGuidesDirectory});

  double get defaultChannelVolume => faderDefault80 ? 0.8 : 1.0;

  AppSettings copyWith({bool? faderDefault80, bool? stereoSplit, Object? customClicksDirectory = _keep, Object? customGuidesDirectory = _keep}) =>
      AppSettings(
        faderDefault80: faderDefault80 ?? this.faderDefault80,
        stereoSplit: stereoSplit ?? this.stereoSplit,
        customClicksDirectory: identical(customClicksDirectory, _keep) ? this.customClicksDirectory : customClicksDirectory as String?,
        customGuidesDirectory: identical(customGuidesDirectory, _keep) ? this.customGuidesDirectory : customGuidesDirectory as String?,
      );
  static const _keep = Object();

  Map<String, dynamic> toJson() => {
        'faderDefault80': faderDefault80,
        'stereoSplit': stereoSplit,
        if (customClicksDirectory != null) 'customClicksDirectory': customClicksDirectory,
        if (customGuidesDirectory != null) 'customGuidesDirectory': customGuidesDirectory,
      };

  factory AppSettings.fromJson(Object? json) {
    if (json is! Map) return const AppSettings();
    bool flag(String key) => json[key] is bool && json[key] as bool;
    String? path(String key) => json[key] is String && (json[key] as String).isNotEmpty ? json[key] as String : null;
    return AppSettings(
      faderDefault80: flag('faderDefault80'),
      stereoSplit: flag('stereoSplit'),
      customClicksDirectory: path('customClicksDirectory'),
      customGuidesDirectory: path('customGuidesDirectory'),
    );
  }

  @override
  bool operator ==(Object other) =>
      other is AppSettings &&
      other.faderDefault80 == faderDefault80 &&
      other.stereoSplit == stereoSplit &&
      other.customClicksDirectory == customClicksDirectory &&
      other.customGuidesDirectory == customGuidesDirectory;
  @override
  int get hashCode => Object.hash(faderDefault80, stereoSplit, customClicksDirectory, customGuidesDirectory);
}
