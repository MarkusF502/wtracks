import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:flutter_app/models/track.dart';
import 'package:flutter_app/models/song_section.dart';
import 'package:flutter_app/providers/engine_provider.dart';
import 'package:flutter_app/screens/section_editor_screen.dart';
import 'harness/harness_support.dart';

void main() {
  test('old tracks gain empty sections and new ordered sections round-trip', () {
    final old = Track.fromJson({'id': 'old', 'title': 'Old', 'channels': []});
    expect(old.schemaVersion, 1);
    expect(old.sections, isEmpty);
    const section = SongSection(id: 'intro', name: 'Intro', startSeconds: 1.25, endSeconds: 10);
    final track = old.copyWith(sections: [section, const SongSection(id: 'verse', name: 'Verse', startSeconds: 10, endSeconds: 20)]);
    expect(Track.fromJson(track.toJson()).toJson(), track.toJson());
    expect(track.toJson()['schemaVersion'], Track.currentSchemaVersion);
  });
  test('invalid, overlapping, duplicate and unordered sections are rejected', () {
    const a = SongSection(id: 'a', name: 'A', startSeconds: 0, endSeconds: 10);
    for (final list in [
      [a, const SongSection(id: 'b', name: 'B', startSeconds: 9, endSeconds: 20)],
      [a, const SongSection(id: 'a', name: 'B', startSeconds: 10, endSeconds: 20)],
      [const SongSection(id: 'b', name: 'B', startSeconds: 10, endSeconds: 20), a],
      [const SongSection(id: 'bad', name: 'Bad', startSeconds: -1, endSeconds: 1)],
      [const SongSection(id: 'bad', name: 'Bad', startSeconds: 1, endSeconds: 1)],
      [const SongSection(id: 'bad', name: 'Bad', startSeconds: double.nan, endSeconds: 1)],
    ]) {
      expect(SongSection.validSequence(list), false);
      expect(() => SongSection.fromJsonList(list.map((s) => s.toJson()).toList()), throwsFormatException);
    }
  });
  testWidgets('section CRUD persists, dialog exits cleanly, navigation seeks without play', (tester) async {
    final engine = FakeEngine();
    final persistence = InMemoryPersistence();
    final container = ProviderContainer(overrides: [engineProvider.overrideWithValue(engine),
      persistenceServiceProvider.overrideWithValue(persistence)]);

    container.read(currentTrackProvider.notifier).setLoadedTrack(const Track(id: 'song', title: 'Song', channels: []));
    await tester.pumpWidget(UncontrolledProviderScope(container: container,
      child: const MaterialApp(home: SectionEditorScreen(trackId: 'song'))));
    await tester.tap(find.byTooltip('Adicionar seção'));
    await tester.pumpAndSettle();
    await tester.enterText(find.byKey(const Key('section-name')), 'Verso');
    await tester.enterText(find.byKey(const Key('section-start')), '2.5');
    await tester.enterText(find.byKey(const Key('section-end')), '12');
    await tester.tap(find.text('Salvar'));
    await tester.pumpAndSettle();
    expect(tester.takeException(), null);
    expect(persistence.tracks['song']?.sections.single.name, 'Verso');
    await tester.tap(find.text('Verso'));
    await tester.pump();
    expect(engine.calls, contains('seek(2.5)'));
    expect(engine.calls, isNot(contains('play')));
    await tester.tap(find.byTooltip('Editar seção'));
    await tester.pumpAndSettle();
    await tester.enterText(find.byKey(const Key('section-name')), 'Refrão');
    await tester.tap(find.text('Salvar'));
    await tester.pumpAndSettle();
    expect(persistence.tracks['song']?.sections.single.name, 'Refrão');
    await tester.tap(find.byTooltip('Excluir seção'));
    await tester.pumpAndSettle();
    await tester.tap(find.text('Excluir'));
    await tester.pumpAndSettle();
    expect(persistence.tracks['song']?.sections, isEmpty);
    expect(tester.takeException(), null);
    await tester.pumpWidget(const SizedBox.shrink());
    container.dispose();
  });
}
