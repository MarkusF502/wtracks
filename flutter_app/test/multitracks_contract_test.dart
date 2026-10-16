import 'dart:convert';
import 'dart:io';

import 'package:flutter_app/services/multitracks_contract.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  const context = MultiTracksLibraryContext(
    hash: 'session-hash',
    customerId: 10,
    userAccessId: 20,
    countryId: 30,
    build: 86204,
    restricted: false,
    language: 'pt',
    siteId: 40,
  );
  const builder = MultiTracksLibraryRequestBuilder(context);

  test('songs reproduces the captured route-specific contract', () {
    final request = builder.songs(pageSize: 4, filter: 4);

    expect(request.route, 'library/songs');
    expect(request.body, {
      'hash': 'session-hash',
      'customerID': 10,
      'userAccessID': 20,
      'countryID': 30,
      'build': 86204,
      'pageNumber': 1,
      'pageSize': 4,
      'restricted': false,
      'language': 'pt',
      'search': '',
      'filter': 4,
      'sort': 3,
      'sortDirection': 2,
      'siteID': 40,
    });
  });

  test('artists and albums use purchased-content sorting', () {
    for (final request in [builder.artists(), builder.albums()]) {
      expect(request.body['purchasedContent'], isTrue);
      expect(request.body['sort'], 2);
      expect(request.body['sortDirection'], 1);
      expect(request.body['siteID'], 40);
      expect(request.body['customer'], isNull);
    }
  });

  test('themes and genres omit sort and siteID as captured', () {
    for (final request in [builder.themes(), builder.genres()]) {
      expect(request.body['purchasedContent'], isTrue);
      expect(request.body['sortDirection'], 1);
      expect(request.body.containsKey('sort'), isFalse);
      expect(request.body.containsKey('siteID'), isFalse);
    }
  });

  test('default exploration contains only the five read-only routes', () {
    expect(builder.defaultExploration().map((request) => request.route), [
      'library/songs',
      'library/artists',
      'library/albums',
      'library/themes',
      'library/genres',
    ]);
  });

  test('routes that need siteID reject a missing site context', () {
    const withoutSite = MultiTracksLibraryRequestBuilder(
      MultiTracksLibraryContext(
        hash: 'session-hash',
        customerId: 10,
        userAccessId: 20,
        countryId: 30,
        build: 86204,
        restricted: false,
        language: 'pt',
      ),
    );

    expect(withoutSite.songs, throwsStateError);
    expect(withoutSite.artists, throwsStateError);
    expect(withoutSite.albums, throwsStateError);
    expect(withoutSite.themes, returnsNormally);
    expect(withoutSite.genres, returnsNormally);
  });

  test('empty captured page is successful and ends pagination', () async {
    final fixture = await File(
      'test/fixtures/multitracks/library_empty_success.json',
    ).readAsString();
    final envelope = MultiTracksPageEnvelope.fromJson(
      (jsonDecode(fixture) as Map).cast<String, Object?>(),
    );

    expect(envelope.isSuccess, isTrue);
    expect(envelope.data, isEmpty);
    expect(envelope.pageNumber, 0);
    expect(envelope.hasNextPage, isFalse);
  });

  test('non-empty synthetic page can request the next page', () {
    final envelope = MultiTracksPageEnvelope.fromJson({
      'data': [
        {'contentID': 1},
      ],
      'pageNumber': 1,
      'totalPages': 2,
      'totalRecords': 2,
      'result': 1,
      'errorCode': 0,
    });

    expect(envelope.hasNextPage, isTrue);
  });

  test(
    'captured non-empty song schema parses from a synthetic fixture',
    () async {
      final fixture = await File(
        'test/fixtures/multitracks/library_songs_page.json',
      ).readAsString();
      final envelope = MultiTracksPageEnvelope.fromJson(
        (jsonDecode(fixture) as Map).cast<String, Object?>(),
      );
      final song = MultiTracksSongSummary.fromJson(
        (envelope.data.single as Map).cast<String, Object?>(),
      );

      expect(song.libraryId, 101);
      expect(song.songId, 202);
      expect(song.song, 'Synthetic Song');
      expect(song.dateContentPurchased, isNull);
      expect(song.rentalsAvailable, isTrue);
      expect(song.cloudSong, isFalse);
      expect(envelope.hasNextPage, isFalse);
    },
  );

  test('song schema changes fail closed', () {
    expect(
      () => MultiTracksSongSummary.fromJson({
        'libraryID': 101,
        'songID': 202,
        'song': 'Synthetic Song',
        'songStatus': 1,
        'artistID': 303,
        'artist': 'Synthetic Artist',
        'albumID': 404,
        'album': 'Synthetic Album',
        'image': 'https://example.invalid/image.jpg',
        'image2x': 'https://example.invalid/image@2x.jpg',
        'previewUrl': 'https://example.invalid/preview.m4a',
        'dateContentPurchased': 123,
        'rentalsAvailable': true,
        'cloudSong': false,
      }),
      throwsFormatException,
    );
  });

  test('schema changes fail closed', () {
    expect(
      () => MultiTracksPageEnvelope.fromJson({
        'data': const [],
        'pageNumber': '0',
        'totalPages': 0,
        'totalRecords': 0,
        'result': 1,
        'errorCode': 0,
      }),
      throwsFormatException,
    );
  });
}
