import 'package:flutter/foundation.dart';

import '../services/multitracks_contract.dart';
import 'multitracks_origin.dart';

/// Uma tonalidade devolvida pela API (`keys[]`). Só entram as que trazem `keyID` inteiro e `title` texto.
@immutable
class MultiTracksKeyOption {
  final int keyId;
  final String title;
  const MultiTracksKeyOption(this.keyId, this.title);
}

/// Direito observado na resposta. [kind] só sai de [MultiTracksEntitlementKind.unknown] com evidência direta:
/// `playOfTheWeek: true` (oferta semanal), `rentalsInfo` preenchido (Rental) ou `dateContentPurchased` na biblioteca.
@immutable
class MultiTracksEntitlement {
  final MultiTracksEntitlementKind kind;
  final DateTime? expiresAt;
  const MultiTracksEntitlement(this.kind, [this.expiresAt]);
}

/// Metadados de uma música para a tela de detalhes, derivados de `content/download` sem link e sem resgate.
@immutable
class MultiTracksSongDetails {
  final MultiTracksContentSelection selection;
  final MultiTracksContentItem item;
  final String title;
  final String? artist, album, originalKey, imageUrl;
  final num? bpm;
  final List<MultiTracksKeyOption> keys;
  final MultiTracksEntitlement entitlement;

  /// Créditos de Rental restantes, quando a resposta informou.
  final int? rentalsRemaining;

  /// O backend indicou que Rental é possível (`rentalsRemaining > 0` ou `rentalsAvailable` na biblioteca).
  final bool rentalPossible;

  const MultiTracksSongDetails({
    required this.selection,
    required this.item,
    required this.title,
    this.artist,
    this.album,
    this.originalKey,
    this.imageUrl,
    this.bpm,
    required this.keys,
    required this.entitlement,
    this.rentalsRemaining,
    required this.rentalPossible,
  });

  factory MultiTracksSongDetails.from(
    MultiTracksContentSelection selection,
    MultiTracksContentResponse response, {
    MultiTracksSongSummary? summary,
  }) {
    final matching = response.items.where(
      (item) => item.contentId == null || item.contentId == selection.contentId,
    );
    if (matching.isEmpty) {
      throw const FormatException('Resposta sem o conteúdo pedido');
    }
    final item = matching.first;
    final raw = item.raw;
    String? text(String key) =>
        raw[key] is String && (raw[key] as String).trim().isNotEmpty
        ? (raw[key] as String).trim()
        : null;
    final bpm = raw['bpm'];
    final remaining = response.rentalsRemaining;
    return MultiTracksSongDetails(
      selection: selection,
      item: item,
      title:
          item.title ?? summary?.song ?? 'MultiTracks ${selection.contentId}',
      artist: text('artist') ?? summary?.artist,
      album: text('album') ?? summary?.album,
      originalKey: text('originalKey'),
      imageUrl: text('image') ?? summary?.image,
      bpm: bpm is num && bpm.isFinite && bpm > 0 ? bpm : null,
      keys: parseKeys(raw['keys']),
      entitlement: entitlementOf(item, summary),
      rentalsRemaining: remaining,
      rentalPossible:
          (remaining != null && remaining > 0) ||
          (summary?.rentalsAvailable ?? false),
    );
  }

  static List<MultiTracksKeyOption> parseKeys(Object? value) {
    if (value is! List) return const [];
    final seen = <int>{};
    return List.unmodifiable([
      for (final key in value)
        if (key is Map &&
            key['keyID'] is int &&
            key['title'] is String &&
            seen.add(key['keyID'] as int))
          MultiTracksKeyOption(
            key['keyID'] as int,
            (key['title'] as String).trim(),
          ),
    ]);
  }

  static MultiTracksEntitlement entitlementOf(
    MultiTracksContentItem item,
    MultiTracksSongSummary? summary,
  ) {
    final rental = item.raw['rentalsInfo'];
    final rentalExpiry = rental is Map
        ? MultiTracksOrigin.parseZonedDate(rental['rentalDateExpiration'])
        : null;
    if (item.playOfTheWeek == true) {
      return MultiTracksEntitlement(
        MultiTracksEntitlementKind.weekly,
        rentalExpiry ??
            MultiTracksOrigin.parseZonedDate(
              item.raw['freeContentDateExpiration'],
            ),
      );
    }
    if (rental is Map) {
      return MultiTracksEntitlement(
        MultiTracksEntitlementKind.rental,
        rentalExpiry,
      );
    }
    if (summary?.dateContentPurchased != null) {
      return const MultiTracksEntitlement(MultiTracksEntitlementKind.owned);
    }
    return const MultiTracksEntitlement(MultiTracksEntitlementKind.unknown);
  }

  /// Título da tonalidade selecionada, quando a API a listou.
  String? get selectedKeyTitle =>
      keys.where((k) => k.keyId == selection.keyId).firstOrNull?.title;

  /// Resolve a consulta inicial da biblioteca (`keyID: 0`) para uma tonalidade baixável. A API capturada informa o
  /// tom original como texto e a lista de `keys`; campos numéricos são aceitos quando presentes em outras versões.
  MultiTracksContentSelection? get resolvedSelection {
    if (selection.keyId > 0) return selection;
    final rawKey = item.raw['originalKeyID'] ?? item.raw['keyID'];
    var keyId = rawKey is int && rawKey > 0 ? rawKey : null;
    final wanted = _normalizedKey(originalKey);
    if (keyId == null && wanted != null) {
      keyId = keys
          .where((key) => _normalizedKey(key.title) == wanted)
          .firstOrNull
          ?.keyId;
    }
    keyId ??= keys.firstOrNull?.keyId;
    keyId ??= item.stems.where((stem) => stem.keyId > 0).firstOrNull?.keyId;
    if (keyId == null) return null;
    return MultiTracksContentSelection(
      contentId: selection.contentId,
      contentType: selection.contentType,
      keyId: keyId,
      midiBankId: selection.midiBankId,
      demoSetlistSongId: selection.demoSetlistSongId,
    );
  }

  /// Faixas da tonalidade selecionada (as da própria tonalidade e as `anyKey`), na ordem da API, sem repetir `stemID`.
  /// É a mesma regra que o importador usa para casar os arquivos do pacote.
  List<MultiTracksStemDescriptor> get stemsForSelectedKey =>
      stemsForKey(item.stems, selection.keyId);

  static List<MultiTracksStemDescriptor> stemsForKey(
    List<MultiTracksStemDescriptor> stems,
    int keyId,
  ) {
    final seen = <int>{};
    final selected =
        [
          for (final stem in stems)
            if ((stem.keyId == keyId || stem.anyKey) && seen.add(stem.stemId))
              stem,
        ]..sort(
          (a, b) => a.order != b.order
              ? a.order.compareTo(b.order)
              : a.stemId.compareTo(b.stemId),
        );
    return List.unmodifiable(selected);
  }

  /// Versão do pacote informada pela API, como texto (tipo serializado não confirmado).
  String? get stemsVersion => _versionText(item.raw['stemsVersion']);
  String? get packageVersion => _versionText(item.raw['version']);

  static String? _versionText(Object? value) =>
      value is String || value is int ? value.toString() : null;

  static String? _normalizedKey(String? value) {
    final normalized = value
        ?.trim()
        .toLowerCase()
        .replaceAll('♭', 'b')
        .replaceAll('♯', '#');
    return normalized == null || normalized.isEmpty ? null : normalized;
  }
}

/// Espaço necessário para importar um pacote de [packageBytes]: o `.mtrack`, o ZIP decodificado, os M4A extraídos e os
/// WAV — duas vezes, porque o salvamento copia para a biblioteca antes de apagar a origem. A expansão AAC→WAV 16 bits
/// é estimada em até 12× (AAC a ~118 kbps contra 1411 kbps do PCM estéreo 44,1 kHz): uma estimativa, não uma medida.
int estimateImportBytes(int packageBytes, {int expansionFactor = 12}) {
  if (packageBytes <= 0) return 0;
  const limit =
      1 << 52; // muito além de qualquer disco; evita estouro de inteiro
  final perUnit = 3 + 2 * expansionFactor;
  if (packageBytes > limit ~/ perUnit) return limit;
  return packageBytes * perUnit;
}
