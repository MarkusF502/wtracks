// Run only on the dedicated test AVD: creates and removes its own fixtures.
import 'dart:io';
import 'dart:math';
import 'dart:typed_data';

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_app/main.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/providers/waveform_provider.dart';
import 'package:flutter_app/services/persistence_service.dart';
import 'package:flutter_app/screens/performance_screen.dart';
import 'package:flutter_app/screens/library_screen.dart';
import 'package:flutter_app/screens/setlist_editor_screen.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:integration_test/integration_test.dart';

Future<File> wav(Directory dir, String name) async {
  const rate = 44100;
  const n = rate * 8;
  final data = ByteData(44 + n * 2);
  void ascii(int offset, String value) {
    for (var i = 0; i < value.length; i++) {
      data.setUint8(offset + i, value.codeUnitAt(i));
    }
  }

  ascii(0, 'RIFF');
  data.setUint32(4, 36 + n * 2, Endian.little);
  ascii(8, 'WAVE');
  ascii(12, 'fmt ');
  data.setUint32(16, 16, Endian.little);
  data.setUint16(20, 1, Endian.little);
  data.setUint16(22, 1, Endian.little);
  data.setUint32(24, rate, Endian.little);
  data.setUint32(28, rate * 2, Endian.little);
  data.setUint16(32, 2, Endian.little);
  data.setUint16(34, 16, Endian.little);
  ascii(36, 'data');
  data.setUint32(40, n * 2, Endian.little);
  for (var i = 0; i < n; i++) {
    data.setInt16(
      44 + i * 2,
      (sin(2 * pi * 440 * i / rate) * 8000).round(),
      Endian.little,
    );
  }
  return File('${dir.path}/$name.wav').writeAsBytes(data.buffer.asUint8List());
}

Future<void> frames(WidgetTester tester, [int count = 10]) async {
  for (var i = 0; i < count; i++) {
    await tester.pump(const Duration(milliseconds: 100));
  }
}

void main() {
  IntegrationTestWidgetsFlutterBinding.ensureInitialized();
  testWidgets('Fase 5 Android: setlists, picker, waveform, transporte e exclusão', (
    tester,
  ) async {
    final fixtureRoot = await Directory.systemTemp.createTemp(
      'wtracks_phase5_',
    );
    final persistence = PersistenceService(
      rootDirectoryResolver: () async => fixtureRoot,
    );
    final tracks = <Track>[];
    for (var i = 0; i < 3; i++) {
      final audio = await wav(fixtureRoot, 'song$i');
      tracks.add(
        await persistence.saveTrack(
          Track(
            id: 'phase5_$i',
            title: 'Teste $i',
            channels: [
              ChannelInfo(
                label: 'Guia',
                filePath: audio.path,
                volume: 0.5,
                muted: i == 2,
              ),
            ],
          ),
        ),
      );
    }
    await persistence.saveSetlist(
      Setlist(id: 'setA', name: 'Teste A', tracks: tracks),
    );
    await persistence.saveSetlist(
      Setlist(id: 'setB', name: 'Teste B', tracks: tracks.reversed.toList()),
    );
    final c = ProviderContainer(
      overrides: [persistenceServiceProvider.overrideWithValue(persistence)],
    );
    await tester.pumpWidget(
      UncontrolledProviderScope(container: c, child: const WTracksApp()),
    );
    await frames(tester);
    expect(c.read(engineProvider).ready, true);
    debugPrint('PHASE5: engine Android inicializado');

    await tester.tap(find.byTooltip('Setlists'));
    await frames(tester);
    for (final name in ['Teste A', 'Teste B', 'Teste A']) {
      await tester.tap(find.text(name));
      await frames(tester);
      for (var i = 0; i < 3; i++) {
        final list = tester.widget<ReorderableListView>(
          find.byType(ReorderableListView),
        );
        list.onReorderItem!(0, 2);
        await frames(tester, 2);
      }
      await tester.tap(find.byTooltip('Adicionar Música'));
      await frames(tester);
      // Existing IDs are preselected: confirm exercises route disposal and editor updates.
      await tester.tap(find.text('Teste 2'));
      await tester.tap(find.text('Teste 2'));
      await tester.tap(find.text('Adicionar'));
      await frames(tester);
      await SystemChrome.setPreferredOrientations([
        DeviceOrientation.landscapeLeft,
      ]);
      await frames(tester);
      expect(tester.takeException(), isNull);
      await SystemChrome.setPreferredOrientations([
        DeviceOrientation.portraitUp,
      ]);
      await frames(tester);
      await tester.pageBack();
      await frames(tester);
    }
    debugPrint(
      'PHASE5: reordenação, alternância, picker e rotação do editor OK',
    );
    await tester.pageBack();
    await frames(tester);

    // Double tap before asynchronous native load finishes must open one route.
    await tester.tap(find.text('Teste 0'));
    await tester.tap(find.text('Teste 0'));
    await frames(tester, 20);
    expect(find.byType(PerformanceScreen), findsOneWidget);
    expect(c.read(currentTrackProvider)?.id, tracks[0].id);
    expect(c.read(engineProvider).totalLengthSeconds, closeTo(8, 0.05));
    expect(c.read(waveformProvider).peaks, isNotNull);
    expect(await persistence.loadWaveformPeaks(tracks[0].id), isNotNull);
    debugPrint('PHASE5: double tap, waveform nativa e cache em disco OK');
    final waveform = find.byWidgetPredicate(
      (w) =>
          w is GestureDetector &&
          w.onTapDown != null &&
          w.onHorizontalDragUpdate != null,
    );
    await tester.tap(waveform);
    expect(c.read(engineProvider).currentPositionSeconds, closeTo(4, 0.2));
    await tester.drag(waveform, const Offset(50, 0));
    expect(c.read(engineProvider).currentPositionSeconds, greaterThan(4));
    await c
        .read(waveformProvider.notifier)
        .loadFor(
          Track(
            id: 'bad-wave',
            title: 'Inválida',
            channels: [
              ChannelInfo(
                label: 'bad',
                filePath: '${fixtureRoot.path}/missing.wav',
              ),
            ],
          ),
        );
    await frames(tester, 2);
    final fallback = find.byWidgetPredicate((w) => w is Slider && w.max == 8);
    await tester.tap(fallback);
    expect(c.read(engineProvider).currentPositionSeconds, closeTo(4, 0.3));
    await c.read(waveformProvider.notifier).loadFor(tracks[0]);
    await frames(tester, 2);
    expect(c.read(waveformProvider).isGenerating, false);
    expect(c.read(waveformProvider).peaks, isNotNull);
    debugPrint(
      'PHASE5: waveform toque/arraste, fallback nativo e reabertura do cache OK',
    );

    for (final orientation in [
      DeviceOrientation.portraitUp,
      DeviceOrientation.landscapeLeft,
    ]) {
      await SystemChrome.setPreferredOrientations([orientation]);
      await frames(tester);
      c.read(engineProvider).stop();
      c.read(engineProvider).play();
      await frames(tester, 2);
      await tester.tap(find.text('BPM'));
      await frames(tester);
      c.read(transportProvider.notifier).seekTo(1.25);
      await frames(tester, 2);
      await tester.ensureVisible(find.text('Marcar 1º tempo'));
      await tester.tap(find.text('Marcar 1º tempo'));
      await frames(tester);
      expect(
        c.read(currentTrackProvider)!.clickSettings.beatOffsetSeconds,
        greaterThan(1),
      );
      await c.read(transportProvider.notifier).pause();
      Navigator.of(tester.element(find.text('Marcar 1º tempo'))).pop();
      await frames(tester);
      expect(tester.takeException(), isNull);
    }
    await SystemChrome.setPreferredOrientations([DeviceOrientation.portraitUp]);
    await frames(tester);
    await tester.pageBack();
    await frames(tester);

    // First request may display Android's permission dialog; runner answers via adb.
    for (final track in tracks) {
      expect(await c.read(currentTrackProvider.notifier).load(track), true);
      await c.read(transportProvider.notifier).play();
      await frames(tester, 90);
      expect(c.read(engineProvider).isPlaying, false);
      expect(c.read(engineProvider).currentPositionSeconds, closeTo(8, 0.05));
    }
    debugPrint('PHASE5: três músicas consecutivas encerradas no fim OK');
    expect(await c.read(currentTrackProvider.notifier).load(tracks[0]), true);
    await c.read(transportProvider.notifier).play();
    await frames(tester, 5);
    await c.read(transportProvider.notifier).pause();
    expect(c.read(engineProvider).isPlaying, false);
    await c.read(trackLibraryProvider.notifier).deleteTrack(tracks[0].id);
    expect(c.read(currentTrackProvider), isNull);
    expect(c.read(engineProvider).channelCount, 0);
    expect(await persistence.loadWaveformPeaks(tracks[0].id), isNull);
    expect(
      (await persistence.loadAllSetlists())
          .expand((s) => s.tracks)
          .any((t) => t.id == tracks[0].id),
      false,
    );
    expect(find.byType(SetlistEditorScreen), findsNothing);
    expect(tester.takeException(), isNull);
    debugPrint('PHASE5: pause e exclusão consistente OK');
    await tester.pumpWidget(const SizedBox());
    c.dispose();
    await fixtureRoot.delete(recursive: true);
  });
  testWidgets(
    'crash regression Android: renomear depois de remover rota de origem',
    (tester) async {
      final root = await Directory.systemTemp.createTemp('wtracks_dialog_');
      final persistence = PersistenceService(
        rootDirectoryResolver: () async => root,
      );
      final track = await persistence.saveTrack(
        Track(id: 'dialog', title: 'Original', channels: []),
      );
      final c = ProviderContainer(
        overrides: [persistenceServiceProvider.overrideWithValue(persistence)],
      );
      await tester.pumpWidget(
        UncontrolledProviderScope(
          container: c,
          child: MaterialApp(
            home: Builder(
              builder: (context) => TextButton(
                onPressed: () => Navigator.of(context).push(
                  MaterialPageRoute<void>(
                    builder: (_) => const LibraryScreen(),
                  ),
                ),
                child: const Text('Abrir biblioteca'),
              ),
            ),
          ),
        ),
      );
      await tester.tap(find.text('Abrir biblioteca'));
      await frames(tester);
      final context = tester.element(find.byType(LibraryScreen));
      final navigator = Navigator.of(context);
      final route = ModalRoute.of(context)!;
      await tester.longPress(find.text(track.title));
      await frames(tester);
      await tester.enterText(find.byType(TextField), 'Outro nome');
      navigator.removeRoute(route);
      await tester.pump();
      await tester.tap(find.text('Salvar'));
      await frames(tester);
      expect(tester.takeException(), isNull);
      expect((await persistence.loadTrack(track.id))!.title, 'Original');
      await tester.pumpWidget(const SizedBox());
      c.dispose();
      await root.delete(recursive: true);
      debugPrint(
        'PHASE5: regressão do controller/InheritedElement no Android OK',
      );
    },
  );
}
