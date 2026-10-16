import 'dart:async';
import 'dart:io';

import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:path_provider/path_provider.dart';

import '../models/multitracks_import_job.dart';
import '../models/multitracks_session.dart';
import '../services/diagnostics_log.dart';
import '../services/multitracks_auth_service.dart';
import '../services/multitracks_content_provider.dart';
import '../services/multitracks_contract.dart';
import '../services/multitracks_import_coordinator.dart';
import '../services/multitracks_library_service.dart';
import '../services/multitracks_package_downloader.dart';
import '../services/multitracks_session_store.dart';
import 'engine_provider.dart';

// ---------------------------------------------------------------------------
// Dependências (substituídas por falsas nos testes; nenhuma API real em CI)
// ---------------------------------------------------------------------------

final multitracksIdentityProvider = Provider<MultiTracksClientIdentity>((ref) => MultiTracksClientIdentity.transitionalPlayback);

final multitracksTransportProvider = Provider<MultiTracksJsonTransport>((ref) {
  final transport = IoMultiTracksJsonTransport(client: HttpClient()..connectionTimeout = const Duration(seconds: 20));
  ref.onDispose(() => transport.close(force: true));
  return transport;
});

final multitracksSessionStoreProvider = Provider<MultiTracksSessionStore>((ref) => MultiTracksSessionStore(platformSecureStore()));

final multitracksAuthServiceProvider = Provider<MultiTracksAuthService>((ref) => MultiTracksAuthService(
    transport: ref.watch(multitracksTransportProvider), identity: ref.watch(multitracksIdentityProvider)));

final multitracksLibraryServiceProvider = Provider<MultiTracksLibraryService>((ref) => MultiTracksLibraryService(
    transport: ref.watch(multitracksTransportProvider), profile: ref.watch(multitracksIdentityProvider).profile));

final multitracksContentProvider = Provider<MultiTracksContentProvider>((ref) => MultiTracksContentProvider(
    transport: ref.watch(multitracksTransportProvider), profile: ref.watch(multitracksIdentityProvider).profile));

final multitracksDownloaderProvider = Provider<MultiTracksPackageDownloader>((ref) {
  final transport = IoMultiTracksDownloadTransport(client: HttpClient()..connectionTimeout = const Duration(seconds: 20));
  ref.onDispose(() => transport.close(force: true));
  return MultiTracksPackageDownloader(transport: transport);
});

final multitracksImportRunnerProvider = Provider<MultiTracksImportRunner>((ref) => const IsolateMultiTracksImportRunner());

/// Staging no diretório temporário (cache): fora de `wtracks_data`, logo fora do backup do WTracks e do backup automático.
final multitracksStagingRootProvider = Provider<Future<Directory> Function()>(
    (ref) => () async => Directory('${(await getTemporaryDirectory()).path}/multitracks-staging'));

final multitracksFreeBytesProvider = Provider<Future<int?> Function(String path)?>((ref) => Platform.isAndroid ? _androidFreeBytes : null);

Future<int?> _androidFreeBytes(String path) async {
  try {
    return await const MethodChannel('wtracks/multitracks_audio').invokeMethod<int>('freeBytes', {'path': path});
  } on PlatformException {
    return null;
  }
}

// ---------------------------------------------------------------------------
// Sessão
// ---------------------------------------------------------------------------

enum MultiTracksSessionStatus { unknown, restoring, signedOut, authenticating, authenticated, expired, failure, unavailable }

@immutable
class MultiTracksSessionState {
  final MultiTracksSessionStatus status;
  final MultiTracksSession? session;

  /// Muda a cada login/logout/expiração: respostas de gerações anteriores são descartadas.
  final int generation;
  final String? error;
  final bool deviceLimit;

  const MultiTracksSessionState({
    this.status = MultiTracksSessionStatus.unknown,
    this.session,
    this.generation = 0,
    this.error,
    this.deviceLimit = false,
  });

  bool get isAuthenticated => status == MultiTracksSessionStatus.authenticated && session != null;
}

class MultiTracksSessionNotifier extends Notifier<MultiTracksSessionState> {
  @override
  MultiTracksSessionState build() => const MultiTracksSessionState();

  MultiTracksSessionStore get _store => ref.read(multitracksSessionStoreProvider);

  /// Restaura a sessão guardada, sem pedir a senha de novo.
  Future<void> restore() async {
    if (state.status != MultiTracksSessionStatus.unknown) return;
    if (!_store.isAvailable) {
      state = const MultiTracksSessionState(status: MultiTracksSessionStatus.unavailable);
      return;
    }
    final generation = state.generation;
    state = MultiTracksSessionState(status: MultiTracksSessionStatus.restoring, generation: generation);
    MultiTracksSession? session;
    try {
      session = await _store.loadSession();
    } on Object {
      session = null; // armazenamento ilegível: pede login de novo
    }
    if (state.generation != generation) return;
    if (session == null) {
      state = MultiTracksSessionState(status: MultiTracksSessionStatus.signedOut, generation: generation);
      return;
    }
    ref.read(multitracksContentProvider).replaceSession(session.toContext());
    state = MultiTracksSessionState(status: MultiTracksSessionStatus.authenticated, session: session, generation: generation);
  }

  /// A senha só existe nos argumentos desta chamada; nada dela é guardado nem registrado.
  Future<void> signIn(String username, String password) async {
    if (state.status == MultiTracksSessionStatus.authenticating) return;
    if (!_store.isAvailable) {
      state = MultiTracksSessionState(status: MultiTracksSessionStatus.unavailable, generation: state.generation);
      return;
    }
    final generation = state.generation + 1;
    state = MultiTracksSessionState(status: MultiTracksSessionStatus.authenticating, generation: generation);
    MultiTracksSessionState next;
    try {
      final deviceId = await _store.deviceIdentifier();
      final outcome = await ref
          .read(multitracksAuthServiceProvider)
          .authenticate(username: username.trim(), password: password, deviceIdentifier: deviceId);
      if (state.generation != generation) return;
      switch (outcome) {
        case MultiTracksLoginAccepted(:final session):
          await _store.saveSession(session);
          if (state.generation != generation) return;
          ref.read(multitracksContentProvider).replaceSession(session.toContext());
          next = MultiTracksSessionState(status: MultiTracksSessionStatus.authenticated, session: session, generation: generation);
        case MultiTracksLoginDeviceLimit(:final serverMessage):
          next = MultiTracksSessionState(
            status: MultiTracksSessionStatus.failure,
            generation: generation,
            deviceLimit: true,
            error: serverMessage ??
                'Limite de aparelhos da conta atingido. Remova um aparelho na sua conta MultiTracks e tente de novo.',
          );
        case MultiTracksLoginRejected(:final serverMessage, :final result, :final errorCode):
          next = MultiTracksSessionState(
            status: MultiTracksSessionStatus.failure,
            generation: generation,
            error: serverMessage ?? 'Login recusado (resultado ${result ?? '?'}, erro ${errorCode ?? '?'}).',
          );
        case MultiTracksLoginIncomplete():
          next = MultiTracksSessionState(
            status: MultiTracksSessionStatus.failure,
            generation: generation,
            error: 'O login foi aceito, mas a resposta não trouxe os dados da organização necessários.',
          );
      }
    } on MultiTracksHttpFailure catch (error) {
      next = MultiTracksSessionState(
          status: MultiTracksSessionStatus.failure, generation: generation, error: 'O servidor respondeu HTTP ${error.statusCode}.');
    } on FormatException {
      next = MultiTracksSessionState(
          status: MultiTracksSessionStatus.failure, generation: generation, error: 'Resposta inesperada do servidor.');
    } on Object {
      next = MultiTracksSessionState(
          status: MultiTracksSessionStatus.failure, generation: generation, error: 'Sem conexão com a MultiTracks. Tente novamente.');
    }
    if (state.generation == generation) state = next;
  }

  /// Sai localmente. A rota `logout` existe, mas o corpo não foi capturado; não é chamada.
  Future<void> signOut() async {
    final generation = state.generation + 1;
    ref.read(multitracksContentProvider).clearSession();
    state = MultiTracksSessionState(status: MultiTracksSessionStatus.signedOut, generation: generation);
    try {
      await _store.clearSession();
    } on Object {
      // a sessão já foi esquecida na memória
    }
  }

  /// Sessão recusada pelo servidor (HTTP 401/403) na geração [generation].
  Future<void> markExpired(int generation) async {
    if (state.generation != generation || !state.isAuthenticated) return;
    ref.read(multitracksContentProvider).clearSession();
    state = MultiTracksSessionState(status: MultiTracksSessionStatus.expired, generation: generation + 1);
    try {
      await _store.clearSession();
    } on Object {
      // idem
    }
  }

  void clearError() {
    if (state.status == MultiTracksSessionStatus.failure || state.status == MultiTracksSessionStatus.expired) {
      state = MultiTracksSessionState(status: MultiTracksSessionStatus.signedOut, generation: state.generation);
    }
  }
}

final multitracksSessionProvider =
    NotifierProvider<MultiTracksSessionNotifier, MultiTracksSessionState>(MultiTracksSessionNotifier.new);

// ---------------------------------------------------------------------------
// Biblioteca
// ---------------------------------------------------------------------------

enum MultiTracksLibraryStatus { idle, initialLoading, searching, refreshing, loadingMore, data, failure }

@immutable
class MultiTracksLibraryState {
  final MultiTracksLibraryStatus status;
  final List<MultiTracksSongSummary> songs;
  final String search;
  final bool hasMore;
  final String? error;
  final bool offline;

  const MultiTracksLibraryState({
    this.status = MultiTracksLibraryStatus.idle,
    this.songs = const [],
    this.search = '',
    this.hasMore = false,
    this.error,
    this.offline = false,
  });

  bool get isBusy =>
      status == MultiTracksLibraryStatus.initialLoading ||
      status == MultiTracksLibraryStatus.searching ||
      status == MultiTracksLibraryStatus.refreshing ||
      status == MultiTracksLibraryStatus.loadingMore;

  MultiTracksLibraryState copyWith({
    MultiTracksLibraryStatus? status,
    List<MultiTracksSongSummary>? songs,
    String? search,
    bool? hasMore,
    Object? error = _keep,
    bool? offline,
  }) =>
      MultiTracksLibraryState(
        status: status ?? this.status,
        songs: songs ?? this.songs,
        search: search ?? this.search,
        hasMore: hasMore ?? this.hasMore,
        error: identical(error, _keep) ? this.error : error as String?,
        offline: offline ?? this.offline,
      );

  static const _keep = Object();
}

class MultiTracksLibraryNotifier extends Notifier<MultiTracksLibraryState> {
  /// Cada busca/recarga nova invalida as respostas pendentes das anteriores.
  int _token = 0;
  int _page = 0;

  @override
  MultiTracksLibraryState build() {
    ref.listen<int>(multitracksSessionProvider.select((s) => s.generation), (_, _) {
      _token++;
      _page = 0;
      state = const MultiTracksLibraryState();
    });
    return const MultiTracksLibraryState();
  }

  /// Primeira página para [search] (ou recarrega a busca atual). A lista válida continua visível enquanto carrega.
  Future<void> load({String? search}) async {
    final query = (search ?? state.search).trim();
    final sameQuery = query == state.search && state.songs.isNotEmpty;
    final token = ++_token;
    state = state.copyWith(
      status: sameQuery
          ? MultiTracksLibraryStatus.refreshing
          : (state.songs.isEmpty ? MultiTracksLibraryStatus.initialLoading : MultiTracksLibraryStatus.searching),
      search: query,
      error: null,
    );
    await _fetch(token, page: 1, query: query, append: false);
  }

  Future<void> loadMore() async {
    if (!state.hasMore || state.isBusy) return;
    final token = _token;
    state = state.copyWith(status: MultiTracksLibraryStatus.loadingMore, error: null);
    await _fetch(token, page: _page + 1, query: state.search, append: true);
  }

  Future<void> _fetch(int token, {required int page, required String query, required bool append}) async {
    final sessionState = ref.read(multitracksSessionProvider);
    final session = sessionState.session;
    if (!sessionState.isAuthenticated || session == null) {
      state = state.copyWith(status: MultiTracksLibraryStatus.failure, error: 'Entre na sua conta MultiTracks.');
      return;
    }
    if (session.siteId == null) {
      state = state.copyWith(
          status: MultiTracksLibraryStatus.failure, error: 'A conta não informou o site necessário para consultar a biblioteca.');
      return;
    }
    try {
      final result =
          await ref.read(multitracksLibraryServiceProvider).songs(session.toContext(), pageNumber: page, search: query);
      if (token != _token || ref.read(multitracksSessionProvider).generation != sessionState.generation) return;
      final known = append ? {for (final song in state.songs) song.libraryId} : <int>{};
      final fresh = [for (final song in result.songs) if (known.add(song.libraryId)) song];
      _page = page;
      state = state.copyWith(
        status: MultiTracksLibraryStatus.data,
        songs: List.unmodifiable([if (append) ...state.songs, ...fresh]),
        // Página sem itens novos encerra a paginação mesmo que o servidor anuncie mais.
        hasMore: result.hasNextPage && fresh.isNotEmpty,
        error: null,
        offline: false,
      );
    } on Object catch (error) {
      if (token != _token) return;
      final expired = error is MultiTracksSessionExpired ||
          (error is MultiTracksHttpFailure && (error.statusCode == 401 || error.statusCode == 403));
      if (expired) {
        await ref.read(multitracksSessionProvider.notifier).markExpired(sessionState.generation);
        return;
      }
      final offline = error is SocketException || error is TimeoutException || error is HttpException;
      state = state.copyWith(
        status: MultiTracksLibraryStatus.failure,
        offline: offline,
        error: switch (error) {
          _ when offline => 'Sem conexão com a MultiTracks. A biblioteca local do WTracks continua disponível.',
          MultiTracksBusinessFailure(:final serverMessage, :final result, :final errorCode) =>
            serverMessage ?? 'A MultiTracks recusou a consulta (resultado $result, erro $errorCode).',
          MultiTracksHttpFailure(:final statusCode) => 'O servidor respondeu HTTP $statusCode.',
          FormatException() => 'Resposta da biblioteca em formato inesperado.',
          _ => 'Não foi possível carregar a biblioteca.',
        },
      );
    }
  }
}

final multitracksLibraryProvider =
    NotifierProvider<MultiTracksLibraryNotifier, MultiTracksLibraryState>(MultiTracksLibraryNotifier.new);

// ---------------------------------------------------------------------------
// Importação
// ---------------------------------------------------------------------------

/// Trabalhos por `contentId:keyId`. Vive fora das telas: sair da tela de detalhes não interrompe nem perde o progresso.
class MultiTracksImportNotifier extends Notifier<Map<String, MultiTracksImportJob>> {
  MultiTracksImportCoordinator? _coordinator;

  MultiTracksImportCoordinator get coordinator => _coordinator ??= MultiTracksImportCoordinator(
        content: ref.read(multitracksContentProvider),
        downloader: ref.read(multitracksDownloaderProvider),
        runner: ref.read(multitracksImportRunnerProvider),
        stagingRoot: ref.read(multitracksStagingRootProvider),
        freeBytes: ref.read(multitracksFreeBytesProvider),
        publish: (content, origin) {
          for (final warning in content.structureWarnings) {
            ref.read(diagnosticsProvider.notifier).info('MultiTracks "${content.track.title}": $warning.');
          }
          return ref.read(trackLibraryProvider.notifier).publishImported(content.track.copyWith(origin: origin));
        },
        onUpdate: (job) => state = {...state, job.key: job},
      );

  @override
  Map<String, MultiTracksImportJob> build() {
    ref.listen<int>(multitracksSessionProvider.select((s) => s.generation), (_, _) {
      // Logout/troca de conta: interrompe o que estiver em curso e esquece os aluguéis pedidos.
      for (final job in state.values) {
        if (job.phase.isActive) coordinator.cancel(job.key);
      }
      coordinator.resetSession();
    });
    unawaited(Future(() => coordinator.cleanStaleStaging()).catchError((Object _) {}));
    return const {};
  }

  Future<MultiTracksImportJob> start(MultiTracksImportRequest request,
          {required MultiTracksRentalConfirmation confirmRental}) =>
      coordinator.start(request, confirmRental: confirmRental);

  void cancel(String key) => coordinator.cancel(key);

  /// Esconde um trabalho terminado.
  void dismiss(String key) {
    final job = state[key];
    if (job == null || job.phase.isActive) return;
    state = {...state}..remove(key);
  }
}

final multitracksImportProvider =
    NotifierProvider<MultiTracksImportNotifier, Map<String, MultiTracksImportJob>>(MultiTracksImportNotifier.new);
