# Playback 8.5.3 — local feature inventory (static evidence)

Sources: Core Data model `Payload/Playback.app/AppData.momd/AppData 145.mom` decoded by `scripts/decode_momd.py`
(`analysis/coredata-model-145.json`, 39 entities); Mach-O strings (`analysis/ui/main-ui-strings.txt`, 1472 user-visible
strings); Ghidra export of the main executable (39996 functions, 1 failed: `0x100194a54` "Unable to find unique hash for varnode");
subsystem contracts (`subsystem-contracts.md`). No iOS execution. Cloud, account, purchase, download, ads, Planning Center and
Church-licence features are out of scope by user decision.

Status: DONE = implemented in WTracks with tests; PARTIAL; TODO. "Own" marks a design the binary does not prescribe.

| Feature | Evidence | Status |
|---|---|---|
| Click: 4 voices, tempo/meter/offset | `SongClicks.stored{Accents,Quarters,Eighths,Sixteenths}` (arrays of times), `ClickAU`, strings "Sub click accent/fourth/eighth/sixteenth" | DONE |
| Tempo map (BPM changes along the song) | `SongTempo{storedBPM, storedTimecode, storedTempoID}`, `MetadataClick{bpm,timeSignatureID}`, `MetadataTimeSignature{beatUnit,beatsPerBar}` | DONE (tempo changes: `TempoChange`, native `TempoMap.h`) |
| Song map: sections with trim, loop count, infinite loop, preset infinite loop, count-in, guide cue | `SongSection{startTimeOriginal,endTimeOriginal,storedStart/EndTimeTrimOffset,loopCount,loopInfinite,presetInfiniteLoop,storedPlayCountIn,storedPlayGuideCue,storedAutomationCues}`, strings "Play Section Count In", "Play Section Guide Cue", "Enable Preset Infinite Loop" | loopCount + preset infinite loop DONE (native counted/preset loops); count-in on play from a section start DONE (pre-roll, own design: `Preroll.h`); guide/count flags drive dynamic guides DONE; trim DONE (`configureSkips`: sample-exact jumps over trimmed areas outside loops with a decoded 3 s bridge, cues inside do not fire — string "Cues contained within a trimmed area will not fire during playback"; loops/presets/pre-roll use the played part; jumping inside loops and guides placed in trimmed areas are own choices); loop pass counter in the transport header DONE |
| Dynamic guide cues: section name + count | `GuideCue(cueType, sectionTypeID, cueSequenceTimecode, songMapElementStartTimecode, cueEnabled, cueFilePath, replacementCountCueFilePath)`, settings "Count Into Each Section", "Song Section Pre-roll", "Guide Cue Language"; GuideAU "selects normal or replacement resource" | DONE (`dynamic_guides.dart`, `GuideTimeline` replacement, `Preroll.h`). Evidence (GuideDSPKernel::process, GuideAUFramework 0x6140): type-0 cues play only with a next element queued or for sectionTypeID 7; replacement = type 0/section 7 when the queued element is the current one, or disabled type-1 cues → WTracks: section names are silent while the active loop wraps, counts always play. Own rules: cues fill the bar before the section (tempo segment just before its start); name on beat 1 covering the first half of the bar, spoken count on the rest; section type 7 and type-1 cues have no identified counterpart; pre-roll = one bar of click + count when play() starts exactly on a section start (stems, MIDI and timecode wait). Not compared with iOS |
| Guide files by language/gender/type | filenames `guidecue-{count,section}-<lang>-<gender>-<name>` | DONE: catalog parsed from names (8 voices), section-name matching with pt/es aliases (own) |
| Mixer: tracks, buses, per-song bus level/mute/solo, master (per song), VU meters, fader default 80% | `SongTrack`, `SongBus{id,muted,volume}`, `GlobalBus`, `SongArrangement.masterVolumeLevel`, `MixerVUMeterView`, strings "Fader Default Level 80%", "Song Specific Buses", "Song Specific Master Fader" | channel gain/mute/solo/master DONE (20 ms de-zipper from the BusChannel/Mixer ParameterRamper); VU meters DONE (post-fader channel peaks + L/R output peaks, lock-free `PeakMeter`, own ballistics: instant rise, 24 dB/s fall, -60..0 dB, yellow from -12, red from -3); buses DONE per song (`SongBus`, up to 16, strips + meters in the mixer, "Buses e roteamento" screen); bus names come from the server in Playback and are user-defined here; global buses / "Song Specific Buses" switch and "Song Specific Master Fader" switch not reproduced (levels and master are always per song); "Fader Default Level 80%" DONE as a setting for imported songs (`DefaultsManager.reducedDefaultFaderLevelEnabled` confirmed; where it is applied is our reading); buses TODO |
| Output routing: track -> bus -> output channel; "Send Click & Guide to left and tracks to right" | `OutputRouting`, `OutputChannel`, `AudioDevice`, `MetadataTrack.busID`, `SongTrack.isClickOrGuide`, strings | DONE: track → bus → output, bus = BusChannelAU contract (ramped gain, mute gate, output base, mono (L+R)/2 or stereo, invalid route silent), verified against `BusChannelDSPKernel::process` 0x58b0; bus automation (`bus:<i>:volume|mute`); solo across tracks and buses (own rule); "Send Click & Guide to left and tracks to right" = click/guides on output 1, every track/bus mono on output 2 (own reading; Playback ties it to `autoPanEnabled`). Device output channel naming (`OutputChannel`) not reproduced |
| Automation: points on the timeline that move faders / master / pad over a transition length in beats; mute is instant | `AutomationCue{name,details,transitionBeats,sampleTimecode,sequenceTimecode,applyTransitionLengthCorrection,storedItems}`, `AutomationItem{automationID,storedValue}`, strings "Transition length is the length of time (in beats) the faders will start leading to the Automation point. Mute or unmute changes are instant.", "Set the Automation Snapshot", copy/paste | DONE for channel volume/mute and master (`MixerAutomation.h`, `mixer_automation.dart`, `MixerAutomationScreen`; buses come with the bus cycle). Own design: linear ramp of `transitionBeats` beats (tempo just before the point) ending at the point, mute switches at the point (20 ms de-zipper, as the BusChannel/Mixer ParameterRamper: sampleRate * 0.02), value is a pure function of the playhead (seek/loop safe), manual value before the first point and when the transport "AUTO" switch is off; `applyTransitionLengthCorrection` = the ramp never starts before the previous point of the same fader (without it the new ramp cuts the previous one); ids `channel:<i>:volume|mute`, `master:volume`; solo has its own gate. Snapshot, copy/paste, saved per song. The ramp arithmetic was not located in the keyword-selected pseudocode (only the editor and Core Data bridging use `transitionBeats`/`applyTransitionLengthCorrection`). MIDI-only cues DONE |
| Fade out (transport "5 Second Fade Out"), end fade, excludeFromFade | `SongArrangement.endFade`, `currentFadeVolume`, `Fadeable`, `FadersDisableForFade`, string "Transport Fade button" | DONE (`FadeOut` in `MixerStage.h`, transport button, "Fim da música e fade" sheet). Evidence (pseudocode/fade.c): SongTrack fade defaults to 5.0 s (`FUN_10002a5fc`); `endFade` makes the Sequencer start the same transport fade once the playhead passes `SongChannelGroup.fadeStartTimecode` and lights the fade button → WTracks does the same at end − 5 s. `excludeFromFade` belongs to `SongGenre` (track group) → per channel here. Own: linear amplitude curve (per-track stepping not recovered), pause + FadeFinished event at silence; internal click/guides fade with the song |
| Setlist transitions: cue next song / stay in song, continue pad | `SongArrangement.storedTransition/transitionContinuePad`, `TransitionMenuViewController`, strings | DONE without pad (no pad audio): `SetlistSession` (setlist opened from the editor), engine EndReached/FadeFinished events; "Cue Next Song" loads the next song stopped at 0, "Stay In Song" stays; per-song transition editable in the setlist editor and the ending sheet. Numeric values of `storedTransition` not recovered (names are ours); `FUN_1002da058` shows at least values 3 (with live crossfade) and 4 (special-cased), not mapped |
| MIDI out: banks, buses (port, channel), events (note, velocity, duration, type), copy/paste section cues | `MIDIBank`, `MIDIBus{channel,enabled,allChannels,storedPortID}`, `MIDIEvent`, callback `requestsMIDIEventOutputAtIndex:isPrerolled:isRewound:` | DONE: banks (active bank per song), MIDI buses (channel / all channels / enabled), events note (with duration → note-off) / CC / PC, `disableLoop`, copy/paste section cues with overwrite confirmation. Evidence (`FUN_1004a1188` behind requestsMIDIEventOutputAtIndex:isPrerolled:isRewound:): note on/off with `currentNoteOnEvents`, CC, PC → engine releases held notes on pause/seek/loop jumps/end and chases the last PC/CC before the playhead when starting mid-song (own selection rule). Per-bus output port (`storedPortID`) not reproduced: one MIDI output for all buses |
| MIDI cue mute (console "MUTE MIDI") | user guide: "temporarily disables the overall sending of MIDI Cues" | DONE: `AudioEngine::setMidiCuesMuted` (cues and the chase on play stop; held notes are released and their note-offs still pass) |
| MIDI clock | `MIDIClockAU`, `MIDIDevice.selectedMIDIClockEndpointIDs` | DONE |
| MIDI in mapping + keyboard shortcuts | `ControlMapping{mappingID,mappingTypeID,intValue1..3,stringValue1}`, `MIDIDevice.selectedMIDIInEndpointIDs`, strings "MIDI Mapping 2.0", "Keyboard Mapping" | DONE: MIDI input (`MidiInput.h`, lock-free queue polled by the UI), learn mode, note/CC/PC mappings, keyboard keys on the performance screen, global persistence. Own: the action list (play/pause, stop, next/previous song and section, fade, click, guides, automation), type numbering, CC triggers at value >= 64, default keys. Tested with injected messages only (no MIDI hardware) |
| SMPTE/LTC | `TimecodeAU`, `SongArrangement{smpteStartTime,storedSMPTETimelineLocation,storedSMPTEEnabled}`, "Follow Default Arrangement" | DONE (basic) |
| Tempo / key change (time-stretch) | `CelastiqueSOLOV3`, `TimePitchProcessingManager`, strings "Requires shift to bpm/keyID" | DONE (own algorithm) |
| Ambient Pad Player (keyed pad loops, crossfade, intro/outro only) | `Pad`, `PadTrack`, `SongPadTrack`, `SongArrangement.{includePad,padIntroOutroOnly,useDefaultPad}` | no pad audio in the package: out of scope |
| Custom sounds directories (clicks, guides, pads) | strings "Custom Clicks/Guides/Pads Directory Path" | DONE for clicks and guides (settings): own file naming = bundled names (`<Family>-<voice>.wav`, `guidecue-…-<lang>-<gender>-<name>.wav`), custom guides override bundled ones; pads out of scope |
| Playback Remote (local-network control) | `WSServer`, `PlaybackRemoteView`, strings "Allow Remote Connections" | DONE as our own protocol (NOT compatible with the iOS app, whose cloud/organization pairing and wire format were not recovered): WebSocket host on the LAN (`remote_server.dart`), 4-digit PIN pairing, the control actions as commands, status every 250 ms, connected devices with disconnect; off by default. Android needs the INTERNET permission (added) |
| Waveform: sections, markers, grid, trim, veil | `Waveform*` classes, setting "Waveform Grid" | partial |

## Performance screen layout

Evidence: Transport/Mixer/Waveform storyboards in `ui/view-trees` and the MultiTracks user guide screenshots, GIFs and
videos catalogued in `ui/helpcenter/README.md`, with colours measured on the iPad captures. Status: DONE (layout v2),
screenshots in `docs/ui-performance/`.

Implemented:
- The performance screen is the app's home: a single window, with the library, setlists, song menu and settings opening over it.
- Top bar: tempo and meter that follow the tempo map; time display (tap opens the song menu); CLICK in the PAD slot;
  back to start; play/pause; 5 s fade; EDIT (tap toggles setlist edit, hold opens Setlist / MIDI cues / MIDI mapping /
  song sections); Setlists popover; ≡ menu.
- Setlist row: cards titled "Title (Key)", a transition badge (tap picks Cue Next / Stay), and a green ▷ on the current song.
  Stopped, a tap selects a song; playing, a double tap does. Edit mode adds (−) remove, (…) song menu and (+) add-song popover.
- Waveform: scrolls under a fixed playhead and stays draggable. Sections are rounded boxes tinted by section, each with a
  badge (double tap jumps to the section) and a loop icon. A tap on the loop icon arms one repeat; in edit mode it toggles
  the preset infinite loop, and (−)/(+) delete or add sections. Also shown: a bar grid (setting "Grade da waveform"),
  orange MIDI-cue triangles and the loop-pass chip.
- Mixer: S buttons, faders with ticks and a cap, drag-only. A tap on the name mutes; in edit mode it picks the output.
  A metronome strip with ▶ opens the Accent / 1/4 / 1/8 / 1/16 faders.
- Console: Tracks / Buses (/ Waveform on a phone in landscape), MUTE MIDI (native `setMidiCuesMuted`), Loop (one repeat
  of the current section), Infinite Loop and AUTO; Master fader with L/R meters.

Own:
- No artwork: card colours derive from the title.
- Section colours come from the name's first letter, because our model has no section type.
- The metronome is a mixer strip, since the click is generated.
- A double tap while playing switches songs (Playback crossfades).
- A double tap on a badge jumps at once (Playback's Live ReOrder waits for the current section to end).
- Adding a song outside a setlist replaces the open song.
- The current song cannot be removed from the setlist.
- About 45 s of waveform is visible.

Divergences still open (from the guide):
- The Fade button fades tracks out *and back in* while click, guide and pad keep playing. Ours ends in a pause.
- AutoLink, Overlap, Crossfade and Cue First Song transitions are missing. `storedTransition` is decoded in `FUN_1004bad90` (transition.c ~10337): 0 Cue Next Song, 1 AutoLink, 2 Overlap, 3 Crossfade, 4 Stay In Song, 5 Cue First Song; Continue Pad applies to 0/4/5 (mask 0x31). See `docs/PLANO-DESENVOLVIMENTO.md`.
- Live crossfade between songs and Live ReOrder are missing.
- Pad Player and arrangements are missing.
- Settings are not yet a single tabbed panel (General / Tracks / Buses / MIDI / About).
- The song menu still links to separate screens instead of editing in place.

Development plan with the remaining gaps and the second Ghidra pass list: `docs/PLANO-DESENVOLVIMENTO.md`.
