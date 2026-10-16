import 'package:flutter/foundation.dart';

/// Tipo de direito com que o conteúdo MultiTracks foi obtido. Só é diferente de [unknown] quando a resposta da API deu
/// evidência direta (ver [MultiTracksOrigin]); o WTracks não deduz direitos de enums ainda não decifrados.
enum MultiTracksEntitlementKind {
  owned('Adquirida'),
  rental('Rental'),
  weekly('Oferta semanal'),
  unknown('Direito não confirmado');

  final String label;
  const MultiTracksEntitlementKind(this.label);

  static MultiTracksEntitlementKind parse(Object? name) =>
      values.firstWhere((kind) => kind.name == name, orElse: () => unknown);
}

/// Procedência de uma música importada da MultiTracks, gravada junto da [Track]. Nunca guarda senha, hash de sessão,
/// URL assinada, identificador do aparelho nem a resposta bruta da API.
@immutable
class MultiTracksOrigin {
  static const provider = 'multitracks';

  final int contentId;
  final int? libraryId;
  final int keyId;
  final int contentType;

  /// Versões informadas pela API (`stemsVersion`/`version`); o tipo serializado ainda não foi confirmado, então são
  /// guardadas como texto só para comparar uma versão local com a do servidor.
  final String? stemsVersion, packageVersion;
  final MultiTracksEntitlementKind entitlementKind;

  /// Somente quando a API informou a data com fuso horário; em UTC.
  final DateTime? entitlementExpiresAt;
  final DateTime lastValidatedAt;

  const MultiTracksOrigin({
    required this.contentId,
    this.libraryId,
    required this.keyId,
    required this.contentType,
    this.stemsVersion,
    this.packageVersion,
    this.entitlementKind = MultiTracksEntitlementKind.unknown,
    this.entitlementExpiresAt,
    required this.lastValidatedAt,
  });

  /// Conteúdo com validade vencida: sinalizado e revalidado antes de novo download, nunca apagado nem prolongado localmente.
  bool isExpiredAt(DateTime now) => entitlementExpiresAt != null && !now.toUtc().isBefore(entitlementExpiresAt!);

  Map<String, dynamic> toJson() => {
        'provider': provider,
        'contentId': contentId,
        if (libraryId != null) 'libraryId': libraryId,
        'keyId': keyId,
        'contentType': contentType,
        if (stemsVersion != null) 'stemsVersion': stemsVersion,
        if (packageVersion != null) 'packageVersion': packageVersion,
        'entitlementKind': entitlementKind.name,
        if (entitlementExpiresAt != null) 'entitlementExpiresAt': entitlementExpiresAt!.toUtc().toIso8601String(),
        'lastValidatedAt': lastValidatedAt.toUtc().toIso8601String(),
      };

  /// `null` quando a origem é de outro provedor (versões futuras) ou está incompleta: a música continua abrindo sem ela.
  static MultiTracksOrigin? fromJson(Object? json) {
    if (json is! Map || json['provider'] != provider) return null;
    final contentId = json['contentId'], keyId = json['keyId'], contentType = json['contentType'];
    final validated = DateTime.tryParse(json['lastValidatedAt'] as String? ?? '');
    if (contentId is! int || keyId is! int || contentType is! int || validated == null) return null;
    final libraryId = json['libraryId'];
    return MultiTracksOrigin(
      contentId: contentId,
      libraryId: libraryId is int ? libraryId : null,
      keyId: keyId,
      contentType: contentType,
      stemsVersion: json['stemsVersion'] as String?,
      packageVersion: json['packageVersion'] as String?,
      entitlementKind: MultiTracksEntitlementKind.parse(json['entitlementKind']),
      entitlementExpiresAt: parseZonedDate(json['entitlementExpiresAt']),
      lastValidatedAt: validated.toUtc(),
    );
  }

  /// Aceita apenas datas ISO-8601 com `Z` ou deslocamento explícito; datas sem fuso e sentinelas (anos 0001/1900) viram
  /// `null` para não inventar uma validade.
  static DateTime? parseZonedDate(Object? value) {
    if (value is! String || !RegExp(r'(Z|[+-]\d{2}:?\d{2})$').hasMatch(value)) return null;
    final parsed = DateTime.tryParse(value);
    if (parsed == null || parsed.year <= 1900) return null;
    return parsed.toUtc();
  }

  @override
  bool operator ==(Object other) =>
      other is MultiTracksOrigin &&
      other.contentId == contentId &&
      other.libraryId == libraryId &&
      other.keyId == keyId &&
      other.contentType == contentType &&
      other.stemsVersion == stemsVersion &&
      other.packageVersion == packageVersion &&
      other.entitlementKind == entitlementKind &&
      other.entitlementExpiresAt == entitlementExpiresAt &&
      other.lastValidatedAt == lastValidatedAt;

  @override
  int get hashCode => Object.hash(contentId, libraryId, keyId, contentType, stemsVersion, packageVersion, entitlementKind,
      entitlementExpiresAt, lastValidatedAt);
}
