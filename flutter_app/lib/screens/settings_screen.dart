import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import '../providers/engine_provider.dart';
import '../theme/app_colors.dart';
import 'guide_settings_sheet.dart';

/// Configurações do app.
class SettingsScreen extends ConsumerWidget {
  const SettingsScreen({super.key});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final settings = ref.watch(appSettingsProvider);
    return Scaffold(
      backgroundColor: kBg,
      appBar: AppBar(backgroundColor: kPanelBg, title: const Text('Configurações')),
      body: ListView(children: [
        SwitchListTile(
          key: const Key('fader-default-80'),
          title: const Text('Nível padrão dos faders em 80%'),
          subtitle: const Text('Músicas importadas começam com os canais em 80%'),
          value: settings.faderDefault80,
          onChanged: (v) => ref.read(appSettingsProvider.notifier).apply(settings.copyWith(faderDefault80: v)),
        ),
        SwitchListTile(
          key: const Key('stereo-split'),
          title: const Text('Enviar click e guia para a esquerda e faixas para a direita'),
          subtitle: const Text('Somente saída estéreo'),
          value: settings.stereoSplit,
          onChanged: (v) => ref.read(appSettingsProvider.notifier).apply(settings.copyWith(stereoSplit: v)),
        ),
        ListTile(
          leading: const Icon(Icons.record_voice_over_outlined),
          title: const Text('Guias'),
          subtitle: const Text('Idioma, voz, contagem e pré-roll'),
          onTap: () => showModalBottomSheet<void>(
              context: context, backgroundColor: kPanelBg, isScrollControlled: true, builder: (_) => const GuideSettingsSheet()),
        ),
      ]),
    );
  }
}
