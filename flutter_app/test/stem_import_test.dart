import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/file_import_service.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/screens/import_screen.dart';
import 'package:flutter_app/services/stem_detection.dart';
import 'harness/harness_support.dart';

class _FakePicker extends FileImportService {
  List<String> next = [];
  @override
  Future<List<String>> pickAndImportChannelFiles() async => next;
}

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  mockBackgroundChannel();

  group('detecting stems by file name', () {
    String label(String name) => guessStem('/cache/1/$name').label;

    test('click and guide are recognised in several spellings, in Portuguese and English', () {
      for (final name in ['Click.wav', '01 Click.wav', 'CLICK TRACK.aif', 'metronome.wav', 'Metrônomo.wav', '03_Met.flac']) {
        final guess = guessStem(name);
        expect((guess.label, guess.isClickOrGuide, guess.rank), ('Click', true, 0), reason: name);
      }
      for (final name in ['Guia.wav', 'Guide.wav', 'GUIA-VOZ.aiff', 'Cues.wav', 'Voice guide.wav']) {
        final guess = guessStem(name);
        expect((guess.label, guess.isClickOrGuide, guess.rank), ('Guia', true, 1), reason: name);
      }
    });

    test('common instruments get friendly names; unknown names are kept', () {
      expect(label('Drums.wav'), 'Bateria');
      expect(label('02 - Bass DI.wav'), 'Baixo');
      expect(label('Keys 1.wav'), 'Teclas');
      expect(label('Piano.wav'), 'Teclas');
      expect(label('Ambient Pad.wav'), 'Pad');
      expect(label('Lead Guitar.wav'), 'Guitarra');
      expect(label('Acoustic.wav'), 'Violão');
      expect(label('BVs.wav'), 'Backing vocal');
      expect(label('Lead Vocal.wav'), 'Voz');
      expect(label('Voz Ref.wav'), 'Voz');
      expect(label('Strings.wav'), 'Cordas/Sopros');
      expect(label('Theremin Solo.wav'), 'Theremin Solo');
      expect(label('07 Hammond B3.wav'), 'Hammond B3');
    });

    test('the number in front of the file name and the folder do not matter; only audio extensions count', () {
      expect(stemBaseName('/a/b/12_Drums.wav'), 'Drums');
      expect(stemBaseName(r'C:\x\Drums.WAV'), 'Drums');
      expect(stemBaseName('/a/Notes.txt'), 'Notes.txt');
      expect(isImportableAudio('x.AIFF'), true);
      expect(isImportableAudio('x.flac'), true);
      expect(isImportableAudio('x.mp3'), false);
      expect(isImportableAudio('x.txt'), false);
    });

    test('order puts click then guide first and keeps the rest stable; repeated names get numbers', () {
      final guesses = ['Bass.wav', 'Drums.wav', 'Guia.wav', 'Click.wav', 'Keys.wav'].map(guessStem).toList();
      expect(suggestedOrder(guesses), [3, 2, 0, 1, 4]);
      expect(uniqueLabels(['Guitarra', 'Voz', 'Guitarra', 'Guitarra']), ['Guitarra', 'Voz', 'Guitarra 2', 'Guitarra 3']);
    });
  });

  group('import screen', () {
    Future<(ProviderContainer, _FakePicker, FakeEngine)> open(WidgetTester tester) async {
      tester.view.physicalSize = const Size(600, 1400);
      tester.view.devicePixelRatio = 1;
      addTearDown(tester.view.resetPhysicalSize);
      addTearDown(tester.view.resetDevicePixelRatio);
      final picker = _FakePicker();
      final engine = FakeEngine();
      final c = ProviderContainer(overrides: [
        engineProvider.overrideWithValue(engine),
        fileImportServiceProvider.overrideWithValue(picker),
        persistenceServiceProvider.overrideWithValue(InMemoryPersistence()),
      ]);
      addTearDown(c.dispose);
      await tester.pumpWidget(UncontrolledProviderScope(
        container: c,
        child: MaterialApp(home: Builder(builder: (context) => Scaffold(body: Center(child: FilledButton(onPressed: () => Navigator.of(context).push(MaterialPageRoute<void>(builder: (_) => const ImportScreen())), child: const Text('open')))))),
      ));
      await tester.tap(find.text('open'));
      await tester.pumpAndSettle();
      return (c, picker, engine);
    }

    testWidgets('a song with 12 files imports 12 channels: click and guide first, instruments named, order kept', (tester) async {
      final (c, picker, engine) = await open(tester);
      picker.next = [
        for (final name in ['Drums', 'Bass', 'Keys', 'Pad', 'Guitar', 'Guitar 2', 'Acoustic', 'BVs', 'Lead Vocal', 'Strings', 'Guia', 'Click'])
          '/cache/${name.replaceAll(' ', '_')}.wav',
      ];
      await tester.tap(find.byKey(const Key('add-files')));
      await tester.pumpAndSettle();
      expect(find.text('0/64 canais'), findsNothing);
      expect(find.text('12/64 canais'), findsOneWidget);
      await tester.tap(find.byKey(const Key('finalize-import')));
      await tester.pumpAndSettle();
      final track = c.read(currentTrackProvider)!;
      expect(track.channels.map((ch) => ch.label), ['Click', 'Guia', 'Bateria', 'Baixo', 'Teclas', 'Pad', 'Guitarra', 'Guitarra 2', 'Violão', 'Backing vocal', 'Voz', 'Cordas/Sopros']);
      expect(track.channels.take(2).every((ch) => ch.isClickOrGuide), true);
      expect(track.channels.skip(2).any((ch) => ch.isClickOrGuide), false);
      expect(engine.loadedPaths.single.length, 12);
      expect(engine.loadedPaths.single.first, endsWith('Click.wav'));
      await tester.pumpWidget(const SizedBox.shrink());
      c.dispose();
    });

    testWidgets('rename, switch click/guide, remove and reorder before importing', (tester) async {
      final (c, picker, _) = await open(tester);
      picker.next = ['/cache/Drums.wav', '/cache/Bass.wav', '/cache/Click.wav', '/cache/readme.txt'];
      await tester.tap(find.byKey(const Key('add-files')));
      await tester.pumpAndSettle();
      expect(find.textContaining('1 arquivo ignorado'), findsOneWidget);
      expect(find.text('3/64 canais'), findsOneWidget);

      await tester.tap(find.byKey(const Key('stem-label-1'))); // Bateria
      await tester.pumpAndSettle();
      await tester.enterText(find.byKey(const Key('stem-name')), 'Bateria ao vivo');
      await tester.tap(find.text('OK'));
      await tester.pumpAndSettle();
      await tester.tap(find.byKey(const Key('stem-click-1'))); // mark as click/guide by hand
      await tester.tap(find.byKey(const Key('stem-remove-2'))); // Baixo
      await tester.pumpAndSettle();
      expect(find.text('2/64 canais'), findsOneWidget);
      await tester.tap(find.byKey(const Key('finalize-import')));
      await tester.pumpAndSettle();
      final track = c.read(currentTrackProvider)!;
      expect(track.channels.map((ch) => (ch.label, ch.isClickOrGuide)), [('Click', true), ('Bateria ao vivo', true)]);
      await tester.pumpWidget(const SizedBox.shrink());
      c.dispose();
    });

    testWidgets('a second pick adds to the list and the limit of 64 channels is explained', (tester) async {
      final (_, picker, _) = await open(tester);
      picker.next = [for (var i = 0; i < 60; i++) '/cache/Stem $i.wav'];
      await tester.tap(find.byKey(const Key('add-files')));
      await tester.pumpAndSettle();
      picker.next = [for (var i = 0; i < 10; i++) '/cache/More $i.wav'];
      await tester.tap(find.byKey(const Key('add-files')));
      await tester.pumpAndSettle();
      expect(find.text('64/64 canais'), findsOneWidget);
      expect(find.textContaining('6 fora do limite'), findsOneWidget);
      expect(tester.widget<FilledButton>(find.byKey(const Key('add-files'))).onPressed, isNull);
    });
  });
}
