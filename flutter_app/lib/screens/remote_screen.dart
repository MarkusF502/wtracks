import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import '../providers/remote_provider.dart';
import '../theme/app_colors.dart';

/// Controle remoto local (protocolo próprio do WTracks; não conecta ao Playback Remote do iOS).
class RemoteScreen extends ConsumerWidget {
  const RemoteScreen({super.key});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final remote = ref.watch(remoteProvider);
    final notifier = ref.read(remoteProvider.notifier);
    return Scaffold(
      backgroundColor: kBg,
      appBar: AppBar(backgroundColor: kPanelBg, title: const Text('Controle remoto')),
      body: ListView(children: [
        SwitchListTile(
          key: const Key('remote-enabled'),
          title: const Text('Permitir conexões remotas'),
          subtitle: const Text('Outro aparelho na mesma rede controla este WTracks com o PIN abaixo.'),
          value: remote.enabled,
          onChanged: (v) => v ? notifier.enable() : notifier.disable(),
        ),
        if (remote.error != null) ListTile(title: Text(remote.error!, style: const TextStyle(color: Colors.orangeAccent))),
        if (remote.enabled) ...[
          ListTile(title: const Text('PIN'), trailing: Text(remote.pin, key: const Key('remote-pin'), style: const TextStyle(fontSize: 22))),
          ListTile(
            title: const Text('Endereço'),
            subtitle: Text(remote.addresses.isEmpty
                ? 'porta ${remote.port}'
                : remote.addresses.map((a) => 'ws://$a:${remote.port}/remote').join('\n')),
          ),
          const Divider(),
          const ListTile(title: Text('Aparelhos conectados', style: TextStyle(fontWeight: FontWeight.bold))),
          if (remote.clients.isEmpty) const ListTile(title: Text('Nenhum')),
          for (final c in remote.clients)
            ListTile(
              title: Text(c.name),
              subtitle: Text(c.address),
              trailing: IconButton(
                tooltip: 'Desconectar ${c.name}',
                icon: const Icon(Icons.link_off),
                onPressed: () => notifier.disconnect(c.id),
              ),
            ),
        ],
      ]),
    );
  }
}
