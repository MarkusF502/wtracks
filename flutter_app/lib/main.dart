import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import 'providers/engine_provider.dart';
import 'screens/library_screen.dart';

void main() {
  runApp(const ProviderScope(child: WTracksApp()));
}

class WTracksApp extends ConsumerWidget {
  const WTracksApp({super.key});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    // Ler o provider aqui já dispara initialise() na primeira vez que a
    // árvore de widgets é construída.
    ref.watch(engineProvider);

    return MaterialApp(
      title: 'WTracks',
      theme: ThemeData(
        colorSchemeSeed: Colors.indigo,
        brightness: Brightness.dark,
        useMaterial3: true,
      ),
      home: const LibraryScreen(),
    );
  }
}