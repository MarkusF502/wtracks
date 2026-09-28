import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/track.dart';
import '../providers/engine_provider.dart';
import '../services/track_navigation.dart';
import 'import_screen.dart';
import 'performance_screen.dart';
import 'setlists_screen.dart';

const _bg = Color(0xFF07070E);
const _panelBg = Color(0xFF111119);
const _border = Color(0xFF1E1E2E);
const _textDim = Color(0xFF8888A8);
const _accent = Color(0xFF00E5FF);

/// Tela inicial do app: lista as músicas salvas em disco (via
/// [trackLibraryProvider]) e permite reabrir uma delas ou importar uma
/// música nova.
class LibraryScreen extends ConsumerWidget {
  const LibraryScreen({super.key});

  Future<void> _renameTrack(BuildContext context, WidgetRef ref, Track track) async {
    final controller = TextEditingController(text: track.title);
    final newTitle = await showDialog<String>(
      context: context,
      builder: (ctx) => AlertDialog(
        backgroundColor: _panelBg,
        title: const Text('Renomear música', style: TextStyle(color: Color(0xFFF0F0FA))),
        content: TextField(
          controller: controller,
          autofocus: true,
          style: const TextStyle(color: Color(0xFFF0F0FA)),
          decoration: const InputDecoration(
            enabledBorder: OutlineInputBorder(borderSide: BorderSide(color: _border)),
            focusedBorder: OutlineInputBorder(borderSide: BorderSide(color: _accent)),
          ),
          onSubmitted: (value) => Navigator.of(ctx).pop(value),
        ),
        actions: [
          TextButton(onPressed: () => Navigator.of(ctx).pop(), child: const Text('Cancelar')),
          FilledButton(
            onPressed: () => Navigator.of(ctx).pop(controller.text),
            child: const Text('Salvar'),
          ),
        ],
      ),
    );
    controller.dispose();

    final trimmed = newTitle?.trim();
    if (trimmed == null || trimmed.isEmpty || trimmed == track.title) return;

    try {
      await ref.read(trackLibraryProvider.notifier).renameTrack(track.id, trimmed);
    } catch (e) {
      if (!context.mounted) return;
      ScaffoldMessenger.of(context)
          .showSnackBar(SnackBar(content: Text('Falha ao renomear: $e')));
    }
  }

  Future<void> _goImport(BuildContext context, WidgetRef ref) async {
    final track = await Navigator.of(context)
        .push<Track>(MaterialPageRoute(builder: (_) => const ImportScreen()));
    if (track != null) {
      // O ImportScreen já deixou a track carregada no engine ao voltar
      // (mesmo fluxo de antes) -- só refletimos isso navegando pra
      // performance e deixando o usuário decidir se quer salvar.
      if (!context.mounted) return;
      Navigator.of(context).push(MaterialPageRoute(builder: (_) => const PerformanceScreen()));
    }
  }

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final tracks = ref.watch(trackLibraryProvider);

    return Scaffold(
      backgroundColor: _bg,
      appBar: AppBar(
        backgroundColor: _panelBg,
        title: const Text('WTracks'),
        actions: [
          IconButton(
            icon: const Icon(Icons.queue_music),
            tooltip: 'Setlists',
            onPressed: () => Navigator.of(context)
                .push(MaterialPageRoute(builder: (_) => const SetlistsScreen())),
          ),
        ],
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () => _goImport(context, ref),
        backgroundColor: _accent,
        foregroundColor: _bg,
        child: const Icon(Icons.add),
      ),
      body: tracks.isEmpty
          ? Center(
              child: Column(
                mainAxisSize: MainAxisSize.min,
                children: [
                  const Text('Nenhuma música salva ainda.', style: TextStyle(color: _textDim)),
                  const SizedBox(height: 16),
                  FilledButton.icon(
                    onPressed: () => _goImport(context, ref),
                    icon: const Icon(Icons.folder_open),
                    label: const Text('Importar música'),
                  ),
                ],
              ),
            )
          : ListView.builder(
              padding: const EdgeInsets.all(12),
              itemCount: tracks.length,
              itemBuilder: (context, index) {
                final track = tracks[index];
                return Card(
                  color: _panelBg,
                  margin: const EdgeInsets.symmetric(vertical: 4),
                  shape: RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(8),
                    side: const BorderSide(color: _border),
                  ),
                  child: ListTile(
                    leading: const Icon(Icons.graphic_eq, color: _accent),
                    title: Text(track.title, style: const TextStyle(color: Color(0xFFF0F0FA))),
                    subtitle: Text('${track.channels.length} canais',
                        style: const TextStyle(color: _textDim)),
                    trailing: IconButton(
                      icon: const Icon(Icons.edit_outlined, color: _textDim),
                      tooltip: 'Renomear',
                      onPressed: () => _renameTrack(context, ref, track),
                    ),
                    onTap: () => openTrack(context, ref, track),
                    onLongPress: () => _renameTrack(context, ref, track),
                  ),
                );
              },
            ),
    );
  }
}
