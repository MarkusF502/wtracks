// Teste de comunicação com a API do Playback (Fase 6.1.1). VOCÊ executa este programa no seu terminal:
//
//   dart tool/multitracks_probe.dart --site multitracks --out ~/multitracks-schema.txt
//   dart tool/multitracks_probe.dart --site multitracks --explore --out ~/multitracks-schema.txt
//   dart tool/multitracks_probe.dart --content-id N --content-type N --key-id N --structure-out ~/multitracks-structure.json
//
// --structure-out grava, só para análise local (fora do Git, permissão 600), os VALORES da estrutura musical da música consultada:
// duração, BPM, tom, andamentos, compassos, seções, clicks e descritores dos stems. Nada de conta, URL, hash, aluguel ou preço.
//
// - Pede usuário e senha no terminal (a senha não aparece e não é gravada em lugar nenhum).
// - Faz UM login (sem tentar de novo se falhar), consulta biblioteca com --explore e só toca conteúdo quando IDs e flags explícitos são passados.
// - Imprime e grava apenas o ESQUEMA das respostas: status HTTP, tipos e chaves. Todo valor (texto, número, id, hash, e-mail, URL) é
//   redigido. Só mensagens de erro curtas de campos chamados message/error* são mostradas.
// - Não imprime nem grava a senha, o userHash, cabeçalhos de autenticação ou cookies.
import 'dart:convert';
import 'dart:io';
import 'dart:math';

import '../flutter_app/lib/services/multitracks_contract.dart';

const _playbackApplication = 'iPhone12,1';
const _playbackPlatform = 1;
const _playbackBuild = 86204;
const _playbackDeviceName = 'iPhone 11 (26.2)';

Future<void> main(List<String> args) async {
  final options = _Options.parse(args);
  final out = StringBuffer();
  void say(String line) {
    stdout.writeln(line);
    out.writeln(line);
  }

  stdout.write('Usuário MultiTracks: ');
  final username = stdin.readLineSync()?.trim() ?? '';
  stdout.write('Senha (não aparece): ');
  final hasTerminal = stdin.hasTerminal;
  if (hasTerminal) stdin.echoMode = false;
  var password = '';
  try {
    password = stdin.readLineSync() ?? '';
  } finally {
    if (hasTerminal) stdin.echoMode = true;
  }
  stdout.writeln();
  if (username.isEmpty || password.isEmpty) {
    stderr.writeln('Usuário ou senha vazios.');
    exit(2);
  }

  final base = Uri.parse(
    options.baseUrl ?? 'https://api.${options.site}.com/playback/',
  );
  say('Base: $base');
  say(
    'Perfil de cliente autorizado: Playback ${options.appVersion} para iOS '
    '(application=${options.application}, platform=${options.platform}, build=${options.build}, deviceName=${options.deviceName})',
  );
  final client = HttpClient()..connectionTimeout = const Duration(seconds: 20);

  Future<(int, Object?)> post(String route, Map<String, Object?> body) async {
    final request = await client.postUrl(base.resolve(route));
    // Cabeçalhos observados na captura do Playback 8.6.2.
    request.headers.set(
      HttpHeaders.contentTypeHeader,
      'application/json; charset=utf-8',
    );
    request.headers.set(HttpHeaders.userAgentHeader, options.userAgent);
    request.headers.set(HttpHeaders.acceptHeader, '*/*');
    request.headers.set(
      HttpHeaders.acceptLanguageHeader,
      options.acceptLanguage,
    );
    // Dart não decodifica Brotli automaticamente. Solicita corpo sem compressão.
    request.headers.set(HttpHeaders.acceptEncodingHeader, 'identity');
    final bytes = utf8.encode(jsonEncode(body));
    // Content-Length explícito: sem ele o Dart envia o corpo em "chunked", que alguns servidores não leem ao ligar o JSON ao modelo.
    request.contentLength = bytes.length;
    say(
      '\nContent-Type enviado: ${request.headers.value(HttpHeaders.contentTypeHeader)}',
    );
    say(
      'Enviando para $route: ${bytes.length} bytes, ${body.length} chaves: '
      '${body.entries.map((e) => '${e.key}${e.value is String ? '(len=${(e.value as String).length})' : '(${e.value.runtimeType})'}').join(', ')}',
    );
    request.add(bytes);
    final response = await request.close().timeout(const Duration(seconds: 60));
    final text = await response.transform(utf8.decoder).join();
    Object? json;
    try {
      json = jsonDecode(text);
    } on FormatException {
      json = null;
    }
    say(
      '\nPOST $route -> HTTP ${response.statusCode} (${response.headers.contentType?.mimeType ?? 'sem content-type'}, '
      '${text.length} bytes, cabeçalhos: ${(<String>[]..addAll(_headerNames(response))).join(', ')})',
    );
    if (json == null)
      say(
        '  (corpo não é JSON: ${text.isEmpty ? 'vazio' : 'texto de ${text.length} caracteres, redigido'})',
      );
    return (response.statusCode, json);
  }

  final deviceId = await _deviceIdentifier();
  say(
    'Identificador do aparelho de teste: redigido (persistido no diretório pessoal; o login pode registrar o aparelho '
    '"${options.deviceName}" na sua conta MultiTracks)',
  );
  Object? login;
  try {
    // Captura real: oito campos; deviceIdentifier é texto e platform é inteiro.
    final (status, json) = await post('authenticate', {
      'username': username,
      'password': password,
      'build': options.build,
      'language': options.language,
      'deviceName': options.deviceName,
      'deviceIdentifier': deviceId,
      'application': options.application,
      'platform': options.platform,
    });
    password = ''; // a senha não é mais necessária
    login = json;
    say(_schema(json));
    if (status != 200 ||
        json is! Map ||
        json['result'] != 1 ||
        json['errorCode'] != 0 ||
        json['hash'] is! String ||
        (json['hash'] as String).isEmpty) {
      if (json is Map && json['result'] == 5 && json['errorCode'] == 4) {
        say(
          '\nLimite de dispositivos Playback atingido. Remova um aparelho obsoleto na página Playback Devices da sua conta e execute novamente. '
          'Não apague ~/.config/wtracks-probe/device-id: trocar o identificador criaria outro aparelho.',
        );
      }
      say(
        '\nO login não foi aceito. Nenhuma outra chamada foi feita e nada foi repetido.',
      );
      await _finish(options, out);
      client.close();
      return;
    }
  } on Exception catch (e) {
    say('\nFalha de rede: ${e.runtimeType}');
    await _finish(options, out);
    client.close();
    return;
  } finally {
    password = '';
  }

  if (options.explore || options.contentSelection != null) {
    final session = _Session.from(login);
    say(
      '\nDa resposta do login: hash=${session.hash == null ? 'NÃO ENCONTRADO' : 'encontrado (redigido)'}, '
      'customerID=${session.customerId == null ? 'NÃO ENCONTRADO' : 'encontrado (redigido)'}, '
      'userAccessID=${session.userAccessId == null ? 'NÃO ENCONTRADO' : 'encontrado (redigido)'}, '
      'countryID=${session.countryId == null ? 'NÃO ENCONTRADO' : 'encontrado (redigido)'}, '
      'restricted=${session.restricted == null ? 'NÃO ENCONTRADO' : 'encontrado'}, '
      'siteID=${session.siteId == null ? 'NÃO ENCONTRADO' : 'encontrado (redigido)'}',
    );
    final context = session.contentContext(options);
    if (context == null) {
      say(
        '\nA resposta não contém todo o contexto capturado para chamadas autenticadas. Nenhuma consulta foi feita.',
      );
    } else {
      if (options.explore) {
        final libraryContext = session.libraryContext(options);
        if (libraryContext == null) {
          say(
            '\nsiteID não encontrado; as consultas de biblioteca foram puladas.',
          );
        } else {
          final requests = MultiTracksLibraryRequestBuilder(
            libraryContext,
          ).defaultExploration();
          for (final request in requests) {
            try {
              final (status, json) = await post(request.route, request.body);
              say(_schema(json));
              if (status == 401 || status == 403 || status == 429) {
                say(
                  '\nO servidor recusou ou limitou (HTTP $status): parando por aqui.',
                );
                break;
              }
              if (!_businessSuccess(json)) {
                say(
                  '\nA consulta retornou erro de negócio: parando para não repetir chamadas inválidas.',
                );
                break;
              }
            } on Exception catch (e) {
              say('\nFalha em ${request.route}: ${e.runtimeType}');
              break;
            }
          }
        }
      }

      final selection = options.contentSelection;
      if (selection != null) {
        final builder = MultiTracksContentRequestBuilder(context);
        final metadataRequest = builder.metadata(selection);
        final (metadataStatus, metadataJson) = await post(
          metadataRequest.route,
          metadataRequest.body,
        );
        say(_schema(metadataJson));
        if (options.structureOut != null && metadataStatus == 200 && _businessSuccess(metadataJson)) {
          await _writeStructure(metadataJson, options.structureOut!, say);
        }
        if (metadataStatus != 200 || !_businessSuccess(metadataJson)) {
          say(
            '\nA consulta de metadados não foi aceita. Nenhum link foi solicitado e nenhum resgate foi feito.',
          );
        } else if (options.downloadContent || options.redeemRental) {
          final linkRequest = options.redeemRental
              ? builder.redeemRental(selection)
              : builder.downloadLink(selection);
          if (options.redeemRental) {
            say(
              '\nATENÇÃO: enviando uma única solicitação explícita de resgate de Rental. Ela não será repetida automaticamente.',
            );
          }
          var (linkStatus, linkJson) = await post(
            linkRequest.route,
            linkRequest.body,
          );
          say(_schema(linkJson));
          if (options.redeemRental &&
              linkStatus == 200 &&
              _businessSuccess(linkJson) &&
              _findStringByKey(linkJson, 'downloadUrl') == null) {
            say(
              '\nO resgate foi aceito sem downloadUrl. Solicitando o link uma única vez, sem repetir o resgate.',
            );
            final followUpRequest = builder.downloadLink(selection);
            (linkStatus, linkJson) = await post(
              followUpRequest.route,
              followUpRequest.body,
            );
            say(_schema(linkJson));
          }
          if (linkStatus != 200 || !_businessSuccess(linkJson)) {
            say(
              '\nO servidor não emitiu um link válido. Nenhum download foi iniciado.',
            );
          } else {
            final rawUrl = _findStringByKey(linkJson, 'downloadUrl');
            final downloadUrl = rawUrl == null ? null : Uri.tryParse(rawUrl);
            if (downloadUrl == null) {
              say(
                '\nA resposta não contém downloadUrl. Nenhum download foi iniciado.',
              );
            } else {
              try {
                final downloaded = await _downloadPackage(
                  downloadUrl,
                  Directory(options.downloadDirectory!),
                  selection.contentId,
                  say,
                );
                say(
                  '\nPacote baixado e validado: ${downloaded.path} (${await downloaded.length()} bytes).',
                );
              } on Exception catch (e) {
                say(
                  '\nFalha no download: ${e.runtimeType}. Nenhum pacote parcial foi publicado.',
                );
              }
            }
          }
        }
      }
    }
  }
  client.close();
  await _finish(options, out);
}

bool _businessSuccess(Object? json) =>
    json is Map && json['result'] == 1 && json['errorCode'] == 0;

String? _findStringByKey(Object? node, String wanted) {
  if (node is Map) {
    for (final entry in node.entries) {
      if (entry.key.toString() == wanted && entry.value is String) {
        return entry.value as String;
      }
      final nested = _findStringByKey(entry.value, wanted);
      if (nested != null) return nested;
    }
  } else if (node is List) {
    for (final item in node) {
      final nested = _findStringByKey(item, wanted);
      if (nested != null) return nested;
    }
  }
  return null;
}

Future<File> _downloadPackage(
  Uri initialUrl,
  Directory destinationDirectory,
  int contentId,
  void Function(String) say,
) async {
  const allowedHost = 'playback.blob.core.windows.net';
  const maximumBytes = 2 * 1024 * 1024 * 1024;
  void validate(Uri url) {
    if (url.scheme != 'https' || url.host != allowedHost) {
      throw StateError('URL de download não confiável');
    }
  }

  validate(initialUrl);
  final downloadClient = HttpClient()
    ..connectionTimeout = const Duration(seconds: 20);
  HttpClientResponse? response;
  var current = initialUrl;
  try {
    for (var redirects = 0; redirects <= 3; redirects++) {
      validate(current);
      final request = await downloadClient.getUrl(current);
      request.followRedirects = false;
      request.headers.set(HttpHeaders.acceptEncodingHeader, 'identity');
      response = await request.close().timeout(const Duration(seconds: 60));
      if (response.isRedirect) {
        final location = response.headers.value(HttpHeaders.locationHeader);
        await response.drain<void>();
        if (location == null || redirects == 3) {
          throw StateError('Redirecionamento inválido');
        }
        current = current.resolve(location);
        response = null;
        continue;
      }
      break;
    }
    final body = response;
    if (body == null || body.statusCode != HttpStatus.ok) {
      throw StateError('HTTP de download inesperado');
    }
    final mime = body.headers.contentType?.mimeType;
    if (mime != null && mime != ContentType.binary.mimeType) {
      throw StateError('Content-Type de download inesperado');
    }
    final announced = body.contentLength >= 0 ? body.contentLength : null;
    if (announced != null && announced > maximumBytes) {
      throw StateError('Pacote excede o limite de tamanho');
    }
    await destinationDirectory.create(recursive: true);
    final destination = File('${destinationDirectory.path}/$contentId.mtrack');
    final partial = File('${destination.path}.part');
    if (await partial.exists()) await partial.delete();
    final output = partial.openWrite();
    var received = 0;
    try {
      await for (final chunk in body) {
        received += chunk.length;
        if (received > maximumBytes) {
          throw StateError('Pacote excede o limite de tamanho');
        }
        output.add(chunk);
      }
      await output.flush();
      await output.close();
      if (announced != null && received != announced) {
        throw StateError('Download incompleto');
      }
      final expectedMd5 = body.headers.value('content-md5');
      if (expectedMd5 != null) {
        final process = await Process.run('md5sum', [partial.path]);
        if (process.exitCode != 0) {
          throw StateError('md5sum indisponível');
        }
        final actualHex = process.stdout
            .toString()
            .trim()
            .split(RegExp(r'\s+'))
            .first
            .toLowerCase();
        final expectedHex = base64Decode(
          expectedMd5,
        ).map((byte) => byte.toRadixString(16).padLeft(2, '0')).join();
        if (actualHex != expectedHex) {
          throw StateError('Content-MD5 divergente');
        }
      }
      final previous = File('${destination.path}.previous');
      if (await previous.exists()) await previous.delete();
      final hadDestination = await destination.exists();
      if (hadDestination) await destination.rename(previous.path);
      try {
        await partial.rename(destination.path);
        if (hadDestination && await previous.exists()) await previous.delete();
      } catch (_) {
        if (hadDestination && await previous.exists()) {
          await previous.rename(destination.path);
        }
        rethrow;
      }
      say('Transferência concluída; URL assinada não foi registrada.');
      return destination;
    } catch (_) {
      await output.close();
      if (await partial.exists()) await partial.delete();
      rethrow;
    }
  } finally {
    downloadClient.close(force: true);
  }
}

/// Um identificador estável para este computador (gerado uma vez): um novo a cada execução criaria um aparelho novo na conta a cada teste.
Future<String> _deviceIdentifier() async {
  final dir = Directory('${_homeDirectory()}/.config/wtracks-probe');
  final file = File('${dir.path}/device-id');
  if (await file.exists()) {
    final saved = (await file.readAsString()).trim();
    if (saved.isNotEmpty) return saved;
  }
  final random = Random.secure();
  String hex(int n) =>
      List.generate(n, (_) => random.nextInt(16).toRadixString(16)).join();
  final id =
      '${hex(8)}-${hex(4)}-4${hex(3)}-${(8 + random.nextInt(4)).toRadixString(16)}${hex(3)}-${hex(12)}'
          .toUpperCase();
  await dir.create(recursive: true);
  await file.writeAsString(id);
  return id;
}

String _homeDirectory() {
  final home =
      Platform.environment['HOME'] ?? Platform.environment['USERPROFILE'];
  if (home == null || home.isEmpty) {
    throw StateError(
      'Diretório pessoal não encontrado; não gravar identidade no repositório.',
    );
  }
  return home;
}

Iterable<String> _headerNames(HttpClientResponse response) {
  final names = <String>[];
  response.headers.forEach((name, _) => names.add(name));
  return names;
}

Future<void> _finish(_Options options, StringBuffer out) async {
  if (options.out != null) {
    await File(options.out!).writeAsString(out.toString());
    stdout.writeln(
      '\nEsquema gravado em ${options.out} (sem valores, senha nem hash).',
    );
  }
}

/// Esquema redigido: chaves e tipos; texto só para mensagens de erro curtas.
String _schema(Object? json, [int depth = 0]) {
  final pad = '  ' * (depth + 1);
  if (json is Map) {
    final lines = <String>[];
    for (final entry in json.entries) {
      final key = entry.key.toString();
      final v = entry.value;
      final lower = key.toLowerCase();
      if (v is String &&
          (lower == 'message' || lower.startsWith('error')) &&
          v.length <= 120 &&
          !v.contains('@')) {
        lines.add('$pad$key: "$v"');
      } else if (v is int &&
          (lower == 'result' ||
              lower == 'resultid' ||
              lower.startsWith('errorcode'))) {
        lines.add(
          '$pad$key: $v',
        ); // códigos de resultado/erro não são dados pessoais
      } else if (v is Map || v is List) {
        lines.add('$pad$key: ${_describe(v)}');
        if (depth < 4) lines.add(_schema(v, depth + 1));
      } else {
        lines.add('$pad$key: ${_describe(v)}');
      }
    }
    return lines.where((l) => l.isNotEmpty).join('\n');
  }
  if (json is List) {
    if (json.isEmpty) return '${pad}(lista vazia)';
    final first = json.first;
    return '${pad}[0] de ${json.length}: ${_describe(first)}\n${first is Map || first is List ? _schema(first, depth + 1) : ''}'
        .trimRight();
  }
  return '$pad${_describe(json)}';
}

String _describe(Object? v) => switch (v) {
  null => 'null',
  bool() => 'bool',
  int() => 'int',
  double() => 'double',
  String() => 'string(len=${v.length})',
  List() => 'lista(${v.length})',
  Map() => 'objeto(${v.length} chaves)',
  _ => v.runtimeType.toString(),
};

/// Procura, na resposta do login, os valores de sessão usados nas chamadas seguintes (heurística; nada é impresso).
class _Session {
  final String? hash;
  final int? customerId;
  final int? userAccessId;
  final int? countryId;
  final int? siteId;
  final bool? restricted;
  _Session(
    this.hash,
    this.customerId,
    this.userAccessId,
    this.countryId,
    this.siteId,
    this.restricted,
  );

  factory _Session.from(Object? json) {
    String? hash;
    int? customerId, userAccessId, countryId, siteId;
    bool? restricted;
    void walk(Object? node) {
      if (node is Map) {
        for (final e in node.entries) {
          final k = e.key.toString();
          final lower = k.toLowerCase();
          if (hash == null &&
              (lower == 'userhash' || lower == 'hash') &&
              e.value is String)
            hash = e.value as String;
          if (customerId == null && lower == 'customerid' && e.value is int) {
            customerId = e.value as int;
          }
          if (userAccessId == null &&
              lower == 'useraccessid' &&
              e.value is int) {
            userAccessId = e.value as int;
          }
          if (countryId == null && lower == 'countryid' && e.value is int) {
            countryId = e.value as int;
          }
          if (siteId == null && lower == 'siteid' && e.value is int) {
            siteId = e.value as int;
          }
          if (restricted == null && lower == 'restricted' && e.value is bool) {
            restricted = e.value as bool;
          }
          walk(e.value);
        }
      } else if (node is List) {
        for (final item in node) {
          walk(item);
        }
      }
    }

    walk(json);
    return _Session(
      hash,
      customerId,
      userAccessId,
      countryId,
      siteId,
      restricted,
    );
  }

  MultiTracksLibraryContext? libraryContext(_Options options) {
    final context = contentContext(options);
    final site = siteId;
    if (context == null || site == null) return null;
    return MultiTracksLibraryContext(
      hash: context.hash,
      customerId: context.customerId,
      userAccessId: context.userAccessId,
      countryId: context.countryId,
      build: context.build,
      restricted: context.restricted,
      language: context.language,
      siteId: site,
    );
  }

  MultiTracksLibraryContext? contentContext(_Options options) {
    final sessionHash = hash;
    final customer = customerId;
    final access = userAccessId;
    final country = countryId;
    final isRestricted = restricted;
    if (sessionHash == null ||
        customer == null ||
        access == null ||
        country == null ||
        isRestricted == null) {
      return null;
    }
    return MultiTracksLibraryContext(
      hash: sessionHash,
      customerId: customer,
      userAccessId: access,
      countryId: country,
      build: options.build,
      restricted: isRestricted,
      language: options.language,
      siteId: siteId,
    );
  }
}

class _Options {
  final String site, language, deviceName, application;
  final String appVersion, iosVersion, alamofireVersion, acceptLanguage;
  final int build, platform;
  final String? out, baseUrl, downloadDirectory, structureOut;
  final bool explore, downloadContent, redeemRental;
  final int? contentId, contentType, keyId;
  _Options(
    this.site,
    this.language,
    this.deviceName,
    this.application,
    this.platform,
    this.build,
    this.out,
    this.explore,
    this.baseUrl,
    this.appVersion,
    this.iosVersion,
    this.alamofireVersion,
    this.acceptLanguage,
    this.contentId,
    this.contentType,
    this.keyId,
    this.downloadContent,
    this.redeemRental,
    this.downloadDirectory,
    this.structureOut,
  );

  MultiTracksContentSelection? get contentSelection => contentId == null
      ? null
      : MultiTracksContentSelection(
          contentId: contentId!,
          contentType: contentType!,
          keyId: keyId!,
        );

  String get userAgent =>
      'Playback/$appVersion (com.multitracks.custommixplayer; build:$build; iOS $iosVersion) Alamofire/$alamofireVersion';

  static _Options parse(List<String> args) {
    String value(String name, String fallback) {
      final i = args.indexOf('--$name');
      return i >= 0 && i + 1 < args.length ? args[i + 1] : fallback;
    }

    int integerValue(String name, int fallback) {
      final raw = value(name, fallback.toString());
      final parsed = int.tryParse(raw);
      if (parsed == null) {
        stderr.writeln('--$name precisa ser um número inteiro.');
        exit(2);
      }
      return parsed;
    }

    int? optionalIntegerValue(String name) {
      final raw = value(name, '');
      if (raw.isEmpty) return null;
      final parsed = int.tryParse(raw);
      if (parsed == null) {
        stderr.writeln('--$name precisa ser um número inteiro.');
        exit(2);
      }
      return parsed;
    }

    if (args.contains('--help') || args.contains('-h')) {
      stdout.writeln(
        'Uso: dart tool/multitracks_probe.dart [--site multitracks] [--language pt] [--device-name "iPhone 11 (26.2)"]\n'
        '       [--application iPhone12,1] [--platform 1] [--build 86204] [--explore] [--out arquivo.txt]\n'
        '       [--app-version 8.6.2] [--ios-version 26.2.0] [--alamofire-version 5.11.2] [--accept-language "pt-BR;q=1.0"]\n'
        '       [--content-id N --content-type N --key-id N [--structure-out estrutura.json]]\n'
        '       [--download-content --download-dir DIRETORIO]\n'
        '       [--redeem-rental --confirm-redeem-rental CONSUMIR --download-dir DIRETORIO]\n'
        '\nPerfil da captura autorizada do Playback 8.6.2. platform e build são inteiros.\n'
        'User-Agent é montado com as versões e o build acima. A identidade é própria e estável, sem copiar o UUID do iPhone.\n'
        'O download sem --redeem-rental apenas solicita link para conteúdo já concedido. O resgate exige confirmação literal e nunca é repetido.',
      );
      exit(0);
    }
    final out = value('out', '');
    final contentId = optionalIntegerValue('content-id');
    final contentType = optionalIntegerValue('content-type');
    final keyId = optionalIntegerValue('key-id');
    final downloadContent = args.contains('--download-content');
    final redeemRental = args.contains('--redeem-rental');
    final downloadDirectory = value('download-dir', '');
    final structureOut = value('structure-out', '');
    if (structureOut.isNotEmpty && contentId == null) {
      stderr.writeln('--structure-out exige --content-id, --content-type e --key-id.');
      exit(2);
    }
    if ([contentId, contentType, keyId].any((value) => value != null) &&
        [contentId, contentType, keyId].any((value) => value == null)) {
      stderr.writeln(
        '--content-id, --content-type e --key-id devem ser informados juntos.',
      );
      exit(2);
    }
    if ((downloadContent || redeemRental) && contentId == null) {
      stderr.writeln(
        'Download/resgate exige os três identificadores de conteúdo.',
      );
      exit(2);
    }
    if ((downloadContent || redeemRental) && downloadDirectory.isEmpty) {
      stderr.writeln('--download-dir é obrigatório para baixar conteúdo.');
      exit(2);
    }
    if (redeemRental && value('confirm-redeem-rental', '') != 'CONSUMIR') {
      stderr.writeln(
        'Resgate pode consumir crédito. Confirme com --confirm-redeem-rental CONSUMIR.',
      );
      exit(2);
    }
    return _Options(
      value('site', 'multitracks'),
      value('language', 'pt'),
      value('device-name', _playbackDeviceName),
      value('application', _playbackApplication),
      integerValue('platform', _playbackPlatform),
      integerValue('build', _playbackBuild),
      out.isEmpty ? null : out.replaceFirst(RegExp(r'^~'), _homeDirectory()),
      args.contains('--explore'),
      value('base-url', '').isEmpty
          ? null
          : value('base-url', ''), // só para testes contra um servidor local
      value('app-version', '8.6.2'),
      value('ios-version', '26.2.0'),
      value('alamofire-version', '5.11.2'),
      value('accept-language', 'pt-BR;q=1.0'),
      contentId,
      contentType,
      keyId,
      downloadContent,
      redeemRental,
      downloadDirectory.isEmpty
          ? null
          : downloadDirectory.replaceFirst(RegExp(r'^~'), _homeDirectory()),
      structureOut.isEmpty ? null : structureOut.replaceFirst(RegExp(r'^~'), _homeDirectory()),
    );
  }
}

/// Campos de estrutura musical copiados com valores para `--structure-out`. Todo o resto da resposta fica de fora.
const _structureKeys = ['title', 'duration', 'bpm', 'originalKey', 'keyChanges', 'tempos', 'timeSignatures', 'sections', 'clicks'];
const _stemKeys = ['stemID', 'partID', 'keyID', 'part', 'abbreviation', 'anyKey', 'clickOrGuide', 'vocal', 'order', 'range'];

Future<void> _writeStructure(Object? json, String path, void Function(String) say) async {
  Map? item;
  void find(Object? node) {
    if (item != null) return;
    if (node is Map) {
      if (node['tempos'] is List || node['sections'] is List) {
        item = node;
        return;
      }
      node.values.forEach(find);
    } else if (node is List) {
      node.forEach(find);
    }
  }

  find(json);
  if (item == null) {
    say('\n--structure-out: a resposta não trouxe tempos/seções; nada foi gravado.');
    return;
  }
  final structure = <String, Object?>{
    for (final key in _structureKeys)
      if (item!.containsKey(key)) key: item![key],
    if (item!['stems'] is List)
      'stems': [
        for (final stem in item!['stems'] as List)
          if (stem is Map) {for (final key in _stemKeys) if (stem.containsKey(key)) key: stem[key]},
      ],
  };
  final file = File(path);
  await file.writeAsString(const JsonEncoder.withIndent('  ').convert(structure));
  if (!Platform.isWindows) await Process.run('chmod', ['600', path]);
  say('\nEstrutura musical gravada em $path (só valores de andamento, compasso, seções, clicks e stems; nada de conta ou URL).');
}
