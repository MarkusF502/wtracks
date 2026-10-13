import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:uuid/uuid.dart';
import '../models/automation_cue.dart';
import '../models/timecode_settings.dart';
import '../providers/engine_provider.dart';
import '../theme/app_colors.dart';
import '../models/track.dart';
import '../models/song_section.dart';
import '../widgets/dialog_text_controller.dart';

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
    final current = ref.read(currentTrackProvider);
    if (current == null) return;
    final result = await showDialog<AutomationCue>(
        context: context, builder: (_) => _CueDialog(cue: cue, buses: current.midiBuses, bankId: current.activeMidiBankId));
    if (!mounted || result == null) return;
    final track = ref.read(currentTrackProvider);
    if (track?.id != widget.trackId) return;
    final cues = [...track!.automationCues.where((c) => c.id != result.id), result]..sort((a, b) => a.timeSeconds.compareTo(b.timeSeconds));
    await _apply(cues, track.midiClockEnabled);
  }

  /// Bancos, buses MIDI, banco ativo ou cues; salva se aceito.
  Future<void> _applyMidi({List<AutomationCue>? cues, List<MidiBank>? banks, List<MidiBus>? buses, Object? activeBankId = _keep}) async {
    final ok = ref.read(currentTrackProvider.notifier).updateMidi(widget.trackId, cues: cues, banks: banks, buses: buses,
        activeBankId: identical(activeBankId, _keep) ? ref.read(currentTrackProvider)?.activeMidiBankId : activeBankId);
    if (!ok) {
      _toast('Não foi possível aplicar o MIDI.');
      return;
    }
    try {
      await ref.read(trackLibraryProvider.notifier).saveCurrent();
    } catch (_) {
      if (mounted) _toast('Falha ao salvar o MIDI.');
    }
  }

  static const _keep = Object();

  Future<String?> _askText(String title, String label) => showDialog<String>(
        context: context,
        builder: (ctx) => DialogTextController(
          builder: (controller) => AlertDialog(
            backgroundColor: kPanelBg,
            title: Text(title),
            content: TextField(key: const Key('midi-name'), controller: controller, autofocus: true, decoration: InputDecoration(labelText: label)),
            actions: [
              TextButton(onPressed: () => Navigator.pop(ctx), child: const Text('Cancelar')),
              FilledButton(onPressed: () => Navigator.pop(ctx, controller.text.trim()), child: const Text('Salvar')),
            ],
          ),
        ),
      );

  List<AutomationCue>? _sectionClipboard;

  Future<void> _pasteSection(Track track, SongSection section) async {
    final copied = _sectionClipboard;
    if (copied == null) return;
    final bank = track.activeMidiBankId;
    final existing = track.automationCues.where((c) => c.bankId == bank && c.timeSeconds >= section.startSeconds && c.timeSeconds < section.endSeconds);
    if (existing.isNotEmpty) {
      final confirmed = await showDialog<bool>(
        context: context,
        builder: (ctx) => AlertDialog(
          backgroundColor: kPanelBg,
          title: const Text('Substituir cues MIDI?'),
          content: const Text('Os cues MIDI desta seção serão substituídos.'),
          actions: [
            TextButton(onPressed: () => Navigator.pop(ctx, false), child: const Text('Cancelar')),
            FilledButton(onPressed: () => Navigator.pop(ctx, true), child: const Text('Substituir')),
          ],
        ),
      );
      if (confirmed != true || !mounted) return;
    }
    await _applyMidi(
        cues: pasteSectionCues(track.automationCues, copied, section.startSeconds, section.endSeconds, () => const Uuid().v4(), bankId: bank));
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
                Row(children: [
                  const Text('Banco MIDI'),
                  const SizedBox(width: 12),
                  Expanded(
                    child: DropdownButton<String?>(
                      key: const Key('midi-bank'),
                      isExpanded: true,
                      value: track.activeMidiBankId,
                      items: [
                        const DropdownMenuItem<String?>(value: null, child: Text('Padrão')),
                        for (final b in track.midiBanks) DropdownMenuItem<String?>(value: b.id, child: Text(b.title)),
                      ],
                      onChanged: (id) => _applyMidi(activeBankId: id),
                    ),
                  ),
                  IconButton(
                    tooltip: 'Novo banco MIDI',
                    icon: const Icon(Icons.library_add_outlined),
                    onPressed: () async {
                      final title = await _askText('Novo banco MIDI', 'Nome do banco');
                      if (title == null || title.isEmpty) return;
                      final bank = MidiBank(id: const Uuid().v4(), title: title);
                      await _applyMidi(banks: [...track.midiBanks, bank], activeBankId: bank.id);
                    },
                  ),
                  if (track.activeMidiBankId != null)
                    IconButton(
                      tooltip: 'Excluir banco MIDI',
                      icon: const Icon(Icons.delete_sweep_outlined),
                      onPressed: () => _applyMidi(
                        banks: track.midiBanks.where((b) => b.id != track.activeMidiBankId).toList(),
                        cues: track.automationCues.where((c) => c.bankId != track.activeMidiBankId).toList(),
                        activeBankId: null,
                      ),
                    ),
                ]),
                ExpansionTile(
                  key: const Key('midi-buses'),
                  tilePadding: EdgeInsets.zero,
                  title: Text('Buses MIDI (${track.midiBuses.length})'),
                  children: [
                    for (final bus in track.midiBuses)
                      ListTile(
                        contentPadding: EdgeInsets.zero,
                        title: Text(bus.title),
                        subtitle: Text(bus.allChannels ? 'Canal de cada cue' : 'Canal ${bus.channel}'),
                        trailing: Row(mainAxisSize: MainAxisSize.min, children: [
                          DropdownButton<int>(
                            value: bus.allChannels ? 0 : bus.channel,
                            items: [
                              const DropdownMenuItem(value: 0, child: Text('Todos')),
                              for (var c = 1; c <= 16; c++) DropdownMenuItem(value: c, child: Text('$c')),
                            ],
                            onChanged: (c) => c == null
                                ? null
                                : _applyMidi(buses: [
                                    for (final b in track.midiBuses)
                                      b.id == bus.id ? b.copyWith(allChannels: c == 0, channel: c == 0 ? b.channel : c) : b
                                  ]),
                          ),
                          Switch(
                            value: bus.enabled,
                            onChanged: (v) => _applyMidi(buses: [for (final b in track.midiBuses) b.id == bus.id ? b.copyWith(enabled: v) : b]),
                          ),
                          IconButton(
                            tooltip: 'Excluir bus MIDI',
                            icon: const Icon(Icons.delete_outline),
                            onPressed: () => _applyMidi(
                              buses: track.midiBuses.where((b) => b.id != bus.id).toList(),
                              cues: [for (final c in track.automationCues) c.busId == bus.id ? c.copyWith(busId: null) : c],
                            ),
                          ),
                        ]),
                      ),
                    Align(
                      alignment: Alignment.centerLeft,
                      child: TextButton.icon(
                        key: const Key('add-midi-bus'),
                        icon: const Icon(Icons.add),
                        label: const Text('Adicionar bus MIDI'),
                        onPressed: () async {
                          final title = await _askText('Novo bus MIDI', 'Nome do bus');
                          if (title == null || title.isEmpty) return;
                          await _applyMidi(buses: [...track.midiBuses, MidiBus(id: const Uuid().v4(), title: title)]);
                        },
                      ),
                    ),
                  ],
                ),
                if (track.sections.isNotEmpty)
                  ExpansionTile(
                    key: const Key('section-cues'),
                    tilePadding: EdgeInsets.zero,
                    title: const Text('Cues por seção'),
                    subtitle: Text(_sectionClipboard == null ? 'Copie os cues de uma seção e cole em outra' : '${_sectionClipboard!.length} cues copiados'),
                    children: [
                      for (final section in track.sections)
                        ListTile(
                          contentPadding: EdgeInsets.zero,
                          title: Text(section.name),
                          trailing: Row(mainAxisSize: MainAxisSize.min, children: [
                            IconButton(
                              tooltip: 'Copiar cues: ${section.name}',
                              icon: const Icon(Icons.copy),
                              onPressed: () => setState(() => _sectionClipboard = copySectionCues(
                                  track.automationCues, section.startSeconds, section.endSeconds, bankId: track.activeMidiBankId)),
                            ),
                            IconButton(
                              tooltip: 'Colar cues: ${section.name}',
                              icon: const Icon(Icons.paste),
                              onPressed: _sectionClipboard == null ? null : () => _pasteSection(track, section),
                            ),
                          ]),
                        ),
                    ],
                  ),
                const Divider(),
                if (!track.automationCues.any((c) => c.bankId == track.activeMidiBankId))
                  const Padding(padding: EdgeInsets.all(24), child: Center(child: Text('Adicione automações à música.'))),
                for (final cue in track.automationCues.where((c) => c.bankId == track.activeMidiBankId))
                  Card(
                    color: kPanelBg,
                    child: ListTile(
                      title: Text(cue.label),
                      subtitle: Text('${cue.timeSeconds.toStringAsFixed(2)}s · ${_describe(cue)}'
                          '${cue.busId == null ? '' : ' · bus ${track.midiBuses.where((b) => b.id == cue.busId).firstOrNull?.title ?? '?'}'}'
                          '${cue.durationSeconds > 0 ? ' · ${cue.durationSeconds}s' : ''}${cue.disableLoop ? ' · não repete no laço' : ''}'),
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
  final List<MidiBus> buses;
  final String? bankId;
  const _CueDialog({required this.cue, this.buses = const [], this.bankId});
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
  late String? _busId = widget.buses.any((b) => b.id == widget.cue?.busId) ? widget.cue?.busId : null;
  late final _duration = TextEditingController(text: (widget.cue?.durationSeconds ?? 0).toString());
  late bool _disableLoop = widget.cue?.disableLoop ?? false;

  @override
  void dispose() {
    _label.dispose();
    _time.dispose();
    _data1.dispose();
    _data2.dispose();
    _duration.dispose();
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
                if (_kind == AutomationMessageKind.noteOn)
                  TextFormField(
                    key: const Key('cue-duration'),
                    controller: _duration,
                    keyboardType: const TextInputType.numberWithOptions(decimal: true),
                    decoration: const InputDecoration(labelText: 'Duração da nota (s, 0 = sem note-off)'),
                    validator: (s) {
                      final n = double.tryParse((s ?? '').replaceAll(',', '.'));
                      return n == null || !n.isFinite || n < 0 || n > 3600 ? 'Informe uma duração válida' : null;
                    },
                  ),
                if (widget.buses.isNotEmpty)
                  DropdownButtonFormField<String?>(
                    key: const Key('cue-bus'),
                    initialValue: _busId,
                    decoration: const InputDecoration(labelText: 'Bus MIDI'),
                    items: [
                      const DropdownMenuItem<String?>(value: null, child: Text('Nenhum (canal do cue)')),
                      for (final b in widget.buses) DropdownMenuItem<String?>(value: b.id, child: Text(b.title)),
                    ],
                    onChanged: (id) => setState(() => _busId = id),
                  ),
                SwitchListTile(
                  key: const Key('cue-disable-loop'),
                  contentPadding: EdgeInsets.zero,
                  title: const Text('Não repetir em laços'),
                  value: _disableLoop,
                  onChanged: (v) => setState(() => _disableLoop = v),
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
                bankId: widget.cue == null ? widget.bankId : widget.cue!.bankId,
                busId: hasMessage ? _busId : null,
                durationSeconds: _kind == AutomationMessageKind.noteOn ? double.parse(_duration.text.replaceAll(',', '.')) : 0,
                disableLoop: hasMessage && _disableLoop,
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
