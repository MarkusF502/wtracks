import 'dart:async';

import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/track.dart';
import '../providers/multitracks_provider.dart';
import '../services/multitracks_contract.dart';
import '../theme/app_colors.dart';
import 'multitracks_login_screen.dart';
import 'multitracks_song_screen.dart';

/// Biblioteca da organização na MultiTracks (não é o catálogo global). Sem sessão, mostra o login no lugar da lista.
/// Nada aqui mexe no motor de áudio: abrir esta tela não altera a música tocando.
///
/// Com [pickMode] (aberta por "Adicionar música"), devolve a [Track] importada/escolhida com `Navigator.pop`.
class MultiTracksLibraryScreen extends ConsumerStatefulWidget {
  final bool pickMode;
  const MultiTracksLibraryScreen({super.key, this.pickMode = false});

  @override
  ConsumerState<MultiTracksLibraryScreen> createState() => _MultiTracksLibraryScreenState();
}

class _MultiTracksLibraryScreenState extends ConsumerState<MultiTracksLibraryScreen> {
  @override
  void initState() {
    super.initState();
    Future.microtask(() {
      if (mounted) ref.read(multitracksSessionProvider.notifier).restore();
    });
  }

  Future<void> _openSong({MultiTracksSongSummary? summary, MultiTracksContentSelection? selection}) async {
    final track = await Navigator.of(context).push<Track>(MaterialPageRoute(
      builder: (_) => MultiTracksSongScreen(summary: summary, selection: selection, pickMode: widget.pickMode),
    ));
    if (track != null && mounted && widget.pickMode) Navigator.of(context).pop(track);
  }

  Future<void> _openByIdentifier() async {
    final selection = await showContentIdentifierDialog(context);
    if (selection != null && mounted) await _openSong(selection: selection);
  }

  Future<void> _signOut() async {
    final confirmed = await showDialog<bool>(
      context: context,
      builder: (ctx) => AlertDialog(
        title: const Text('Sair da MultiTracks?'),
        content: const Text('As músicas já importadas continuam na biblioteca do WTracks.'),
        actions: [
          TextButton(onPressed: () => Navigator.pop(ctx, false), child: const Text('Cancelar')),
          FilledButton(onPressed: () => Navigator.pop(ctx, true), child: const Text('Sair')),
        ],
      ),
    );
    if (confirmed == true) await ref.read(multitracksSessionProvider.notifier).signOut();
  }

  @override
  Widget build(BuildContext context) {
    final session = ref.watch(multitracksSessionProvider);
    final library = ref.watch(multitracksLibraryProvider);

    final Widget body = switch (session.status) {
      MultiTracksSessionStatus.unknown || MultiTracksSessionStatus.restoring =>
        const Center(child: CircularProgressIndicator(color: kAccent)),
      MultiTracksSessionStatus.unavailable => const _Message(
          icon: Icons.phonelink_lock,
          title: 'Disponível somente no Android',
          text: 'A conta MultiTracks precisa do armazenamento seguro do aparelho para guardar a sessão e uma identidade '
              'estável. A biblioteca local do WTracks continua disponível.',
        ),
      MultiTracksSessionStatus.authenticated => _LibraryBody(onOpen: (song) => _openSong(summary: song)),
      _ => const MultiTracksLoginPanel(),
    };

    return Scaffold(
      backgroundColor: kBg,
      appBar: AppBar(
        backgroundColor: kPanelBg,
        title: const Text('Biblioteca MultiTracks'),
        actions: [
          if (session.isAuthenticated) ...[
            Tooltip(
              message: library.offline ? 'Sem conexão' : 'Conectado como ${session.session?.displayName ?? 'você'}',
              child: Padding(
                padding: const EdgeInsets.symmetric(horizontal: 8),
                child: Icon(library.offline ? Icons.cloud_off : Icons.cloud_done_outlined,
                    color: library.offline ? Colors.orangeAccent : kAccent),
              ),
            ),
            PopupMenuButton<String>(
              tooltip: 'Opções da MultiTracks',
              onSelected: (action) => switch (action) {
                'refresh' => ref.read(multitracksLibraryProvider.notifier).load(),
                'identifier' => _openByIdentifier(),
                _ => _signOut(),
              },
              itemBuilder: (_) => const [
                PopupMenuItem(value: 'refresh', child: Text('Atualizar')),
                PopupMenuItem(value: 'identifier', child: Text('Abrir por identificador…')),
                PopupMenuItem(value: 'signout', child: Text('Sair da conta')),
              ],
            ),
          ],
        ],
      ),
      body: SafeArea(child: body),
    );
  }
}

class _LibraryBody extends ConsumerStatefulWidget {
  final void Function(MultiTracksSongSummary song) onOpen;
  const _LibraryBody({required this.onOpen});

  @override
  ConsumerState<_LibraryBody> createState() => _LibraryBodyState();
}

class _LibraryBodyState extends ConsumerState<_LibraryBody> {
  final _search = TextEditingController();
  final _scroll = ScrollController();
  Timer? _debounce;

  @override
  void initState() {
    super.initState();
    _search.text = ref.read(multitracksLibraryProvider).search;
    _scroll.addListener(_maybeLoadMore);
    Future.microtask(() {
      if (mounted && ref.read(multitracksLibraryProvider).status == MultiTracksLibraryStatus.idle) {
        ref.read(multitracksLibraryProvider.notifier).load();
      }
    });
  }

  @override
  void dispose() {
    _debounce?.cancel();
    _search.dispose();
    _scroll.dispose();
    super.dispose();
  }

  void _maybeLoadMore() {
    // Depois de uma falha, só o botão "Tentar de novo" pede a página: rolar não repete chamadas que falharam.
    if (_scroll.position.extentAfter < 400 && ref.read(multitracksLibraryProvider).status != MultiTracksLibraryStatus.failure) {
      ref.read(multitracksLibraryProvider.notifier).loadMore();
    }
  }

  void _onSearch(String value) {
    _debounce?.cancel();
    _debounce = Timer(const Duration(milliseconds: 400), () {
      if (mounted) ref.read(multitracksLibraryProvider.notifier).load(search: value);
    });
  }

  @override
  Widget build(BuildContext context) {
    final state = ref.watch(multitracksLibraryProvider);
    final session = ref.watch(multitracksSessionProvider).session;
    final songs = state.songs;

    Widget list;
    if (state.status == MultiTracksLibraryStatus.initialLoading || state.status == MultiTracksLibraryStatus.idle) {
      list = ListView(
        key: const Key('multitracks-library-skeleton'),
        physics: const AlwaysScrollableScrollPhysics(),
        children: [for (var i = 0; i < 6; i++) const _SkeletonTile()],
      );
    } else if (songs.isEmpty && state.status == MultiTracksLibraryStatus.failure) {
      list = ListView(physics: const AlwaysScrollableScrollPhysics(), children: [
        _Message(
          icon: state.offline ? Icons.cloud_off : Icons.error_outline,
          title: state.offline ? 'Sem conexão' : 'Não foi possível carregar',
          text: state.error ?? '',
          action: FilledButton(
              onPressed: () => ref.read(multitracksLibraryProvider.notifier).load(), child: const Text('Tentar novamente')),
        ),
      ]);
    } else if (songs.isEmpty && state.status == MultiTracksLibraryStatus.data) {
      list = ListView(physics: const AlwaysScrollableScrollPhysics(), children: [
        state.search.isEmpty
            ? const _Message(
                icon: Icons.library_music_outlined,
                title: 'Biblioteca vazia',
                text: 'A organização ainda não tem músicas na biblioteca MultiTracks.',
              )
            : _Message(icon: Icons.search_off, title: 'Nenhum resultado', text: 'Nada encontrado para "${state.search}".'),
      ]);
    } else {
      final footer = state.status == MultiTracksLibraryStatus.loadingMore
          ? const Padding(padding: EdgeInsets.all(16), child: Center(child: CircularProgressIndicator()))
          : state.status == MultiTracksLibraryStatus.failure
              ? _InlineError(text: state.error ?? '', onRetry: () => ref.read(multitracksLibraryProvider.notifier).loadMore())
              : null;
      list = ListView.builder(
        key: const Key('multitracks-library-list'),
        controller: _scroll,
        physics: const AlwaysScrollableScrollPhysics(),
        padding: const EdgeInsets.fromLTRB(12, 0, 12, 12),
        itemCount: songs.length + (footer == null ? 0 : 1),
        itemBuilder: (context, index) {
          if (index == songs.length) return footer!;
          final song = songs[index];
          return _SongTile(song: song, onTap: () => widget.onOpen(song));
        },
      );
    }

    return Column(children: [
      Padding(
        padding: const EdgeInsets.all(12),
        child: TextField(
          key: const Key('multitracks-search'),
          controller: _search,
          textInputAction: TextInputAction.search,
          style: const TextStyle(color: kText),
          decoration: InputDecoration(
            isDense: true,
            hintText: 'Buscar na biblioteca da organização',
            hintStyle: const TextStyle(color: kTextDim),
            prefixIcon: const Icon(Icons.search, color: kTextDim),
            suffixIcon: state.status == MultiTracksLibraryStatus.searching
                ? const Padding(padding: EdgeInsets.all(12), child: SizedBox.square(dimension: 16, child: CircularProgressIndicator(strokeWidth: 2)))
                : null,
            filled: true,
            fillColor: kPanelBg,
            border: OutlineInputBorder(borderRadius: BorderRadius.circular(10), borderSide: BorderSide.none),
          ),
          onChanged: _onSearch,
          onSubmitted: (value) {
            _debounce?.cancel();
            ref.read(multitracksLibraryProvider.notifier).load(search: value);
          },
        ),
      ),
      if (session?.hasMultipleOrganizations ?? false)
        const Padding(
          padding: EdgeInsets.fromLTRB(16, 0, 16, 8),
          child: Text('Sua conta tem mais de uma organização; o WTracks usa a organização padrão (troca ainda não suportada).',
              style: TextStyle(color: kTextDim, fontSize: 12)),
        ),
      if (state.status == MultiTracksLibraryStatus.refreshing) const LinearProgressIndicator(minHeight: 2, color: kAccent),
      Expanded(
        child: RefreshIndicator(
          color: kAccent,
          onRefresh: () => ref.read(multitracksLibraryProvider.notifier).load(),
          child: list,
        ),
      ),
    ]);
  }
}

class _SongTile extends StatelessWidget {
  final MultiTracksSongSummary song;
  final VoidCallback onTap;
  const _SongTile({required this.song, required this.onTap});

  @override
  Widget build(BuildContext context) {
    final details = [if (song.artist.isNotEmpty) song.artist, if (song.album.isNotEmpty) song.album].join(' · ');
    final access = song.dateContentPurchased != null
        ? 'Adquirida'
        : song.rentalsAvailable
            ? 'Rental disponível'
            : null;
    return Card(
      color: kPanelBg,
      margin: const EdgeInsets.symmetric(vertical: 4),
      shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(8), side: const BorderSide(color: kBorder)),
      child: ListTile(
        minVerticalPadding: 10,
        leading: MultiTracksCover(url: song.image),
        title: Text(song.song, style: const TextStyle(color: kText)),
        subtitle: details.isEmpty ? null : Text(details, style: const TextStyle(color: kTextDim)),
        trailing: access == null ? const Icon(Icons.chevron_right, color: kTextDim) : Text(access, style: const TextStyle(color: kAccent, fontSize: 12)),
        onTap: onTap,
      ),
    );
  }
}

class _SkeletonTile extends StatelessWidget {
  const _SkeletonTile();
  @override
  Widget build(BuildContext context) => Container(
        height: 64,
        margin: const EdgeInsets.symmetric(horizontal: 12, vertical: 4),
        decoration: BoxDecoration(color: kPanelBg, borderRadius: BorderRadius.circular(8), border: Border.all(color: kBorder)),
      );
}

class _InlineError extends StatelessWidget {
  final String text;
  final VoidCallback onRetry;
  const _InlineError({required this.text, required this.onRetry});
  @override
  Widget build(BuildContext context) => Padding(
        padding: const EdgeInsets.all(12),
        child: Row(children: [
          const Icon(Icons.error_outline, color: Colors.redAccent),
          const SizedBox(width: 8),
          Expanded(child: Text(text, style: const TextStyle(color: kText))),
          TextButton(onPressed: onRetry, child: const Text('Tentar de novo')),
        ]),
      );
}

class _Message extends StatelessWidget {
  final IconData icon;
  final String title, text;
  final Widget? action;
  const _Message({required this.icon, required this.title, required this.text, this.action});

  @override
  Widget build(BuildContext context) => Padding(
        padding: const EdgeInsets.all(32),
        child: Column(mainAxisSize: MainAxisSize.min, children: [
          Icon(icon, color: kTextDim, size: 48),
          const SizedBox(height: 12),
          Text(title, textAlign: TextAlign.center, style: const TextStyle(color: kText, fontSize: 18)),
          const SizedBox(height: 8),
          Text(text, textAlign: TextAlign.center, style: const TextStyle(color: kTextDim)),
          if (action != null) ...[const SizedBox(height: 16), action!],
        ]),
      );
}
