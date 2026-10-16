import 'package:flutter/foundation.dart';

import '../services/multitracks_contract.dart';

/// Sessão MultiTracks aceita pelo login. O [hash] é a credencial das chamadas seguintes: só vive em memória e no
/// armazenamento seguro, nunca em logs, JSON de música ou diagnósticos.
@immutable
class MultiTracksSession {
  final String hash;
  final int customerId, userAccessId, countryId;
  final int? siteId;
  final bool restricted;
  final int build;
  final String language;

  /// Primeiro nome devolvido pelo login, só para exibir "Conectado como".
  final String? displayName;

  /// O login trouxe mais de uma organização; o WTracks usa a padrão da conta (seleção ainda não capturada).
  final bool hasMultipleOrganizations;

  const MultiTracksSession({
    required this.hash,
    required this.customerId,
    required this.userAccessId,
    required this.countryId,
    required this.restricted,
    required this.build,
    required this.language,
    this.siteId,
    this.displayName,
    this.hasMultipleOrganizations = false,
  });

  MultiTracksLibraryContext toContext() => MultiTracksLibraryContext(
        hash: hash,
        customerId: customerId,
        userAccessId: userAccessId,
        countryId: countryId,
        build: build,
        restricted: restricted,
        language: language,
        siteId: siteId,
      );

  /// Formato do armazenamento seguro (não é o JSON da API).
  Map<String, Object?> toStorageJson() => {
        'hash': hash,
        'customerId': customerId,
        'userAccessId': userAccessId,
        'countryId': countryId,
        if (siteId != null) 'siteId': siteId,
        'restricted': restricted,
        'build': build,
        'language': language,
        if (displayName != null) 'displayName': displayName,
        'hasMultipleOrganizations': hasMultipleOrganizations,
      };

  static MultiTracksSession? fromStorageJson(Object? json) {
    if (json is! Map) return null;
    final hash = json['hash'], customer = json['customerId'], access = json['userAccessId'], country = json['countryId'];
    final restricted = json['restricted'], build = json['build'], language = json['language'], site = json['siteId'];
    if (hash is! String || hash.isEmpty || customer is! int || access is! int || country is! int) return null;
    if (restricted is! bool || build is! int || language is! String || (site != null && site is! int)) return null;
    final name = json['displayName'];
    return MultiTracksSession(
      hash: hash,
      customerId: customer,
      userAccessId: access,
      countryId: country,
      siteId: site as int?,
      restricted: restricted,
      build: build,
      language: language,
      displayName: name is String ? name : null,
      hasMultipleOrganizations: json['hasMultipleOrganizations'] == true,
    );
  }

  @override
  String toString() => 'MultiTracksSession(<redigida>)';
}

/// Resultado do login, interpretado pelos códigos de negócio (HTTP 200 sozinho não comprova sucesso).
sealed class MultiTracksLoginOutcome {
  const MultiTracksLoginOutcome();
}

class MultiTracksLoginAccepted extends MultiTracksLoginOutcome {
  final MultiTracksSession session;
  const MultiTracksLoginAccepted(this.session);
}

/// `result: 5`, `errorCode: 4` (confirmado em 2026-10-15). O `hash` que acompanha essa resposta não é sessão válida.
class MultiTracksLoginDeviceLimit extends MultiTracksLoginOutcome {
  final String? serverMessage;
  const MultiTracksLoginDeviceLimit(this.serverMessage);
}

/// Recusa de negócio sem código conhecido (credenciais inválidas, falta de permissão…): mostra a mensagem do servidor.
class MultiTracksLoginRejected extends MultiTracksLoginOutcome {
  final int? result, errorCode;
  final String? serverMessage;
  const MultiTracksLoginRejected({this.result, this.errorCode, this.serverMessage});
}

/// Login aceito, mas sem algum campo do contexto validado nas consultas (não dá para montar as chamadas seguintes).
class MultiTracksLoginIncomplete extends MultiTracksLoginOutcome {
  const MultiTracksLoginIncomplete();
}

/// Mensagem curta do servidor, segura para exibir: sem quebras, sem endereços de e-mail e com tamanho limitado.
String? safeServerMessage(Object? value) {
  if (value is! String) return null;
  final text = value.replaceAll(RegExp(r'\s+'), ' ').trim();
  if (text.isEmpty || text.contains('@') || text.contains('://')) return null;
  return text.length <= 200 ? text : '${text.substring(0, 197)}…';
}
