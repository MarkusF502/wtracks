import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import '../models/track.dart';
import '../providers/engine_provider.dart';

/// Fim da música: transição na setlist (as seis do Playback), fade nos últimos 5 s
/// (SongArrangement.endFade) e canais que não entram no fade (excludeFromFade).
class SongEndingSheet extends ConsumerWidget {
  const SongEndingSheet({super.key});

  Future<void> _save(BuildContext context, WidgetRef ref) async {
    if (!ref.read(trackLibraryProvider).any((t) => t.id == ref.read(currentTrackProvider)?.id)) return;
    try {
      await ref.read(trackLibraryProvider.notifier).saveCurrent();
    } catch (_) {
      if (context.mounted) {
        ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Falha ao salvar a música.')));
      }
    }
  }

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final track = ref.watch(currentTrackProvider);
    if (track == null) return const SizedBox.shrink();
    final notifier = ref.read(currentTrackProvider.notifier);
    return SafeArea(
      child: SingleChildScrollView(
        child: Column(
          mainAxisSize: MainAxisSize.min,
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            const ListTile(title: Text('Fim da música', style: TextStyle(fontWeight: FontWeight.bold))),
            RadioGroup<SongTransition>(
              groupValue: track.transition,
              onChanged: (v) {
                if (v == null) return;
                notifier.setTransition(v);
                _save(context, ref);
              },
              child: Column(children: [
                for (final value in SongTransition.values)
                  RadioListTile<SongTransition>(
                    key: Key('transition-${value.name}'),
                    value: value,
                    title: Text(value.label),
                    subtitle: Text(value.description),
                  ),
              ]),
            ),
            SwitchListTile(
              key: const Key('end-fade'),
              title: const Text('Fade no final'),
              subtitle: const Text('Abaixa o volume nos últimos 5 segundos'),
              value: track.endFade,
              onChanged: (v) {
                notifier.setEndFade(v);
                _save(context, ref);
              },
            ),
            const ListTile(dense: true, title: Text('Fora do fade (continuam no volume)')),
            for (var i = 0; i < track.channels.length; i++)
              CheckboxListTile(
                key: Key('exclude-fade-$i'),
                dense: true,
                title: Text(track.channels[i].label),
                subtitle: track.channels[i].isClickOrGuide ? const Text('Click e guia nunca entram no fade') : null,
                value: track.channels[i].fadeExcluded,
                onChanged: track.channels[i].isClickOrGuide ? null : (v) {
                  notifier.setChannelExcludedFromFade(i, v ?? false);
                  _save(context, ref);
                },
              ),
          ],
        ),
      ),
    );
  }
}
