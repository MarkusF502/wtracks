import 'dart:async';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'harness/harness_support.dart';
import 'package:flutter_app/services/click_resource_service.dart';

class DelayedClickEngine extends FakeEngine {
  final entered = Completer<void>();
  final release = Completer<void>();
  @override
  Future<bool> loadClickBankAsync(List<String?> paths) async {
    entered.complete();
    await release.future;
    return super.loadClickBankAsync(paths);
  }
}

class FailingBankEngine extends FakeEngine {
  bool failBank = false;
  @override
  Future<bool> loadClickBankAsync(List<String?> paths) async {
    if (failBank) return false;
    return super.loadClickBankAsync(paths);
  }
}

class SyntheticResourceService extends ClickResourceService {
  @override
  Future<List<String?>> prepare(String family) async => List.filled(4, null);
}


void main() {
  TestWidgetsFlutterBinding.ensureInitialized();
  test('legacy click preserves fractional BPM, offset and synthetic /4 defaults', () {
    final settings = ClickSettings.fromJson({'bpm': 123.456, 'beatOffsetSeconds': 1.25, 'timeSignatureNumerator': 3});
    expect(settings.schemaVersion, 1);
    expect(settings.bpm, 123.456);
    expect(settings.beatOffsetSeconds, 1.25);
    expect(settings.timeSignatureDenominator, 4);
    expect(settings.bpmUnit, 4);
    expect(settings.timbreFamily, 'synthetic');
    expect(settings.eighthGain, 0);
    expect(settings.sixteenthGain, 0);
  });
  test('new click round-trip preserves compound meter and subdivisions', () {
    const settings = ClickSettings(bpm: 87.25, timeSignatureNumerator: 6, timeSignatureDenominator: 8,
      bpmUnit: 8, accentGain: 0.7, quarterGain: 0.6, eighthGain: 0.5, sixteenthGain: 0.4,
      volume: 0.8, timbreFamily: 'Custom', calibrated: true);
    expect(ClickSettings.fromJson(settings.toJson()).toJson(), settings.toJson());
  });
  test('invalid configuration is rejected before reaching native', () {
    for (final settings in [const ClickSettings(bpm: 0), const ClickSettings(bpm: double.nan),
      const ClickSettings(timeSignatureDenominator: 3), const ClickSettings(bpmUnit: 0),
      const ClickSettings(beatOffsetSeconds: -1), const ClickSettings(volume: 2.1)]) {
      expect(settings.isValid, false);
      expect(() => ClickSettings.fromJson(settings.toJson()), throwsFormatException);
    }
  });
  test('track load and edits apply the complete settings contract', () async {
    final engine = FakeEngine();
    final container = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine)]);
    addTearDown(container.dispose);
    final notifier = container.read(currentTrackProvider.notifier);
    const settings = ClickSettings(timeSignatureNumerator: 7, timeSignatureDenominator: 8,
      bpmUnit: 8, eighthGain: 0.5, volume: 0.3);
    expect(await notifier.load(const Track(id: 'click', title: 'Click', channels: [], clickSettings: settings)), true);
    expect(engine.configuredClick?.toJson(), settings.toJson());
    expect(engine.calls.where((c) => c.startsWith('clickSound')).length, 4);
    notifier.updateBpm(125.75);
    expect(engine.configuredClick?.bpm, 125.75);
    expect(engine.configuredClick?.timeSignatureDenominator, 8);
    expect(engine.configuredClick?.eighthGain, 0.5);
    expect(notifier.updateClickSettings(const ClickSettings(bpm: -2)), false);
    expect(container.read(currentTrackProvider)?.clickSettings.bpm, 125.75);
  });
  test('unload during click decode does not publish obsolete track or configure it', () async {
    final engine = DelayedClickEngine();
    final container = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine),
      clickResourceServiceProvider.overrideWithValue(SyntheticResourceService())]);
    addTearDown(container.dispose);
    final notifier = container.read(currentTrackProvider.notifier);
    final loading = notifier.load(const Track(id: 'obsolete', title: 'Obsolete', channels: []));
    await engine.entered.future;
    final unloading = notifier.unload();
    engine.release.complete();
    expect(await loading, false);
    await unloading;
    expect(container.read(currentTrackProvider), null);
    expect(engine.configuredClick, null);
    expect(engine.calls.where((call) => call.startsWith('clickSound')).length, 4);
    expect(engine.calls.last, 'unload');
  });

  test('failed timbre bank leaves saved family and native settings intact', () async {
    final engine = FailingBankEngine();
    final container = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine),
      clickResourceServiceProvider.overrideWithValue(SyntheticResourceService())]);
    addTearDown(container.dispose);
    final notifier = container.read(currentTrackProvider.notifier);
    const settings = ClickSettings(timbreFamily: 'Classic', volume: 0.3);
    expect(await notifier.load(const Track(id: 'bank', title: 'Bank', channels: [], clickSettings: settings)), true);
    engine.failBank = true;
    final calls = engine.calls.length;
    expect(await notifier.updateClickTimbre('Woodblock'), false);
    expect(container.read(currentTrackProvider)?.clickSettings.toJson(), settings.toJson());
    expect(engine.configuredClick?.toJson(), settings.toJson());
    expect(engine.calls.length, calls);
  });

}
