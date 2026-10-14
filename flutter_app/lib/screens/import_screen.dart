import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:uuid/uuid.dart';

import '../file_import_service.dart';
import '../models/track.dart';
import '../models/engine_error.dart';
import '../providers/engine_provider.dart';
import '../services/stem_detection.dart';
import '../widgets/dialog_text_controller.dart';

const _uuid = Uuid();

/// Máximo de canais por música (limite do motor: medidores e automação de 64 canais).
const maxImportChannels = 64;

/// Um arquivo já importado (copiado pro cache local) que vai virar um canal.
class ImportStem {
  final String id;
  final String localPath;
  final String label;
  final bool isClickOrGuide;

  /// 0 = click, 1 = guia, 2 = outro (ordem sugerida; ver [StemGuess.rank]).
  final int rank;
  const ImportStem({required this.id, required this.localPath, required this.label, required this.isClickOrGuide, required this.rank});

  ImportStem copyWith({String? label, bool? isClickOrGuide}) =>
      ImportStem(id: id, localPath: localPath, label: label ?? this.label, isClickOrGuide: isClickOrGuide ?? this.isClickOrGuide, rank: rank);
}

/// Junta os arquivos novos aos já escolhidos. Enquanto o usuário não reordenou, click e guia sobem para o início; depois da primeira
/// reordenação manual os novos entram no fim, sem mexer no que ele arrumou. Nomes repetidos ganham um número.
List<ImportStem> mergeImportedStems(List<ImportStem> current, List<String> newPaths, {required bool keepOrder}) {
  final added = [
    for (final path in newPaths)
      () {
        final guess = guessStem(path);
        return ImportStem(id: _uuid.v4(), localPath: path, label: guess.label, isClickOrGuide: guess.isClickOrGuide, rank: guess.rank);
      }()
  ];
  final all = [...current, ...added];
  if (!keepOrder) {
    final indexed = all.indexed.toList()..sort((a, b) => a.$2.rank != b.$2.rank ? a.$2.rank.compareTo(b.$2.rank) : a.$1.compareTo(b.$1));
    all
      ..clear()
      ..addAll(indexed.map((e) => e.$2));
  }
  final labels = uniqueLabels([for (final stem in all) stem.label]);
  return [for (var i = 0; i < all.length; i++) all[i].copyWith(label: labels[i])];
}

class ImportScreen extends ConsumerStatefulWidget {
  const ImportScreen({super.key});

  @override
  ConsumerState<ImportScreen> createState() => _ImportScreenState();
}

class _ImportScreenState extends ConsumerState<ImportScreen> {
  final _titleController = TextEditingController(text: 'Música importada');

  List<ImportStem> _stems = [];
  bool _reordered = false;
  bool _isImporting = false;
  bool _isFinalizing = false;
  String? _error;

  Future<void> _pickFiles() async {
    if (_isFinalizing) return; // Bloqueia toques duplos

    setState(() {
      _isImporting = true;
      _error = null;
    });

    try {
      final localPaths = await ref.read(fileImportServiceProvider).pickAndImportChannelFiles();
      if (!mounted) return;
      final room = maxImportChannels - _stems.length;
      final accepted = localPaths.where((p) => isImportableAudio(p)).toList();
      final skipped = localPaths.length - accepted.length;
      setState(() {
        _stems = mergeImportedStems(_stems, accepted.take(room).toList(), keepOrder: _reordered);
        final notes = [
          if (skipped > 0) '$skipped arquivo${skipped == 1 ? '' : 's'} ignorado${skipped == 1 ? '' : 's'} (só WAV, AIFF e FLAC)',
          if (accepted.length > room) '${accepted.length - room} fora do limite de $maxImportChannels canais',
        ];
        _error = notes.isEmpty ? null : notes.join('; ');
      });
    } catch (e) {
      if (!mounted) return;
      setState(() => _error = 'Erro ao importar arquivos: $e');
    } finally {
      if (mounted) setState(() => _isImporting = false);
    }
  }

  void _reorder(int oldIndex, int newIndex) {
    if (_isFinalizing) return;
    setState(() {
      final list = [..._stems];
      if (newIndex > oldIndex) newIndex -= 1;
      list.insert(newIndex, list.removeAt(oldIndex));
      _stems = list;
      _reordered = true;
    });
  }

  Future<void> _rename(int index) async {
    final stem = _stems[index];
    final label = await showDialog<String>(
      context: context,
      builder: (ctx) => DialogTextController(
        initialText: stem.label,
        builder: (controller) => AlertDialog(
          title: const Text('Nome do canal'),
          content: TextField(key: const Key('stem-name'), controller: controller, autofocus: true),
          actions: [
            TextButton(onPressed: () => Navigator.pop(ctx), child: const Text('Cancelar')),
            FilledButton(onPressed: () => Navigator.pop(ctx, controller.text.trim()), child: const Text('OK')),
          ],
        ),
      ),
    );
    if (label == null || label.isEmpty || !mounted) return;
    setState(() => _stems = [..._stems]..[index] = stem.copyWith(label: label));
  }

  void _toggleClickOrGuide(int index) => setState(() => _stems = [..._stems]..[index] = _stems[index].copyWith(isClickOrGuide: !_stems[index].isClickOrGuide));

  void _remove(int index) => setState(() => _stems = [..._stems]..removeAt(index));

  Future<void> _finalize() async {
    setState(() {
      _isFinalizing = true;
      _error = null;
    });

    // Envolvemos tudo num try-catch para capturar falhas silenciosas do Dart
    try {
      final defaultVolume = ref.read(appSettingsProvider).defaultChannelVolume;
      final channelInfos = <ChannelInfo>[
        for (final stem in _stems)
          ChannelInfo(label: stem.label, filePath: stem.localPath, volume: defaultVolume, isClickOrGuide: stem.isClickOrGuide),
      ];

      final title = _titleController.text.trim();
      final track = Track(
        id: _uuid.v4(),
        title: title.isEmpty ? 'Música importada' : title,
        channels: channelInfos,
      );

      // Aguarda o Isolate rodar o motor C++ em background
      final loaded = await ref.read(currentTrackProvider.notifier).load(track);

      if (!mounted) return;

      if (!loaded) {
        final lastError = engineErrorMessage(ref.read(engineProvider).lastErrorCode);
        setState(() {
          _error = 'Falha ao carregar no motor: $lastError';
          _isFinalizing = false;
        });
        return;
      }

      // Sucesso total! Volta pra tela do Mixer.
      Navigator.of(context).pop(track);

    } catch (e, stack) {
      if (!mounted) return;
      // Se qualquer erro no Dart acontecer (ex: Track mal formatada), mostra aqui.
      setState(() {
        _error = 'Erro interno inesperado: $e';
        _isFinalizing = false;
      });
      debugPrint('Erro crítico em _finalize: $e\n$stack');
    }
  }


  @override
  void dispose() {
    _titleController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    final count = _stems.length;

    return Scaffold(
      backgroundColor: const Color(0xFF07070E),
      appBar: AppBar(
        backgroundColor: const Color(0xFF111119),
        title: const Text('Importar Arquivos'),
      ),
      body: Column(
        children: [
          if (_error != null)
            Container(
              width: double.infinity,
              color: Colors.redAccent.withValues(alpha: 0.15),
              padding: const EdgeInsets.all(12),
              child: Text(_error!, style: const TextStyle(color: Colors.redAccent)),
            ),
          Padding(
            padding: const EdgeInsets.fromLTRB(12, 12, 12, 0),
            child: TextField(
              controller: _titleController,
              enabled: !_isFinalizing,
              style: const TextStyle(color: Color(0xFFF0F0FA)),
              decoration: const InputDecoration(
                labelText: 'Nome da música',
                labelStyle: TextStyle(color: Color(0xFF8888A8)),
                enabledBorder: OutlineInputBorder(borderSide: BorderSide(color: Color(0xFF1E1E2E))),
                focusedBorder: OutlineInputBorder(borderSide: BorderSide(color: Color(0xFF00E5FF))),
                border: OutlineInputBorder(),
              ),
            ),
          ),
          Padding(
            padding: const EdgeInsets.all(12),
            child: FilledButton.icon(
              key: const Key('add-files'),
              onPressed: (_isImporting || _isFinalizing || count >= maxImportChannels) ? null : _pickFiles,
              icon: _isImporting
                  ? const SizedBox(width: 16, height: 16, child: CircularProgressIndicator(strokeWidth: 2))
                  : const Icon(Icons.add),
              label: const Text('Adicionar arquivos (WAV, AIFF, FLAC)'),
            ),
          ),
          const _SectionHeader(label: 'CANAIS — ARRASTE PARA REORDENAR, TOQUE NO NOME PARA RENOMEAR'),
          Expanded(
            child: _stems.isEmpty
                ? const Center(child: Text('Nenhum arquivo importado ainda.', style: TextStyle(color: Color(0xFF55556A))))
                : ReorderableListView.builder(
                    buildDefaultDragHandles: false,
                    padding: const EdgeInsets.symmetric(horizontal: 8, vertical: 6),
                    itemCount: _stems.length,
                    onReorderItem: _reorder,
                    itemBuilder: (context, index) {
                      final stem = _stems[index];
                      return _StemRow(
                        key: ValueKey(stem.id),
                        index: index,
                        stem: stem,
                        fileName: stem.localPath.split('/').last,
                        onRename: () => _rename(index),
                        onToggleClickOrGuide: () => _toggleClickOrGuide(index),
                        onRemove: () => _remove(index),
                      );
                    },
                  ),
          ),
          SafeArea(
            top: false,
            child: Padding(
              padding: const EdgeInsets.all(16),
              child: Row(
                children: [
                  Text('$count/$maxImportChannels canais', style: const TextStyle(color: Color(0xFF8888A8))),
                  const Spacer(),
                  FilledButton(
                    key: const Key('finalize-import'),
                    onPressed: (count > 0 && !_isFinalizing) ? _finalize : null,
                    child: _isFinalizing
                        ? const SizedBox(width: 20, height: 20, child: CircularProgressIndicator(strokeWidth: 2, color: Colors.white))
                        : const Text('Finalizar Importação'),
                  ),
                ],
              ),
            ),
          ),
        ],
      ),
    );
  }
}


class _SectionHeader extends StatelessWidget {
  final String label;
  const _SectionHeader({required this.label});

  @override
  Widget build(BuildContext context) {
    return Container(
      width: double.infinity,
      height: 28,
      color: const Color(0xFF0D0D18),
      alignment: Alignment.centerLeft,
      padding: const EdgeInsets.symmetric(horizontal: 12),
      child: Text(
        label,
        style: const TextStyle(
            fontSize: 10, fontWeight: FontWeight.bold, color: Color(0xFF44445A), letterSpacing: 1),
      ),
    );
  }
}

class _StemRow extends StatelessWidget {
  final int index;
  final ImportStem stem;
  final String fileName;
  final VoidCallback onRename, onToggleClickOrGuide, onRemove;

  const _StemRow({
    super.key,
    required this.index,
    required this.stem,
    required this.fileName,
    required this.onRename,
    required this.onToggleClickOrGuide,
    required this.onRemove,
  });

  @override
  Widget build(BuildContext context) {
    final accent = stem.isClickOrGuide ? const Color(0xFFFFC107) : const Color(0xFF00E5FF);
    return Card(
      color: const Color(0xFF111119),
      margin: const EdgeInsets.symmetric(vertical: 3),
      shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(8), side: BorderSide(color: accent.withValues(alpha: 0.35))),
      child: ListTile(
        leading: ReorderableDragStartListener(index: index, child: const Icon(Icons.drag_handle, color: Color(0xFF8888A8))),
        title: InkWell(
          key: Key('stem-label-$index'),
          onTap: onRename,
          child: Text(stem.label, style: const TextStyle(color: Color(0xFFF0F0FA), fontWeight: FontWeight.w600)),
        ),
        subtitle: Text(fileName, maxLines: 1, overflow: TextOverflow.ellipsis, style: const TextStyle(fontSize: 11, color: Color(0xFF8888A8))),
        trailing: Row(mainAxisSize: MainAxisSize.min, children: [
          FilterChip(
            key: Key('stem-click-$index'),
            label: const Text('Click/guia'),
            selected: stem.isClickOrGuide,
            onSelected: (_) => onToggleClickOrGuide(),
          ),
          IconButton(key: Key('stem-remove-$index'), icon: const Icon(Icons.close), tooltip: 'Remover', onPressed: onRemove),
        ]),
      ),
    );
  }
}
