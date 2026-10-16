import 'dart:convert';
import 'dart:io';
import 'dart:typed_data';

import 'package:archive/archive.dart';
import 'package:flutter_app/services/multitracks_contract.dart';
import 'package:flutter_app/services/multitracks_package_importer.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  late Directory root;
  late MultiTracksContentItem item;
  const selection = MultiTracksContentSelection(
    contentId: 48052,
    contentType: 26,
    keyId: 30,
  );

  setUp(() async {
    root = await Directory.systemTemp.createTemp('multitracks-import-');
    item = MultiTracksContentItem.fromJson({
      'contentID': 48052,
      'title': 'Synthetic Song',
      'artist': 'Synthetic Artist',
      'keys': [
        {'keyID': 30, 'title': 'E'},
      ],
      'stems': [
        _stem(102, 'Bateria', order: 2),
        _stem(101, 'Click', order: 0, clickOrGuide: true),
      ],
    });
  });

  tearDown(() => root.delete(recursive: true));

  test(
    'decodes raw LZ4, validates ZIP and maps every stem by stemID',
    () async {
      final package = await _writePackage(root, {
        '102.m4a': [2, 2, 2],
        '101.m4a': [1, 1],
        'Album1x.jpg': [0xff, 0xd8, 0xff, 0xd9],
      });
      final importer = MultiTracksPackageImporter(
        transcoder: const _FakeTranscoder(),
      );

      final imported = await importer.import(
        package: package,
        destinationDirectory: Directory('${root.path}/output'),
        item: item,
        selection: selection,
      );

      expect(imported.stemIds, [101, 102]);
      expect(imported.track.title, 'Synthetic Song');
      expect(imported.track.artist, 'Synthetic Artist');
      expect(imported.track.key, 'E');
      expect(imported.track.channels.map((channel) => channel.label), [
        'Click',
        'Bateria',
      ]);
      expect(imported.track.channels.first.isClickOrGuide, isTrue);
      expect(
        imported.track.channels.every(
          (channel) => File(channel.filePath).existsSync(),
        ),
        isTrue,
      );
      expect(
        Directory('${root.path}/output')
            .listSync()
            .whereType<Directory>()
            .where((directory) => directory.path.contains('.import-')),
        isEmpty,
      );
    },
  );

  test('the API item brings sections, tempo map and fixed clicks; a guide stem silences the spoken guide', () async {
    final structure = jsonDecode(File('test/fixtures/multitracks/content_structure.json').readAsStringSync()) as Map<String, Object?>;
    final package = await _writePackage(root, {'101.m4a': [1], '103.m4a': [3]});
    item = MultiTracksContentItem.fromJson({
      ...structure,
      'contentID': 48052,
      'title': 'Structured',
      'stems': [
        _stem(101, 'Click Track', order: 0, clickOrGuide: true),
        _stem(103, 'Guide (Dynamic)', order: 1, clickOrGuide: true),
      ],
    });
    final imported = await MultiTracksPackageImporter(transcoder: const _FakeTranscoder()).import(
      package: package,
      destinationDirectory: Directory('${root.path}/output'),
      item: item,
      selection: selection,
    );
    expect(imported.structureWarnings, isEmpty);
    expect(imported.track.sections.map((s) => s.name), ['Contagem', 'Introdução', 'Refrão', 'Seção']);
    expect(imported.track.sections.every((s) => !s.playGuideCue), isTrue);
    expect(imported.track.tempoChanges.length, 4);
    expect(imported.track.clickSettings.bpm, 120);
    expect(imported.track.fixedClicks?.accents, [0.0001, 2.0001, 4.0001]);
  });

  test('decodes a compressed LZ4 block', () async {
    final package = await _writePackage(root, {
      '101.m4a': [1, 2, 3],
    }, compressedBlock: true);
    item = MultiTracksContentItem.fromJson({
      'contentID': 48052,
      'title': 'Compressed',
      'stems': [_stem(101, 'Click', order: 0, clickOrGuide: true)],
    });

    final imported =
        await MultiTracksPackageImporter(
          transcoder: const _FakeTranscoder(),
        ).import(
          package: package,
          destinationDirectory: Directory('${root.path}/output'),
          item: item,
          selection: selection,
        );

    expect(imported.stemIds, [101]);
  });

  test(
    'fails closed when an audio member has no matching descriptor',
    () async {
      final package = await _writePackage(root, {
        '999.m4a': [1, 2, 3],
      });
      final output = Directory('${root.path}/output');

      await expectLater(
        MultiTracksPackageImporter(transcoder: const _FakeTranscoder()).import(
          package: package,
          destinationDirectory: output,
          item: item,
          selection: selection,
        ),
        throwsA(isA<MultiTracksPackageImportFailure>()),
      );

      expect(
        output.existsSync() ? output.listSync() : const <FileSystemEntity>[],
        isEmpty,
      );
    },
  );

  test('rejects an LZ4 content checksum mismatch', () async {
    final package = await _writePackage(root, {
      '101.m4a': [1, 2, 3],
    });
    final bytes = package.readAsBytesSync();
    bytes[bytes.length - 1] ^= 0xff;
    package.writeAsBytesSync(bytes);

    await expectLater(
      MultiTracksPackageImporter(transcoder: const _FakeTranscoder()).import(
        package: package,
        destinationDirectory: Directory('${root.path}/output'),
        item: item,
        selection: selection,
      ),
      throwsA(
        isA<MultiTracksPackageImportFailure>().having(
          (failure) => failure.message,
          'message',
          contains('checksum'),
        ),
      ),
    );
  });
}

Map<String, Object?> _stem(
  int stemId,
  String part, {
  required int order,
  bool clickOrGuide = false,
}) => {
  'contentType': 26,
  'stemID': stemId,
  'partID': stemId,
  'keyID': 30,
  'range': 0,
  'part': part,
  'abbreviation': part.substring(0, 1),
  'anyKey': false,
  'clickOrGuide': clickOrGuide,
  'vocal': false,
  'order': order,
};

Future<File> _writePackage(
  Directory root,
  Map<String, List<int>> entries, {
  bool compressedBlock = false,
}) async {
  final archive = Archive();
  for (final entry in entries.entries) {
    archive.addFile(ArchiveFile(entry.key, entry.value.length, entry.value));
  }
  final zip = Uint8List.fromList(ZipEncoder().encode(archive)!);
  final package = File('${root.path}/48052.mtrack');
  await package.writeAsBytes(_lz4Frame(zip, compressedBlock: compressedBlock));
  return package;
}

Uint8List _lz4Frame(Uint8List content, {required bool compressedBlock}) {
  const flg = 0x64;
  const bd = 0x70;
  final descriptor = Uint8List.fromList([flg, bd]);
  final block = compressedBlock ? _literalLz4Block(content) : content;
  final builder = BytesBuilder(copy: false)
    ..add(_uint32(0x184d2204))
    ..add(descriptor)
    ..addByte((_xxHash32(descriptor) >> 8) & 0xff)
    ..add(_uint32(block.length | (compressedBlock ? 0 : 0x80000000)))
    ..add(block)
    ..add(_uint32(0))
    ..add(_uint32(_xxHash32(content)));
  return builder.takeBytes();
}

Uint8List _literalLz4Block(Uint8List content) {
  final builder = BytesBuilder(copy: false)..addByte(0xf0);
  var remaining = content.length - 15;
  while (remaining >= 255) {
    builder.addByte(255);
    remaining -= 255;
  }
  builder
    ..addByte(remaining)
    ..add(content);
  return builder.takeBytes();
}

Uint8List _uint32(int value) =>
    Uint8List(4)..buffer.asByteData().setUint32(0, value, Endian.little);

int _xxHash32(Uint8List bytes) {
  const prime1 = 0x9e3779b1;
  const prime2 = 0x85ebca77;
  const prime3 = 0xc2b2ae3d;
  const prime4 = 0x27d4eb2f;
  const prime5 = 0x165667b1;
  int rotate(int value, int count) =>
      ((value << count) | (value >>> (32 - count))) & 0xffffffff;
  int round(int accumulator, int input) =>
      (rotate((accumulator + input * prime2) & 0xffffffff, 13) * prime1) &
      0xffffffff;

  final data = ByteData.sublistView(bytes);
  var offset = 0;
  late int hash;
  if (bytes.length >= 16) {
    var v1 = (prime1 + prime2) & 0xffffffff;
    var v2 = prime2;
    var v3 = 0;
    var v4 = (-prime1) & 0xffffffff;
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

class _FakeTranscoder implements MultiTracksAudioTranscoder {
  const _FakeTranscoder();

  @override
  Future<void> m4aToWav({required File input, required File output}) async {
    final payload = await input.readAsBytes();
    final header = Uint8List(44 + payload.length);
    header.setRange(0, 4, 'RIFF'.codeUnits);
    header.setRange(8, 12, 'WAVE'.codeUnits);
    header.setRange(44, header.length, payload);
    await output.writeAsBytes(header);
  }
}
