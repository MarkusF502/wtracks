import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/track.dart';
import '../providers/engine_provider.dart';
import '../theme/app_colors.dart';

/// Seletor de músicas da Biblioteca com multi-seleção, usado pelo botão
/// "Adicionar Música" da SetlistEditorScreen. Tracks já presentes no setlist
/// atual aparecem pré-marcadas (equivalente a "não adicionar de novo", e
/// permite desmarcar sem precisar desabilitar o item).
class TrackPickerScreen extends ConsumerStatefulWidget {
  final Set<String> initiallySelectedIds;

  const TrackPickerScreen({super.key, required this.initiallySelectedIds});

  @override
  ConsumerState<TrackPickerScreen> createState() => _TrackPickerScreenState();
}

class _TrackPickerScreenState extends ConsumerState<TrackPickerScreen> {
  late final Set<String> _selectedIds;

  @override
  void initState() {
    super.initState();
    _selectedIds = {...widget.initiallySelectedIds};
  }

  void _confirm(List<Track> tracks) {
    final selected = tracks.where((t) => _selectedIds.contains(t.id)).toList();
    Navigator.of(context).pop(selected);
  }

  @override
  Widget build(BuildContext context) {
    final tracks = ref.watch(trackLibraryProvider);

    return Scaffold(
      backgroundColor: kBg,
      appBar: AppBar(
        backgroundColor: kPanelBg,
        title: const Text('Adicionar Música'),
        actions: [
          TextButton(
            onPressed: () => _confirm(tracks),
            child: const Text('Adicionar', style: TextStyle(color: kAccent)),
          ),
        ],
      ),
      body: tracks.isEmpty
          ? const Center(
              child: Padding(
                padding: EdgeInsets.all(24),
                child: Text(
                  'Nenhuma música na biblioteca ainda -- importe uma música primeiro',
                  style: TextStyle(color: kTextDim),
                  textAlign: TextAlign.center,
                ),
              ),
            )
          : ListView.builder(
              padding: const EdgeInsets.all(12),
              itemCount: tracks.length,
              itemBuilder: (context, index) {
                final track = tracks[index];
                final selected = _selectedIds.contains(track.id);
                return Card(
                  color: kPanelBg,
                  margin: const EdgeInsets.symmetric(vertical: 4),
                  shape: RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(8),
                    side: BorderSide(color: selected ? kAccent : kBorder),
                  ),
                  child: CheckboxListTile(
                    value: selected,
                    activeColor: kAccent,
                    checkColor: kBg,
                    title: Text(track.title, style: const TextStyle(color: kText)),
                    subtitle: Text(
                      [
                        if (track.artist != null) track.artist!,
                        '${track.channels.length} canais',
                      ].join(' · '),
                      style: const TextStyle(color: kTextDim),
                    ),
                    onChanged: (value) {
                      setState(() {
                        if (value == true) {
                          _selectedIds.add(track.id);
                        } else {
                          _selectedIds.remove(track.id);
                        }
                      });
                    },
                  ),
                );
              },
            ),
    );
  }
}
