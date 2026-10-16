import 'dart:math' as math;

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/song_section.dart';
import '../models/track.dart';
import '../theme/app_colors.dart';
import '../widgets/dialog_text_controller.dart';
import '../providers/engine_provider.dart';
import '../providers/transition_provider.dart';
import '../providers/waveform_provider.dart';
import '../services/dynamic_guides.dart' show TempoSegment;
import '../utils/tap_tempo.dart';
import 'section_editor_screen.dart';
import 'guide_editor_screen.dart';
import 'time_pitch_sheet.dart';
import 'midi_screen.dart';
import 'tempo_map_screen.dart';
import 'mixer_automation_screen.dart';
import 'song_ending_sheet.dart';
import 'song_range_sheet.dart';
import 'buses_screen.dart';
import 'control_mapping_screen.dart';
import 'library_screen.dart';
import 'setlists_screen.dart';
import 'settings_screen.dart';
import 'remote_screen.dart';
import 'import_screen.dart';
import 'multitracks_library_screen.dart';
import '../providers/control_provider.dart';
import '../providers/meter_provider.dart';
import '../services/diagnostics_log.dart';
import 'diagnostics_screen.dart';

// Tela única no modelo do Playback (guia do usuário, docs/playback-analysis/ui/helpcenter): barra superior, faixa da
// setlist, waveform das seções e o painel de faixas/buses com o console e o Master. Biblioteca, setlists, edição da
// música e ajustes abrem por cima dela. Cores medidas nas capturas; proporções e o que não aparece no guia são escolha
// própria.
const _bg = kStageBg;
const _panelBg = kStagePanel;
const _button = kStageButton;
const _border = kStageBorder;
const _text = kStageText;
const _textDim = kStageTextDim;
const _textFaint = kStageTextFaint;
const _accent = kStageFaderLine;

String _formatTime(double seconds) {
  final total = seconds.isFinite ? seconds.floor() : 0;
  final m = total ~/ 60;
  final s = total % 60;
  return '$m:${s.toString().padLeft(2, '0')}';
}

String _clock(double seconds) {
  final total = seconds.isFinite ? seconds.floor() : 0;
  return '${(total ~/ 60).toString().padLeft(2, '0')}:${(total % 60).toString().padLeft(2, '0')}';
}

/// Modo de edição da setlist (Playback: EDIT → DONE).
final performanceEditProvider = StateProvider<bool>((ref) => false);

/// O que o painel de baixo mostra (Playback: botão do console alterna Tracks / Buses / Waveform no iPhone).
enum _Pane { tracks, buses, waveform }

final _paneProvider = StateProvider<_Pane?>((ref) => null);

class PerformanceScreen extends ConsumerWidget {
  const PerformanceScreen({super.key});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final track = ref.watch(currentTrackProvider);
    // NÃO observamos transportProvider aqui: ele muda a cada 100ms e reconstruiria a tela inteira, mixer incluído.
    ref.watch(controlProvider.select((c) => c.inputOpen)); // mantém a leitura da entrada MIDI mapeada
    // Mantém a biblioteca viva: é ela que grava automaticamente cada mudança da música aberta.
    ref.watch(trackLibraryProvider.select((library) => library.length));
    // Falhas de leitura/gravação nunca passam caladas.
    ref.listen<String?>(persistenceAlertProvider, (_, message) {
      if (message == null) return;
      ScaffoldMessenger.of(context).showSnackBar(SnackBar(
        content: Text(message),
        duration: const Duration(seconds: 8),
        action: SnackBarAction(
          label: 'Detalhes',
          onPressed: () => Navigator.of(context).push(MaterialPageRoute<void>(builder: (_) => const DiagnosticsScreen())),
        ),
      ));
      Future.microtask(() => ref.read(persistenceAlertProvider.notifier).state = null);
    });

    return Scaffold(
      backgroundColor: _bg,
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
            if (track == null) return _EmptyPerformance(wide: wide);
            // No celular deitado a waveform divide o painel de baixo com o mixer (Playback no iPhone).
            final pane = ref.watch(_paneProvider) ?? (short ? _Pane.waveform : _Pane.tracks);
            return Column(
              children: [
                _TopBar(track: track, wide: wide),
                _SetlistRow(track: track, compact: short),
                const _TransitionNoticeBar(),
                if (!short) _WaveformView(track: track, height: wide ? 132 : 104),
                Expanded(child: _BottomPane(track: track, pane: pane, short: short)),
              ],
            );
          }),
        ),
      ),
    );
  }
}

/// Sem música: a faixa da setlist mostra só "ADICIONAR MÚSICA" (Playback: "ADD A SONG").
class _EmptyPerformance extends ConsumerWidget {
  final bool wide;
  const _EmptyPerformance({required this.wide});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    return Column(children: [
      Container(
        color: _bg,
        padding: const EdgeInsets.all(6),
        height: 64,
        child: Row(children: [
          const _TempoDisplay(track: null),
          const SizedBox(width: 6),
          const _TimeBox(empty: true),
          const Spacer(),
          _SetlistsButton(),
          const SizedBox(width: 6),
          const _MoreMenu(track: null),
        ]),
      ),
      Expanded(
        child: Center(
          child: _AddSongCard(onTap: () => _addSong(context, ref, null)),
        ),
      ),
    ]);
  }
}

class _AddSongCard extends StatelessWidget {
  final VoidCallback onTap;
  const _AddSongCard({required this.onTap});
  @override
  Widget build(BuildContext context) {
    return InkWell(
      onTap: onTap,
      borderRadius: BorderRadius.circular(8),
      child: Container(
        width: 220,
        height: 140,
        decoration: BoxDecoration(
          color: _button,
          borderRadius: BorderRadius.circular(8),
          border: Border.all(color: _textFaint, width: 1.5),
        ),
        child: const Column(mainAxisAlignment: MainAxisAlignment.center, children: [
          Icon(Icons.add, color: _text, size: 44),
          SizedBox(height: 6),
          Text('ADICIONAR MÚSICA', style: TextStyle(color: _text, fontSize: 15, letterSpacing: 0.5)),
        ]),
      ),
    );
  }
}

/// Escolhe uma música da biblioteca. Na setlist em execução entra na posição [insertAt]; sem setlist, substitui a
/// música aberta (escolha própria: o WTracks não tem "setlist atual" sempre aberta como o Playback).
Future<void> _addSong(BuildContext context, WidgetRef ref, int? insertAt) async {
  final picked = await showDialog<Track>(context: context, builder: (_) => const _AddSongDialog());
  if (picked == null || !context.mounted) return;
  // A importação já deixa a música carregada (e o salvamento automático move o áudio do cache): usa a versão atual.
  final current = ref.read(currentTrackProvider);
  final alreadyLoaded = current?.id == picked.id;
  final chosen = alreadyLoaded ? current! : picked;
  final session = ref.read(setlistSessionProvider);
  if (session != null && insertAt != null) {
    if (!await ref.read(setlistSessionProvider.notifier).insertTrack(insertAt, chosen) && context.mounted) {
      ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('A música já está na setlist.')));
    }
    return;
  }
  final ok = alreadyLoaded || await ref.read(currentTrackProvider.notifier).load(chosen);
  if (ok) ref.read(setlistSessionProvider.notifier).end();
  if (!ok && context.mounted) {
    ScaffoldMessenger.of(context).showSnackBar(SnackBar(content: Text('Falha ao carregar "${chosen.title}".')));
  }
}

/// "Adicionar música" (Playback: busca + listas). Aqui: busca na biblioteca local e importação.
class _AddSongDialog extends ConsumerStatefulWidget {
  const _AddSongDialog();
  @override
  ConsumerState<_AddSongDialog> createState() => _AddSongDialogState();
}

class _AddSongDialogState extends ConsumerState<_AddSongDialog> {
  String _query = '';

  @override
  Widget build(BuildContext context) {
    final library = ref.watch(trackLibraryProvider);
    final q = _query.trim().toLowerCase();
    final songs = [
      for (final t in library)
        if (q.isEmpty || t.title.toLowerCase().contains(q) || (t.artist ?? '').toLowerCase().contains(q)) t
    ];
    return _SheetDialog(
      title: 'Adicionar música',
      children: [
        Padding(
          padding: const EdgeInsets.fromLTRB(12, 4, 12, 8),
          child: TextField(
            key: const Key('add-song-search'),
            autofocus: false,
            style: const TextStyle(color: _text),
            decoration: InputDecoration(
              isDense: true,
              hintText: 'Buscar',
              hintStyle: const TextStyle(color: _textFaint),
              prefixIcon: const Icon(Icons.search, color: _textFaint, size: 20),
              filled: true,
              fillColor: kStageSheetRow,
              border: OutlineInputBorder(borderRadius: BorderRadius.circular(10), borderSide: BorderSide.none),
            ),
            onChanged: (v) => setState(() => _query = v),
          ),
        ),
        _SheetSection(children: [
          _SheetRow(
            label: 'Importar música…',
            onTap: () async {
              final navigator = Navigator.of(context);
              final imported = await navigator.push<Track>(MaterialPageRoute(builder: (_) => const ImportScreen()));
              if (imported != null && mounted) navigator.pop(imported);
            },
          ),
          _SheetRow(
            label: 'Biblioteca MultiTracks…',
            onTap: () async {
              final navigator = Navigator.of(context);
              final picked = await navigator.push<Track>(
                  MaterialPageRoute(builder: (_) => const MultiTracksLibraryScreen(pickMode: true)));
              if (picked != null && mounted) navigator.pop(picked);
            },
          ),
        ]),
        _SheetSection(header: 'BIBLIOTECA', children: [
          if (songs.isEmpty) const _SheetRow(label: 'Nenhuma música encontrada', dim: true),
          for (final song in songs)
            _SheetRow(
              label: song.title,
              detail: [if ((song.artist ?? '').isNotEmpty) song.artist!, if ((song.key ?? '').isNotEmpty) song.key!].join(' · '),
              onTap: () => Navigator.of(context).pop(song),
            ),
        ]),
      ],
    );
  }
}

/// Painel em lista no estilo dos popovers do Playback (fundo #2C2C2E, linhas agrupadas, cabeçalhos em caixa alta).
class _SheetDialog extends StatelessWidget {
  final String title;
  final List<Widget> children;
  final Widget? trailing;
  const _SheetDialog({required this.title, required this.children, this.trailing});

  @override
  Widget build(BuildContext context) {
    return Dialog(
      backgroundColor: kStageSheet,
      insetPadding: const EdgeInsets.symmetric(horizontal: 16, vertical: 24),
      shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(14)),
      child: ConstrainedBox(
        constraints: const BoxConstraints(maxWidth: 400, maxHeight: 640),
        child: Column(mainAxisSize: MainAxisSize.min, children: [
          SizedBox(
            height: 48,
            child: Row(children: [
              TextButton(
                onPressed: () => Navigator.of(context).pop(),
                child: const Text('Fechar', style: TextStyle(color: Color(0xFF0A84FF))),
              ),
              Expanded(
                child: Text(title,
                    textAlign: TextAlign.center,
                    overflow: TextOverflow.ellipsis,
                    style: const TextStyle(color: _text, fontSize: 16, fontWeight: FontWeight.w600)),
              ),
              SizedBox(width: 72, child: trailing),
            ]),
          ),
          const Divider(height: 1, color: kStageSheetRow),
          Flexible(child: ListView(shrinkWrap: true, padding: const EdgeInsets.only(bottom: 12), children: children)),
        ]),
      ),
    );
  }
}

class _SheetSection extends StatelessWidget {
  final String? header;
  final List<Widget> children;
  const _SheetSection({this.header, required this.children});
  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.only(top: 12),
      child: Column(crossAxisAlignment: CrossAxisAlignment.start, children: [
        if (header != null)
          Padding(
            padding: const EdgeInsets.fromLTRB(16, 4, 16, 6),
            child: Text(header!, style: const TextStyle(color: _textFaint, fontSize: 12, letterSpacing: 0.3)),
          ),
        Container(
          color: kStageSheetRow.withValues(alpha: 0.45),
          child: Column(children: [
            for (var i = 0; i < children.length; i++) ...[
              if (i > 0) const Divider(height: 1, indent: 16, color: kStageSheetRow),
              children[i],
            ],
          ]),
        ),
      ]),
    );
  }
}

class _SheetRow extends StatelessWidget {
  final String label;
  final String? detail;
  final VoidCallback? onTap;
  final bool dim, destructive;
  final Widget? trailing;
  const _SheetRow({required this.label, this.detail, this.onTap, this.dim = false, this.destructive = false, this.trailing});
  @override
  Widget build(BuildContext context) {
    return InkWell(
      onTap: onTap,
      child: ConstrainedBox(
        constraints: const BoxConstraints(minHeight: 46),
        child: Padding(
          padding: const EdgeInsets.symmetric(horizontal: 16, vertical: 8),
          child: Row(children: [
            Expanded(
              child: Text(label,
                  style: TextStyle(color: destructive ? kStageRed : (dim ? _textFaint : _text), fontSize: 15)),
            ),
            if (detail != null && detail!.isNotEmpty)
              Flexible(
                child: Text(detail!,
                    textAlign: TextAlign.right,
                    overflow: TextOverflow.ellipsis,
                    style: const TextStyle(color: _textFaint, fontSize: 14)),
              ),
            ?trailing,
            if (onTap != null && trailing == null) const Icon(Icons.chevron_right, color: _textFaint, size: 20),
          ]),
        ),
      ),
    );
  }
}

/// Barra superior (Playback: compasso/BPM, tempo, PAD, voltar ao início, play, fade, EDIT, setlists, menu). No lugar
/// do PAD (fora do escopo) fica o liga/desliga do click. Abaixo de 600 px quebra em duas linhas (escolha própria).
class _TopBar extends ConsumerWidget {
  final Track track;
  final bool wide;
  const _TopBar({required this.track, required this.wide});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final info = <Widget>[
      _TempoDisplay(track: track),
      _TimeBox(narrow: !wide),
      _ClickButton(narrow: !wide),
    ];
    final actions = <Widget>[
      _EditButton(track: track),
      _SetlistsButton(),
      _MoreMenu(track: track),
    ];
    const transport = _TransportButtons();
    return Container(
      color: _bg,
      padding: const EdgeInsets.fromLTRB(6, 6, 6, 4),
      child: wide
          ? SizedBox(
              height: 56,
              child: Row(children: [
                ..._spaced(info),
                const SizedBox(width: 6),
                const Expanded(child: transport),
                const SizedBox(width: 6),
                ..._spaced(actions),
              ]),
            )
          : Column(children: [
              SizedBox(height: 48, child: Row(children: [..._spaced(info), const Spacer(), const SizedBox(width: 6), ..._spaced(actions)])),
              const SizedBox(height: 6),
              const SizedBox(height: 48, child: transport),
            ]),
    );
  }

  static List<Widget> _spaced(List<Widget> items) => [
        for (var i = 0; i < items.length; i++) ...[if (i > 0) const SizedBox(width: 6), items[i]],
      ];
}

/// Botão escuro da barra (Playback: fundo #131516, mais escuro que a tela, cantos de 6 px).
class _BarButton extends StatelessWidget {
  final Widget child;
  final VoidCallback? onTap;
  final VoidCallback? onLongPress;
  final String? tooltip;
  final double? width;
  final bool highlighted;
  const _BarButton({required this.child, this.onTap, this.onLongPress, this.tooltip, this.width, this.highlighted = false});

  @override
  Widget build(BuildContext context) {
    Widget button = Material(
      color: highlighted ? const Color(0xFF26292B) : _button,
      shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(6), side: const BorderSide(color: Color(0xFF0E0F10))),
      child: InkWell(
        onTap: onTap,
        onLongPress: onLongPress,
        borderRadius: BorderRadius.circular(6),
        child: SizedBox(width: width, height: double.infinity, child: Center(child: child)),
      ),
    );
    if (tooltip != null) button = Tooltip(message: tooltip!, child: button);
    return button;
  }
}

/// Liga/desliga o click (no lugar do PAD do Playback, que está fora do escopo).
class _ClickButton extends ConsumerWidget {
  final bool narrow;
  const _ClickButton({this.narrow = false});
  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final enabled = ref.watch(clickEnabledProvider);
    return _BarButton(
      tooltip: enabled ? 'Desligar click' : 'Ligar click',
      width: narrow ? 48 : 52,
      onTap: () => _setClick(ref, !enabled),
      child: FittedBox(
          fit: BoxFit.scaleDown,
          child: Text('CLICK', style: TextStyle(color: enabled ? kStageGreen : _textFaint, fontSize: 13))),
    );
  }
}

void _setClick(WidgetRef ref, bool enabled) {
  ref.read(clickEnabledProvider.notifier).state = enabled;
  ref.read(engineProvider).setClickEnabled(enabled);
}

/// Voltar ao início, play/pausa e fade (Playback: TransportRTZButton, PlayPause, Fade; ícones de contorno).
class _TransportButtons extends ConsumerWidget {
  const _TransportButtons();
  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final isPlaying = ref.watch(transportProvider.select((t) => t.isPlaying));
    final prerolling = ref.watch(transportProvider.select((t) => t.prerolling));
    final faded = ref.watch(transportProvider.select((t) => t.faded));
    final notifier = ref.read(transportProvider.notifier);
    final playColor = prerolling ? kStageYellow : kStageGreen;
    return Row(children: [
      Expanded(
        child: _BarButton(
          tooltip: 'Voltar ao início',
          onTap: notifier.returnToZero,
          child: CustomPaint(size: const Size(30, 26), painter: _RtzIconPainter(_textDim)),
        ),
      ),
      const SizedBox(width: 6),
      Expanded(
        flex: 2,
        child: _BarButton(
          tooltip: prerolling ? 'Contagem' : (isPlaying ? 'Pausar' : 'Tocar'),
          onTap: isPlaying ? notifier.pause : notifier.play,
          child: prerolling
              ? const Icon(Icons.av_timer, color: kStageYellow, size: 30)
              : CustomPaint(size: const Size(26, 28), painter: _PlayIconPainter(playColor, paused: !isPlaying)),
        ),
      ),
      const SizedBox(width: 6),
      Expanded(
        child: _BarButton(
          tooltip: 'Fade de 5 segundos',
          highlighted: faded,
          onTap: () => notifier.fadeToggle(),
          child: CustomPaint(size: const Size(40, 24), painter: _FadeIconPainter(faded ? kStageOrange : const Color(0xFF919191))),
        ),
      ),
    ]);
  }
}

/// |◁ de contorno.
class _RtzIconPainter extends CustomPainter {
  final Color color;
  const _RtzIconPainter(this.color);
  @override
  void paint(Canvas canvas, Size size) {
    final paint = Paint()
      ..color = color
      ..style = PaintingStyle.stroke
      ..strokeWidth = 1.8
      ..strokeJoin = StrokeJoin.round;
    canvas.drawRRect(RRect.fromLTRBR(2, 1, 8, size.height - 1, const Radius.circular(1.5)), paint);
    canvas.drawPath(
        Path()
          ..moveTo(size.width - 2, 1)
          ..lineTo(11, size.height / 2)
          ..lineTo(size.width - 2, size.height - 1)
          ..close(),
        paint);
  }

  @override
  bool shouldRepaint(covariant _RtzIconPainter old) => old.color != color;
}

/// ▷ de contorno (ou ‖ quando tocando).
class _PlayIconPainter extends CustomPainter {
  final Color color;
  final bool paused;
  const _PlayIconPainter(this.color, {required this.paused});
  @override
  void paint(Canvas canvas, Size size) {
    final paint = Paint()
      ..color = color
      ..style = PaintingStyle.stroke
      ..strokeWidth = 2
      ..strokeJoin = StrokeJoin.round;
    if (paused) {
      canvas.drawPath(
          Path()
            ..moveTo(3, 1)
            ..lineTo(size.width - 2, size.height / 2)
            ..lineTo(3, size.height - 1)
            ..close(),
          paint);
    } else {
      canvas.drawRRect(RRect.fromLTRBR(4, 1, 10, size.height - 1, const Radius.circular(1.5)), paint);
      canvas.drawRRect(RRect.fromLTRBR(size.width - 10, 1, size.width - 4, size.height - 1, const Radius.circular(1.5)), paint);
    }
  }

  @override
  bool shouldRepaint(covariant _PlayIconPainter old) => old.color != color || old.paused != paused;
}

/// Rampa descendente do fade (Playback: TransportFadeButton).
class _FadeIconPainter extends CustomPainter {
  final Color color;
  const _FadeIconPainter(this.color);
  @override
  void paint(Canvas canvas, Size size) {
    final path = Path()
      ..moveTo(2, 1)
      ..quadraticBezierTo(size.width * 0.3, size.height * 0.9, size.width - 1, size.height - 1)
      ..lineTo(2, size.height - 1)
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

/// EDIT: toque entra/sai do modo de edição da setlist; segurar abre os outros modos (Playback: Setlist, MIDI Cues,
/// MIDI Mapping, Song Sections). Aqui os modos de gatilhos, mapeamento e seções abrem as telas próprias.
class _EditButton extends ConsumerWidget {
  final Track track;
  const _EditButton({required this.track});
  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final editing = ref.watch(performanceEditProvider);
    void push(Widget screen) => Navigator.of(context).push(MaterialPageRoute<void>(builder: (_) => screen));
    return _BarButton(
      tooltip: editing ? 'Concluir edição' : 'Editar (segure para outros modos)',
      width: 54,
      highlighted: editing,
      onTap: () => ref.read(performanceEditProvider.notifier).state = !editing,
      onLongPress: () async {
        final box = context.findRenderObject() as RenderBox;
        final origin = box.localToGlobal(Offset(0, box.size.height));
        final choice = await showMenu<String>(
          context: context,
          color: kStageSheet,
          position: RelativeRect.fromLTRB(origin.dx, origin.dy, origin.dx + box.size.width, 0),
          items: const [
            PopupMenuItem(value: 'setlist', child: Text('Setlist')),
            PopupMenuItem(value: 'cues', child: Text('Gatilhos MIDI')),
            PopupMenuItem(value: 'mapping', child: Text('Mapeamento MIDI')),
            PopupMenuItem(value: 'sections', child: Text('Seções da música')),
          ],
        );
        switch (choice) {
          case 'setlist':
            ref.read(performanceEditProvider.notifier).state = true;
          case 'cues':
            push(MidiScreen(trackId: track.id));
          case 'mapping':
            push(const ControlMappingScreen());
          case 'sections':
            push(SectionEditorScreen(trackId: track.id));
        }
      },
      child: FittedBox(
          fit: BoxFit.scaleDown,
          child: Text(editing ? 'OK' : 'EDITAR', style: TextStyle(color: editing ? _text : _textFaint, fontSize: 13))),
    );
  }
}

/// Setlists (Playback: popover "Setlists" com nova, abrir, a atual e salvar como nova).
class _SetlistsButton extends ConsumerWidget {
  @override
  Widget build(BuildContext context, WidgetRef ref) {
    return _BarButton(
      tooltip: 'Setlists',
      width: 44,
      onTap: () => showDialog<void>(context: context, builder: (_) => const _SetlistsDialog()),
      child: const Icon(Icons.queue_music, color: _textFaint, size: 24),
    );
  }
}

class _SetlistsDialog extends ConsumerWidget {
  const _SetlistsDialog();
  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final session = ref.watch(setlistSessionProvider);
    void open(Widget screen) {
      Navigator.of(context).pop();
      Navigator.of(context).push(MaterialPageRoute<void>(builder: (_) => screen));
    }

    return _SheetDialog(title: 'Setlists', children: [
      _SheetSection(children: [
        _SheetRow(label: 'Abrir ou criar setlist', onTap: () => open(const SetlistsScreen())),
        _SheetRow(label: 'Biblioteca de músicas', onTap: () => open(const LibraryScreen())),
      ]),
      _SheetSection(header: 'SETLIST ATUAL', children: [
        if (session == null)
          const _SheetRow(label: 'Nenhuma setlist aberta', dim: true)
        else ...[
          _SheetRow(
            label: session.setlist.name,
            detail: '${session.setlist.tracks.length} músicas · ${session.index + 1}/${session.setlist.tracks.length}',
          ),
          _SheetRow(
            label: 'Fechar setlist',
            destructive: true,
            onTap: () {
              ref.read(setlistSessionProvider.notifier).end();
              Navigator.of(context).pop();
            },
          ),
        ],
      ]),
    ]);
  }
}

/// Menu ≡ (Playback: menu com os ajustes). Também leva à edição da música aberta.
class _MoreMenu extends ConsumerWidget {
  final Track? track;
  const _MoreMenu({required this.track});
  @override
  Widget build(BuildContext context, WidgetRef ref) {
    void push(Widget screen) => Navigator.of(context).push(MaterialPageRoute<void>(builder: (_) => screen));
    return Material(
      color: _button,
      shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(6), side: const BorderSide(color: Color(0xFF0E0F10))),
      child: SizedBox(
        width: 44,
        child: PopupMenuButton<String>(
          tooltip: 'Mais',
          color: kStageSheet,
          icon: const Icon(Icons.menu, color: _textFaint),
          onSelected: (choice) {
            switch (choice) {
              case 'song':
                if (track != null) _showSongMenu(context, ref, track!);
              case 'settings':
                push(const SettingsScreen());
              case 'library':
                push(const LibraryScreen());
              case 'mapping':
                push(const ControlMappingScreen());
              case 'remote':
                push(const RemoteScreen());
            }
          },
          itemBuilder: (_) => [
            if (track != null) const PopupMenuItem(value: 'song', child: Text('Editar música…')),
            const PopupMenuItem(value: 'settings', child: Text('Ajustes')),
            const PopupMenuItem(value: 'library', child: Text('Biblioteca')),
            const PopupMenuItem(value: 'mapping', child: Text('Mapeamento MIDI e teclado')),
            const PopupMenuItem(value: 'remote', child: Text('Controle remoto')),
          ],
        ),
      ),
    );
  }
}

/// Menu "Editar música" (Playback: popover do "…" no cartão, com arranjo, conteúdo, tom e andamento, duração, pad e
/// MIDI out). Aqui cada grupo abre a tela/painel que o WTracks já tem.
Future<void> _showSongMenu(BuildContext context, WidgetRef ref, Track track) {
  return showDialog<void>(context: context, builder: (_) => _SongMenuDialog(track: track));
}

class _SongMenuDialog extends ConsumerWidget {
  final Track track;
  const _SongMenuDialog({required this.track});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final current = ref.watch(currentTrackProvider);
    final song = current?.id == track.id ? current! : track;
    final navigator = Navigator.of(context);
    void push(Widget screen) {
      navigator.pop();
      navigator.push(MaterialPageRoute<void>(builder: (_) => screen));
    }

    void sheet(Widget child) {
      navigator.pop();
      showModalBottomSheet<void>(context: navigator.context, isScrollControlled: true, builder: (_) => child);
    }

    final click = song.clickSettings;
    // O menu fecha antes das ações terminarem: elas usam o container do app, não o `ref` deste diálogo.
    final reader = ProviderReader.of(context);
    return _SheetDialog(
      title: song.title,
      trailing: TextButton(
        onPressed: () {
          navigator.pop();
          _save(navigator.context, reader.read);
        },
        child: const Text('Salvar', style: TextStyle(color: Color(0xFF0A84FF), fontWeight: FontWeight.w600)),
      ),
      children: [
        _SheetSection(header: 'MÚSICA', children: [
          _SheetRow(label: 'Nome', detail: song.title, onTap: () {
            navigator.pop();
            _renameTrack(navigator.context, reader.read, song);
          }),
        ]),
        _SheetSection(header: 'TOM E ANDAMENTO', children: [
          _SheetRow(label: 'Tom e andamento', detail: song.key ?? '', onTap: () => sheet(TimePitchSheet(trackId: song.id))),
          _SheetRow(label: 'Metrônomo', detail: '${click.bpm.round()} BPM · ${click.timeSignatureNumerator}/${click.timeSignatureDenominator}', onTap: () {
            navigator.pop();
            showMetronomeSheet(navigator.context, reader, song, reader.read(transportProvider).isPlaying);
          }),
          _SheetRow(label: 'Mapa de andamento', onTap: () => push(TempoMapScreen(trackId: song.id))),
        ]),
        _SheetSection(header: 'DURAÇÃO', children: [
          _SheetRow(label: 'Início e fim da música', detail: song.startSeconds == null && song.endSeconds == null ? '' : 'personalizado', onTap: () => sheet(const SongRangeSheet())),
          _SheetRow(label: 'Fim da música e fade', detail: song.endFade ? 'Fade de 5 s' : '', onTap: () => sheet(const SongEndingSheet())),
        ]),
        _SheetSection(header: 'MAPA DA MÚSICA', children: [
          _SheetRow(label: 'Seções', detail: '${song.sections.length}', onTap: () => push(SectionEditorScreen(trackId: song.id))),
          _SheetRow(label: 'Guias', onTap: () => push(GuideEditorScreen(trackId: song.id))),
        ]),
        _SheetSection(header: 'MIXER', children: [
          _SheetRow(label: 'Automação do mixer', detail: '${song.mixerAutomation.length}', onTap: () => push(MixerAutomationScreen(trackId: song.id))),
          _SheetRow(label: 'Buses e roteamento', detail: '${song.buses.length}', onTap: () => push(BusesScreen(trackId: song.id))),
        ]),
        _SheetSection(header: 'MIDI OUT', children: [
          _SheetRow(label: 'MIDI, automações e timecode', onTap: () => push(MidiScreen(trackId: song.id))),
        ]),
      ],
    );
  }
}

/// Lê providers sem depender do widget que abriu a ação (o menu pode fechar antes de ela terminar).
typedef ProviderRead = T Function<T>(ProviderListenable<T> provider);

/// Leitor de providers que sobrevive ao widget que abriu a ação (usa o container do app).
class ProviderReader {
  final ProviderRead read;
  const ProviderReader(this.read);
  factory ProviderReader.of(BuildContext context) => ProviderReader(ProviderScope.containerOf(context, listen: false).read);
}

Future<void> _renameTrack(BuildContext context, ProviderRead read, Track track) async {
  final newTitle = await showDialog<String>(
    context: context,
    builder: (ctx) => DialogTextController(
      initialText: track.title,
      builder: (controller) => AlertDialog(
        backgroundColor: kStageSheet,
        title: const Text('Renomear música', style: TextStyle(color: _text)),
        content: TextField(
          controller: controller,
          autofocus: true,
          style: const TextStyle(color: _text),
          onSubmitted: (value) => Navigator.of(ctx).pop(value),
        ),
        actions: [
          TextButton(onPressed: () => Navigator.of(ctx).pop(), child: const Text('Cancelar')),
          FilledButton(onPressed: () => Navigator.of(ctx).pop(controller.text), child: const Text('Salvar')),
        ],
      ),
    ),
  );
  if (!context.mounted) return;
  final trimmed = newTitle?.trim();
  if (trimmed == null || trimmed.isEmpty || trimmed == track.title) return;
  read(currentTrackProvider.notifier).renameCurrent(trimmed); // o salvamento automático grava
}

Future<void> _save(BuildContext context, ProviderRead read) async {
  final messenger = ScaffoldMessenger.of(context);
  try {
    await read(trackLibraryProvider.notifier).saveCurrent();
    messenger.showSnackBar(const SnackBar(content: Text('Música salva.')));
  } catch (e) {
    read(diagnosticsProvider.notifier).error('Falha ao salvar: $e');
    messenger.showSnackBar(SnackBar(content: Text('Falha ao salvar: $e')));
  }
}

/// Tempo atual grande e "decorrido / duração" embaixo (Playback: "00:00" sobre "0:00 / 4:43"). Toque edita o início e o fim.
class _TimeBox extends ConsumerWidget {
  final bool empty, narrow;
  const _TimeBox({this.empty = false, this.narrow = false});
  @override
  Widget build(BuildContext context, WidgetRef ref) {
    // Sem música não observa o transporte (o polling de 100 ms só começa quando há o que tocar).
    final position = empty ? 0.0 : ref.watch(transportProvider.select((t) => t.positionSeconds));
    final length = empty ? 0.0 : ref.watch(transportProvider.select((t) => t.lengthSeconds));
    const figures = [FontFeature.tabularFigures()];
    final track = ref.read(currentTrackProvider);
    return _BarButton(
      tooltip: 'Início e fim da música',
      width: narrow ? 80 : 92,
      onTap: empty || track == null ? null : () => showModalBottomSheet<void>(context: context, builder: (_) => const SongRangeSheet()),
      child: FittedBox(fit: BoxFit.scaleDown, child: Column(mainAxisAlignment: MainAxisAlignment.center, children: [
        Text(empty ? '--:--' : _clock(position),
            style: const TextStyle(color: _text, fontSize: 22, fontWeight: FontWeight.w300, fontFeatures: figures)),
        Text(empty ? '-- / --' : '${_formatTime(position)} / ${_formatTime(length)}',
            maxLines: 1, style: const TextStyle(color: _textDim, fontSize: 11, fontFeatures: figures)),
      ])),
    );
  }
}

/// BPM sobre o compasso, sem moldura (Playback: TransportTempoTimeSignatureButton). Acompanha o mapa de andamento
/// durante a música. Toque abre o metrônomo.
class _TempoDisplay extends ConsumerWidget {
  final Track? track;
  const _TempoDisplay({required this.track});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final t = track;
    final position = t == null || t.tempoChanges.isEmpty ? 0.0 : ref.watch(transportProvider.select((s) => s.positionSeconds));
    final segment = t == null ? null : TempoSegment.at(position, t.clickSettings, t.tempoChanges);
    return InkWell(
      onTap: t == null ? null : () => showMetronomeSheet(context, ProviderReader(ref.read), t, ref.read(transportProvider).isPlaying),
      child: SizedBox(
        width: 46,
        child: FittedBox(fit: BoxFit.scaleDown, child: Column(mainAxisAlignment: MainAxisAlignment.center, children: [
          Text(segment == null ? '' : segment.bpm.round().toString(), style: const TextStyle(color: _text, fontSize: 16)),
          Container(height: 1, width: 34, color: _textFaint, margin: const EdgeInsets.symmetric(vertical: 3)),
          Text(segment == null ? '' : '${segment.numerator}/${segment.denominator}',
              style: const TextStyle(color: _text, fontSize: 16)),
          if (t != null) const Text('BPM', style: TextStyle(color: _textFaint, fontSize: 7, height: 1)),
        ])),
      ),
    );
  }
}

/// Metrônomo: BPM, tap tempo, compasso, timbre, ganhos das subdivisões e offset do 1º tempo.
void showMetronomeSheet(BuildContext context, ProviderReader ref, Track track, bool isPlaying) {
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


/// Aviso de que a passagem para a próxima música não saiu como planejado (pré-carga falhou, entrou com corte, não carregou). Fase C:
/// o fallback precisa ser visível no palco, não só no Diagnóstico. Escolha própria; o Playback não tem equivalente.
class _TransitionNoticeBar extends ConsumerWidget {
  const _TransitionNoticeBar();

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final notice = ref.watch(transitionProvider.select((s) => s.notice));
    if (notice == null) return const SizedBox.shrink();
    final color = notice.kind == TransitionNoticeKind.nextFailed ? kStageRed : const Color(0xFFFFB020);
    return Container(
      key: const Key('transition-notice'),
      margin: const EdgeInsets.fromLTRB(10, 4, 10, 0),
      padding: const EdgeInsets.only(left: 10),
      decoration: BoxDecoration(
        color: color.withValues(alpha: 0.14),
        borderRadius: BorderRadius.circular(6),
        border: Border.all(color: color.withValues(alpha: 0.6)),
      ),
      child: Row(children: [
        Icon(notice.kind == TransitionNoticeKind.nextFailed ? Icons.error_outline : Icons.warning_amber_rounded, color: color, size: 18),
        const SizedBox(width: 8),
        Expanded(child: Text(notice.message, style: const TextStyle(color: _text, fontSize: 13))),
        IconButton(
          tooltip: 'Fechar aviso',
          icon: const Icon(Icons.close, color: _textDim, size: 18),
          onPressed: () => ref.read(transitionProvider.notifier).dismissNotice(),
        ),
      ]),
    );
  }
}

/// Faixa da setlist (Playback: cartões com capa, "Título (Tom)", selo da transição no canto e ▷ verde na atual). Parado,
/// um toque seleciona a música; tocando, é preciso tocar duas vezes (no Playback isso faz um crossfade; aqui troca de
/// música -- escolha própria até existir crossfade no motor). No modo de edição: (−) remove, (…) edita, (+) adiciona.
class _SetlistRow extends ConsumerWidget {
  final Track track;
  final bool compact;
  const _SetlistRow({required this.track, required this.compact});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final session = ref.watch(setlistSessionProvider);
    final editing = ref.watch(performanceEditProvider);
    final playing = ref.watch(transportProvider.select((t) => t.isPlaying));
    final inSession = session != null && session.current.id == track.id;
    final songs = inSession ? session.setlist.tracks : [track];
    final current = inSession ? session.index : 0;
    final notifier = ref.read(setlistSessionProvider.notifier);
    final cardWidth = compact ? 120.0 : 178.0;
    final artHeight = compact ? 44.0 : 82.0;
    return Container(
      color: _bg,
      height: artHeight + (compact ? 34 : 38),
      child: ListView.builder(
        scrollDirection: Axis.horizontal,
        padding: const EdgeInsets.fromLTRB(10, 6, 10, 0),
        itemCount: songs.length,
        itemBuilder: (context, i) {
          final song = i == current ? track : songs[i];
          final last = i == songs.length - 1;
          return Padding(
            padding: const EdgeInsets.only(right: 12),
            child: _SongCard(
              song: song,
              width: cardWidth,
              artHeight: artHeight,
              current: i == current,
              editing: editing,
              badge: inSession && (!last || song.transition == SongTransition.cueFirstSong) ? song.transition : null,
              onTransition: i == current ? () => _chooseTransition(context, ref) : null,
              onSelect: i == current ? null : (playing ? null : () => notifier.go(i)),
              onDoubleTap: i == current || !playing ? null : () => ref.read(transitionProvider.notifier).liveCrossfade(i),
              onRemove: inSession && i != current ? () => notifier.removeAt(i) : null,
              onMenu: i == current ? () => _showSongMenu(context, ref, track) : null,
              onAdd: () => _addSong(context, ref, inSession ? i + 1 : null),
            ),
          );
        },
      ),
    );
  }

  /// Transições (Playback: Cue Next Song, AutoLink, Overlap, Crossfade, Stay In Song, Cue First Song). O Continue Pad fica
  /// para a Fase 8 (Pad Player).
  Future<void> _chooseTransition(BuildContext context, WidgetRef ref) async {
    final current = ref.read(currentTrackProvider);
    if (current == null) return;
    final choice = await showDialog<SongTransition>(
      context: context,
      builder: (ctx) => _SheetDialog(title: 'Transição', children: [
        _SheetSection(children: [
          for (final value in SongTransition.values)
            _SheetRow(
              label: value.label,
              onTap: () => Navigator.of(ctx).pop(value),
              trailing: Icon(current.transition == value ? Icons.check : null, color: const Color(0xFF0A84FF), size: 20),
            ),
        ]),
      ]),
    );
    if (choice == null) return;
    ref.read(currentTrackProvider.notifier).setTransition(choice); // o salvamento automático grava
  }
}

class _SongCard extends StatelessWidget {
  final Track song;
  final double width, artHeight;
  final bool current, editing;
  final SongTransition? badge;
  final VoidCallback? onSelect, onDoubleTap, onRemove, onMenu, onAdd, onTransition;
  const _SongCard({
    required this.song,
    required this.width,
    required this.artHeight,
    required this.current,
    required this.editing,
    required this.badge,
    this.onSelect,
    this.onDoubleTap,
    this.onRemove,
    this.onMenu,
    this.onAdd,
    this.onTransition,
  });

  @override
  Widget build(BuildContext context) {
    // Sem capa no nosso modelo: um bloco colorido derivado do título (escolha própria).
    final hue = (song.title.hashCode % 360).abs().toDouble();
    final top = HSLColor.fromAHSL(1, hue, 0.30, 0.34).toColor();
    final bottom = HSLColor.fromAHSL(1, (hue + 40) % 360, 0.30, 0.16).toColor();
    final key = song.key;
    return SizedBox(
      width: width,
      child: Column(crossAxisAlignment: CrossAxisAlignment.start, children: [
        SizedBox(
          height: artHeight,
          child: Stack(clipBehavior: Clip.none, children: [
            Positioned.fill(
              child: GestureDetector(
                onTap: onSelect,
                onDoubleTap: onDoubleTap,
                child: Container(
                  decoration: BoxDecoration(
                    borderRadius: BorderRadius.circular(6),
                    border: Border.all(color: current ? _text : Colors.transparent, width: 1.5),
                    gradient: LinearGradient(colors: [top, bottom], begin: Alignment.topLeft, end: Alignment.bottomRight),
                  ),
                  alignment: Alignment.center,
                  child: Text(song.title.isEmpty ? '' : song.title.substring(0, 1).toUpperCase(),
                      style: TextStyle(color: Colors.white.withValues(alpha: 0.22), fontSize: artHeight * 0.5, fontWeight: FontWeight.w700)),
                ),
              ),
            ),
            if (badge != null)
              Positioned(
                right: -12,
                top: -4,
                child: Tooltip(
                  message: 'Transição',
                  child: GestureDetector(
                    onTap: onTransition,
                    child: Container(
                      width: 26,
                      height: 26,
                      decoration: BoxDecoration(
                        color: const Color(0xFF2B2D2E),
                        shape: BoxShape.circle,
                        border: Border.all(color: current ? kStageGreen : const Color(0xFF2B2D2E), width: 1.5),
                      ),
                      child: Icon(badge!.icon, size: 16, color: _text),
                    ),
                  ),
                ),
              ),
            if (editing && onRemove != null)
              Positioned(left: 10, top: artHeight / 2 - 13, child: _CircleAction(icon: Icons.remove, color: kStageRed, tooltip: 'Remover da setlist', onTap: onRemove!)),
            if (editing && onMenu != null)
              Positioned(left: width / 2 - 13, top: artHeight / 2 - 13, child: _CircleAction(icon: Icons.more_horiz, color: const Color(0xFF2B2D2E), tooltip: 'Editar música', onTap: onMenu!)),
            if (editing && onAdd != null)
              Positioned(right: -13, bottom: -6, child: _CircleAction(icon: Icons.add, color: const Color(0xFF2B2D2E), tooltip: 'Adicionar música', onTap: onAdd!)),
          ]),
        ),
        const SizedBox(height: 6),
        Row(children: [
          if (current) const Icon(Icons.play_arrow_outlined, size: 18, color: kStageGreen),
          Expanded(
            child: Text(
              key == null || key.isEmpty ? song.title : '${song.title} ($key)',
              maxLines: 1,
              overflow: TextOverflow.ellipsis,
              style: TextStyle(color: _text, fontSize: 14, fontWeight: current ? FontWeight.w600 : FontWeight.w400),
            ),
          ),
        ]),
      ]),
    );
  }
}

class _CircleAction extends StatelessWidget {
  final IconData icon;
  final Color color;
  final String tooltip;
  final VoidCallback onTap;
  const _CircleAction({required this.icon, required this.color, required this.tooltip, required this.onTap});
  @override
  Widget build(BuildContext context) {
    return Tooltip(
      message: tooltip,
      child: GestureDetector(
        onTap: onTap,
        child: Container(
          width: 26,
          height: 26,
          decoration: BoxDecoration(color: color, shape: BoxShape.circle),
          child: Icon(icon, size: 18, color: Colors.white),
        ),
      ),
    );
  }
}

/// Sigla da seção (Playback: selos "Co", "I", "V1", "R1"...).
String _sectionBadge(String name) {
  final trimmed = name.trim();
  if (trimmed.isEmpty) return '?';
  final digits = RegExp(r'\d+').firstMatch(trimmed)?.group(0) ?? '';
  final badge = '${trimmed.substring(0, 1).toUpperCase()}$digits';
  return badge.length > 3 ? badge.substring(0, 3) : badge;
}

/// Cor da seção pelo nome. O Playback colore pelo tipo de seção (Intro #5DA4B5, Verso #92278F, Refrão laranja,
/// contagem cinza, medidos nas capturas); o nosso modelo não tem tipo, então a inicial decide (escolha própria).
Color _sectionColor(String name) {
  final n = name.trim().toLowerCase();
  if (n.startsWith('v')) return kStagePurple; // verso, verse
  if (n.startsWith('r') || n.startsWith('c')) return kStageOrange; // refrão, coro, chorus
  if (n.startsWith('p') || n.startsWith('b')) return kStageBlue; // ponte, pré-refrão, bridge
  if (n.startsWith('i')) return kStageTeal; // intro
  if (n.startsWith('o') || n.startsWith('f') || n.startsWith('e')) return kStageGreen; // outro, final, ending
  return kStageGrey;
}

/// Início de cada compasso até [length] (grade da waveform), seguindo o mapa de andamento.
List<double> _barTimes(Track track, double length) {
  final bars = <double>[];
  var t = track.clickSettings.beatOffsetSeconds;
  while (t < length && bars.length < 4000) {
    bars.add(t);
    final segment = TempoSegment.at(t + 1e-6, track.clickSettings, track.tempoChanges);
    final barLength = segment.beatSeconds(track.clickSettings.bpmUnit) * segment.numerator;
    if (!(barLength > 0.05)) break;
    var next = t + barLength;
    // Uma mudança de andamento no meio do compasso reinicia a grade nela.
    for (final change in track.tempoChanges) {
      if (change.startSeconds > t + 1e-6 && change.startSeconds < next) {
        next = change.startSeconds;
        break;
      }
    }
    t = next;
  }
  return bars;
}

/// Waveform rolante (Playback: a música passa sob uma agulha fixa à esquerda; seções em caixas coloridas com selo e
/// botão de laço; grade de compassos). Arrastar rola a vista (volta a seguir a agulha 5 s depois); tocar busca o
/// ponto. Laço da seção: um toque arma uma repetição dela (desliga se já ativo); no modo de edição liga/desliga o laço
/// infinito predefinido. Toque duplo no selo pula para a seção (o "Live ReOrder" do Playback espera o fim da seção
/// atual; aqui o salto é imediato -- escolha própria).
class _WaveformView extends ConsumerStatefulWidget {
  final Track track;
  final double height;
  const _WaveformView({required this.track, required this.height});
  @override
  ConsumerState<_WaveformView> createState() => _WaveformViewState();
}

class _WaveformViewState extends ConsumerState<_WaveformView> {
  double? _manualStart; // início da vista em segundos enquanto o usuário rola
  DateTime _lastScroll = DateTime.fromMillisecondsSinceEpoch(0);
  List<double> _bars = const [];
  Object? _barsKey;

  @override
  void initState() {
    super.initState();
    WidgetsBinding.instance.addPostFrameCallback((_) => _load());
  }

  @override
  void didUpdateWidget(covariant _WaveformView oldWidget) {
    super.didUpdateWidget(oldWidget);
    if (oldWidget.track.id != widget.track.id) {
      _manualStart = null;
      WidgetsBinding.instance.addPostFrameCallback((_) => _load());
    }
  }

  void _load() {
    if (!mounted) return;
    ref.read(waveformProvider.notifier).loadFor(widget.track);
  }

  void _seek(double seconds) {
    _manualStart = null;
    ref.read(transportProvider.notifier).seekTo(seconds);
  }

  Future<void> _loop(SongSection section) async {
    final transport = ref.read(transportProvider);
    if (transport.activeSection(section)) {
      ref.read(transportProvider.notifier).disableLoop();
      return;
    }
    // Uma repetição: duas passagens pela seção (o motor conta passagens).
    final ok = await ref.read(currentTrackProvider.notifier).setSectionLoop(section.copyWith(loopCount: 2));
    if (!ok && mounted) {
      ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Não foi possível preparar o loop desta seção.')));
    }
  }

  Future<void> _updateSections(List<SongSection> sections) async {
    final notifier = ref.read(currentTrackProvider.notifier);
    notifier.updateSections(widget.track.id, sections); // o salvamento automático grava
  }

  Future<void> _deleteSection(SongSection section) async {
    final confirmed = await showDialog<bool>(
      context: context,
      builder: (ctx) => AlertDialog(
        backgroundColor: kStageSheet,
        title: Text('Excluir "${section.name}"?'),
        actions: [
          TextButton(onPressed: () => Navigator.pop(ctx, false), child: const Text('Cancelar')),
          TextButton(onPressed: () => Navigator.pop(ctx, true), child: const Text('Excluir')),
        ],
      ),
    );
    if (confirmed == true) await _updateSections(widget.track.sections.where((s) => s.id != section.id).toList());
  }

  @override
  Widget build(BuildContext context) {
    final waveform = ref.watch(waveformProvider);
    final transport = ref.watch(transportProvider);
    final editing = ref.watch(performanceEditProvider);
    final grid = ref.watch(appSettingsProvider.select((s) => s.waveformGrid));
    final track = widget.track;
    final length = transport.lengthSeconds;
    final key = (track.id, track.clickSettings, track.tempoChanges, length);
    if (_barsKey != key) {
      _barsKey = key;
      _bars = length > 0 ? _barTimes(track, length) : const [];
    }
    if (_manualStart != null && DateTime.now().difference(_lastScroll) > const Duration(seconds: 5)) _manualStart = null;

    return Container(
      height: widget.height,
      color: _panelBg,
      child: LayoutBuilder(builder: (context, constraints) {
        final width = constraints.maxWidth;
        final pps = (width / 45).clamp(6.0, 40.0); // pixels por segundo: ~45 s visíveis
        final playheadX = math.max(40.0, width * 0.07);
        final viewStart = _manualStart ?? (transport.positionSeconds - playheadX / pps);
        double x(double t) => (t - viewStart) * pps;
        final visible = [
          for (final s in track.sections)
            if (x(s.endSeconds) > 0 && x(s.startSeconds) < width) s
        ];
        return Stack(clipBehavior: Clip.hardEdge, children: [
          Positioned.fill(
            child: GestureDetector(
              behavior: HitTestBehavior.opaque,
              onTapDown: (d) {
                if (length > 0) _seek((viewStart + d.localPosition.dx / pps).clamp(0.0, length));
              },
              onHorizontalDragUpdate: (d) => setState(() {
                _lastScroll = DateTime.now();
                final start = (_manualStart ?? viewStart) - d.delta.dx / pps;
                _manualStart = start.clamp(-playheadX / pps, math.max(0.0, length - playheadX / pps));
              }),
              child: CustomPaint(
                painter: _WaveformPainter(
                  peaks: waveform.peaks,
                  lengthSeconds: length,
                  viewStart: viewStart,
                  pixelsPerSecond: pps,
                  playheadX: x(transport.positionSeconds),
                  sections: track.sections,
                  activeLoop: [for (final s in track.sections) transport.activeSection(s)],
                  bars: grid ? _bars : const [],
                  cues: [for (final c in track.automationCues) c.timeSeconds],
                  generating: waveform.isGenerating,
                ),
              ),
            ),
          ),
          for (final s in visible) ..._sectionControls(s, x(s.startSeconds), x(s.endSeconds), width, transport, editing),
          if (transport.loopPass > 0)
            Positioned(
              right: 8,
              bottom: 6,
              child: IgnorePointer(
                child: Container(
                  key: const Key('loop-pass'),
                  padding: const EdgeInsets.symmetric(horizontal: 6, vertical: 1),
                  decoration: BoxDecoration(
                    color: _bg.withValues(alpha: 0.85),
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

  List<Widget> _sectionControls(SongSection section, double left, double right, double width, TransportState transport, bool editing) {
    final color = _sectionColor(section.name);
    final active = transport.activeSection(section);
    final queued = transport.queuedSection(section);
    final loopColor = active ? kStageGreen : (queued ? kStageYellow : (section.presetInfiniteLoop ? kStageOrange : const Color(0xFF686F71)));
    // Selo e laço ficam presos às bordas da vista enquanto a seção aparece (a caixa pode passar da tela).
    final badgeLeft = math.max(left + 8, 6.0);
    final loopLeft = math.min(right - 44, width - 44);
    final visibleWidth = math.min(right, width) - math.max(left, 0);
    return [
      Positioned(
        left: badgeLeft,
        top: 8,
        child: Tooltip(
          message: section.name,
          child: GestureDetector(
            onDoubleTap: () => _seek(section.playStart),
            child: Container(
              width: 26,
              height: 26,
              alignment: Alignment.center,
              decoration: BoxDecoration(
                color: _panelBg.withValues(alpha: 0.6),
                shape: BoxShape.circle,
                border: Border.all(color: color, width: 1.5),
              ),
              child: Text(_sectionBadge(section.name), style: const TextStyle(color: _text, fontSize: 10)),
            ),
          ),
        ),
      ),
      if (editing)
        Positioned(
          left: badgeLeft,
          top: widget.height / 2 - 4,
          child: _CircleAction(icon: Icons.remove, color: kStageRed, tooltip: 'Excluir seção', onTap: () => _deleteSection(section)),
        ),
      if (editing && visibleWidth > 110)
        Positioned(
          left: loopLeft + 10,
          top: widget.height / 2 - 4,
          child: _CircleAction(
            icon: Icons.add,
            color: const Color(0xFF2B2D2E),
            tooltip: 'Adicionar seção',
            onTap: () => Navigator.of(context).push(MaterialPageRoute<void>(builder: (_) => SectionEditorScreen(trackId: widget.track.id))),
          ),
        ),
      if (visibleWidth >= 80)
        Positioned(
          left: loopLeft,
          top: 8,
          child: Tooltip(
            message: editing ? 'Laço infinito predefinido: ${section.name}' : 'Repetir ${section.name}',
            child: GestureDetector(
              onTap: () => editing
                  ? _updateSections([
                      for (final s in widget.track.sections)
                        s.id == section.id ? s.copyWith(presetInfiniteLoop: !s.presetInfiniteLoop) : s
                    ])
                  : _loop(section),
              onLongPress: transport.loopEnabled
                  ? () => ref.read(currentTrackProvider.notifier).setSectionLoop(section, queue: true)
                  : null,
              child: SizedBox(
                width: 36,
                height: 24,
                child: CustomPaint(painter: _LoopIconPainter(loopColor, infinite: section.presetInfiniteLoop && editing)),
              ),
            ),
          ),
        ),
    ];
  }
}

/// Ícone de laço do Playback (contorno de pílula aberta) e o ∞ do laço infinito.
class _LoopIconPainter extends CustomPainter {
  final Color color;
  final bool infinite;
  const _LoopIconPainter(this.color, {this.infinite = false});
  @override
  void paint(Canvas canvas, Size size) {
    final paint = Paint()
      ..color = color
      ..style = PaintingStyle.stroke
      ..strokeWidth = 2.2
      ..strokeCap = StrokeCap.round;
    final h = size.height * 0.62, w = size.width * 0.86;
    final rect = Rect.fromCenter(center: size.center(Offset.zero), width: w, height: h);
    if (infinite) {
      final r = h / 2;
      canvas.drawCircle(Offset(rect.left + r, rect.center.dy), r, paint);
      canvas.drawCircle(Offset(rect.right - r, rect.center.dy), r, paint);
      return;
    }
    final path = Path()..addRRect(RRect.fromRectAndRadius(rect, Radius.circular(h / 2)));
    // Abertura no topo, à direita (como o símbolo do Playback).
    final metric = path.computeMetrics().first;
    canvas.drawPath(metric.extractPath(metric.length * 0.06, metric.length * 0.94), paint);
  }

  @override
  bool shouldRepaint(covariant _LoopIconPainter old) => old.color != color || old.infinite != infinite;
}

class _WaveformPainter extends CustomPainter {
  final List<double>? peaks;
  final double lengthSeconds, viewStart, pixelsPerSecond, playheadX;
  final List<SongSection> sections;
  final List<bool> activeLoop;
  final List<double> bars, cues;
  final bool generating;

  _WaveformPainter({
    required this.peaks,
    required this.lengthSeconds,
    required this.viewStart,
    required this.pixelsPerSecond,
    required this.playheadX,
    required this.sections,
    required this.activeLoop,
    required this.bars,
    required this.cues,
    required this.generating,
  });

  double _x(double t) => (t - viewStart) * pixelsPerSecond;

  @override
  void paint(Canvas canvas, Size size) {
    if (size.width <= 0 || size.height <= 0) return;
    final top = 4.0, bottom = size.height - 10;
    final mid = (top + bottom) / 2;
    // Seções: caixas arredondadas com fundo e borda na cor da seção.
    for (var i = 0; i < sections.length; i++) {
      final s = sections[i];
      final rect = RRect.fromLTRBR(_x(s.startSeconds) + 1, top, _x(s.endSeconds) - 1, bottom, const Radius.circular(8));
      if (rect.right < 0 || rect.left > size.width) continue;
      final color = _sectionColor(s.name);
      canvas.drawRRect(rect, Paint()..color = color.withValues(alpha: activeLoop[i] ? 0.22 : 0.10));
      canvas.drawRRect(
          rect,
          Paint()
            ..style = PaintingStyle.stroke
            ..color = (activeLoop[i] ? kStageGreen : const Color(0xFF3A3C3E)));
      // Trechos cortados (trim) escurecidos.
      final dim = Paint()..color = Colors.black.withValues(alpha: 0.5);
      if (s.trimStartSeconds > 0) canvas.drawRect(Rect.fromLTRB(_x(s.startSeconds), top, _x(s.playStart), bottom), dim);
      if (s.trimEndSeconds > 0) canvas.drawRect(Rect.fromLTRB(_x(s.playEnd), top, _x(s.endSeconds), bottom), dim);
    }
    // Grade de compassos.
    final barPaint = Paint()..color = Colors.white.withValues(alpha: 0.16);
    for (final b in bars) {
      final x = _x(b);
      if (x < 0) continue;
      if (x > size.width) break;
      canvas.drawRect(Rect.fromLTWH(x, top, 1, bottom - top), barPaint);
    }
    // Waveform, tingida pela seção em que cada barra cai.
    final p = peaks;
    if (p != null && p.isNotEmpty && lengthSeconds > 0) {
      final secondsPerPeak = lengthSeconds / p.length;
      final step = math.max(1, (1.5 / (secondsPerPeak * pixelsPerSecond)).ceil());
      final first = math.max(0, (viewStart / secondsPerPeak).floor());
      final last = math.min(p.length, ((viewStart + size.width / pixelsPerSecond) / secondsPerPeak).ceil() + 1);
      final width = math.max(1.0, secondsPerPeak * step * pixelsPerSecond - 0.6);
      var sectionIndex = 0;
      for (var i = first - first % step; i < last; i += step) {
        final t = i * secondsPerPeak;
        while (sectionIndex < sections.length && sections[sectionIndex].endSeconds <= t) {
          sectionIndex++;
        }
        final inSection = sectionIndex < sections.length && sections[sectionIndex].startSeconds <= t;
        final tint = inSection ? _sectionColor(sections[sectionIndex].name) : Colors.white;
        final color = Color.lerp(Colors.white, tint, 0.22)!.withValues(alpha: 0.82);
        var peak = 0.0;
        for (var j = i; j < math.min(i + step, p.length); j++) {
          peak = math.max(peak, p[j]);
        }
        final h = peak.clamp(0.0, 1.0) * (bottom - top) * 0.82;
        canvas.drawRect(Rect.fromLTWH(_x(t), mid - h / 2, width, h), Paint()..color = color);
      }
    } else {
      canvas.drawRect(Rect.fromLTWH(_x(0), mid - 0.5, lengthSeconds * pixelsPerSecond, 1),
          Paint()..color = Colors.white.withValues(alpha: 0.35));
      if (generating) {
        final tp = TextPainter(
          text: const TextSpan(text: 'Gerando waveform...', style: TextStyle(color: _textFaint, fontSize: 12)),
          textDirection: TextDirection.ltr,
        )..layout();
        tp.paint(canvas, Offset(size.width / 2 - tp.width / 2, mid + 6));
      }
    }
    // Gatilhos MIDI: triângulos laranja sob a waveform.
    final cuePaint = Paint()..color = kStageOrange;
    for (final c in cues) {
      final x = _x(c);
      if (x < -5 || x > size.width + 5) continue;
      canvas.drawPath(
          Path()
            ..moveTo(x - 5, size.height)
            ..lineTo(x, size.height - 6)
            ..lineTo(x + 5, size.height)
            ..close(),
          cuePaint);
    }
    // Agulha.
    canvas.drawRect(Rect.fromLTWH(playheadX - 1, 0, 2, size.height - 2), Paint()..color = Colors.white);
    canvas.drawRect(Rect.fromLTWH(playheadX - 4, 0, 8, 2), Paint()..color = Colors.white);
  }

  @override
  bool shouldRepaint(covariant _WaveformPainter old) =>
      old.peaks != peaks ||
      old.viewStart != viewStart ||
      old.pixelsPerSecond != pixelsPerSecond ||
      old.playheadX != playheadX ||
      old.sections != sections ||
      old.bars != bars ||
      old.cues.length != cues.length ||
      old.generating != generating ||
      old.lengthSeconds != lengthSeconds ||
      !_same(old.activeLoop, activeLoop);

  static bool _same(List<bool> a, List<bool> b) {
    if (a.length != b.length) return false;
    for (var i = 0; i < a.length; i++) {
      if (a[i] != b[i]) return false;
    }
    return true;
  }
}


/// Painel de baixo: faixas ou buses (ou a waveform no celular deitado), o console e o Master.
class _BottomPane extends ConsumerWidget {
  final Track track;
  final _Pane pane;
  final bool short;
  const _BottomPane({required this.track, required this.pane, required this.short});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final notifier = ref.read(currentTrackProvider.notifier);
    // Com a automação agindo, os faders mostram os valores que o motor está aplicando.
    final mix = ref.watch(automatedMixProvider);
    final masterVolume = mix?.master ?? track.masterVolume;
    return Container(
      color: _bg,
      padding: const EdgeInsets.fromLTRB(4, 8, 6, 6),
      child: Row(children: [
        Expanded(
          child: switch (pane) {
            _Pane.waveform => LayoutBuilder(
                builder: (_, c) => _WaveformView(track: track, height: c.maxHeight),
              ),
            _Pane.buses => _BusStrips(track: track),
            _Pane.tracks => _TrackStrips(track: track),
          },
        ),
        const SizedBox(width: 4),
        _Console(track: track, pane: pane, short: short),
        const SizedBox(width: 8),
        _MasterStrip(volume: masterVolume, onChanged: notifier.setMasterVolume),
      ]),
    );
  }
}

/// Faixas: o click do WTracks (gerado pelo motor) primeiro, com ▶ para abrir as subdivisões (Playback: segurar o fader
/// do Click abre Acento, 1/4, 1/8 e 1/16), depois os canais da música.
class _TrackStrips extends ConsumerStatefulWidget {
  final Track track;
  const _TrackStrips({required this.track});
  @override
  ConsumerState<_TrackStrips> createState() => _TrackStripsState();
}

class _TrackStripsState extends ConsumerState<_TrackStrips> {
  bool _subdivisions = false;

  @override
  Widget build(BuildContext context) {
    final track = widget.track;
    final notifier = ref.read(currentTrackProvider.notifier);
    final mix = ref.watch(automatedMixProvider);
    final editing = ref.watch(performanceEditProvider);
    final clickOn = ref.watch(clickEnabledProvider);
    final click = track.clickSettings;
    void clickGain(ClickSettings next) => notifier.updateClickSettings(next);
    final strips = <Widget>[
      _Strip(
        label: 'Metrônomo',
        expandable: true,
        expanded: _subdivisions,
        onExpand: () => setState(() => _subdivisions = !_subdivisions),
        volume: click.volume,
        max: 2,
        muted: !clickOn,
        onMute: () => _setClick(ref, !clickOn),
        onVolume: (v) => clickGain(click.copyWith(volume: v)),
      ),
      if (_subdivisions)
        for (final (label, value, apply) in <(String, double, ClickSettings Function(double))>[
          ('Acento', click.accentGain, (v) => click.copyWith(accentGain: v)),
          ('1/4', click.quarterGain, (v) => click.copyWith(quarterGain: v)),
          ('1/8', click.eighthGain, (v) => click.copyWith(eighthGain: v)),
          ('1/16', click.sixteenthGain, (v) => click.copyWith(sixteenthGain: v)),
        ])
          _Strip(label: label, volume: value, max: 2, dimLabel: true, onVolume: (v) => clickGain(apply(v))),
      for (var i = 0; i < track.channels.length; i++)
        _Strip(
          key: ValueKey('channel-$i'),
          label: track.channels[i].label,
          meter: _ChannelMeter(index: i),
          volume: mix != null && i < mix.volumes.length ? mix.volumes[i] : track.channels[i].volume,
          muted: mix != null && i < mix.mutes.length ? mix.mutes[i] : track.channels[i].muted,
          soloed: track.channels[i].soloed,
          route: track.channels[i].route,
          onSolo: () => notifier.toggleChannelSolo(i),
          onMute: editing
              ? () => _chooseOutput(context, track.channels[i].label, track.channels[i].route,
                  (r) => notifier.setChannelRoute(i, r))
              : () => notifier.setChannelMuted(i, !track.channels[i].muted),
          onVolume: (v) => notifier.setChannelVolume(i, v),
        ),
    ];
    return LayoutBuilder(builder: (context, c) {
      // As faixas se alargam até 110 px quando cabem todas (Playback no iPad: ~120 px).
      final width = (c.maxWidth / strips.length).clamp(66.0, 110.0);
      return ListView(scrollDirection: Axis.horizontal, children: [for (final s in strips) SizedBox(width: width, child: s)]);
    });
  }
}

class _BusStrips extends ConsumerWidget {
  final Track track;
  const _BusStrips({required this.track});
  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final notifier = ref.read(currentTrackProvider.notifier);
    final mix = ref.watch(automatedMixProvider);
    final editing = ref.watch(performanceEditProvider);
    if (track.buses.isEmpty) {
      return Center(
        child: TextButton(
          onPressed: () => Navigator.of(context).push(MaterialPageRoute<void>(builder: (_) => BusesScreen(trackId: track.id))),
          child: const Text('Nenhum bus. Criar buses…', style: TextStyle(color: _textDim)),
        ),
      );
    }
    return LayoutBuilder(builder: (context, c) => ListView(scrollDirection: Axis.horizontal, children: [
      for (var b = 0; b < track.buses.length; b++)
        SizedBox(width: (c.maxWidth / track.buses.length).clamp(66.0, 110.0), child:
        _Strip(
          key: ValueKey('bus-${track.buses[b].id}'),
          label: track.buses[b].name,
          meter: _ChannelMeter(index: b, isBus: true),
          volume: mix != null && b < mix.busVolumes.length ? mix.busVolumes[b] : track.buses[b].volume,
          muted: mix != null && b < mix.busMutes.length ? mix.busMutes[b] : track.buses[b].muted,
          soloed: track.buses[b].soloed,
          route: track.buses[b].route,
          onSolo: () => notifier.toggleBusSolo(track.buses[b].id),
          onMute: editing
              ? () => _chooseOutput(context, track.buses[b].name, track.buses[b].route,
                  (r) => notifier.updateBus(track.buses[b].copyWith(route: r)))
              : () => notifier.updateBus(track.buses[b].copyWith(muted: !track.buses[b].muted)),
          onVolume: (v) => notifier.updateBus(track.buses[b].copyWith(volume: v)),
        )),
    ]));
  }
}

/// Saída de uma faixa ou bus (Playback: no modo de edição, tocar no nome abre "Select Output").
Future<void> _chooseOutput(BuildContext context, String name, ChannelRoute current, ValueChanged<ChannelRoute> apply) async {
  final choice = await showDialog<ChannelRoute>(
    context: context,
    builder: (ctx) => _SheetDialog(title: 'Saída: $name', children: [
      _SheetSection(children: [
        for (final (route, label) in const [
          (ChannelRoute.stereo, 'Estéreo'),
          (ChannelRoute.left, 'Esquerda (mono)'),
          (ChannelRoute.right, 'Direita (mono)'),
        ])
          _SheetRow(
            label: label,
            onTap: () => Navigator.of(ctx).pop(route),
            trailing: Icon(route == current ? Icons.check : null, color: const Color(0xFF0A84FF), size: 20),
          ),
      ]),
    ]),
  );
  if (choice != null) apply(choice);
}

/// Faixa do mixer (Playback: "S" no alto, fader com traços dos dois lados e tampa com linha ciano, medidor fino à
/// esquerda e o nome embaixo; tocar no nome muta).
class _Strip extends StatelessWidget {
  final String label;
  final double volume, max;
  final bool muted, soloed, expandable, expanded, dimLabel;
  final ChannelRoute route;
  final Widget? meter;
  final VoidCallback? onSolo, onMute, onExpand;
  final ValueChanged<double> onVolume;
  const _Strip({
    super.key,
    required this.label,
    required this.volume,
    this.max = 1,
    this.muted = false,
    this.soloed = false,
    this.expandable = false,
    this.expanded = false,
    this.dimLabel = false,
    this.route = ChannelRoute.stereo,
    this.meter,
    this.onSolo,
    this.onMute,
    this.onExpand,
    required this.onVolume,
  });

  @override
  Widget build(BuildContext context) {
    final routeMark = switch (route) { ChannelRoute.stereo => '', ChannelRoute.left => ' · E', ChannelRoute.right => ' · D' };
    return SizedBox(
      child: Column(children: [
        SizedBox(
          height: 26,
          child: Row(mainAxisAlignment: MainAxisAlignment.center, children: [
            if (onSolo != null)
              Tooltip(
                message: 'Solo $label',
                child: GestureDetector(
                  onTap: onSolo,
                  child: Container(
                    width: 24,
                    height: 24,
                    alignment: Alignment.center,
                    decoration: BoxDecoration(
                      color: soloed ? kStageYellow : const Color(0xFF2B2D2E),
                      shape: BoxShape.circle,
                    ),
                    child: Text('S', style: TextStyle(color: soloed ? Colors.black : const Color(0xFF8E9091), fontSize: 11)),
                  ),
                ),
              ),
                      const SizedBox(width: 30),
          ]),
        ),
        const SizedBox(height: 4),
        Expanded(
          child: Row(mainAxisAlignment: MainAxisAlignment.center, children: [
            SizedBox(width: 3, child: meter ?? const SizedBox()),
            const SizedBox(width: 4),
            SizedBox(width: 50, child: _Fader(value: volume, max: max, muted: muted, onChanged: onVolume)),
            const SizedBox(width: 7),
          ]),
        ),
        const SizedBox(height: 6),
        Tooltip(
          message: onMute == null ? label : 'Mutar $label',
          child: InkWell(
            onTap: onMute,
            child: SizedBox(
              height: 24,
              child: Row(mainAxisAlignment: MainAxisAlignment.center, children: [
                Flexible(
                  child: Text(
                    '$label$routeMark',
                    maxLines: 1,
                    overflow: TextOverflow.ellipsis,
                    style: TextStyle(
                      color: muted ? kStageRed : (dimLabel ? _textFaint : _text),
                      fontSize: 12,
                      decoration: muted ? TextDecoration.lineThrough : null,
                      decorationColor: kStageRed,
                    ),
                  ),
                ),
                if (expandable)
                  GestureDetector(
                    onTap: onExpand,
                    child: Padding(
                      padding: const EdgeInsets.only(left: 3),
                      child: Icon(expanded ? Icons.arrow_left : Icons.arrow_right, size: 16, color: _textFaint),
                    ),
                  ),
              ]),
            ),
          ),
        ),
      ]),
    );
  }
}

/// Fader vertical com traços dos dois lados e tampa escura com a linha ciano (Playback: MixerTrackFaderCapView).
/// Muda só arrastando (Playback: "press and hold any fader"), para um toque acidental não mexer no volume.
class _Fader extends StatelessWidget {
  final double value, max;
  final bool muted;
  final ValueChanged<double> onChanged;
  const _Fader({super.key, required this.value, this.max = 1, this.muted = false, required this.onChanged});

  static const capHeight = 30.0;

  @override
  Widget build(BuildContext context) {
    return LayoutBuilder(builder: (context, c) {
      final travel = math.max(1.0, c.maxHeight - capHeight);
      return Semantics(
        slider: true,
        value: '${(value / max * 100).round()}%',
        child: GestureDetector(
          behavior: HitTestBehavior.opaque,
          onVerticalDragUpdate: (d) => onChanged((value - d.delta.dy / travel * max).clamp(0.0, max)),
          child: CustomPaint(
            size: Size(c.maxWidth, c.maxHeight),
            painter: _FaderPainter(fraction: (value / max).clamp(0.0, 1.0), muted: muted),
          ),
        ),
      );
    });
  }
}

class _FaderPainter extends CustomPainter {
  final double fraction;
  final bool muted;
  const _FaderPainter({required this.fraction, required this.muted});

  @override
  void paint(Canvas canvas, Size size) {
    const capH = _Fader.capHeight;
    final cx = size.width / 2;
    final travel = size.height - capH;
    // Traços dos dois lados do trilho.
    final tick = Paint()..color = kStageTick;
    const ticks = 11;
    for (var i = 0; i <= ticks; i++) {
      final y = capH / 2 + travel * i / ticks;
      canvas.drawRect(Rect.fromLTWH(cx - 22, y, 12, 1), tick);
      canvas.drawRect(Rect.fromLTWH(cx + 10, y, 12, 1), tick);
    }
    // Trilho (fenda preta).
    canvas.drawRRect(RRect.fromLTRBR(cx - 2.5, capH / 2, cx + 2.5, size.height - capH / 2, const Radius.circular(2)),
        Paint()..color = Colors.black);
    // Tampa.
    final top = travel * (1 - fraction);
    final cap = RRect.fromLTRBR(cx - 22, top, cx + 22, top + capH, const Radius.circular(3));
    canvas.drawRRect(cap, Paint()..color = const Color(0xFF111415));
    final groove = Paint()..color = const Color(0xFF1E2224);
    for (var y = top + 5; y < top + capH - 3; y += 4) {
      canvas.drawRect(Rect.fromLTWH(cx - 19, y, 38, 1), groove);
    }
    canvas.drawRRect(cap, Paint()
      ..style = PaintingStyle.stroke
      ..color = const Color(0xFF2E3234));
    canvas.drawRect(Rect.fromLTWH(cx - 17, top + capH / 2 - 1, 34, 2), Paint()..color = muted ? _textFaint : _accent);
  }

  @override
  bool shouldRepaint(covariant _FaderPainter old) => old.fraction != fraction || old.muted != muted;
}

/// Console entre as faixas e o Master (Playback: alternar painel, MUTE MIDI, Laço e Laço infinito). AUTO (automação
/// do mixer) é do WTracks.
class _Console extends ConsumerWidget {
  final Track track;
  final _Pane pane;
  final bool short;
  const _Console({required this.track, required this.pane, required this.short});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final sections = track.sections;
    // Só reconstrói quando a seção sob a agulha ou o estado do laço muda, não a cada tick de posição.
    final at = ref.watch(transportProvider.select((t) =>
        sections.indexWhere((s) => t.positionSeconds >= s.playStart && t.positionSeconds < s.playEnd)));
    final loopEnabled = ref.watch(transportProvider.select((t) => t.loopEnabled));
    final repeats = ref.watch(transportProvider.select((t) => t.loopRepeats));
    final midiMuted = ref.watch(midiCuesMutedProvider);
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

    // Laço: arma uma repetição da seção atual (duas passagens), depois a música segue; laço infinito: repete até
    // tocar de novo (Playback: Loop / Infinite Loop).
    final finite = loopEnabled && repeats > 0;
    final infinite = loopEnabled && repeats == 0;
    final panes = [_Pane.tracks, _Pane.buses, if (short) _Pane.waveform];
    Widget cell(Widget child, {Key? key}) => SizedBox(key: key, width: 60, height: short ? 38 : 50, child: child);
    return SizedBox(
      width: 60,
      child: SingleChildScrollView(
        child: Column(children: [
          cell(_BarButton(
            tooltip: switch (pane) {
              _Pane.tracks => 'Faixas (toque para buses)',
              _Pane.buses => short ? 'Buses (toque para a waveform)' : 'Buses (toque para faixas)',
              _Pane.waveform => 'Waveform (toque para faixas)',
            },
            onTap: () => ref.read(_paneProvider.notifier).state = panes[(panes.indexOf(pane) + 1) % panes.length],
            child: Icon(
                switch (pane) { _Pane.tracks => Icons.tune, _Pane.buses => Icons.call_split, _Pane.waveform => Icons.graphic_eq },
                color: _textDim, size: 24),
          )),
          const SizedBox(height: 8),
          cell(_BarButton(
            tooltip: midiMuted ? 'Reativar MIDI' : 'Silenciar gatilhos MIDI',
            highlighted: midiMuted,
            onTap: () => ref.read(midiCuesMutedProvider.notifier).set(!midiMuted),
            child: Text('MUTE\nMIDI',
                textAlign: TextAlign.center,
                style: TextStyle(color: midiMuted ? kStageRed : _textFaint, fontSize: 10, height: 1.2, letterSpacing: 0.5)),
          )),
          const SizedBox(height: 8),
          cell(_BarButton(
            tooltip: finite ? 'Desativar loop' : 'Repetir seção atual',
            highlighted: finite,
            onTap: finite ? () => transport.disableLoop() : (section == null ? null : () => loop(section.copyWith(loopCount: 2))),
            child: SizedBox(
                width: 30,
                height: 20,
                child: CustomPaint(painter: _LoopIconPainter(finite ? kStageGreen : (section == null ? _border : _textFaint)))),
          )),
          const SizedBox(height: 8),
          cell(_BarButton(
            tooltip: infinite ? 'Desativar loop' : 'Laço infinito na seção atual',
            highlighted: infinite,
            onTap: infinite ? () => transport.disableLoop() : (section == null ? null : () => loop(section.copyWith(loopCount: 0))),
            child: SizedBox(
                width: 30,
                height: 20,
                child: CustomPaint(
                    painter: _LoopIconPainter(infinite ? kStageGreen : (section == null ? _border : _textFaint), infinite: true))),
          )),
          if (track.mixerAutomation.isNotEmpty) ...[
            const SizedBox(height: 8),
            cell(
              key: const Key('transport-automation'),
              _BarButton(
                tooltip: 'Automação do mixer',
                highlighted: track.automationEnabled,
                onTap: () => trackNotifier.setAutomationEnabled(!track.automationEnabled),
                child: Text('AUTO', style: TextStyle(color: track.automationEnabled ? kStageGreen : _textFaint, fontSize: 11)),
              ),
            ),
          ],
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
      width: 72,
      child: Column(children: [
        Expanded(
          child: Row(children: [
            const _MasterMeter(),
            Expanded(child: _Fader(key: const Key('master-volume'), value: volume.clamp(0.0, 2.0), max: 2, onChanged: onChanged)),
          ]),
        ),
        const SizedBox(height: 4),
        const Text('Master', style: TextStyle(color: _text, fontSize: 12)),
        Text('${(volume * 100).round()}%',
            style: const TextStyle(color: _textFaint, fontSize: 9, fontFeatures: [FontFeature.tabularFigures()])),
      ]),
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
            : kStageMeterGreen;
    return Container(
      width: thickness,
      color: Colors.black,
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
      padding: const EdgeInsets.symmetric(vertical: _Fader.capHeight / 2),
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
      padding: const EdgeInsets.symmetric(vertical: _Fader.capHeight / 2),
      child: Row(children: [
        _MeterBar(key: const Key('meter-master-l'), level: at(0), thickness: 4),
        const SizedBox(width: 4),
        _MeterBar(key: const Key('meter-master-r'), level: at(1), thickness: 4),
      ]),
    );
  }
}
