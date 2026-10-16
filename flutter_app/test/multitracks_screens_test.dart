import 'package:flutter/material.dart';
import 'package:flutter_app/models/multitracks_import_job.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/providers/multitracks_provider.dart';
import 'package:flutter_app/screens/library_screen.dart';
import 'package:flutter_app/screens/multitracks_library_screen.dart';
import 'package:flutter_app/screens/multitracks_song_screen.dart';
import 'package:flutter_app/services/multitracks_contract.dart';
import 'package:flutter_app/services/multitracks_session_store.dart';
import 'package:flutter_app/widgets/multitracks_import_progress.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_test/flutter_test.dart';

import 'harness/harness_support.dart';
import 'support/multitracks_fakes.dart';

const _selection = MultiTracksContentSelection(
  contentId: 202,
  contentType: 26,
  keyId: 30,
);

void main() {
  late ScriptedJsonTransport api;
  late InMemoryMultiTracksSecureStore secure;

  setUp(() {
    api = ScriptedJsonTransport();
    api.handlers['authenticate'] = (_) => ok(loginSuccess());
    api.handlers['library/songs'] = (body) => ok(
      songsPage([
        if ('${body['search']}'.isEmpty) ...[
          songSummary(1, title: 'Primeira', rentals: true),
          songSummary(2, title: 'Segunda'),
        ],
      ]),
    );
    secure = InMemoryMultiTracksSecureStore();
  });

  Future<ProviderContainer> pump(
    WidgetTester tester,
    Widget home, {
    List<Track> tracks = const [],
  }) async {
    tester.view.physicalSize = const Size(390, 844);
    tester.view.devicePixelRatio = 1.0;
    addTearDown(tester.view.reset);
    final container = ProviderContainer(
      overrides: [
        engineProvider.overrideWithValue(FakeEngine()),
        persistenceServiceProvider.overrideWithValue(
          InMemoryPersistence(initialTracks: tracks),
        ),
        multitracksTransportProvider.overrideWithValue(api),
        multitracksSessionStoreProvider.overrideWithValue(
          MultiTracksSessionStore(secure),
        ),
        multitracksFreeBytesProvider.overrideWithValue(null),
      ],
    );
    addTearDown(container.dispose);
    await tester.pumpWidget(
      UncontrolledProviderScope(
        container: container,
        child: MaterialApp(
          theme: ThemeData.dark(useMaterial3: true),
          home: home,
        ),
      ),
    );
    await tester.pump();
    await tester.pump();
    return container;
  }

  Future<void> settle(WidgetTester tester) async {
    for (var i = 0; i < 12; i++) {
      await tester.pump(const Duration(milliseconds: 50));
    }
  }

  Future<void> signIn(ProviderContainer container) async {
    await container.read(multitracksSessionProvider.notifier).restore();
    await container
        .read(multitracksSessionProvider.notifier)
        .signIn('user', 'secret');
  }

  group('login', () {
    testWidgets('device limit shows the server message and stays on the form', (
      tester,
    ) async {
      api.handlers['authenticate'] = (_) => ok({
        ...loginSuccess(),
        'result': 5,
        'errorCode': 4,
        'message': 'Remova um aparelho.',
      });
      await pump(tester, const MultiTracksLibraryScreen());
      await tester.enterText(
        find.byKey(const Key('multitracks-username')),
        'user',
      );
      await tester.enterText(
        find.byKey(const Key('multitracks-password')),
        'secret',
      );
      await tester.tap(find.byKey(const Key('multitracks-sign-in')));
      await settle(tester);
      expect(find.byKey(const Key('multitracks-login-error')), findsOneWidget);
      expect(find.text('Remova um aparelho.'), findsOneWidget);
      expect(find.byKey(const Key('multitracks-library-list')), findsNothing);
    });

    testWidgets(
      'success clears the password and lists the organization library',
      (tester) async {
        await pump(tester, const MultiTracksLibraryScreen());
        await tester.enterText(
          find.byKey(const Key('multitracks-username')),
          'user',
        );
        await tester.enterText(
          find.byKey(const Key('multitracks-password')),
          'secret',
        );
        await tester.tap(find.byKey(const Key('multitracks-sign-in')));
        await settle(tester);
        expect(find.byKey(const Key('multitracks-password')), findsNothing);
        expect(find.text('Primeira'), findsOneWidget);
        expect(find.text('Rental disponível'), findsOneWidget);
        expect(
          api.calls.where((c) => c.$1 == 'content/download'),
          isEmpty,
          reason: 'listing never touches content',
        );
      },
    );
  });

  group('library', () {
    testWidgets('search is debounced and an empty result is explained', (
      tester,
    ) async {
      final container = await pump(tester, const SizedBox());
      await signIn(container);
      await tester.pumpWidget(
        UncontrolledProviderScope(
          container: container,
          child: const MaterialApp(home: MultiTracksLibraryScreen()),
        ),
      );
      await settle(tester);
      final before = api.calls.length;
      await tester.enterText(
        find.byKey(const Key('multitracks-search')),
        'nada',
      );
      await tester.pump(const Duration(milliseconds: 100));
      expect(api.calls.length, before, reason: 'still debouncing');
      await settle(tester);
      expect(api.calls.last.$2['search'], 'nada');
      expect(find.text('Nenhum resultado'), findsOneWidget);
    });

    testWidgets(
      'a library item resolves songID as contentID without requesting a link or rental',
      (tester) async {
        api.handlers['content/download'] = contentHandler(
          metadata: contentResponse,
          link: contentResponse,
        );
        final container = await pump(tester, const SizedBox());
        await signIn(container);
        await tester.pumpWidget(
          UncontrolledProviderScope(
            container: container,
            child: MaterialApp(
              home: MultiTracksSongScreen(
                summary: MultiTracksSongSummary.fromJson(
                  songSummary(1, songId: 202),
                ),
              ),
            ),
          ),
        );
        await settle(tester);
        final item = api.contentItems.single;
        expect(item['contentID'], 202);
        expect(item['contentType'], 26);
        expect(item['keyID'], 0);
        expect(item['downloadLink'], isFalse);
        expect(item['redeemRental'], isFalse);
        expect(
          find.byKey(const Key('multitracks-identity-pending')),
          findsNothing,
        );
        expect(find.widgetWithText(ChoiceChip, 'G'), findsOneWidget);
        expect(
          tester
              .widget<ChoiceChip>(find.widgetWithText(ChoiceChip, 'G'))
              .selected,
          isTrue,
        );
      },
    );
  });

  group('song details', () {
    Future<ProviderContainer> openDetails(
      WidgetTester tester, {
      List<Track> tracks = const [],
    }) async {
      final container = await pump(tester, const SizedBox(), tracks: tracks);
      await signIn(container);
      await tester.pumpWidget(
        UncontrolledProviderScope(
          container: container,
          child: const MaterialApp(
            home: MultiTracksSongScreen(selection: _selection),
          ),
        ),
      );
      await settle(tester);
      return container;
    }

    testWidgets(
      'opening only consults metadata and shows keys and every track',
      (tester) async {
        api.handlers['content/download'] = contentHandler(
          metadata: contentResponse,
          link: contentResponse,
        );
        await openDetails(tester);
        final item = api.contentItems.single;
        expect(item['downloadLink'], isFalse);
        expect(item['redeemRental'], isFalse);
        expect(find.widgetWithText(ChoiceChip, 'G'), findsOneWidget);
        expect(find.widgetWithText(ChoiceChip, 'A'), findsOneWidget);
        expect(find.text('Click'), findsOneWidget);
        expect(find.text('Bass'), findsOneWidget);
        expect(find.text('Click/Guia'), findsOneWidget);
        expect(find.text('Alugar e baixar'), findsOneWidget);
      },
    );

    testWidgets('changing key consults again without link or rental', (
      tester,
    ) async {
      api.handlers['content/download'] = contentHandler(
        metadata: contentResponse,
        link: contentResponse,
      );
      await openDetails(tester);
      await tester.tap(find.widgetWithText(ChoiceChip, 'A'));
      await settle(tester);
      expect(api.contentItems.map((i) => i['keyID']), [30, 31]);
      expect(
        api.contentItems.every(
          (i) => i['downloadLink'] == false && i['redeemRental'] == false,
        ),
        isTrue,
      );
    });

    testWidgets('cancelling the rental dialog never redeems', (tester) async {
      api.handlers['content/download'] = contentHandler(
        metadata: contentResponse,
        link: contentResponse,
      );
      await openDetails(tester);
      await tester.tap(find.byKey(const Key('multitracks-download')));
      await settle(tester);
      expect(find.text('Confirmar aluguel'), findsWidgets);
      await tester.tap(find.byKey(const Key('multitracks-rental-cancel')));
      await settle(tester);
      expect(api.redeemCalls, 0);
      expect(find.text('Importação cancelada'), findsOneWidget);
    });

    testWidgets('confirming redeems exactly once, even with repeated taps', (
      tester,
    ) async {
      api.handlers['content/download'] = contentHandler(
        metadata: contentResponse,
        link: contentResponse,
        redeem: () => contentResponse(),
      );
      await openDetails(tester);
      await tester.tap(find.byKey(const Key('multitracks-download')));
      await settle(tester);
      final confirm = find.byKey(const Key('multitracks-rental-confirm'));
      await tester.tap(confirm);
      await tester.tap(confirm, warnIfMissed: false);
      await settle(tester);
      expect(api.redeemCalls, 1);
      expect(
        find.textContaining('Falhou em'),
        findsOneWidget,
        reason: 'no link after the rental: reported, not retried',
      );
    });

    testWidgets(
      'a local copy of the same key offers Abrir and Baixar novamente',
      (tester) async {
        api.handlers['content/download'] = contentHandler(
          metadata: contentResponse,
          link: contentResponse,
        );
        await openDetails(
          tester,
          tracks: [
            Track(
              id: multitracksTrackId(202, 30),
              title: 'Synthetic Song',
              channels: const [],
            ),
          ],
        );
        expect(find.byKey(const Key('multitracks-open-local')), findsOneWidget);
        expect(find.byKey(const Key('multitracks-redownload')), findsOneWidget);
        expect(find.byKey(const Key('multitracks-download')), findsNothing);
      },
    );
  });

  group('progress', () {
    Future<void> show(
      WidgetTester tester,
      MultiTracksImportJob job, {
      VoidCallback? onCancel,
      VoidCallback? onOpen,
    }) => tester.pumpWidget(
      MaterialApp(
        home: Scaffold(
          body: MultiTracksImportProgress(
            job: job,
            onCancel: onCancel ?? () {},
            onRetry: () {},
            onDismiss: () {},
            onOpen: onOpen,
          ),
        ),
      ),
    );

    const base = MultiTracksImportJob(key: '202:30', title: 'Synthetic Song');

    testWidgets('download shows bytes and can be cancelled', (tester) async {
      var cancelled = false;
      await show(
        tester,
        base.copyWith(
          phase: MultiTracksImportPhase.downloading,
          receivedBytes: 512 * 1024,
          totalBytes: 1024 * 1024,
        ),
        onCancel: () => cancelled = true,
      );
      expect(find.text('512.0 KB de 1.0 MB (50%)'), findsOneWidget);
      await tester.tap(find.byKey(const Key('multitracks-cancel-import')));
      expect(cancelled, isTrue);
    });

    testWidgets('conversion names the current track and does not claim 100%', (
      tester,
    ) async {
      await show(
        tester,
        base.copyWith(
          phase: MultiTracksImportPhase.transcoding,
          stemIndex: 1,
          stemCount: 3,
          stemLabel: 'Bass',
        ),
      );
      expect(find.text('Convertendo faixa 2 de 3'), findsOneWidget);
      expect(find.text('Bass'), findsOneWidget);
      final bar = tester.widget<LinearProgressIndicator>(
        find.byType(LinearProgressIndicator),
      );
      expect(bar.value, closeTo(1 / 3, 1e-9));
    });

    testWidgets(
      'failure names the step and offers retry; saving cannot be cancelled',
      (tester) async {
        await show(
          tester,
          base.copyWith(
            phase: MultiTracksImportPhase.failed,
            failedPhase: MultiTracksImportPhase.downloading,
            message: 'MD5',
          ),
        );
        expect(find.text('Falhou em: Baixando'), findsOneWidget);
        expect(find.byKey(const Key('multitracks-retry')), findsOneWidget);
        await show(tester, base.copyWith(phase: MultiTracksImportPhase.saving));
        expect(
          find.byKey(const Key('multitracks-cancel-import')),
          findsNothing,
        );
      },
    );

    testWidgets('completion offers to open the song', (tester) async {
      var opened = false;
      await show(
        tester,
        base.copyWith(
          phase: MultiTracksImportPhase.completed,
          track: const Track(
            id: 'multitracks-202-30',
            title: 'Synthetic Song',
            channels: [],
          ),
        ),
        onOpen: () => opened = true,
      );
      await tester.tap(find.byKey(const Key('multitracks-open-imported')));
      expect(opened, isTrue);
    });
  });

  testWidgets('the library + button offers MultiTracks next to file import', (
    tester,
  ) async {
    await pump(tester, const LibraryScreen());
    await tester.tap(find.byTooltip('Adicionar música'));
    await settle(tester);
    expect(find.byKey(const Key('add-source-files')), findsOneWidget);
    await tester.tap(find.byKey(const Key('add-source-multitracks')));
    await settle(tester);
    expect(find.text('Biblioteca MultiTracks'), findsOneWidget);
    expect(find.byKey(const Key('multitracks-sign-in')), findsOneWidget);
  });
}
