import 'dart:async';
import 'dart:io';

import 'package:flutter_app/models/multitracks_import_job.dart';
import 'package:flutter_app/models/multitracks_origin.dart';
import 'package:flutter_app/models/multitracks_song_details.dart';
import 'package:flutter_app/services/multitracks_auth_service.dart';
import 'package:flutter_app/services/multitracks_content_provider.dart';
import 'package:flutter_app/services/multitracks_contract.dart';
import 'package:flutter_app/services/multitracks_import_coordinator.dart';
import 'package:flutter_app/services/multitracks_package_downloader.dart';
import 'package:flutter_app/services/multitracks_package_importer.dart';
import 'package:flutter_test/flutter_test.dart';

import 'support/multitracks_fakes.dart';

const _context = MultiTracksLibraryContext(
  hash: 'synthetic',
  customerId: 10,
  userAccessId: 20,
  countryId: 30,
  build: 86204,
  restricted: false,
  language: 'pt',
  siteId: 40,
);
const _selection = MultiTracksContentSelection(contentId: 202, contentType: 26, keyId: 30);

void main() {
  late Directory tmp;
  late ScriptedJsonTransport api;
  late MultiTracksContentProvider content;
  late List<MultiTracksImportJob> updates;
  late List<(MultiTracksImportedContent, MultiTracksOrigin)> published;
  late FakeTranscoder transcoder;

  setUp(() {
    tmp = Directory.systemTemp.createTempSync('mt-coordinator');
    api = ScriptedJsonTransport();
    content = MultiTracksContentProvider(transport: api, profile: MultiTracksClientIdentity.transitionalPlayback.profile)
      ..replaceSession(_context);
    updates = [];
    published = [];
    transcoder = FakeTranscoder();
  });

  tearDown(() => tmp.deleteSync(recursive: true));

  final package = syntheticPackage({301: [1, 2, 3], 302: [4, 5, 6, 7]});

  MultiTracksImportCoordinator coordinator({MultiTracksDownloadTransport? download, Future<int?> Function(String)? freeBytes}) =>
      MultiTracksImportCoordinator(
        content: content,
        downloader: MultiTracksPackageDownloader(transport: download ?? FakeDownloadTransport(package)),
        runner: InlineMultiTracksImportRunner(MultiTracksPackageImporter(transcoder: transcoder)),
        stagingRoot: () async => Directory('${tmp.path}/staging'),
        publish: (imported, origin) async {
          published.add((imported, origin));
          return imported.track.copyWith(origin: origin);
        },
        onUpdate: updates.add,
        freeBytes: freeBytes,
        clock: () => DateTime.utc(2026, 10, 15),
      );

  MultiTracksSongDetails details({int? rentalsRemaining = 2}) => MultiTracksSongDetails.from(
      _selection, MultiTracksContentResponse.fromJson(contentResponse(rentalsRemaining: rentalsRemaining)));

  Future<bool> neverAsked(MultiTracksRentalPrompt _) async => fail('rental prompt not expected');

  bool stagingIsEmpty() {
    final root = Directory('${tmp.path}/staging');
    return !root.existsSync() || root.listSync().isEmpty;
  }

  test('granted content: link, download, validate, convert every track and save once', () async {
    api.handlers['content/download'] =
        contentHandler(metadata: contentResponse, link: () => contentResponse(downloadUrl: syntheticDownloadUrl));

    final job = await coordinator().start(MultiTracksImportRequest(details()), confirmRental: neverAsked);

    expect(job.phase, MultiTracksImportPhase.completed);
    expect(api.redeemCalls, 0);
    expect(api.linkCalls, 1);
    final phases = updates.map((u) => u.phase).toSet();
    expect(phases, containsAll([
      MultiTracksImportPhase.requestingDownloadLink,
      MultiTracksImportPhase.downloading,
      MultiTracksImportPhase.validating,
      MultiTracksImportPhase.extracting,
      MultiTracksImportPhase.transcoding,
      MultiTracksImportPhase.saving,
    ]));
    expect(updates.where((u) => u.phase == MultiTracksImportPhase.transcoding).map((u) => u.stemLabel), contains('Bass'));
    final (imported, origin) = published.single;
    expect(imported.track.channels.map((c) => c.label), ['Click', 'Bass']);
    expect(imported.track.channels.first.isClickOrGuide, isTrue);
    expect(transcoder.calls, 2);
    expect(origin.contentId, 202);
    expect(origin.keyId, 30);
    expect(origin.contentType, 26);
    expect(origin.stemsVersion, '5');
    expect(origin.lastValidatedAt, DateTime.utc(2026, 10, 15));
    expect(stagingIsEmpty(), isTrue);
    expect(updates.any((u) => (u.message ?? '').contains('https://')), isFalse);
  });

  test('cancelling the rental confirmation never calls redeemRental', () async {
    final download = FakeDownloadTransport(package);
    api.handlers['content/download'] = contentHandler(metadata: contentResponse, link: contentResponse);
    var asked = 0;

    final job = await coordinator(download: download).start(MultiTracksImportRequest(details()), confirmRental: (prompt) async {
      asked++;
      expect(prompt.title, 'Synthetic Song');
      expect(prompt.keyTitle, 'G');
      expect(prompt.rentalsRemaining, 2);
      expect(updates.last.phase, MultiTracksImportPhase.awaitingRentalConfirmation);
      return false;
    });

    expect(asked, 1);
    expect(job.phase, MultiTracksImportPhase.cancelled);
    expect(api.redeemCalls, 0);
    expect(download.opens, 0);
    expect(published, isEmpty);
  });

  test('confirmed rental redeems exactly once and records the rental', () async {
    api.handlers['content/download'] = contentHandler(
      metadata: contentResponse,
      link: contentResponse,
      redeem: () => contentResponse(downloadUrl: syntheticDownloadUrl, rentalsInfo: {
        'status': 2,
        'rentalDateExpiration': '2026-10-22T03:40:00Z',
      }),
    );

    final job = await coordinator().start(MultiTracksImportRequest(details()), confirmRental: (_) async => true);

    expect(job.phase, MultiTracksImportPhase.completed);
    expect(job.rentalRedeemed, isTrue);
    expect(api.redeemCalls, 1);
    expect(published.single.$2.entitlementKind, MultiTracksEntitlementKind.rental);
    expect(published.single.$2.entitlementExpiresAt, DateTime.utc(2026, 10, 22, 3, 40));
  });

  test('a lost redeem response is reconciled without redeeming again, even on retry', () async {
    api.handlers['content/download'] = contentHandler(
      metadata: contentResponse,
      link: contentResponse,
      redeem: () => throw TimeoutException('synthetic'),
    );
    final subject = coordinator();
    var asked = 0;
    Future<bool> confirm(MultiTracksRentalPrompt _) async {
      asked++;
      return true;
    }

    final first = await subject.start(MultiTracksImportRequest(details()), confirmRental: confirm);
    expect(first.phase, MultiTracksImportPhase.failed);
    expect(first.rentalRedeemed, isTrue);
    expect(api.redeemCalls, 1);
    expect(api.linkCalls, 2, reason: 'initial link + one reconciliation');

    final retry = await subject.start(MultiTracksImportRequest(details()), confirmRental: confirm);
    expect(retry.phase, MultiTracksImportPhase.failed);
    expect(retry.message, contains('não repete'));
    expect(asked, 1);
    expect(api.redeemCalls, 1);
  });

  test('without a link and without rental indication it fails without asking', () async {
    api.handlers['content/download'] = contentHandler(metadata: contentResponse, link: contentResponse);
    final job = await coordinator().start(MultiTracksImportRequest(details(rentalsRemaining: 0)), confirmRental: neverAsked);
    expect(job.phase, MultiTracksImportPhase.failed);
    expect(job.failedPhase, MultiTracksImportPhase.requestingDownloadLink);
    expect(api.redeemCalls, 0);
  });

  test('cancel during download stops, cleans staging and publishes nothing', () async {
    final gate = Completer<void>();
    final downloading = Completer<void>();
    api.handlers['content/download'] =
        contentHandler(metadata: contentResponse, link: () => contentResponse(downloadUrl: syntheticDownloadUrl));
    final subject = coordinator(download: FakeDownloadTransport(package, gate: gate));
    final running = subject.start(MultiTracksImportRequest(details()), confirmRental: neverAsked);
    while (!updates.any((u) => u.phase == MultiTracksImportPhase.downloading && u.receivedBytes > 0)) {
      await Future<void>.delayed(const Duration(milliseconds: 5));
    }
    downloading.complete();
    expect(subject.isActive('202:30'), isTrue);
    expect(identical(subject.start(MultiTracksImportRequest(details()), confirmRental: neverAsked), running), isTrue,
        reason: 'one active job per contentId:keyId');
    subject.cancel('202:30');
    gate.complete();

    final job = await running;
    expect(job.phase, MultiTracksImportPhase.cancelled);
    expect(published, isEmpty);
    expect(stagingIsEmpty(), isTrue);
    expect(api.linkCalls, 1);
  });

  test('MD5 mismatch fails at download and leaves nothing behind', () async {
    api.handlers['content/download'] =
        contentHandler(metadata: contentResponse, link: () => contentResponse(downloadUrl: syntheticDownloadUrl));
    final job = await coordinator(download: FakeDownloadTransport(package, contentMd5: 'AAAAAAAAAAAAAAAAAAAAAA=='))
        .start(MultiTracksImportRequest(details()), confirmRental: neverAsked);
    expect(job.phase, MultiTracksImportPhase.failed);
    expect(job.failedPhase, MultiTracksImportPhase.downloading);
    expect(job.message, contains('MD5'));
    expect(published, isEmpty);
    expect(stagingIsEmpty(), isTrue);
  });

  test('a package missing a described file never reaches the library', () async {
    api.handlers['content/download'] = contentHandler(
      metadata: contentResponse,
      link: () => contentResponse(downloadUrl: syntheticDownloadUrl, stems: [stem(301, 'Click')]),
    );
    final job = await coordinator().start(MultiTracksImportRequest(details()), confirmRental: neverAsked);
    expect(job.phase, MultiTracksImportPhase.failed);
    expect(published, isEmpty);
    expect(stagingIsEmpty(), isTrue);
  });

  test('insufficient free space stops before converting', () async {
    api.handlers['content/download'] =
        contentHandler(metadata: contentResponse, link: () => contentResponse(downloadUrl: syntheticDownloadUrl));
    final job = await coordinator(freeBytes: (_) async => 10).start(MultiTracksImportRequest(details()), confirmRental: neverAsked);
    expect(job.phase, MultiTracksImportPhase.failed);
    expect(job.message, contains('Espaço insuficiente'));
    expect(transcoder.calls, 0);
  });

  test('logout during the link request discards the response', () async {
    final answer = Completer<void>();
    api.handlers['content/download'] = (body) async {
      await answer.future;
      return ok(contentResponse(downloadUrl: syntheticDownloadUrl));
    };
    final running = coordinator().start(MultiTracksImportRequest(details()), confirmRental: neverAsked);
    await Future<void>.delayed(Duration.zero);
    content.clearSession();
    answer.complete();
    final job = await running;
    expect(job.phase, MultiTracksImportPhase.failed);
    expect(job.message, contains('sessão'));
    expect(published, isEmpty);
  });
}
