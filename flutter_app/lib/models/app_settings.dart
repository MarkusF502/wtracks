import 'package:flutter/foundation.dart';

/// Preferências gerais do app. [faderDefault80]: Playback "Fader Default Level 80%" — músicas importadas começam
/// com os faders dos canais em 80% em vez de 100% (o que o Playback faz além disso não foi recuperado).
/// [stereoSplit]: "Send Click & Guide to left and tracks to right (Stereo output only)".
@immutable
class AppSettings {
  final bool faderDefault80;
  final bool stereoSplit;
  const AppSettings({this.faderDefault80 = false, this.stereoSplit = false});

  double get defaultChannelVolume => faderDefault80 ? 0.8 : 1.0;

  AppSettings copyWith({bool? faderDefault80, bool? stereoSplit}) => AppSettings(
      faderDefault80: faderDefault80 ?? this.faderDefault80, stereoSplit: stereoSplit ?? this.stereoSplit);

  Map<String, dynamic> toJson() => {'faderDefault80': faderDefault80, 'stereoSplit': stereoSplit};

  factory AppSettings.fromJson(Object? json) {
    if (json is! Map) return const AppSettings();
    bool flag(String key) => json[key] is bool && json[key] as bool;
    return AppSettings(faderDefault80: flag('faderDefault80'), stereoSplit: flag('stereoSplit'));
  }

  @override
  bool operator ==(Object other) =>
      other is AppSettings && other.faderDefault80 == faderDefault80 && other.stereoSplit == stereoSplit;
  @override
  int get hashCode => Object.hash(faderDefault80, stereoSplit);
}
