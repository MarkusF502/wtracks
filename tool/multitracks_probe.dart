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

const _appName = 'WTracks';

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

  final base = Uri.parse(options.baseUrl ?? 'https://api.${options.site}.com/playback/');
  say('Base: $base');
  final client = HttpClient()..connectionTimeout = const Duration(seconds: 20);

  Future<(int, Object?)> post(String route, Map<String, Object?> body) async {
    final request = await client.postUrl(base.resolve(route));
    request.headers.contentType = ContentType.json;
    request.headers.set('Accept', 'application/json');
    request.headers.set('User-Agent', '$_appName-probe/1');
    request.add(utf8.encode(jsonEncode(body)));
    final response = await request.close().timeout(const Duration(seconds: 60));
    final text = await response.transform(utf8.decoder).join();
    Object? json;
    try {
      json = jsonDecode(text);
    } on FormatException {
      json = null;
    }
    say('\nPOST $route -> HTTP ${response.statusCode} (${response.headers.contentType?.mimeType ?? 'sem content-type'}, '
        '${text.length} bytes, cabeçalhos: ${(<String>[]..addAll(_headerNames(response))).join(', ')})');
    if (json == null) say('  (corpo não é JSON: ${text.isEmpty ? 'vazio' : 'texto de ${text.length} caracteres, redigido'})');
    return (response.statusCode, json);
  }

  final deviceId = await _deviceIdentifier();
  say('Identificador do aparelho de teste: $deviceId (fica em ~/.config/wtracks-probe/device-id; o login pode registrar o aparelho '
      '"${options.deviceName}" na sua conta MultiTracks)');
  Object? login;
  try {
    final (status, json) = await post('authenticate', {
      // O servidor respondeu "Username, password and device identifier are required fields.": o nome exato da chave do identificador não
      // aparece no binário (nomes com mais de 15 caracteres não são decodificados); envia as variantes prováveis, o servidor ignora as outras.
      // Nomes de chave encontrados no binário perto dos campos do login: deviceID, deviceUUID, deviceIdentifier, identifierForVendor.
      'deviceIdentifier': deviceId,
      'deviceID': deviceId,
      'deviceId': deviceId,
      'deviceUUID': deviceId,
      'uuid': deviceId,
      'identifierForVendor': deviceId,
      'username': username,
      'password': password,
      'language': options.language,
      'deviceName': options.deviceName,
      'pushToken': '',
      'application': options.application,
      'platform': options.platform,
    });
    password = ''; // a senha não é mais necessária
    login = json;
    say(_schema(json));
    if (status != 200 || json == null) {
      say('\nO login não foi aceito. Nenhuma outra chamada foi feita e nada foi repetido.');
      await _finish(options, out);
      return;
    }
  } on Exception catch (e) {
    say('\nFalha de rede: ${e.runtimeType}');
    await _finish(options, out);
    return;
  }

  if (options.explore) {
    final session = _Session.from(login);
    say('\nDa resposta do login: hash=${session.hash == null ? 'NÃO ENCONTRADO' : 'encontrado (redigido)'}, '
        'customer=${session.customer == null ? 'NÃO ENCONTRADO' : 'encontrado (redigido)'}, siteID=${session.siteID ?? 'não encontrado'}');
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
            say('\nO servidor recusou ou limitou (HTTP $status): parando por aqui.');
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
  final dir = Directory('${Platform.environment['HOME'] ?? '.'}/.config/wtracks-probe');
  final file = File('${dir.path}/device-id');
  if (await file.exists()) {
    final saved = (await file.readAsString()).trim();
    if (saved.isNotEmpty) return saved;
  }
  final random = Random.secure();
  String hex(int n) => List.generate(n, (_) => random.nextInt(16).toRadixString(16)).join();
  final id = '${hex(8)}-${hex(4)}-4${hex(3)}-${(8 + random.nextInt(4)).toRadixString(16)}${hex(3)}-${hex(12)}'.toUpperCase();
  await dir.create(recursive: true);
  await file.writeAsString(id);
  return id;
}

Iterable<String> _headerNames(HttpClientResponse response) {
  final names = <String>[];
  response.headers.forEach((name, _) => names.add(name));
  return names;
}

Future<void> _finish(_Options options, StringBuffer out) async {
  if (options.out != null) {
    await File(options.out!).writeAsString(out.toString());
    stdout.writeln('\nEsquema gravado em ${options.out} (sem valores, senha nem hash).');
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
      if (v is String && (lower == 'message' || lower.startsWith('error')) && v.length <= 120 && !v.contains('@')) {
        lines.add('$pad$key: "$v"');
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
    return '${pad}[0] de ${json.length}: ${_describe(first)}\n${first is Map || first is List ? _schema(first, depth + 1) : ''}'.trimRight();
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
          if (hash == null && (lower == 'userhash' || lower == 'hash') && e.value is String) hash = e.value as String;
          if (customer == null && (lower == 'customer' || lower == 'customerid' || lower == 'organizationid') && e.value != null && e.value is! Map && e.value is! List) {
            customer = e.value;
          }
          if (siteID == null && lower == 'siteid' && e.value != null && e.value is! Map && e.value is! List) siteID = e.value;
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
  final String site, language, deviceName, application, platform;
  final String? out, baseUrl;
  final bool explore;
  _Options(this.site, this.language, this.deviceName, this.application, this.platform, this.out, this.explore, this.baseUrl);

  static _Options parse(List<String> args) {
    String value(String name, String fallback) {
      final i = args.indexOf('--$name');
      return i >= 0 && i + 1 < args.length ? args[i + 1] : fallback;
    }

    if (args.contains('--help') || args.contains('-h')) {
      stdout.writeln('Uso: dart tool/multitracks_probe.dart [--site multitracks] [--language en] [--device-name "WTracks (teste)"]\n'
          '       [--application WTracks] [--platform linux] [--explore] [--out arquivo.txt]');
      exit(0);
    }
    final out = value('out', '');
    return _Options(
      value('site', 'multitracks'),
      value('language', 'en'),
      value('device-name', 'WTracks (teste)'),
      value('application', _appName),
      value('platform', Platform.operatingSystem),
      out.isEmpty ? null : out.replaceFirst(RegExp(r'^~'), Platform.environment['HOME'] ?? '~'),
      args.contains('--explore'),
      value('base-url', '').isEmpty ? null : value('base-url', ''), // só para testes contra um servidor local
    );
  }
}
