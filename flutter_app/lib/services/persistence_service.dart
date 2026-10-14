import 'dart:convert';
import 'dart:io';

import 'package:flutter/foundation.dart';
import 'package:path_provider/path_provider.dart';

import '../models/track.dart';

/// Persiste [Track]/[Setlist]/[ClickSettings] em disco como JSON local,
/// sob o diretório privado do app (`getApplicationSupportDirectory()`),
/// que sobrevive à limpeza de cache do Android e só é apagado se o app for
/// desinstalado.
///
/// Layout em disco (ver spec):
/// ```
/// <appSupportDir>/wtracks_data/
///   tracks/<trackId>.json
///   setlists/<setlistId>.json
///   audio/<trackId>/<nome-do-arquivo-original>.wav
///   waveforms/<trackId>.json   -- { "peaks": [0.12, 0.87, ...] }
/// ```
class PersistenceService {
  /// Resolve o diretório raiz onde `wtracks_data/` é criado. Por padrão usa
  /// `getApplicationSupportDirectory()` (o real, do path_provider); testes
  /// injetam um `Directory.systemTemp.createTempSync()` aqui pra não tocar
  /// no diretório real do app/dispositivo.
  final Future<Directory> Function() rootDirectoryResolver;

  PersistenceService({Future<Directory> Function()? rootDirectoryResolver})
      : rootDirectoryResolver = rootDirectoryResolver ?? getApplicationSupportDirectory;

  Future<Directory> _dataDir() async {
    final supportDir = await rootDirectoryResolver();
    final dir = Directory('${supportDir.path}/wtracks_data');
    if (!await dir.exists()) await dir.create(recursive: true);
    return dir;
  }

  Future<Directory> _tracksDir() async {
    final dir = Directory('${(await _dataDir()).path}/tracks');
    if (!await dir.exists()) await dir.create(recursive: true);
    return dir;
  }

  Future<Directory> _setlistsDir() async {
    final dir = Directory('${(await _dataDir()).path}/setlists');
    if (!await dir.exists()) await dir.create(recursive: true);
    return dir;
  }

  Future<Directory> _audioDir(String trackId) async {
    final dir = Directory('${(await _dataDir()).path}/audio/$trackId');
    if (!await dir.exists()) await dir.create(recursive: true);
    return dir;
  }

  Future<Directory> _waveformsDir() async {
    final dir = Directory('${(await _dataDir()).path}/waveforms');
    if (!await dir.exists()) await dir.create(recursive: true);
    return dir;
  }

  // Serialize writes to the same destination, including rapid reorders.
  static final Map<String, Future<void>> _writes = {};

  Future<void> _writeJson(File file, Object value) async {
    final content = jsonEncode(value);
    final previous = _writes[file.path] ?? Future<void>.value();
    final operation = previous.then((_) async {
      final temporary = File('${file.path}.tmp');
      await temporary.writeAsString(content, flush: true);
      await temporary.rename(file.path);
    });
    final settled = operation.then<void>((_) {}, onError: (Object _, StackTrace _) {});
    _writes[file.path] = settled;
    try {
      await operation;
    } finally {
      if (identical(_writes[file.path], settled)) _writes.remove(file.path);
    }
  }

  // ---------------------------------------------------------------------
  // Tracks
  // ---------------------------------------------------------------------

  /// Move os arquivos de áudio de [track] (tipicamente ainda no cache
  /// temporário de import) para `audio/<track.id>/` e grava
  /// `tracks/<track.id>.json`. Retorna a [Track] com os [ChannelInfo]s já
  /// apontando pros novos paths -- é essa versão que deve substituir a
  /// track em uso no estado do app, não a original.
  ///
  /// Chamar de novo com a mesma track (ex: usuário aperta "Salvar" duas
  /// vezes) sobrescreve o JSON e não tenta mover arquivos que já estão no
  /// lugar certo.
  Future<Track> saveTrack(Track track) async {
    final audioDir = await _audioDir(track.id);
    final usedNames = <String>{};
    final updatedChannels = <ChannelInfo>[];

    for (var i = 0; i < track.channels.length; i++) {
      final channel = track.channels[i];
      final sourcePath = channel.filePath;

      // Já está no destino final -- nada a mover (idempotente: salvar duas
      // vezes não tenta mover um arquivo para cima dele mesmo).
      if (sourcePath.startsWith('${audioDir.path}/')) {
        final name = sourcePath.split('/').last;
        usedNames.add(name);
        updatedChannels.add(channel);
        continue;
      }

      var originalName = sourcePath.split('/').last;
      var destName = originalName;
      // Colisão de nome entre canais diferentes (ex: dois arquivos
      // "click.wav" vindos de import distintos) -- prefixa com o índice do
      // canal em vez de deixar um sobrescrever o outro silenciosamente.
      if (usedNames.contains(destName)) {
        destName = '${i}_$originalName';
      }
      usedNames.add(destName);

      final destPath = '${audioDir.path}/$destName';
      final sourceFile = File(sourcePath);
      if (!await sourceFile.exists()) {
        throw FileSystemException('Áudio do canal "${channel.label}" não encontrado', sourcePath);
      }
      try {
        await sourceFile.rename(destPath);
      } on FileSystemException {
        // rename() falha ao cruzar filesystems/partições -- comum em
        // Android entre o diretório de cache e o de app storage. Fallback
        // pra copy + delete, conferindo o tamanho antes de apagar a origem.
        final expected = await sourceFile.length();
        final copy = await sourceFile.copy(destPath);
        if (await copy.length() != expected) {
          await copy.delete();
          throw FileSystemException('Cópia incompleta do áudio do canal "${channel.label}"', destPath);
        }
        await sourceFile.delete();
      }

      updatedChannels.add(channel.copyWith(filePath: destPath));
    }

    final updatedTrack = track.copyWith(channels: updatedChannels);

    // TODO: se o app for morto entre o move dos arquivos de áudio (acima)
    // e a escrita do JSON (abaixo), fica uma inconsistência -- áudio já
    // migrado mas track.json desatualizado/ausente. Cenário raro, aceitável
    // por ora; não há transação/rollback implementado.
    final jsonFile = File('${(await _tracksDir()).path}/${track.id}.json');
    await _writeJson(jsonFile, updatedTrack.toJson());

    return updatedTrack;
  }

  /// Arquivos que falharam na última leitura em lote (caminho → erro), para o diagnóstico.
  final Map<String, String> lastLoadFailures = {};

  Future<List<Track>> loadAllTracks() async {
    final dir = await _tracksDir();
    final entries = await dir.list().toList();
    final tracks = <Track>[];
    lastLoadFailures.removeWhere((path, _) => path.contains('/tracks/'));

    for (final entry in entries) {
      if (entry is! File || !entry.path.endsWith('.json')) continue;
      try {
        final content = await entry.readAsString();
        final json = jsonDecode(content) as Map<String, dynamic>;
        tracks.add(Track.fromJson(json));
      } catch (e) {
        // Um arquivo corrompido não deve derrubar o carregamento das
        // demais tracks -- loga e pula.
        debugPrint('PersistenceService: falha ao carregar ${entry.path}: $e');
        lastLoadFailures[entry.path] = '$e';
      }
    }

    return tracks;
  }

  Future<Track?> loadTrack(String id) async {
    final file = File('${(await _tracksDir()).path}/$id.json');
    if (!await file.exists()) return null;
    try {
      final content = await file.readAsString();
      return Track.fromJson(jsonDecode(content) as Map<String, dynamic>);
    } catch (e) {
      debugPrint('PersistenceService: falha ao carregar track $id: $e');
      return null;
    }
  }

  /// Remove `tracks/<id>.json` e `audio/<id>/` recursivamente.
  ///
  Future<void> deleteTrack(String id) async {
    final jsonFile = File('${(await _tracksDir()).path}/$id.json');
    if (await jsonFile.exists()) await jsonFile.delete();

    final audioDir = Directory('${(await _dataDir()).path}/audio/$id');
    if (await audioDir.exists()) await audioDir.delete(recursive: true);

    await deleteWaveformPeaks(id);
  }

  // ---------------------------------------------------------------------
  // Setlists
  // ---------------------------------------------------------------------

  Future<void> saveSetlist(Setlist setlist) async {
    final jsonFile = File('${(await _setlistsDir()).path}/${setlist.id}.json');
    await _writeJson(jsonFile, setlist.toJson());
  }

  Future<List<Setlist>> loadAllSetlists() async {
    final dir = await _setlistsDir();
    final entries = await dir.list().toList();
    final setlists = <Setlist>[];
    lastLoadFailures.removeWhere((path, _) => path.contains('/setlists/'));

    for (final entry in entries) {
      if (entry is! File || !entry.path.endsWith('.json')) continue;
      try {
        final setlist = await _resolveSetlistFile(entry);
        if (setlist != null) setlists.add(setlist);
      } catch (e) {
        debugPrint('PersistenceService: falha ao carregar ${entry.path}: $e');
        lastLoadFailures[entry.path] = '$e';
      }
    }

    return setlists;
  }

  Future<Setlist?> loadSetlist(String id) async {
    final file = File('${(await _setlistsDir()).path}/$id.json');
    if (!await file.exists()) return null;
    try {
      return await _resolveSetlistFile(file);
    } catch (e) {
      debugPrint('PersistenceService: falha ao carregar setlist $id: $e');
      return null;
    }
  }

  Future<void> deleteSetlist(String id) async {
    final file = File('${(await _setlistsDir()).path}/$id.json');
    if (await file.exists()) await file.delete();
  }

  /// Lê o JSON de uma setlist e resolve cada `trackId` pra uma [Track]
  /// completa via [loadTrack]. Tracks que não forem mais encontradas em
  /// disco (ex: deletadas) são simplesmente omitidas da lista resultante.
  Future<Setlist?> _resolveSetlistFile(File file) async {
    final content = await file.readAsString();
    final json = jsonDecode(content) as Map<String, dynamic>;

    final trackIds = Setlist.trackIdsFromJson(json);
    final tracks = <Track>[];
    for (final id in trackIds) {
      final track = await loadTrack(id);
      if (track != null) tracks.add(track);
    }

    return Setlist(
      id: Setlist.idFromJson(json),
      name: Setlist.nameFromJson(json),
      tracks: tracks,
    );
  }

  // ---------------------------------------------------------------------
  // Waveform (cache dos picos de amplitude usados na timeline)
  // ---------------------------------------------------------------------

  Future<void> saveWaveformPeaks(String trackId, List<double> peaks) async {
    final jsonFile = File('${(await _waveformsDir()).path}/$trackId.json');
    await _writeJson(jsonFile, {'peaks': peaks});
  }

  /// Retorna `null` se o arquivo não existir (track nunca teve cache
  /// gerado) ou se o JSON estiver corrompido -- nunca lança exceção pra
  /// quem chamou, mesmo padrão dos outros loaders.
  Future<List<double>?> loadWaveformPeaks(String trackId) async {
    final file = File('${(await _waveformsDir()).path}/$trackId.json');
    if (!await file.exists()) return null;
    try {
      final content = await file.readAsString();
      final json = jsonDecode(content) as Map<String, dynamic>;
      return (json['peaks'] as List).map((p) => (p as num).toDouble()).toList();
    } catch (e) {
      debugPrint('PersistenceService: falha ao carregar waveform $trackId: $e');
      return null;
    }
  }

  Future<void> deleteWaveformPeaks(String trackId) async {
    final file = File('${(await _waveformsDir()).path}/$trackId.json');
    if (await file.exists()) await file.delete();
  }
}
