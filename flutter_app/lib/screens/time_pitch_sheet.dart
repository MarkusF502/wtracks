import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import '../models/time_pitch_settings.dart';
import '../providers/engine_provider.dart';
import '../theme/app_colors.dart';

/// Tom (semitons) e andamento da música. Aplicar renderiza as faixas offline.
class TimePitchSheet extends ConsumerStatefulWidget {
  final String trackId;
  const TimePitchSheet({super.key, required this.trackId});
  @override
  ConsumerState<TimePitchSheet> createState() => _TimePitchSheetState();
}

class _TimePitchSheetState extends ConsumerState<TimePitchSheet> {
  late TimePitchSettings _draft;
  bool _busy = false;
  late final CurrentTrackNotifier _notifier;

  @override
  void initState() {
    super.initState();
    _notifier = ref.read(currentTrackProvider.notifier);
    _draft = ref.read(currentTrackProvider)?.timePitch ?? const TimePitchSettings();
    _notifier.timePitchListeners.add(_onProgress);
  }

  @override
  void dispose() {
    _notifier.timePitchListeners.remove(_onProgress);
    super.dispose();
  }

  void _onProgress() {
    if (mounted) setState(() {});
  }

  Future<void> _apply() async {
    if (_busy) return;
    setState(() => _busy = true);
    try {
      final ok = await _notifier.setTimePitch(widget.trackId, _draft);
      if (!mounted) return;
      if (!ok) {
        ScaffoldMessenger.of(context).showSnackBar(
          const SnackBar(content: Text('Não foi possível aplicar o tom e o andamento.')),
        );
        return;
      }
      await ref.read(trackLibraryProvider.notifier).saveCurrent();
      if (mounted) Navigator.of(context).pop();
    } finally {
      if (mounted) setState(() => _busy = false);
    }
  }

  String get _semitoneLabel => _draft.semitones > 0 ? '+${_draft.semitones}' : '${_draft.semitones}';

  @override
  Widget build(BuildContext context) {
    final active = ref.watch(currentTrackProvider)?.id == widget.trackId;
    final progress = _notifier.timePitchProgress;
    return Padding(
      padding: EdgeInsets.fromLTRB(20, 16, 20, 16 + MediaQuery.of(context).viewInsets.bottom),
      child: Column(
        mainAxisSize: MainAxisSize.min,
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          const Text('Tom e andamento', style: TextStyle(fontSize: 18, fontWeight: FontWeight.w600)),
          const SizedBox(height: 12),
          Row(
            children: [
              const Expanded(child: Text('Tom (semitons)')),
              IconButton(
                tooltip: 'Descer meio tom',
                icon: const Icon(Icons.remove_circle_outline),
                onPressed: _busy || _draft.semitones <= TimePitchSettings.minSemitones
                    ? null
                    : () => setState(() => _draft = _draft.copyWith(semitones: _draft.semitones - 1)),
              ),
              SizedBox(
                width: 44,
                child: Text(_semitoneLabel, key: const Key('semitone-value'), textAlign: TextAlign.center),
              ),
              IconButton(
                tooltip: 'Subir meio tom',
                icon: const Icon(Icons.add_circle_outline),
                onPressed: _busy || _draft.semitones >= TimePitchSettings.maxSemitones
                    ? null
                    : () => setState(() => _draft = _draft.copyWith(semitones: _draft.semitones + 1)),
              ),
            ],
          ),
          Text('Andamento: ${(_draft.tempoRatio * 100).round()}%'),
          Slider(
            key: const Key('tempo-slider'),
            value: _draft.tempoRatio.clamp(TimePitchSettings.minTempo, TimePitchSettings.maxTempo),
            min: TimePitchSettings.minTempo,
            max: TimePitchSettings.maxTempo,
            divisions: 150,
            onChanged: _busy ? null : (v) => setState(() => _draft = _draft.copyWith(tempoRatio: (v * 100).round() / 100)),
          ),
          SwitchListTile(
            contentPadding: EdgeInsets.zero,
            title: const Text('Algoritmo complexo'),
            subtitle: const Text('Melhor afinação; transientes mais suaves.'),
            value: _draft.complex,
            onChanged: _busy ? null : (v) => setState(() => _draft = _draft.copyWith(complex: v)),
          ),
          if (_busy && progress != null) ...[
            LinearProgressIndicator(value: progress > 0 ? progress : null, color: kAccent),
            const SizedBox(height: 8),
          ],
          Row(
            mainAxisAlignment: MainAxisAlignment.end,
            children: [
              TextButton(
                onPressed: _busy ? null : () => setState(() => _draft = const TimePitchSettings()),
                child: const Text('Original'),
              ),
              const SizedBox(width: 8),
              if (_busy)
                OutlinedButton(onPressed: _notifier.cancelTimePitch, child: const Text('Cancelar'))
              else
                FilledButton(onPressed: active ? _apply : null, child: const Text('Aplicar')),
            ],
          ),
        ],
      ),
    );
  }
}
