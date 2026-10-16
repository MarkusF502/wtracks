import 'dart:async';
import 'dart:convert';
import 'dart:io';

import 'package:crypto/crypto.dart';

class MultiTracksDownloadSource {
  const MultiTracksDownloadSource({
    required this.effectiveUrl,
    required this.statusCode,
    required this.bytes,
    this.contentLength,
    this.contentMd5,
    this.contentType,
  });

  final Uri effectiveUrl;
  final int statusCode;
  final Stream<List<int>> bytes;
  final int? contentLength;
  final String? contentMd5;
  final String? contentType;
}

abstract class MultiTracksDownloadTransport {
  Future<MultiTracksDownloadSource> open(
    Uri url, {
    required Set<String> allowedHosts,
  });
}

class IoMultiTracksDownloadTransport implements MultiTracksDownloadTransport {
  IoMultiTracksDownloadTransport({HttpClient? client})
    : _client = client ?? HttpClient();

  final HttpClient _client;

  @override
  Future<MultiTracksDownloadSource> open(
    Uri url, {
    required Set<String> allowedHosts,
  }) async {
    var current = url;
    for (var redirects = 0; redirects <= 3; redirects++) {
      _validateUrl(current, allowedHosts);
      final request = await _client.getUrl(current);
      request.followRedirects = false;
      request.headers.set(HttpHeaders.acceptEncodingHeader, 'identity');
      final response = await request.close().timeout(
        const Duration(seconds: 60),
      );
      if (_isRedirect(response.statusCode)) {
        final location = response.headers.value(HttpHeaders.locationHeader);
        await response.drain<void>();
        if (location == null || redirects == 3) {
          throw const MultiTracksDownloadFailure('Invalid download redirect');
        }
        current = current.resolve(location);
        continue;
      }
      return MultiTracksDownloadSource(
        effectiveUrl: current,
        statusCode: response.statusCode,
        bytes: response,
        contentLength: response.contentLength >= 0
            ? response.contentLength
            : null,
        contentMd5: response.headers.value('content-md5'),
        contentType: response.headers.contentType?.mimeType,
      );
    }
    throw const MultiTracksDownloadFailure('Too many redirects');
  }

  void close({bool force = false}) => _client.close(force: force);
}

class MultiTracksDownloadedPackage {
  const MultiTracksDownloadedPackage({
    required this.file,
    required this.length,
    required this.md5Base64,
    required this.md5Validated,
  });

  final File file;
  final int length;
  final String md5Base64;
  final bool md5Validated;
}

class MultiTracksDownloadFailure implements Exception {
  const MultiTracksDownloadFailure(this.message);

  final String message;

  @override
  String toString() => 'MultiTracksDownloadFailure: $message';
}

class MultiTracksDownloadCancelled extends MultiTracksDownloadFailure {
  const MultiTracksDownloadCancelled() : super('Download cancelled');
}

class MultiTracksPackageDownloader {
  factory MultiTracksPackageDownloader({
    required MultiTracksDownloadTransport transport,
    Set<String> allowedHosts = const {'playback.blob.core.windows.net'},
    int maximumBytes = 2 * 1024 * 1024 * 1024,
  }) => MultiTracksPackageDownloader._(transport, allowedHosts, maximumBytes);

  MultiTracksPackageDownloader._(
    this._transport,
    this.allowedHosts,
    this.maximumBytes,
  );

  final MultiTracksDownloadTransport _transport;
  final Set<String> allowedHosts;
  final int maximumBytes;

  Future<MultiTracksDownloadedPackage> download({
    required Uri url,
    required Directory destinationDirectory,
    required int packageId,
    bool Function()? isCancelled,
    void Function(int received, int? total)? onProgress,
  }) async {
    _validateUrl(url, allowedHosts);
    if (packageId <= 0) {
      throw ArgumentError.value(packageId, 'packageId', 'must be positive');
    }
    final source = await _transport.open(url, allowedHosts: allowedHosts);
    _validateUrl(source.effectiveUrl, allowedHosts);
    if (source.statusCode != HttpStatus.ok) {
      throw MultiTracksDownloadFailure(
        'Unexpected download status ${source.statusCode}',
      );
    }
    if (source.contentType != null &&
        source.contentType != ContentType.binary.mimeType) {
      throw MultiTracksDownloadFailure(
        'Unexpected content type ${source.contentType}',
      );
    }
    final announcedLength = source.contentLength;
    if (announcedLength != null && announcedLength > maximumBytes) {
      throw const MultiTracksDownloadFailure('Package exceeds size limit');
    }

    await destinationDirectory.create(recursive: true);
    final destination = File('${destinationDirectory.path}/$packageId.mtrack');
    final partial = File('${destination.path}.part');
    if (await partial.exists()) await partial.delete();

    IOSink? output;
    Digest? actualDigest;
    var received = 0;
    final digestSink = md5.startChunkedConversion(
      ChunkedConversionSink<Digest>.withCallback((digests) {
        actualDigest = digests.single;
      }),
    );
    try {
      output = partial.openWrite();
      await for (final chunk in source.bytes) {
        if (isCancelled?.call() ?? false) {
          throw const MultiTracksDownloadCancelled();
        }
        received += chunk.length;
        if (received > maximumBytes) {
          throw const MultiTracksDownloadFailure('Package exceeds size limit');
        }
        output.add(chunk);
        digestSink.add(chunk);
        onProgress?.call(received, announcedLength);
      }
      await output.flush();
      await output.close();
      output = null;
      digestSink.close();

      if (announcedLength != null && received != announcedLength) {
        throw const MultiTracksDownloadFailure('Incomplete package');
      }
      final digest = actualDigest;
      if (digest == null) {
        throw const MultiTracksDownloadFailure('Could not calculate MD5');
      }
      final md5Base64 = base64Encode(digest.bytes);
      final expectedMd5 = source.contentMd5;
      if (expectedMd5 != null && expectedMd5 != md5Base64) {
        throw const MultiTracksDownloadFailure('Content-MD5 mismatch');
      }
      await _publish(partial, destination);
      return MultiTracksDownloadedPackage(
        file: destination,
        length: received,
        md5Base64: md5Base64,
        md5Validated: expectedMd5 != null,
      );
    } catch (_) {
      await output?.close();
      digestSink.close();
      if (await partial.exists()) await partial.delete();
      rethrow;
    }
  }

  Future<void> _publish(File partial, File destination) async {
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
  }
}

bool _isRedirect(int statusCode) =>
    statusCode == HttpStatus.movedPermanently ||
    statusCode == HttpStatus.found ||
    statusCode == HttpStatus.seeOther ||
    statusCode == HttpStatus.temporaryRedirect ||
    statusCode == HttpStatus.permanentRedirect;

void _validateUrl(Uri url, Set<String> allowedHosts) {
  if (url.scheme != 'https' || !allowedHosts.contains(url.host)) {
    throw const MultiTracksDownloadFailure('Untrusted download URL');
  }
}
