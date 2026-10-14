// O motor nativo (JUCE) carrega e inicializa no Android? Construir o WTracksEngine abre libwtracks_engine.so e resolve todos
// os símbolos do ffi_bridge: um símbolo faltando (ou a biblioteca ausente no APK) falha aqui. Inicializar o dispositivo de
// áudio pode legitimamente falhar no emulador do CI (sem placa de som); isso só é registrado.
import 'dart:io';

import 'package:flutter/foundation.dart';
import 'package:flutter_app/native/wtracks_bindings.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:integration_test/integration_test.dart';
import 'package:path_provider/path_provider.dart';

import '../test/harness/harness_support.dart';

void main() {
  IntegrationTestWidgetsFlutterBinding.ensureInitialized();

  testWidgets('Android: o motor nativo carrega e inicializa', (tester) async {
    final engine = WTracksEngine(); // lança se a biblioteca ou algum símbolo faltar
    addTearDown(engine.shutdown);
    final ok = engine.initialise();
    debugPrint('WTracks engine: initialise=$ok erro="${engine.lastError}"');
    expect(engine.ready, ok);
    if (!ok) return; // sem dispositivo de áudio neste emulador: nada mais a verificar

    final dir = await Directory('${(await getTemporaryDirectory()).path}/engine-it').create(recursive: true);
    addTearDown(() => dir.deleteSync(recursive: true));
    final song = writeSineWav('${dir.path}/song.wav', seconds: 2);
    expect(await engine.loadTrackAsync('engine-it', [song.path]), true, reason: engine.lastError);
    expect(engine.setPlayRange(0.5, 1.5), true);
    expect(engine.setFade(true, 5), true);
    expect(engine.fadeDown, true);
    engine.resetTransportState();
    expect(engine.fadeDown, false);
  });
}
