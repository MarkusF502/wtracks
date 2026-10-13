import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:uuid/uuid.dart';
import '../models/mixer_automation.dart';
import '../models/track.dart';
import '../providers/engine_provider.dart';
import '../theme/app_colors.dart';

/// Itens copiados de um ponto (Playback: "Copy and Paste Cues" / "Paste Automation").
final automationClipboardProvider = StateProvider<List<AutomationItem>?>((ref) => null);

/// Pontos de automação do mixer da música carregada.
class MixerAutomationScreen extends ConsumerStatefulWidget {
  final String trackId;
  const MixerAutomationScreen({super.key, required this.trackId});
  @override
  ConsumerState<MixerAutomationScreen> createState() => _MixerAutomationScreenState();
}

class _MixerAutomationScreenState extends ConsumerState<MixerAutomationScreen> {
  void _toast(String text) => ScaffoldMessenger.of(context).showSnackBar(SnackBar(content: Text(text)));

  Future<void> _apply(List<MixerAutomationCue> cues) async {
    final sorted = [...cues]..sort((a, b) => a.timeSeconds.compareTo(b.timeSeconds));
    if (!ref.read(currentTrackProvider.notifier).updateMixerAutomation(widget.trackId, sorted)) {
      _toast('Não foi possível aplicar a automação.');
      return;
    }
    try {
      await ref.read(trackLibraryProvider.notifier).saveCurrent();
    } catch (_) {
      if (mounted) _toast('Falha ao salvar a automação.');
    }
  }

  Future<void> _edit(Track track, [MixerAutomationCue? cue]) async {
    final position = ref.read(engineProvider).currentPositionSeconds;
    final initial = cue ??
        MixerAutomationCue(
          id: const Uuid().v4(),
          name: 'Automação ${track.mixerAutomation.length + 1}',
          timeSeconds: double.parse(position.toStringAsFixed(3)),
          items: MixerAutomationCue.snapshot(track),
        );
    final result = await showDialog<MixerAutomationCue>(
        context: context, builder: (_) => _AutomationDialog(cue: initial, track: track, isNew: cue == null));
    if (!mounted || result == null) return;
    final current = ref.read(currentTrackProvider);
    if (current?.id != widget.trackId) return;
    await _apply([...current!.mixerAutomation.where((c) => c.id != result.id), result]);
  }

  @override
  Widget build(BuildContext context) {
    final track = ref.watch(currentTrackProvider);
    final clipboard = ref.watch(automationClipboardProvider);
    final active = track?.id == widget.trackId;
    return Scaffold(
      backgroundColor: kBg,
      appBar: AppBar(
        backgroundColor: kPanelBg,
        title: const Text('Automação do mixer'),
        actions: [
          if (active)
            Tooltip(
              message: 'Automação ligada',
              child: Switch(
                key: const Key('automation-enabled'),
                value: track!.automationEnabled,
                onChanged: (v) async {
                  ref.read(currentTrackProvider.notifier).setAutomationEnabled(v);
                  try {
                    await ref.read(trackLibraryProvider.notifier).saveCurrent();
                  } catch (_) {
                    if (mounted) _toast('Falha ao salvar a automação.');
                  }
                },
              ),
            ),
        ],
      ),
      floatingActionButton: !active
          ? null
          : FloatingActionButton(
              tooltip: 'Adicionar ponto de automação',
              onPressed: () => _edit(track!),
              child: const Icon(Icons.add),
            ),
      body: !active
          ? const Center(child: Text('A música foi descarregada.'))
          : ListView(
              padding: const EdgeInsets.only(bottom: 88),
              children: [
                const ListTile(
                  subtitle: Text('A transição é o tempo (em tempos do compasso) em que os faders começam a ir até o ponto. '
                      'Mute e unmute são instantâneos.'),
                ),
                if (track!.mixerAutomation.isEmpty)
                  const Padding(
                    padding: EdgeInsets.all(24),
                    child: Center(child: Text('Nenhum ponto. Toque + para fotografar o mixer na posição atual.')),
                  ),
                for (final cue in track.mixerAutomation)
                  Card(
                    color: kPanelBg,
                    child: ListTile(
                      title: Text(cue.name),
                      subtitle: Text('${cue.timeSeconds.toStringAsFixed(2)}s · transição ${cue.transitionBeats} tempos'
                          '${cue.applyTransitionLengthCorrection ? ' (corrigida)' : ''} · ${cue.items.length} itens'),
                      onTap: () => ref.read(transportProvider.notifier).seekTo(cue.timeSeconds),
                      trailing: PopupMenuButton<String>(
                        tooltip: 'Ações do ponto',
                        onSelected: (choice) {
                          switch (choice) {
                            case 'edit':
                              _edit(track, cue);
                            case 'copy':
                              ref.read(automationClipboardProvider.notifier).state = cue.items;
                              _toast('Itens copiados.');
                            case 'paste':
                              if (clipboard != null) {
                                _apply([for (final c in track.mixerAutomation) c.id == cue.id ? c.copyWith(items: clipboard) : c]);
                              }
                            case 'snapshot':
                              _apply([
                                for (final c in track.mixerAutomation)
                                  c.id == cue.id ? c.copyWith(items: MixerAutomationCue.snapshot(track)) : c
                              ]);
                            case 'delete':
                              _apply(track.mixerAutomation.where((c) => c.id != cue.id).toList());
                          }
                        },
                        itemBuilder: (_) => [
                          const PopupMenuItem(value: 'edit', child: Text('Editar')),
                          const PopupMenuItem(value: 'snapshot', child: Text('Definir com o mixer atual')),
                          const PopupMenuItem(value: 'copy', child: Text('Copiar')),
                          PopupMenuItem(value: 'paste', enabled: clipboard != null, child: const Text('Colar (substitui os itens)')),
                          const PopupMenuItem(value: 'delete', child: Text('Excluir')),
                        ],
                      ),
                    ),
                  ),
              ],
            ),
    );
  }
}

class _AutomationDialog extends StatefulWidget {
  final MixerAutomationCue cue;
  final Track track;
  final bool isNew;
  const _AutomationDialog({required this.cue, required this.track, required this.isNew});
  @override
  State<_AutomationDialog> createState() => _AutomationDialogState();
}

class _AutomationDialogState extends State<_AutomationDialog> {
  final _form = GlobalKey<FormState>();
  late final _name = TextEditingController(text: widget.cue.name);
  late final _time = TextEditingController(text: widget.cue.timeSeconds.toString());
  late final _beats = TextEditingController(text: widget.cue.transitionBeats.toString());
  late bool _correction = widget.cue.applyTransitionLengthCorrection;
  late final Map<String, double> _items = {for (final i in widget.cue.items) i.automationID: i.value};

  @override
  void dispose() {
    _name.dispose();
    _time.dispose();
    _beats.dispose();
    super.dispose();
  }

  Widget _volume(String id, String label, double max, double fallback) {
    final included = _items.containsKey(id);
    return Row(children: [
      Checkbox(
        key: Key('include-$id'),
        value: included,
        onChanged: (v) => setState(() => v == true ? _items[id] = fallback : _items.remove(id)),
      ),
      SizedBox(width: 72, child: Text(label, overflow: TextOverflow.ellipsis)),
      Expanded(
        child: Slider(
          key: Key('value-$id'),
          value: (_items[id] ?? fallback).clamp(0.0, max),
          max: max,
          onChanged: included ? (v) => setState(() => _items[id] = v) : null,
        ),
      ),
      SizedBox(width: 40, child: Text(included ? '${((_items[id]!) * 100).round()}%' : '—')),
    ]);
  }

  Widget _mute(String id, String label) {
    final included = _items.containsKey(id);
    return Row(children: [
      Checkbox(
        key: Key('include-$id'),
        value: included,
        onChanged: (v) => setState(() => v == true ? _items[id] = 0 : _items.remove(id)),
      ),
      Expanded(child: Text(label)),
      Switch(
        key: Key('value-$id'),
        value: (_items[id] ?? 0) == 1,
        onChanged: included ? (v) => setState(() => _items[id] = v ? 1 : 0) : null,
      ),
    ]);
  }

  @override
  Widget build(BuildContext context) {
    final channels = widget.track.channels;
    return AlertDialog(
      backgroundColor: kPanelBg,
      title: Text(widget.isNew ? 'Adicionar ponto de automação' : 'Editar ponto de automação'),
      content: SizedBox(
        width: 420,
        child: SingleChildScrollView(
          child: Form(
            key: _form,
            child: Column(
              mainAxisSize: MainAxisSize.min,
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                TextFormField(
                  key: const Key('automation-name'),
                  controller: _name,
                  decoration: const InputDecoration(labelText: 'Nome'),
                  validator: (s) => (s ?? '').trim().isEmpty ? 'Informe o nome' : null,
                ),
                TextFormField(
                  key: const Key('automation-time'),
                  controller: _time,
                  keyboardType: const TextInputType.numberWithOptions(decimal: true),
                  decoration: const InputDecoration(labelText: 'Instante (segundos)'),
                  validator: (s) {
                    final n = double.tryParse((s ?? '').replaceAll(',', '.'));
                    return n == null || !n.isFinite || n < 0 || n > 86400 ? 'Informe um instante válido' : null;
                  },
                ),
                TextFormField(
                  key: const Key('automation-beats'),
                  controller: _beats,
                  keyboardType: TextInputType.number,
                  decoration: const InputDecoration(labelText: 'Duração da transição (tempos)'),
                  validator: (s) {
                    final n = int.tryParse(s ?? '');
                    return n == null || n < 0 || n > MixerAutomationCue.maxTransitionBeats ? 'De 0 a 256 tempos' : null;
                  },
                ),
                SwitchListTile(
                  key: const Key('automation-correction'),
                  contentPadding: EdgeInsets.zero,
                  title: const Text('Corrigir duração da transição'),
                  subtitle: const Text('Não começa antes do ponto anterior do mesmo fader'),
                  value: _correction,
                  onChanged: (v) => setState(() => _correction = v),
                ),
                Align(
                  alignment: Alignment.centerRight,
                  child: TextButton.icon(
                    icon: const Icon(Icons.camera_alt_outlined),
                    label: const Text('Fotografar mixer'),
                    onPressed: () => setState(() {
                      _items
                        ..clear()
                        ..addEntries(MixerAutomationCue.snapshot(widget.track).map((i) => MapEntry(i.automationID, i.value)));
                    }),
                  ),
                ),
                _volume(AutomationItem.masterVolume, 'Master', 2, widget.track.masterVolume.clamp(0.0, 2.0)),
                for (var i = 0; i < channels.length && i < AutomationItem.maxChannels; i++) ...[
                  _volume(AutomationItem.channelVolume(i), channels[i].label, 1, channels[i].volume.clamp(0.0, 1.0)),
                  _mute(AutomationItem.channelMute(i), 'Mute ${channels[i].label}'),
                ],
              ],
            ),
          ),
        ),
      ),
      actions: [
        TextButton(onPressed: () => Navigator.pop(context), child: const Text('Cancelar')),
        FilledButton(
          onPressed: () {
            if (!_form.currentState!.validate()) return;
            Navigator.pop(
              context,
              widget.cue.copyWith(
                name: _name.text.trim(),
                timeSeconds: double.parse(_time.text.replaceAll(',', '.')),
                transitionBeats: int.parse(_beats.text),
                applyTransitionLengthCorrection: _correction,
                items: [for (final e in _items.entries) AutomationItem(e.key, e.value)],
              ),
            );
          },
          child: const Text('Salvar'),
        ),
      ],
    );
  }
}
