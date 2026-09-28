import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/track.dart';
import '../providers/setlist_provider.dart';
import '../theme/app_colors.dart';
import 'setlist_editor_screen.dart';

/// Lista de setlists salvos -- acessível a partir da AppBar da LibraryScreen.
class SetlistsScreen extends ConsumerWidget {
  const SetlistsScreen({super.key});

  Future<void> _openEditor(BuildContext context, String setlistId) async {
    Navigator.of(context).push(
      MaterialPageRoute(builder: (_) => SetlistEditorScreen(setlistId: setlistId)),
    );
  }

  Future<void> _createSetlist(BuildContext context, WidgetRef ref) async {
    final controller = TextEditingController();
    final name = await showDialog<String>(
      context: context,
      builder: (ctx) => AlertDialog(
        backgroundColor: kPanelBg,
        title: const Text('Novo setlist', style: TextStyle(color: kText)),
        content: TextField(
          controller: controller,
          autofocus: true,
          style: const TextStyle(color: kText),
          decoration: const InputDecoration(
            hintText: 'Nome do setlist',
            hintStyle: TextStyle(color: kTextDim),
            enabledBorder: OutlineInputBorder(borderSide: BorderSide(color: kBorder)),
            focusedBorder: OutlineInputBorder(borderSide: BorderSide(color: kAccent)),
          ),
          onSubmitted: (value) => Navigator.of(ctx).pop(value),
        ),
        actions: [
          TextButton(onPressed: () => Navigator.of(ctx).pop(), child: const Text('Cancelar')),
          FilledButton(
            onPressed: () => Navigator.of(ctx).pop(controller.text),
            child: const Text('Criar'),
          ),
        ],
      ),
    );
    controller.dispose();

    final trimmed = name?.trim();
    if (trimmed == null || trimmed.isEmpty) return;

    final setlist = await ref.read(setlistLibraryProvider.notifier).createSetlist(trimmed);
    if (!context.mounted) return;
    _openEditor(context, setlist.id);
  }

  Future<void> _deleteSetlist(BuildContext context, WidgetRef ref, Setlist setlist) async {
    final confirmed = await showDialog<bool>(
      context: context,
      builder: (ctx) => AlertDialog(
        backgroundColor: kPanelBg,
        title: const Text('Excluir setlist?', style: TextStyle(color: kText)),
        content: Text(
          'Tem certeza que deseja excluir "${setlist.name}"? Essa ação não pode ser desfeita.',
          style: const TextStyle(color: kTextDim),
        ),
        actions: [
          TextButton(onPressed: () => Navigator.of(ctx).pop(false), child: const Text('Cancelar')),
          FilledButton(
            style: FilledButton.styleFrom(backgroundColor: Colors.redAccent),
            onPressed: () => Navigator.of(ctx).pop(true),
            child: const Text('Excluir'),
          ),
        ],
      ),
    );

    if (confirmed == true) {
      await ref.read(setlistLibraryProvider.notifier).deleteSetlist(setlist.id);
    }
  }

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final setlists = ref.watch(setlistLibraryProvider);

    return Scaffold(
      backgroundColor: kBg,
      appBar: AppBar(
        backgroundColor: kPanelBg,
        title: const Text('Setlists'),
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () => _createSetlist(context, ref),
        backgroundColor: kAccent,
        foregroundColor: kBg,
        child: const Icon(Icons.add),
      ),
      body: setlists.isEmpty
          ? Center(
              child: Column(
                mainAxisSize: MainAxisSize.min,
                children: [
                  const Text('Nenhum setlist criado ainda', style: TextStyle(color: kTextDim)),
                  const SizedBox(height: 16),
                  FilledButton.icon(
                    onPressed: () => _createSetlist(context, ref),
                    icon: const Icon(Icons.add),
                    label: const Text('Criar setlist'),
                  ),
                ],
              ),
            )
          : ListView.builder(
              padding: const EdgeInsets.all(12),
              itemCount: setlists.length,
              itemBuilder: (context, index) {
                final setlist = setlists[index];
                return Card(
                  color: kPanelBg,
                  margin: const EdgeInsets.symmetric(vertical: 4),
                  shape: RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(8),
                    side: const BorderSide(color: kBorder),
                  ),
                  child: ListTile(
                    leading: const Icon(Icons.queue_music, color: kAccent),
                    title: Text(setlist.name, style: const TextStyle(color: kText)),
                    subtitle: Text('${setlist.tracks.length} músicas',
                        style: const TextStyle(color: kTextDim)),
                    trailing: IconButton(
                      icon: const Icon(Icons.delete_outline, color: kTextDim),
                      tooltip: 'Excluir',
                      onPressed: () => _deleteSetlist(context, ref, setlist),
                    ),
                    onTap: () => _openEditor(context, setlist.id),
                  ),
                );
              },
            ),
    );
  }
}
