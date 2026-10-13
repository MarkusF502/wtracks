# Click agenda origin — static findings (cycle 6-8 follow-up)

Binary: `Playback` main executable, SHA256 `2a11a6f98134ba035c9df55d0ab5cabd376597ce83980ff40704f4f42b1ad423`,
profile `decompiled/Playback/2a11a6f98134-2a4a38e34a84`. No iOS execution; everything below is static.

## Observed

- Callers of the ClickAudioUnit wrapper constructor `0x1001de0f4`: `FUN_100545a98` = `ClickChannel` initializer
  (ivars `meterStartDate`, `currentElementIsLastSongMapElementEnding`). Callers of `0x1001de6c8` (`updateClickTimes`):
  `FUN_10034fc58`, `FUN_100350578`, `FUN_100350d68`, all of which walk `Song.workingCopyArrangement` → `storedSections`.
- `SongMap.Element` (Swift) owns four lazy arrays `accentGridTimes`, `quarterGridTimes`, `eighthGridTimes`,
  `sixteenthGridTimes` (getters `0x100212bb0`, `0x100213f64`, `0x100213f74`, `0x100213f84`, all through `FUN_100213f94(storage, voice 0..3)`).
  The four voices of our click bank match these four arrays. The click agenda is therefore a precomputed list of times per
  song-map element, not a runtime generator driven by one global BPM.
- Element times derive from `SongSection.startTimeOriginal`, `storedStartTimeTrimOffset`, and a tempo ratio built from the song's
  `bpm` and `bpmOriginal` (ratio guarded to >= 1.0 values; content types with `(contentTypeID & 0xfe) == 0x10` skip it).
  Elements also carry `fullTimelineStartTime/EndTime`, `trimTimelineStartTime/EndTime`, `hasTrimmedStart`, `liveLoopCount`,
  `privateInfiniteLoop`, and `editMode`.
- Song map editing exposes `stagedPlaySectionGuideCue` and `stagedPlaySectionCountIn`: sections have a play-time guide cue and a count-in.
  `SongMap.AutomationCue` and `SongMap.MIDIEvent` are separate ObjC classes (fields not recovered).

## Not recovered / our choices (not equivalence)

- The body of `FUN_100213f94` (grid generation arithmetic) and the direction of the `bpm/bpmOriginal` ratio were not read in full.
- WTracks uses one global BPM / meter / offset for the whole song (`ClickSettings`) and our own subdivision policy
  (accent replaces the quarter on the downbeat; eighth on halves; sixteenth on the remaining quarters).
- Open gaps this implies: per-section tempo and meter (song map), per-section count-in, and section-driven guide cues.
