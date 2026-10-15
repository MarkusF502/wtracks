import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../providers/audio_diagnostics_provider.dart';
import '../providers/engine_provider.dart';
import '../services/diagnostics_log.dart';
import '../theme/app_colors.dart';

/// Registro de diagnóstico (Playback: "Diagnostic Information" — "Device details have been copied to the clipboard").
/// Mostra a saúde do áudio em tempo real, as falhas de leitura/gravação e permite copiar o texto para enviar.
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
      body: ListView(
        children: [
          const RealtimeAudioSection(),
          const Divider(color: kBorder),
          if (entries.isEmpty)
            const Padding(
              padding: EdgeInsets.all(24),
              child: Center(child: Text('Nenhum evento registrado nesta sessão.', style: TextStyle(color: kTextDim))),
            )
          else
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

/// Seção "Áudio em tempo real": configuração real, carga do callback e falhas desde a medição atual.
class RealtimeAudioSection extends ConsumerWidget {
  const RealtimeAudioSection({super.key});

  /// Opções de diagnóstico (plano de otimização, 7.2); só as que o dispositivo oferece aparecem.
  static const bufferChoices = [256, 512, 1024];

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final d = ref.watch(audioDiagnosticsProvider);
    final playing = ref.watch(transportProvider.select((t) => t.isPlaying));
    final available = ref.read(engineProvider).availableBufferSizes;
    final c = d.config, s = d.stats;
    String pct(double v) => '${(v * 100).toStringAsFixed(1)}%';
    final health = d.health;
    final healthColor = switch (health) {
      AudioHealth.idle => kTextDim,
      AudioHealth.stable => kStageGreen,
      AudioHealth.deviceXruns => kStageOrange,
      AudioHealth.underruns || AudioHealth.overruns => Colors.redAccent,
    };
    Widget row(String label, String value) => Padding(
          padding: const EdgeInsets.symmetric(vertical: 2),
          child: Row(crossAxisAlignment: CrossAxisAlignment.start, children: [
            SizedBox(width: 150, child: Text(label, style: const TextStyle(color: kTextDim, fontSize: 13))),
            Expanded(child: Text(value, style: const TextStyle(color: kText, fontSize: 13))),
          ]),
        );
    return Padding(
      padding: const EdgeInsets.fromLTRB(16, 12, 16, 8),
      child: Column(crossAxisAlignment: CrossAxisAlignment.start, children: [
        const Text('Áudio em tempo real', style: TextStyle(color: kText, fontSize: 16, fontWeight: FontWeight.w600)),
        const SizedBox(height: 6),
        Text(AudioDiagnostics.healthLabel(health), key: const Key('audio-health'),
            style: TextStyle(color: healthColor, fontWeight: FontWeight.w600)),
        const SizedBox(height: 6),
        row('Dispositivo', '${c.deviceRate} Hz · buffer ${c.deviceBuffer} frames'),
        row('Preparado', '${c.preparedRate} Hz · bloco ${c.preparedBlock} · prazo ${c.deadlineMs.toStringAsFixed(2)} ms'),
        row('Pedido', '${c.requestedRate} Hz · ${c.requestedBuffer} frames'),
        row('Canais', c.channels == 0
            ? 'nenhum carregado'
            : '${c.channels} · arquivos ${c.fileRate.round()} Hz${c.resampling ? ' · resampling ×${c.resampleRatio.toStringAsFixed(4)}' : ''}'),
        const SizedBox(height: 6),
        row('Medição', d.base == null ? 'não iniciada' : 'há ${d.elapsed.inMinutes} min ${d.elapsed.inSeconds % 60} s'),
        row('Underruns', d.base == null ? '—' : '${d.underruns}'),
        row('Xruns do dispositivo', d.base == null ? '—' : d.deviceXruns < 0 ? 'não informado' : '${d.deviceXruns}'),
        row('Callbacks', '${s.callbacks} · prazo ${s.deadlineMs.toStringAsFixed(2)} ms · acima do prazo ${s.overruns}'),
        row('Carga P50/P95/P99', '${pct(s.p50Load)} / ${pct(s.p95Load)} / ${pct(s.p99Load)}'),
        row('Máximo', '${s.maxMs.toStringAsFixed(2)} ms (${pct(s.maxLoad)})'),
        const SizedBox(height: 8),
        Wrap(spacing: 8, runSpacing: 8, children: [
          FilledButton.tonal(
            onPressed: () => ref.read(audioDiagnosticsProvider.notifier).startMeasurement(),
            child: const Text('Iniciar nova medição'),
          ),
          OutlinedButton(
            onPressed: () async {
              final text = ref.read(audioDiagnosticsProvider).export();
              debugPrint(text.split('\n').map((l) => 'WTRACKS_AUDIO_DIAG $l').join('\n'));
              await Clipboard.setData(ClipboardData(text: text));
              if (context.mounted) {
                ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Diagnóstico copiado.')));
              }
            },
            child: const Text('Copiar diagnóstico'),
          ),
        ]),
        const SizedBox(height: 12),
        const Text('Buffer do dispositivo', style: TextStyle(color: kText, fontWeight: FontWeight.w600)),
        Text(playing
            ? 'Pare a reprodução para trocar o buffer.'
            : 'Buffer maior tolera mais atraso do sistema, ao custo de latência nos controles ao vivo.',
            style: const TextStyle(color: kTextDim, fontSize: 12)),
        const SizedBox(height: 4),
        Wrap(spacing: 8, children: [
          for (final frames in bufferChoices)
            if (available.isEmpty || available.contains(frames))
              ChoiceChip(
                key: Key('buffer-$frames'),
                label: Text(c.deviceRate > 0 ? '$frames (${(1000 * frames / c.deviceRate).toStringAsFixed(1)} ms)' : '$frames'),
                selected: c.deviceBuffer == frames,
                onSelected: playing
                    ? null
                    : (_) {
                        final ok = ref.read(audioDiagnosticsProvider.notifier).setBufferSize(frames);
                        if (!ok) {
                          ScaffoldMessenger.of(context)
                              .showSnackBar(const SnackBar(content: Text('O dispositivo não aceitou esse buffer.')));
                        }
                      },
              ),
        ]),
      ]),
    );
  }
}
