import 'dart:io';
import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import '../providers/engine_provider.dart';
import '../theme/app_colors.dart';
import 'backup_screen.dart';
import 'diagnostics_screen.dart';
import 'guide_settings_sheet.dart';
import 'remote_screen.dart';
import '../widgets/dialog_text_controller.dart';

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
          key: const Key('diagnostics'),
          leading: const Icon(Icons.bug_report_outlined),
          title: const Text('Diagnóstico'),
          subtitle: const Text('Falhas de leitura e gravação desta sessão'),
          onTap: () => Navigator.of(context).push(MaterialPageRoute<void>(builder: (_) => const DiagnosticsScreen())),
        ),
        SwitchListTile(
          key: const Key('waveform-grid'),
          title: const Text('Grade da waveform'),
          subtitle: const Text('Linhas de compasso sobre a waveform'),
          value: settings.waveformGrid,
          onChanged: (v) => ref.read(appSettingsProvider.notifier).apply(settings.copyWith(waveformGrid: v)),
        ),
        _DirectoryTile(
          key: const Key('custom-clicks'),
          title: 'Pasta de clicks personalizados',
          help: 'Arquivos <Família>-accents/quarter/eighth/sixteenth.wav',
          value: settings.customClicksDirectory,
          onChanged: (path) => ref.read(appSettingsProvider.notifier).apply(settings.copyWith(customClicksDirectory: path)),
        ),
        _DirectoryTile(
          key: const Key('custom-guides'),
          title: 'Pasta de guias personalizadas',
          help: 'Arquivos guidecue-section|count-<idioma>-<gênero>-<nome>.wav',
          value: settings.customGuidesDirectory,
          onChanged: (path) => ref.read(appSettingsProvider.notifier).apply(settings.copyWith(customGuidesDirectory: path)),
        ),
        ListTile(
          key: const Key('backup'),
          leading: const Icon(Icons.backup_outlined),
          title: const Text('Backup e restauração'),
          subtitle: const Text('Músicas, áudios, setlists e preferências num arquivo .zip'),
          onTap: () => Navigator.of(context).push(MaterialPageRoute<void>(builder: (_) => const BackupScreen())),
        ),
        ListTile(
          leading: const Icon(Icons.settings_remote_outlined),
          title: const Text('Controle remoto'),
          subtitle: const Text('Permitir conexões remotas pela rede local'),
          onTap: () => Navigator.of(context).push(MaterialPageRoute<void>(builder: (_) => const RemoteScreen())),
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

class _DirectoryTile extends StatelessWidget {
  final String title, help;
  final String? value;
  final ValueChanged<String?> onChanged;
  const _DirectoryTile({super.key, required this.title, required this.help, required this.value, required this.onChanged});

  Future<void> _edit(BuildContext context) async {
    final result = await showDialog<(bool, String?)>(
      context: context,
      builder: (ctx) => DialogTextController(
        initialText: value ?? '',
        builder: (controller) => AlertDialog(
          backgroundColor: kPanelBg,
          title: Text(title),
          content: TextField(
            key: const Key('directory-path'),
            controller: controller,
            decoration: InputDecoration(labelText: 'Caminho da pasta', helperText: help),
          ),
          actions: [
            TextButton(onPressed: () => Navigator.pop(ctx), child: const Text('Cancelar')),
            TextButton(onPressed: () => Navigator.pop(ctx, (true, null)), child: const Text('Remover')),
            FilledButton(onPressed: () => Navigator.pop(ctx, (true, controller.text.trim())), child: const Text('Salvar')),
          ],
        ),
      ),
    );
    if (result == null || !context.mounted) return;
    final path = result.$2;
    if (path != null && path.isNotEmpty && !Directory(path).existsSync()) {
      ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Pasta não encontrada.')));
      return;
    }
    onChanged(path == null || path.isEmpty ? null : path);
  }

  @override
  Widget build(BuildContext context) => ListTile(
        leading: const Icon(Icons.folder_outlined),
        title: Text(title),
        subtitle: Text(value ?? 'Nenhuma (somente os sons do pacote)'),
        onTap: () => _edit(context),
      );
}
