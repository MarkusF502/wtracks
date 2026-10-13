import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import '../models/control_mapping.dart';
import '../providers/control_provider.dart';
import '../theme/app_colors.dart';

/// Mapeamento MIDI e de teclado (Playback: "MIDI Mapping 2.0", "Keyboard Mapping", "Keyboard shortcuts").
class ControlMappingScreen extends ConsumerStatefulWidget {
  const ControlMappingScreen({super.key});
  @override
  ConsumerState<ControlMappingScreen> createState() => _ControlMappingScreenState();
}

class _ControlMappingScreenState extends ConsumerState<ControlMappingScreen> {
  @override
  void initState() {
    super.initState();
    Future.microtask(() => ref.read(controlProvider.notifier).refreshInputs());
  }

  Future<void> _captureKey(ControlAction action) async {
    final label = await showDialog<String>(context: context, builder: (_) => const _KeyCaptureDialog());
    if (label == null || !mounted) return;
    await ref.read(controlProvider.notifier).setMapping(
        action, ControlMapping(mappingID: action.name, mappingTypeID: MappingType.keyboard.index, stringValue1: label),
        keyboard: true);
  }

  @override
  Widget build(BuildContext context) {
    final control = ref.watch(controlProvider);
    final notifier = ref.read(controlProvider.notifier);
    final selected = control.inputs.any((d) => d.id == control.inputId) ? control.inputId : null;
    return Scaffold(
      backgroundColor: kBg,
      appBar: AppBar(
        backgroundColor: kPanelBg,
        title: const Text('Mapeamento MIDI e teclado'),
        actions: [IconButton(tooltip: 'Atualizar entradas', icon: const Icon(Icons.refresh), onPressed: notifier.refreshInputs)],
      ),
      body: ListView(children: [
        ListTile(
          title: const Text('Entrada MIDI'),
          subtitle: Text(control.inputOpen ? 'Conectada' : (control.inputs.isEmpty ? 'Nenhuma entrada encontrada' : 'Desconectada')),
          trailing: DropdownButton<String?>(
            key: const Key('midi-input'),
            value: selected,
            hint: const Text('Escolher'),
            items: [
              const DropdownMenuItem<String?>(value: null, child: Text('Nenhuma')),
              for (final d in control.inputs) DropdownMenuItem<String?>(value: d.id, child: Text(d.name)),
            ],
            onChanged: (id) => notifier.selectInput(id),
          ),
        ),
        if (control.lastMessage != null)
          ListTile(
            dense: true,
            title: Text('Última mensagem: ${control.lastMessage!.map((b) => b.toRadixString(16).padLeft(2, '0').toUpperCase()).join(' ')}'),
          ),
        const Divider(),
        for (final action in ControlAction.values)
          ListTile(
            key: Key('action-${action.name}'),
            title: Text(action.label),
            subtitle: Text([
              control.learning == action ? 'Aguardando MIDI…' : (control.midiFor(action)?.describe() ?? 'MIDI: —'),
              control.keyFor(action)?.describe() ?? 'Tecla: —',
            ].join(' · ')),
            trailing: Row(mainAxisSize: MainAxisSize.min, children: [
              IconButton(
                tooltip: 'Aprender MIDI: ${action.label}',
                icon: Icon(control.learning == action ? Icons.hearing : Icons.piano_outlined),
                onPressed: () => notifier.learn(control.learning == action ? null : action),
              ),
              IconButton(
                tooltip: 'Definir tecla: ${action.label}',
                icon: const Icon(Icons.keyboard_outlined),
                onPressed: () => _captureKey(action),
              ),
              PopupMenuButton<String>(
                tooltip: 'Limpar: ${action.label}',
                icon: const Icon(Icons.clear),
                onSelected: (v) => notifier.setMapping(action, null, keyboard: v == 'key'),
                itemBuilder: (_) => const [
                  PopupMenuItem(value: 'midi', child: Text('Remover MIDI')),
                  PopupMenuItem(value: 'key', child: Text('Remover tecla')),
                ],
              ),
            ]),
          ),
      ]),
    );
  }
}

class _KeyCaptureDialog extends StatelessWidget {
  const _KeyCaptureDialog();
  @override
  Widget build(BuildContext context) => Focus(
        autofocus: true,
        onKeyEvent: (_, event) {
          if (event is KeyDownEvent) {
            Navigator.pop(context, event.logicalKey.keyLabel.isEmpty ? event.logicalKey.debugName : event.logicalKey.keyLabel);
            return KeyEventResult.handled;
          }
          return KeyEventResult.ignored;
        },
        child: AlertDialog(
          backgroundColor: kPanelBg,
          title: const Text('Pressione uma tecla'),
          actions: [TextButton(onPressed: () => Navigator.pop(context), child: const Text('Cancelar'))],
        ),
      );
}
