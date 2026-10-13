import 'dart:math' as math;

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/song_section.dart';
import '../models/track.dart';
import '../theme/app_colors.dart';
import '../widgets/dialog_text_controller.dart';
import '../providers/engine_provider.dart';
import '../providers/waveform_provider.dart';
import '../utils/tap_tempo.dart';
import 'section_editor_screen.dart';
import 'guide_editor_screen.dart';
import 'time_pitch_sheet.dart';
import 'midi_screen.dart';
import 'tempo_map_screen.dart';
import 'mixer_automation_screen.dart';
import 'song_ending_sheet.dart';
import 'buses_screen.dart';
import 'control_mapping_screen.dart';
import '../providers/control_provider.dart';
import '../providers/meter_provider.dart';

// Layout inspirado no Playback (barra de transporte no topo, faixa da setlist, waveform com as seções e o mixer
// embaixo com a coluna do Master), com as cores dos storyboards. Proporções, botões e agrupamentos são escolha
// própria: não é uma cópia da tela do iOS.
const _bg = kStageBg;
const _panelBg = kStagePanel;
const _button = kStageButton;
const _border = kStageBorder;
const _text = kStageText;
const _textDim = kStageTextDim;
const _textFaint = kStageTextFaint;
const _accent = kAccent; // tampas dos faders e posição

String _formatTime(double seconds) {
  final total = seconds.isFinite ? seconds.floor() : 0;
  final m = total ~/ 60;
  final s = total % 60;
  return '$m:${s.toString().padLeft(2, '0')}';
}

class PerformanceScreen extends ConsumerWidget {
  const PerformanceScreen({super.key});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final track = ref.watch(currentTrackProvider);
    // NÃO observamos transportProvider aqui de propósito: ele muda a cada 100ms (polling da posição) e reconstruiria
    // a tela inteira, mixer incluído. Só os widgets que dependem da posição (_TimeBox, _WaveformTimeline, botões de
    // transporte e de laço) o observam.
    ref.watch(controlProvider.select((c) => c.inputOpen)); // mantém a leitura da entrada MIDI mapeada

    if (track == null) {
      return const Scaffold(
        backgroundColor: _bg,
        body: Center(
          child: Text('Nenhuma música carregada.', style: TextStyle(color: _textDim)),
        ),
      );
    }

    return Scaffold(
      backgroundColor: _bg,
      // Atalhos de teclado (Keyboard Mapping) e entrada MIDI mapeada ficam ativos enquanto a performance está aberta.
      body: Focus(
        autofocus: true,
        onKeyEvent: (_, event) {
          if (event is! KeyDownEvent) return KeyEventResult.ignored;
          final control = ref.read(controlProvider.notifier);
          return control.handleKey(event.logicalKey.keyLabel) ? KeyEventResult.handled : KeyEventResult.ignored;
        },
        child: SafeArea(
          child: LayoutBuilder(builder: (context, constraints) {
            final wide = constraints.maxWidth >= 600;
            final short = constraints.maxHeight < 500;
            return Column(
              children: [
                _TransportBar(track: track, wide: wide),
                _SongStrip(track: track, compact: short),
                _WaveformTimeline(track: track, height: short ? 60 : 84),
                Expanded(child: _Mixer(track: track)),
              ],
            );
          }),
        ),
      ),
    );
  }
}

Future<void> _renameTrack(BuildContext context, WidgetRef ref, Track track) async {
  final newTitle = await showDialog<String>(
    context: context,
    builder: (ctx) => DialogTextController(
      initialText: track.title,
      builder: (controller) => AlertDialog(
        backgroundColor: _panelBg,
        title: const Text('Renomear música', style: TextStyle(color: _text)),
        content: TextField(
          controller: controller,
          autofocus: true,
          style: const TextStyle(color: _text),
          decoration: const InputDecoration(
            enabledBorder: OutlineInputBorder(borderSide: BorderSide(color: _border)),
            focusedBorder: OutlineInputBorder(borderSide: BorderSide(color: _accent)),
          ),
          onSubmitted: (value) => Navigator.of(ctx).pop(value),
        ),
        actions: [
          TextButton(onPressed: () => Navigator.of(ctx).pop(), child: const Text('Cancelar')),
          FilledButton(
            onPressed: () => Navigator.of(ctx).pop(controller.text),
            child: const Text('Salvar'),
          ),
        ],
      ),
    ),
  );
  if (!context.mounted) return;

  final trimmed = newTitle?.trim();
  if (trimmed == null || trimmed.isEmpty || trimmed == track.title) return;

  ref.read(currentTrackProvider.notifier).renameCurrent(trimmed);

  // Se a música já estava salva na biblioteca, persiste o novo nome também -- senão a renomeação só sobrevive em
  // memória.
  final alreadySaved = ref.read(trackLibraryProvider).any((t) => t.id == track.id);
  if (alreadySaved) {
    await ref.read(trackLibraryProvider.notifier).saveCurrent();
  }
}

Future<void> _save(BuildContext context, WidgetRef ref) async {
  final messenger = ScaffoldMessenger.of(context);
  try {
    await ref.read(trackLibraryProvider.notifier).saveCurrent();
    if (!context.mounted) return;
    messenger.showSnackBar(const SnackBar(content: Text('Música salva.')));
  } catch (e) {
    if (!context.mounted) return;
    messenger.showSnackBar(SnackBar(content: Text('Falha ao salvar: $e')));
  }
}

/// Barra de transporte (Playback: tempo/compasso, tempo decorrido, PAD, anterior, play, fade, EDIT, setlist, menu).
/// No lugar do PAD (fora do escopo) fica o liga/desliga do click; "Anterior" volta ao início (RTZ) e a navegação
/// entre músicas fica na faixa da setlist. Em telas estreitas a barra quebra em duas linhas (escolha própria).
class _TransportBar extends ConsumerWidget {
  final Track track;
  final bool wide;
  const _TransportBar({required this.track, required this.wide});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final canPop = Navigator.of(context).canPop();
    final info = <Widget>[
      if (canPop)
        _SquareButton(
          tooltip: 'Voltar',
          width: 36,
          onTap: () => Navigator.of(context).maybePop(),
          child: const Icon(Icons.chevron_left, color: _textDim),
        ),
      _TempoBox(track: track),
      const _TimeBox(),
      const _ClickButton(),
    ];
    final actions = <Widget>[
      _SquareButton(
        tooltip: 'Seções',
        width: 56,
        onTap: () => Navigator.of(context)
            .push(MaterialPageRoute<void>(builder: (_) => SectionEditorScreen(trackId: track.id))),
        child: const Text('EDITAR', style: TextStyle(color: _textDim, fontSize: 11, letterSpacing: 0.5)),
      ),
      _MoreMenu(track: track),
    ];
    const transport = _TransportButtons();
    return Container(
      color: _panelBg,
      padding: const EdgeInsets.fromLTRB(6, 6, 6, 6),
      child: wide
          ? SizedBox(
              height: 52,
              child: Row(children: [
                ..._spaced(info),
                const SizedBox(width: 6),
                const Expanded(child: transport),
                const SizedBox(width: 6),
                ..._spaced(actions),
              ]),
            )
          : Column(children: [
              SizedBox(
                height: 48,
                child: Row(children: [..._spaced(info), const Spacer(), ..._spaced(actions)]),
              ),
              const SizedBox(height: 6),
              const SizedBox(height: 48, child: transport),
            ]),
    );
  }

  static List<Widget> _spaced(List<Widget> items) => [
        for (var i = 0; i < items.length; i++) ...[if (i > 0) const SizedBox(width: 6), items[i]],
      ];
}

/// Botão retangular escuro da barra (Playback: TransportEditButton, TransportPadButton...).
class _SquareButton extends StatelessWidget {
  final Widget child;
  final VoidCallback? onTap;
  final String? tooltip;
  final double? width;
  final bool active;
  final Color activeColor;
  const _SquareButton({
    required this.child,
    this.onTap,
    this.tooltip,
    this.width,
    this.active = false,
    this.activeColor = kStageGreen,
  });

  @override
  Widget build(BuildContext context) {
    Widget button = Material(
      color: active ? activeColor.withValues(alpha: 0.12) : _button,
      shape: RoundedRectangleBorder(
        borderRadius: BorderRadius.circular(6),
        side: BorderSide(color: active ? activeColor : _border),
      ),
      child: InkWell(
        onTap: onTap,
        borderRadius: BorderRadius.circular(6),
        child: SizedBox(width: width, height: double.infinity, child: Center(child: child)),
      ),
    );
    if (tooltip != null) button = Tooltip(message: tooltip!, child: button);
    return button;
  }
}

/// Liga/desliga o click (ocupa o lugar do PAD do Playback, que está fora do escopo).
class _ClickButton extends ConsumerWidget {
  const _ClickButton();
  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final enabled = ref.watch(clickEnabledProvider);
    return _SquareButton(
      tooltip: enabled ? 'Desligar click' : 'Ligar click',
      width: 52,
      active: enabled,
      onTap: () {
        ref.read(clickEnabledProvider.notifier).state = !enabled;
        ref.read(engineProvider).setClickEnabled(!enabled);
      },
      child: Text('CLICK',
          style: TextStyle(
              color: enabled ? kStageGreen : _textFaint, fontSize: 11, fontWeight: FontWeight.w600, letterSpacing: 0.5)),
    );
  }
}

/// Os três botões grandes: voltar ao início, play/pausa e fade de 5 s (Playback: RTZ/Previous, PlayPause, Fade).
class _TransportButtons extends ConsumerWidget {
  const _TransportButtons();
  @override
  Widget build(BuildContext context, WidgetRef ref) {
    // `select` reconstrói só quando estes campos mudam, não a cada tick de posição.
    final isPlaying = ref.watch(transportProvider.select((t) => t.isPlaying));
    final prerolling = ref.watch(transportProvider.select((t) => t.prerolling));
    final fading = ref.watch(transportProvider.select((t) => t.fading));
    final notifier = ref.read(transportProvider.notifier);
    final playColor = prerolling ? kStageYellow : kStageGreen;
    return Row(children: [
      Expanded(
        child: _SquareButton(
          tooltip: 'Parar e voltar ao início',
          onTap: notifier.stop,
          child: const Icon(Icons.stop, color: _textDim, size: 26),
        ),
      ),
      const SizedBox(width: 6),
      Expanded(
        flex: 2,
        child: _SquareButton(
          tooltip: prerolling ? 'Contagem' : (isPlaying ? 'Pausar' : 'Tocar'),
          active: isPlaying || prerolling,
          activeColor: playColor,
          onTap: isPlaying ? notifier.pause : notifier.play,
          child: Icon(prerolling ? Icons.av_timer : (isPlaying ? Icons.pause : Icons.play_arrow),
              color: playColor, size: 32),
        ),
      ),
      const SizedBox(width: 6),
      Expanded(
        child: _SquareButton(
          tooltip: 'Fade de 5 segundos',
          active: fading,
          activeColor: kStageOrange,
          onTap: () => notifier.fadeOut(),
          child: CustomPaint(size: const Size(26, 18), painter: _FadeIconPainter(fading ? kStageOrange : _textDim)),
        ),
      ),
    ]);
  }
}

/// Rampa descendente do botão de fade (Playback: TransportFadeButton).
class _FadeIconPainter extends CustomPainter {
  final Color color;
  const _FadeIconPainter(this.color);
  @override
  void paint(Canvas canvas, Size size) {
    final path = Path()
      ..moveTo(1, 1)
      ..lineTo(size.width - 1, size.height - 1)
      ..lineTo(1, size.height - 1)
      ..close();
    canvas.drawPath(
        path,
        Paint()
          ..color = color
          ..style = PaintingStyle.stroke
          ..strokeWidth = 1.6
          ..strokeJoin = StrokeJoin.round);
  }

  @override
  bool shouldRepaint(covariant _FadeIconPainter old) => old.color != color;
}

class _MoreMenu extends ConsumerWidget {
  final Track track;
  const _MoreMenu({required this.track});
  @override
  Widget build(BuildContext context, WidgetRef ref) {
    void push(Widget screen) => Navigator.of(context).push(MaterialPageRoute<void>(builder: (_) => screen));
    return Material(
      color: _button,
      shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(6), side: const BorderSide(color: _border)),
      child: PopupMenuButton<String>(
        tooltip: 'Mais',
        icon: const Icon(Icons.menu, color: _textDim),
        onSelected: (choice) {
          switch (choice) {
            case 'save':
              _save(context, ref);
            case 'rename':
              _renameTrack(context, ref, track);
            case 'midi':
              push(MidiScreen(trackId: track.id));
            case 'pitch':
              showModalBottomSheet<void>(
                  context: context, isScrollControlled: true, builder: (_) => TimePitchSheet(trackId: track.id));
            case 'guides':
              push(GuideEditorScreen(trackId: track.id));
            case 'tempo':
              push(TempoMapScreen(trackId: track.id));
            case 'mapping':
              push(const ControlMappingScreen());
            case 'buses':
              push(BusesScreen(trackId: track.id));
            case 'ending':
              showModalBottomSheet<void>(context: context, isScrollControlled: true, builder: (_) => const SongEndingSheet());
            case 'automation':
              push(MixerAutomationScreen(trackId: track.id));
          }
        },
        itemBuilder: (_) => const [
          PopupMenuItem(value: 'save', child: Text('Salvar música')),
          PopupMenuItem(value: 'rename', child: Text('Renomear música')),
          PopupMenuDivider(),
          PopupMenuItem(value: 'tempo', child: Text('Mapa de andamento')),
          PopupMenuItem(value: 'pitch', child: Text('Tom e andamento')),
          PopupMenuItem(value: 'guides', child: Text('Guias')),
          PopupMenuItem(value: 'automation', child: Text('Automação do mixer')),
          PopupMenuItem(value: 'ending', child: Text('Fim da música e fade')),
          PopupMenuItem(value: 'buses', child: Text('Buses e roteamento')),
          PopupMenuItem(value: 'mapping', child: Text('Mapeamento MIDI e teclado')),
          PopupMenuItem(value: 'midi', child: Text('MIDI, automações e timecode')),
        ],
      ),
    );
  }
}

/// Posição atual grande e "decorrido / duração" embaixo (Playback: "00:45" sobre "0:00 / 6:58").
class _TimeBox extends ConsumerWidget {
  const _TimeBox();
  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final position = ref.watch(transportProvider.select((t) => t.positionSeconds));
    final length = ref.watch(transportProvider.select((t) => t.lengthSeconds));
    const figures = [FontFeature.tabularFigures()];
    return Container(
      width: 84,
      decoration: BoxDecoration(color: _button, borderRadius: BorderRadius.circular(6), border: Border.all(color: _border)),
      child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          Text(_formatTime(position),
              style: const TextStyle(color: _text, fontSize: 18, fontWeight: FontWeight.w300, fontFeatures: figures)),
          Text('-${_formatTime(math.max(0, length - position))} / ${_formatTime(length)}',
              maxLines: 1,
              style: const TextStyle(color: _textFaint, fontSize: 9, fontFeatures: figures)),
        ],
      ),
    );
  }
}

/// Andamento e compasso (Playback: TransportTempoTimeSignatureButton). Toque abre o metrônomo.
class _TempoBox extends ConsumerWidget {
  final Track track;
  const _TempoBox({required this.track});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final click = track.clickSettings;
    return _SquareButton(
      tooltip: 'Metrônomo e andamento',
      width: 60,
      onTap: () => _showBpmDialog(context, ref, ref.read(transportProvider).isPlaying),
      child: Column(
        mainAxisSize: MainAxisSize.min,
        children: [
          Row(mainAxisSize: MainAxisSize.min, crossAxisAlignment: CrossAxisAlignment.baseline,
              textBaseline: TextBaseline.alphabetic, children: [
            Text(click.bpm.round().toString(),
                style: const TextStyle(color: _text, fontSize: 15, fontWeight: FontWeight.w500)),
            const SizedBox(width: 2),
            const Text('BPM', style: TextStyle(color: _textFaint, fontSize: 8)),
            if (click.calibrated) ...[
              const SizedBox(width: 2),
              const Icon(Icons.check_circle, color: kStageGreen, size: 9),
            ],
          ]),
          Container(height: 1, width: 36, color: _border, margin: const EdgeInsets.symmetric(vertical: 2)),
          Text('${click.timeSignatureNumerator}/${click.timeSignatureDenominator}',
              style: const TextStyle(color: _textDim, fontSize: 12)),
        ],
      ),
    );
  }

  void _showBpmDialog(BuildContext context, WidgetRef ref, bool isPlaying) {
    double tempBpm = track.clickSettings.bpm;
    bool calibrated = track.clickSettings.calibrated;
    // Vive no escopo de _showBpmDialog (fora do StatefulBuilder) pra
    // sobreviver aos rebuilds do bottom sheet -- reabrir o diálogo chama
    // este método de novo e cria uma instância nova automaticamente.
    final tapCalculator = TapTempoCalculator();
    String tapHint = 'Toque no ritmo da música';

    showModalBottomSheet(
      context: context,
      backgroundColor: _panelBg,
      // Em paisagem / telas baixas o conteúdo não cabe nos 9/16 padrão.
      isScrollControlled: true,
      useSafeArea: true,
      builder: (ctx) {
        return StatefulBuilder(
          builder: (context, setState) {
            return SingleChildScrollView(child: Container(
              padding: const EdgeInsets.all(24),
              child: Column(
                mainAxisSize: MainAxisSize.min,
                children: [
                  const Text(
                      'Configurar metrônomo', style: TextStyle(color: Colors.white, fontSize: 16),
                    ),
                  const SizedBox(height: 24),
                  Row(
                    children: [
                      Text(tempBpm.round().toString(), style: const TextStyle(color: _accent, fontSize: 24, fontWeight: FontWeight.bold,
                          ),
                        ),
                      if (calibrated) ...[
                        const SizedBox(width: 6),
                        const Icon(Icons.check_circle, color: _accent, size: 18,
                          ),
                      ],
                      Expanded(
                        child: Slider(
                          value: tempBpm.clamp(40, 240),
                          min: 40,
                          max: 240,
                          activeColor: _accent,
                          onChanged: (val) {
                            setState(() => tempBpm = val);
                            ref.read(currentTrackProvider.notifier).updateBpm(val);
                          },
                        ),
                      ),
                    ],
                  ),
                  const SizedBox(height: 16),
                  Text(tapHint, style: const TextStyle(color: _textFaint, fontSize: 13),
                    ),
                  const SizedBox(height: 12),
                  Row(
                    children: [
                      Expanded(
                        flex: 3,
                        child: ElevatedButton(
                          style: ElevatedButton.styleFrom(
                            backgroundColor: _accent,
                            foregroundColor: Colors.black,
                            padding: const EdgeInsets.symmetric(vertical: 20),
                          ),
                          onPressed: () {
                            final bpm = tapCalculator.registerTap();
                            setState(() {
                              if (bpm == null) {
                                tapHint = 'Continue tocando no ritmo...';
                              } else {
                                tempBpm = bpm;
                                calibrated = true;
                                tapHint = 'Continue tocando pra refinar...';
                                ref.read(currentTrackProvider.notifier).applyCalibratedBpm(bpm);
                              }
                            });
                          },
                          child: const Text('TAP', style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold,
                              ),
                            ),
                        ),
                      ),
                      const SizedBox(width: 12),
                      Expanded(
                        flex: 1,
                        child: OutlinedButton(
                          style: OutlinedButton.styleFrom(
                            foregroundColor: _textFaint,
                            padding: const EdgeInsets.symmetric(vertical: 20),
                          ),
                          onPressed: () {
                            tapCalculator.reset();
                            setState(() {
                              tapHint = 'Toque no ritmo da música';
                            });
                          },
                          child: const Text('Reiniciar'),
                        ),
                      ),
                    ],
                  ),
                  const SizedBox(height: 20),
                  const Divider(color: _border),
                  const SizedBox(height: 8),
                    Consumer(
                      builder: (context, ref, _) {
                        final settings =
                            ref.watch(currentTrackProvider)?.clickSettings ??
                            track.clickSettings;
                        void apply(ClickSettings next) => ref
                            .read(currentTrackProvider.notifier)
                            .updateClickSettings(next);
                        Widget choice(
                          String label,
                          int value,
                          List<int> values,
                          ValueChanged<int> change,
                        ) => Row(
                          children: [
                            Expanded(
                              child: Text(
                                label,
                                style: const TextStyle(color: Colors.white),
                              ),
                            ),
                            DropdownButton<int>(
                              value: value,
                              items: values
                                  .map(
                                    (n) => DropdownMenuItem(
                                      value: n,
                                      child: Text('$n'),
                                    ),
                                  )
                                  .toList(),
                              onChanged: (n) {
                                if (n != null) change(n);
                              },
                            ),
                          ],
                        );
                        Widget gain(
                          String label,
                          double value,
                          ValueChanged<double> change,
                        ) => Row(
                          children: [
                            SizedBox(
                              width: 100,
                              child: Text(
                                label,
                                style: const TextStyle(color: Colors.white),
                              ),
                            ),
                            Expanded(
                              child: Slider(
                                value: value,
                                max: 2,
                                onChanged: change,
                              ),
                            ),
                            Text(
                              '${(value * 100).round()}%',
                              style: const TextStyle(color: _textFaint),
                            ),
                          ],
                        );
                        return Column(
                          children: [
                            choice(
                              'Tempos por compasso',
                              settings.timeSignatureNumerator,
                              List.generate(64, (i) => i + 1),
                              (n) => apply(
                                settings.copyWith(timeSignatureNumerator: n),
                              ),
                            ),
                            choice(
                              'Unidade do compasso',
                              settings.timeSignatureDenominator,
                              const [1, 2, 4, 8, 16, 32, 64],
                              (n) => apply(
                                settings.copyWith(timeSignatureDenominator: n),
                              ),
                            ),
                            choice(
                              'Unidade do BPM',
                              settings.bpmUnit,
                              const [1, 2, 4, 8, 16, 32, 64],
                              (n) => apply(settings.copyWith(bpmUnit: n)),
                            ),
                            Row(
                              children: [
                                const Expanded(
                                  child: Text(
                                    'Timbre',
                                    style: TextStyle(color: Colors.white),
                                  ),
                                ),
                                DropdownButton<String>(
                                  value: settings.timbreFamily,
                                  items:
                                      {
                                            'synthetic',
                                            settings.timbreFamily,
                                            ...?ref
                                                .watch(clickFamiliesProvider)
                                                .asData
                                                ?.value,
                                          }
                                          .map(
                                            (family) => DropdownMenuItem(
                                              value: family,
                                              child: Text(
                                                family == 'synthetic'
                                                    ? 'Sintético'
                                                    : family,
                                              ),
                                            ),
                                          )
                                          .toList(),
                                  onChanged: (family) async {
                                    if (family == null) return;
                                    final ok = await ref
                                        .read(currentTrackProvider.notifier)
                                        .updateClickTimbre(family);
                                    if (!ok && context.mounted) {
                                      ScaffoldMessenger.of(
                                        context,
                                      ).showSnackBar(
                                        const SnackBar(
                                          content: Text(
                                            'Não foi possível carregar o timbre',
                                          ),
                                        ),
                                      );
                                    }
                                  },
                                ),
                              ],
                            ),
                            gain(
                              'Volume',
                              settings.volume,
                              (n) => apply(settings.copyWith(volume: n)),
                            ),
                            gain(
                              'Acento',
                              settings.accentGain,
                              (n) => apply(settings.copyWith(accentGain: n)),
                            ),
                            gain(
                              'Semínimas',
                              settings.quarterGain,
                              (n) => apply(settings.copyWith(quarterGain: n)),
                            ),
                            gain(
                              'Colcheias',
                              settings.eighthGain,
                              (n) => apply(settings.copyWith(eighthGain: n)),
                            ),
                            gain(
                              'Semicolcheias',
                              settings.sixteenthGain,
                              (n) => apply(settings.copyWith(sixteenthGain: n)),
                            ),
                            const SizedBox(height: 12),
                          ],
                        );
                      },
                    ),
                    const Text('Offset do click', style: TextStyle(color: Colors.white, fontSize: 16),
                    ),
                  const SizedBox(height: 8),
                  // Lê o offset do provider (não do `track` capturado ao abrir
                  // o diálogo), senão o valor exibido nunca atualiza.
                  Consumer(builder: (context, ref, _) {
                    final offset = ref.watch(currentTrackProvider
                        .select((t) => t?.clickSettings.beatOffsetSeconds ?? 0.0,
                          ),
                        );
                    return Text(
                      '${offset >= 0 ? '+' : ''}${offset.toStringAsFixed(2)}s',
                      style: const TextStyle(color: _accent, fontSize: 18, fontWeight: FontWeight.bold,
                          ),
                    );
                  },
                    ),
                  const SizedBox(height: 8),
                  if (!isPlaying)
                    const Text('Toque play e marque no primeiro tempo real',
                        style: TextStyle(color: _textFaint, fontSize: 13),
                      ),
                  const SizedBox(height: 8),
                  Row(
                    children: [
                      Expanded(
                        flex: 3,
                        child: ElevatedButton(
                          style: ElevatedButton.styleFrom(
                            backgroundColor: _accent,
                            foregroundColor: Colors.black,
                            padding: const EdgeInsets.symmetric(vertical: 16),
                          ),
                          onPressed: isPlaying
                              ? () {
                                  final positionSeconds =
                                      ref.read(transportProvider).positionSeconds;
                                  ref
                                      .read(currentTrackProvider.notifier)
                                      .applyClickOffset(positionSeconds);
                                  setState(() {});
                                }
                              : null,
                          child: const Text('Marcar 1º tempo'),
                        ),
                      ),
                      const SizedBox(width: 12),
                      Expanded(
                        flex: 1,
                        child: OutlinedButton(
                          style: OutlinedButton.styleFrom(
                            foregroundColor: _textFaint,
                            padding: const EdgeInsets.symmetric(vertical: 16),
                          ),
                          onPressed: () {
                            ref.read(currentTrackProvider.notifier).applyClickOffset(0.0);
                            setState(() {});
                          },
                          child: const Text('Zerar offset'),
                        ),
                      ),
                    ],
                  ),
                ],
              ),
            ),
            );
          },
        );
      },
    );
  }

}

/// Faixa das músicas (Playback: cartões da setlist com o título e o tom, seta de transição e ▷ na música atual).
/// Sem setlist, mostra só a música aberta. Toque no cartão atual renomeia; nos outros, carrega a música.
class _SongStrip extends ConsumerWidget {
  final Track track;
  final bool compact;
  const _SongStrip({required this.track, required this.compact});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final session = ref.watch(setlistSessionProvider);
    final inSession = session != null && session.current.id == track.id;
    final songs = inSession ? session.setlist.tracks : [track];
    final current = inSession ? session.index : 0;
    final notifier = ref.read(setlistSessionProvider.notifier);
    final cardWidth = compact ? 128.0 : 156.0;
    return Container(
      color: _bg,
      padding: EdgeInsets.fromLTRB(6, 6, 6, inSession ? 0 : 6),
      child: Column(children: [
        SizedBox(
          height: compact ? 44 : 58,
          child: ListView.separated(
            scrollDirection: Axis.horizontal,
            itemCount: songs.length,
            separatorBuilder: (_, _) => const SizedBox(width: 6),
            itemBuilder: (context, i) {
              final song = i == current ? track : songs[i];
              return _SongCard(
                song: song,
                width: cardWidth,
                current: i == current,
                cuesNext: inSession && i < songs.length - 1 && song.transition == SongTransition.cueNextSong,
                onTap: i == current ? () => _renameTrack(context, ref, track) : () => notifier.go(i),
              );
            },
          ),
        ),
        if (inSession) _SetlistCaption(session: session, track: track),
      ]),
    );
  }
}

class _SongCard extends StatelessWidget {
  final Track song;
  final double width;
  final bool current, cuesNext;
  final VoidCallback onTap;
  const _SongCard({required this.song, required this.width, required this.current, required this.cuesNext, required this.onTap});

  @override
  Widget build(BuildContext context) {
    // Sem capa no nosso modelo: um bloco colorido derivado do título (escolha própria).
    final hue = (song.title.hashCode % 360).abs().toDouble();
    final top = HSLColor.fromAHSL(1, hue, 0.35, 0.30).toColor();
    final bottom = HSLColor.fromAHSL(1, (hue + 40) % 360, 0.35, 0.16).toColor();
    final key = song.key;
    return Tooltip(
      message: current ? 'Renomear música' : 'Abrir ${song.title}',
      child: InkWell(
        onTap: onTap,
        borderRadius: BorderRadius.circular(6),
        child: SizedBox(
          width: width,
          child: Column(crossAxisAlignment: CrossAxisAlignment.start, children: [
            Expanded(
              child: Container(
                decoration: BoxDecoration(
                  borderRadius: BorderRadius.circular(6),
                  border: Border.all(color: current ? _text : _border, width: current ? 1.5 : 1),
                  gradient: LinearGradient(colors: [top, bottom], begin: Alignment.topLeft, end: Alignment.bottomRight),
                ),
                child: Stack(children: [
                  Positioned(
                    left: 8,
                    bottom: 2,
                    child: Text(
                      song.title.isEmpty ? '' : song.title.substring(0, 1).toUpperCase(),
                      style: TextStyle(color: Colors.white.withValues(alpha: 0.25), fontSize: 20, fontWeight: FontWeight.w700),
                    ),
                  ),
                  if (cuesNext)
                    Positioned(
                      right: 0,
                      top: 0,
                      child: Container(
                        padding: const EdgeInsets.symmetric(horizontal: 4),
                        decoration: const BoxDecoration(
                          color: Colors.white,
                          borderRadius: BorderRadius.only(topRight: Radius.circular(5), bottomLeft: Radius.circular(5)),
                        ),
                        child: const Icon(Icons.arrow_forward, size: 12, color: Colors.black),
                      ),
                    ),
                ]),
              ),
            ),
            const SizedBox(height: 2),
            Row(children: [
              if (current) const Icon(Icons.play_arrow_outlined, size: 13, color: kStageGreen),
              Expanded(
                child: Text(
                  key == null || key.isEmpty ? song.title : '${song.title} ($key)',
                  maxLines: 1,
                  overflow: TextOverflow.ellipsis,
                  style: TextStyle(
                      color: current ? _text : _textDim, fontSize: 11, fontWeight: current ? FontWeight.w600 : FontWeight.w400),
                ),
              ),
            ]),
          ]),
        ),
      ),
    );
  }
}

/// Posição na setlist, a próxima música e a navegação.
class _SetlistCaption extends ConsumerWidget {
  final SetlistSession session;
  final Track track;
  const _SetlistCaption({required this.session, required this.track});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final notifier = ref.read(setlistSessionProvider.notifier);
    final next = session.next;
    final label = next == null
        ? 'Última música'
        : (track.transition == SongTransition.cueNextSong ? 'Próxima: ${next.title}' : 'Fica na música · depois: ${next.title}');
    Widget nav(IconData icon, String tooltip, VoidCallback? onTap) => Tooltip(
          message: tooltip,
          child: InkWell(
            onTap: onTap,
            child: SizedBox(width: 32, height: 22, child: Icon(icon, size: 16, color: onTap == null ? _border : _textDim)),
          ),
        );
    return SizedBox(
      height: 22,
      child: Row(children: [
        Text('${session.index + 1}/${session.setlist.tracks.length}', style: const TextStyle(color: _textFaint, fontSize: 11)),
        const SizedBox(width: 8),
        Expanded(child: Text(label, overflow: TextOverflow.ellipsis, style: const TextStyle(color: _textDim, fontSize: 11))),
        nav(Icons.skip_previous, 'Música anterior', session.previous == null ? null : notifier.previous),
        nav(Icons.skip_next, 'Próxima música', next == null ? null : notifier.next),
      ]),
    );
  }
}

/// Sigla e cor da seção no waveform (Playback: selos "V1", "R1", "I"...). A cor pela inicial do nome é escolha
/// própria: o Playback colore pelo tipo de seção, que o nosso modelo não tem.
String _sectionBadge(String name) {
  final trimmed = name.trim();
  if (trimmed.isEmpty) return '?';
  final digits = RegExp(r'\d+').firstMatch(trimmed)?.group(0) ?? '';
  final badge = '${trimmed.substring(0, 1).toUpperCase()}$digits';
  return badge.length > 3 ? badge.substring(0, 3) : badge;
}

Color _sectionColor(String name) {
  final n = name.trim().toLowerCase();
  if (n.startsWith('v')) return kStagePurple; // verso, verse
  if (n.startsWith('r') || n.startsWith('c')) return kStageOrange; // refrão, coro, chorus
  if (n.startsWith('p') || n.startsWith('b')) return kStageBlue; // ponte, pré-refrão, bridge
  if (n.startsWith('i') || n.startsWith('o') || n.startsWith('f') || n.startsWith('e')) return kStageGreen;
  return kStageYellow;
}

/// Waveform com as seções coloridas, selo e botão de laço por seção, e a agulha de posição. Toque/arrasto busca; o
/// laço de uma seção liga com um toque no ícone (segurar enfileira como próxima seção). Sem waveform (falha ou
/// nunca gerada), cai num slider simples -- o seek continua funcionando.
class _WaveformTimeline extends ConsumerStatefulWidget {
  final Track track;
  final double height;

  const _WaveformTimeline({required this.track, required this.height});

  @override
  ConsumerState<_WaveformTimeline> createState() => _WaveformTimelineState();
}

class _WaveformTimelineState extends ConsumerState<_WaveformTimeline> {
  @override
  void initState() {
    super.initState();
    WidgetsBinding.instance.addPostFrameCallback((_) => _load());
  }

  @override
  void didUpdateWidget(covariant _WaveformTimeline oldWidget) {
    super.didUpdateWidget(oldWidget);
    if (oldWidget.track.id != widget.track.id) {
      WidgetsBinding.instance.addPostFrameCallback((_) => _load());
    }
  }

  void _load() {
    if (!mounted) return;
    ref.read(waveformProvider.notifier).loadFor(widget.track);
  }

  void _seek(double seconds) => ref.read(transportProvider.notifier).seekTo(seconds);

  void _handleSeek(Offset localPosition, double width) {
    final length = ref.read(transportProvider).lengthSeconds;
    if (length <= 0 || width <= 0) return;
    final fraction = (localPosition.dx / width).clamp(0.0, 1.0);
    _seek(fraction * length);
  }

  Future<void> _loop(SongSection section, {bool queue = false}) async {
    if (queue && !ref.read(transportProvider).loopEnabled) return;
    final ok = await ref.read(currentTrackProvider.notifier).setSectionLoop(section, queue: queue);
    if (!ok && mounted) {
      ScaffoldMessenger.of(context)
          .showSnackBar(const SnackBar(content: Text('Não foi possível preparar o loop desta seção.')));
    }
  }

  @override
  Widget build(BuildContext context) {
    final waveform = ref.watch(waveformProvider);
    final transport = ref.watch(transportProvider);
    final length = transport.lengthSeconds > 0 ? transport.lengthSeconds : 1.0;
    final sections = widget.track.sections;

    final Widget content;
    if (waveform.isGenerating) {
      content = const Center(child: Text('Gerando waveform...', style: TextStyle(color: _textFaint, fontSize: 12)));
    } else if (waveform.peaks == null) {
      content = Padding(
        padding: const EdgeInsets.symmetric(horizontal: 12),
        child: Center(
          child: SliderTheme(
            data: SliderTheme.of(context).copyWith(
              activeTrackColor: _text,
              inactiveTrackColor: _border,
              thumbColor: _text,
              overlayColor: _text.withValues(alpha: 0.15),
            ),
            child: Slider(
              value: transport.positionSeconds.clamp(0, length),
              max: length,
              onChanged: (_) {},
              onChangeEnd: _seek,
            ),
          ),
        ),
      );
    } else {
      final progress = (transport.positionSeconds / length).clamp(0.0, 1.0).toDouble();
      content = LayoutBuilder(
        builder: (context, constraints) {
          final width = constraints.maxWidth;
          return GestureDetector(
            onTapDown: (details) => _handleSeek(details.localPosition, width),
            onHorizontalDragUpdate: (details) => _handleSeek(details.localPosition, width),
            child: CustomPaint(
              size: Size(width, constraints.maxHeight),
              painter: _WaveformPainter(peaks: waveform.peaks!, progress: progress),
            ),
          );
        },
      );
    }

    return Container(
      height: widget.height,
      decoration: const BoxDecoration(
        color: _panelBg,
        border: Border.symmetric(horizontal: BorderSide(color: _border)),
      ),
      child: LayoutBuilder(builder: (context, constraints) {
        final width = constraints.maxWidth;
        double x(double seconds) => (seconds / length).clamp(0.0, 1.0) * width;
        return Stack(children: [
          Positioned.fill(
            child: CustomPaint(
              painter: _SectionsPainter(
                sections: sections,
                lengthSeconds: transport.lengthSeconds,
                active: [for (final s in sections) transport.activeSection(s)],
              ),
            ),
          ),
          Positioned.fill(child: content),
          if (transport.lengthSeconds > 0)
            for (final section in sections) ..._sectionControls(section, x(section.startSeconds), x(section.endSeconds), transport),
          if (transport.loopPass > 0)
            Positioned(
              right: 6,
              bottom: 4,
              child: IgnorePointer(
                child: Container(
                  key: const Key('loop-pass'),
                  padding: const EdgeInsets.symmetric(horizontal: 6, vertical: 1),
                  decoration: BoxDecoration(
                    color: _bg.withValues(alpha: 0.8),
                    border: Border.all(color: kStageGreen),
                    borderRadius: BorderRadius.circular(4),
                  ),
                  child: Text(
                    transport.loopRepeats > 0 ? 'Laço ${transport.loopPass}/${transport.loopRepeats}' : 'Laço ${transport.loopPass}',
                    style: const TextStyle(color: kStageGreen, fontSize: 11),
                  ),
                ),
              ),
            ),
        ]);
      }),
    );
  }

  List<Widget> _sectionControls(SongSection section, double left, double right, TransportState transport) {
    final color = _sectionColor(section.name);
    final active = transport.activeSection(section);
    final queued = transport.queuedSection(section);
    return [
      Positioned(
        left: left + 4,
        top: 4,
        child: Tooltip(
          message: section.name,
          child: GestureDetector(
            onTap: () => _seek(section.playStart),
            child: Container(
              width: 22,
              height: 22,
              alignment: Alignment.center,
              decoration: BoxDecoration(
                color: _bg.withValues(alpha: 0.75),
                shape: BoxShape.circle,
                border: Border.all(color: color, width: 1.5),
              ),
              child: Text(_sectionBadge(section.name),
                  style: TextStyle(color: color, fontSize: 9, fontWeight: FontWeight.w700)),
            ),
          ),
        ),
      ),
      if (right - left >= 60)
        Positioned(
          left: right - 26,
          top: 4,
          child: Tooltip(
            message: 'Repetir ${section.name}',
            child: GestureDetector(
              onTap: () => active ? ref.read(transportProvider.notifier).disableLoop() : _loop(section),
              onLongPress: () => _loop(section, queue: true),
              child: Container(
                width: 22,
                height: 22,
                decoration: BoxDecoration(
                  color: _bg.withValues(alpha: 0.6),
                  borderRadius: BorderRadius.circular(6),
                  border: Border.all(color: active ? kStageGreen : (queued ? kStageYellow : _border)),
                ),
                child: Icon(Icons.repeat, size: 14, color: active ? kStageGreen : (queued ? kStageYellow : _textDim)),
              ),
            ),
          ),
        ),
    ];
  }
}

/// Fundo das seções: faixa colorida translúcida e linha de início (laço ativo mais forte).
class _SectionsPainter extends CustomPainter {
  final List<SongSection> sections;
  final double lengthSeconds;
  final List<bool> active;
  _SectionsPainter({required this.sections, required this.lengthSeconds, required this.active});

  @override
  void paint(Canvas canvas, Size size) {
    if (lengthSeconds <= 0 || size.width <= 0) return;
    for (var i = 0; i < sections.length; i++) {
      final s = sections[i];
      final left = (s.startSeconds / lengthSeconds).clamp(0.0, 1.0) * size.width;
      final right = (s.endSeconds / lengthSeconds).clamp(0.0, 1.0) * size.width;
      if (right <= left) continue;
      final color = _sectionColor(s.name);
      canvas.drawRect(Rect.fromLTRB(left, 0, right, size.height),
          Paint()..color = color.withValues(alpha: active[i] ? 0.30 : 0.13));
      canvas.drawRect(Rect.fromLTWH(left, 0, 1, size.height), Paint()..color = color.withValues(alpha: 0.7));
      // Trechos cortados (trim) ficam escurecidos.
      final dim = Paint()..color = Colors.black.withValues(alpha: 0.55);
      if (s.trimStartSeconds > 0) {
        canvas.drawRect(Rect.fromLTRB(left, 0, (s.playStart / lengthSeconds).clamp(0.0, 1.0) * size.width, size.height), dim);
      }
      if (s.trimEndSeconds > 0) {
        canvas.drawRect(Rect.fromLTRB((s.playEnd / lengthSeconds).clamp(0.0, 1.0) * size.width, 0, right, size.height), dim);
      }
    }
  }

  @override
  bool shouldRepaint(covariant _SectionsPainter old) =>
      old.sections != sections || old.lengthSeconds != lengthSeconds || !_sameFlags(old.active, active);

  static bool _sameFlags(List<bool> a, List<bool> b) {
    if (a.length != b.length) return false;
    for (var i = 0; i < a.length; i++) {
      if (a[i] != b[i]) return false;
    }
    return true;
  }
}

class _WaveformPainter extends CustomPainter {
  final List<double> peaks;
  final double progress; // 0.0 - 1.0

  _WaveformPainter({required this.peaks, required this.progress});

  @override
  void paint(Canvas canvas, Size size) {
    if (peaks.isEmpty || size.width <= 0 || size.height <= 0) return;

    final barWidth = size.width / peaks.length;
    final centerY = size.height / 2;
    final playedBars = (peaks.length * progress).round();

    final playedPaint = Paint()..color = const Color(0xFFE6E6E6);
    final remainingPaint = Paint()..color = const Color(0xFF8A8A8F);

    // Deixa 1px de respiro entre as barras quando há espaço -- com barWidth < 1px desenha a barra cheia (um
    // `clamp(1.0, barWidth)` lançaria ArgumentError: min > max).
    final rectWidth = barWidth > 1.0 ? barWidth - 1.0 : barWidth;
    final usable = size.height * 0.8;

    for (var i = 0; i < peaks.length; i++) {
      final barHeight = math.min(usable, (peaks[i].clamp(0.0, 1.0)) * usable);
      final left = i * barWidth;
      final rect = Rect.fromLTWH(left, centerY - barHeight / 2, rectWidth, barHeight);
      canvas.drawRect(rect, i < playedBars ? playedPaint : remainingPaint);
    }
    // Agulha de posição.
    final x = progress * size.width;
    canvas.drawRect(Rect.fromLTWH(x - 1, 0, 2, size.height), Paint()..color = Colors.white);
  }

  @override
  bool shouldRepaint(covariant _WaveformPainter oldDelegate) {
    return oldDelegate.peaks != peaks || oldDelegate.progress != progress;
  }
}

/// Mixer: canais e buses em faixas verticais roláveis; à direita, automação, laços e o Master (Playback: MixerView com
/// MixerModeButton, MixerLoopButton e MixerMasterFader).
class _Mixer extends ConsumerWidget {
  final Track track;
  const _Mixer({required this.track});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final notifier = ref.read(currentTrackProvider.notifier);
    // Com a automação agindo, os faders mostram os valores que o motor está aplicando.
    final mix = ref.watch(automatedMixProvider);
    final masterVolume = mix?.master ?? track.masterVolume;

    return Container(
      color: _bg,
      padding: const EdgeInsets.fromLTRB(4, 6, 6, 6),
      child: Row(
        children: [
          Expanded(
            child: ListView.builder(
              scrollDirection: Axis.horizontal,
              itemCount: track.channels.length + track.buses.length,
              itemBuilder: (context, index) {
                if (index >= track.channels.length) {
                  final b = index - track.channels.length;
                  final bus = track.buses[b];
                  return _MixerChannelStrip(
                    index: b,
                    isBus: true,
                    label: 'BUS ${bus.name.toUpperCase()}',
                    color: _textDim,
                    volume: mix != null && b < mix.busVolumes.length ? mix.busVolumes[b] : bus.volume,
                    muted: mix != null && b < mix.busMutes.length ? mix.busMutes[b] : bus.muted,
                    soloed: bus.soloed,
                    route: bus.route,
                    onRouteToggled: () => notifier.updateBus(
                        bus.copyWith(route: ChannelRoute.values[(bus.route.index + 1) % ChannelRoute.values.length])),
                    onVolumeChanged: (v) => notifier.updateBus(bus.copyWith(volume: v)),
                    onMuteToggled: () => notifier.updateBus(bus.copyWith(muted: !bus.muted)),
                    onSoloToggled: () => notifier.toggleBusSolo(bus.id),
                  );
                }
                final channel = track.channels[index];
                return _MixerChannelStrip(
                  index: index,
                  label: channel.label,
                  color: _colorForChannel(index),
                  volume: mix != null && index < mix.volumes.length ? mix.volumes[index] : channel.volume,
                  muted: mix != null && index < mix.mutes.length ? mix.mutes[index] : channel.muted,
                  soloed: channel.soloed,
                  route: channel.route,
                  onRouteToggled: () => notifier.setChannelRoute(
                      index, ChannelRoute.values[(channel.route.index + 1) % ChannelRoute.values.length]),
                  onVolumeChanged: (v) => notifier.setChannelVolume(index, v),
                  onMuteToggled: () => notifier.setChannelMuted(index, !channel.muted),
                  onSoloToggled: () => notifier.toggleChannelSolo(index),
                );
              },
            ),
          ),
          Container(width: 1, color: _border, margin: const EdgeInsets.symmetric(horizontal: 6)),
          _MixerControls(track: track),
          const SizedBox(width: 6),
          _MasterStrip(volume: masterVolume, onChanged: notifier.setMasterVolume),
        ],
      ),
    );
  }
}

/// Coluna de controles ao lado do Master: AUTO (automação do mixer), laço da seção atual e laço infinito.
class _MixerControls extends ConsumerWidget {
  final Track track;
  const _MixerControls({required this.track});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final sections = track.sections;
    // Só reconstrói quando a seção sob a agulha ou o estado do laço muda, não a cada tick de posição.
    final at = ref.watch(transportProvider.select((t) => sections.indexWhere(
        (s) => t.positionSeconds >= s.playStart && t.positionSeconds < s.playEnd)));
    final loopEnabled = ref.watch(transportProvider.select((t) => t.loopEnabled));
    final repeats = ref.watch(transportProvider.select((t) => t.loopRepeats));
    final section = at >= 0 ? sections[at] : null;
    final transport = ref.read(transportProvider.notifier);
    final trackNotifier = ref.read(currentTrackProvider.notifier);

    Future<void> loop(SongSection s) async {
      final ok = await trackNotifier.setSectionLoop(s);
      if (!ok && context.mounted) {
        ScaffoldMessenger.of(context)
            .showSnackBar(const SnackBar(content: Text('Não foi possível preparar o loop desta seção.')));
      }
    }

    // "Laço": usa as repetições da própria seção; "Laço infinito": repete até soltar (escolha própria de mapeamento
    // para MixerLoopButton / "Inf Loop").
    final finite = loopEnabled && repeats > 0;
    final infinite = loopEnabled && repeats == 0;
    Widget cell(Widget child) => SizedBox(width: 52, height: 36, child: child);
    return SizedBox(
      width: 52,
      child: SingleChildScrollView(
        child: Column(children: [
          if (track.mixerAutomation.isNotEmpty) ...[
            SizedBox(
              key: const Key('transport-automation'),
              width: 52,
              height: 36,
              child: _SquareButton(
                tooltip: 'Automação do mixer',
                active: track.automationEnabled,
                onTap: () => trackNotifier.setAutomationEnabled(!track.automationEnabled),
                child: Text('AUTO',
                    style: TextStyle(
                        color: track.automationEnabled ? kStageGreen : _textFaint,
                        fontSize: 11,
                        fontWeight: FontWeight.w600)),
              ),
            ),
            const SizedBox(height: 6),
          ],
          cell(_SquareButton(
            tooltip: finite ? 'Desativar loop' : 'Repetir seção atual',
            active: finite,
            onTap: finite
                ? () => transport.disableLoop()
                : (section == null ? null : () => loop(section)),
            child: Icon(Icons.repeat, size: 20, color: finite ? kStageGreen : (section == null ? _border : _textDim)),
          )),
          const SizedBox(height: 6),
          cell(_SquareButton(
            tooltip: infinite ? 'Desativar loop' : 'Laço infinito na seção atual',
            active: infinite,
            onTap: infinite
                ? () => transport.disableLoop()
                : (section == null ? null : () => loop(section.copyWith(loopCount: 0))),
            child: Icon(Icons.all_inclusive, size: 20, color: infinite ? kStageGreen : (section == null ? _border : _textDim)),
          )),
        ]),
      ),
    );
  }
}

class _MasterStrip extends StatelessWidget {
  final double volume; // 0..2
  final ValueChanged<double> onChanged;
  const _MasterStrip({required this.volume, required this.onChanged});

  @override
  Widget build(BuildContext context) {
    return SizedBox(
      width: 64,
      child: Column(children: [
        Expanded(
          child: Row(children: [
            const _MasterMeter(),
            Expanded(
              child: _Fader(
                key: const Key('master-volume'),
                value: volume.clamp(0.0, 2.0),
                max: 2,
                color: _accent,
                onChanged: onChanged,
              ),
            ),
          ]),
        ),
        const Text('Master', style: TextStyle(color: _text, fontSize: 11)),
        Text('${(volume * 100).round()}%',
            style: const TextStyle(color: _textFaint, fontSize: 10, fontFeatures: [FontFeature.tabularFigures()])),
      ]),
    );
  }
}

/// Fader vertical com tampa (Playback: MixerTrackFaderCapView): trilho fino e tampa escura com a linha na cor do
/// canal.
class _Fader extends StatelessWidget {
  final double value, max;
  final Color color;
  final ValueChanged<double> onChanged;
  const _Fader({super.key, required this.value, this.max = 1, required this.color, required this.onChanged});

  @override
  Widget build(BuildContext context) {
    return RotatedBox(
      quarterTurns: 3,
      child: SliderTheme(
        data: SliderTheme.of(context).copyWith(
          trackHeight: 2,
          activeTrackColor: color.withValues(alpha: 0.55),
          inactiveTrackColor: _border,
          thumbShape: _FaderCapShape(color),
          overlayShape: const RoundSliderOverlayShape(overlayRadius: 14),
          overlayColor: color.withValues(alpha: 0.12),
        ),
        child: Slider(value: value, max: max, onChanged: onChanged),
      ),
    );
  }
}

class _FaderCapShape extends SliderComponentShape {
  final Color line;
  const _FaderCapShape(this.line);

  // No sistema do slider (horizontal, antes da rotação): estreita ao longo do trilho, larga atravessando.
  static const _size = Size(14, 28);

  @override
  Size getPreferredSize(bool isEnabled, bool isDiscrete) => _size;

  @override
  void paint(PaintingContext context, Offset center,
      {required Animation<double> activationAnimation,
      required Animation<double> enableAnimation,
      required bool isDiscrete,
      required TextPainter labelPainter,
      required RenderBox parentBox,
      required SliderThemeData sliderTheme,
      required TextDirection textDirection,
      required double value,
      required double textScaleFactor,
      required Size sizeWithOverflow}) {
    final canvas = context.canvas;
    final rect = Rect.fromCenter(center: center, width: _size.width, height: _size.height);
    canvas.drawRRect(RRect.fromRectAndRadius(rect, const Radius.circular(3)), Paint()..color = const Color(0xFF3A3B40));
    canvas.drawRRect(
        RRect.fromRectAndRadius(rect, const Radius.circular(3)),
        Paint()
          ..style = PaintingStyle.stroke
          ..color = const Color(0xFF55565C));
    canvas.drawRect(Rect.fromCenter(center: center, width: 2, height: _size.height - 6), Paint()..color = line);
  }
}

const _channelPalette = [
  Color(0xFFFF3B4E),
  Color(0xFFFFC107),
  Color(0xFFF5A020),
  Color(0xFFA78BFA),
  Color(0xFF00C896),
  Color(0xFF5B7CF5),
  Color(0xFFF03060),
  Color(0xFF00E5FF),
];

Color _colorForChannel(int index) => _channelPalette[index % _channelPalette.length];

class _MixerChannelStrip extends StatelessWidget {
  final String label;
  final Color color;
  final double volume; // 0.0 - 1.0
  final int index; // canal (ou bus) no motor (medidor)
  final bool isBus;
  final bool muted;
  final bool soloed;
  final ChannelRoute route;
  final VoidCallback onRouteToggled;
  final ValueChanged<double> onVolumeChanged;
  final VoidCallback onMuteToggled;
  final VoidCallback onSoloToggled;

  const _MixerChannelStrip({
    required this.label,
    required this.color,
    required this.volume,
    required this.index,
    this.isBus = false,
    required this.muted,
    required this.soloed,
    required this.route,
    required this.onRouteToggled,
    required this.onVolumeChanged,
    required this.onMuteToggled,
    required this.onSoloToggled,
  });

  String get _volumeLabel {
    if (volume >= 0.995) return '0 dB';
    if (volume <= 0.005) return '-∞';
    final db = ((volume - 1.0) * 60).round();
    return '$db dB';
  }

  @override
  Widget build(BuildContext context) {
    final labelColor = muted ? _textFaint : _textDim;
    return Container(
      width: 60,
      margin: const EdgeInsets.symmetric(horizontal: 2),
      decoration: BoxDecoration(
        color: isBus ? const Color(0xFF101114) : null,
        border: const Border(right: BorderSide(color: Color(0xFF16171A))),
      ),
      child: Column(
        children: [
          _RoundToggle(label: 'S', active: soloed, activeColor: kStageYellow, onTap: onSoloToggled),
          Expanded(
            child: Row(children: [
              const SizedBox(width: 4),
              _ChannelMeter(index: index, isBus: isBus),
              Expanded(
                child: _Fader(
                  value: volume.clamp(0.0, 1.0),
                  color: muted ? _textFaint : _accent,
                  onChanged: onVolumeChanged,
                ),
              ),
            ]),
          ),
          Text(_volumeLabel,
              style: TextStyle(color: labelColor, fontSize: 9, fontFeatures: const [FontFeature.tabularFigures()])),
          const SizedBox(height: 3),
          _MixerToggleButton(label: 'M', active: muted, activeColor: kStageRed, onTap: onMuteToggled, height: 22),
          const SizedBox(height: 3),
          _MixerToggleButton(
            label: switch (route) { ChannelRoute.stereo => 'ST', ChannelRoute.left => 'L', ChannelRoute.right => 'R' },
            active: route != ChannelRoute.stereo,
            activeColor: kStageBlue,
            onTap: onRouteToggled,
            height: 20,
          ),
          const SizedBox(height: 3),
          Row(children: [
            Container(
              width: 6,
              height: 6,
              margin: const EdgeInsets.only(left: 2, right: 3),
              decoration: BoxDecoration(color: muted ? _border : color, shape: BoxShape.circle),
            ),
            Expanded(
              child: Text(
                label,
                maxLines: 1,
                overflow: TextOverflow.ellipsis,
                style: TextStyle(color: muted ? _textFaint : _text, fontSize: 10),
              ),
            ),
          ]),
        ],
      ),
    );
  }
}

/// Botão redondo de solo no topo da faixa (Playback: "S" sobre o fader).
class _RoundToggle extends StatelessWidget {
  final String label;
  final bool active;
  final Color activeColor;
  final VoidCallback onTap;
  const _RoundToggle({required this.label, required this.active, required this.activeColor, required this.onTap});

  @override
  Widget build(BuildContext context) {
    return Material(
      color: active ? activeColor : _button,
      shape: CircleBorder(side: BorderSide(color: active ? activeColor : _border)),
      child: InkWell(
        onTap: onTap,
        customBorder: const CircleBorder(),
        child: SizedBox(
          width: 24,
          height: 24,
          child: Center(
            child: Text(label,
                style: TextStyle(color: active ? Colors.black : _textFaint, fontSize: 10, fontWeight: FontWeight.w700)),
          ),
        ),
      ),
    );
  }
}

/// Barra de nível (-60..0 dB): verde, amarelo a partir de -12 dB, vermelho a partir de -3 dB.
class _MeterBar extends StatelessWidget {
  final double level; // 0..1
  final double thickness;
  const _MeterBar({super.key, required this.level, this.thickness = 3});

  @override
  Widget build(BuildContext context) {
    final color = level >= 57 / 60
        ? kStageRed
        : level >= 48 / 60
            ? kStageYellow
            : kStageGreen;
    return Container(
      width: thickness,
      color: const Color(0xFF1A1B1E),
      child: FractionallySizedBox(
        alignment: Alignment.bottomCenter,
        heightFactor: level.clamp(0.0, 1.0),
        child: Container(color: color),
      ),
    );
  }
}

class _ChannelMeter extends ConsumerWidget {
  final int index;
  final bool isBus;
  const _ChannelMeter({required this.index, this.isBus = false});
  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final level = ref.watch(meterProvider.select((m) {
      final levels = isBus ? m.buses : m.channels;
      return index < levels.length ? levels[index] : 0.0;
    }));
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 10),
      child: _MeterBar(key: Key(isBus ? 'meter-bus-$index' : 'meter-$index'), level: level),
    );
  }
}

class _MasterMeter extends ConsumerWidget {
  const _MasterMeter();
  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final outputs = ref.watch(meterProvider.select((m) => m.outputs));
    double at(int i) => i < outputs.length ? outputs[i] : 0.0;
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 10),
      child: Row(children: [
        _MeterBar(key: const Key('meter-master-l'), level: at(0), thickness: 4),
        const SizedBox(width: 2),
        _MeterBar(key: const Key('meter-master-r'), level: at(1), thickness: 4),
      ]),
    );
  }
}

class _MixerToggleButton extends StatelessWidget {
  final String label;
  final bool active;
  final Color activeColor;
  final VoidCallback onTap;
  final double height;

  const _MixerToggleButton({
    required this.label,
    required this.active,
    required this.activeColor,
    required this.onTap,
    this.height = 26,
  });

  @override
  Widget build(BuildContext context) {
    return Material(
      color: active ? activeColor : _button,
      shape: RoundedRectangleBorder(
        borderRadius: BorderRadius.circular(4),
        side: BorderSide(color: active ? activeColor : _border),
      ),
      child: InkWell(
        onTap: onTap,
        borderRadius: BorderRadius.circular(4),
        child: SizedBox(
          width: 48,
          height: height,
          child: Center(
            child: Text(
              label,
              style: TextStyle(
                color: active ? Colors.white : _textDim,
                fontWeight: FontWeight.bold,
                fontSize: 10,
                letterSpacing: 1,
              ),
            ),
          ),
        ),
      ),
    );
  }
}
