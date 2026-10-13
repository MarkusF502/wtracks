import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:uuid/uuid.dart';
import '../models/guide_cue.dart';
import '../models/song_section.dart';
import '../providers/engine_provider.dart';
import '../services/dynamic_guides.dart';
import '../theme/app_colors.dart';
import 'guide_settings_sheet.dart';

class GuideEditorScreen extends ConsumerStatefulWidget {
  final String trackId;
  const GuideEditorScreen({super.key, required this.trackId});
  @override
  ConsumerState<GuideEditorScreen> createState() => _GuideEditorScreenState();
}

class _GuideEditorScreenState extends ConsumerState<GuideEditorScreen> {
  bool _busy = false;
  Future<void> _apply(List<GuideCue> cues, bool enabled) async {
    if (_busy) return;
    setState(() => _busy = true);
    try {
      final ok = await ref
          .read(currentTrackProvider.notifier)
          .updateGuides(widget.trackId, cues, enabled);
      if (!mounted) return;
      if (!ok) {
        ScaffoldMessenger.of(context).showSnackBar(
          const SnackBar(content: Text('Não foi possível preparar as guias.')),
        );
        return;
      }
      await ref.read(trackLibraryProvider.notifier).saveCurrent();
    } catch (e) {
      if (mounted) {
        ScaffoldMessenger.of(context).showSnackBar(
          const SnackBar(content: Text('Falha ao salvar as guias.')),
        );
      }
    } finally {
      if (mounted) setState(() => _busy = false);
    }
  }

  Future<void> _edit([GuideCue? cue]) async {
    final catalog = ref.read(guideResourcesProvider).asData?.value;
    if (catalog == null || catalog.isEmpty || _busy) return;
    final result = await showDialog<GuideCue>(
      context: context,
      builder: (_) => _GuideDialog(cue: cue, catalog: catalog),
    );
    if (!mounted || result == null) return;
    final track = ref.read(currentTrackProvider);
    if (track?.id != widget.trackId) return;
    final cues = [...track!.guideCues.where((c) => c.id != result.id), result]
      ..sort((a, b) => a.timeSeconds.compareTo(b.timeSeconds));
    await _apply(cues, track.guidesEnabled);
  }

  @override
  Widget build(BuildContext context) {
    final track = ref.watch(currentTrackProvider);
    final active = track?.id == widget.trackId;
    final resources = ref.watch(guideResourcesProvider);
    return Scaffold(
      backgroundColor: kBg,
      appBar: AppBar(
        backgroundColor: kPanelBg,
        title: const Text('Guias'),
        actions: [
          IconButton(
            tooltip: 'Configurar guias',
            icon: const Icon(Icons.record_voice_over_outlined),
            onPressed: () => showModalBottomSheet<void>(
              context: context,
              backgroundColor: kPanelBg,
              isScrollControlled: true,
              builder: (_) => const GuideSettingsSheet(),
            ),
          ),
          if (active)
            Switch(
              value: track!.guidesEnabled,
              onChanged: _busy
                  ? null
                  : (enabled) => _apply(track.guideCues, enabled),
            ),
        ],
      ),
      floatingActionButton: !active || _busy || !resources.hasValue
          ? null
          : FloatingActionButton(
              tooltip: 'Adicionar guia',
              onPressed: () => _edit(),
              child: const Icon(Icons.add),
            ),
      body: !active
          ? const Center(child: Text('A música foi descarregada.'))
          : resources.when(
              loading: () => const Center(child: CircularProgressIndicator()),
              error: (e, st) => const Center(
                child: Text('Não foi possível carregar os recursos de guia.'),
              ),
              data: (_) => ListView(
                      children: [
                        _SectionGuidesCard(sections: track!.sections, plan: ref.watch(dynamicGuidePlanProvider)),
                        const Padding(
                          padding: EdgeInsets.fromLTRB(16, 16, 16, 4),
                          child: Text('Guias manuais', style: TextStyle(fontWeight: FontWeight.bold)),
                        ),
                        if (track.guideCues.isEmpty)
                          const Padding(
                            padding: EdgeInsets.all(16),
                            child: Center(child: Text('Adicione as guias da música.')),
                          ),
                        ...track.guideCues
                          .map(
                            (cue) => Card(
                              color: kPanelBg,
                              child: ListTile(
                                title: Text(cue.label),
                                subtitle: Text(
                                  '${cue.timeSeconds.toStringAsFixed(2)}s · ${(cue.gain * 100).round()}%',
                                ),
                                onTap: _busy
                                    ? null
                                    : () => ref
                                          .read(transportProvider.notifier)
                                          .seekTo(cue.timeSeconds),
                                trailing: Row(
                                  mainAxisSize: MainAxisSize.min,
                                  children: [
                                    IconButton(
                                      tooltip: 'Editar guia',
                                      icon: const Icon(Icons.edit_outlined),
                                      onPressed: _busy
                                          ? null
                                          : () => _edit(cue),
                                    ),
                                    IconButton(
                                      tooltip: 'Excluir guia',
                                      icon: const Icon(Icons.delete_outline),
                                      onPressed: _busy
                                          ? null
                                          : () => _apply(
                                              track.guideCues
                                                  .where((c) => c.id != cue.id)
                                                  .toList(),
                                              track.guidesEnabled,
                                            ),
                                    ),
                                  ],
                                ),
                              ),
                            ),
                          ),
                      ],
                    ),
            ),
    );
  }
}

/// Resumo das guias geradas a partir das seções (somente leitura; edita-se nas seções e nas preferências).
class _SectionGuidesCard extends StatelessWidget {
  final List<SongSection> sections;
  final DynamicGuidePlan? plan;
  const _SectionGuidesCard({required this.sections, required this.plan});

  @override
  Widget build(BuildContext context) {
    final plan = this.plan;
    final rows = <Widget>[];
    if (plan != null) {
      for (final section in sections) {
        final cues = plan.cues.where((c) => c.sectionId == section.id).toList();
        if (cues.isEmpty) continue;
        final spoken = <String>[
          if (cues.any((c) => c.cueType == GuideCueType.section)) 'nome',
          for (final c in cues)
            if (c.cueType == GuideCueType.count && c.cueFilePath != null) c.cueFilePath!.split('-').last,
        ];
        rows.add(ListTile(
          dense: true,
          title: Text(section.name),
          subtitle: Text('${cues.first.cueSequenceTimecode.toStringAsFixed(2)}s · ${spoken.join(', ')}'),
        ));
      }
    }
    return Card(
      color: kPanelBg,
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          const ListTile(
            title: Text('Guias das seções', style: TextStyle(fontWeight: FontWeight.bold)),
            subtitle: Text('Geradas pelas seções: nome no compasso anterior e contagem. Ajuste em "Configurar guias".'),
          ),
          if (plan == null)
            const Padding(padding: EdgeInsets.fromLTRB(16, 0, 16, 16), child: Text('Carregando vozes…'))
          else if (rows.isEmpty)
            const Padding(
              padding: EdgeInsets.fromLTRB(16, 0, 16, 16),
              child: Text('Nenhuma seção com guia ou contagem.'),
            )
          else
            ...rows,
          if (plan != null && plan.missingSectionNames.isNotEmpty)
            Padding(
              padding: const EdgeInsets.fromLTRB(16, 0, 16, 12),
              child: Text(
                'Sem áudio nesta voz: ${plan.missingSectionNames.join(', ')}',
                style: const TextStyle(color: Colors.orangeAccent),
              ),
            ),
        ],
      ),
    );
  }
}

class _GuideDialog extends StatefulWidget {
  final GuideCue? cue;
  final List<Map<String, dynamic>> catalog;
  const _GuideDialog({required this.cue, required this.catalog});
  @override
  State<_GuideDialog> createState() => _GuideDialogState();
}

class _GuideDialogState extends State<_GuideDialog> {
  final _form = GlobalKey<FormState>();
  late final _label = TextEditingController(text: widget.cue?.label ?? '');
  late final _time = TextEditingController(
    text: (widget.cue?.timeSeconds ?? 0).toString(),
  );
  late String _resource =
      widget.cue?.resourceName ?? widget.catalog.first['name'] as String;
  late double _gain = widget.cue?.gain ?? 1;
  @override
  void dispose() {
    _label.dispose();
    _time.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) => AlertDialog(
    backgroundColor: kPanelBg,
    title: Text(widget.cue == null ? 'Adicionar guia' : 'Editar guia'),
    content: SizedBox(
      width: 350,
      child: SingleChildScrollView(
        child: Form(
          key: _form,
          child: Column(
            mainAxisSize: MainAxisSize.min,
            children: [
              TextFormField(
                key: const Key('guide-label'),
                controller: _label,
                decoration: const InputDecoration(labelText: 'Nome'),
                validator: (s) =>
                    (s ?? '').trim().isEmpty ? 'Informe o nome' : null,
              ),
              TextFormField(
                key: const Key('guide-time'),
                controller: _time,
                keyboardType: const TextInputType.numberWithOptions(
                  decimal: true,
                ),
                decoration: const InputDecoration(
                  labelText: 'Instante (segundos)',
                ),
                validator: (s) {
                  final n = double.tryParse((s ?? '').replaceAll(',', '.'));
                  return n == null || !n.isFinite || n < 0
                      ? 'Informe um instante válido'
                      : null;
                },
              ),
              DropdownButtonFormField<String>(
                initialValue: _resource,
                isExpanded: true,
                decoration: const InputDecoration(labelText: 'Recurso'),
                items: widget.catalog
                    .map(
                      (r) => DropdownMenuItem(
                        value: r['name'] as String,
                        child: Text(
                          r['label'] as String,
                          maxLines: 1,
                          overflow: TextOverflow.ellipsis,
                        ),
                      ),
                    )
                    .toList(),
                onChanged: (s) {
                  if (s != null) setState(() => _resource = s);
                },
              ),
              Text('Volume: ${(_gain * 100).round()}%'),
              Slider(
                value: _gain,
                max: 2,
                onChanged: (v) => setState(() => _gain = v),
              ),
            ],
          ),
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
            GuideCue(
              id: widget.cue?.id ?? const Uuid().v4(),
              label: _label.text.trim(),
              resourceName: _resource,
              timeSeconds: double.parse(_time.text.replaceAll(',', '.')),
              gain: _gain,
            ),
          );
        },
        child: const Text('Salvar'),
      ),
    ],
  );
}
