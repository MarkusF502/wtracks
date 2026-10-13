import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:uuid/uuid.dart';
import '../models/song_section.dart';
import '../providers/engine_provider.dart';
import '../theme/app_colors.dart';

class SectionEditorScreen extends ConsumerStatefulWidget {
  final String trackId;
  const SectionEditorScreen({super.key, required this.trackId});
  @override
  ConsumerState<SectionEditorScreen> createState() =>
      _SectionEditorScreenState();
}

class _SectionEditorScreenState extends ConsumerState<SectionEditorScreen> {
  bool _saving = false;
  bool _loopBusy = false;
  Future<void> _loop(SongSection section, {bool queue = false}) async {
    if (_loopBusy) return;
    setState(() => _loopBusy = true);
    try {
      final ok = await ref.read(currentTrackProvider.notifier).setSectionLoop(section, queue: queue);
      if (!ok && mounted) ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Não foi possível preparar o loop desta seção.')));
    } finally { if (mounted) setState(() => _loopBusy = false); }
  }

  Future<void> _edit([SongSection? section]) async {
    final track = ref.read(currentTrackProvider);
    if (track?.id != widget.trackId || _saving || _loopBusy) return;
    final start =
        section?.startSeconds ??
        (track!.sections.isEmpty ? 0.0 : track.sections.last.endSeconds);
    final result = await showDialog<SongSection>(
      context: context,
      builder: (_) => _SectionDialog(section: section, initialStart: start),
    );
    if (!mounted || result == null) return;
    final current = ref.read(currentTrackProvider);
    if (current?.id != widget.trackId) return;
    final sections = [
      ...current!.sections.where((s) => s.id != result.id),
      result,
    ]..sort((a, b) => a.startSeconds.compareTo(b.startSeconds));
    await _save(sections);
  }

  Future<void> _save(List<SongSection> sections) async {
    if (_saving || _loopBusy) return;
    if (!ref
        .read(currentTrackProvider.notifier)
        .updateSections(widget.trackId, sections)) {
      ScaffoldMessenger.of(context).showSnackBar(
        const SnackBar(content: Text('As seções não podem se sobrepor')),
      );
      return;
    }
    setState(() => _saving = true);
    try {
      await ref.read(trackLibraryProvider.notifier).saveCurrent();
    } catch (e) {
      if (mounted) {
        ScaffoldMessenger.of(context).showSnackBar(
          const SnackBar(
            content: Text('Falha ao salvar as seções. Tente novamente.'),
          ),
        );
      }
    } finally {
      if (mounted) setState(() => _saving = false);
    }
  }

  Future<void> _delete(SongSection section) async {
    final confirmed = await showDialog<bool>(
      context: context,
      builder: (ctx) => AlertDialog(
        backgroundColor: kPanelBg,
        title: const Text('Excluir seção?'),
        content: Text(section.name),
        actions: [
          TextButton(
            onPressed: () => Navigator.pop(ctx, false),
            child: const Text('Cancelar'),
          ),
          FilledButton(
            onPressed: () => Navigator.pop(ctx, true),
            child: const Text('Excluir'),
          ),
        ],
      ),
    );
    if (!mounted || confirmed != true) return;
    final current = ref.read(currentTrackProvider);
    if (current?.id == widget.trackId) {
      await _save(current!.sections.where((s) => s.id != section.id).toList());
    }
  }

  @override
  Widget build(BuildContext context) {
    final track = ref.watch(currentTrackProvider);
    final active = track?.id == widget.trackId;
    final transport = ref.watch(transportProvider);
    return Scaffold(
      backgroundColor: kBg,
      appBar: AppBar(
        backgroundColor: kPanelBg,
        title: const Text('Seções'),
        actions: [
          if (transport.queuedLoopEnabled) IconButton(tooltip: 'Cancelar próxima seção',
            icon: const Icon(Icons.playlist_remove), onPressed: _loopBusy ? null : () => ref.read(transportProvider.notifier).clearQueuedLoop()),
          if (transport.loopEnabled) IconButton(tooltip: 'Desativar loop', icon: const Icon(Icons.repeat_on),
            onPressed: _loopBusy ? null : () {
              if (!ref.read(transportProvider.notifier).disableLoop()) ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Não foi possível desativar o loop.')));
            }),
          IconButton(
            tooltip: 'Salvar seções',
            icon: const Icon(Icons.save_outlined),
            onPressed: !active || _saving || _loopBusy ? null : () => _save(track!.sections),
          ),
        ],
      ),
      floatingActionButton: !active || _saving || _loopBusy
          ? null
          : FloatingActionButton(
              tooltip: 'Adicionar seção',
              onPressed: () => _edit(),
              child: const Icon(Icons.add),
            ),
      body: !active
          ? const Center(child: Text('A música foi descarregada.'))
          : track!.sections.isEmpty
          ? const Center(child: Text('Adicione as seções da música.'))
          : ListView.builder(
              itemCount: track.sections.length,
              itemBuilder: (context, index) {
                final section = track.sections[index];
                return Card(
                  color: kPanelBg,
                  child: ListTile(
                    title: Text(
                      section.name,
                      style: const TextStyle(color: kText),
                    ),
                    subtitle: Text(
                      '${section.startSeconds.toStringAsFixed(2)}s – ${section.endSeconds.toStringAsFixed(2)}s',
                      style: const TextStyle(color: kTextDim),
                    ),
                    onTap: _saving
                        ? null
                        : () {
                            ref
                                .read(transportProvider.notifier)
                                .seekTo(section.startSeconds);
                          },
                    trailing: Wrap(
                      spacing: 0,
                      children: [
                        IconButton(tooltip: 'Repetir ${section.name}',
                          icon: Icon(Icons.repeat, color: transport.activeSection(section) ? kAccent : kTextDim),
                          onPressed: _saving || _loopBusy ? null : () => _loop(section)),
                        IconButton(tooltip: 'Próxima seção: ${section.name}',
                          icon: Icon(Icons.playlist_play, color: transport.queuedSection(section) ? kAccent : kTextDim),
                          onPressed: _saving || _loopBusy || !transport.loopEnabled ? null : () => _loop(section, queue: true)),
                        IconButton(
                          tooltip: 'Editar seção',
                          icon: const Icon(Icons.edit_outlined),
                          onPressed: _saving || _loopBusy ? null : () => _edit(section),
                        ),
                        IconButton(
                          tooltip: 'Excluir seção',
                          icon: const Icon(Icons.delete_outline),
                          onPressed: _saving || _loopBusy ? null : () => _delete(section),
                        ),
                      ],
                    ),
                  ),
                );
              },
            ),
    );
  }
}

/// Controllers are owned until the dialog's exit animation unmounts it.
class _SectionDialog extends StatefulWidget {
  final SongSection? section;
  final double initialStart;
  const _SectionDialog({required this.section, required this.initialStart});
  @override
  State<_SectionDialog> createState() => _SectionDialogState();
}

class _SectionDialogState extends State<_SectionDialog> {
  final _form = GlobalKey<FormState>();
  late final _name = TextEditingController(text: widget.section?.name ?? '');
  late final _start = TextEditingController(
    text: widget.initialStart.toString(),
  );
  late final _end = TextEditingController(
    text: (widget.section?.endSeconds ?? widget.initialStart + 10).toString(),
  );
  late final _loops = TextEditingController(text: (widget.section?.loopCount ?? 0).toString());
  late final _trimStart = TextEditingController(text: (widget.section?.trimStartSeconds ?? 0).toString());
  late final _trimEnd = TextEditingController(text: (widget.section?.trimEndSeconds ?? 0).toString());
  late bool _preset = widget.section?.presetInfiniteLoop ?? false;
  late bool _guide = widget.section?.playGuideCue ?? true;
  late bool _countIn = widget.section?.playCountIn ?? false;
  double? _number(String? text) =>
      double.tryParse((text ?? '').replaceAll(',', '.'));
  @override
  void dispose() {
    _name.dispose();
    _start.dispose();
    _end.dispose();
    _loops.dispose();
    _trimStart.dispose();
    _trimEnd.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) => AlertDialog(
    backgroundColor: kPanelBg,
    title: Text(widget.section == null ? 'Adicionar seção' : 'Editar seção'),
    content: SingleChildScrollView(
      child: Form(
        key: _form,
        child: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            TextFormField(
              key: const Key('section-name'),
              controller: _name,
              decoration: const InputDecoration(labelText: 'Nome'),
              validator: (text) =>
                  (text ?? '').trim().isEmpty ? 'Informe o nome' : null,
            ),
            TextFormField(
              key: const Key('section-start'),
              controller: _start,
              keyboardType: const TextInputType.numberWithOptions(
                decimal: true,
              ),
              decoration: const InputDecoration(labelText: 'Início (segundos)'),
              validator: (text) {
                final n = _number(text);
                return n == null || !n.isFinite || n < 0
                    ? 'Informe um início válido'
                    : null;
              },
            ),
            TextFormField(
              key: const Key('section-end'),
              controller: _end,
              keyboardType: const TextInputType.numberWithOptions(
                decimal: true,
              ),
              decoration: const InputDecoration(labelText: 'Fim (segundos)'),
              validator: (text) {
                final n = _number(text);
                final start = _number(_start.text);
                return n == null || !n.isFinite || start == null || n <= start
                    ? 'O fim deve ser maior que o início'
                    : null;
              },
            ),
            TextFormField(
              key: const Key('section-loops'),
              controller: _loops,
              keyboardType: TextInputType.number,
              decoration: const InputDecoration(labelText: 'Repetições do laço (0 = infinito)'),
              validator: (text) {
                final n = int.tryParse((text ?? '').trim());
                return n == null || n < 0 || n > SongSection.maxLoopCount ? 'Use 0 a ${SongSection.maxLoopCount}' : null;
              },
            ),
            TextFormField(
              key: const Key('section-trim-start'),
              controller: _trimStart,
              keyboardType: const TextInputType.numberWithOptions(decimal: true),
              decoration: const InputDecoration(labelText: 'Cortar do início (segundos)'),
              validator: (text) {
                final n = _number(text);
                return n == null || !n.isFinite || n < 0 ? 'Informe um corte válido' : null;
              },
            ),
            TextFormField(
              key: const Key('section-trim-end'),
              controller: _trimEnd,
              keyboardType: const TextInputType.numberWithOptions(decimal: true),
              decoration: const InputDecoration(
                labelText: 'Cortar do fim (segundos)',
                helperText: 'Trechos cortados não tocam; cues neles não disparam.',
              ),
              validator: (text) {
                final n = _number(text), a = _number(_trimStart.text), start = _number(_start.text), end = _number(_end.text);
                if (n == null || !n.isFinite || n < 0) return 'Informe um corte válido';
                if (a != null && start != null && end != null && end - start - a - n < 0.01) return 'Os cortes ocupam a seção inteira';
                return null;
              },
            ),
            SwitchListTile(
              key: const Key('section-preset'),
              contentPadding: EdgeInsets.zero,
              title: const Text('Laço infinito automático'),
              subtitle: const Text('Entra em laço ao chegar nesta seção.'),
              value: _preset,
              onChanged: (v) => setState(() => _preset = v),
            ),
            SwitchListTile(
              key: const Key('section-guide'),
              contentPadding: EdgeInsets.zero,
              title: const Text('Guia falado da seção'),
              value: _guide,
              onChanged: (v) => setState(() => _guide = v),
            ),
            SwitchListTile(
              key: const Key('section-countin'),
              contentPadding: EdgeInsets.zero,
              title: const Text('Contagem ao entrar'),
              value: _countIn,
              onChanged: (v) => setState(() => _countIn = v),
            ),
          ],
        ),
      ),
    ),
    actions: [
      TextButton(
        onPressed: () => Navigator.pop(context),
        child: const Text('Cancelar'),
      ),
      FilledButton(
        onPressed: () {
          if (!_form.currentState!.validate()) return;
          Navigator.pop(
            context,
            SongSection(
              id: widget.section?.id ?? const Uuid().v4(),
              name: _name.text.trim(),
              startSeconds: _number(_start.text)!,
              endSeconds: _number(_end.text)!,
              loopCount: int.parse(_loops.text.trim()),
              presetInfiniteLoop: _preset,
              playGuideCue: _guide,
              playCountIn: _countIn,
              trimStartSeconds: _number(_trimStart.text)!,
              trimEndSeconds: _number(_trimEnd.text)!,
            ),
          );
        },
        child: const Text('Salvar'),
      ),
    ],
  );
}
