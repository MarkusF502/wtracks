import 'package:flutter/foundation.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

/// Entrada do registro de diagnóstico (Playback: "Diagnostic Information").
@immutable
class DiagnosticEntry {
  final DateTime time;
  final String message;
  final bool error;
  const DiagnosticEntry(this.time, this.message, {this.error = false});

  @override
  String toString() => '${time.toIso8601String()} ${error ? 'ERRO' : 'info'} $message';
}

/// Registro em memória das falhas de leitura/gravação e de eventos importantes. A tela de diagnóstico mostra e copia
/// o texto; [lastError] alimenta o aviso na tela de performance. Guarda as 300 entradas mais recentes.
class DiagnosticsLog extends Notifier<List<DiagnosticEntry>> {
  static const capacity = 300;

  @override
  List<DiagnosticEntry> build() => const [];

  void info(String message) => _add(DiagnosticEntry(DateTime.now(), message));

  void error(String message) {
    debugPrint('WTracks: $message');
    _add(DiagnosticEntry(DateTime.now(), message, error: true));
  }

  void _add(DiagnosticEntry entry) {
    final next = [...state, entry];
    state = next.length > capacity ? next.sublist(next.length - capacity) : next;
  }

  String export() => state.map((e) => e.toString()).join('\n');
}

final diagnosticsProvider = NotifierProvider<DiagnosticsLog, List<DiagnosticEntry>>(DiagnosticsLog.new);

/// Última falha a avisar na tela (null depois de mostrada).
final persistenceAlertProvider = StateProvider<String?>((ref) => null);
