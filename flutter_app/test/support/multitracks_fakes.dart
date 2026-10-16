// Dublês sintéticos da API MultiTracks para testes. Nenhum dado real: IDs, textos e URLs são inventados e a URL de
// download aponta para o host permitido só para passar na validação; nenhum teste faz rede.
import 'dart:async';
import 'dart:convert';
import 'dart:io';
import 'dart:typed_data';

import 'package:archive/archive.dart';
import 'package:crypto/crypto.dart';
import 'package:flutter_app/services/multitracks_content_provider.dart';
import 'package:flutter_app/services/multitracks_package_downloader.dart';
import 'package:flutter_app/services/multitracks_package_importer.dart';

const syntheticDownloadUrl =
    'https://playback.blob.core.windows.net/cloud/x/streaming/202.mtrack?sig=synthetic';

typedef JsonHandler =
    FutureOr<MultiTracksJsonResponse> Function(Map<String, Object?> body);

/// Transporte JSON roteirizado: cada rota responde pelo seu handler e toda chamada fica registrada.
class ScriptedJsonTransport implements MultiTracksJsonTransport {
  final handlers = <String, JsonHandler>{};
  final calls = <(String, Map<String, Object?>)>[];

  @override
  Future<MultiTracksJsonResponse> post(
    MultiTracksClientProfile profile,
    String route,
    Map<String, Object?> body,
  ) async {
    calls.add((route, body));
    final handler = handlers[route];
    if (handler == null) throw StateError('rota inesperada: $route');
    return handler(body);
  }

  /// Itens de `content/download` enviados, na ordem.
  List<Map<String, Object?>> get contentItems => [
    for (final (route, body) in calls)
      if (route == 'content/download')
        ((body['items'] as List).single as Map).cast<String, Object?>(),
  ];

  int get redeemCalls =>
      contentItems.where((item) => item['redeemRental'] == true).length;
  int get linkCalls => contentItems
      .where(
        (item) => item['downloadLink'] == true && item['redeemRental'] != true,
      )
      .length;
}

MultiTracksJsonResponse ok(Map<String, Object?> body) =>
    MultiTracksJsonResponse(200, body);

Map<String, Object?> loginSuccess({List<Object?>? organizations}) => {
  'customerID': 10,
  'userID': 11,
  'userAccessID': 20,
  'firstName': 'Pessoa',
  'hash': 'synthetic-session-hash',
  'siteID': 40,
  'countryID': 30,
  'restricted': false,
  'organizations':
      organizations ??
      [
        {'default': true},
      ],
  'result': 1,
  'errorCode': 0,
  'message': 'Success',
};

Map<String, Object?> songSummary(
  int id, {
  int? songId,
  String? title,
  bool rentals = false,
  String? purchased,
}) => {
  'libraryID': id,
  'songID': songId ?? id + 1000,
  'song': title ?? 'Song $id',
  'songStatus': 1,
  'artistID': 1,
  'artist': 'Artist',
  'albumID': 2,
  'album': 'Album',
  'image': '',
  'image2x': '',
  'previewUrl': '',
  'dateContentPurchased': purchased,
  'rentalsAvailable': rentals,
  'cloudSong': false,
};

Map<String, Object?> songsPage(
  List<Map<String, Object?>> songs, {
  int page = 1,
  int totalPages = 1,
}) => {
  'data': songs,
  'pageNumber': page,
  'totalPages': totalPages,
  'totalRecords': songs.length,
  'result': 1,
  'errorCode': 0,
  'message': 'Success',
};

Map<String, Object?> stem(
  int stemId,
  String part, {
  int order = 0,
  int keyId = 30,
  bool anyKey = false,
  bool clickOrGuide = false,
  bool vocal = false,
}) => {
  'contentType': 26,
  'stemID': stemId,
  'partID': stemId,
  'keyID': keyId,
  'range': 0,
  'part': part,
  'abbreviation': part.substring(0, 1),
  'anyKey': anyKey,
  'clickOrGuide': clickOrGuide,
  'vocal': vocal,
  'order': order,
};

/// Duas faixas para o tom 30 (click e baixo) e uma variante do tom 31.
List<Map<String, Object?>> syntheticStems() => [
  stem(302, 'Bass', order: 2),
  stem(301, 'Click', order: 0, anyKey: true, clickOrGuide: true),
  stem(399, 'Bass', order: 2, keyId: 31),
];

Map<String, Object?> contentResponse({
  String? downloadUrl,
  bool playOfTheWeek = false,
  Map<String, Object?>? rentalsInfo,
  int? rentalsRemaining = 2,
  List<Map<String, Object?>>? stems,
  int result = 1,
  int errorCode = 0,
}) => {
  'data': {
    'rentalsRemaining': rentalsRemaining,
    'rentalsPreviews': 0,
    'items': [
      {
        'libraryID': 101,
        'contentID': 202,
        'title': 'Synthetic Song',
        'artist': 'Synthetic Artist',
        'album': 'Synthetic Album',
        'bpm': 72,
        'originalKey': 'G',
        'version': 3,
        'stemsVersion': 5,
        'contentStatus': 1,
        'songStatus': 1,
        'downloadUrl': downloadUrl,
        'fileSize': 1,
        'playOfTheWeek': playOfTheWeek,
        'rentalsInfo': rentalsInfo,
        'keys': [
          {'keyID': 30, 'title': 'G'},
          {'keyID': 31, 'title': 'A'},
        ],
        'stems': stems ?? syntheticStems(),
      },
    ],
  },
  'result': result,
  'errorCode': errorCode,
  'message': 'Success',
};

/// Handler de `content/download` que escolhe a resposta pelas flags do item.
JsonHandler contentHandler({
  required Map<String, Object?> Function() metadata,
  required Map<String, Object?> Function() link,
  FutureOr<Map<String, Object?>> Function()? redeem,
}) => (body) async {
  final item = (body['items'] as List).single as Map;
  if (item['redeemRental'] == true) {
    if (redeem == null) throw StateError('resgate não esperado');
    return ok(await redeem());
  }
  return ok(item['downloadLink'] == true ? link() : metadata());
};

/// `.mtrack` sintético: frame LZ4 com bloco cru contendo um ZIP de M4A falsos nomeados por stemID.
Uint8List syntheticPackage(Map<int, List<int>> stems) {
  final archive = Archive();
  for (final entry in stems.entries) {
    archive.addFile(
      ArchiveFile('${entry.key}.m4a', entry.value.length, entry.value),
    );
  }
  final zip = Uint8List.fromList(ZipEncoder().encode(archive)!);
  const descriptor = [0x64, 0x70];
  return (BytesBuilder(copy: false)
        ..add(_uint32(0x184d2204))
        ..add(descriptor)
        ..addByte((_xxHash32(Uint8List.fromList(descriptor)) >> 8) & 0xff)
        ..add(_uint32(zip.length | 0x80000000))
        ..add(zip)
        ..add(_uint32(0))
        ..add(_uint32(_xxHash32(zip))))
      .takeBytes();
}

class FakeDownloadTransport implements MultiTracksDownloadTransport {
  FakeDownloadTransport(this.data, {String? contentMd5, this.gate})
    : contentMd5 = contentMd5 ?? base64Encode(md5.convert(data).bytes);

  final List<int> data;
  final String contentMd5;

  /// Quando presente, o corpo só é entregue depois que o teste completar o gate.
  final Completer<void>? gate;
  int opens = 0;

  @override
  Future<MultiTracksDownloadSource> open(
    Uri url, {
    required Set<String> allowedHosts,
  }) async {
    opens++;
    final half = data.length ~/ 2;
    Stream<List<int>> body() async* {
      yield data.sublist(0, half);
      if (gate != null) await gate!.future;
      yield data.sublist(half);
    }

    return MultiTracksDownloadSource(
      effectiveUrl: url,
      statusCode: 200,
      bytes: body(),
      contentLength: data.length,
      contentMd5: contentMd5,
      contentType: 'application/octet-stream',
    );
  }
}

class FakeTranscoder implements MultiTracksAudioTranscoder {
  int calls = 0;
  @override
  Future<void> m4aToWav({required File input, required File output}) async {
    calls++;
    final payload = await input.readAsBytes();
    final bytes = Uint8List(44 + payload.length)
      ..setRange(0, 4, 'RIFF'.codeUnits)
      ..setRange(8, 12, 'WAVE'.codeUnits)
      ..setRange(44, 44 + payload.length, payload);
    await output.writeAsBytes(bytes);
  }
}

Uint8List _uint32(int value) =>
    Uint8List(4)..buffer.asByteData().setUint32(0, value, Endian.little);

int _xxHash32(Uint8List bytes) {
  const prime1 = 0x9e3779b1,
      prime2 = 0x85ebca77,
      prime3 = 0xc2b2ae3d,
      prime4 = 0x27d4eb2f,
      prime5 = 0x165667b1;
  int rotate(int value, int count) =>
      ((value << count) | (value >>> (32 - count))) & 0xffffffff;
  int round(int accumulator, int input) =>
      (rotate((accumulator + input * prime2) & 0xffffffff, 13) * prime1) &
      0xffffffff;
  final data = ByteData.sublistView(bytes);
  var offset = 0;
  late int hash;
  if (bytes.length >= 16) {
    var v1 = (prime1 + prime2) & 0xffffffff,
        v2 = prime2,
        v3 = 0,
        v4 = (-prime1) & 0xffffffff;
    while (offset + 16 <= bytes.length) {
      v1 = round(v1, data.getUint32(offset, Endian.little));
      v2 = round(v2, data.getUint32(offset + 4, Endian.little));
      v3 = round(v3, data.getUint32(offset + 8, Endian.little));
      v4 = round(v4, data.getUint32(offset + 12, Endian.little));
      offset += 16;
    }
    hash =
        (rotate(v1, 1) + rotate(v2, 7) + rotate(v3, 12) + rotate(v4, 18)) &
        0xffffffff;
  } else {
    hash = prime5;
  }
  hash = (hash + bytes.length) & 0xffffffff;
  while (offset + 4 <= bytes.length) {
    hash = (hash + data.getUint32(offset, Endian.little) * prime3) & 0xffffffff;
    hash = (rotate(hash, 17) * prime4) & 0xffffffff;
    offset += 4;
  }
  while (offset < bytes.length) {
    hash = (hash + bytes[offset++] * prime5) & 0xffffffff;
    hash = (rotate(hash, 11) * prime1) & 0xffffffff;
  }
  hash ^= hash >>> 15;
  hash = (hash * prime2) & 0xffffffff;
  hash ^= hash >>> 13;
  hash = (hash * prime3) & 0xffffffff;
  hash ^= hash >>> 16;
  return hash & 0xffffffff;
}
