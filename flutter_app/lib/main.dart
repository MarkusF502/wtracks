import 'dart:async';

import 'package:flutter/material.dart';

import 'file_import_service.dart';
import '/native/wtracks_bindings.dart';

void main() {
  runApp(const WTracksApp());
}

class WTracksApp extends StatelessWidget {
  const WTracksApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'WTracks',
      theme: ThemeData(colorSchemeSeed: Colors.indigo, useMaterial3: true),
      home: const EnginePage(),
    );
  }
}

class EnginePage extends StatefulWidget {
  const EnginePage({super.key});

  @override
  State<EnginePage> createState() => _EnginePageState();
}

class _EnginePageState extends State<EnginePage> {
  final _engine = WTracksEngine();
  final _fileImportService = FileImportService();

  Timer? _positionTimer;

  bool _engineReady = false;
  bool _isLoadingFiles = false;
  String? _lastError;

  double _positionSeconds = 0;
  double _lengthSeconds = 0;
  bool _isPlaying = false;

  bool _clickEnabled = false;
  double _clickBpm = 120;
  int _clickNumerator = 4;
  int _clickDenominator = 4;

  // Estado de UI por canal -- espelha o engine, mas mantido aqui pra não
  // precisar de um getter nativo por canal a cada frame.
  int _channelCount = 0;
  final List<double> _channelVolumes = [];
  final List<bool> _channelMuted = [];
  final List<String> _channelNames = [];

  @override
  void initState() {
    super.initState();
    _engineReady = _engine.initialise();
    if (!_engineReady) {
      _lastError = 'Falha ao inicializar o dispositivo de áudio.';
    }

    // Mesma cadência que o app de teste JUCE usava (10Hz / 100ms).
    _positionTimer = Timer.periodic(const Duration(milliseconds: 100), (_) {
      if (!mounted) return;
      setState(() {
        _positionSeconds = _engine.currentPositionSeconds;
        _lengthSeconds = _engine.totalLengthSeconds;
        _isPlaying = _engine.isPlaying;
      });
    });
  }

  @override
  void dispose() {
    _positionTimer?.cancel();
    _engine.shutdown();
    super.dispose();
  }

  Future<void> _onLoadPressed() async {
    setState(() {
      _isLoadingFiles = true;
      _lastError = null;
    });

    try {
      final channelPaths = await _fileImportService.pickAndImportChannelFiles();
      if (channelPaths.isEmpty) return; // usuário cancelou

      _engine.stop();

      final songId = 'teste_manual_${DateTime.now().millisecondsSinceEpoch}';
      final loaded = _engine.loadTrack(songId, channelPaths);

      if (!loaded) {
        setState(() {
          _lastError = 'Falha ao carregar um ou mais canais -- verifique se '
              'todos têm o mesmo sample rate e duração compatível.';
        });
        return;
      }

      _rebuildChannelState(channelPaths);
    } catch (e) {
      setState(() => _lastError = 'Erro ao importar arquivos: $e');
    } finally {
      setState(() => _isLoadingFiles = false);
    }
  }

  void _rebuildChannelState(List<String> channelPaths) {
    final count = _engine.channelCount;
    setState(() {
      _channelCount = count;
      _channelVolumes
        ..clear()
        ..addAll(List.filled(count, 1.0));
      _channelMuted
        ..clear()
        ..addAll(List.filled(count, false));
      _channelNames
        ..clear()
        ..addAll(List.generate(count, (i) {
          // Nome amigável a partir do arquivo (sem extensão/caminho),
          // só pra identificar o canal na UI.
          final fileName = channelPaths[i].split('/').last;
          return fileName.contains('.')
              ? fileName.substring(0, fileName.lastIndexOf('.'))
              : fileName;
        }));
    });
  }

  String _formatSeconds(double seconds) {
    final total = seconds.isFinite ? seconds.round() : 0;
    final minutes = total ~/ 60;
    final secs = total % 60;
    return '${minutes.toString().padLeft(2, '0')}:${secs.toString().padLeft(2, '0')}';
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('WTracks — teste FFI')),
      body: SafeArea(
        child: ListView(
          padding: const EdgeInsets.all(16),
          children: [
            if (!_engineReady)
              const Card(
                color: Colors.redAccent,
                child: Padding(
                  padding: EdgeInsets.all(12),
                  child: Text('Motor de áudio não inicializou.',
                      style: TextStyle(color: Colors.white)),
                ),
              ),
            if (_lastError != null)
              Card(
                color: Colors.orangeAccent.shade100,
                child: Padding(
                  padding: const EdgeInsets.all(12),
                  child: Text(_lastError!),
                ),
              ),
            const SizedBox(height: 8),
            FilledButton.icon(
              onPressed: _engineReady && !_isLoadingFiles ? _onLoadPressed : null,
              icon: _isLoadingFiles
                  ? const SizedBox(
                      width: 16,
                      height: 16,
                      child: CircularProgressIndicator(strokeWidth: 2))
                  : const Icon(Icons.folder_open),
              label: const Text('Carregar canais (.wav)'),
            ),
            const SizedBox(height: 16),
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              children: [
                IconButton.filledTonal(
                  onPressed: _channelCount > 0 ? () => _engine.play() : null,
                  icon: const Icon(Icons.play_arrow),
                ),
                IconButton.filledTonal(
                  onPressed: _channelCount > 0 ? () => _engine.pause() : null,
                  icon: const Icon(Icons.pause),
                ),
                IconButton.filledTonal(
                  onPressed: _channelCount > 0 ? () => _engine.stop() : null,
                  icon: const Icon(Icons.stop),
                ),
              ],
            ),
            const SizedBox(height: 8),
            Slider(
              value: _lengthSeconds > 0
                  ? _positionSeconds.clamp(0, _lengthSeconds)
                  : 0,
              max: _lengthSeconds > 0 ? _lengthSeconds : 1,
              onChanged: _lengthSeconds > 0
                  ? (value) => setState(() => _positionSeconds = value)
                  : null,
              // Só faz o seek de fato ao soltar, mesmo princípio do
              // seekSlider.onDragEnd no app de teste JUCE -- evita
              // sobrecarregar o engine com um seek por pixel arrastado.
              onChangeEnd: (value) => _engine.seekToSeconds(value),
            ),
            Center(
              child: Text(
                '${_formatSeconds(_positionSeconds)} / ${_formatSeconds(_lengthSeconds)}'
                '  ${_isPlaying ? "[tocando]" : "[parado]"}',
              ),
            ),
            const SizedBox(height: 16),
            const Divider(),
            SwitchListTile(
              title: const Text('Click habilitado'),
              value: _clickEnabled,
              onChanged: (value) {
                setState(() => _clickEnabled = value);
                _engine.setClickEnabled(value);
              },
            ),
            ListTile(
              title: const Text('BPM'),
              subtitle: Slider(
                value: _clickBpm,
                min: 40,
                max: 220,
                divisions: 180,
                label: _clickBpm.round().toString(),
                onChanged: (value) {
                  setState(() => _clickBpm = value);
                  _engine.setClickBpm(value);
                },
              ),
              trailing: Text(_clickBpm.round().toString()),
            ),
            ListTile(
              title: const Text('Compasso do click'),
              subtitle: Row(
                children: [
                  Expanded(
                    child: DropdownButton<int>(
                      value: _clickNumerator,
                      isExpanded: true,
                      items: const [
                        DropdownMenuItem(value: 2, child: Text('2')),
                        DropdownMenuItem(value: 3, child: Text('3')),
                        DropdownMenuItem(value: 4, child: Text('4')),
                        DropdownMenuItem(value: 6, child: Text('6')),
                        DropdownMenuItem(value: 8, child: Text('8')),
                      ],
                      onChanged: (value) {
                        if (value == null) return;
                        setState(() => _clickNumerator = value);
                        _engine.setClickTimeSignature(value, _clickDenominator);
                      },
                    ),
                  ),
                  const Padding(
                    padding: EdgeInsets.symmetric(horizontal: 8),
                    child: Text('/'),
                  ),
                  SizedBox(
                    width: 110,
                    child: DropdownButton<int>(
                      value: _clickDenominator,
                      isExpanded: true,
                      items: const [
                        DropdownMenuItem(value: 2, child: Text('2')),
                        DropdownMenuItem(value: 4, child: Text('4')),
                        DropdownMenuItem(value: 8, child: Text('8')),
                      ],
                      onChanged: (value) {
                        if (value == null) return;
                        setState(() => _clickDenominator = value);
                        _engine.setClickTimeSignature(_clickNumerator, value);
                      },
                    ),
                  ),
                ],
              ),
              trailing: Text('$_clickNumerator/$_clickDenominator'),
            ),
            const SizedBox(height: 16),
            const Divider(),
            if (_channelCount == 0)
              const Padding(
                padding: EdgeInsets.symmetric(vertical: 24),
                child: Center(child: Text('Nenhum canal carregado ainda.')),
              )
            else
              for (var i = 0; i < _channelCount; i++) _buildChannelRow(i),
          ],
        ),
      ),
    );
  }

  Widget _buildChannelRow(int index) {
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 4),
      child: Row(
        children: [
          SizedBox(
            width: 90,
            child: Text(
              _channelNames.length > index ? _channelNames[index] : 'Canal $index',
              overflow: TextOverflow.ellipsis,
            ),
          ),
          Expanded(
            child: Slider(
              value: _channelVolumes[index],
              onChanged: (value) {
                setState(() => _channelVolumes[index] = value);
                _engine.setChannelVolume(index, value);
              },
            ),
          ),
          IconButton(
            icon: Icon(_channelMuted[index] ? Icons.volume_off : Icons.volume_up),
            onPressed: () {
              final muted = !_channelMuted[index];
              setState(() => _channelMuted[index] = muted);
              _engine.setChannelMuted(index, muted);
            },
          ),
        ],
      ),
    );
  }
}