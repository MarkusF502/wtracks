import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:uuid/uuid.dart';
import '../models/track.dart';
import '../providers/engine_provider.dart';
import '../theme/app_colors.dart';
import '../widgets/dialog_text_controller.dart';

/// Buses da música e roteamento faixa → bus → saída (Playback: "Bus levels, mute, and solo are per song",
/// "Assign Multiple Buses", "Reset Track Routings"). Até 16 buses por música.
class BusesScreen extends ConsumerWidget {
  final String trackId;
  const BusesScreen({super.key, required this.trackId});

  static const _routeLabels = {ChannelRoute.stereo: 'Estéreo', ChannelRoute.left: 'Esquerda (mono)', ChannelRoute.right: 'Direita (mono)'};

  Future<void> _persist(BuildContext context, WidgetRef ref, bool ok) async {
    if (!ok) {
      ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Não foi possível aplicar o roteamento.')));
      return;
    }
    if (!ref.read(trackLibraryProvider).any((t) => t.id == trackId)) return;
    try {
      await ref.read(trackLibraryProvider.notifier).saveCurrent();
    } catch (_) {
      if (context.mounted) {
        ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Falha ao salvar a música.')));
      }
    }
  }

  Future<String?> _askName(BuildContext context, String title, [String initial = '']) => showDialog<String>(
        context: context,
        builder: (ctx) => DialogTextController(
          initialText: initial,
          builder: (controller) => AlertDialog(
            backgroundColor: kPanelBg,
            title: Text(title),
            content: TextField(
              key: const Key('bus-name'),
              controller: controller,
              autofocus: true,
              decoration: const InputDecoration(labelText: 'Nome do bus'),
              onSubmitted: (v) => Navigator.pop(ctx, v),
            ),
            actions: [
              TextButton(onPressed: () => Navigator.pop(ctx), child: const Text('Cancelar')),
              FilledButton(onPressed: () => Navigator.pop(ctx, controller.text), child: const Text('Salvar')),
            ],
          ),
        ),
      );

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final track = ref.watch(currentTrackProvider);
    final notifier = ref.read(currentTrackProvider.notifier);
    final active = track?.id == trackId;
    return Scaffold(
      backgroundColor: kBg,
      appBar: AppBar(backgroundColor: kPanelBg, title: const Text('Buses e roteamento')),
      floatingActionButton: !active || track!.buses.length >= SongBus.maxBuses
          ? null
          : FloatingActionButton(
              tooltip: 'Adicionar bus',
              child: const Icon(Icons.add),
              onPressed: () async {
                final name = (await _askName(context, 'Novo bus'))?.trim();
                if (name == null || name.isEmpty || !context.mounted) return;
                await _persist(context, ref, notifier.addBus(SongBus(id: const Uuid().v4(), name: name)));
              },
            ),
      body: !active
          ? const Center(child: Text('A música foi descarregada.'))
          : ListView(
              padding: const EdgeInsets.only(bottom: 88),
              children: [
                const ListTile(title: Text('Buses', style: TextStyle(fontWeight: FontWeight.bold))),
                if (track!.buses.isEmpty)
                  const Padding(
                    padding: EdgeInsets.symmetric(horizontal: 16, vertical: 8),
                    child: Text('Sem buses: cada faixa vai direto para a sua saída. Toque + para agrupar faixas.'),
                  ),
                for (final bus in track.buses)
                  ListTile(
                    title: Text(bus.name),
                    subtitle: Text('${track.channels.where((c) => c.busId == bus.id).length} faixas'),
                    trailing: Row(mainAxisSize: MainAxisSize.min, children: [
                      DropdownButton<ChannelRoute>(
                        key: Key('bus-route-${bus.id}'),
                        value: bus.route,
                        items: [for (final r in ChannelRoute.values) DropdownMenuItem(value: r, child: Text(_routeLabels[r]!))],
                        onChanged: (r) => r == null ? null : _persist(context, ref, notifier.updateBus(bus.copyWith(route: r))),
                      ),
                      IconButton(
                        tooltip: 'Renomear bus',
                        icon: const Icon(Icons.edit_outlined),
                        onPressed: () async {
                          final name = (await _askName(context, 'Renomear bus', bus.name))?.trim();
                          if (name == null || name.isEmpty || !context.mounted) return;
                          await _persist(context, ref, notifier.updateBus(bus.copyWith(name: name)));
                        },
                      ),
                      IconButton(
                        tooltip: 'Excluir bus',
                        icon: const Icon(Icons.delete_outline),
                        onPressed: () => _persist(context, ref, notifier.removeBus(bus.id)),
                      ),
                    ]),
                  ),
                const Divider(),
                const ListTile(title: Text('Faixas', style: TextStyle(fontWeight: FontWeight.bold))),
                for (var i = 0; i < track.channels.length; i++)
                  ListTile(
                    title: Text(track.channels[i].label),
                    trailing: DropdownButton<String?>(
                      key: Key('channel-bus-$i'),
                      value: track.busIndex(track.channels[i].busId) >= 0 ? track.channels[i].busId : null,
                      items: [
                        const DropdownMenuItem<String?>(value: null, child: Text('Direto')),
                        for (final bus in track.buses) DropdownMenuItem<String?>(value: bus.id, child: Text(bus.name)),
                      ],
                      onChanged: (id) => _persist(context, ref, notifier.assignChannelToBus(i, id)),
                    ),
                  ),
                if (track.buses.isNotEmpty)
                  Padding(
                    padding: const EdgeInsets.all(16),
                    child: OutlinedButton.icon(
                      key: const Key('reset-track-routings'),
                      icon: const Icon(Icons.restart_alt),
                      label: const Text('Redefinir roteamento das faixas'),
                      onPressed: () async {
                        var ok = true;
                        for (var i = 0; i < track.channels.length; i++) {
                          ok = notifier.assignChannelToBus(i, null) && ok;
                        }
                        await _persist(context, ref, ok);
                      },
                    ),
                  ),
              ],
            ),
    );
  }
}
