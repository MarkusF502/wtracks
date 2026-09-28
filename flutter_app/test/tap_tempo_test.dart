import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/utils/tap_tempo.dart';

void main() {
  group('TapTempoCalculator', () {
    test('toque isolado retorna null', () {
      final calc = TapTempoCalculator();
      final now = DateTime(2026, 1, 1, 12, 0, 0);
      expect(calc.registerTap(now), isNull);
      expect(calc.tapCount, 1);
    });

    test('2 toques com intervalo conhecido geram o BPM correto', () {
      final calc = TapTempoCalculator();
      final t0 = DateTime(2026, 1, 1, 12, 0, 0);
      // 500ms de intervalo == 120 BPM
      final t1 = t0.add(const Duration(milliseconds: 500));

      calc.registerTap(t0);
      final bpm = calc.registerTap(t1);

      expect(bpm, closeTo(120.0, 0.001));
    });

    test('sequência com gap > 2s no meio reinicia a contagem', () {
      final calc = TapTempoCalculator();
      final t0 = DateTime(2026, 1, 1, 12, 0, 0);
      final t1 = t0.add(const Duration(milliseconds: 400)); // ~150 BPM

      calc.registerTap(t0);
      calc.registerTap(t1);

      // Gap grande -> reinicia
      final t2 = t1.add(const Duration(seconds: 3));
      final afterGap = calc.registerTap(t2);
      expect(afterGap, isNull); // só 1 toque na nova sequência
      expect(calc.tapCount, 1);

      // Novo intervalo de 500ms -> 120 BPM, refletindo só os toques
      // depois do gap.
      final t3 = t2.add(const Duration(milliseconds: 500));
      final bpm = calc.registerTap(t3);
      expect(bpm, closeTo(120.0, 0.001));
    });

    test('BPM fora do range 40-240 é clampado', () {
      final calc = TapTempoCalculator();
      final t0 = DateTime(2026, 1, 1, 12, 0, 0);
      // Intervalo muito curto -> BPM bem acima de 240
      final t1 = t0.add(const Duration(milliseconds: 100));

      calc.registerTap(t0);
      final bpmHigh = calc.registerTap(t1);
      expect(bpmHigh, 240.0);

      final calc2 = TapTempoCalculator();
      final s0 = DateTime(2026, 1, 1, 12, 0, 0);
      // Intervalo bem longo (mas < 2s de reset gap) -> BPM abaixo de 40
      final s1 = s0.add(const Duration(milliseconds: 1900));
      calc2.registerTap(s0);
      final bpmLow = calc2.registerTap(s1);
      expect(bpmLow, 40.0);
    });

    test('janela deslizante de _maxTaps não deixa a lista crescer sem limite', () {
      final calc = TapTempoCalculator();
      var t = DateTime(2026, 1, 1, 12, 0, 0);

      for (var i = 0; i < 12; i++) {
        calc.registerTap(t);
        t = t.add(const Duration(milliseconds: 500));
      }

      // No máximo 8 toques mantidos na janela.
      expect(calc.tapCount, 8);
    });

    test('reset() limpa os toques acumulados', () {
      final calc = TapTempoCalculator();
      final t0 = DateTime(2026, 1, 1, 12, 0, 0);
      calc.registerTap(t0);
      calc.reset();
      expect(calc.tapCount, 0);
    });
  });
}
