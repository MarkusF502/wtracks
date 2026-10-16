import 'dart:io';
import 'dart:typed_data';

import 'package:archive/archive_io.dart';
import 'package:flutter/services.dart';

import '../models/track.dart';
import 'multitracks_contract.dart';
import 'stem_detection.dart';

class MultiTracksPackageImportFailure implements Exception {
  const MultiTracksPackageImportFailure(this.message);

  final String message;

  @override
  String toString() => 'MultiTracksPackageImportFailure: $message';
}

abstract class MultiTracksAudioTranscoder {
  Future<void> m4aToWav({required File input, required File output});
}

class AndroidMultiTracksAudioTranscoder implements MultiTracksAudioTranscoder {
  const AndroidMultiTracksAudioTranscoder();

  static const _channel = MethodChannel('wtracks/multitracks_audio');

  @override
  Future<void> m4aToWav({required File input, required File output}) async {
    if (!Platform.isAndroid) {
      throw const MultiTracksPackageImportFailure(
        'AAC/M4A transcoding is only available on Android',
      );
    }
    await _channel.invokeMethod<void>('m4aToWav', {
      'input': input.path,
      'output': output.path,
    });
  }
}

/// Etapas do importador, para a interface mostrar progresso real.
enum MultiTracksPackageStage { validating, extracting, transcoding }

class MultiTracksImportedContent {
  const MultiTracksImportedContent({
    required this.track,
    required this.stemIds,
    required this.expandedAudioBytes,
  });

  final Track track;
  final List<int> stemIds;
  final int expandedAudioBytes;
}

class MultiTracksPackageImporter {
  MultiTracksPackageImporter({
    required this.transcoder,
    this.maximumPackageBytes = 2 * 1024 * 1024 * 1024,
    this.maximumExpandedBytes = 4 * 1024 * 1024 * 1024,
    this.maximumEntries = 512,
  });

  final MultiTracksAudioTranscoder transcoder;
  final int maximumPackageBytes;
  final int maximumExpandedBytes;
  final int maximumEntries;

  Future<MultiTracksImportedContent> import({
    required File package,
    required Directory destinationDirectory,
    required MultiTracksContentItem item,
    required MultiTracksContentSelection selection,
    bool Function()? isCancelled,
    void Function(int completed, int total)? onProgress,
    void Function(MultiTracksPackageStage stage)? onStage,
    void Function(int index, int total, String label)? onStemStarted,
  }) async {
    if (!await package.exists()) {
      throw const MultiTracksPackageImportFailure('Package not found');
    }
    final packageLength = await package.length();
    if (packageLength <= 0 || packageLength > maximumPackageBytes) {
      throw const MultiTracksPackageImportFailure('Invalid package size');
    }
    if (item.contentId != null && item.contentId != selection.contentId) {
      throw const MultiTracksPackageImportFailure('Content identity mismatch');
    }

    await destinationDirectory.create(recursive: true);
    final work = Directory(
      '${destinationDirectory.path}/.${selection.contentId}.import-${DateTime.now().microsecondsSinceEpoch}',
    );
    await work.create(recursive: true);
    final zipFile = File('${work.path}/package.zip');
    InputFileStream? archiveInput;
    try {
      onStage?.call(MultiTracksPackageStage.validating);
      await _Lz4FrameDecoder(
        maximumOutputBytes: maximumPackageBytes,
      ).decode(package, zipFile, isCancelled: isCancelled);
      onStage?.call(MultiTracksPackageStage.extracting);
      archiveInput = InputFileStream(zipFile.path);
      late final Archive archive;
      try {
        archive = ZipDecoder().decodeBuffer(archiveInput);
      } on Object catch (error) {
        throw MultiTracksPackageImportFailure('Invalid inner ZIP: $error');
      }
      if (archive.isEmpty || archive.length > maximumEntries) {
        throw const MultiTracksPackageImportFailure(
          'Invalid number of package entries',
        );
      }

      final entriesByStem = <int, ArchiveFile>{};
      final names = <String>{};
      var expandedBytes = 0;
      for (final entry in archive.files) {
        final name = entry.name;
        if (!entry.isFile ||
            entry.isSymbolicLink ||
            name.contains('/') ||
            name.contains(r'\') ||
            name == '.' ||
            name == '..' ||
            !names.add(name)) {
          throw const MultiTracksPackageImportFailure(
            'Unsafe or duplicate package entry',
          );
        }
        if (entry.size < 0) {
          throw const MultiTracksPackageImportFailure('Invalid entry size');
        }
        expandedBytes += entry.size;
        if (expandedBytes > maximumExpandedBytes) {
          throw const MultiTracksPackageImportFailure(
            'Expanded package exceeds size limit',
          );
        }
        final match = RegExp(r'^(\d+)\.m4a$').firstMatch(name);
        if (match != null) {
          final stemId = int.parse(match.group(1)!);
          if (entriesByStem.putIfAbsent(stemId, () => entry) != entry) {
            throw const MultiTracksPackageImportFailure('Duplicate stem ID');
          }
        } else if (!_isKnownArtwork(name)) {
          throw MultiTracksPackageImportFailure(
            'Unsupported package entry: $name',
          );
        }
      }
      if (entriesByStem.isEmpty) {
        throw const MultiTracksPackageImportFailure('Package has no audio');
      }

      final descriptors = <MultiTracksStemDescriptor>[];
      for (final stemId in entriesByStem.keys) {
        final matches = item.stems
            .where(
              (stem) =>
                  stem.stemId == stemId &&
                  (stem.keyId == selection.keyId || stem.anyKey),
            )
            .toList();
        if (matches.length != 1) {
          throw MultiTracksPackageImportFailure(
            'Stem $stemId has ${matches.length} matching descriptors',
          );
        }
        descriptors.add(matches.single);
      }
      descriptors.sort((left, right) {
        final byOrder = left.order.compareTo(right.order);
        return byOrder != 0 ? byOrder : left.stemId.compareTo(right.stemId);
      });
      final labels = uniqueLabels(
        descriptors.map((descriptor) => descriptor.part).toList(),
      );
      final rawArtist = item.raw['artist'];
      if (rawArtist != null && rawArtist is! String) {
        throw const MultiTracksPackageImportFailure('Invalid artist metadata');
      }

      final sourceDirectory = await Directory('${work.path}/source').create();
      final audioDirectory = await Directory('${work.path}/audio').create();
      final channels = <ChannelInfo>[];
      var wavBytes = 0;
      onStage?.call(MultiTracksPackageStage.transcoding);
      for (final (index, descriptor) in descriptors.indexed) {
        if (isCancelled?.call() ?? false) {
          throw const MultiTracksPackageImportFailure('Import cancelled');
        }
        onStemStarted?.call(index, descriptors.length, labels[index]);
        final archiveEntry = entriesByStem[descriptor.stemId]!;
        final source = File('${sourceDirectory.path}/${descriptor.stemId}.m4a');
        final sourceOutput = OutputFileStream(source.path);
        try {
          archiveEntry.writeContent(sourceOutput);
        } finally {
          sourceOutput.closeSync();
        }
        if (await source.length() != archiveEntry.size) {
          throw MultiTracksPackageImportFailure(
            'Incomplete stem ${descriptor.stemId}',
          );
        }
        await _validateArchiveEntry(source, archiveEntry);
        final output = File(
          '${audioDirectory.path}/${index.toString().padLeft(2, '0')}-${descriptor.stemId}.wav',
        );
        await transcoder.m4aToWav(input: source, output: output);
        await _validateWave(output);
        wavBytes += await output.length();
        if (wavBytes > maximumExpandedBytes) {
          throw const MultiTracksPackageImportFailure(
            'Decoded audio exceeds size limit',
          );
        }
        channels.add(
          ChannelInfo(
            label: labels[index],
            filePath: output.path,
            isClickOrGuide: descriptor.clickOrGuide,
            excludeFromFade: descriptor.clickOrGuide,
          ),
        );
        onProgress?.call(index + 1, descriptors.length);
      }

      final published = Directory(
        '${destinationDirectory.path}/multitracks-${selection.contentId}-${selection.keyId}',
      );
      final previous = Directory('${published.path}.previous');
      if (await previous.exists()) await previous.delete(recursive: true);
      final hadPublished = await published.exists();
      if (hadPublished) await published.rename(previous.path);
      try {
        await audioDirectory.rename(published.path);
        if (hadPublished && await previous.exists()) {
          await previous.delete(recursive: true);
        }
      } on Object {
        if (hadPublished && await previous.exists()) {
          await previous.rename(published.path);
        }
        rethrow;
      }

      final channelsByStem = <int, ChannelInfo>{
        for (var index = 0; index < descriptors.length; index++)
          descriptors[index].stemId: channels[index].copyWith(
            filePath:
                '${published.path}/${index.toString().padLeft(2, '0')}-${descriptors[index].stemId}.wav',
          ),
      };
      return MultiTracksImportedContent(
        track: Track(
          id: 'multitracks-${selection.contentId}-${selection.keyId}',
          title: item.title ?? 'MultiTracks ${selection.contentId}',
          artist: rawArtist as String?,
          key: _selectedKeyTitle(item.raw, selection.keyId),
          channels: descriptors
              .map((descriptor) => channelsByStem[descriptor.stemId]!)
              .toList(growable: false),
        ),
        stemIds: descriptors
            .map((descriptor) => descriptor.stemId)
            .toList(growable: false),
        expandedAudioBytes: wavBytes,
      );
    } finally {
      archiveInput?.closeSync();
      if (await work.exists()) await work.delete(recursive: true);
    }
  }
}

bool _isKnownArtwork(String name) => RegExp(
  r'^(Album[12]x\.jpg|Waveform[12]x\.(32|48|64)\.png)$',
).hasMatch(name);

String? _selectedKeyTitle(Map<String, Object?> raw, int keyId) {
  final keys = raw['keys'];
  if (keys is! List) return null;
  for (final key in keys) {
    if (key is Map && key['keyID'] == keyId && key['title'] is String) {
      return key['title'] as String;
    }
  }
  return null;
}

Future<void> _validateWave(File file) async {
  if (!await file.exists() || await file.length() < 44) {
    throw const MultiTracksPackageImportFailure('Transcoder produced no audio');
  }
  final input = await file.open();
  try {
    final header = await input.read(12);
    if (header.length != 12 ||
        String.fromCharCodes(header.sublist(0, 4)) != 'RIFF' ||
        String.fromCharCodes(header.sublist(8, 12)) != 'WAVE') {
      throw const MultiTracksPackageImportFailure(
        'Transcoder produced an invalid WAV',
      );
    }
  } finally {
    await input.close();
  }
}

Future<void> _validateArchiveEntry(File file, ArchiveFile entry) async {
  final crc = Crc32();
  await for (final chunk in file.openRead()) {
    crc.add(chunk);
  }
  if (entry.crc32 == null || crc.hash != entry.crc32) {
    throw MultiTracksPackageImportFailure('ZIP CRC mismatch for ${entry.name}');
  }
}

class _Lz4FrameDecoder {
  const _Lz4FrameDecoder({required this.maximumOutputBytes});

  static const _magic = 0x184d2204;
  final int maximumOutputBytes;

  Future<void> decode(
    File input,
    File output, {
    bool Function()? isCancelled,
  }) async {
    final source = await input.open();
    IOSink? sink;
    try {
      if (await _readUint32(source) != _magic) {
        throw const MultiTracksPackageImportFailure('Invalid LZ4 frame magic');
      }
      final flg = await _readByte(source);
      final bd = await _readByte(source);
      if ((flg >> 6) != 1 ||
          (flg & 0x20) == 0 ||
          (flg & 0x02) != 0 ||
          (bd & 0x8f) != 0) {
        throw const MultiTracksPackageImportFailure(
          'Unsupported LZ4 frame options',
        );
      }
      final blockMaximum = switch ((bd >> 4) & 0x07) {
        4 => 64 * 1024,
        5 => 256 * 1024,
        6 => 1024 * 1024,
        7 => 4 * 1024 * 1024,
        _ => throw const MultiTracksPackageImportFailure(
          'Invalid LZ4 block size',
        ),
      };
      final descriptor = BytesBuilder(copy: false)
        ..addByte(flg)
        ..addByte(bd);
      int? declaredContentSize;
      if ((flg & 0x08) != 0) {
        final bytes = await _readExact(source, 8);
        descriptor.add(bytes);
        declaredContentSize = ByteData.sublistView(
          bytes,
        ).getUint64(0, Endian.little);
        if (declaredContentSize > maximumOutputBytes) {
          throw const MultiTracksPackageImportFailure(
            'LZ4 content exceeds size limit',
          );
        }
      }
      if ((flg & 0x01) != 0) {
        descriptor.add(await _readExact(source, 4));
      }
      final headerChecksum = await _readByte(source);
      if (((_xxHash32(descriptor.takeBytes()) >> 8) & 0xff) != headerChecksum) {
        throw const MultiTracksPackageImportFailure(
          'LZ4 header checksum mismatch',
        );
      }

      final contentHash = _XxHash32();
      var written = 0;
      sink = output.openWrite();
      while (true) {
        if (isCancelled?.call() ?? false) {
          throw const MultiTracksPackageImportFailure('Import cancelled');
        }
        final rawSize = await _readUint32(source);
        if (rawSize == 0) break;
        final uncompressed = (rawSize & 0x80000000) != 0;
        final storedSize = rawSize & 0x7fffffff;
        if (storedSize <= 0 || storedSize > blockMaximum) {
          throw const MultiTracksPackageImportFailure('Invalid LZ4 block');
        }
        final stored = await _readExact(source, storedSize);
        if ((flg & 0x10) != 0 &&
            await _readUint32(source) != _xxHash32(stored)) {
          throw const MultiTracksPackageImportFailure(
            'LZ4 block checksum mismatch',
          );
        }
        final decoded = uncompressed
            ? stored
            : _decodeLz4Block(stored, blockMaximum);
        written += decoded.length;
        if (written > maximumOutputBytes) {
          throw const MultiTracksPackageImportFailure(
            'LZ4 content exceeds size limit',
          );
        }
        sink.add(decoded);
        contentHash.add(decoded);
      }
      if (declaredContentSize != null && written != declaredContentSize) {
        throw const MultiTracksPackageImportFailure(
          'LZ4 content size mismatch',
        );
      }
      if ((flg & 0x04) != 0 &&
          await _readUint32(source) != contentHash.digest()) {
        throw const MultiTracksPackageImportFailure(
          'LZ4 content checksum mismatch',
        );
      }
      if (await source.position() != await source.length()) {
        throw const MultiTracksPackageImportFailure(
          'Unexpected data after LZ4 frame',
        );
      }
      await sink.flush();
      await sink.close();
      sink = null;
    } on MultiTracksPackageImportFailure {
      rethrow;
    } on Object catch (error) {
      throw MultiTracksPackageImportFailure('Could not decode package: $error');
    } finally {
      await sink?.close();
      await source.close();
      if (sink != null && await output.exists()) await output.delete();
    }
  }
}

Uint8List _decodeLz4Block(Uint8List input, int maximumOutputBytes) {
  final output = BytesBuilder(copy: false);
  final history = <int>[];
  var offset = 0;
  int extendedLength(int initial) {
    var length = initial;
    if (initial == 15) {
      while (true) {
        if (offset >= input.length) {
          throw const MultiTracksPackageImportFailure('Truncated LZ4 block');
        }
        final next = input[offset++];
        length += next;
        if (next != 255) break;
      }
    }
    return length;
  }

  while (offset < input.length) {
    final token = input[offset++];
    final literalLength = extendedLength(token >> 4);
    if (offset + literalLength > input.length) {
      throw const MultiTracksPackageImportFailure('Truncated LZ4 literals');
    }
    for (var index = 0; index < literalLength; index++) {
      history.add(input[offset++]);
    }
    if (history.length > maximumOutputBytes) {
      throw const MultiTracksPackageImportFailure('LZ4 block is too large');
    }
    if (offset == input.length) break;
    if (offset + 2 > input.length) {
      throw const MultiTracksPackageImportFailure('Truncated LZ4 match');
    }
    final matchOffset = input[offset] | (input[offset + 1] << 8);
    offset += 2;
    if (matchOffset == 0 || matchOffset > history.length) {
      throw const MultiTracksPackageImportFailure('Invalid LZ4 match offset');
    }
    final matchLength = extendedLength(token & 0x0f) + 4;
    if (history.length + matchLength > maximumOutputBytes) {
      throw const MultiTracksPackageImportFailure('LZ4 block is too large');
    }
    for (var index = 0; index < matchLength; index++) {
      history.add(history[history.length - matchOffset]);
    }
  }
  output.add(history);
  return output.takeBytes();
}

Future<int> _readByte(RandomAccessFile file) async {
  final bytes = await file.read(1);
  if (bytes.length != 1) {
    throw const MultiTracksPackageImportFailure('Truncated package');
  }
  return bytes.single;
}

Future<Uint8List> _readExact(RandomAccessFile file, int length) async {
  final builder = BytesBuilder(copy: false);
  var remaining = length;
  while (remaining > 0) {
    final chunk = await file.read(remaining);
    if (chunk.isEmpty) {
      throw const MultiTracksPackageImportFailure('Truncated package');
    }
    builder.add(chunk);
    remaining -= chunk.length;
  }
  return builder.takeBytes();
}

Future<int> _readUint32(RandomAccessFile file) async =>
    ByteData.sublistView(await _readExact(file, 4)).getUint32(0, Endian.little);

int _rotateLeft32(int value, int count) =>
    (((value << count) | (value >>> (32 - count))) & 0xffffffff);

int _xxRound(int accumulator, int input) {
  var value = (accumulator + input * 0x85ebca77) & 0xffffffff;
  value = _rotateLeft32(value, 13);
  return (value * 0x9e3779b1) & 0xffffffff;
}

int _xxHash32(List<int> bytes) {
  final hash = _XxHash32()..add(bytes);
  return hash.digest();
}

class _XxHash32 {
  static const _prime1 = 0x9e3779b1;
  static const _prime2 = 0x85ebca77;
  static const _prime3 = 0xc2b2ae3d;
  static const _prime4 = 0x27d4eb2f;
  static const _prime5 = 0x165667b1;

  final _tail = <int>[];
  var _totalLength = 0;
  var _v1 = (_prime1 + _prime2) & 0xffffffff;
  var _v2 = _prime2;
  var _v3 = 0;
  var _v4 = (-_prime1) & 0xffffffff;

  void add(List<int> bytes) {
    _totalLength += bytes.length;
    var offset = 0;
    if (_tail.isNotEmpty) {
      final needed = 16 - _tail.length;
      final copied = needed < bytes.length ? needed : bytes.length;
      _tail.addAll(bytes.sublist(0, copied));
      offset += copied;
      if (_tail.length == 16) {
        _consume16(Uint8List.fromList(_tail), 0);
        _tail.clear();
      }
    }
    final view = bytes is Uint8List ? bytes : Uint8List.fromList(bytes);
    while (offset + 16 <= view.length) {
      _consume16(view, offset);
      offset += 16;
    }
    if (offset < view.length) _tail.addAll(view.sublist(offset));
  }

  void _consume16(Uint8List bytes, int offset) {
    final data = ByteData.sublistView(bytes);
    _v1 = _xxRound(_v1, data.getUint32(offset, Endian.little));
    _v2 = _xxRound(_v2, data.getUint32(offset + 4, Endian.little));
    _v3 = _xxRound(_v3, data.getUint32(offset + 8, Endian.little));
    _v4 = _xxRound(_v4, data.getUint32(offset + 12, Endian.little));
  }

  int digest() {
    var hash = _totalLength >= 16
        ? (_rotateLeft32(_v1, 1) +
                  _rotateLeft32(_v2, 7) +
                  _rotateLeft32(_v3, 12) +
                  _rotateLeft32(_v4, 18)) &
              0xffffffff
        : _prime5;
    hash = (hash + _totalLength) & 0xffffffff;
    final data = ByteData.sublistView(Uint8List.fromList(_tail));
    var offset = 0;
    while (offset + 4 <= _tail.length) {
      hash =
          (hash + data.getUint32(offset, Endian.little) * _prime3) & 0xffffffff;
      hash = (_rotateLeft32(hash, 17) * _prime4) & 0xffffffff;
      offset += 4;
    }
    while (offset < _tail.length) {
      hash = (hash + _tail[offset++] * _prime5) & 0xffffffff;
      hash = (_rotateLeft32(hash, 11) * _prime1) & 0xffffffff;
    }
    hash ^= hash >>> 15;
    hash = (hash * _prime2) & 0xffffffff;
    hash ^= hash >>> 13;
    hash = (hash * _prime3) & 0xffffffff;
    hash ^= hash >>> 16;
    return hash & 0xffffffff;
  }
}
