import 'dart:convert';
import 'dart:io';

/// Resultado de [SafeJson.read]: o valor (null se não havia arquivo ou nada foi aproveitável) e, se algo deu errado, o que foi feito.
class SafeJsonRead<T> {
  final T? value;
  final String? problem;
  const SafeJsonRead(this.value, [this.problem]);
}

/// Leitura e escrita de arquivos JSON de preferências sem perder dados em silêncio:
/// - a escrita é serializada por arquivo (duas gravações seguidas não pisam no mesmo temporário), vai para `.tmp`, guarda a versão
///   anterior em `.bak` e só então troca o nome;
/// - a leitura que falha tenta o `.bak`; se também não der, o arquivo ilegível é guardado como `.corrupt` (nunca sobrescrito) e a
///   falha volta em [SafeJsonRead.problem] para quem chamou mostrar — em vez de parecer um reset de fábrica.
class SafeJson {
  static final Map<String, Future<void>> _queues = {};

  static Future<void> write(File file, Object value) {
    final content = jsonEncode(value);
    final previous = _queues[file.path] ?? Future<void>.value();
    final operation = previous.then((_) async {
      final temporary = File('${file.path}.tmp');
      await temporary.writeAsString(content, flush: true);
      if (await file.exists()) await file.copy('${file.path}.bak');
      await temporary.rename(file.path);
    });
    final settled = operation.then<void>((_) {}, onError: (Object _, StackTrace _) {});
    _queues[file.path] = settled;
    return operation.whenComplete(() {
      if (identical(_queues[file.path], settled)) _queues.remove(file.path);
    });
  }

  static Future<SafeJsonRead<T>> read<T>(File file, T Function(Object? json) parse) async {
    if (!await file.exists()) return const SafeJsonRead(null);
    final name = file.path.split('/').last;
    try {
      return SafeJsonRead(parse(jsonDecode(await file.readAsString())));
    } catch (e) {
      final backup = File('${file.path}.bak');
      Object? backupError;
      if (await backup.exists()) {
        try {
          final recovered = parse(jsonDecode(await backup.readAsString()));
          await _setAside(file);
          return SafeJsonRead(recovered, '$name estava ilegível ($e); usada a cópia anterior (.bak).');
        } catch (b) {
          backupError = b;
        }
      }
      await _setAside(file);
      return SafeJsonRead(null,
          '$name estava ilegível ($e)${backupError == null ? '' : ' e a cópia anterior também ($backupError)'}; '
          'os valores padrão foram usados e o arquivo foi guardado como $name.corrupt.');
    }
  }

  static Future<void> _setAside(File file) async {
    try {
      await file.rename('${file.path}.corrupt');
    } on FileSystemException {
      // sem como guardar: a próxima gravação ainda troca o nome de forma atômica
    }
  }
}
