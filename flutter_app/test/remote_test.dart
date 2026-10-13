import 'dart:async';
import 'dart:convert';
import 'dart:io';
import 'dart:math' as math;
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/control_mapping.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/providers/remote_provider.dart';
import 'package:flutter_app/services/remote_server.dart';
import 'harness/harness_support.dart';

Future<(WebSocket, StreamIterator<dynamic>)> _connect(int port) async {
  final socket = await WebSocket.connect('ws://127.0.0.1:$port/remote');
  return (socket, StreamIterator<dynamic>(socket));
}

Future<Map<String, dynamic>> _next(StreamIterator<dynamic> it) async {
  expect(await it.moveNext().timeout(const Duration(seconds: 2)), true);
  return jsonDecode(it.current as String) as Map<String, dynamic>;
}

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  mockBackgroundChannel();

  test('PIN pairing, status, actions, bad clients and host-side disconnect', () async {
    final actions = <ControlAction>[];
    var changes = 0;
    final server = RemoteServer(pin: '4321', onAction: (a) async => actions.add(a), status: () => {'title': 'Song'},
        onClientsChanged: () => changes++);
    await server.start(port: 0, address: InternetAddress.loopbackIPv4);
    addTearDown(server.stop);
    final port = server.port!;

    final (bad, badIt) = await _connect(port);
    bad.add(jsonEncode({'type': 'hello', 'pin': '0000'}));
    expect(await badIt.moveNext().timeout(const Duration(seconds: 2)), false);
    expect(bad.closeCode, WebSocketStatus.policyViolation);

    final (big, bigIt) = await _connect(port);
    big.add('x' * 5000);
    expect(await bigIt.moveNext().timeout(const Duration(seconds: 2)), false);

    final (good, it) = await _connect(port);
    good.add(jsonEncode({'type': 'hello', 'pin': '4321', 'name': 'Tablet'}));
    expect(await _next(it), {'type': 'status', 'title': 'Song'});
    expect(server.clients.single.name, 'Tablet');
    good.add(jsonEncode({'type': 'action', 'action': 'playPause'}));
    good.add(jsonEncode({'type': 'action', 'action': 'selfDestruct'}));
    good.add(jsonEncode({'type': 'action', 'action': 'fadeOut'}));
    await Future<void>.delayed(const Duration(milliseconds: 100));
    expect(actions, [ControlAction.playPause, ControlAction.fadeOut]);
    server.broadcast();
    expect((await _next(it))['title'], 'Song');
    await server.disconnect(server.clients.single.id);
    expect(await it.moveNext().timeout(const Duration(seconds: 2)), false);
    expect(server.clients, isEmpty);
    expect(changes, 2);

    // Raw TCP: the test binding replaces HttpClient with a fake that answers 400.
    final raw = await Socket.connect(InternetAddress.loopbackIPv4, port);
    raw.write('GET /other HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n');
    final reply = await utf8.decoder.bind(raw).join();
    expect(reply, startsWith('HTTP/1.1 404'));
    expect(RemoteServer.randomPin(math.Random(1)).length, 4);
  });

  test('provider: enable opens the host, actions reach the transport, disable closes it', () async {
    final engine = FakeEngine();
    final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine)]);
    addTearDown(c.dispose);
    c.read(currentTrackProvider.notifier).setLoadedTrack(sampleTrack(id: 's', title: 'Hino'));
    final notifier = c.read(remoteProvider.notifier);
    expect(await notifier.enable(port: 0, address: InternetAddress.loopbackIPv4), true);
    final state = c.read(remoteProvider);
    expect(state.enabled, true);
    expect(state.pin.length, 4);
    final (socket, it) = await _connect(state.port!);
    socket.add(jsonEncode({'type': 'hello', 'pin': state.pin, 'name': 'Celular'}));
    final status = await _next(it);
    expect(status['title'], 'Hino');
    expect(c.read(remoteProvider).clients.single.name, 'Celular');
    socket.add(jsonEncode({'type': 'action', 'action': 'playPause'}));
    await Future<void>.delayed(const Duration(milliseconds: 100));
    expect(engine.calls, contains('play'));
    await notifier.disable();
    expect(c.read(remoteProvider).enabled, false);
    expect(await it.moveNext().timeout(const Duration(seconds: 2)), false);
  });
}
