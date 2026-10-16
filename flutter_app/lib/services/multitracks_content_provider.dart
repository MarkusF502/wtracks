import 'dart:convert';
import 'dart:io';

import 'multitracks_contract.dart';

class MultiTracksClientProfile {
  const MultiTracksClientProfile({
    required this.baseUrl,
    required this.userAgent,
    required this.acceptLanguage,
  });

  final Uri baseUrl;
  final String userAgent;
  final String acceptLanguage;
}

class MultiTracksJsonResponse {
  const MultiTracksJsonResponse(this.statusCode, this.body);

  final int statusCode;
  final Map<String, Object?> body;
}

abstract class MultiTracksJsonTransport {
  Future<MultiTracksJsonResponse> post(
    MultiTracksClientProfile profile,
    String route,
    Map<String, Object?> body,
  );
}

class IoMultiTracksJsonTransport implements MultiTracksJsonTransport {
  IoMultiTracksJsonTransport({HttpClient? client})
    : _client = client ?? HttpClient();

  final HttpClient _client;

  @override
  Future<MultiTracksJsonResponse> post(
    MultiTracksClientProfile profile,
    String route,
    Map<String, Object?> body,
  ) async {
    final request = await _client.postUrl(profile.baseUrl.resolve(route));
    request.headers.set(
      HttpHeaders.contentTypeHeader,
      'application/json; charset=utf-8',
    );
    request.headers.set(HttpHeaders.userAgentHeader, profile.userAgent);
    request.headers.set(HttpHeaders.acceptHeader, '*/*');
    request.headers.set(
      HttpHeaders.acceptLanguageHeader,
      profile.acceptLanguage,
    );
    request.headers.set(HttpHeaders.acceptEncodingHeader, 'identity');
    final bytes = utf8.encode(jsonEncode(body));
    request.contentLength = bytes.length;
    request.add(bytes);
    final response = await request.close().timeout(
      const Duration(seconds: 120),
    );
    final text = await response.transform(utf8.decoder).join();
    final decoded = jsonDecode(text);
    if (decoded is! Map) {
      throw const FormatException('MultiTracks response is not an object');
    }
    return MultiTracksJsonResponse(
      response.statusCode,
      decoded.cast<String, Object?>(),
    );
  }

  void close({bool force = false}) => _client.close(force: force);
}

class MultiTracksStaleSession implements Exception {
  const MultiTracksStaleSession();
}

class MultiTracksHttpFailure implements Exception {
  const MultiTracksHttpFailure(this.statusCode);

  final int statusCode;
}

class MultiTracksContentProvider {
  factory MultiTracksContentProvider({
    required MultiTracksJsonTransport transport,
    required MultiTracksClientProfile profile,
  }) => MultiTracksContentProvider._(transport, profile);

  MultiTracksContentProvider._(this._transport, this._profile);

  final MultiTracksJsonTransport _transport;
  final MultiTracksClientProfile _profile;
  MultiTracksLibraryContext? _context;
  int _generation = 0;

  bool get hasSession => _context != null;

  void replaceSession(MultiTracksLibraryContext context) {
    _context = context;
    _generation++;
  }

  void clearSession() {
    _context = null;
    _generation++;
  }

  Future<MultiTracksContentResponse> consultMetadata(
    MultiTracksContentSelection selection,
  ) => _request((builder) => builder.metadata(selection));

  Future<MultiTracksContentResponse> requestDownloadLink(
    MultiTracksContentSelection selection,
  ) => _request((builder) => builder.downloadLink(selection));

  Future<MultiTracksContentResponse> redeemRental(
    MultiTracksContentSelection selection,
  ) => _request((builder) => builder.redeemRental(selection));

  Future<MultiTracksContentResponse> _request(
    MultiTracksLibraryRequest Function(MultiTracksContentRequestBuilder) build,
  ) async {
    final context = _context;
    if (context == null) throw const MultiTracksStaleSession();
    final generation = _generation;
    final request = build(MultiTracksContentRequestBuilder(context));
    final response = await _transport.post(
      _profile,
      request.route,
      request.body,
    );
    if (generation != _generation || !identical(context, _context)) {
      throw const MultiTracksStaleSession();
    }
    if (response.statusCode != HttpStatus.ok) {
      throw MultiTracksHttpFailure(response.statusCode);
    }
    return MultiTracksContentResponse.fromJson(response.body);
  }
}
