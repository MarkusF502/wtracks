import 'dart:convert';
import 'dart:io';

import 'package:flutter/services.dart';
import 'package:uuid/uuid.dart';

import '../models/multitracks_session.dart';

/// Chave/valor cifrado. No Android, os valores são cifrados com uma chave AES-GCM do Android Keystore e ficam fora do
/// backup automático (ver MultiTracksSecureStore.kt e res/xml/*backup*).
abstract class MultiTracksSecureStore {
  Future<String?> read(String key);
  Future<void> write(String key, String value);
  Future<void> delete(String key);
}

class AndroidMultiTracksSecureStore implements MultiTracksSecureStore {
  const AndroidMultiTracksSecureStore();

  static const _channel = MethodChannel('wtracks/secure_store');

  @override
  Future<String?> read(String key) => _channel.invokeMethod<String>('read', {'key': key});

  @override
  Future<void> write(String key, String value) => _channel.invokeMethod<void>('write', {'key': key, 'value': value});

  @override
  Future<void> delete(String key) => _channel.invokeMethod<void>('delete', {'key': key});
}

/// Para testes. Nada sai da memória do processo.
class InMemoryMultiTracksSecureStore implements MultiTracksSecureStore {
  final values = <String, String>{};

  @override
  Future<String?> read(String key) async => values[key];

  @override
  Future<void> write(String key, String value) async => values[key] = value;

  @override
  Future<void> delete(String key) async => values.remove(key);
}

class MultiTracksSecureStorageUnavailable implements Exception {
  const MultiTracksSecureStorageUnavailable();
}

/// Sessão (hash e contexto) e identidade estável do aparelho. Nunca guarda a senha.
class MultiTracksSessionStore {
  MultiTracksSessionStore(this._store);

  static const _sessionKey = 'multitracks.session';
  static const _deviceKey = 'multitracks.deviceIdentifier';

  final MultiTracksSecureStore? _store;

  /// Sem armazenamento seguro (fora do Android) não há como manter a identidade estável: o login fica indisponível em
  /// vez de registrar um aparelho novo na conta a cada execução.
  bool get isAvailable => _store != null;

  MultiTracksSecureStore get _required => _store ?? (throw const MultiTracksSecureStorageUnavailable());

  Future<MultiTracksSession?> loadSession() async {
    final raw = await _required.read(_sessionKey);
    if (raw == null) return null;
    try {
      return MultiTracksSession.fromStorageJson(jsonDecode(raw));
    } on FormatException {
      return null;
    }
  }

  Future<void> saveSession(MultiTracksSession session) =>
      _required.write(_sessionKey, jsonEncode(session.toStorageJson()));

  Future<void> clearSession() => _required.delete(_sessionKey);

  /// UUID próprio do WTracks, gerado uma vez e reutilizado: gerar outro tentaria registrar mais um aparelho na conta.
  Future<String> deviceIdentifier() async {
    final saved = await _required.read(_deviceKey);
    if (saved != null && saved.trim().isNotEmpty) return saved;
    final created = const Uuid().v4().toUpperCase();
    await _required.write(_deviceKey, created);
    return created;
  }
}

MultiTracksSecureStore? platformSecureStore() => Platform.isAndroid ? const AndroidMultiTracksSecureStore() : null;
