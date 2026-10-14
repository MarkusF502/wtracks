import 'dart:io';

import 'package:file_selector/file_selector.dart';
import 'package:flutter/services.dart' show MethodChannel, PlatformException;

/// De onde vem e para onde vai o arquivo de backup: o seletor do sistema (no Android, SAF, sem pedir permissão de armazenamento) ou o
/// diálogo de arquivos do desktop.
abstract class BackupFiles {
  /// Grava [source] no lugar que o usuário escolher. false se ele cancelou.
  Future<bool> saveBackup(File source, String suggestedName);

  /// Deixa o usuário escolher um backup e devolve uma cópia local dele; null se cancelou.
  Future<File?> pickBackup();
}

class PlatformBackupFiles implements BackupFiles {
  static const _channel = MethodChannel('wtracks/backup');

  @override
  Future<bool> saveBackup(File source, String suggestedName) async {
    if (Platform.isAndroid) {
      try {
        final saved = await _channel.invokeMethod<String>('saveBackup', {'source': source.path, 'name': suggestedName});
        return saved != null;
      } on PlatformException catch (e) {
        throw FileSystemException('Não foi possível gravar o backup: ${e.message}');
      }
    }
    final location = await getSaveLocation(
      suggestedName: suggestedName,
      acceptedTypeGroups: const [XTypeGroup(label: 'Backup do WTracks', extensions: ['zip'])],
    );
    if (location == null) return false;
    await source.copy(location.path);
    return true;
  }

  @override
  Future<File?> pickBackup() async {
    if (Platform.isAndroid) {
      try {
        final path = await _channel.invokeMethod<String>('pickBackup');
        return path == null ? null : File(path);
      } on PlatformException catch (e) {
        throw FileSystemException('Não foi possível abrir o backup: ${e.message}');
      }
    }
    final file = await openFile(acceptedTypeGroups: const [XTypeGroup(label: 'Backup do WTracks', extensions: ['zip'])]);
    return file == null ? null : File(file.path);
  }
}
