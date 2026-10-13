import 'package:flutter/foundation.dart';

/// Preferências globais de guia (valem para todas as músicas), como no Playback:
/// "Guide Cue Language/Gender", "Count Into Each Section" ("Adds a verbal count
/// into each song section") e "Song Section Pre-roll" ("Provides a count-in when
/// playing from the beginning of a section"). [dynamicEnabled] liga a geração das
/// guias a partir das seções (escolha própria: no Playback é parte do arranjo).
@immutable
class GuideSettings {
  final bool dynamicEnabled;
  final String language; // código do nome dos arquivos: en, es, fr, id, ko, ph, pt
  final String gender; // female | male
  final bool countIntoEachSection;
  final bool sectionPreroll;

  const GuideSettings({
    this.dynamicEnabled = true,
    this.language = 'en',
    this.gender = 'female',
    this.countIntoEachSection = false,
    this.sectionPreroll = false,
  });

  GuideSettings copyWith({bool? dynamicEnabled, String? language, String? gender, bool? countIntoEachSection, bool? sectionPreroll}) =>
      GuideSettings(
        dynamicEnabled: dynamicEnabled ?? this.dynamicEnabled,
        language: language ?? this.language,
        gender: gender ?? this.gender,
        countIntoEachSection: countIntoEachSection ?? this.countIntoEachSection,
        sectionPreroll: sectionPreroll ?? this.sectionPreroll,
      );

  Map<String, dynamic> toJson() => {
        'dynamicEnabled': dynamicEnabled,
        'language': language,
        'gender': gender,
        'countIntoEachSection': countIntoEachSection,
        'sectionPreroll': sectionPreroll,
      };

  /// Valores ausentes ou de tipo errado voltam ao padrão (arquivo antigo ou corrompido).
  factory GuideSettings.fromJson(Object? json) {
    if (json is! Map) return const GuideSettings();
    T pick<T>(String key, T fallback) => json[key] is T ? json[key] as T : fallback;
    final language = pick<String>('language', 'en');
    final gender = pick<String>('gender', 'female');
    return GuideSettings(
      dynamicEnabled: pick<bool>('dynamicEnabled', true),
      language: RegExp(r'^[a-z]{2}$').hasMatch(language) ? language : 'en',
      gender: gender == 'male' ? 'male' : 'female',
      countIntoEachSection: pick<bool>('countIntoEachSection', false),
      sectionPreroll: pick<bool>('sectionPreroll', false),
    );
  }

  @override
  bool operator ==(Object other) =>
      other is GuideSettings &&
      other.dynamicEnabled == dynamicEnabled &&
      other.language == language &&
      other.gender == gender &&
      other.countIntoEachSection == countIntoEachSection &&
      other.sectionPreroll == sectionPreroll;
  @override
  int get hashCode => Object.hash(dynamicEnabled, language, gender, countIntoEachSection, sectionPreroll);
}
