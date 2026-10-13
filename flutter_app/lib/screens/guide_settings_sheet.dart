import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import '../models/guide_settings.dart';
import '../providers/engine_provider.dart';
import '../services/dynamic_guides.dart';

/// Preferências de guia do app (Playback: "Guide Cue Language", "Count Into Each Section", "Song Section Pre-roll").
class GuideSettingsSheet extends ConsumerStatefulWidget {
  const GuideSettingsSheet({super.key});
  @override
  ConsumerState<GuideSettingsSheet> createState() => _GuideSettingsSheetState();
}

class _GuideSettingsSheetState extends ConsumerState<GuideSettingsSheet> {
  bool _busy = false;

  Future<void> _apply(GuideSettings settings) async {
    if (_busy) return;
    setState(() => _busy = true);
    try {
      final ok = await ref.read(guideSettingsProvider.notifier).apply(settings);
      if (!ok && mounted && ref.read(currentTrackProvider) != null) {
        ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Não foi possível preparar as guias.')));
      }
    } finally {
      if (mounted) setState(() => _busy = false);
    }
  }

  @override
  Widget build(BuildContext context) {
    final settings = ref.watch(guideSettingsProvider);
    final voices = ref.watch(guideCatalogProvider).asData?.value.voices ?? const <GuideVoice>[];
    final languages = {for (final v in voices) v.language}.toList()..sort();
    final genders = [for (final v in voices) if (v.language == settings.language) v.gender];
    String genderLabel(String g) => g == 'male' ? 'Masculina' : 'Feminina';
    return SafeArea(
      child: SingleChildScrollView(
        padding: const EdgeInsets.only(bottom: 16),
        child: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            const ListTile(title: Text('Guias', style: TextStyle(fontWeight: FontWeight.bold))),
            SwitchListTile(
              key: const Key('guide-dynamic'),
              title: const Text('Guias das seções'),
              subtitle: const Text('Fala o nome e a contagem antes de cada seção'),
              value: settings.dynamicEnabled,
              onChanged: _busy ? null : (v) => _apply(settings.copyWith(dynamicEnabled: v)),
            ),
            ListTile(
              title: const Text('Idioma da guia'),
              trailing: DropdownButton<String>(
                key: const Key('guide-language'),
                value: languages.contains(settings.language) ? settings.language : null,
                hint: Text(settings.language),
                items: [for (final l in languages) DropdownMenuItem(value: l, child: Text(guideLanguageNames[l] ?? l))],
                onChanged: _busy
                    ? null
                    : (l) {
                        if (l == null) return;
                        final available = [for (final v in voices) if (v.language == l) v.gender];
                        final gender = available.contains(settings.gender) ? settings.gender : available.first;
                        _apply(settings.copyWith(language: l, gender: gender));
                      },
              ),
            ),
            ListTile(
              title: const Text('Voz'),
              trailing: DropdownButton<String>(
                key: const Key('guide-gender'),
                value: genders.contains(settings.gender) ? settings.gender : null,
                hint: Text(genderLabel(settings.gender)),
                items: [for (final g in genders) DropdownMenuItem(value: g, child: Text(genderLabel(g)))],
                onChanged: _busy || genders.length < 2 ? null : (g) => g == null ? null : _apply(settings.copyWith(gender: g)),
              ),
            ),
            SwitchListTile(
              key: const Key('guide-count-each'),
              title: const Text('Contar ao entrar em cada seção'),
              subtitle: const Text('Adiciona uma contagem falada antes de todas as seções'),
              value: settings.countIntoEachSection,
              onChanged: _busy ? null : (v) => _apply(settings.copyWith(countIntoEachSection: v)),
            ),
            SwitchListTile(
              key: const Key('guide-preroll'),
              title: const Text('Pré-roll de seção'),
              subtitle: const Text('Conta um compasso antes de tocar a partir do início de uma seção'),
              value: settings.sectionPreroll,
              onChanged: _busy ? null : (v) => _apply(settings.copyWith(sectionPreroll: v)),
            ),
          ],
        ),
      ),
    );
  }
}
