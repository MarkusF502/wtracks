import 'dart:convert';
import 'dart:io';

import 'package:crypto/crypto.dart';
import 'package:flutter_app/services/multitracks_package_downloader.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  late Directory root;
  setUp(() async {
    root = await Directory.systemTemp.createTemp('multitracks-download-');
  });
  tearDown(() => root.delete(recursive: true));

  test('downloads, validates MD5 and atomically replaces a package', () async {
    final bytes = utf8.encode('new package');
    final destination = File('${root.path}/202.mtrack')
      ..writeAsStringSync('old package');
    final downloader = MultiTracksPackageDownloader(
      transport: _FakeDownloadTransport(bytes),
    );

    final result = await downloader.download(
      url: _trustedUrl,
      destinationDirectory: root,
      packageId: 202,
    );

    expect(result.file.path, destination.path);
    expect(result.file.readAsBytesSync(), bytes);
    expect(result.md5Validated, isTrue);
    expect(File('${destination.path}.part').existsSync(), isFalse);
    expect(File('${destination.path}.previous').existsSync(), isFalse);
  });

  test('MD5 mismatch keeps the previous package and removes staging', () async {
    final destination = File('${root.path}/202.mtrack')
      ..writeAsStringSync('old package');
    final downloader = MultiTracksPackageDownloader(
      transport: _FakeDownloadTransport(
        utf8.encode('damaged package'),
        contentMd5: base64Encode(md5.convert(utf8.encode('other')).bytes),
      ),
    );

    await expectLater(
      downloader.download(
        url: _trustedUrl,
        destinationDirectory: root,
        packageId: 202,
      ),
      throwsA(isA<MultiTracksDownloadFailure>()),
    );

    expect(destination.readAsStringSync(), 'old package');
    expect(File('${destination.path}.part').existsSync(), isFalse);
  });

  test('rejects untrusted URLs before opening a connection', () async {
    final transport = _FakeDownloadTransport(utf8.encode('package'));
    final downloader = MultiTracksPackageDownloader(transport: transport);

    await expectLater(
      downloader.download(
        url: Uri.parse('https://example.invalid/package.mtrack'),
        destinationDirectory: root,
        packageId: 202,
      ),
      throwsA(isA<MultiTracksDownloadFailure>()),
    );
    expect(transport.opened, isFalse);
  });

  test('cancellation removes staging and publishes nothing', () async {
    final downloader = MultiTracksPackageDownloader(
      transport: _FakeDownloadTransport(utf8.encode('package')),
    );

    await expectLater(
      downloader.download(
        url: _trustedUrl,
        destinationDirectory: root,
        packageId: 202,
        isCancelled: () => true,
      ),
      throwsA(isA<MultiTracksDownloadCancelled>()),
    );
    expect(File('${root.path}/202.mtrack').existsSync(), isFalse);
    expect(File('${root.path}/202.mtrack.part').existsSync(), isFalse);
  });
}

final _trustedUrl = Uri.parse(
  'https://playback.blob.core.windows.net/cloud/example/streaming/202.mtrack?sig=redacted',
);

class _FakeDownloadTransport implements MultiTracksDownloadTransport {
  _FakeDownloadTransport(this.data, {String? contentMd5})
    : contentMd5 = contentMd5 ?? base64Encode(md5.convert(data).bytes);

  final List<int> data;
  final String contentMd5;
  bool opened = false;

  @override
  Future<MultiTracksDownloadSource> open(
    Uri url, {
    required Set<String> allowedHosts,
  }) async {
    opened = true;
    return MultiTracksDownloadSource(
      effectiveUrl: url,
      statusCode: 200,
      bytes: Stream.value(data),
      contentLength: data.length,
      contentMd5: contentMd5,
      contentType: 'application/octet-stream',
    );
  }
}
