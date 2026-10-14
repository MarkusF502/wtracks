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
      // A versão anterior fica como .bak: se o arquivo novo um dia estiver ilegível, a leitura recupera a anterior.
      if (await file.exists()) await file.copy('${file.path}.bak');
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
    final created = <File>[]; // cópias feitas por este salvamento (desfeitas se ele não confirmar)
    final sources = <File>[]; // origens a apagar depois da confirmação

    for (final channel in track.channels) {  // nomes já ocupados por canais que ficam onde estão
      if (channel.filePath.startsWith('${audioDir.path}/')) usedNames.add(channel.filePath.split('/').last);
    }
    final reserved = {...usedNames};
    usedNames.clear();

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
      if (usedNames.contains(destName) || reserved.contains(destName)) {
        destName = '${i}_$originalName';
      }
      usedNames.add(destName);

      final destPath = '${audioDir.path}/$destName';
      final sourceFile = File(sourcePath);
      if (!await sourceFile.exists()) {
        await _discardCopies(created);
        throw FileSystemException('Áudio do canal "${channel.label}" não encontrado', sourcePath);
      }
      try {
        // Copia (não move) para um arquivo parcial, confere o tamanho e só então publica o nome final: se o processo morrer aqui,
        // a origem continua intacta e nenhum JSON aponta para um áudio incompleto.
        await _copyVerified(sourceFile, destPath, channel.label);
      } catch (_) {
        await _discardCopies(created);
        rethrow;
      }
      created.add(File(destPath));
      sources.add(sourceFile);
      updatedChannels.add(channel.copyWith(filePath: destPath));
    }

    final updatedTrack = track.copyWith(channels: updatedChannels);

    // Confirmação: o JSON é a última coisa a ser gravada. Antes dele a música ainda não existe para o app e as origens seguem
    // no lugar; depois dele os áudios já estão no destino e só sobra apagar as origens (cópias do cache de importação).
    final jsonFile = File('${(await _tracksDir()).path}/${track.id}.json');
    try {
      await _writeJson(jsonFile, updatedTrack.toJson());
    } catch (_) {
      await _discardCopies(created);
      rethrow;
    }
    for (final source in sources) {
      try {
        await source.delete();
      } on FileSystemException {
        // Sobra de cache: não afeta a música salva.
      }
    }
    return updatedTrack;
  }

  Future<void> _copyVerified(File source, String destination, String label) async {
    final partial = File('$destination.part');
    final expected = await source.length();
    final copy = await source.copy(partial.path);
    if (await copy.length() != expected) {
      await copy.delete();
      throw FileSystemException('Cópia incompleta do áudio do canal "$label"', destination);
    }
    await copy.rename(destination);
  }

  /// Desfaz as cópias feitas por um salvamento que não chegou a confirmar (nunca toca nas origens).
  Future<void> _discardCopies(List<File> copies) async {
    for (final copy in copies) {
      try {
        if (await copy.exists()) await copy.delete();
      } on FileSystemException {
        // fica como órfão; recoverInterruptedImports limpa os parciais
      }
    }
  }

  /// Apaga parciais (`*.part`) deixados por um processo que morreu no meio de uma cópia.
  Future<void> recoverInterruptedImports() async {
    final audio = Directory('${(await _dataDir()).path}/audio');
    if (!await audio.exists()) return;
    await for (final entry in audio.list(recursive: true)) {
      if (entry is File && entry.path.endsWith('.part')) {
        try {
          await entry.delete();
        } on FileSystemException {
          // tenta de novo na próxima abertura
        }
      }
    }
  }

  /// Arquivos que falharam na última leitura em lote (caminho → erro), para o diagnóstico.
  final Map<String, String> lastLoadFailures = {};

  Future<List<Track>> loadAllTracks() async {
    await recoverInterruptedImports();
    final dir = await _tracksDir();
    final entries = await dir.list().toList();
    final tracks = <Track>[];
    lastLoadFailures.removeWhere((path, _) => path.contains('/tracks/'));

    for (final entry in entries) {
      if (entry is! File || !entry.path.endsWith('.json')) continue;
      try {
        tracks.add(await _readTrack(entry));
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
      return await _readTrack(file);
    } catch (e) {
      debugPrint('PersistenceService: falha ao carregar track $id: $e');
      return null;
    }
  }

  /// Músicas lidas da cópia anterior (`.bak`) porque o arquivo principal estava ilegível (caminho → erro do principal).
  final Map<String, String> lastRecoveries = {};

  Future<Track> _readTrack(File file) async {
    try {
      return Track.fromJson(jsonDecode(await file.readAsString()) as Map<String, dynamic>);
    } on UnsupportedSchemaException {
      rethrow; // um arquivo de versão futura não se "recupera" com uma versão antiga dele
    } catch (e) {
      final backup = File('${file.path}.bak');
      if (!await backup.exists()) rethrow;
      final recovered = Track.fromJson(jsonDecode(await backup.readAsString()) as Map<String, dynamic>);
      lastRecoveries[file.path] = '$e';
      return recovered;
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
