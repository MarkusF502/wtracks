import 'dart:async';
import 'dart:convert';
import 'dart:io';

import 'package:flutter_app/services/multitracks_content_provider.dart';
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
  const selection = MultiTracksContentSelection(
    contentId: 202,
    contentType: 26,
    keyId: 30,
  );
  final profile = MultiTracksClientProfile(
    baseUrl: Uri.parse('https://api.multitracks.com/playback/'),
    userAgent: 'synthetic-agent',
    acceptLanguage: 'pt-BR;q=1.0',
  );

  test('content builders keep metadata, link and redemption distinct', () {
    const builder = MultiTracksContentRequestBuilder(context);

    final metadata = _singleItem(builder.metadata(selection));
    expect(metadata['metadata'], isTrue);
    expect(metadata['downloadLink'], isFalse);
    expect(metadata['redeemRental'], isFalse);
    expect(metadata.containsKey('redemptionID'), isFalse);

    final link = _singleItem(builder.downloadLink(selection));
    expect(link['downloadLink'], isTrue);
    expect(link['redeemRental'], isFalse);
    expect(link['redemptionID'], 0);

    final redeem = _singleItem(builder.redeemRental(selection));
    expect(redeem['downloadLink'], isTrue);
    expect(redeem['redeemRental'], isTrue);
    expect(redeem['redemptionID'], 0);
  });

  test('captured content response parses link and stem metadata', () async {
    final fixture = await File(
      'test/fixtures/multitracks/content_download_link.json',
    ).readAsString();
    final response = MultiTracksContentResponse.fromJson(
      (jsonDecode(fixture) as Map).cast<String, Object?>(),
    );

    expect(response.isSuccess, isTrue);
    expect(response.rentalsRemaining, 2);
    expect(response.items.single.downloadUrl, startsWith('https://'));
    expect(response.items.single.playOfTheWeek, isTrue);
    expect(response.items.single.stems.single.part, 'Click');
    expect(response.items.single.stems.single.clickOrGuide, isTrue);
  });

  test('provider sends link request without redeeming', () async {
    final transport = _ImmediateTransport(_successResponse());
    final provider = MultiTracksContentProvider(
      transport: transport,
      profile: profile,
    )..replaceSession(context);

    final response = await provider.requestDownloadLink(selection);

    expect(response.isSuccess, isTrue);
    expect(transport.route, 'content/download');
    final item = _singleItemFromBody(transport.body!);
    expect(item['downloadLink'], isTrue);
    expect(item['redeemRental'], isFalse);
  });

  test('response from an obsolete session is discarded', () async {
    final transport = _DeferredTransport();
    final provider = MultiTracksContentProvider(
      transport: transport,
      profile: profile,
    )..replaceSession(context);

    final pending = provider.consultMetadata(selection);
    provider.clearSession();
    transport.complete(_successResponse());

    await expectLater(pending, throwsA(isA<MultiTracksStaleSession>()));
  });
}

Map<String, Object?> _singleItem(MultiTracksLibraryRequest request) =>
    _singleItemFromBody(request.body);

Map<String, Object?> _singleItemFromBody(Map<String, Object?> body) =>
    ((body['items'] as List).single as Map).cast<String, Object?>();

MultiTracksJsonResponse _successResponse() =>
    const MultiTracksJsonResponse(200, {
      'data': {
        'rentalsRemaining': 2,
        'rentalsPreviews': 1,
        'items': [
          {'contentID': 202},
        ],
      },
      'result': 1,
      'errorCode': 0,
    });

class _ImmediateTransport implements MultiTracksJsonTransport {
  _ImmediateTransport(this.response);

  final MultiTracksJsonResponse response;
  String? route;
  Map<String, Object?>? body;

  @override
  Future<MultiTracksJsonResponse> post(
    MultiTracksClientProfile profile,
    String route,
    Map<String, Object?> body,
  ) async {
    this.route = route;
    this.body = body;
    return response;
  }
}

class _DeferredTransport implements MultiTracksJsonTransport {
  final _completer = Completer<MultiTracksJsonResponse>();

  void complete(MultiTracksJsonResponse response) =>
      _completer.complete(response);

  @override
  Future<MultiTracksJsonResponse> post(
    MultiTracksClientProfile profile,
    String route,
    Map<String, Object?> body,
  ) => _completer.future;
}
