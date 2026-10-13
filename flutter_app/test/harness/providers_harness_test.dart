import 'dart:io';

import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/native/wtracks_bindings.dart';
import 'package:flutter_app/providers/engine_provider.dart';

import 'harness_support.dart';

class NativeLoadFakeEngine extends FakeEngine {
  @override
  Future<bool> loadTrackAsync(String id, List<String> paths) =>
      WTracksEngine().loadTrackAsync(id, paths);
}

ProviderContainer makeContainer(FakeEngine engine, {InMemoryPersistence? persistence}) {
  final c = ProviderContainer(overrides: [
    engineProvider.overrideWithValue(engine),
    persistenceServiceProvider.overrideWithValue(persistence ?? InMemoryPersistence()),
  ]);
  addTearDown(c.dispose);
  return c;
}

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  mockBackgroundChannel();

  group('Mixer (solo/mute/volume) -> engine', () {
    test('solo em um canal muta os outros no engine sem alterar o mute manual', () {
      final engine = FakeEngine();
      final c = makeContainer(engine);
      c.read(currentTrackProvider.notifier).setLoadedTrack(sampleTrack(channels: 3));

      c.read(currentTrackProvider.notifier).toggleChannelSolo(1);

      expect(engine.calls, containsAll(['solo(0,true)', 'solo(1,false)', 'solo(2,true)', 'muted(0,false)', 'muted(1,false)', 'muted(2,false)']));
      expect(c.read(currentTrackProvider)!.channels.map((ch) => ch.muted), everyElement(false));
    });

    test('volume vai pro engine e pro estado', () {
      final engine = FakeEngine();
      final c = makeContainer(engine);
      c.read(currentTrackProvider.notifier).setLoadedTrack(sampleTrack());

      c.read(currentTrackProvider.notifier).setChannelVolume(2, 0.25);

      expect(engine.calls, contains('volume(2,0.25)'));
      expect(c.read(currentTrackProvider)!.channels[2].volume, 0.25);
    });
  });

  group('[D1] CurrentTrackNotifier.load aplica o mix salvo no engine', () {
    late Directory tmp;
    final nativeOk = nativeEngineAvailable();

    setUpAll(() {
      if (!nativeOk) return;
      // O load() roda wtracks_load_track num Isolate contra o engine
      // global nativo -- que só existe depois de wtracks_initialise.
      WTracksEngine().initialise();
      tmp = Directory.systemTemp.createTempSync('wtracks_harness_');
    });
    tearDownAll(() {
      if (nativeOk) tmp.deleteSync(recursive: true);
    });

    test('volume/mute/solo persistidos são reenviados ao engine ao reabrir a música', () async {
      final a = writeSineWav('${tmp.path}/a.wav');
      final b = writeSineWav('${tmp.path}/b.wav', freq: 220);
      final saved = Track(id: 'reopen', title: 'Reaberta', channels: [
        ChannelInfo(label: 'Guia', filePath: a.path, volume: 0.5),
        ChannelInfo(label: 'Click', filePath: b.path, muted: true),
      ]);

      final engine = NativeLoadFakeEngine();
      final c = makeContainer(engine);
      final ok = await c.read(currentTrackProvider.notifier).load(saved);

      expect(ok, isTrue, reason: 'o engine nativo deveria aceitar os WAVs gerados');
      // A UI (mixer) mostra 50% e "M" aceso, porque vem de track.channels...
      expect(c.read(currentTrackProvider)!.channels[1].muted, isTrue);
      // ...então o engine precisa receber o mesmo estado, senão toca tudo a 100%.
      expect(engine.calls, contains('volume(0,0.5)'),
          reason: 'volume salvo não foi aplicado no engine: ${engine.calls}');
      expect(engine.calls, contains('muted(1,true)'),
          reason: 'mute salvo não foi aplicado no engine: ${engine.calls}');
    }, skip: nativeOk ? false : 'libwtracks_engine.so não encontrada (rode via run_harness.sh)');
  });

  group('[D7] TransportNotifier', () {
    test('não notifica ouvintes a cada 100ms quando nada mudou (parado)', () async {
      final engine = FakeEngine();
      final c = makeContainer(engine);
      var notifications = 0;
      final sub = c.listen(transportProvider, (_, _) => notifications++);
      addTearDown(sub.close);

      await Future<void>.delayed(const Duration(seconds: 1));

      expect(notifications, lessThanOrEqualTo(1),
          reason: '$notifications rebuilds em 1s com o player parado');
    });
  });
}
