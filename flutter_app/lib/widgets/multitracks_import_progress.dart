import 'package:flutter/material.dart';

import '../models/multitracks_import_job.dart';
import '../services/multitracks_import_coordinator.dart' show formatBytes;
import '../theme/app_colors.dart';

/// Etapas mostradas na lista; as de Rental aparecem dentro de "Obtendo autorização".
const _steps = [
  MultiTracksImportPhase.preparing,
  MultiTracksImportPhase.requestingDownloadLink,
  MultiTracksImportPhase.downloading,
  MultiTracksImportPhase.validating,
  MultiTracksImportPhase.extracting,
  MultiTracksImportPhase.transcoding,
  MultiTracksImportPhase.saving,
  MultiTracksImportPhase.completed,
];

int _stepIndex(MultiTracksImportPhase phase) => switch (phase) {
      MultiTracksImportPhase.awaitingRentalConfirmation || MultiTracksImportPhase.redeemingRental => 1,
      final other => _steps.indexOf(other),
    };

/// Progresso de um trabalho de importação MultiTracks. O estado vem do provider, então sobrevive à reconstrução da tela.
class MultiTracksImportProgress extends StatelessWidget {
  final MultiTracksImportJob job;
  final VoidCallback onCancel, onRetry, onDismiss;
  final VoidCallback? onOpen, onAddToSetlist;
  final String openLabel;

  const MultiTracksImportProgress({
    super.key,
    required this.job,
    required this.onCancel,
    required this.onRetry,
    required this.onDismiss,
    this.onOpen,
    this.onAddToSetlist,
    this.openLabel = 'Abrir música',
  });

  @override
  Widget build(BuildContext context) {
    final phase = job.phase;
    final failed = phase == MultiTracksImportPhase.failed;
    final reached = _stepIndex(failed ? (job.failedPhase ?? MultiTracksImportPhase.preparing) : phase);

    return Container(
      key: const Key('multitracks-import-progress'),
      padding: const EdgeInsets.all(16),
      decoration: BoxDecoration(
        color: kPanelBg,
        borderRadius: BorderRadius.circular(10),
        border: Border.all(color: failed ? Colors.redAccent.withValues(alpha: 0.6) : kBorder),
      ),
      child: Column(crossAxisAlignment: CrossAxisAlignment.stretch, mainAxisSize: MainAxisSize.min, children: [
        Semantics(
          liveRegion: true,
          child: Text(_headline(), style: const TextStyle(color: kText, fontSize: 16, fontWeight: FontWeight.w600)),
        ),
        if (_detail() case final detail?) ...[
          const SizedBox(height: 4),
          Text(detail, style: const TextStyle(color: kTextDim)),
        ],
        if (phase.isActive) ...[
          const SizedBox(height: 10),
          LinearProgressIndicator(value: _fraction(), color: kAccent, backgroundColor: kBorder, minHeight: 6),
        ],
        const SizedBox(height: 12),
        Wrap(spacing: 6, runSpacing: 6, children: [
          for (var i = 0; i < _steps.length; i++)
            _StepChip(
              label: _steps[i].label,
              state: failed && i == reached
                  ? _StepState.failed
                  : (i < reached || phase == MultiTracksImportPhase.completed)
                      ? _StepState.done
                      : (i == reached && phase.isActive ? _StepState.current : _StepState.pending),
            ),
        ]),
        if (job.message != null && !failed) ...[
          const SizedBox(height: 10),
          Text(job.message!, style: const TextStyle(color: kTextDim)),
        ],
        const SizedBox(height: 12),
        Wrap(alignment: WrapAlignment.end, spacing: 8, runSpacing: 8, children: _actions()),
      ]),
    );
  }

  String _headline() => switch (job.phase) {
        MultiTracksImportPhase.completed => 'Pronta na biblioteca do WTracks',
        MultiTracksImportPhase.failed => 'Falhou em: ${(job.failedPhase ?? MultiTracksImportPhase.preparing).label}',
        MultiTracksImportPhase.cancelled => 'Importação cancelada',
        MultiTracksImportPhase.transcoding when job.stemCount > 0 =>
          'Convertendo faixa ${job.stemIndex + 1} de ${job.stemCount}',
        final phase => phase.label,
      };

  String? _detail() => switch (job.phase) {
        MultiTracksImportPhase.failed => job.message,
        MultiTracksImportPhase.downloading => _bytes(),
        MultiTracksImportPhase.transcoding => job.stemLabel,
        MultiTracksImportPhase.awaitingRentalConfirmation => 'Confirme o aluguel para continuar.',
        MultiTracksImportPhase.completed => job.track == null ? null : '${job.track!.title} · ${job.track!.channels.length} faixas',
        _ => null,
      };

  String? _bytes() {
    if (job.receivedBytes <= 0) return null;
    final total = job.totalBytes;
    if (total == null || total <= 0) return formatBytes(job.receivedBytes);
    return '${formatBytes(job.receivedBytes)} de ${formatBytes(total)} (${(job.downloadFraction! * 100).floor()}%)';
  }

  double? _fraction() => switch (job.phase) {
        MultiTracksImportPhase.downloading => job.downloadFraction,
        MultiTracksImportPhase.transcoding when job.stemCount > 0 => job.stemIndex / job.stemCount,
        _ => null,
      };

  List<Widget> _actions() => switch (job.phase) {
        MultiTracksImportPhase.completed => [
            TextButton(onPressed: onDismiss, child: const Text('Fechar')),
            if (onAddToSetlist != null)
              OutlinedButton(onPressed: onAddToSetlist, child: const Text('Adicionar à setlist atual')),
            if (onOpen != null)
              FilledButton.icon(
                key: const Key('multitracks-open-imported'),
                onPressed: onOpen,
                icon: const Icon(Icons.play_arrow),
                label: Text(openLabel),
              ),
          ],
        MultiTracksImportPhase.failed || MultiTracksImportPhase.cancelled => [
            TextButton(onPressed: onDismiss, child: const Text('Fechar')),
            FilledButton(key: const Key('multitracks-retry'), onPressed: onRetry, child: const Text('Tentar novamente')),
          ],
        final phase when phase.canCancel => [
            if (job.rentalRedeemed)
              const Padding(
                padding: EdgeInsets.only(top: 10),
                child: Text('O crédito de aluguel já confirmado não volta ao cancelar.', style: TextStyle(color: kTextDim, fontSize: 12)),
              ),
            OutlinedButton.icon(
              key: const Key('multitracks-cancel-import'),
              onPressed: onCancel,
              icon: const Icon(Icons.close),
              label: const Text('Cancelar'),
            ),
          ],
        _ => const [],
      };
}

enum _StepState { pending, current, done, failed }

class _StepChip extends StatelessWidget {
  final String label;
  final _StepState state;
  const _StepChip({required this.label, required this.state});

  @override
  Widget build(BuildContext context) {
    final (icon, color) = switch (state) {
      _StepState.done => (Icons.check_circle, kAccent),
      _StepState.current => (Icons.timelapse, kText),
      _StepState.failed => (Icons.error, Colors.redAccent),
      _StepState.pending => (Icons.radio_button_unchecked, kTextDim),
    };
    return Semantics(
      label: '$label: ${switch (state) {
        _StepState.done => 'concluído',
        _StepState.current => 'em andamento',
        _StepState.failed => 'falhou',
        _StepState.pending => 'pendente',
      }}',
      excludeSemantics: true,
      child: Row(mainAxisSize: MainAxisSize.min, children: [
        Icon(icon, size: 14, color: color),
        const SizedBox(width: 4),
        Text(label, style: TextStyle(color: color, fontSize: 12)),
      ]),
    );
  }
}
