// A transição entre duas músicas com o motor real no Android: dois decks, o dispositivo de áudio de verdade e o hand-off.
// Só valida o que o motor consegue provar sem ouvir: as posições andam, os eventos chegam, o hand-off troca os decks e o som continua.
import 'dart:io';

import 'package:flutter/foundation.dart';
import 'package:flutter_app/native/wtracks_bindings.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:integration_test/integration_test.dart';
import 'package:path_provider/path_provider.dart';

import '../test/harness/harness_support.dart';

void main() {
  IntegrationTestWidgetsFlutterBinding.ensureInitialized();

  testWidgets('Android: Crossfade entre duas músicas com o motor real termina no hand-off', (tester) async {
    final engine = WTracksEngine();
    addTearDown(engine.shutdown);
    final ready = engine.initialise();
    debugPrint('WTracks engine: initialise=$ready erro="${engine.lastError}"');
    if (!ready) return; // sem dispositivo de áudio neste emulador

    final dir = await Directory('${(await getTemporaryDirectory()).path}/transition-it').create(recursive: true);
    addTearDown(() => dir.deleteSync(recursive: true));
    final songA = writeSineWav('${dir.path}/a.wav', seconds: 4, freq: 440);
    final songB = writeSineWav('${dir.path}/b.wav', seconds: 3, freq: 660);

    expect(engine.prepareNextDeck(), true);
    final next = WTracksEngine(deck: 1);
    expect(await engine.loadTrackAsync('a', [songA.path]), true, reason: engine.lastError);
    expect(await next.loadTrackAsync('b', [songB.path]), true, reason: next.lastError);

    // a janela de 1 s termina junto com a música A
    expect(engine.scheduleTransition(1, 3.0, 1.0), true, reason: engine.lastError);
    engine.play();
    expect(engine.isPlaying, true);

    var events = 0;
    final deadline = DateTime.now().add(const Duration(seconds: 12));
    while (DateTime.now().isBefore(deadline) && events & WTracksEngine.transportEventTransitionFinished == 0) {
      await Future<void>.delayed(const Duration(milliseconds: 50));
      events |= engine.pollTransportEvents();
    }
    expect(events & WTracksEngine.transportEventTransitionStarted, isNonZero, reason: 'a janela começou');
    expect(events & WTracksEngine.transportEventTransitionFinished, isNonZero, reason: 'a janela terminou');
    expect(next.isPlaying, true, reason: 'a música que entra está tocando');
    expect(next.currentPositionSeconds, greaterThan(0.5));

    expect(engine.handoff(), true);
    // o deck 0 agora é a música B
    expect(engine.totalLengthSeconds, closeTo(3, 0.05));
    expect(engine.isPlaying, true);
    final before = engine.currentPositionSeconds;
    await Future<void>.delayed(const Duration(milliseconds: 400));
    expect(engine.currentPositionSeconds, greaterThan(before), reason: 'o som segue depois do hand-off');
    expect(next.isPlaying, false);
    next.unloadTrack();
    engine.stop();
  });
}
