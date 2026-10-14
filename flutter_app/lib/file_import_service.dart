import 'package:flutter/foundation.dart';
import 'dart:io';
import 'dart:async';

import 'package:flutter/services.dart' show MethodChannel, PlatformException;
import 'package:file_selector/file_selector.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'services/stem_detection.dart';
import 'package:path_provider/path_provider.dart';

/// O serviço de seleção de arquivos (substituível nos testes).
final fileImportServiceProvider = Provider<FileImportService>((ref) => FileImportService());

/// Porta pro Flutter o mesmo princípio que validamos no MainComponent.cpp:
/// no Android, arquivos escolhidos pelo seletor do sistema podem vir de
/// content:// URIs (Google Drive, outro app, etc.), então não dá pra confiar
/// que o "path" devolvido é um caminho de disco de verdade -- é preciso
/// materializar uma cópia local antes de entregar pro AudioEngine nativo.
class FileImportService {
  /// Abre o seletor de arquivos permitindo multi-seleção de .wav e retorna
  /// os caminhos LOCAIS (já copiados) prontos para passar a
  /// WTracksEngine.loadTrack. Retorna lista vazia se o usuário cancelar.
  Future<List<String>> pickAndImportChannelFiles() async {
    // On Android prefer the native method channel implementation which copies
    // content:// URIs to the app cache without sending large buffers via
    // platform channels. If it fails, fallback to the file_selector flow.
    if (Platform.isAndroid) {
      try {
        final channel = MethodChannel('wtracks/file_picker');
        // Rede de segurança: se o processo Android for recriado/morto enquanto
        // o seletor de arquivos está aberto (comportamento agressivo do MIUI),
        // o MethodChannel.Result nativo original se perde e este invokeMethod
        // ficaria pendurado para sempre sem o timeout. 90s é generoso o
        // suficiente para o usuário navegar no seletor e copiar arquivos
        // grandes, mas garante que a UI eventualmente reaja em vez de travar
        // com spinner infinito.
        final List<dynamic> paths = await channel
            .invokeMethod('pickAndImport')
            .timeout(
              const Duration(seconds: 90),
              onTimeout: () => throw PlatformException(
                code: 'TIMEOUT',
                message: 'Seletor de arquivo nativo não respondeu a tempo '
                    '(possível recriação de processo pelo sistema)',
              ),
            );
        return paths.cast<String>();
      } on PlatformException catch (e) {
        debugPrint('FileImportService: method channel failed: $e');
        // fall through to file_selector fallback
      }
    }
    final XTypeGroup typeGroup = XTypeGroup(
      label: 'Áudio (WAV, AIFF, FLAC)',
      extensions: importableAudioExtensions,
    );

    final List<XFile> files = await openFiles(
        acceptedTypeGroups: <XTypeGroup>[typeGroup]);

    if (files.isEmpty) return [];

    // Subpasta por importação: multitracks costumam repetir nomes
    // (Click.wav, Guia.wav...) e sobrescreveriam o áudio de uma música
    // importada antes e ainda não salva.
    final cacheDir = await Directory(
      '${(await _importCacheDirectory()).path}/${DateTime.now().microsecondsSinceEpoch}',
    ).create(recursive: true);
    final localPaths = <String>[];

    for (final (index, pickedFile) in files.indexed) {
      // Uma pasta por arquivo: dois arquivos com o mesmo nome (de pastas diferentes) não se sobrescrevem, e o nome do provedor
      // nunca vira caminho.
      final fileDir = await Directory('${cacheDir.path}/$index').create(recursive: true);
      final localFile = File('${fileDir.path}/${safeImportName(pickedFile.name)}');

      // Se o XFile já fornece um path (caso comum em Android), copie diretamente
      // do arquivo temporário que o plugin criou para o nosso diretório.
      if (pickedFile.path.isNotEmpty) {
        final source = File(pickedFile.path);
        // Debug log para investigar casos onde o arquivo some durante a cópia.
        debugPrint('FileImportService: copying from ${source.path} to ${localFile.path}');
        await source.copy(localFile.path);
      } else {
        // Fallback: usar saveTo que internamente lida com content:// URIs.
        debugPrint('FileImportService: saving ${pickedFile.name} to ${localFile.path} via saveTo');
        await pickedFile.saveTo(localFile.path);
      }

      if (!await localFile.exists() || await localFile.length() == 0) {
        throw StateError('Falha ao copiar o arquivo: ${pickedFile.name}');
      }

      debugPrint('FileImportService: imported ${localFile.path} size=${await localFile.length()}');
      localPaths.add(localFile.path);
    }

    return localPaths;
  }

  Future<Directory> _importCacheDirectory() async {
    final tempDir = await getTemporaryDirectory();
    final importDir = Directory('${tempDir.path}/wtracks_import');
    if (!await importDir.exists()) {
      await importDir.create(recursive: true);
    }
    return importDir;
  }
}

/// Nome de arquivo seguro a partir do que o seletor informa: só o último componente, sem controle nem pontos nas pontas.
String safeImportName(String raw) {
  final last = raw.split('/').last.split(r'\').last;
  final cleaned = String.fromCharCodes(last.runes.where((c) => c >= 0x20 && c != 0x7f)).trim().replaceAll(RegExp(r'^\.+|\.+$'), '');
  final limited = cleaned.length > 120 ? cleaned.substring(cleaned.length - 120) : cleaned;
  return limited.isEmpty ? 'file_${DateTime.now().microsecondsSinceEpoch}.wav' : limited;
}
