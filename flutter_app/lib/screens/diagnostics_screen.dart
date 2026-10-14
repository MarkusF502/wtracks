import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../services/diagnostics_log.dart';
import '../theme/app_colors.dart';

/// Registro de diagnóstico (Playback: "Diagnostic Information" — "Device details have been copied to the clipboard").
/// Mostra as falhas de leitura/gravação e permite copiar o texto para enviar.
class DiagnosticsScreen extends ConsumerWidget {
  const DiagnosticsScreen({super.key});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final entries = ref.watch(diagnosticsProvider);
    return Scaffold(
      backgroundColor: kBg,
      appBar: AppBar(
        backgroundColor: kPanelBg,
        title: const Text('Diagnóstico'),
        actions: [
          IconButton(
            tooltip: 'Copiar registro',
            icon: const Icon(Icons.copy),
            onPressed: () async {
              await Clipboard.setData(ClipboardData(text: ref.read(diagnosticsProvider.notifier).export()));
              if (context.mounted) {
                ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Registro copiado.')));
              }
            },
          ),
        ],
      ),
      body: entries.isEmpty
          ? const Center(child: Text('Nenhum evento registrado nesta sessão.', style: TextStyle(color: kTextDim)))
          : ListView(
              children: [
                for (final e in entries.reversed)
                  ListTile(
                    dense: true,
                    leading: Icon(e.error ? Icons.error_outline : Icons.info_outline,
                        color: e.error ? Colors.redAccent : kTextDim),
                    title: Text(e.message, style: const TextStyle(color: kText)),
                    subtitle: Text(e.time.toLocal().toString().substring(0, 19), style: const TextStyle(color: kTextDim)),
                  ),
              ],
            ),
    );
  }
}
