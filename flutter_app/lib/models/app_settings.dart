import 'package:flutter/foundation.dart';

/// Preferências gerais do app. [faderDefault80]: Playback "Fader Default Level 80%" — músicas importadas começam
/// com os faders dos canais em 80% em vez de 100% (o que o Playback faz além disso não foi recuperado).
@immutable
class AppSettings {
  final bool faderDefault80;
  const AppSettings({this.faderDefault80 = false});

  double get defaultChannelVolume => faderDefault80 ? 0.8 : 1.0;

  AppSettings copyWith({bool? faderDefault80}) => AppSettings(faderDefault80: faderDefault80 ?? this.faderDefault80);

  Map<String, dynamic> toJson() => {'faderDefault80': faderDefault80};

  factory AppSettings.fromJson(Object? json) {
    if (json is! Map) return const AppSettings();
    final fader = json['faderDefault80'];
    return AppSettings(faderDefault80: fader is bool && fader);
  }

  @override
  bool operator ==(Object other) => other is AppSettings && other.faderDefault80 == faderDefault80;
  @override
  int get hashCode => faderDefault80.hashCode;
}
