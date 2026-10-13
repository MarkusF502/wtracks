import 'dart:io';
import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/services/click_resource_service.dart';
import 'package:flutter_app/native/wtracks_bindings.dart';
import 'package:flutter_app/models/track.dart';
import 'harness/harness_support.dart';

class FileAssetBundle extends CachingAssetBundle {
  @override
  Future<ByteData> load(String key) async {
    final bytes = await File(key).readAsBytes();
    return ByteData.sublistView(bytes);
  }
}

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  test('every packaged family materializes four PCM voices and synthetic needs no files', () async {
    final directory = await Directory.systemTemp.createTemp('click-test-');
    addTearDown(() => directory.delete(recursive: true));
    final service = ClickResourceService(bundle: FileAssetBundle(), directoryResolver: () async => directory);
    final families = await service.families();
    expect(families.length, 11);
    for (final family in families) {
      final paths = await service.prepare(family);
      expect(paths.length, 4);
      for (final path in paths) {
        final bytes = await File(path!).readAsBytes();
        expect(String.fromCharCodes(bytes.take(4)), 'RIFF');
      }
      expect(await service.prepare(family), paths);
    }
    expect(await service.prepare('synthetic'), [null, null, null, null]);
    await expectLater(service.prepare('missing'), throwsFormatException);
  });
  test('real FFI configures compound click, loads Classic asynchronously and clears voices', () async {
    final engine = WTracksEngine();
    engine.initialise(); // Creates shared engine even where no audio device is available.
    addTearDown(engine.shutdown);
    final directory = await Directory.systemTemp.createTemp('click-native-');
    addTearDown(() => directory.delete(recursive: true));
    final service = ClickResourceService(bundle: FileAssetBundle(), directoryResolver: () async => directory);
    final paths = await service.prepare('Classic');
    expect(await engine.loadClickBankAsync(paths), true, reason: engine.lastError);
    expect(await engine.loadClickBankAsync([paths[0], '/missing/invalid.wav', paths[2], paths[3]]), false);
    expect(await engine.loadClickBankAsync([paths[0]]), false);
    expect(engine.configureClick(const ClickSettings(timeSignatureNumerator: 6, timeSignatureDenominator: 8,
      bpmUnit: 8, bpm: 97.375, eighthGain: 0.7, volume: 0.4)), true, reason: engine.lastError);
    expect(engine.configureClick(const ClickSettings(bpmUnit: 3)), false);
    expect(await engine.loadClickBankAsync([null, null, null, null]), true);
  }, skip: !nativeEngineAvailable() ? 'Native library unavailable' : false);
}
