import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:uuid/uuid.dart';

import '../file_import_service.dart';
import '../models/track.dart';
import '../models/engine_error.dart';
import '../providers/engine_provider.dart';

const _uuid = Uuid();


/// Um arquivo já importado (copiado pro cache local) esperando ser
/// mapeado a um canal.
class _ImportedFile {
  final String name; // nome de exibição (sem extensão)
  final String localPath;

  _ImportedFile({required this.name, required this.localPath});
}

const _defaultChannelSlots = [
  ('Click', Color(0xFFFF3B4E)),
  ('Guia', Color(0xFFFFC107)),
  ('Bateria', Color(0xFFF5A020)),
  ('Baixo', Color(0xFFA78BFA)),
  ('Teclas', Color(0xFF00C896)),
  ('Guitarra', Color(0xFF5B7CF5)),
  ('Pad', Color(0xFFF03060)),
  ('Voz Ref', Color(0xFF00E5FF)),
];


class ImportScreen extends ConsumerStatefulWidget {
  const ImportScreen({super.key});

  @override
  ConsumerState<ImportScreen> createState() => _ImportScreenState();
}

class _ImportScreenState extends ConsumerState<ImportScreen> {
  final _fileImportService = FileImportService();
  final _titleController = TextEditingController(text: 'Música importada');

  final List<_ImportedFile> _files = [];
  // index do arquivo -> index do slot de canal que ele foi mapeado para
  final Map<int, int> _mapping = {};

  int? _selectedFileIndex;
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
      final localPaths = await _fileImportService.pickAndImportChannelFiles();
      if (!mounted) return;
      setState(() {
        for (final path in localPaths) {
          final fileName = path.split('/').last;
          final displayName =
              fileName.contains('.') ? fileName.substring(0, fileName.lastIndexOf('.')) : fileName;
          _files.add(_ImportedFile(name: displayName, localPath: path));
        }
      });
    } catch (e) {
      if (!mounted) return;
      setState(() => _error = 'Erro ao importar arquivos: $e');
    } finally {
      if (mounted) setState(() => _isImporting = false);
    }
  }


  void _onFileTap(int fileIndex) {
    if (_isFinalizing) return;
    setState(() {
      _selectedFileIndex = _selectedFileIndex == fileIndex ? null : fileIndex;
    });
  }

  void _onChannelTap(int slotIndex) {
    if (_isFinalizing) return;
    
    if (_selectedFileIndex != null) {
      setState(() {
        // Um arquivo só pode estar mapeado a um canal por vez.
        _mapping.removeWhere((_, mappedSlot) => mappedSlot == slotIndex);
        _mapping[_selectedFileIndex!] = slotIndex;
        _selectedFileIndex = null;
      });
      return;
    }

    // Sem arquivo selecionado: tocar num canal já mapeado desmapeia.
    final mappedFileIndex =
        _mapping.entries.where((e) => e.value == slotIndex).map((e) => e.key).firstOrNull;
    if (mappedFileIndex != null) {
      setState(() => _mapping.remove(mappedFileIndex));
    }
  }


  Future<void> _finalize() async {
    setState(() {
      _isFinalizing = true;
      _error = null;
    });

    // Envolvemos tudo num try-catch para capturar falhas silenciosas do Dart
    try {
      final channels = <int, _ImportedFile>{
        for (final entry in _mapping.entries) entry.value: _files[entry.key],
      };

      final channelInfos = <ChannelInfo>[
        for (var slot = 0; slot < _defaultChannelSlots.length; slot++)
          if (channels[slot] != null)
            ChannelInfo(
              label: _defaultChannelSlots[slot].$1,
              filePath: channels[slot]!.localPath,
            ),
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
    final mappedCount = _mapping.length;

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
              onPressed: (_isImporting || _isFinalizing) ? null : _pickFiles,
              icon: _isImporting
                  ? const SizedBox(
                      width: 16, height: 16, child: CircularProgressIndicator(strokeWidth: 2))
                  : const Icon(Icons.add),
              label: const Text('Adicionar arquivos (.wav)'),
            ),
          ),
          const _SectionHeader(label: 'ARQUIVOS IMPORTADOS'),
          Expanded(
            flex: 45,
            child: _files.isEmpty
                ? const Center(
                    child: Text('Nenhum arquivo importado ainda.',
                        style: TextStyle(color: Color(0xFF55556A))))
                : ListView.builder(
                    padding: const EdgeInsets.symmetric(horizontal: 8, vertical: 6),
                    itemCount: _files.length,
                    itemBuilder: (context, index) => _FileRow(
                      name: _files[index].name,
                      isSelected: _selectedFileIndex == index,
                      isUsed: _mapping.containsKey(index),
                      onTap: () => _onFileTap(index),
                    ),
                  ),
          ),
          const _SectionHeader(label: 'TOQUE NUM ARQUIVO, DEPOIS NUM CANAL'),
          Expanded(
            flex: 55,
            child: ListView.builder(
              padding: const EdgeInsets.symmetric(horizontal: 8, vertical: 6),
              itemCount: _defaultChannelSlots.length,
              itemBuilder: (context, slotIndex) {
                final (label, color) = _defaultChannelSlots[slotIndex];
                final mappedFileIndex = _mapping.entries
                    .where((e) => e.value == slotIndex)
                    .map((e) => e.key)
                    .firstOrNull;
                final mappedFile = mappedFileIndex != null ? _files[mappedFileIndex] : null;

                return _ChannelRow(
                  label: label,
                  color: color,
                  mappedFileName: mappedFile?.name,
                  isTarget: _selectedFileIndex != null,
                  onTap: () => _onChannelTap(slotIndex),
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
                  Text('$mappedCount/${_defaultChannelSlots.length} canais',
                      style: const TextStyle(color: Color(0xFF8888A8))),
                  const Spacer(),
                  FilledButton(
                    onPressed: (mappedCount > 0 && !_isFinalizing) ? _finalize : null,
                    child: _isFinalizing
                        ? const SizedBox(
                            width: 20, height: 20, child: CircularProgressIndicator(strokeWidth: 2, color: Colors.white))
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

class _FileRow extends StatelessWidget {
  final String name;
  final bool isSelected;
  final bool isUsed;
  final VoidCallback onTap;

  const _FileRow({
    required this.name,
    required this.isSelected,
    required this.isUsed,
    required this.onTap,
  });

  @override
  Widget build(BuildContext context) {
    final borderColor = isSelected
        ? const Color(0xFF00E5FF)
        : isUsed
            ? const Color(0x00FF8850)
            : const Color(0xFF1E1E2E);
    final background = isSelected
        ? const Color(0xFF00E5FF).withValues(alpha: 0.1)
        : isUsed
            ? const Color(0xFF0F2A0F)
            : const Color(0xFF111119);

    return Card(
      color: background,
      margin: const EdgeInsets.symmetric(vertical: 3),
      shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(8), side: BorderSide(color: borderColor, width: 1.5)),
      child: ListTile(
        onTap: onTap,
        leading: Icon(Icons.audiotrack,
            color: isUsed ? const Color(0xFF00FF88) : const Color(0xFF8888A8)),
        title: Text(name,
            style: TextStyle(
                color: isSelected
                    ? const Color(0xFF00E5FF)
                    : isUsed
                        ? const Color(0xFFAAEEBB)
                        : const Color(0xFFC8C8E0))),
        trailing: isUsed ? const Icon(Icons.check, color: Color(0xFF00FF88)) : null,
      ),
    );
  }
}

class _ChannelRow extends StatelessWidget {
  final String label;
  final Color color;
  final String? mappedFileName;
  final bool isTarget;
  final VoidCallback onTap;

  const _ChannelRow({
    required this.label,
    required this.color,
    required this.mappedFileName,
    required this.isTarget,
    required this.onTap,
  });

  @override
  Widget build(BuildContext context) {
    final mapped = mappedFileName != null;
    final borderColor = isTarget
        ? color.withValues(alpha: 0.6)
        : mapped
            ? color.withValues(alpha: 0.5)
            : const Color(0xFF1E1E2E);

    return Card(
      color: mapped ? const Color(0xFF111130) : const Color(0xFF0F0F1A),
      margin: const EdgeInsets.symmetric(vertical: 3),
      shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(8), side: BorderSide(color: borderColor, width: 1.5)),
      child: ListTile(
        onTap: onTap,
        leading: Container(width: 4, height: 30, color: color.withValues(alpha: mapped ? 1 : 0.25)),
        title: Text(label.toUpperCase(),
            style: TextStyle(
                fontSize: 12,
                fontWeight: FontWeight.bold,
                letterSpacing: 1,
                color: mapped ? const Color(0xFFF0F0FA) : const Color(0xFF44445A))),
        subtitle: Text(
          mappedFileName ?? (isTarget ? 'Toque para mapear' : '— vazio —'),
          style: TextStyle(
              fontSize: 10, color: mapped ? const Color(0xFF8888A8) : color.withValues(alpha: 0.7)),
        ),
        trailing: mapped ? Icon(Icons.check, color: color) : null,
      ),
    );
  }
}