import 'dart:async';
import 'dart:io';

import 'package:flutter/foundation.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../services/remote_server.dart';
import 'control_provider.dart';
import 'engine_provider.dart';

@immutable
class RemoteState {
  final bool enabled;
  final int? port;
  final String pin;
  final List<String> addresses;
  final List<RemoteClient> clients;
  final String? error;
  const RemoteState({this.enabled = false, this.port, this.pin = '', this.addresses = const [], this.clients = const [], this.error});
}

/// Host do controle remoto local (protocolo próprio, ver [RemoteServer]). O estado vai aos clientes a cada 250 ms.
class RemoteNotifier extends Notifier<RemoteState> {
  static const statusInterval = Duration(milliseconds: 250);
  RemoteServer? _server;
  Timer? _timer;

  @override
  RemoteState build() {
    ref.onDispose(() {
      _timer?.cancel();
      unawaited(_server?.stop());
    });
    return const RemoteState();
  }

  Map<String, Object?> _status() {
    final transport = ref.read(transportProvider);
    final track = ref.read(currentTrackProvider);
    final session = ref.read(setlistSessionProvider);
    final position = transport.positionSeconds;
    final section = track?.sections.where((s) => position >= s.startSeconds && position < s.endSeconds).firstOrNull;
    return {
      'title': track?.title,
      'playing': transport.isPlaying,
      'position': position,
      'length': transport.lengthSeconds,
      'section': section?.name,
      'loop': transport.loopEnabled,
      'next': session?.next?.title,
    };
  }

  Future<bool> enable({int port = 8787, InternetAddress? address}) async {
    await disable();
    final server = RemoteServer(
      pin: RemoteServer.randomPin(),
      onAction: (action) => ref.read(controlProvider.notifier).perform(action),
      status: _status,
      onClientsChanged: () => state = RemoteState(enabled: true, port: _server?.port, pin: _server!.pin,
          addresses: state.addresses, clients: _server!.clients),
    );
    try {
      await server.start(port: port, address: address);
    } on SocketException catch (e) {
      state = RemoteState(error: 'Não foi possível abrir a porta $port: ${e.message}');
      return false;
    }
    _server = server;
    final addresses = <String>[];
    try {
      for (final interface in await NetworkInterface.list(type: InternetAddressType.IPv4)) {
        addresses.addAll(interface.addresses.map((a) => a.address));
      }
    } on Exception {
      // sem lista de interfaces: o usuário vê só a porta
    }
    state = RemoteState(enabled: true, port: server.port, pin: server.pin, addresses: addresses, clients: server.clients);
    _timer = Timer.periodic(statusInterval, (_) => _server?.broadcast());
    return true;
  }

  Future<void> disable() async {
    _timer?.cancel();
    _timer = null;
    await _server?.stop();
    _server = null;
    state = const RemoteState();
  }

  Future<void> disconnect(String clientId) async => _server?.disconnect(clientId);
}

final remoteProvider = NotifierProvider<RemoteNotifier, RemoteState>(RemoteNotifier.new);
