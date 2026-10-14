import 'dart:convert';
import 'dart:io';
import 'dart:typed_data';

import 'package:archive/archive_io.dart';
import 'package:crypto/crypto.dart';

import '../models/track.dart';
import 'persistence_service.dart';

/// Uma entrada do manifesto do backup.
class BackupEntry {
  final String path;
  final int size;
  final String sha256;
  const BackupEntry(this.path, this.size, this.sha256);
  Map<String, dynamic> toJson() => {'path': path, 'size': size, 'sha256': sha256};
  factory BackupEntry.fromJson(Map<String, dynamic> json) =>
      BackupEntry(json['path'] as String, (json['size'] as num).toInt(), json['sha256'] as String);
}

/// O que um backup contém (lido do manifesto, sem restaurar nada).
class BackupSummary {
  final DateTime createdAt;
  final int tracks, setlists, audioFiles, bytes;
  final List<BackupEntry> entries;
  const BackupSummary(this.createdAt, this.tracks, this.setlists, this.audioFiles, this.bytes, this.entries);
}

class BackupException implements Exception {
  final String message;
  const BackupException(this.message);
  @override
  String toString() => message;
}

/// Backup completo e restauração (Fase B do plano de consolidação; pré-requisito da troca de chave de assinatura e do atualizador).
///
/// O backup é um .zip com `manifest.json` (formato, versão, data, e caminho + tamanho + SHA-256 de cada arquivo) mais a pasta de dados
/// do app: músicas, setlists, **áudios** e preferências. Os JSON guardam os caminhos dos áudios **relativos** à pasta de dados, então o
/// backup abre em qualquer instalação. As waveforms (regeneráveis) e os arquivos temporários não entram. Depois de escrito, o zip é
/// reaberto e **todos** os hashes são conferidos antes de ele ser publicado: um backup que não passa nessa conferência nunca aparece.
///
/// A restauração confere o zip inteiro, extrai para uma pasta de preparo, valida cada música, e só então troca a pasta de dados. A pasta
/// anterior é mantida ao lado (`wtracks_data.antes-da-restauracao-<data>`) até o usuário apagá-la.
class BackupService {
  static const formatName = 'wtracks-backup';
  static const formatVersion = 1;
  static const _manifestName = 'manifest.json';

  final PersistenceService persistence;
  BackupService(this.persistence);

  // ---- criar ----

  Future<BackupSummary> create(File destination, {void Function(double progress)? onProgress}) async {
    final dataDir = await persistence.dataDirectory();
    final prefix = '${dataDir.path}/';
    final sources = <String, File>{}; // caminho no zip -> arquivo real
    await for (final entity in dataDir.list(recursive: true, followLinks: false)) {
      if (entity is! File) continue;
      final relative = entity.path.substring(prefix.length);
      if (_skipped(relative)) continue;
      sources[relative] = entity;
    }
    final names = sources.keys.toList()..sort();

    // Os JSON entram com caminhos relativos; calcula conteúdo e hash de tudo antes de escrever o zip.
    final entries = <BackupEntry>[];
    final generated = <String, Uint8List>{};
    var done = 0;
    for (final name in names) {
      final file = sources[name]!;
      if (_isPortableJson(name)) {
        final bytes = Uint8List.fromList(utf8.encode(jsonEncode(_makePortable(jsonDecode(await file.readAsString()), prefix, name))));
        generated[name] = bytes;
        entries.add(BackupEntry(name, bytes.length, sha256.convert(bytes).toString()));
      } else {
        entries.add(BackupEntry(name, await file.length(), await _hashFile(file)));
      }
      onProgress?.call(0.35 * ++done / names.length);
    }
    final summary = _summarize(DateTime.now().toUtc(), entries);
    final manifest = utf8.encode(jsonEncode({
      'format': formatName,
      'version': formatVersion,
      'createdAt': summary.createdAt.toIso8601String(),
      'trackSchemaVersion': Track.currentSchemaVersion,
      'counts': {'tracks': summary.tracks, 'setlists': summary.setlists, 'audioFiles': summary.audioFiles},
      'files': [for (final e in entries) e.toJson()],
    }));

    final partial = File('${destination.path}.part');
    if (await partial.exists()) await partial.delete();
    await destination.parent.create(recursive: true);
    final encoder = ZipFileEncoder();
    encoder.create(partial.path);
    try {
      encoder.addArchiveFile(ArchiveFile(_manifestName, manifest.length, manifest));
      for (var i = 0; i < names.length; i++) {
        final name = names[i];
        final bytes = generated[name];
        if (bytes != null) {
          encoder.addArchiveFile(ArchiveFile(name, bytes.length, bytes));
        } else {
          // Áudio quase não comprime: guarda sem comprimir (rápido e com pouca memória).
          await encoder.addFile(sources[name]!, name, ZipFileEncoder.STORE);
        }
        onProgress?.call(0.35 + 0.35 * (i + 1) / names.length);
      }
    } finally {
      await encoder.close();
    }

    try {
      await verify(partial, onProgress: (p) => onProgress?.call(0.7 + 0.3 * p));
    } catch (_) {
      if (await partial.exists()) await partial.delete();
      rethrow;
    }
    if (await destination.exists()) await destination.delete();
    await partial.rename(destination.path);
    return summary;
  }

  bool _skipped(String relative) {
    if (relative.startsWith('waveforms/')) return true;
    return relative.endsWith('.tmp') || relative.endsWith('.part') || relative.endsWith('.bak') || relative.endsWith('.corrupt');
  }

  bool _isPortableJson(String name) =>
      (name.startsWith('tracks/') || name.startsWith('setlists/')) && name.endsWith('.json') || name == 'settings.json';

  /// Troca o prefixo da pasta de dados por nada nos `filePath` (músicas e setlists, que embutem músicas) e tira do `settings.json` as
  /// pastas personalizadas (caminhos que só existem neste aparelho).
  Object? _makePortable(Object? json, String prefix, String name) {
    if (name == 'settings.json' && json is Map) {
      return {...json}..remove('customClicksDirectory')..remove('customGuidesDirectory');
    }
    Object? walk(Object? node) {
      if (node is Map) {
        return <String, dynamic>{
          for (final entry in node.entries)
            entry.key as String: entry.key == 'filePath' && entry.value is String && (entry.value as String).startsWith(prefix)
                ? (entry.value as String).substring(prefix.length)
                : walk(entry.value),
        };
      }
      if (node is List) return [for (final item in node) walk(item)];
      return node;
    }
    return walk(json);
  }

  BackupSummary _summarize(DateTime createdAt, List<BackupEntry> entries) => BackupSummary(
        createdAt,
        entries.where((e) => e.path.startsWith('tracks/') && e.path.endsWith('.json')).length,
        entries.where((e) => e.path.startsWith('setlists/') && e.path.endsWith('.json')).length,
        entries.where((e) => e.path.startsWith('audio/')).length,
        entries.fold(0, (sum, e) => sum + e.size),
        entries,
      );

  Future<String> _hashFile(File file) async => (await sha256.bind(file.openRead()).first).toString();

  // ---- conferir ----

  /// Abre o zip, lê o manifesto e confere o tamanho e o SHA-256 de **todos** os arquivos (e que não sobra nem falta nenhum).
  /// Lança [BackupException] no primeiro problema.
  Future<BackupSummary> verify(File zip, {void Function(double progress)? onProgress}) async {
    if (!await zip.exists()) throw BackupException('Backup não encontrado: ${zip.path}');
    final input = InputFileStream(zip.path);
    try {
      final archive = ZipDecoder().decodeBuffer(input);
      final manifest = _readManifest(archive);
      final byName = {for (final f in archive.files) if (f.isFile) f.name: f};
      final expected = {for (final e in manifest.entries) e.path};
      final extra = byName.keys.where((n) => n != _manifestName && !expected.contains(n));
      if (extra.isNotEmpty) throw BackupException('O backup tem arquivos fora do manifesto: ${extra.first}');
      var done = 0;
      for (final entry in manifest.entries) {
        final file = byName[entry.path];
        if (file == null) throw BackupException('Falta no backup: ${entry.path}');
        final sink = _HashingOutput();
        file.writeContent(sink);
        if (sink.length != entry.size) throw BackupException('Tamanho diferente em ${entry.path} (${sink.length} em vez de ${entry.size})');
        if (sink.digest() != entry.sha256) throw BackupException('Conteúdo diferente do manifesto em ${entry.path}');
        onProgress?.call(++done / manifest.entries.length);
      }
      return manifest;
    } on BackupException {
      rethrow;
    } catch (e) {
      throw BackupException('O arquivo não é um backup válido do WTracks ($e)');
    } finally {
      await input.close();
    }
  }

  BackupSummary _readManifest(Archive archive) {
    final file = archive.files.where((f) => f.isFile && f.name == _manifestName).firstOrNull;
    if (file == null) throw const BackupException('O arquivo não tem manifesto: não é um backup do WTracks.');
    final json = jsonDecode(utf8.decode(file.content as List<int>)) as Map<String, dynamic>;
    if (json['format'] != formatName) throw const BackupException('O arquivo não é um backup do WTracks.');
    final version = (json['version'] as num?)?.toInt() ?? 0;
    if (version > formatVersion) {
      throw BackupException('Backup de uma versão mais nova do WTracks (formato $version); atualize o app para restaurá-lo.');
    }
    final schema = (json['trackSchemaVersion'] as num?)?.toInt() ?? 1;
    if (schema > Track.currentSchemaVersion) {
      throw BackupException('As músicas do backup são de um formato mais novo ($schema); atualize o app para restaurá-lo.');
    }
    final entries = [for (final e in json['files'] as List) BackupEntry.fromJson(e as Map<String, dynamic>)];
    for (final e in entries) {
      if (e.path.startsWith('/') || e.path.split('/').contains('..') || e.path.contains('\\')) {
        throw BackupException('Caminho inválido no backup: ${e.path}');
      }
    }
    return _summarize(DateTime.tryParse(json['createdAt'] as String? ?? '') ?? DateTime.fromMillisecondsSinceEpoch(0, isUtc: true), entries);
  }

  // ---- restaurar ----

  /// Substitui a biblioteca pelo conteúdo do backup. Nada muda se alguma conferência falhar. Devolve a pasta com os dados anteriores.
  Future<Directory?> restore(File zip, {void Function(double progress)? onProgress}) async {
    final summary = await verify(zip, onProgress: (p) => onProgress?.call(0.4 * p));
    final dataDir = await persistence.dataDirectory();
    final parent = dataDir.parent;
    final staging = Directory('${parent.path}/wtracks_data.restaurando');
    if (await staging.exists()) await staging.delete(recursive: true);
    await staging.create(recursive: true);
    final input = InputFileStream(zip.path);
    try {
      final archive = ZipDecoder().decodeBuffer(input);
      final byName = {for (final f in archive.files) if (f.isFile) f.name: f};
      var done = 0;
      for (final entry in summary.entries) {
        final target = File('${staging.path}/${entry.path}');
        await target.parent.create(recursive: true);
        final output = OutputFileStream(target.path);
        try {
          byName[entry.path]!.writeContent(output);
        } finally {
          await output.close();
        }
        onProgress?.call(0.4 + 0.4 * ++done / summary.entries.length);
      }
    } catch (e) {
      await staging.delete(recursive: true);
      throw BackupException('Falha ao extrair o backup: $e');
    } finally {
      await input.close();
    }

    try {
      await _finishStaging(staging, '${dataDir.path}/');
    } catch (_) {
      await staging.delete(recursive: true);
      rethrow;
    }

    // Troca: a pasta atual vai para o lado e a restaurada ocupa o lugar. Se a segunda troca falhar, volta a anterior.
    final stamp = DateTime.now().toUtc().toIso8601String().replaceAll(':', '-').split('.').first;
    final previous = Directory('${parent.path}/wtracks_data.antes-da-restauracao-$stamp');
    if (await dataDir.exists() && await dataDir.list().isEmpty) await dataDir.delete(); // instalação limpa: nada a guardar
    final hadPrevious = await dataDir.exists();
    if (hadPrevious) await dataDir.rename(previous.path);
    try {
      await staging.rename(dataDir.path);
    } catch (e) {
      if (hadPrevious) await previous.rename(dataDir.path);
      await staging.delete(recursive: true);
      throw BackupException('Não foi possível ativar o backup restaurado: $e');
    }
    onProgress?.call(1);
    return hadPrevious ? previous : null;
  }

  /// Na pasta de preparo: volta os caminhos relativos a absolutos (da instalação de destino) e valida cada música e setlist.
  Future<void> _finishStaging(Directory staging, String targetPrefix) async {
    for (final dirName in const ['tracks', 'setlists']) {
      final dir = Directory('${staging.path}/$dirName');
      if (!await dir.exists()) continue;
      await for (final entity in dir.list()) {
        if (entity is! File || !entity.path.endsWith('.json')) continue;
        final json = jsonDecode(await entity.readAsString());
        final absolute = _makeAbsolute(json, targetPrefix);
        final tracks = <Map<String, dynamic>>[];
        if (dirName == 'tracks') {
          tracks.add(absolute as Map<String, dynamic>);
        } else if (absolute is Map && absolute['tracks'] is List) {
          tracks.addAll((absolute['tracks'] as List).cast<Map<String, dynamic>>());
        }
        for (final track in tracks) {
          try {
            Track.fromJson(track);
          } catch (e) {
            throw BackupException('Música inválida no backup (${entity.path.split('/').last}): $e');
          }
        }
        if (dirName == 'tracks') {
          for (final channel in (absolute as Map)['channels'] as List) {
            final path = (channel as Map)['filePath'] as String;
            final inStaging = path.replaceFirst(targetPrefix, '${staging.path}/');
            if (!await File(inStaging).exists()) throw BackupException('Falta o áudio de uma música: ${path.substring(targetPrefix.length)}');
          }
        }
        await entity.writeAsString(jsonEncode(absolute), flush: true);
      }
    }
  }

  Object? _makeAbsolute(Object? node, String targetPrefix) {
    if (node is Map) {
      return <String, dynamic>{
        for (final entry in node.entries)
          entry.key as String: entry.key == 'filePath' && entry.value is String && !(entry.value as String).startsWith('/')
              ? '$targetPrefix${entry.value}'
              : _makeAbsolute(entry.value, targetPrefix),
      };
    }
    if (node is List) return [for (final item in node) _makeAbsolute(item, targetPrefix)];
    return node;
  }
}

/// Destino de [ArchiveFile.writeContent] que só conta e calcula o SHA-256 (nada fica em memória).
class _HashingOutput extends OutputStreamBase {
  final _digest = _DigestSink();
  late final ByteConversionSink _sink = sha256.startChunkedConversion(_digest);
  @override
  int length = 0;
  String digest() {
    _sink.close();
    return _digest.value.toString();
  }

  @override
  void flush() {}
  @override
  void writeByte(int value) => writeBytes([value & 0xff]);
  @override
  void writeBytes(List<int> bytes, [int? len]) {
    final count = len ?? bytes.length;
    _sink.add(count == bytes.length ? bytes : bytes.sublist(0, count));
    length += count;
  }

  @override
  void writeInputStream(InputStreamBase stream) {
    while (!stream.isEOS) {
      final chunk = stream.readBytes(64 * 1024).toUint8List();
      writeBytes(chunk);
    }
  }

  @override
  void writeUint16(int value) => writeBytes([value & 0xff, (value >> 8) & 0xff]);
  @override
  void writeUint32(int value) => writeBytes([for (var i = 0; i < 4; i++) (value >> (8 * i)) & 0xff]);
  @override
  void writeUint64(int value) => writeBytes([for (var i = 0; i < 8; i++) (value >> (8 * i)) & 0xff]);
}

class _DigestSink implements Sink<Digest> {
  late Digest value;
  @override
  void add(Digest data) => value = data;
  @override
  void close() {}
}
