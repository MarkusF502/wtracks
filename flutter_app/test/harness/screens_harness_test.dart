import 'dart:io';

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/screens/import_screen.dart';
import 'package:flutter_app/screens/library_screen.dart';
import 'package:flutter_app/screens/performance_screen.dart';
import 'package:flutter_app/screens/setlist_editor_screen.dart';
import 'package:flutter_app/screens/setlists_screen.dart';
import 'package:flutter_app/screens/track_picker_screen.dart';

import 'harness_support.dart';

/// Tamanhos lógicos de um celular comum (iPhone 14 / Pixel 7 ~ 390x844).
const portrait = Size(390, 844);
const landscape = Size(844, 390);
/// Alto o bastante pra o bottom sheet de BPM caber -- usado nos testes que
/// verificam a LÓGICA do diálogo, isolando-a do bug de layout [D3].
const tall = Size(390, 1400);

/// Carrega a Roboto real do cache do SDK: a fonte padrão dos testes
/// (FlutterTest) desenha cada glifo como um quadrado de 1em e gera falsos
/// overflows horizontais.
Future<void> loadRealFonts() async {
  final dir = '${Platform.environment['FLUTTER_ROOT'] ?? '${Platform.environment['HOME']}/development/flutter'}'
      '/bin/cache/artifacts/material_fonts';
  final loader = FontLoader('Roboto');
  for (final f in ['Roboto-Regular.ttf', 'Roboto-Medium.ttf', 'Roboto-Bold.ttf']) {
    final file = File('$dir/$f');
    if (file.existsSync()) loader.addFont(Future.value(ByteData.sublistView(file.readAsBytesSync())));
  }
  await loader.load();
}

final tracks = [
  sampleTrack(id: 't1', title: 'Grande é o Senhor'),
  sampleTrack(id: 't2', title: 'Uma música com um título muito comprido pra testar ellipsis', channels: 8),
];
final setlist = Setlist(id: 's1', name: 'Culto domingo', tracks: tracks);

Future<ProviderContainer> pumpScreen(
  WidgetTester tester,
  Widget screen, {
  required Size size,
  FakeEngine? engine,
  Track? loaded,
}) async {
  tester.view.physicalSize = size;
  tester.view.devicePixelRatio = 1.0;
  addTearDown(tester.view.reset);

  final container = ProviderContainer(overrides: [
    engineProvider.overrideWithValue(engine ?? FakeEngine()),
    persistenceServiceProvider.overrideWithValue(
        InMemoryPersistence(initialTracks: tracks, initialSetlists: [setlist])),
  ]);
  _current = container;
  if (loaded != null) container.read(currentTrackProvider.notifier).setLoadedTrack(loaded);

  await tester.pumpWidget(UncontrolledProviderScope(
    container: container,
    child: MaterialApp(theme: ThemeData.dark(useMaterial3: true), home: screen),
  ));
  // Sem pumpAndSettle: o polling de 100ms do transporte nunca "assenta".
  for (var i = 0; i < 5; i++) {
    await tester.pump(const Duration(milliseconds: 100));
  }
  return container;
}

/// Avança frames suficientes pra animações (ex: bottom sheet) terminarem.
Future<void> settle(WidgetTester tester) async {
  for (var i = 0; i < 10; i++) {
    await tester.pump(const Duration(milliseconds: 50));
  }
}

ProviderContainer? _current;

/// Desmonta a árvore e descarta o container (cancela o Timer periódico do
/// transporte antes da checagem de timers pendentes do testWidgets).
Future<void> unmount(WidgetTester tester) async {
  await tester.pumpWidget(const SizedBox());
  _current?.dispose();
  _current = null;
}

void main() {
  setUpAll(loadRealFonts);
  setUp(mockBackgroundChannel);

  final screens = <String, Widget Function()>{
    'LibraryScreen': () => const LibraryScreen(),
    'SetlistsScreen': () => const SetlistsScreen(),
    'SetlistEditorScreen': () => const SetlistEditorScreen(setlistId: 's1'),
    'TrackPickerScreen': () => const TrackPickerScreen(initiallySelectedIds: {'t1'}),
    'ImportScreen': () => const ImportScreen(),
    'PerformanceScreen': () => const PerformanceScreen(),
  };

  group('Smoke: todas as telas renderizam sem exceção/overflow', () {
    for (final entry in screens.entries) {
      for (final (label, size) in [('retrato', portrait), ('paisagem', landscape)]) {
        testWidgets('${entry.key} em $label', (tester) async {
          await pumpScreen(tester, entry.value(), size: size, loaded: tracks[1]);
          expect(tester.takeException(), isNull);
          await unmount(tester);
        });
      }
    }
  });

  group('PerformanceScreen: transporte e mixer', () {
    testWidgets('play/stop chegam ao engine e iniciam/param o serviço de background',
        (tester) async {
      final engine = FakeEngine();
      final bg = mockBackgroundChannel();
      await pumpScreen(tester, const PerformanceScreen(), size: portrait, engine: engine, loaded: tracks[0]);

      await tester.tap(find.byIcon(Icons.play_arrow));
      await tester.pump(const Duration(milliseconds: 200));
      expect(engine.calls, contains('play'));
      expect(find.byIcon(Icons.pause), findsOneWidget);

      await tester.tap(find.byIcon(Icons.stop));
      await tester.pump(const Duration(milliseconds: 200));
      expect(engine.calls, contains('stop'));
      expect(bg.map((c) => c.method), ['start', 'stop']);
      await unmount(tester);
    });

    testWidgets('botão S (solo) do mixer muta os outros canais no engine', (tester) async {
      final engine = FakeEngine();
      await pumpScreen(tester, const PerformanceScreen(), size: portrait, engine: engine, loaded: tracks[0]);

      await tester.tap(find.text('S').first);
      await tester.pump(const Duration(milliseconds: 100));
      expect(engine.calls, containsAll(['muted(0,false)', 'muted(1,true)', 'muted(2,true)', 'muted(3,true)']));
      await unmount(tester);
    });
  });

  group('PerformanceScreen: diálogo de BPM/offset', () {
    testWidgets('[D2] "Marcar 1º tempo" atualiza o offset exibido no diálogo', (tester) async {
      final engine = FakeEngine()
        ..playing = true
        ..position = 1.25;
      await pumpScreen(tester, const PerformanceScreen(), size: tall, engine: engine, loaded: tracks[0]);

      await tester.tap(find.text('BPM'));
      await settle(tester);
      expect(find.text('+0.00s'), findsOneWidget);

      await tester.tap(find.text('Marcar 1º tempo'));
      await tester.pump(const Duration(milliseconds: 200));

      expect(engine.calls, contains('offset(1.25)'), reason: 'o engine recebe o offset...');
      expect(find.text('+1.25s'), findsOneWidget, reason: '...mas o diálogo continua mostrando o valor antigo');
      await unmount(tester);
    });

    for (final (label, size) in [
      ('retrato 390x844', portrait),
      ('retrato compacto 360x640', const Size(360, 640)),
      ('paisagem 844x390', landscape),
    ]) {
      testWidgets('[D3] diálogo de BPM cabe na tela em $label (sem overflow)', (tester) async {
        await pumpScreen(tester, const PerformanceScreen(), size: size, loaded: tracks[0]);

        await tester.tap(find.text('BPM'));
        await settle(tester);

        expect(tester.takeException(), isNull);
        await unmount(tester);
      });
    }

    testWidgets('TAP tempo calibra o BPM e marca como calibrado', (tester) async {
      final engine = FakeEngine();
      final c = await pumpScreen(tester, const PerformanceScreen(),
          size: tall, engine: engine, loaded: tracks[0]);

      await tester.tap(find.text('BPM'));
      await settle(tester);
      // Toques reais via DateTime.now(): basta que dois toques gerem um BPM
      // dentro do range aceito.
      await tester.tap(find.text('TAP'));
      await tester.runAsync(() => Future<void>.delayed(const Duration(milliseconds: 500)));
      await tester.tap(find.text('TAP'));
      await tester.pump(const Duration(milliseconds: 100));

      final click = c.read(currentTrackProvider)!.clickSettings;
      expect(click.calibrated, isTrue);
      expect(click.bpm, inInclusiveRange(40, 240));
      expect(engine.calls.where((e) => e.startsWith('bpm(')), isNotEmpty);
      await unmount(tester);
    });
  });
}
