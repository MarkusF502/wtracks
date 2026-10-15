// Teste de comunicação com a API do Playback (Fase 6.1.1). VOCÊ executa este programa no seu terminal:
//
//   dart tool/multitracks_probe.dart --site multitracks --out ~/multitracks-schema.txt
//   dart tool/multitracks_probe.dart --site multitracks --explore --out ~/multitracks-schema.txt
//
// - Pede usuário e senha no terminal (a senha não aparece e não é gravada em lugar nenhum).
// - Faz UM login (sem tentar de novo se falhar) e, com --explore, algumas consultas de leitura. Nunca baixa conteúdo nem gasta crédito.
// - Imprime e grava apenas o ESQUEMA das respostas: status HTTP, tipos e chaves. Todo valor (texto, número, id, hash, e-mail, URL) é
//   redigido. Só mensagens de erro curtas de campos chamados message/error* são mostradas.
// - Não imprime nem grava a senha, o userHash, cabeçalhos de autenticação ou cookies.
import 'dart:convert';
import 'dart:io';
import 'dart:math';

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

  if (options.explore) {
    final session = _Session.from(login);
    say(
      '\nDa resposta do login: hash=${session.hash == null ? 'NÃO ENCONTRADO' : 'encontrado (redigido)'}, '
      'customer=${session.customer == null ? 'NÃO ENCONTRADO' : 'encontrado (redigido)'}, siteID=${session.siteID == null ? 'não encontrado' : 'encontrado (redigido)'}',
    );
    if (session.hash != null) {
      final common = <String, Object?>{
        'hash': session.hash,
        if (session.customer != null) 'customer': session.customer,
        'language': options.language,
        if (session.siteID != null) 'siteID': session.siteID,
      };
      for (final (route, extra) in <(String, Map<String, Object?>)>[
        ('organization', {}),
        ('library/rentals', {'pageNumber': 1, 'pageSize': 5}),
        ('library/songs', {'pageNumber': 1, 'pageSize': 5}),
      ]) {
        try {
          final (status, json) = await post(route, {...common, ...extra});
          say(_schema(json));
          if (status == 401 || status == 403 || status == 429) {
            say(
              '\nO servidor recusou ou limitou (HTTP $status): parando por aqui.',
            );
            break;
          }
        } on Exception catch (e) {
          say('\nFalha de rede em $route: ${e.runtimeType}');
          break;
        }
      }
    }
  }
  client.close();
  await _finish(options, out);
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
  final Object? customer;
  final Object? siteID;
  _Session(this.hash, this.customer, this.siteID);

  factory _Session.from(Object? json) {
    String? hash;
    Object? customer, siteID;
    void walk(Object? node, {bool inOrg = false}) {
      if (node is Map) {
        for (final e in node.entries) {
          final k = e.key.toString();
          final lower = k.toLowerCase();
          if (hash == null &&
              (lower == 'userhash' || lower == 'hash') &&
              e.value is String)
            hash = e.value as String;
          if (customer == null &&
              (lower == 'customer' ||
                  lower == 'customerid' ||
                  lower == 'organizationid') &&
              e.value != null &&
              e.value is! Map &&
              e.value is! List) {
            customer = e.value;
          }
          if (siteID == null &&
              lower == 'siteid' &&
              e.value != null &&
              e.value is! Map &&
              e.value is! List)
            siteID = e.value;
          walk(e.value, inOrg: inOrg || lower == 'organizations');
        }
      } else if (node is List) {
        for (final item in node) {
          walk(item, inOrg: inOrg);
        }
      }
    }

    walk(json);
    return _Session(hash, customer, siteID);
  }
}

class _Options {
  final String site, language, deviceName, application;
  final String appVersion, iosVersion, alamofireVersion, acceptLanguage;
  final int build, platform;
  final String? out, baseUrl;
  final bool explore;
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

    if (args.contains('--help') || args.contains('-h')) {
      stdout.writeln(
        'Uso: dart tool/multitracks_probe.dart [--site multitracks] [--language pt] [--device-name "iPhone 11 (26.2)"]\n'
        '       [--application iPhone12,1] [--platform 1] [--build 86204] [--explore] [--out arquivo.txt]\n'
        '       [--app-version 8.6.2] [--ios-version 26.2.0] [--alamofire-version 5.11.2] [--accept-language "pt-BR;q=1.0"]\n'
        '\nPerfil da captura autorizada do Playback 8.6.2. platform e build são inteiros.\n'
        'User-Agent é montado com as versões e o build acima. A identidade é própria e estável, sem copiar o UUID do iPhone.',
      );
      exit(0);
    }
    final out = value('out', '');
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
    );
  }
}
