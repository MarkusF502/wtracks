import 'dart:io';

import '../models/multitracks_session.dart';
import 'multitracks_content_provider.dart';

/// Perfil de cliente do login. A MultiTracks autorizou, como compatibilidade transitória, o perfil Playback/iOS
/// capturado do Playback 8.6.2 (ver docs/playback-analysis/multitracks-api-contract.md). Não afirma que o WTracks seja o
/// aplicativo oficial; o identificador do aparelho é o do próprio WTracks.
class MultiTracksClientIdentity {
  final String application, deviceName, language, appVersion, iosVersion, alamofireVersion, acceptLanguage;
  final int platform, build;
  final Uri baseUrl;

  const MultiTracksClientIdentity({
    required this.application,
    required this.deviceName,
    required this.language,
    required this.platform,
    required this.build,
    required this.appVersion,
    required this.iosVersion,
    required this.alamofireVersion,
    required this.acceptLanguage,
    required this.baseUrl,
  });

  static final transitionalPlayback = MultiTracksClientIdentity(
    application: 'iPhone12,1',
    deviceName: 'iPhone 11 (26.2)',
    language: 'pt',
    platform: 1,
    build: 86204,
    appVersion: '8.6.2',
    iosVersion: '26.2.0',
    alamofireVersion: '5.11.2',
    acceptLanguage: 'pt-BR;q=1.0',
    baseUrl: Uri.parse('https://api.multitracks.com/playback/'),
  );

  String get userAgent =>
      'Playback/$appVersion (com.multitracks.custommixplayer; build:$build; iOS $iosVersion) Alamofire/$alamofireVersion';

  MultiTracksClientProfile get profile =>
      MultiTracksClientProfile(baseUrl: baseUrl, userAgent: userAgent, acceptLanguage: acceptLanguage);
}

/// `POST authenticate` e interpretação do envelope. A senha só existe nos argumentos desta chamada.
class MultiTracksAuthService {
  MultiTracksAuthService({required this.transport, required this.identity});

  final MultiTracksJsonTransport transport;
  final MultiTracksClientIdentity identity;

  Future<MultiTracksLoginOutcome> authenticate({
    required String username,
    required String password,
    required String deviceIdentifier,
  }) async {
    final response = await transport.post(identity.profile, 'authenticate', {
      'username': username,
      'password': password,
      'build': identity.build,
      'language': identity.language,
      'deviceName': identity.deviceName,
      'deviceIdentifier': deviceIdentifier,
      'application': identity.application,
      'platform': identity.platform,
    });
    if (response.statusCode != HttpStatus.ok) throw MultiTracksHttpFailure(response.statusCode);
    return interpretLogin(response.body, build: identity.build, language: identity.language);
  }
}

/// Interpreta a resposta do login sem confiar em HTTP 200: exige `result: 1`, `errorCode: 0`, `hash` não vazio e o
/// contexto de nível superior que as consultas de biblioteca validaram.
MultiTracksLoginOutcome interpretLogin(Map<String, Object?> json, {required int build, required String language}) {
  final result = json['result'], errorCode = json['errorCode'];
  final message = safeServerMessage(json['message']);
  if (result == 5 && errorCode == 4) return MultiTracksLoginDeviceLimit(message);
  final hash = json['hash'];
  if (result != 1 || errorCode != 0 || hash is! String || hash.isEmpty) {
    return MultiTracksLoginRejected(
      result: result is int ? result : null,
      errorCode: errorCode is int ? errorCode : null,
      serverMessage: message,
    );
  }
  final customer = json['customerID'], access = json['userAccessID'], country = json['countryID'];
  final restricted = json['restricted'], site = json['siteID'];
  if (customer is! int || access is! int || country is! int || restricted is! bool || (site != null && site is! int)) {
    return const MultiTracksLoginIncomplete();
  }
  final organizations = json['organizations'];
  final firstName = json['firstName'];
  return MultiTracksLoginAccepted(MultiTracksSession(
    hash: hash,
    customerId: customer,
    userAccessId: access,
    countryId: country,
    siteId: site as int?,
    restricted: restricted,
    build: build,
    language: language,
    displayName: firstName is String && firstName.trim().isNotEmpty ? firstName.trim() : null,
    hasMultipleOrganizations: organizations is List && organizations.length > 1,
  ));
}
