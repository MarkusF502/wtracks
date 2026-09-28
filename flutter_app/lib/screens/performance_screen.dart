import 'dart:math' as math;

import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/track.dart';
import '../providers/engine_provider.dart';
import '../providers/waveform_provider.dart';
import '../utils/tap_tempo.dart';

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
final clickEnabledProvider = StateProvider<bool>((ref) => false);

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
          IconButton(
            icon: const Icon(Icons.save_outlined),
            tooltip: 'Salvar',
            onPressed: () => _save(context, ref),
          ),
        ],
      ),
      body: SafeArea(
        child: isLandscape
            ? _buildLandscapeLayout(track, transportNotifier, context, ref)
            : _buildPortraitLayout(track, transportNotifier, context, ref),
      ),
    );
  }

  Future<void> _renameTrack(BuildContext context, WidgetRef ref, Track track) async {
    final controller = TextEditingController(text: track.title);
    final newTitle = await showDialog<String>(
      context: context,
      builder: (ctx) => AlertDialog(
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
    );
    controller.dispose();

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
    if (oldWidget.track.id != widget.track.id) _load();
  }

  void _load() {
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
                  const Text('Ajustar BPM do Metrônomo', style: TextStyle(color: Colors.white, fontSize: 16)),
                  const SizedBox(height: 24),
                  Row(
                    children: [
                      Text(tempBpm.round().toString(), style: const TextStyle(color: _accent, fontSize: 24, fontWeight: FontWeight.bold)),
                      if (calibrated) ...[
                        const SizedBox(width: 6),
                        const Icon(Icons.check_circle, color: _accent, size: 18),
                      ],
                      Expanded(
                        child: Slider(
                          value: tempBpm,
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
                  Text(tapHint, style: const TextStyle(color: _textFaint, fontSize: 13)),
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
                          child: const Text('TAP', style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold)),
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
                  const Text('Offset do click', style: TextStyle(color: Colors.white, fontSize: 16)),
                  const SizedBox(height: 8),
                  // Lê o offset do provider (não do `track` capturado ao abrir
                  // o diálogo), senão o valor exibido nunca atualiza.
                  Consumer(builder: (context, ref, _) {
                    final offset = ref.watch(currentTrackProvider
                        .select((t) => t?.clickSettings.beatOffsetSeconds ?? 0.0));
                    return Text(
                      '${offset >= 0 ? '+' : ''}${offset.toStringAsFixed(2)}s',
                      style: const TextStyle(color: _accent, fontSize: 18, fontWeight: FontWeight.bold),
                    );
                  }),
                  const SizedBox(height: 8),
                  if (!isPlaying)
                    const Text('Toque play e marque no primeiro tempo real',
                        style: TextStyle(color: _textFaint, fontSize: 13)),
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
            ));
          }
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
          _PlayButton(isPlaying: isPlaying, onTap: onPlayPause),
          
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

class _TransportButton extends StatelessWidget {
  final IconData icon;
  final Color accent;
  final bool isActive;
  final VoidCallback onTap;

  const _TransportButton({required this.icon, required this.accent, required this.onTap, this.isActive = false});

  @override
  Widget build(BuildContext context) {
    return Material(
      color: isActive ? accent.withValues(alpha: 0.15) : const Color(0xFF1A1A25),
      shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(10), side: BorderSide(color: isActive ? accent : _border, width: 1.5)),
      child: InkWell(
        onTap: onTap,
        borderRadius: BorderRadius.circular(10),
        child: SizedBox(width: 48, height: 48, child: Icon(icon, color: isActive ? accent : _textDim)),
      ),
    );
  }
}

class _PlayButton extends StatelessWidget {
  final bool isPlaying;
  final VoidCallback onTap;

  const _PlayButton({required this.isPlaying, required this.onTap});

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
          child: Icon(isPlaying ? Icons.pause : Icons.play_arrow,
              color: isPlaying ? _accent : _bg, size: 28),
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
            child: const Text('MIXER',
                style: TextStyle(
                    color: _textFaint, fontSize: 11, fontWeight: FontWeight.bold, letterSpacing: 1.5)),
          ),
          Expanded(
            child: ListView.builder(
              scrollDirection: Axis.horizontal,
              padding: const EdgeInsets.symmetric(horizontal: 8, vertical: 8),
              itemCount: track.channels.length,
              itemBuilder: (context, index) {
                final channel = track.channels[index];
                return _MixerChannelStrip(
                  label: channel.label,
                  color: _colorForChannel(index),
                  volume: channel.volume,
                  muted: channel.muted,
                  soloed: channel.soloed,
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
  final bool muted;
  final bool soloed;
  final ValueChanged<double> onVolumeChanged;
  final VoidCallback onMuteToggled;
  final VoidCallback onSoloToggled;

  const _MixerChannelStrip({
    required this.label,
    required this.color,
    required this.volume,
    required this.muted,
    required this.soloed,
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