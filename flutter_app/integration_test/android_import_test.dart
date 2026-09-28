import 'dart:io';
import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:integration_test/integration_test.dart';

// Select Download/PHASE5-A/Click.wav, then Download/PHASE5-B/Click.wav
// in the real Android document picker. Fixtures must have distinct bytes.
void main() {
  IntegrationTestWidgetsFlutterBinding.ensureInitialized();
  testWidgets('D4 Android: duas importações content:// com mesmo nome preservam áudio', (tester) async {
    const channel = MethodChannel('wtracks/file_picker');
    final first = (await channel.invokeListMethod<String>('pickAndImport'))!.single;
    final original = await File(first).readAsBytes();
    final second = (await channel.invokeListMethod<String>('pickAndImport'))!.single;
    expect(first, isNot(second));
    expect(File(first).parent.path, isNot(File(second).parent.path));
    expect(await File(first).readAsBytes(), original);
    expect(await File(second).readAsBytes(), isNot(original));
    await File(first).parent.delete(recursive: true);
    await File(second).parent.delete(recursive: true);
  });
}
