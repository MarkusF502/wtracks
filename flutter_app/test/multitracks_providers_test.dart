import 'dart:async';
import 'dart:io';

import 'package:flutter_app/models/multitracks_origin.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/providers/multitracks_provider.dart';
import 'package:flutter_app/services/multitracks_content_provider.dart';
import 'package:flutter_app/services/multitracks_session_store.dart';
import 'package:flutter_app/services/persistence_service.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';

import 'harness/harness_support.dart';
import 'support/multitracks_fakes.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  late ScriptedJsonTransport api;
  late InMemoryMultiTracksSecureStore secure;

  ProviderContainer container({PersistenceService? persistence}) {
    final c = ProviderContainer(overrides: [
      engineProvider.overrideWithValue(FakeEngine()),
      persistenceServiceProvider.overrideWithValue(persistence ?? InMemoryPersistence()),
      multitracksTransportProvider.overrideWithValue(api),
      multitracksSessionStoreProvider.overrideWithValue(MultiTracksSessionStore(secure)),
    ]);
    addTearDown(c.dispose);
    return c;
  }

  setUp(() {
    api = ScriptedJsonTransport()..handlers['authenticate'] = (_) => ok(loginSuccess());
    secure = InMemoryMultiTracksSecureStore();
  });

  Future<ProviderContainer> signedIn() async {
    final c = container();
    await c.read(multitracksSessionProvider.notifier).restore();
    await c.read(multitracksSessionProvider.notifier).signIn('user', 'secret');
    expect(c.read(multitracksSessionProvider).isAuthenticated, isTrue);
    return c;
  }

  group('session', () {
    test('sign in stores the session, restores it later and signs out locally', () async {
      final c = await signedIn();
      expect(c.read(multitracksContentProvider).hasSession, isTrue);
      expect(secure.values.values.join().contains('secret'), isFalse, reason: 'password never stored');

      final restored = container();
      await restored.read(multitracksSessionProvider.notifier).restore();
      expect(restored.read(multitracksSessionProvider).isAuthenticated, isTrue);
      expect(api.calls.where((c) => c.$1 == 'authenticate'), hasLength(1), reason: 'restoring does not log in again');

      await restored.read(multitracksSessionProvider.notifier).signOut();
      expect(restored.read(multitracksSessionProvider).status, MultiTracksSessionStatus.signedOut);
      expect(restored.read(multitracksContentProvider).hasSession, isFalse);
      expect(await MultiTracksSessionStore(secure).loadSession(), isNull);
    });

    test('device limit is a failure, never a session', () async {
      api.handlers['authenticate'] = (_) => ok({...loginSuccess(), 'result': 5, 'errorCode': 4, 'message': 'Limite'});
      final c = container();
      await c.read(multitracksSessionProvider.notifier).restore();
      await c.read(multitracksSessionProvider.notifier).signIn('user', 'secret');
      final state = c.read(multitracksSessionProvider);
      expect(state.status, MultiTracksSessionStatus.failure);
      expect(state.deviceLimit, isTrue);
      expect(await MultiTracksSessionStore(secure).loadSession(), isNull);
    });

    test('a login answered after sign-out is discarded', () async {
      final answer = Completer<void>();
      api.handlers['authenticate'] = (_) async {
        await answer.future;
        return ok(loginSuccess());
      };
      final c = container();
      await c.read(multitracksSessionProvider.notifier).restore();
      final pending = c.read(multitracksSessionProvider.notifier).signIn('user', 'secret');
      await Future<void>.delayed(Duration.zero);
      await c.read(multitracksSessionProvider.notifier).signOut();
      answer.complete();
      await pending;
      expect(c.read(multitracksSessionProvider).status, MultiTracksSessionStatus.signedOut);
      expect(await MultiTracksSessionStore(secure).loadSession(), isNull);
    });

    test('without secure storage login is unavailable', () async {
      final c = ProviderContainer(overrides: [
        multitracksTransportProvider.overrideWithValue(api),
        multitracksSessionStoreProvider.overrideWithValue(MultiTracksSessionStore(null)),
      ]);
      addTearDown(c.dispose);
      await c.read(multitracksSessionProvider.notifier).restore();
      expect(c.read(multitracksSessionProvider).status, MultiTracksSessionStatus.unavailable);
      await c.read(multitracksSessionProvider.notifier).signIn('user', 'secret');
      expect(api.calls, isEmpty);
    });
  });

  group('library', () {
    test('pages append without duplicates and stop at the end', () async {
      api.handlers['library/songs'] = (body) => switch (body['pageNumber']) {
            1 => ok(songsPage([songSummary(1), songSummary(2)], page: 1, totalPages: 3)),
            2 => ok(songsPage([songSummary(2), songSummary(3)], page: 2, totalPages: 3)),
            _ => ok(songsPage([songSummary(3)], page: 3, totalPages: 3)),
          };
      final c = await signedIn();
      final library = c.read(multitracksLibraryProvider.notifier);
      await library.load();
      expect(c.read(multitracksLibraryProvider).hasMore, isTrue);
      await library.loadMore();
      expect(c.read(multitracksLibraryProvider).songs.map((s) => s.libraryId), [1, 2, 3]);
      await library.loadMore();
      expect(c.read(multitracksLibraryProvider).hasMore, isFalse, reason: 'a page with nothing new ends paging');
      await library.loadMore();
      expect(api.calls.where((call) => call.$1 == 'library/songs'), hasLength(3));
      final body = api.calls.firstWhere((call) => call.$1 == 'library/songs').$2;
      expect(body['siteID'], 40);
      expect(body['filter'], 1);
    });

    test('a slow older search never overwrites a newer one', () async {
      final slow = Completer<void>();
      api.handlers['library/songs'] = (body) async {
        if (body['search'] == 'old') await slow.future;
        return ok(songsPage([songSummary(body['search'] == 'old' ? 1 : 2)]));
      };
      final c = await signedIn();
      final library = c.read(multitracksLibraryProvider.notifier);
      final older = library.load(search: 'old');
      await library.load(search: 'new');
      slow.complete();
      await older;
      final state = c.read(multitracksLibraryProvider);
      expect(state.search, 'new');
      expect(state.songs.single.libraryId, 2);
    });

    test('a failed next page can be retried', () async {
      var fail = true;
      api.handlers['library/songs'] = (body) async {
        if (body['pageNumber'] == 2 && fail) throw const SocketException('offline');
        return ok(songsPage([songSummary(body['pageNumber'] as int)], page: body['pageNumber'] as int, totalPages: 2));
      };
      final c = await signedIn();
      await c.read(multitracksLibraryProvider.notifier).load();
      await c.read(multitracksLibraryProvider.notifier).loadMore();
      expect(c.read(multitracksLibraryProvider).status, MultiTracksLibraryStatus.failure);
      fail = false;
      await c.read(multitracksLibraryProvider.notifier).loadMore();
      expect(c.read(multitracksLibraryProvider).songs.map((s) => s.libraryId), [1, 2]);
    });

    test('a refresh failure keeps the valid list', () async {
      var fail = false;
      api.handlers['library/songs'] = (_) async {
        if (fail) throw const SocketException('offline');
        return ok(songsPage([songSummary(1)]));
      };
      final c = await signedIn();
      await c.read(multitracksLibraryProvider.notifier).load();
      fail = true;
      await c.read(multitracksLibraryProvider.notifier).load();
      final state = c.read(multitracksLibraryProvider);
      expect(state.songs, hasLength(1));
      expect(state.offline, isTrue);
      expect(state.status, MultiTracksLibraryStatus.failure);
    });

    test('HTTP 401 expires the session and clears the list', () async {
      api.handlers['library/songs'] = (_) => const MultiTracksJsonResponse(401, {});
      final c = await signedIn();
      await c.read(multitracksLibraryProvider.notifier).load();
      expect(c.read(multitracksSessionProvider).status, MultiTracksSessionStatus.expired);
      expect(c.read(multitracksLibraryProvider).songs, isEmpty);
      expect(await MultiTracksSessionStore(secure).loadSession(), isNull);
    });
  });

  group('publishImported', () {
    late Directory root;
    setUp(() => root = Directory.systemTemp.createTempSync('mt-publish'));
    tearDown(() => root.deleteSync(recursive: true));

    Future<Track> staged(String version) async {
      final dir = Directory('${root.path}/staging-$version')..createSync();
      ChannelInfo channel(String label, String name) {
        File('${dir.path}/$name').writeAsStringSync('$label-$version');
        return ChannelInfo(label: label, filePath: '${dir.path}/$name', isClickOrGuide: label == 'Click');
      }

      return Track(
        id: 'multitracks-202-30',
        title: 'Synthetic $version',
        key: 'G',
        channels: [channel('Click', '00-301.wav'), channel('Bass', '01-302.wav')],
        origin: MultiTracksOrigin(contentId: 202, keyId: 30, contentType: 26, lastValidatedAt: DateTime.utc(2026)),
      );
    }

    test('saves once, then updates keeping preferences and removing the old audio', () async {
      final persistence = PersistenceService(rootDirectoryResolver: () async => root);
      final c = container(persistence: persistence);
      final library = c.read(trackLibraryProvider.notifier);
      await Future<void>.delayed(Duration.zero);

      final first = await library.publishImported(await staged('v1'));
      expect(c.read(trackLibraryProvider).single.id, 'multitracks-202-30');
      expect(first.channels.every((ch) => ch.filePath.startsWith('${root.path}/wtracks_data/audio/')), isTrue);
      expect(first.channels.first.isClickOrGuide, isTrue);
      expect(first.origin?.contentId, 202);
      expect(c.read(currentTrackProvider), isNull, reason: 'importing does not touch the engine');

      await library.setTransition(first.id, SongTransition.autoLink);
      final second = await library.publishImported(await staged('v2'));
      expect(second.transition, SongTransition.autoLink);
      expect(second.title, 'Synthetic v2');
      expect(c.read(trackLibraryProvider), hasLength(1));
      for (final old in first.channels) {
        expect(File(old.filePath).existsSync(), isFalse);
      }
      expect(File(second.channels.last.filePath).readAsStringSync(), 'Bass-v2');
      final reloaded = await persistence.loadTrack(second.id);
      expect(reloaded?.channels.map((ch) => ch.label), ['Click', 'Bass']);
    });

    test('refuses to replace the song that is open', () async {
      final c = container(persistence: PersistenceService(rootDirectoryResolver: () async => root));
      c.read(currentTrackProvider.notifier).setLoadedTrack(Track(id: 'multitracks-202-30', title: 'x', channels: const []));
      await expectLater(c.read(trackLibraryProvider.notifier).publishImported(await staged('v1')), throwsStateError);
    });
  });
}
