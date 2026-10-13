import 'dart:async';
import 'dart:convert';
import 'dart:io';
import 'dart:math' as math;

import 'package:flutter/foundation.dart';

import '../models/control_mapping.dart';

/// Controle remoto pela rede local (Playback: "Allow Remote Connections", "Connected Remote Devices",
/// "Disconnect Remote Session"). O Playback Remote original pareia aparelhos pela conta na nuvem e o protocolo não foi
/// recuperado; este é um protocolo próprio, NÃO compatível com o app iOS:
/// - WebSocket em `ws://<ip>:<porta>/remote`; a primeira mensagem do cliente deve ser `{"type":"hello","pin":"1234",
///   "name":"..."}` (PIN de 4 dígitos exibido no aparelho host); sem ela em 5 s ou com PIN errado, a conexão fecha;
/// - comandos: `{"type":"action","action":"<ControlAction.name>"}`;
/// - o host envia `{"type":"status", ...}` periodicamente e logo após o hello.
/// Mensagens acima de 4 KiB fecham a conexão.
class RemoteClient {
  final String id, name, address;
  final WebSocket socket;
  RemoteClient(this.id, this.name, this.address, this.socket);
}

class RemoteServer {
  static const maxMessageBytes = 4096;
  static const helloTimeout = Duration(seconds: 5);

  final String pin;
  final Future<void> Function(ControlAction action) onAction;
  final Map<String, Object?> Function() status;
  final void Function()? onClientsChanged;
  HttpServer? _server;
  final _clients = <RemoteClient>[];
  var _nextId = 0;

  RemoteServer({required this.pin, required this.onAction, required this.status, this.onClientsChanged});

  static String randomPin([math.Random? random]) => ((random ?? math.Random.secure()).nextInt(9000) + 1000).toString();

  int? get port => _server?.port;
  List<RemoteClient> get clients => List.unmodifiable(_clients);

  Future<void> start({int port = 8787, InternetAddress? address}) async {
    await stop();
    final server = await HttpServer.bind(address ?? InternetAddress.anyIPv4, port);
    _server = server;
    server.listen((request) async {
      if (request.uri.path != '/remote' || !WebSocketTransformer.isUpgradeRequest(request)) {
        request.response.statusCode = HttpStatus.notFound;
        await request.response.close();
        return;
      }
      try {
        final socket = await WebSocketTransformer.upgrade(request);
        _handle(socket, request.connectionInfo?.remoteAddress.address ?? '?');
      } catch (e) {
        debugPrint('Conexão remota recusada: $e');
      }
    });
  }

  void _handle(WebSocket socket, String address) {
    RemoteClient? client;
    final timer = Timer(helloTimeout, () {
      if (client == null) socket.close(WebSocketStatus.policyViolation, 'hello timeout');
    });
    socket.listen((data) {
      if (data is! String || data.length > maxMessageBytes) {
        socket.close(WebSocketStatus.messageTooBig, 'message');
        return;
      }
      final Object? message;
      try {
        message = jsonDecode(data);
      } on FormatException {
        socket.close(WebSocketStatus.invalidFramePayloadData, 'json');
        return;
      }
      if (message is! Map) return;
      if (client == null) {
        if (message['type'] != 'hello' || message['pin'] != pin) {
          socket.close(WebSocketStatus.policyViolation, 'pin');
          return;
        }
        timer.cancel();
        final name = message['name'] is String ? (message['name'] as String) : 'Remoto';
        client = RemoteClient('${_nextId++}', name.length > 40 ? name.substring(0, 40) : name, address, socket);
        _clients.add(client!);
        onClientsChanged?.call();
        _send(socket, status());
        return;
      }
      if (message['type'] == 'action') {
        final action = ControlAction.parse(message['action']);
        if (action != null) unawaited(onAction(action));
      }
    }, onDone: () {
      timer.cancel();
      if (client != null && _clients.remove(client)) onClientsChanged?.call();
    }, onError: (_) {});
  }

  void _send(WebSocket socket, Map<String, Object?> payload) {
    if (socket.readyState == WebSocket.open) socket.add(jsonEncode({'type': 'status', ...payload}));
  }

  /// Envia o estado a todos os clientes pareados.
  void broadcast() {
    final payload = status();
    for (final c in _clients) {
      _send(c.socket, payload);
    }
  }

  Future<void> disconnect(String clientId) async {
    final client = _clients.where((c) => c.id == clientId).firstOrNull;
    if (client == null) return;
    _clients.remove(client);
    await client.socket.close(WebSocketStatus.normalClosure, 'removed');
    onClientsChanged?.call();
  }

  Future<void> stop() async {
    for (final c in [..._clients]) {
      await c.socket.close(WebSocketStatus.goingAway, 'stopped');
    }
    _clients.clear();
    await _server?.close(force: true);
    _server = null;
  }
}
