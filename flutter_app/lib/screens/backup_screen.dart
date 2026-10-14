import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../providers/backup_provider.dart';
import '../theme/app_colors.dart';

/// Backup completo e restauração. Faça um backup antes de atualizar o app por cima de uma versão assinada com outra chave,
/// de trocar de aparelho ou de reinstalar: o zip tem as músicas, os áudios, as setlists e as preferências.
class BackupScreen extends ConsumerWidget {
  const BackupScreen({super.key});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final state = ref.watch(backupProvider);
    final notifier = ref.read(backupProvider.notifier);
    ref.listen(backupProvider.select((s) => s.pendingSummary), (_, summary) {
      if (summary == null) return;
      showDialog<void>(
        context: context,
        barrierDismissible: false,
        builder: (ctx) => AlertDialog(
          backgroundColor: kPanelBg,
          title: const Text('Restaurar este backup?'),
          content: Text(
            'O backup (conferido) tem ${BackupNotifier.describe(summary)}, criado em ${summary.createdAt.toLocal().toString().split('.').first}.\n\n'
            'A biblioteca atual será substituída. Os dados de agora ficam guardados numa pasta ao lado até você apagá-la.',
          ),
          actions: [
            TextButton(
              key: const Key('restore-cancel'),
              onPressed: () {
                Navigator.pop(ctx);
                notifier.cancelPending();
              },
              child: const Text('Cancelar'),
            ),
            FilledButton(
              key: const Key('restore-confirm'),
              onPressed: () {
                Navigator.pop(ctx);
                notifier.confirmRestore();
              },
              child: const Text('Restaurar'),
            ),
          ],
        ),
      );
    });
    return Scaffold(
      backgroundColor: kBg,
      appBar: AppBar(backgroundColor: kPanelBg, title: const Text('Backup e restauração')),
      body: ListView(padding: const EdgeInsets.all(16), children: [
        const Text(
          'O backup guarda as músicas, os áudios, as setlists e as preferências num arquivo .zip, conferido por hash antes de ser '
          'entregue. Faça um backup antes de atualizar o app por cima de uma versão assinada com outra chave, de trocar de aparelho '
          'ou de reinstalar.',
        ),
        const SizedBox(height: 16),
        FilledButton.icon(
          key: const Key('backup-create'),
          onPressed: state.busy ? null : notifier.create,
          icon: const Icon(Icons.save_alt),
          label: const Text('Criar backup…'),
        ),
        const SizedBox(height: 8),
        OutlinedButton.icon(
          key: const Key('backup-restore'),
          onPressed: state.busy ? null : notifier.choose,
          icon: const Icon(Icons.settings_backup_restore),
          label: const Text('Restaurar de um backup…'),
        ),
        const SizedBox(height: 16),
        if (state.busy) LinearProgressIndicator(value: state.progress > 0 && state.progress < 1 ? state.progress : null),
        if (state.message != null)
          Padding(
            padding: const EdgeInsets.only(top: 12),
            child: Text(state.message!, key: const Key('backup-message'), style: TextStyle(color: state.error ? kStageRed : null)),
          ),
      ]),
    );
  }
}
