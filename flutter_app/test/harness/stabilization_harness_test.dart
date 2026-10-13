import 'dart:async';
import 'dart:convert';
import 'dart:io';

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/main.dart';
import 'package:flutter_app/models/engine_error.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/providers/setlist_provider.dart';
import 'package:flutter_app/providers/waveform_provider.dart';
import 'package:flutter_app/screens/performance_screen.dart';
import 'package:flutter_app/screens/library_screen.dart';
import 'screens_harness_test.dart' show loadRealFonts;
import 'package:flutter_app/services/persistence_service.dart';

import 'harness_support.dart';

class DelayedEngine extends FakeEngine {
  final loads = <String, Completer<bool>>{};
  final started = <String>[];
  String? nativeTrack;
  @override
  void unloadTrack() {
    nativeTrack = null;
    super.unloadTrack();
  }

  @override
  Future<bool> loadTrackAsync(String id, List<String> paths) async {
    started.add(id);
    final result = await (loads[id] ??= Completer<bool>()).future;
    if (result) nativeTrack = id;
    return result;
  }
}

class WaveEngine extends FakeEngine {
  final extraction = Completer<List<double>?>();
  int extractions = 0;
  @override
  Future<List<double>?> generateWaveformPeaksAsync(List<String> paths) {
    extractions++;
    return extraction.future;
  }
}

class WavePersistence extends InMemoryPersistence {
  final cache = <String, List<double>>{};
  @override
  Future<List<double>?> loadWaveformPeaks(String id) async => cache[id];
  @override
  Future<void> saveWaveformPeaks(String id, List<double> peaks) async =>
      cache[id] = peaks;
  @override
  Future<void> deleteWaveformPeaks(String id) async => cache.remove(id);
}

ProviderContainer container(
  FakeEngine engine, [
  PersistenceService? persistence,
  bool autoDispose = true,
]) {
  final c = ProviderContainer(
    overrides: [
      engineProvider.overrideWithValue(engine),
      persistenceServiceProvider.overrideWithValue(
        persistence ?? InMemoryPersistence(),
      ),
    ],
  );
  if (autoDispose) addTearDown(c.dispose);
  return c;
}

Future<void> tick() => Future<void>.delayed(const Duration(milliseconds: 10));

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  setUp(mockBackgroundChannel);
  setUpAll(loadRealFonts);

  test('erros do ABI têm tradução e código desconhecido tem fallback', () {
    expect(engineErrorCodeFromInt(1), EngineErrorCode.fileUnreadable);
    expect(engineErrorCodeFromInt(2), EngineErrorCode.formatMismatch);
    expect(engineErrorCodeFromInt(3), EngineErrorCode.deviceInitFailed);
    expect(engineErrorCodeFromInt(99), EngineErrorCode.unknown);
    expect(engineErrorCodeFromInt(-1), EngineErrorCode.unknown);
    expect(
      engineErrorMessage(EngineErrorCode.fileUnreadable),
      contains('ler o áudio'),
    );
    expect(
      engineErrorMessage(EngineErrorCode.formatMismatch),
      contains('mesma taxa'),
    );
    expect(
      engineErrorMessage(EngineErrorCode.deviceInitFailed),
      contains('iniciar o áudio'),
    );
    for (final code in EngineErrorCode.values) {
      expect(engineErrorMessage(code), isNotEmpty);
    }
  });

  test(
    'loads concorrentes: antigo lento não publica; nativo e UI ficam no novo',
    () async {
      final engine = DelayedEngine();
      final c = container(engine);
      final notifier = c.read(currentTrackProvider.notifier);
      final first = notifier.load(sampleTrack(id: 'old'));
      await tick();
      final second = notifier.load(sampleTrack(id: 'new'));
      engine.loads['new'] = Completer<bool>()
        ..complete(true); // novo já pronto, antigo atrasado
      await tick();
      expect(engine.started, ['old']); // impedir swap nativo fora de ordem
      engine.loads['old']!.complete(true);
      expect(await first, isFalse);
      expect(await second, isTrue);
      expect(engine.nativeTrack, 'new');
      expect(c.read(currentTrackProvider)?.id, 'new');
      expect(engine.calls.where((s) => s.startsWith('bpm(')).length, 1);
    },
  );

  test(
    'load antigo bem-sucedido seguido de falha não deixa UI e engine divergentes',
    () async {
      final engine = DelayedEngine();
      final c = container(engine);
      final n = c.read(currentTrackProvider.notifier);
      n.setLoadedTrack(sampleTrack(id: 'previous'));
      final old = n.load(sampleTrack(id: 'old'));
      await tick();
      final newest = n.load(sampleTrack(id: 'bad'));
      engine.loads['bad'] = Completer<bool>()..complete(false);
      engine.loads['old']!.complete(true);
      expect(await old, false);
      expect(await newest, false);
      expect(c.read(currentTrackProvider), isNull);
      expect(engine.nativeTrack, isNull);
    },
  );

  test('unload espera load pendente e invalida seu resultado', () async {
    final engine = DelayedEngine();
    final c = container(engine);
    final n = c.read(currentTrackProvider.notifier);
    final load = n.load(sampleTrack());
    await tick();
    final unload = n.unload();
    engine.loads['t1']!.complete(true);
    expect(await load, false);
    await unload;
    expect(c.read(currentTrackProvider), isNull);
    expect(engine.calls.last, 'unload');
  });

  for (final failure in [
    MissingPluginException(),
    PlatformException(code: 'unavailable'),
  ]) {
    test('background $failure não interrompe play/pause/stop', () async {
      TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
          .setMockMethodCallHandler(
            const MethodChannel('wtracks/background'),
            (_) async => throw failure,
          );
      final engine = FakeEngine();
      final c = container(engine);
      final transport = c.read(transportProvider.notifier);
      await transport.play();
      expect(engine.playing, true);
      await transport.pause();
      expect(engine.playing, false);
      await transport.stop();
    });
  }

  test(
    'pause e fim natural encerram notificação inclusive música curta',
    () async {
      final calls = mockBackgroundChannel();
      final engine = FakeEngine();
      final c = container(engine);
      final n = c.read(transportProvider.notifier);
      await n.play();
      await n.pause();
      expect(calls.last.method, 'stop');
      await n.play();
      engine.playing = false;
      await Future<void>.delayed(const Duration(milliseconds: 150));
      expect(calls.map((c) => c.method), [
        'requestNotificationPermission',
        'start',
        'stop',
        'requestNotificationPermission',
        'start',
        'stop',
      ]);
    },
  );

  test('stop durante permissão pendente impede play tardio', () async {
    final permission = Completer<void>();
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(const MethodChannel('wtracks/background'), (
          call,
        ) async {
          if (call.method == 'requestNotificationPermission') {
            await permission.future;
          }
          return null;
        });
    final engine = FakeEngine();
    final c = container(engine);
    final n = c.read(transportProvider.notifier);
    final play = n.play();
    final stop = n.stop();
    permission.complete();
    await Future.wait([play, stop]);
    expect(engine.calls, isNot(contains('play')));
  });

  test(
    'deletar música carregada remove referências, editor e engine',
    () async {
      final track = sampleTrack();
      final other = sampleTrack(id: 'other');
      final persistence = InMemoryPersistence(
        initialTracks: [track, other],
        initialSetlists: [
          Setlist(id: 's1', name: 'A', tracks: [track, other]),
          Setlist(id: 's2', name: 'B', tracks: [track]),
        ],
      );
      final engine = FakeEngine();
      final c = container(engine, persistence);
      await c.read(trackLibraryProvider.notifier).refresh();
      await c.read(setlistEditorProvider.notifier).open('s1');
      c.read(currentTrackProvider.notifier).setLoadedTrack(track);
      await c.read(trackLibraryProvider.notifier).deleteTrack(track.id);
      expect(c.read(currentTrackProvider), isNull);
      expect(engine.calls, containsAllInOrder(['stop', 'unload']));
      expect(persistence.setlists['s1']!.tracks.map((t) => t.id), ['other']);
      expect(persistence.setlists['s2']!.tracks, isEmpty);
      expect(c.read(setlistEditorProvider)!.tracks.map((t) => t.id), ['other']);
      expect(
        c.read(setlistLibraryProvider).expand((s) => s.tracks).map((t) => t.id),
        ['other'],
      );
    },
  );

  test('JSON atômico: concorrência, tmp incompleto e cache excluído', () async {
    final dir = Directory.systemTemp.createTempSync('wtracks_atomic_');
    addTearDown(() => dir.deleteSync(recursive: true));
    final persistence = PersistenceService(
      rootDirectoryResolver: () async => dir,
    );
    final track = sampleTrack(channels: 0);
    await persistence.saveTrack(track);
    final setlist = Setlist(id: 's', name: 'original', tracks: [track]);
    await persistence.saveSetlist(setlist);
    await persistence.saveWaveformPeaks(track.id, [0.1, 1]);
    await File(
      '${dir.path}/wtracks_data/tracks/t1.json.tmp',
    ).writeAsString('{broken');
    expect((await persistence.loadAllTracks()).single.id, track.id);
    await persistence.saveTrack(track.copyWith(title: 'atualizada'));
    await Future.wait(
      List.generate(
        15,
        (i) => persistence.saveSetlist(setlist.copyWith(name: '$i')),
      ),
    );
    expect((await persistence.loadSetlist('s'))!.name, '14');
    expect((await persistence.loadTrack('t1'))!.title, 'atualizada');
    final files = dir.listSync(recursive: true).whereType<File>();
    expect(files.where((f) => f.path.endsWith('.tmp')), isEmpty);
    for (final file in files.where((f) => f.path.endsWith('.json'))) {
      expect(jsonDecode(file.readAsStringSync()), isA<Map>());
    }
    await persistence.deleteTrack('t1');
    expect(await persistence.loadWaveformPeaks('t1'), isNull);
  });

  test(
    'waveform: geração, cache imediato e exclusão durante extração',
    () async {
      final engine = WaveEngine();
      final persistence = WavePersistence();
      final c = container(engine, persistence);
      final n = c.read(waveformProvider.notifier);
      final pending = n.loadFor(sampleTrack());
      await tick();
      expect(c.read(waveformProvider).isGenerating, true);
      engine.extraction.complete([0.2, 1]);
      await pending;
      expect(persistence.cache['t1'], [0.2, 1]);
      await n.loadFor(sampleTrack());
      expect(engine.extractions, 1);
      expect(c.read(waveformProvider).peaks, [0.2, 1]);
    },
  );

  test(
    'waveform: falha volta ao slider e exclusão impede recriar cache',
    () async {
      final engine = WaveEngine();
      final persistence = WavePersistence();
      final c = container(engine, persistence);
      final n = c.read(waveformProvider.notifier);
      final pending = n.loadFor(sampleTrack());
      await tick();
      final forget = n.forget('t1');
      engine.extraction.complete([1]);
      await Future.wait([pending, forget]);
      expect(persistence.cache, isEmpty);
      expect(c.read(waveformProvider).peaks, isNull);
      final failing = WaveEngine();
      final c2 = container(failing);
      final failed = c2.read(waveformProvider.notifier).loadFor(sampleTrack());
      await tick();
      failing.extraction.completeError(StateError('extract failed'));
      await failed;
      expect(c2.read(waveformProvider).isGenerating, false);
      expect(c2.read(waveformProvider).peaks, isNull);
    },
  );

  testWidgets('aviso de falha de inicialização visível', (tester) async {
    final c = container(FakeEngine()..ready = false);
    await tester.pumpWidget(
      UncontrolledProviderScope(container: c, child: const WTracksApp()),
    );
    await tester.pump();
    expect(
      find.text(engineErrorMessage(EngineErrorCode.deviceInitFailed)),
      findsOneWidget,
    );
    await tester.pumpWidget(const SizedBox());
    c.dispose(); // a performance (tela inicial) liga o polling da entrada MIDI mapeada
  });

  testWidgets('trocar track na performance e sair durante waveform não lança', (
    tester,
  ) async {
    final engine = WaveEngine();
    final c = container(engine, null, false);
    c.read(currentTrackProvider.notifier).setLoadedTrack(sampleTrack());
    await tester.pumpWidget(
      UncontrolledProviderScope(
        container: c,
        child: const MaterialApp(home: PerformanceScreen()),
      ),
    );
    await tester.pump();
    c
        .read(currentTrackProvider.notifier)
        .setLoadedTrack(sampleTrack(id: 'new'));
    await tester.pump();
    expect(tester.takeException(), isNull);
    await tester.pumpWidget(const SizedBox());
    engine.extraction.complete([1]);
    await tester.pump();
    c.dispose();
    expect(tester.takeException(), isNull);
  });
  testWidgets('excluir exige confirmação e informa número de setlists', (
    tester,
  ) async {
    final track = sampleTrack();
    final persistence = InMemoryPersistence(
      initialTracks: [track],
      initialSetlists: [
        Setlist(id: 'a', name: 'A', tracks: [track]),
        Setlist(id: 'b', name: 'B', tracks: [track]),
      ],
    );
    final c = container(FakeEngine(), persistence, false);
    await tester.pumpWidget(
      UncontrolledProviderScope(
        container: c,
        child: const MaterialApp(home: LibraryScreen()),
      ),
    );
    await tester.pumpAndSettle();
    await tester.tap(find.byTooltip('Opções da música'));
    await tester.pumpAndSettle();
    await tester.tap(find.text('Excluir'));
    await tester.pumpAndSettle();
    expect(find.textContaining('2 setlist(s)'), findsOneWidget);
    await tester.tap(find.text('Cancelar'));
    await tester.pumpAndSettle();
    expect(persistence.tracks, contains('t1'));
    await tester.tap(find.byTooltip('Opções da música'));
    await tester.pumpAndSettle();
    await tester.tap(find.text('Excluir'));
    await tester.pumpAndSettle();
    await tester.tap(find.text('Excluir'));
    await tester.pumpAndSettle();
    expect(persistence.tracks, isEmpty);
    await tester.pumpWidget(const SizedBox());
    c.dispose();
  });

  for (final cached in [false, true]) {
    testWidgets(
      'seek por toque na waveform ${cached ? 'com picos' : 'sem picos (falha na extração)'}',
      (tester) async {
        final persistence = WavePersistence();
        if (cached) persistence.cache['t1'] = [0.1, 1, 0.2];
        final engine = FakeEngine()..length = 100;
        final c = container(engine, persistence, false);
        c.read(currentTrackProvider.notifier).setLoadedTrack(sampleTrack());
        await tester.pumpWidget(
          UncontrolledProviderScope(
            container: c,
            child: const MaterialApp(home: PerformanceScreen()),
          ),
        );
        await tester.pump(const Duration(milliseconds: 200));
        // A waveform rola sob a agulha: arrastar só move a vista, tocar busca o ponto.
        final waveform = find.byWidgetPredicate(
          (w) =>
              w is GestureDetector &&
              w.onTapDown != null &&
              w.onHorizontalDragUpdate != null,
        );
        await tester.drag(waveform, const Offset(-80, 0));
        expect(engine.calls.where((s) => s.startsWith('seek(')), isEmpty);
        await tester.tap(waveform);
        expect(engine.calls.where((s) => s.startsWith('seek(')), isNotEmpty);
        expect(tester.takeException(), isNull);
        await tester.pumpWidget(const SizedBox());
        c.dispose();
      },
    );
  }

  testWidgets(
    'renomear após desmontar a biblioteca não acessa ref descartado',
    (tester) async {
      final track = sampleTrack();
      final persistence = InMemoryPersistence(initialTracks: [track]);
      final c = container(FakeEngine(), persistence, false);
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
      await tester.pumpAndSettle();
      final context = tester.element(find.byType(LibraryScreen));
      final navigator = Navigator.of(context);
      final route = ModalRoute.of(context)!;
      await tester.longPress(find.text(track.title));
      await tester.pumpAndSettle();
      await tester.enterText(find.byType(TextField), 'Outro nome');
      navigator.removeRoute(route);
      await tester.pump();
      await tester.tap(find.text('Salvar'));
      await tester.pumpAndSettle();
      expect(tester.takeException(), isNull);
      expect(persistence.tracks[track.id]!.title, track.title);
      await tester.pumpWidget(const SizedBox());
      c.dispose();
    },
  );
}
