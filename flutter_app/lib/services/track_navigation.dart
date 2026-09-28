import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/track.dart';
import '../providers/engine_provider.dart';
import '../screens/performance_screen.dart';

/// Carrega [track] no engine e navega para a [PerformanceScreen], igual ao
/// fluxo que já existia em `LibraryScreen._openTrack` -- extraído aqui pra
/// não duplicar o texto de erro e o fluxo de navegação entre LibraryScreen e
/// SetlistEditorScreen.
Future<void> openTrack(BuildContext context, WidgetRef ref, Track track) async {
  final loaded = await ref.read(currentTrackProvider.notifier).load(track);
  if (!context.mounted) return;

  if (!loaded) {
    final lastError = ref.read(engineProvider).lastError;
    ScaffoldMessenger.of(context).showSnackBar(
      SnackBar(
          content: Text(
              'Falha ao carregar "${track.title}": ${lastError.isEmpty ? "Formato inválido" : lastError}')),
    );
    return;
  }

  Navigator.of(context).push(MaterialPageRoute(builder: (_) => const PerformanceScreen()));
}
