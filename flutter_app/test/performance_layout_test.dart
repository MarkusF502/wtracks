import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/models/song_section.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/screens/performance_screen.dart';
import 'harness/harness_support.dart';
import 'harness/screens_harness_test.dart' show pumpScreen, portrait, landscape, unmount, loadRealFonts;

Future<void> _settle(WidgetTester tester) async {
  for (var i = 0; i < 6; i++) {
    await tester.pump(const Duration(milliseconds: 100));
  }
}

void main() {
  setUpAll(loadRealFonts);
  setUp(mockBackgroundChannel);

  final song = sampleTrack(id: 'song').copyWith(sections: const [
    SongSection(id: 'v', name: 'Verso 1', startSeconds: 0, endSeconds: 90),
    SongSection(id: 'r', name: 'Refrão', startSeconds: 90, endSeconds: 180, loopCount: 3),
  ]);

  for (final (label, size) in [('retrato', portrait), ('paisagem', landscape)]) {
    testWidgets('section loop on the waveform, console loops and MUTE MIDI reach the engine ($label)', (tester) async {
      final engine = FakeEngine()..position = 100;
      final c = await pumpScreen(tester, const PerformanceScreen(), size: size, engine: engine, loaded: song);
      expect(find.text('R'), findsOneWidget); // selo da seção sob a agulha

      // Ícone de laço da seção: uma repetição (duas passagens); de novo desliga.
      await tester.tap(find.byTooltip('Repetir Refrão'));
      await _settle(tester);
      expect(engine.calls.last, 'loop(90.0,180.0,true,x2)');
      await tester.tap(find.byTooltip('Repetir Refrão'));
      await _settle(tester);
      expect(engine.loopEnabled, false);

      // Console: laço infinito e laço de uma repetição na seção atual.
      await tester.tap(find.byTooltip('Laço infinito na seção atual'));
      await _settle(tester);
      expect(engine.calls.last, 'loop(90.0,180.0,true)');
      await tester.tap(find.byTooltip('Desativar loop'));
      await _settle(tester);
      await tester.tap(find.byTooltip('Repetir seção atual'));
      await _settle(tester);
      expect(engine.calls.last, 'loop(90.0,180.0,true,x2)');

      await tester.tap(find.byTooltip('Silenciar gatilhos MIDI'));
      await _settle(tester);
      expect(engine.midiCuesMuted, true);
      expect(c.read(midiCuesMutedProvider), true);

      // Modo de edição: o ícone de laço liga o laço infinito predefinido da seção.
      await tester.tap(find.byTooltip('Editar (segure para outros modos)'));
      await _settle(tester);
      await tester.tap(find.byTooltip('Laço infinito predefinido: Refrão'));
      await _settle(tester);
      expect(c.read(currentTrackProvider)!.sections[1].presetInfiniteLoop, true);
      expect(tester.takeException(), isNull);
      await unmount(tester);
    });
  }

  testWidgets('setlist edit mode removes a song and the song menu opens from the card', (tester) async {
    final engine = FakeEngine();
    final tracks = [sampleTrack(id: 'a', title: 'Primeira'), sampleTrack(id: 'b', title: 'Segunda'), sampleTrack(id: 'c', title: 'Terceira')];
    final c = await pumpScreen(tester, const PerformanceScreen(), size: const Size(1180, 820), engine: engine, loaded: tracks[0]);
    c.read(setlistSessionProvider.notifier).begin(Setlist(id: 's', name: 'Domingo', tracks: tracks), 0);
    await _settle(tester);
    expect(find.text('Terceira (G)'), findsOneWidget);
    await tester.tap(find.byTooltip('Editar (segure para outros modos)'));
    await _settle(tester);
    await tester.tap(find.byTooltip('Remover da setlist').last);
    await _settle(tester);
    expect(c.read(setlistSessionProvider)!.setlist.tracks.map((t) => t.id), ['a', 'b']);
    expect(find.text('Terceira (G)'), findsNothing);
    await tester.tap(find.byTooltip('Editar música').last);
    await _settle(tester);
    expect(find.text('TOM E ANDAMENTO'), findsOneWidget);
    expect(tester.takeException(), isNull);
    await unmount(tester);
  });
}
