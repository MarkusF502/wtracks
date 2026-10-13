import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/song_section.dart';
import 'package:flutter_app/screens/performance_screen.dart';
import 'harness/harness_support.dart';
import 'harness/screens_harness_test.dart' show pumpScreen, portrait, landscape, unmount, loadRealFonts;

void main() {
  setUpAll(loadRealFonts);
  setUp(mockBackgroundChannel);

  final song = sampleTrack(id: 'song').copyWith(sections: const [
    SongSection(id: 'v', name: 'Verso 1', startSeconds: 0, endSeconds: 90),
    SongSection(id: 'r', name: 'Refrão', startSeconds: 90, endSeconds: 180, loopCount: 3),
  ]);

  for (final (label, size) in [('retrato', portrait), ('paisagem', landscape)]) {
    testWidgets('section badges, section loop and the loop column reach the engine ($label)', (tester) async {
      final engine = FakeEngine()..position = 100;
      await pumpScreen(tester, const PerformanceScreen(), size: size, engine: engine, loaded: song);
      expect(find.text('V1'), findsOneWidget);
      expect(find.text('R'), findsWidgets);

      // Laço da seção sob a agulha com as repetições dela; tocar de novo desliga.
      await tester.tap(find.byTooltip('Repetir seção atual'));
      await tester.pump(const Duration(milliseconds: 200));
      expect(engine.calls, contains('loop(90.0,180.0,true,x3)'));
      await tester.tap(find.byTooltip('Desativar loop').first);
      await tester.pump(const Duration(milliseconds: 200));
      expect(engine.loopEnabled, false);

      // Laço infinito: repete até soltar.
      await tester.tap(find.byTooltip('Laço infinito na seção atual'));
      await tester.pump(const Duration(milliseconds: 200));
      expect(engine.calls.last, 'loop(90.0,180.0,true)');

      // Ícone de laço no waveform: liga o laço daquela seção.
      await tester.tap(find.byTooltip('Repetir Verso 1'));
      await tester.pump(const Duration(milliseconds: 200));
      expect(engine.calls.last, 'loop(0.0,90.0,true)');
      expect(tester.takeException(), isNull);
      await unmount(tester);
    });
  }
}
