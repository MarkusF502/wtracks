import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:uuid/uuid.dart';
import '../models/tempo_change.dart';
import '../providers/engine_provider.dart';
import '../theme/app_colors.dart';

/// Andamento e compasso ao longo da música: o segmento base vem do click e
/// cada mudança reinicia a contagem de compassos no seu instante.
class TempoMapScreen extends ConsumerStatefulWidget {
  final String trackId;
  const TempoMapScreen({super.key, required this.trackId});
  @override
  ConsumerState<TempoMapScreen> createState() => _TempoMapScreenState();
}

class _TempoMapScreenState extends ConsumerState<TempoMapScreen> {
  void _toast(String text) => ScaffoldMessenger.of(context).showSnackBar(SnackBar(content: Text(text)));

  Future<void> _apply(List<TempoChange> changes) async {
    final ok = ref.read(currentTrackProvider.notifier).updateTempoChanges(widget.trackId, changes);
    if (!ok) {
      _toast('Mudança de andamento inválida: use instantes crescentes depois do início do click.');
      return;
    }
    try {
      await ref.read(trackLibraryProvider.notifier).saveCurrent();
    } catch (_) {
      if (mounted) _toast('Falha ao salvar o mapa de andamento.');
    }
  }

  Future<void> _edit([TempoChange? change]) async {
    final track = ref.read(currentTrackProvider);
    if (track?.id != widget.trackId) return;
    final result = await showDialog<TempoChange>(
      context: context,
      builder: (_) => _TempoDialog(change: change, base: track!.clickSettings.bpm, suggestedStart: track.tempoChanges.isEmpty ? track.clickSettings.beatOffsetSeconds + 1 : track.tempoChanges.last.startSeconds + 1),
    );
    if (!mounted || result == null) return;
    final current = ref.read(currentTrackProvider);
    if (current?.id != widget.trackId) return;
    final changes = [...current!.tempoChanges.where((c) => c.id != result.id), result]..sort((a, b) => a.startSeconds.compareTo(b.startSeconds));
    await _apply(changes);
  }

  @override
  Widget build(BuildContext context) {
    final track = ref.watch(currentTrackProvider);
    final active = track?.id == widget.trackId;
    return Scaffold(
      backgroundColor: kBg,
      appBar: AppBar(backgroundColor: kPanelBg, title: const Text('Mapa de andamento')),
      floatingActionButton: active ? FloatingActionButton(tooltip: 'Adicionar mudança', onPressed: () => _edit(), child: const Icon(Icons.add)) : null,
      body: !active
          ? const Center(child: Text('A música foi descarregada.'))
          : ListView(padding: const EdgeInsets.all(16), children: [
              Card(
                color: kPanelBg,
                child: ListTile(
                  title: const Text('Início'),
                  subtitle: Text('${track!.clickSettings.bpm.toStringAsFixed(2)} BPM · ${track.clickSettings.timeSignatureNumerator}/${track.clickSettings.timeSignatureDenominator} '
                      'a partir de ${track.clickSettings.beatOffsetSeconds.toStringAsFixed(2)}s (ajuste no click)'),
                ),
              ),
              if (track.tempoChanges.isEmpty) const Padding(padding: EdgeInsets.all(24), child: Center(child: Text('Sem mudanças de andamento.'))),
              for (final change in track.tempoChanges)
                Card(
                  color: kPanelBg,
                  child: ListTile(
                    title: Text('${change.startSeconds.toStringAsFixed(2)}s'),
                    subtitle: Text('${change.bpm.toStringAsFixed(2)} BPM · ${change.numerator}/${change.denominator}'),
                    onTap: () => _edit(change),
                    trailing: IconButton(
                      tooltip: 'Excluir mudança',
                      icon: const Icon(Icons.delete_outline),
                      onPressed: () => _apply(track.tempoChanges.where((c) => c.id != change.id).toList()),
                    ),
                  ),
                ),
            ]),
    );
  }
}

class _TempoDialog extends StatefulWidget {
  final TempoChange? change;
  final double base, suggestedStart;
  const _TempoDialog({required this.change, required this.base, required this.suggestedStart});
  @override
  State<_TempoDialog> createState() => _TempoDialogState();
}

class _TempoDialogState extends State<_TempoDialog> {
  final _form = GlobalKey<FormState>();
  late final _start = TextEditingController(text: (widget.change?.startSeconds ?? widget.suggestedStart).toString());
  late final _bpm = TextEditingController(text: (widget.change?.bpm ?? widget.base).toString());
  late int _numerator = widget.change?.numerator ?? 4;
  late int _denominator = widget.change?.denominator ?? 4;

  @override
  void dispose() {
    _start.dispose();
    _bpm.dispose();
    super.dispose();
  }

  double? _number(String? s) => double.tryParse((s ?? '').replaceAll(',', '.'));

  @override
  Widget build(BuildContext context) => AlertDialog(
        backgroundColor: kPanelBg,
        title: Text(widget.change == null ? 'Adicionar mudança' : 'Editar mudança'),
        content: SingleChildScrollView(
          child: Form(
            key: _form,
            child: Column(mainAxisSize: MainAxisSize.min, children: [
              TextFormField(
                key: const Key('tempo-start'),
                controller: _start,
                keyboardType: const TextInputType.numberWithOptions(decimal: true),
                decoration: const InputDecoration(labelText: 'Instante (segundos)'),
                validator: (s) {
                  final n = _number(s);
                  return n == null || !n.isFinite || n <= 0 || n > 86400 ? 'Informe um instante válido' : null;
                },
              ),
              TextFormField(
                key: const Key('tempo-bpm'),
                controller: _bpm,
                keyboardType: const TextInputType.numberWithOptions(decimal: true),
                decoration: const InputDecoration(labelText: 'BPM'),
                validator: (s) {
                  final n = _number(s);
                  return n == null || !n.isFinite || n < 1 || n > 1000 ? 'Use 1 a 1000' : null;
                },
              ),
              Row(children: [
                Expanded(
                  child: DropdownButtonFormField<int>(
                    key: const Key('tempo-numerator'),
                    initialValue: _numerator,
                    decoration: const InputDecoration(labelText: 'Tempos'),
                    items: [for (var n = 1; n <= 16; n++) DropdownMenuItem(value: n, child: Text('$n'))],
                    onChanged: (v) => setState(() => _numerator = v ?? _numerator),
                  ),
                ),
                const SizedBox(width: 12),
                Expanded(
                  child: DropdownButtonFormField<int>(
                    key: const Key('tempo-denominator'),
                    initialValue: _denominator,
                    decoration: const InputDecoration(labelText: 'Unidade'),
                    items: [for (final n in const [1, 2, 4, 8, 16]) DropdownMenuItem(value: n, child: Text('$n'))],
                    onChanged: (v) => setState(() => _denominator = v ?? _denominator),
                  ),
                ),
              ]),
            ]),
          ),
        ),
        actions: [
          TextButton(onPressed: () => Navigator.pop(context), child: const Text('Cancelar')),
          FilledButton(
            onPressed: () {
              if (!_form.currentState!.validate()) return;
              Navigator.pop(
                context,
                TempoChange(
                  id: widget.change?.id ?? const Uuid().v4(),
                  startSeconds: _number(_start.text)!,
                  bpm: _number(_bpm.text)!,
                  numerator: _numerator,
                  denominator: _denominator,
                ),
              );
            },
            child: const Text('Salvar'),
          ),
        ],
      );
}
