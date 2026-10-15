import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/native/wtracks_bindings.dart';
import 'package:flutter_app/providers/audio_diagnostics_provider.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/screens/diagnostics_screen.dart';
import 'harness/harness_support.dart';
import 'harness/screens_harness_test.dart' show pumpScreen, portrait, unmount, loadRealFonts;

const _config = AudioConfigSnapshot(requestedRate: 44100, requestedBuffer: 256, deviceRate: 48000, deviceBuffer: 256,
    preparedRate: 48000, preparedBlock: 256, deadlineMs: 5.333, channels: 11, fileRate: 44100, resampleRatio: 0.91875,
    deviceXruns: 3);

void main() {
  setUpAll(loadRealFonts);
  setUp(mockBackgroundChannel);

  group('AudioDiagnostics', () {
    test('counts only what happened since the measurement started', () {
      final engine = FakeEngine()
        ..audioConfigValue = _config
        ..underrunCount = 7
        ..renderStatsValue = const RenderStatsSnapshot(callbacks: 100);
      final start = DateTime(2026, 10, 15, 12);
      final idle = AudioDiagnostics.read(engine, null, start);
      expect(idle.health, AudioHealth.idle);
      expect(idle.underruns, 0);

      final base = AudioMeasurementBase(start, 7, 3);
      expect(AudioDiagnostics.read(engine, base, start).health, AudioHealth.stable);

      engine.audioConfigValue = const AudioConfigSnapshot(deviceXruns: 5);
      var d = AudioDiagnostics.read(engine, base, start.add(const Duration(seconds: 125)));
      expect(d.deviceXruns, 2);
      expect(d.health, AudioHealth.deviceXruns);
      expect(d.elapsed, const Duration(seconds: 125));

      engine.underrunCount = 9;
      expect(AudioDiagnostics.read(engine, base, start).health, AudioHealth.underruns);

      engine.renderStatsValue = const RenderStatsSnapshot(callbacks: 100, overruns: 1);
      d = AudioDiagnostics.read(engine, base, start);
      expect(d.health, AudioHealth.overruns);
      expect(d.underruns, 2);
    });

    test('a device that does not report xruns stays "not reported"', () {
      final engine = FakeEngine()..renderStatsValue = const RenderStatsSnapshot(callbacks: 1);
      final d = AudioDiagnostics.read(engine, AudioMeasurementBase(DateTime(2026), 0, -1), DateTime(2026));
      expect(d.deviceXruns, -1);
      expect(d.health, AudioHealth.stable);
      expect(d.export(), contains('Xruns do dispositivo: não informado'));
    });

    test('export has the numbers and nothing private', () {
      final engine = FakeEngine()
        ..audioConfigValue = _config
        ..renderStatsValue = const RenderStatsSnapshot(callbacks: 2000, overruns: 0, p50Load: 0.2, p95Load: 0.4, p99Load: 0.5, maxMs: 3.1, maxLoad: 0.58);
      final text = AudioDiagnostics.read(engine, AudioMeasurementBase(DateTime(2026), 0, 3), DateTime(2026)).export();
      expect(text, contains('Dispositivo: 48000 Hz / buffer 256 frames'));
      expect(text, contains('Carga P50/P95/P99: 20.0% / 40.0% / 50.0%'));
      expect(text, contains('razão de resampling 0.91875'));
      for (final private in ['/data/', '/storage/', 'content://', 'http', 'token', 'session', '@']) {
        expect(text.contains(private), false, reason: 'export must not contain "$private"');
      }
    });

    test('starting a measurement resets the callback load but not the engine counters', () {
      final engine = FakeEngine()..audioConfigValue = _config..underrunCount = 4;
      final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine)]);
      addTearDown(c.dispose);
      final sub = c.listen(audioDiagnosticsProvider, (_, _) {});
      c.read(audioDiagnosticsProvider.notifier).startMeasurement();
      expect(engine.renderStatsResets, 1);
      expect(engine.underrunCount, 4);
      final base = c.read(audioMeasurementBaseProvider)!;
      expect((base.underruns, base.deviceXruns), (4, 3));
      sub.close();
    });

    test('the buffer never changes while playing', () {
      final engine = FakeEngine()..audioConfigValue = _config;
      final c = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine)]);
      addTearDown(c.dispose);
      final sub = c.listen(audioDiagnosticsProvider, (_, _) {});
      engine.playing = true;
      expect(c.read(audioDiagnosticsProvider.notifier).setBufferSize(512), false);
      expect(engine.calls.where((call) => call.startsWith('buffer')), isEmpty);
      engine.playing = false;
      expect(c.read(audioDiagnosticsProvider.notifier).setBufferSize(512), true);
      expect(engine.audioConfig.deviceBuffer, 512);
      expect(c.read(audioMeasurementBaseProvider), isNotNull);  // a new buffer starts a new measurement
      sub.close();
    });
  });

  testWidgets('Diagnóstico shows the real-time audio section and polls only while open', (tester) async {
    final engine = FakeEngine()
      ..audioConfigValue = _config
      ..renderStatsValue = const RenderStatsSnapshot(callbacks: 500, p99Load: 0.5);
    final c = await pumpScreen(tester, const DiagnosticsScreen(), size: portrait, engine: engine);
    await tester.pump();
    expect(find.text('Áudio em tempo real'), findsOneWidget);
    expect(find.text('sem medição'), findsOneWidget);
    expect(find.textContaining('48000 Hz · buffer 256 frames'), findsOneWidget);

    await tester.tap(find.text('Iniciar nova medição'));
    await tester.pump(const Duration(milliseconds: 600));
    expect(find.text('estável'), findsOneWidget);

    engine.underrunCount = 2;
    await tester.pump(const Duration(milliseconds: 600));
    expect(find.text('underruns detectados (read-ahead)'), findsOneWidget);

    await tester.tap(find.byKey(const Key('buffer-512')));
    await tester.pump(const Duration(milliseconds: 600));
    expect(engine.calls, contains('buffer(512)'));

    // O polling morre com a tela (um timer pendente faria o teste falhar); a base da medição continua.
    expect(c.read(audioMeasurementBaseProvider), isNotNull);
    await unmount(tester);
  });
}
