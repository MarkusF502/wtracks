import 'dart:convert';

import 'package:flutter_app/models/multitracks_origin.dart';
import 'package:flutter_app/models/multitracks_session.dart';
import 'package:flutter_app/models/multitracks_song_details.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/services/multitracks_auth_service.dart';
import 'package:flutter_app/services/multitracks_contract.dart';
import 'package:flutter_app/services/multitracks_session_store.dart';
import 'package:flutter_test/flutter_test.dart';

import 'support/multitracks_fakes.dart';

void main() {
  group('Track.origin', () {
    final origin = MultiTracksOrigin(
      contentId: 202,
      libraryId: 101,
      keyId: 30,
      contentType: 26,
      stemsVersion: '5',
      entitlementKind: MultiTracksEntitlementKind.weekly,
      entitlementExpiresAt: DateTime.utc(2026, 10, 22, 3, 40),
      lastValidatedAt: DateTime.utc(2026, 10, 15, 12),
    );

    test('songs saved before the field still open', () {
      final track = Track.fromJson({
        'id': 'old',
        'title': 'Antiga',
        'channels': [
          {'label': 'Click', 'filePath': '/x/click.wav'},
        ],
      });
      expect(track.origin, isNull);
      expect(track.toJson().containsKey('origin'), isFalse);
    });

    test('round-trips without credentials, URLs or device identity', () {
      final track = Track(id: 'multitracks-202-30', title: 'T', channels: const [], origin: origin);
      final json = jsonDecode(jsonEncode(track.toJson())) as Map<String, dynamic>;
      expect(Track.fromJson(json).origin, origin);
      final text = jsonEncode(json['origin']);
      for (final forbidden in ['hash', 'password', 'downloadUrl', 'deviceIdentifier', 'https://']) {
        expect(text.contains(forbidden), isFalse, reason: forbidden);
      }
    });

    test('unknown providers and incomplete origins are ignored, copyWith can clear', () {
      expect(MultiTracksOrigin.fromJson({'provider': 'other', 'contentId': 1}), isNull);
      expect(MultiTracksOrigin.fromJson({'provider': 'multitracks', 'contentId': 1}), isNull);
      final track = Track(id: 'a', title: 'a', channels: const [], origin: origin);
      expect(track.copyWith(title: 'b').origin, origin);
      expect(track.copyWith(origin: null).origin, isNull);
    });

    test('only zoned, non-sentinel dates become an expiry', () {
      expect(MultiTracksOrigin.parseZonedDate('2026-10-22T03:40:00Z'), DateTime.utc(2026, 10, 22, 3, 40));
      expect(MultiTracksOrigin.parseZonedDate('2026-10-22T00:40:00-03:00'), DateTime.utc(2026, 10, 22, 3, 40));
      expect(MultiTracksOrigin.parseZonedDate('2026-10-22T03:40:00'), isNull);
      expect(MultiTracksOrigin.parseZonedDate('0001-01-01T00:00:00Z'), isNull);
      expect(MultiTracksOrigin.parseZonedDate('1900-01-01T00:00:00Z'), isNull);
      expect(origin.isExpiredAt(DateTime.utc(2026, 10, 22, 3, 39)), isFalse);
      expect(origin.isExpiredAt(DateTime.utc(2026, 10, 22, 3, 40)), isTrue);
    });
  });

  group('login', () {
    test('success needs result 1, errorCode 0, a hash and the organization context', () {
      final outcome = interpretLogin(loginSuccess(), build: 86204, language: 'pt');
      expect(outcome, isA<MultiTracksLoginAccepted>());
      final session = (outcome as MultiTracksLoginAccepted).session;
      expect(session.toContext().siteId, 40);
      expect(session.displayName, 'Pessoa');
      expect(session.hasMultipleOrganizations, isFalse);
      expect(session.toString(), isNot(contains('synthetic-session-hash')));
    });

    test('device limit is not a session even when a hash comes along', () {
      final outcome = interpretLogin({...loginSuccess(), 'result': 5, 'errorCode': 4, 'message': 'Remova um aparelho'},
          build: 1, language: 'pt');
      expect(outcome, isA<MultiTracksLoginDeviceLimit>());
      expect((outcome as MultiTracksLoginDeviceLimit).serverMessage, 'Remova um aparelho');
    });

    test('other refusals keep a safe server message', () {
      final outcome = interpretLogin({'result': 3, 'errorCode': 1, 'hash': null, 'message': 'Invalid user x@y.z'},
          build: 1, language: 'pt');
      expect(outcome, isA<MultiTracksLoginRejected>());
      expect((outcome as MultiTracksLoginRejected).serverMessage, isNull, reason: 'messages with e-mails are hidden');
      expect(interpretLogin({...loginSuccess(), 'customerID': null}, build: 1, language: 'pt'), isA<MultiTracksLoginIncomplete>());
    });

    test('several organizations are flagged, not selected', () {
      final outcome = interpretLogin(loginSuccess(organizations: [{}, {}]), build: 1, language: 'pt') as MultiTracksLoginAccepted;
      expect(outcome.session.hasMultipleOrganizations, isTrue);
    });

    test('authenticate sends the eight captured fields with integer build and platform', () async {
      final transport = ScriptedJsonTransport()..handlers['authenticate'] = (_) => ok(loginSuccess());
      final service = MultiTracksAuthService(transport: transport, identity: MultiTracksClientIdentity.transitionalPlayback);
      await service.authenticate(username: 'user', password: 'secret', deviceIdentifier: 'DEVICE');
      final body = transport.calls.single.$2;
      expect(body.keys.toSet(),
          {'username', 'password', 'build', 'language', 'deviceName', 'deviceIdentifier', 'application', 'platform'});
      expect(body['build'], 86204);
      expect(body['platform'], 1);
      expect(body['deviceIdentifier'], 'DEVICE');
    });
  });

  group('session store', () {
    test('keeps session and a stable device id, never the password', () async {
      final secure = InMemoryMultiTracksSecureStore();
      final store = MultiTracksSessionStore(secure);
      final session = (interpretLogin(loginSuccess(), build: 86204, language: 'pt') as MultiTracksLoginAccepted).session;
      await store.saveSession(session);
      final first = await store.deviceIdentifier();
      expect(await store.deviceIdentifier(), first);
      expect((await store.loadSession())!.hash, session.hash);
      expect(secure.values.values.any((v) => v.contains('secret')), isFalse);
      await store.clearSession();
      expect(await store.loadSession(), isNull);
      expect(await store.deviceIdentifier(), first, reason: 'logout keeps the device identity');
    });

    test('without secure storage it refuses instead of inventing an identity', () {
      final store = MultiTracksSessionStore(null);
      expect(store.isAvailable, isFalse);
      expect(store.deviceIdentifier, throwsA(isA<MultiTracksSecureStorageUnavailable>()));
    });
  });

  group('song details', () {
    const selection = MultiTracksContentSelection(contentId: 202, contentType: 26, keyId: 30);

    test('lists only valid keys and the selected key tracks in API order', () {
      final details = MultiTracksSongDetails.from(selection, MultiTracksContentResponse.fromJson(contentResponse()));
      expect(details.keys.map((k) => k.title), ['G', 'A']);
      expect(details.selectedKeyTitle, 'G');
      expect(details.stemsForSelectedKey.map((s) => s.stemId), [301, 302]);
      expect(details.stemsForSelectedKey.first.clickOrGuide, isTrue);
      expect(details.bpm, 72);
      expect(details.stemsVersion, '5');
      expect(details.entitlement.kind, MultiTracksEntitlementKind.unknown);
      expect(details.rentalPossible, isTrue);
    });

    test('entitlement only from direct evidence', () {
      MultiTracksEntitlement of(Map<String, Object?> json, [MultiTracksSongSummary? summary]) =>
          MultiTracksSongDetails.from(selection, MultiTracksContentResponse.fromJson(json), summary: summary).entitlement;
      final weekly = of(contentResponse(playOfTheWeek: true, rentalsInfo: {'rentalDateExpiration': '2026-10-22T03:40:00Z'}));
      expect(weekly.kind, MultiTracksEntitlementKind.weekly);
      expect(weekly.expiresAt, DateTime.utc(2026, 10, 22, 3, 40));
      expect(of(contentResponse(rentalsInfo: {'status': 2})).kind, MultiTracksEntitlementKind.rental);
      final purchased = MultiTracksSongSummary.fromJson(songSummary(1, purchased: '2026-01-01T00:00:00Z'));
      expect(of(contentResponse(), purchased).kind, MultiTracksEntitlementKind.owned);
    });

    test('disk estimate never overflows and is zero without a size', () {
      expect(estimateImportBytes(0), 0);
      expect(estimateImportBytes(-5), 0);
      expect(estimateImportBytes(100), 100 * 27);
      expect(estimateImportBytes(1 << 62), greaterThan(0));
    });
  });
}
