import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/track.dart';
import '../widgets/dialog_text_controller.dart';
import '../providers/engine_provider.dart';
import '../providers/setlist_provider.dart';
import '../services/track_navigation.dart';
import '../theme/app_colors.dart';
import 'track_picker_screen.dart';

/// Cor consistente por tom musical -- mesma ideia do KEY_COLORS do protótipo
/// React, mapa fixo tom→cor, com fallback pra [kTextDim] se o tom não
/// estiver mapeado.
const Map<String, Color> _keyColors = {
  'C': Color(0xFFFF6B6B),
  'C#': Color(0xFFFF922B),
  'Db': Color(0xFFFF922B),
  'D': Color(0xFFFFD43B),
  'D#': Color(0xFFA9E34B),
  'Eb': Color(0xFFA9E34B),
  'E': Color(0xFF69DB7C),
  'F': Color(0xFF38D9A9),
  'F#': Color(0xFF3BC9DB),
  'Gb': Color(0xFF3BC9DB),
  'G': Color(0xFF4DABF7),
  'G#': Color(0xFF748FFC),
  'Ab': Color(0xFF748FFC),
  'A': Color(0xFF9775FA),
  'A#': Color(0xFFDA77F2),
  'Bb': Color(0xFFDA77F2),
  'B': Color(0xFFF783AC),
};

/// Tela de edição de um setlist específico: lista reordenável de músicas,
/// adicionar/remover, renomear. Equivalente ao protótipo `SetlistScreen.tsx`.
class SetlistEditorScreen extends ConsumerStatefulWidget {
  final String setlistId;

  const SetlistEditorScreen({super.key, required this.setlistId});

  @override
  ConsumerState<SetlistEditorScreen> createState() => _SetlistEditorScreenState();
}

class _SetlistEditorScreenState extends ConsumerState<SetlistEditorScreen> {
  @override
  void initState() {
    super.initState();
    Future.microtask(() {
      if (mounted) ref.read(setlistEditorProvider.notifier).open(widget.setlistId);
    });
  }

  Future<void> _rename(Setlist setlist) async {
    final newName = await showDialog<String>(
      context: context,
      builder: (ctx) => DialogTextController(
        initialText: setlist.name,
        builder: (controller) => AlertDialog(
          backgroundColor: kPanelBg,
          title: const Text('Renomear setlist', style: TextStyle(color: kText)),
          content: TextField(
            controller: controller,
            autofocus: true,
            style: const TextStyle(color: kText),
            decoration: const InputDecoration(
              enabledBorder: OutlineInputBorder(borderSide: BorderSide(color: kBorder)),
              focusedBorder: OutlineInputBorder(borderSide: BorderSide(color: kAccent)),
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
      ),
    );
    if (!mounted) return;

    final trimmed = newName?.trim();
    if (trimmed == null || trimmed.isEmpty || trimmed == setlist.name) return;

    await ref.read(setlistEditorProvider.notifier).rename(trimmed);
  }

  Future<void> _addTracks(Setlist setlist) async {
    final currentIds = setlist.tracks.map((t) => t.id).toSet();
    final selected = await Navigator.of(context).push<List<Track>>(
      MaterialPageRoute(
        builder: (_) => TrackPickerScreen(initiallySelectedIds: currentIds),
      ),
    );
    if (!mounted || selected == null || selected.isEmpty) return;
    await ref.read(setlistEditorProvider.notifier).addTracks(selected);
  }

  @override
  Widget build(BuildContext context) {
    final setlist = ref.watch(setlistEditorProvider);

    // Mantém o Scaffold/AppBar com a MESMA forma estrutural em ambos os
    // estados (carregando vs. carregado) -- trocar pra um Scaffold sem
    // appBar enquanto a rota ainda está em transição de entrada (o open()
    // do provider resolve quase instantaneamente, no meio da animação de
    // push) faz o Overlay reconciliar uma árvore de elementos muito
    // diferente no meio da transição, o que dispara
    // "'_children.contains(child)': is not true" no framework. Com a
    // estrutura estável, só o conteúdo (title/actions/bottom/body) muda.
    return Scaffold(
      backgroundColor: kBg,
      appBar: AppBar(
        backgroundColor: kPanelBg,
        title: setlist == null
            ? const Text('Setlist')
            : GestureDetector(
                onTap: () => _rename(setlist),
                child: Row(
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    Flexible(child: Text(setlist.name, overflow: TextOverflow.ellipsis)),
                    const SizedBox(width: 6),
                    const Icon(Icons.edit_outlined, size: 16, color: kTextDim),
                  ],
                ),
              ),
        actions: setlist == null
            ? null
            : [
                IconButton(
                  icon: const Icon(Icons.add),
                  tooltip: 'Adicionar Música',
                  onPressed: () => _addTracks(setlist),
                ),
              ],
        bottom: setlist == null
            ? null
            : PreferredSize(
                preferredSize: const Size.fromHeight(24),
                child: Padding(
                  padding: const EdgeInsets.only(bottom: 6),
                  child: Text('${setlist.tracks.length} músicas',
                      style: const TextStyle(color: kTextDim, fontSize: 12)),
                ),
              ),
      ),
      body: setlist == null
          ? const Center(child: CircularProgressIndicator(color: kAccent))
          : setlist.tracks.isEmpty
          ? Center(
              child: Column(
                mainAxisSize: MainAxisSize.min,
                children: [
                  const Text('Nenhuma música neste setlist ainda',
                      style: TextStyle(color: kTextDim)),
                  const SizedBox(height: 16),
                  FilledButton.icon(
                    onPressed: () => _addTracks(setlist),
                    icon: const Icon(Icons.add),
                    label: const Text('Adicionar Música'),
                  ),
                ],
              ),
            )
          : LayoutBuilder(
              builder: (context, constraints) {
                final isLandscape = constraints.maxWidth > constraints.maxHeight;
                return ReorderableListView.builder(
                  padding: const EdgeInsets.all(12),
                  itemCount: setlist.tracks.length,
                  onReorderItem: (oldIndex, newIndex) {
                    ref.read(setlistEditorProvider.notifier).reorder(oldIndex, newIndex > oldIndex ? newIndex + 1 : newIndex);
                  },
                  itemBuilder: (context, index) {
                    final track = setlist.tracks[index];
                    return _SongRow(
                      key: ValueKey(track.id),
                      index: index,
                      track: track,
                      isLandscape: isLandscape,
                      onTap: () => openTrack(context, ref, track, setlist: setlist, index: index),
                      onTransition: () => ref.read(trackLibraryProvider.notifier).setTransition(track.id,
                          SongTransition.values[(track.transition.index + 1) % SongTransition.values.length]),
                      onRemove: () =>
                          ref.read(setlistEditorProvider.notifier).removeTrack(track.id),
                    );
                  },
                );
              },
            ),
    );
  }
}

class _SongRow extends StatelessWidget {
  final int index;
  final Track track;
  final bool isLandscape;
  final VoidCallback onTap;
  final VoidCallback onRemove;
  final VoidCallback onTransition;

  const _SongRow({
    required super.key,
    required this.index,
    required this.track,
    required this.isLandscape,
    required this.onTap,
    required this.onRemove,
    required this.onTransition,
  });

  @override
  Widget build(BuildContext context) {
    final keyChip = track.key != null ? _chip(track.key!, _keyColors[track.key] ?? kTextDim) : null;
    final bpmChip = _chip('${track.clickSettings.bpm.round()} BPM', kAccent);
    final channelsChip = _chip('${track.channels.length} canais', kTextDim);

    return Card(
      key: key,
      color: kPanelBg,
      margin: const EdgeInsets.symmetric(vertical: 4),
      shape: RoundedRectangleBorder(
        borderRadius: BorderRadius.circular(8),
        side: const BorderSide(color: kBorder),
      ),
      child: ListTile(
        onTap: onTap,
        leading: CircleAvatar(
          backgroundColor: kBg,
          child: Text('${index + 1}', style: const TextStyle(color: kTextDim)),
        ),
        title: Text(track.title, style: const TextStyle(color: kText)),
        subtitle: isLandscape
            ? Row(
                children: [
                  if (track.artist != null) ...[
                    Text(track.artist!, style: const TextStyle(color: kTextDim)),
                    const SizedBox(width: 12),
                  ],
                  if (keyChip != null) ...[keyChip, const SizedBox(width: 6)],
                  bpmChip,
                  const SizedBox(width: 6),
                  channelsChip,
                ],
              )
            : Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  if (track.artist != null)
                    Text(track.artist!, style: const TextStyle(color: kTextDim)),
                  const SizedBox(height: 4),
                  Wrap(
                    spacing: 6,
                    children: [
                      ?keyChip,
                      bpmChip,
                      channelsChip,
                    ],
                  ),
                ],
              ),
        trailing: Row(
          mainAxisSize: MainAxisSize.min,
          children: [
            IconButton(
              icon: Icon(track.transition.icon, color: kTextDim),
              tooltip: 'Ao terminar: ${track.transition.label.toLowerCase()} (toque para trocar)',
              onPressed: onTransition,
            ),
            IconButton(
              icon: const Icon(Icons.remove_circle_outline, color: kTextDim),
              tooltip: 'Remover do setlist',
              onPressed: onRemove,
            ),
            const Icon(Icons.drag_handle, color: kTextDim),
          ],
        ),
      ),
    );
  }

  Widget _chip(String label, Color color) => Container(
        padding: const EdgeInsets.symmetric(horizontal: 8, vertical: 2),
        decoration: BoxDecoration(
          color: color.withValues(alpha: 0.15),
          borderRadius: BorderRadius.circular(4),
          border: Border.all(color: color),
        ),
        child: Text(label, style: TextStyle(color: color, fontSize: 12)),
      );
}
