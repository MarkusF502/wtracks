import 'package:flutter/foundation.dart';

import 'track.dart';

/// Etapas reais da importação (seção 7 do plano de interface). Não há etapa de carregar no motor: a importação salva na
/// biblioteca sem trocar a música aberta, que só é carregada quando a pessoa toca em "Abrir música".
enum MultiTracksImportPhase {
  preparing('Preparando'),
  requestingDownloadLink('Obtendo autorização'),
  awaitingRentalConfirmation('Aguardando confirmação do aluguel'),
  redeemingRental('Confirmando aluguel'),
  downloading('Baixando'),
  validating('Validando pacote'),
  extracting('Extraindo pacote'),
  transcoding('Convertendo faixas'),
  saving('Salvando na biblioteca'),
  completed('Concluído'),
  cancelled('Cancelado'),
  failed('Falhou');

  final String label;
  const MultiTracksImportPhase(this.label);

  bool get isActive => this != completed && this != cancelled && this != failed;

  /// Até a publicação final ainda dá para cancelar sem deixar música parcial.
  bool get canCancel => isActive && this != saving;
}

@immutable
class MultiTracksImportJob {
  /// `contentId:keyId` — um único trabalho ativo por par.
  final String key;
  final String title;
  final String? keyTitle;
  final MultiTracksImportPhase phase;
  final int receivedBytes;
  final int? totalBytes;
  final int stemIndex, stemCount;
  final String? stemLabel;

  /// Fase em que a falha aconteceu e mensagem segura (sem URL, hash ou caminhos).
  final MultiTracksImportPhase? failedPhase;
  final String? message;

  /// Um aluguel foi confirmado neste trabalho: cancelar ou falhar depois disso não devolve o crédito.
  final bool rentalRedeemed;
  final Track? track;

  const MultiTracksImportJob({
    required this.key,
    required this.title,
    this.keyTitle,
    this.phase = MultiTracksImportPhase.preparing,
    this.receivedBytes = 0,
    this.totalBytes,
    this.stemIndex = 0,
    this.stemCount = 0,
    this.stemLabel,
    this.failedPhase,
    this.message,
    this.rentalRedeemed = false,
    this.track,
  });

  static String keyFor(int contentId, int keyId) => '$contentId:$keyId';

  /// Fração do download, quando o servidor informou o tamanho.
  double? get downloadFraction {
    final total = totalBytes;
    if (total == null || total <= 0) return null;
    return (receivedBytes / total).clamp(0.0, 1.0);
  }

  MultiTracksImportJob copyWith({
    MultiTracksImportPhase? phase,
    int? receivedBytes,
    Object? totalBytes = _keep,
    int? stemIndex,
    int? stemCount,
    Object? stemLabel = _keep,
    Object? failedPhase = _keep,
    Object? message = _keep,
    bool? rentalRedeemed,
    Object? track = _keep,
  }) =>
      MultiTracksImportJob(
        key: key,
        title: title,
        keyTitle: keyTitle,
        phase: phase ?? this.phase,
        receivedBytes: receivedBytes ?? this.receivedBytes,
        totalBytes: identical(totalBytes, _keep) ? this.totalBytes : totalBytes as int?,
        stemIndex: stemIndex ?? this.stemIndex,
        stemCount: stemCount ?? this.stemCount,
        stemLabel: identical(stemLabel, _keep) ? this.stemLabel : stemLabel as String?,
        failedPhase: identical(failedPhase, _keep) ? this.failedPhase : failedPhase as MultiTracksImportPhase?,
        message: identical(message, _keep) ? this.message : message as String?,
        rentalRedeemed: rentalRedeemed ?? this.rentalRedeemed,
        track: identical(track, _keep) ? this.track : track as Track?,
      );

  static const _keep = Object();
}
