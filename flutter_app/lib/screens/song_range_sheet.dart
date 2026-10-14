import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import '../providers/engine_provider.dart';

/// Início e fim da música (Playback SongArrangement.storedStartTime / storedEndTime; toque no relógio). O play e o RTZ
/// começam no início; ao chegar no fim a música termina e o fade de fim conta a partir dele. Os valores se gravam sozinhos
/// com a música (salvamento automático).
class SongRangeSheet extends ConsumerWidget {
  const SongRangeSheet({super.key});

  static String format(double seconds) {
    final t = seconds.isFinite ? (seconds * 10).round() / 10 : 0.0;
    final m = t ~/ 60;
    final s = t - m * 60;
    return '$m:${s.toStringAsFixed(1).padLeft(4, '0')}';
  }

  void _apply(BuildContext context, WidgetRef ref, double? start, double? end) {
    if (!ref.read(currentTrackProvider.notifier).setSongRange(start, end) && context.mounted) {
      ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('O fim precisa ser depois do início.')));
    }
  }

  Widget _limit({required String rowKey, required String title, required String value, required VoidCallback onHere, required VoidCallback? onClear}) {
    return Column(crossAxisAlignment: CrossAxisAlignment.start, children: [
      ListTile(key: Key(rowKey), title: Text(title), subtitle: Text(value)),
      Padding(
        padding: const EdgeInsets.symmetric(horizontal: 16),
        child: Wrap(spacing: 8, children: [
          OutlinedButton(key: Key('$rowKey-here'), onPressed: onHere, child: const Text('Usar a posição atual')),
          TextButton(key: Key('$rowKey-clear'), onPressed: onClear, child: const Text('Padrão')),
        ]),
      ),
    ]);
  }

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final track = ref.watch(currentTrackProvider);
    if (track == null) return const SizedBox.shrink();
    final length = ref.watch(transportProvider.select((t) => t.lengthSeconds));
    final start = track.startSeconds, end = track.endSeconds;
    double here() => ref.read(transportProvider).positionSeconds;
    return SafeArea(
      child: SingleChildScrollView(
        child: Column(
          mainAxisSize: MainAxisSize.min,
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            const ListTile(
              title: Text('Início e fim da música', style: TextStyle(fontWeight: FontWeight.bold)),
              subtitle: Text('Tocar e voltar ao início começam no início; no fim a música termina.'),
            ),
            _limit(
              rowKey: 'range-start', title: 'Início', value: start == null ? 'Começo do arquivo' : format(start),
              onHere: () => _apply(context, ref, here(), end), onClear: start == null ? null : () => _apply(context, ref, null, end),
            ),
            _limit(
              rowKey: 'range-end', title: 'Fim', value: end == null ? 'Fim do arquivo (${format(length)})' : format(end),
              onHere: () => _apply(context, ref, start, here()), onClear: end == null ? null : () => _apply(context, ref, start, null),
            ),
          ],
        ),
      ),
    );
  }
}
