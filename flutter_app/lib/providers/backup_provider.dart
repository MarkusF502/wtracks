import 'dart:async';
import 'dart:io';

import 'package:flutter/foundation.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:path_provider/path_provider.dart';

import '../services/backup_files.dart';
import '../services/backup_service.dart';
import '../services/diagnostics_log.dart';
import 'engine_provider.dart';
import 'setlist_provider.dart';
import 'transition_provider.dart';

final backupFilesProvider = Provider<BackupFiles>((ref) => PlatformBackupFiles());
final backupServiceProvider = Provider<BackupService>((ref) => BackupService(ref.read(persistenceServiceProvider)));

/// Pasta de trabalho dos backups (o zip é montado e conferido aqui antes de ir para o destino escolhido).
final backupWorkDirectoryProvider = Provider<Future<Directory> Function()>((ref) => getTemporaryDirectory);

@immutable
class BackupState {
  final bool busy;
  final double progress;
  final String? message;
  final bool error;

  /// Backup escolhido para restaurar, já conferido, esperando a confirmação do usuário.
  final File? pendingFile;
  final BackupSummary? pendingSummary;
  const BackupState({this.busy = false, this.progress = 0, this.message, this.error = false, this.pendingFile, this.pendingSummary});
}

class BackupNotifier extends Notifier<BackupState> {
  @override
  BackupState build() => const BackupState();

  void _fail(String what, Object e) {
    ref.read(diagnosticsProvider.notifier).error('$what: $e');
    state = BackupState(message: '$what: $e', error: true);
  }

  static String _stamp(DateTime t) {
    String two(int n) => n.toString().padLeft(2, '0');
    return '${t.year}-${two(t.month)}-${two(t.day)}-${two(t.hour)}${two(t.minute)}';
  }

  static String describe(BackupSummary s) {
    final mb = s.bytes / (1024 * 1024);
    return '${s.tracks} música${s.tracks == 1 ? '' : 's'}, ${s.setlists} setlist${s.setlists == 1 ? '' : 's'}, ${mb.toStringAsFixed(1)} MB';
  }

  /// Cria o backup completo, confere e entrega ao destino escolhido.
  Future<void> create() async {
    if (state.busy) return;
    state = const BackupState(busy: true, message: 'Preparando o backup…');
    File? work;
    try {
      // Nada pode estar sendo gravado enquanto os arquivos são lidos.
      await ref.read(trackLibraryProvider.notifier).autosaveIdle;
      await ref.read(currentTrackProvider.notifier).idle;
      final dir = await ref.read(backupWorkDirectoryProvider)();
      final name = 'wtracks-backup-${_stamp(DateTime.now())}.zip';
      work = File('${dir.path}/$name');
      final summary = await ref.read(backupServiceProvider).create(work, onProgress: (p) {
        state = BackupState(busy: true, progress: p, message: p < 0.7 ? 'Copiando e calculando os hashes…' : 'Conferindo o backup…');
      });
      state = const BackupState(busy: true, progress: 1, message: 'Escolha onde guardar o backup…');
      final saved = await ref.read(backupFilesProvider).saveBackup(work, name);
      state = saved
          ? BackupState(message: 'Backup criado e conferido: ${describe(summary)}.')
          : const BackupState(message: 'Backup cancelado: nada foi gravado.');
    } catch (e) {
      _fail('Falha ao criar o backup', e);
    } finally {
      if (work != null) {
        try {
          if (await work.exists()) await work.delete();
        } on FileSystemException {
          // fica no cache do app
        }
      }
    }
  }

  /// Escolhe um backup e o confere; a restauração só acontece em [confirmRestore].
  Future<void> choose() async {
    if (state.busy) return;
    state = const BackupState(busy: true, message: 'Escolha o arquivo de backup…');
    try {
      final file = await ref.read(backupFilesProvider).pickBackup();
      if (file == null) {
        state = const BackupState();
        return;
      }
      state = const BackupState(busy: true, message: 'Conferindo o backup…');
      final summary = await ref.read(backupServiceProvider).verify(file, onProgress: (p) {
        state = BackupState(busy: true, progress: p, message: 'Conferindo o backup…');
      });
      state = BackupState(pendingFile: file, pendingSummary: summary);
    } catch (e) {
      _fail('Esse backup não pode ser restaurado', e);
    }
  }

  void cancelPending() {
    final file = state.pendingFile;
    state = const BackupState();
    if (file != null) unawaited(_quietDelete(file));
  }

  Future<void> _quietDelete(File file) async {
    try {
      if (await file.exists()) await file.delete();
    } on FileSystemException {
      // cache
    }
  }

  /// Substitui a biblioteca pelo backup escolhido. A biblioteca anterior fica numa pasta ao lado.
  Future<void> confirmRestore() async {
    final file = state.pendingFile;
    if (file == null || state.busy) return;
    state = const BackupState(busy: true, message: 'Restaurando…');
    try {
      // Solta tudo o que usa os arquivos atuais antes de trocá-los.
      ref.read(transitionProvider.notifier).cancel();
      await ref.read(transportProvider.notifier).stop();
      await ref.read(currentTrackProvider.notifier).unload();
      await ref.read(trackLibraryProvider.notifier).autosaveIdle;
      final previous = await ref.read(backupServiceProvider).restore(file, onProgress: (p) {
        state = BackupState(busy: true, progress: p, message: 'Restaurando…');
      });
      await ref.read(trackLibraryProvider.notifier).refresh();
      await ref.read(setlistLibraryProvider.notifier).refresh();
      ref.read(setlistSessionProvider.notifier).end();
      unawaited(_quietDelete(file));
      state = BackupState(
        message: 'Backup restaurado. Feche e abra o WTracks para aplicar as preferências.'
            '${previous == null ? '' : '\nA biblioteca anterior foi mantida em: ${previous.path}'}',
      );
    } catch (e) {
      _fail('Falha ao restaurar o backup (a biblioteca atual não foi alterada)', e);
    }
  }
}

final backupProvider = NotifierProvider<BackupNotifier, BackupState>(BackupNotifier.new);
