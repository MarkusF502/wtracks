import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:uuid/uuid.dart';
import '../models/automation_cue.dart';
import '../models/timecode_settings.dart';
import '../providers/engine_provider.dart';
import '../theme/app_colors.dart';

/// MIDI: saída, relógio (0xF8 na grade do click) e automações com mensagem.
class MidiScreen extends ConsumerStatefulWidget {
  final String trackId;
  const MidiScreen({super.key, required this.trackId});
  @override
  ConsumerState<MidiScreen> createState() => _MidiScreenState();
}

class _MidiScreenState extends ConsumerState<MidiScreen> {
  @override
  void initState() {
    super.initState();
    Future.microtask(() => ref.read(midiControllerProvider.notifier).refresh());
  }

  void _toast(String text) => ScaffoldMessenger.of(context).showSnackBar(SnackBar(content: Text(text)));

  Future<void> _apply(List<AutomationCue> cues, bool clock) async {
    final ok = ref.read(currentTrackProvider.notifier).updateAutomation(widget.trackId, cues, clock);
    if (!ok) {
      _toast('Não foi possível aplicar as automações.');
      return;
    }
    try {
      await ref.read(trackLibraryProvider.notifier).saveCurrent();
    } catch (_) {
      if (mounted) _toast('Falha ao salvar as automações.');
    }
  }

  Future<void> _applyTimecode(TimecodeSettings settings) async {
    final ok = ref.read(currentTrackProvider.notifier).updateTimecode(widget.trackId, settings);
    if (!ok) {
      _toast('Não foi possível aplicar o timecode.');
      return;
    }
    try {
      await ref.read(trackLibraryProvider.notifier).saveCurrent();
    } catch (_) {
      if (mounted) _toast('Falha ao salvar o timecode.');
    }
  }

  Future<void> _editTimecode(TimecodeSettings current) async {
    final result = await showDialog<TimecodeSettings>(context: context, builder: (_) => _TimecodeDialog(settings: current));
    if (!mounted || result == null) return;
    await _applyTimecode(result);
  }

  Future<void> _edit([AutomationCue? cue]) async {
    final result = await showDialog<AutomationCue>(context: context, builder: (_) => _CueDialog(cue: cue));
    if (!mounted || result == null) return;
    final track = ref.read(currentTrackProvider);
    if (track?.id != widget.trackId) return;
    final cues = [...track!.automationCues.where((c) => c.id != result.id), result]..sort((a, b) => a.timeSeconds.compareTo(b.timeSeconds));
    await _apply(cues, track.midiClockEnabled);
  }

  @override
  Widget build(BuildContext context) {
    final track = ref.watch(currentTrackProvider);
    final midi = ref.watch(midiControllerProvider);
    final fired = ref.watch(firedAutomationProvider);
    final active = track?.id == widget.trackId;
    final selected = midi.devices.any((d) => d.id == midi.selectedId) ? midi.selectedId : null;
    return Scaffold(
      backgroundColor: kBg,
      appBar: AppBar(
        backgroundColor: kPanelBg,
        title: const Text('MIDI e automações'),
        actions: [IconButton(tooltip: 'Atualizar dispositivos', icon: const Icon(Icons.refresh), onPressed: () => ref.read(midiControllerProvider.notifier).refresh())],
      ),
      floatingActionButton: active
          ? FloatingActionButton(tooltip: 'Adicionar automação', onPressed: () => _edit(), child: const Icon(Icons.add))
          : null,
      body: !active
          ? const Center(child: Text('A música foi descarregada.'))
          : ListView(
              padding: const EdgeInsets.all(16),
              children: [
                DropdownButtonFormField<String>(
                  key: const Key('midi-output'),
                  initialValue: selected,
                  isExpanded: true,
                  decoration: InputDecoration(
                    labelText: 'Saída MIDI',
                    helperText: midi.devices.isEmpty ? 'Nenhuma saída MIDI encontrada.' : (midi.connected ? 'Conectada' : 'Desconectada'),
                    errorText: midi.error,
                  ),
                  items: [for (final d in midi.devices) DropdownMenuItem(value: d.id, child: Text(d.name, overflow: TextOverflow.ellipsis))],
                  onChanged: (id) {
                    if (id != null) ref.read(midiControllerProvider.notifier).select(id);
                  },
                ),
                const SizedBox(height: 8),
                SwitchListTile(
                  key: const Key('midi-clock'),
                  contentPadding: EdgeInsets.zero,
                  title: const Text('Relógio MIDI'),
                  subtitle: const Text('24 pulsos por semínima na grade do click, com início, continuação e parada.'),
                  value: track!.midiClockEnabled,
                  onChanged: (v) => _apply(track.automationCues, v),
                ),
                Align(
                  alignment: Alignment.centerLeft,
                  child: TextButton.icon(
                    icon: const Icon(Icons.music_note),
                    label: const Text('Enviar nota de teste'),
                    onPressed: () {
                      final notifier = ref.read(midiControllerProvider.notifier);
                      if (notifier.sendTest(const [0x90, 60, 100])) {
                        Future.delayed(const Duration(milliseconds: 250), () => notifier.sendTest(const [0x80, 60, 0]));
                      }
                    },
                  ),
                ),
                SwitchListTile(
                  key: const Key('timecode-enabled'),
                  contentPadding: EdgeInsets.zero,
                  title: const Text('Timecode (LTC)'),
                  subtitle: Text(
                      '${track.timecode.rate.label} fps · início ${TimecodeSettings.format(track.timecode.rateIndex, track.timecode.startFrame)} · '
                      '${track.timecode.outputChannel == 0 ? 'saída esquerda' : 'saída direita'}'),
                  value: track.timecode.enabled,
                  onChanged: (v) => _applyTimecode(track.timecode.copyWith(enabled: v)),
                ),
                Align(
                  alignment: Alignment.centerLeft,
                  child: TextButton.icon(
                    key: const Key('timecode-edit'),
                    icon: const Icon(Icons.timer_outlined),
                    label: const Text('Configurar timecode'),
                    onPressed: () => _editTimecode(track.timecode),
                  ),
                ),
                if (fired != null) Text('Última automação: ${fired.label}', style: const TextStyle(color: kTextDim)),
                const Divider(),
                if (track.automationCues.isEmpty) const Padding(padding: EdgeInsets.all(24), child: Center(child: Text('Adicione automações à música.'))),
                for (final cue in track.automationCues)
                  Card(
                    color: kPanelBg,
                    child: ListTile(
                      title: Text(cue.label),
                      subtitle: Text('${cue.timeSeconds.toStringAsFixed(2)}s · ${_describe(cue)}'),
                      onTap: () => _edit(cue),
                      trailing: IconButton(
                        tooltip: 'Excluir automação',
                        icon: const Icon(Icons.delete_outline),
                        onPressed: () => _apply(track.automationCues.where((c) => c.id != cue.id).toList(), track.midiClockEnabled),
                      ),
                    ),
                  ),
              ],
            ),
    );
  }

  static String _describe(AutomationCue cue) => switch (cue.kind) {
        AutomationMessageKind.none => 'marcador',
        AutomationMessageKind.programChange => 'Program Change ${cue.data1} (canal ${cue.channel})',
        AutomationMessageKind.controlChange => 'CC ${cue.data1} = ${cue.data2} (canal ${cue.channel})',
        AutomationMessageKind.noteOn => 'Nota ${cue.data1} vel. ${cue.data2} (canal ${cue.channel})',
      };
}

class _CueDialog extends StatefulWidget {
  final AutomationCue? cue;
  const _CueDialog({required this.cue});
  @override
  State<_CueDialog> createState() => _CueDialogState();
}

class _CueDialogState extends State<_CueDialog> {
  final _form = GlobalKey<FormState>();
  late final _label = TextEditingController(text: widget.cue?.label ?? '');
  late final _time = TextEditingController(text: (widget.cue?.timeSeconds ?? 0).toString());
  late final _data1 = TextEditingController(text: (widget.cue?.data1 ?? 0).toString());
  late final _data2 = TextEditingController(text: (widget.cue?.data2 ?? 0).toString());
  late AutomationMessageKind _kind = widget.cue?.kind ?? AutomationMessageKind.none;
  late int _channel = widget.cue?.channel ?? 1;

  @override
  void dispose() {
    _label.dispose();
    _time.dispose();
    _data1.dispose();
    _data2.dispose();
    super.dispose();
  }

  static String? _midiByte(String? s) {
    final n = int.tryParse((s ?? '').trim());
    return n == null || n < 0 || n > 127 ? 'Use 0 a 127' : null;
  }

  @override
  Widget build(BuildContext context) {
    final hasMessage = _kind != AutomationMessageKind.none;
    final hasValue = _kind == AutomationMessageKind.controlChange || _kind == AutomationMessageKind.noteOn;
    return AlertDialog(
      backgroundColor: kPanelBg,
      title: Text(widget.cue == null ? 'Adicionar automação' : 'Editar automação'),
      content: SizedBox(
        width: 350,
        child: SingleChildScrollView(
          child: Form(
            key: _form,
            child: Column(mainAxisSize: MainAxisSize.min, children: [
              TextFormField(
                key: const Key('cue-label'),
                controller: _label,
                decoration: const InputDecoration(labelText: 'Nome'),
                validator: (s) => (s ?? '').trim().isEmpty ? 'Informe o nome' : null,
              ),
              TextFormField(
                key: const Key('cue-time'),
                controller: _time,
                keyboardType: const TextInputType.numberWithOptions(decimal: true),
                decoration: const InputDecoration(labelText: 'Instante (segundos)'),
                validator: (s) {
                  final n = double.tryParse((s ?? '').replaceAll(',', '.'));
                  return n == null || !n.isFinite || n < 0 ? 'Informe um instante válido' : null;
                },
              ),
              DropdownButtonFormField<AutomationMessageKind>(
                key: const Key('cue-kind'),
                initialValue: _kind,
                isExpanded: true,
                decoration: const InputDecoration(labelText: 'Mensagem'),
                items: const [
                  DropdownMenuItem(value: AutomationMessageKind.none, child: Text('Somente marcador')),
                  DropdownMenuItem(value: AutomationMessageKind.programChange, child: Text('Program Change')),
                  DropdownMenuItem(value: AutomationMessageKind.controlChange, child: Text('Control Change')),
                  DropdownMenuItem(value: AutomationMessageKind.noteOn, child: Text('Nota (Note On)')),
                ],
                onChanged: (k) => setState(() => _kind = k ?? _kind),
              ),
              if (hasMessage) ...[
                DropdownButtonFormField<int>(
                  initialValue: _channel,
                  decoration: const InputDecoration(labelText: 'Canal'),
                  items: [for (var c = 1; c <= 16; c++) DropdownMenuItem(value: c, child: Text('$c'))],
                  onChanged: (c) => setState(() => _channel = c ?? _channel),
                ),
                TextFormField(
                  key: const Key('cue-data1'),
                  controller: _data1,
                  keyboardType: TextInputType.number,
                  decoration: InputDecoration(labelText: _kind == AutomationMessageKind.programChange ? 'Programa' : _kind == AutomationMessageKind.controlChange ? 'Controlador' : 'Nota'),
                  validator: _midiByte,
                ),
                if (hasValue)
                  TextFormField(
                    key: const Key('cue-data2'),
                    controller: _data2,
                    keyboardType: TextInputType.number,
                    decoration: InputDecoration(labelText: _kind == AutomationMessageKind.controlChange ? 'Valor' : 'Velocidade'),
                    validator: _midiByte,
                  ),
              ],
            ]),
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
              AutomationCue(
                id: widget.cue?.id ?? const Uuid().v4(),
                label: _label.text.trim(),
                timeSeconds: double.parse(_time.text.replaceAll(',', '.')),
                kind: _kind,
                channel: _channel,
                data1: hasMessage ? int.parse(_data1.text.trim()) : 0,
                data2: hasValue ? int.parse(_data2.text.trim()) : 0,
              ),
            );
          },
          child: const Text('Salvar'),
        ),
      ],
    );
  }
}

class _TimecodeDialog extends StatefulWidget {
  final TimecodeSettings settings;
  const _TimecodeDialog({required this.settings});
  @override
  State<_TimecodeDialog> createState() => _TimecodeDialogState();
}

class _TimecodeDialogState extends State<_TimecodeDialog> {
  final _form = GlobalKey<FormState>();
  late final _start = TextEditingController(text: TimecodeSettings.format(widget.settings.rateIndex, widget.settings.startFrame));
  late final _onset = TextEditingController(text: widget.settings.onsetSeconds.toString());
  late int _rate = widget.settings.rateIndex;
  late int _output = widget.settings.outputChannel;
  late double _gain = widget.settings.gain;

  @override
  void dispose() {
    _start.dispose();
    _onset.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) => AlertDialog(
        backgroundColor: kPanelBg,
        title: const Text('Timecode'),
        content: SizedBox(
          width: 350,
          child: SingleChildScrollView(
            child: Form(
              key: _form,
              child: Column(mainAxisSize: MainAxisSize.min, children: [
                DropdownButtonFormField<int>(
                  key: const Key('timecode-rate'),
                  initialValue: _rate,
                  isExpanded: true,
                  decoration: const InputDecoration(labelText: 'Quadros por segundo'),
                  items: [for (var i = 0; i < TimecodeRate.all.length; i++) DropdownMenuItem(value: i, child: Text(TimecodeRate.all[i].label))],
                  onChanged: (v) => setState(() => _rate = v ?? _rate),
                ),
                TextFormField(
                  key: const Key('timecode-start'),
                  controller: _start,
                  decoration: const InputDecoration(labelText: 'Timecode inicial (hh:mm:ss:ff)'),
                  validator: (s) => TimecodeSettings.parse(_rate, s ?? '') == null ? 'Timecode inválido para esta taxa' : null,
                ),
                TextFormField(
                  key: const Key('timecode-onset'),
                  controller: _onset,
                  keyboardType: const TextInputType.numberWithOptions(decimal: true),
                  decoration: const InputDecoration(labelText: 'Começa em (segundos da música)'),
                  validator: (s) {
                    final n = double.tryParse((s ?? '').replaceAll(',', '.'));
                    return n == null || !n.isFinite || n < 0 || n > 86400 ? 'Informe um instante válido' : null;
                  },
                ),
                DropdownButtonFormField<int>(
                  initialValue: _output,
                  decoration: const InputDecoration(labelText: 'Saída'),
                  items: const [DropdownMenuItem(value: 0, child: Text('Esquerda')), DropdownMenuItem(value: 1, child: Text('Direita'))],
                  onChanged: (v) => setState(() => _output = v ?? _output),
                ),
                Text('Nível: ${(_gain * 100).round()}%'),
                Slider(value: _gain, onChanged: (v) => setState(() => _gain = v)),
              ]),
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
                widget.settings.copyWith(
                  rateIndex: _rate,
                  startFrame: TimecodeSettings.parse(_rate, _start.text)!,
                  onsetSeconds: double.parse(_onset.text.replaceAll(',', '.')),
                  outputChannel: _output,
                  gain: _gain,
                ),
              );
            },
            child: const Text('Salvar'),
          ),
        ],
      );
}
