import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:uuid/uuid.dart';

import '../models/track.dart';
import 'engine_provider.dart';
import '../services/diagnostics_log.dart';

const _uuid = Uuid();

/// Lista de setlists salvos, carregada do disco via [PersistenceService].
/// Alimenta a SetlistsScreen.
class SetlistLibraryNotifier extends Notifier<List<Setlist>> {
  @override
  List<Setlist> build() {
    _load();
    return [];
  }

  Future<void> _load() async {
    final persistence = ref.read(persistenceServiceProvider);
    try {
      state = await persistence.loadAllSetlists();
    } catch (e) {
      _report('Falha ao ler as setlists: $e');
    }
    for (final entry in persistence.lastLoadFailures.entries) {
      if (entry.key.contains('/setlists/')) _report('Setlist ilegível ignorada: ${entry.key} (${entry.value})');
    }
  }

  void _report(String message) {
    ref.read(diagnosticsProvider.notifier).error(message);
    ref.read(persistenceAlertProvider.notifier).state = message;
  }

  Future<void> refresh() => _load();

  Future<Setlist> createSetlist(String name) async {
    final setlist = Setlist(id: _uuid.v4(), name: name, tracks: const []);
    await ref.read(persistenceServiceProvider).saveSetlist(setlist);
    state = [...state, setlist];
    return setlist;
  }

  Future<void> deleteSetlist(String id) async {
    await ref.read(persistenceServiceProvider).deleteSetlist(id);
    state = state.where((s) => s.id != id).toList();
  }

  Future<void> renameSetlist(String id, String newName) async {
    final index = state.indexWhere((s) => s.id == id);
    if (index < 0) return;

    final renamed = state[index].copyWith(name: newName);
    await ref.read(persistenceServiceProvider).saveSetlist(renamed);

    final updated = [...state];
    updated[index] = renamed;
    state = updated;

    final editorNotifier = ref.read(setlistEditorProvider.notifier);
    if (ref.read(setlistEditorProvider)?.id == id) {
      editorNotifier.setLoadedSetlist(renamed);
    }
  }

  /// Substitui a entrada de [setlist] na lista sem reler tudo do disco --
  /// usado pelo [SetlistEditorNotifier] pra sincronizar depois de salvar.
  void syncSetlist(Setlist setlist) {
    final index = state.indexWhere((s) => s.id == setlist.id);
    if (index >= 0) {
      final updated = [...state];
      updated[index] = setlist;
      state = updated;
    } else {
      state = [...state, setlist];
    }
  }
}

final setlistLibraryProvider =
    NotifierProvider<SetlistLibraryNotifier, List<Setlist>>(SetlistLibraryNotifier.new);

/// Setlist atualmente aberto no editor (ou null se nenhum) -- carregado sob
/// demanda via [open] ao entrar na SetlistEditorScreen, seguindo o mesmo
/// espírito de [CurrentTrackNotifier].
class SetlistEditorNotifier extends Notifier<Setlist?> {
  @override
  Setlist? build() => null;

  Future<void> open(String setlistId) async {
    final setlist = await ref.read(persistenceServiceProvider).loadSetlist(setlistId);
    state = setlist;
  }

  void setLoadedSetlist(Setlist setlist) {
    state = setlist;
  }

  Future<void> _persist(Setlist updated) async {
    state = updated;
    try {
      await ref.read(persistenceServiceProvider).saveSetlist(updated);
    } catch (e) {
      final message = 'Falha ao salvar a setlist "${updated.name}": $e';
      ref.read(diagnosticsProvider.notifier).error(message);
      ref.read(persistenceAlertProvider.notifier).state = message;
      return;
    }
    ref.read(setlistLibraryProvider.notifier).syncSetlist(updated);
  }

  Future<void> addTracks(List<Track> tracks) async {
    var current = state;
    if (current == null) return;
    for (final track in tracks) {
      current = current!.withTrackAdded(track);
    }
    await _persist(current!);
  }

  Future<void> removeTrack(String trackId) async {
    final current = state;
    if (current == null) return;
    await _persist(current.withTrackRemoved(trackId));
  }

  /// Reordena e persiste imediatamente -- diferente de Track (arquivos de
  /// áudio pesados, save explícito), aqui é só uma lista de ids, custo de
  /// escrita trivial, e salvar na hora evita perder a ordem se o usuário
  /// sair da tela sem lembrar de salvar. Sempre parte do `state` atual (que
  /// já reflete todas as reordenações aplicadas até aqui), não de um
  /// snapshot capturado antes do await -- importante se o usuário arrastar
  /// várias vezes em sequência antes da primeira escrita terminar.
  Future<void> reorder(int oldIndex, int newIndex) async {
    final current = state;
    if (current == null) return;
    await _persist(current.withTracksReordered(oldIndex, newIndex));
  }

  Future<void> rename(String newName) async {
    final current = state;
    if (current == null) return;
    await _persist(current.copyWith(name: newName));
  }
}

final setlistEditorProvider =
    NotifierProvider<SetlistEditorNotifier, Setlist?>(SetlistEditorNotifier.new);
