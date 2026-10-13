import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/track.dart';
import '../models/engine_error.dart';
import '../providers/engine_provider.dart';
import '../screens/performance_screen.dart';

/// Carrega [track] no engine e navega para a [PerformanceScreen], igual ao
/// fluxo que já existia em `LibraryScreen._openTrack` -- extraído aqui pra
/// não duplicar o texto de erro e o fluxo de navegação entre LibraryScreen e
/// SetlistEditorScreen.
/// Aberta a partir de uma setlist ([setlist] e [index]), a música passa a fazer parte da sessão de setlist
/// (próxima música, transições); de outro lugar, a sessão termina.
Future<void> openTrack(BuildContext context, WidgetRef ref, Track track, {Setlist? setlist, int? index}) async {
  final notifier = ref.read(currentTrackProvider.notifier);
  final pending = notifier.load(track);
  final generation = notifier.loadGeneration;
  final loaded = await pending;
  if (generation != notifier.loadGeneration) return;
  if (!context.mounted) return;

  if (!loaded) {
    final lastError = engineErrorMessage(ref.read(engineProvider).lastErrorCode);
    ScaffoldMessenger.of(context).showSnackBar(
      SnackBar(
          content: Text(
              'Falha ao carregar "${track.title}": $lastError')),
    );
    return;
  }

  final session = ref.read(setlistSessionProvider.notifier);
  if (setlist != null && index != null) {
    session.begin(setlist, index);
  } else {
    session.end();
  }
  Navigator.of(context).push(MaterialPageRoute(builder: (_) => const PerformanceScreen()));
}
