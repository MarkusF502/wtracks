import 'dart:math' as math;

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/track.dart';
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

const _bg = Color(0xFF07070E);
const _panelBg = Color(0xFF111119);
const _mixerBg = Color(0xFF0A0A12);
const _border = Color(0xFF1E1E2E);
const _textDim = Color(0xFF8888A8);
const _textFaint = Color(0xFF44445A);
const _accent = Color(0xFF00E5FF);

String _formatTime(double seconds) {
  final total = seconds.isFinite ? seconds.floor() : 0;
  final m = total ~/ 60;
  final s = total % 60;
  return '$m:${s.toString().padLeft(2, '0')}';
}

// Provider local para gerenciar o estado do botão de Metrônomo (Click)

class PerformanceScreen extends ConsumerWidget {
  const PerformanceScreen({super.key});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final track = ref.watch(currentTrackProvider);
    // NÃO observamos transportProvider aqui de propósito: ele muda a cada
    // 100ms (polling da posição de playback) e, se observado neste nível,
    // reconstrói a árvore inteira (incluindo o Mixer, que não depende de
    // posição/tempo nenhum) 10x por segundo. Cada widget que realmente
    // precisa da posição/isPlaying (_Header, _WaveformTimeline, _Transport)
    // observa transportProvider por conta própria, então só eles são
    // reconstruídos a cada tick.
    final transportNotifier = ref.read(transportProvider.notifier);
    ref.watch(controlProvider.select((c) => c.inputOpen)); // mantém a leitura da entrada MIDI mapeada

    // Detecta a orientação do celular
    final isLandscape = MediaQuery.of(context).orientation == Orientation.landscape;

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
      appBar: AppBar(
        backgroundColor: _panelBg,
        title: InkWell(
          onTap: () => _renameTrack(context, ref, track),
          child: Row(
            mainAxisSize: MainAxisSize.min,
            children: [
              Flexible(child: Text(track.title, overflow: TextOverflow.ellipsis)),
              const SizedBox(width: 6),
              const Icon(Icons.edit, size: 16, color: _textDim),
            ],
          ),
        ),
        actions: [
          PopupMenuButton<String>(
            tooltip: 'Mais',
            icon: const Icon(Icons.more_vert),
            onSelected: (choice) {
              switch (choice) {
                case 'midi':
                  Navigator.of(context).push(MaterialPageRoute<void>(builder: (_) => MidiScreen(trackId: track.id)));
                case 'pitch':
                  showModalBottomSheet<void>(context: context, isScrollControlled: true, builder: (_) => TimePitchSheet(trackId: track.id));
                case 'guides':
                  Navigator.of(context).push(MaterialPageRoute<void>(builder: (_) => GuideEditorScreen(trackId: track.id)));
                case 'tempo':
                  Navigator.of(context).push(MaterialPageRoute<void>(builder: (_) => TempoMapScreen(trackId: track.id)));
                case 'mapping':
                  Navigator.of(context).push(MaterialPageRoute<void>(builder: (_) => const ControlMappingScreen()));
                case 'buses':
                  Navigator.of(context).push(MaterialPageRoute<void>(builder: (_) => BusesScreen(trackId: track.id)));
                case 'ending':
                  showModalBottomSheet<void>(context: context, isScrollControlled: true, builder: (_) => const SongEndingSheet());
                case 'automation':
                  Navigator.of(context).push(MaterialPageRoute<void>(builder: (_) => MixerAutomationScreen(trackId: track.id)));
              }
            },
            itemBuilder: (_) => const [
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
          IconButton(icon: const Icon(Icons.segment), tooltip: 'Seções',
            onPressed: () => Navigator.of(context).push(MaterialPageRoute<void>(
              builder: (_) => SectionEditorScreen(trackId: track.id)))),
          IconButton(
            icon: const Icon(Icons.save_outlined),
            tooltip: 'Salvar',
            onPressed: () => _save(context, ref),
          ),
        ],
      ),
      // Atalhos de teclado (Keyboard Mapping) e entrada MIDI mapeada ficam ativos enquanto a performance está aberta.
      body: Focus(
        autofocus: true,
        onKeyEvent: (_, event) {
          if (event is! KeyDownEvent) return KeyEventResult.ignored;
          final control = ref.read(controlProvider.notifier);
          return control.handleKey(event.logicalKey.keyLabel) ? KeyEventResult.handled : KeyEventResult.ignored;
        },
        child: SafeArea(
          child: isLandscape
              ? _buildLandscapeLayout(track, transportNotifier, context, ref)
              : _buildPortraitLayout(track, transportNotifier, context, ref),
        ),
      ),
    );
  }

  Future<void> _renameTrack(BuildContext context, WidgetRef ref, Track track) async {
    final newTitle = await showDialog<String>(
      context: context,
      builder: (ctx) => DialogTextController(
        initialText: track.title,
        builder: (controller) => AlertDialog(
          backgroundColor: _panelBg,
          title: const Text('Renomear música', style: TextStyle(color: Color(0xFFF0F0FA))),
          content: TextField(
            controller: controller,
            autofocus: true,
            style: const TextStyle(color: Color(0xFFF0F0FA)),
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

    // Se a música já estava salva na biblioteca, persiste o novo nome
    // também -- senão a renomeação só sobrevive em memória.
    final alreadySaved =
        ref.read(trackLibraryProvider).any((t) => t.id == track.id);
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

  Widget _buildPortraitLayout(Track track, TransportNotifier notifier, BuildContext context, WidgetRef ref) {
    return Column(
      children: [
        _Header(track: track),
        _SetlistBar(track: track),
        _WaveformTimeline(track: track, onSeek: notifier.seekTo),
        _Transport(onStop: notifier.stop, track: track),
        Expanded(child: _Mixer(track: track)),
      ],
    );
  }

  Widget _buildLandscapeLayout(Track track, TransportNotifier notifier, BuildContext context, WidgetRef ref) {
    return Row(
      children: [
        // Painel Esquerdo: Controles
        SizedBox(
          width: 320,
          child: Column(
            children: [
              _Header(track: track),
              _SetlistBar(track: track),
              _WaveformTimeline(track: track, onSeek: notifier.seekTo),
              Expanded(
                child: Center(
                  child: _Transport(onStop: notifier.stop, track: track),
                ),
              ),
            ],
          ),
        ),
        const VerticalDivider(width: 1, color: _border),
        // Painel Direito: Mixer (ocupa todo o resto e respira verticalmente)
        Expanded(child: _Mixer(track: track)),
      ],
    );
  }
}

class _Header extends ConsumerWidget {
  final Track track;

  const _Header({required this.track});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    // Único ponto que observa a posição/duração aqui -- isola o rebuild de
    // 10x/s (polling do transportProvider) a este widget pequeno, em vez de
    // reconstruir a tela inteira (mixer incluído).
    final transport = ref.watch(transportProvider);
    return Container(
      height: 52,
      padding: const EdgeInsets.symmetric(horizontal: 16),
      decoration: const BoxDecoration(
        color: _panelBg,
        border: Border(bottom: BorderSide(color: _border)),
      ),
      child: Row(
        children: [
          Expanded(
            child: Text(
              track.title,
              style: const TextStyle(
                  color: Color(0xFFF0F0FA), fontSize: 18, fontWeight: FontWeight.bold),
              overflow: TextOverflow.ellipsis,
            ),
          ),
          const SizedBox(width: 12),
          Text.rich(
            TextSpan(
              children: [
                TextSpan(
                  text: _formatTime(transport.positionSeconds),
                  style: const TextStyle(
                      color: _accent,
                      fontSize: 18,
                      fontWeight: FontWeight.bold,
                      fontFeatures: [FontFeature.tabularFigures()]),
                ),
                TextSpan(
                  text: ' / ${_formatTime(transport.lengthSeconds)}',
                  style: const TextStyle(color: _textFaint, fontSize: 13),
                ),
              ],
            ),
          ),
        ],
      ),
    );
  }
}

class _Timeline extends StatelessWidget {
  final TransportState transport;
  final ValueChanged<double> onSeek;

  const _Timeline({required this.transport, required this.onSeek});

  @override
  Widget build(BuildContext context) {
    final length = transport.lengthSeconds > 0 ? transport.lengthSeconds : 1.0;
    return Container(
      height: 56,
      padding: const EdgeInsets.symmetric(horizontal: 12),
      decoration: const BoxDecoration(border: Border(bottom: BorderSide(color: _border))),
      child: Center(
        child: SliderTheme(
          data: SliderTheme.of(context).copyWith(
            activeTrackColor: _accent,
            inactiveTrackColor: _border,
            thumbColor: _accent,
            overlayColor: _accent.withValues(alpha: 0.2),
          ),
          child: Slider(
            value: transport.positionSeconds.clamp(0, length),
            max: length,
            onChanged: (_) {},
            onChangeEnd: onSeek,
          ),
        ),
      ),
    );
  }
}

/// Timeline em waveform: substitui o [_Timeline] antigo como área de seek
/// principal, mas cai de volta pro slider simples se a waveform não estiver
/// disponível (falha na extração ou nunca gerada) -- garante que seek
/// continua funcionando mesmo sem waveform.
class _WaveformTimeline extends ConsumerStatefulWidget {
  final Track track;
  final ValueChanged<double> onSeek;

  const _WaveformTimeline({
    required this.track,
    required this.onSeek,
  });

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

  void _handleSeek(Offset localPosition, double width) {
    // ref.read (não watch) -- só precisamos do valor no momento do toque,
    // este método não faz parte do build.
    final length = ref.read(transportProvider).lengthSeconds;
    if (length <= 0 || width <= 0) return;
    final fraction = (localPosition.dx / width).clamp(0.0, 1.0);
    widget.onSeek(fraction * length);
  }

  @override
  Widget build(BuildContext context) {
    final waveform = ref.watch(waveformProvider);
    final transport = ref.watch(transportProvider);

    if (waveform.isGenerating) {
      return Container(
        height: 56,
        padding: const EdgeInsets.symmetric(horizontal: 12),
        decoration: const BoxDecoration(border: Border(bottom: BorderSide(color: _border))),
        child: const Center(
          child: Text('Gerando waveform...', style: TextStyle(color: _textFaint, fontSize: 12)),
        ),
      );
    }

    final peaks = waveform.peaks;
    if (peaks == null) {
      return _Timeline(transport: transport, onSeek: widget.onSeek);
    }

    final length = transport.lengthSeconds > 0 ? transport.lengthSeconds : 1.0;
    final progress =
        (transport.positionSeconds / length).clamp(0.0, 1.0).toDouble();

    return Container(
      height: 56,
      padding: const EdgeInsets.symmetric(horizontal: 12),
      decoration: const BoxDecoration(border: Border(bottom: BorderSide(color: _border))),
      child: LayoutBuilder(
        builder: (context, constraints) {
          final width = constraints.maxWidth;
          return GestureDetector(
            onTapDown: (details) => _handleSeek(details.localPosition, width),
            onHorizontalDragUpdate: (details) => _handleSeek(details.localPosition, width),
            child: CustomPaint(
              size: Size(width, constraints.maxHeight),
              painter: _WaveformPainter(peaks: peaks, progress: progress),
            ),
          );
        },
      ),
    );
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

    final playedPaint = Paint()..color = _accent;
    final remainingPaint = Paint()..color = _border;

    // Deixa 1px de respiro entre as barras quando há espaço pra isso --
    // em telas estreitas com muitos buckets, barWidth pode ficar menor
    // que 1px, e aí desenha a barra cheia sem gap (um `clamp(1.0,
    // barWidth)` com barWidth < 1.0 lançaria ArgumentError: min > max).
    final rectWidth = barWidth > 1.0 ? barWidth - 1.0 : barWidth;

    for (var i = 0; i < peaks.length; i++) {
      final barHeight = math.min(size.height, (peaks[i].clamp(0.0, 1.0)) * size.height);
      final left = i * barWidth;
      final rect = Rect.fromLTWH(left, centerY - barHeight / 2, rectWidth, barHeight);
      canvas.drawRect(rect, i < playedBars ? playedPaint : remainingPaint);
    }
  }

  @override
  bool shouldRepaint(covariant _WaveformPainter oldDelegate) {
    return oldDelegate.peaks != peaks || oldDelegate.progress != progress;
  }
}

class _Transport extends ConsumerWidget {
  final VoidCallback onStop;
  final Track track;

  const _Transport({
    required this.onStop,
    required this.track,
  });

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

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final clickEnabled = ref.watch(clickEnabledProvider);
    // Único ponto de _Transport que precisa saber se está tocando -- usa
    // `select` pra só reconstruir este widget quando isPlaying de fato
    // muda (não a cada tick de posição/duração do polling de 100ms).
    final isPlaying = ref.watch(transportProvider.select((t) => t.isPlaying));
    final prerolling = ref.watch(transportProvider.select((t) => t.prerolling));
    final fading = ref.watch(transportProvider.select((t) => t.fading));
    final transportNotifier = ref.read(transportProvider.notifier);
    final onPlayPause = isPlaying ? transportNotifier.pause : transportNotifier.play;

    return Container(
      padding: const EdgeInsets.symmetric(vertical: 16),
      decoration: const BoxDecoration(
        color: Color(0xFF0D0D18),
        border: Border(bottom: BorderSide(color: _border)),
      ),
      child: Row(
        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
        children: [
          // Metrônomo (Click) Toggle
          _TransportButton(
            icon: Icons.timer, 
            accent: const Color(0xFF00FF88), 
            isActive: clickEnabled,
            onTap: () {
              final newState = !clickEnabled;
              ref.read(clickEnabledProvider.notifier).state = newState;
              ref.read(engineProvider).setClickEnabled(newState);
            }
          ),
          _TransportButton(icon: Icons.stop, accent: const Color(0xFFFF3B4E), onTap: onStop),
          _PlayButton(isPlaying: isPlaying, prerolling: prerolling, onTap: onPlayPause),
          _TransportButton(
            icon: Icons.trending_down,
            accent: const Color(0xFFF5A020),
            isActive: fading,
            tooltip: 'Fade de 5 segundos',
            onTap: () => transportNotifier.fadeOut(),
          ),
          
          // Indicador de BPM clicável
          GestureDetector(
            onTap: () => _showBpmDialog(context, ref, isPlaying),
            child: Container(
              padding: const EdgeInsets.symmetric(horizontal: 12, vertical: 8),
              decoration: BoxDecoration(
                color: _panelBg,
                border: Border.all(color: _border),
                borderRadius: BorderRadius.circular(8),
              ),
              child: Column(
                mainAxisSize: MainAxisSize.min,
                children: [
                  Row(
                    mainAxisSize: MainAxisSize.min,
                    children: [
                      Text(track.clickSettings.bpm.round().toString(),
                          style: const TextStyle(
                              color: _accent, fontSize: 18, fontWeight: FontWeight.bold)),
                      if (track.clickSettings.calibrated) ...[
                        const SizedBox(width: 4),
                        const Icon(Icons.check_circle, color: _accent, size: 12),
                      ],
                    ],
                  ),
                  const Text('BPM', style: TextStyle(color: _textFaint, fontSize: 11)),
                ],
              ),
            ),
          ),
        ],
      ),
    );
  }
}

/// Setlist em execução: posição, próxima música e navegação.
class _SetlistBar extends ConsumerWidget {
  final Track track;
  const _SetlistBar({required this.track});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final session = ref.watch(setlistSessionProvider);
    if (session == null || session.current.id != track.id) return const SizedBox.shrink();
    final notifier = ref.read(setlistSessionProvider.notifier);
    final next = session.next;
    final label = next == null
        ? 'Última música'
        : (track.transition == SongTransition.cueNextSong ? 'Próxima: ${next.title}' : 'Fica na música · depois: ${next.title}');
    return Container(
      height: 36,
      padding: const EdgeInsets.symmetric(horizontal: 4),
      decoration: const BoxDecoration(border: Border(bottom: BorderSide(color: _border))),
      child: Row(
        children: [
          IconButton(
            tooltip: 'Música anterior',
            iconSize: 18,
            visualDensity: VisualDensity.compact,
            onPressed: session.previous == null ? null : notifier.previous,
            icon: const Icon(Icons.skip_previous),
          ),
          Text('${session.index + 1}/${session.setlist.tracks.length}', style: const TextStyle(color: _textFaint, fontSize: 11)),
          const SizedBox(width: 8),
          Expanded(child: Text(label, overflow: TextOverflow.ellipsis, style: const TextStyle(color: _textDim, fontSize: 12))),
          IconButton(
            tooltip: 'Próxima música',
            iconSize: 18,
            visualDensity: VisualDensity.compact,
            onPressed: next == null ? null : notifier.next,
            icon: const Icon(Icons.skip_next),
          ),
        ],
      ),
    );
  }
}

class _TransportButton extends StatelessWidget {
  final IconData icon;
  final Color accent;
  final bool isActive;
  final VoidCallback onTap;
  final String? tooltip;

  const _TransportButton({required this.icon, required this.accent, required this.onTap, this.isActive = false, this.tooltip});

  @override
  Widget build(BuildContext context) {
    return Material(
      color: isActive ? accent.withValues(alpha: 0.15) : const Color(0xFF1A1A25),
      shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(10), side: BorderSide(color: isActive ? accent : _border, width: 1.5)),
      child: InkWell(
        onTap: onTap,
        borderRadius: BorderRadius.circular(10),
        child: SizedBox(
            width: 48,
            height: 48,
            child: tooltip == null
                ? Icon(icon, color: isActive ? accent : _textDim)
                : Tooltip(message: tooltip!, child: Icon(icon, color: isActive ? accent : _textDim))),
      ),
    );
  }
}

class _PlayButton extends StatelessWidget {
  final bool isPlaying;
  final bool prerolling; // contagem do pré-roll antes da seção
  final VoidCallback onTap;

  const _PlayButton({required this.isPlaying, this.prerolling = false, required this.onTap});

  @override
  Widget build(BuildContext context) {
    return Material(
      color: isPlaying ? _accent.withValues(alpha: 0.13) : _accent,
      shape: CircleBorder(side: BorderSide(color: _accent, width: 3)),
      child: InkWell(
        onTap: onTap,
        customBorder: const CircleBorder(),
        child: SizedBox(
          width: 64,
          height: 64,
          child: Tooltip(
            message: prerolling ? 'Contagem' : (isPlaying ? 'Pausar' : 'Tocar'),
            child: Icon(prerolling ? Icons.av_timer : (isPlaying ? Icons.pause : Icons.play_arrow),
                color: isPlaying ? _accent : _bg, size: 28),
          ),
        ),
      ),
    );
  }
}

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
      color: _mixerBg,
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Container(
            height: 28,
            alignment: Alignment.centerLeft,
            padding: const EdgeInsets.symmetric(horizontal: 16),
            decoration: const BoxDecoration(border: Border(bottom: BorderSide(color: _border))),
            child: Row(
              children: [
                const Text('MIXER',
                    style: TextStyle(
                        color: _textFaint, fontSize: 11, fontWeight: FontWeight.bold, letterSpacing: 1.5)),
                const Spacer(),
                if (track.mixerAutomation.isNotEmpty)
                  TextButton(
                    key: const Key('transport-automation'),
                    onPressed: () => notifier.setAutomationEnabled(!track.automationEnabled),
                    child: Text('AUTO',
                        style: TextStyle(
                            color: track.automationEnabled ? const Color(0xFF00FF88) : _textFaint,
                            fontSize: 11,
                            fontWeight: FontWeight.bold)),
                  ),
                const Text('MASTER', style: TextStyle(color: _textFaint, fontSize: 10)),
                Flexible(
                  flex: 4,
                  child: ConstrainedBox(
                    constraints: const BoxConstraints(maxWidth: 140),
                    child: SliderTheme(
                      data: SliderTheme.of(context).copyWith(trackHeight: 2, overlayShape: SliderComponentShape.noOverlay),
                      child: Slider(
                        key: const Key('master-volume'),
                        value: masterVolume.clamp(0.0, 2.0),
                        max: 2,
                        onChanged: notifier.setMasterVolume,
                      ),
                    ),
                  ),
                ),
                Text('${(masterVolume * 100).round()}%',
                    style: const TextStyle(color: _textFaint, fontSize: 10)),
                const SizedBox(width: 6),
                const _MasterMeter(),
              ],
            ),
          ),
          Expanded(
            child: ListView.builder(
              scrollDirection: Axis.horizontal,
              padding: const EdgeInsets.symmetric(horizontal: 8, vertical: 8),
              itemCount: track.channels.length + track.buses.length,
              itemBuilder: (context, index) {
                if (index >= track.channels.length) {
                  final b = index - track.channels.length;
                  final bus = track.buses[b];
                  return _MixerChannelStrip(
                    index: b,
                    isBus: true,
                    label: 'BUS ${bus.name}',
                    color: const Color(0xFF8A8AA0),
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
        ],
      ),
    );
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
      width: 76,
      margin: const EdgeInsets.symmetric(horizontal: 3),
      decoration: BoxDecoration(
        color: _panelBg,
        border: Border.all(color: _border),
        borderRadius: BorderRadius.circular(10),
      ),
      child: Column(
        children: [
          Container(height: 4, color: muted ? _border : color),
          Container(
            height: 30,
            width: double.infinity,
            alignment: Alignment.center,
            padding: const EdgeInsets.symmetric(horizontal: 4),
            decoration: const BoxDecoration(border: Border(bottom: BorderSide(color: _border))),
            child: Text(
              label.toUpperCase(),
              textAlign: TextAlign.center,
              maxLines: 1,
              overflow: TextOverflow.ellipsis,
              style: TextStyle(color: labelColor, fontSize: 10, fontWeight: FontWeight.w600),
            ),
          ),
          Expanded(
            child: Row(children: [
              const SizedBox(width: 6),
              _ChannelMeter(index: index, isBus: isBus),
              Expanded(
            child: RotatedBox(
              quarterTurns: 3,
              child: SliderTheme(
                data: SliderTheme.of(context).copyWith(
                  activeTrackColor: muted ? _textFaint : color,
                  inactiveTrackColor: _border,
                  thumbColor: muted ? _textFaint : color,
                  trackHeight: 3,
                ),
                child: Slider(
                  value: volume.clamp(0.0, 1.0),
                  onChanged: onVolumeChanged,
                ),
              ),
            ),
          ),
            ]),
          ),
          Padding(
            padding: const EdgeInsets.symmetric(vertical: 4),
            child: Text(_volumeLabel,
                style: TextStyle(color: labelColor, fontSize: 10, fontFeatures: const [FontFeature.tabularFigures()])),
          ),
          _MixerToggleButton(
            label: 'M',
            active: muted,
            activeColor: const Color(0xFFFF3B4E),
            onTap: onMuteToggled,
          ),
          const SizedBox(height: 4),
          _MixerToggleButton(
            label: switch (route) { ChannelRoute.stereo => 'ST', ChannelRoute.left => 'L', ChannelRoute.right => 'R' },
            active: route != ChannelRoute.stereo,
            activeColor: const Color(0xFF5B7CF5),
            onTap: onRouteToggled,
            height: 22,
          ),
          const SizedBox(height: 4),
          _MixerToggleButton(
            label: 'S',
            active: soloed,
            activeColor: const Color(0xFFFFC107),
            activeTextColor: _bg,
            onTap: onSoloToggled,
            height: 22,
          ),
          const SizedBox(height: 6),
        ],
      ),
    );
  }
}

/// Barra de nível (-60..0 dB): verde, amarelo a partir de -12 dB, vermelho a partir de -3 dB.
class _MeterBar extends StatelessWidget {
  final double level; // 0..1
  final Axis axis;
  final double thickness;
  const _MeterBar({super.key, required this.level, this.axis = Axis.vertical, this.thickness = 4});

  @override
  Widget build(BuildContext context) {
    final color = level >= 57 / 60
        ? const Color(0xFFFF3B4E)
        : level >= 48 / 60
            ? const Color(0xFFFFC107)
            : const Color(0xFF00C896);
    return Container(
      width: axis == Axis.vertical ? thickness : null,
      height: axis == Axis.horizontal ? thickness : null,
      color: _border,
      child: FractionallySizedBox(
        alignment: axis == Axis.vertical ? Alignment.bottomCenter : Alignment.centerLeft,
        heightFactor: axis == Axis.vertical ? level : null,
        widthFactor: axis == Axis.horizontal ? level : null,
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
      padding: const EdgeInsets.symmetric(vertical: 8),
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
    return SizedBox(
      width: 36,
      child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          _MeterBar(key: const Key('meter-master-l'), level: at(0), axis: Axis.horizontal, thickness: 3),
          const SizedBox(height: 2),
          _MeterBar(key: const Key('meter-master-r'), level: at(1), axis: Axis.horizontal, thickness: 3),
        ],
      ),
    );
  }
}

class _MixerToggleButton extends StatelessWidget {
  final String label;
  final bool active;
  final Color activeColor;
  final Color activeTextColor;
  final VoidCallback onTap;
  final double height;

  const _MixerToggleButton({
    required this.label,
    required this.active,
    required this.activeColor,
    required this.onTap,
    this.activeTextColor = Colors.white,
    this.height = 26,
  });

  @override
  Widget build(BuildContext context) {
    return Material(
      color: active ? activeColor : const Color(0xFF1F1F2D),
      shape: RoundedRectangleBorder(
        borderRadius: BorderRadius.circular(4),
        side: BorderSide(color: active ? activeColor : _border, width: 1.5),
      ),
      child: InkWell(
        onTap: onTap,
        borderRadius: BorderRadius.circular(4),
        child: SizedBox(
          width: 56,
          height: height,
          child: Center(
            child: Text(
              label,
              style: TextStyle(
                color: active ? activeTextColor : _textDim,
                fontWeight: FontWeight.bold,
                fontSize: 11,
                letterSpacing: 1,
              ),
            ),
          ),
        ),
      ),
    );
  }
}