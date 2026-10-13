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
| Song map: sections with trim, loop count, infinite loop, preset infinite loop, count-in, guide cue | `SongSection{startTimeOriginal,endTimeOriginal,storedStart/EndTimeTrimOffset,loopCount,loopInfinite,presetInfiniteLoop,storedPlayCountIn,storedPlayGuideCue,storedAutomationCues}`, strings "Play Section Count In", "Play Section Guide Cue", "Enable Preset Infinite Loop" | loopCount + preset infinite loop DONE (native counted/preset loops); count-in on jump and trim TODO; guide/count flags stored, dynamic guides TODO |
| Dynamic guide cues: section name + count | `GuideCue(cueType, sectionTypeID, cueSequenceTimecode, songMapElementStartTimecode, cueEnabled, cueFilePath, replacementCountCueFilePath)`, settings "Count Into Each Section", "Song Section Pre-roll", "Guide Cue Language" | cycle 9 |
| Guide files by language/gender/type | filenames `guidecue-{count,section}-<lang>-<gender>-<name>` | resources DONE, selection cycle 9 |
| Mixer: tracks, buses, per-song bus level/mute/solo, master (per song), VU meters, fader default 80% | `SongTrack`, `SongBus{id,muted,volume}`, `GlobalBus`, `SongArrangement.masterVolumeLevel`, `MixerVUMeterView`, strings "Fader Default Level 80%", "Song Specific Buses", "Song Specific Master Fader" | channel gain/mute/solo/master DONE; buses/VU TODO |
| Output routing: track -> bus -> output channel; "Send Click & Guide to left and tracks to right" | `OutputRouting`, `OutputChannel`, `AudioDevice`, `MetadataTrack.busID`, `SongTrack.isClickOrGuide`, strings | per-channel L/R DONE; buses TODO |
| Automation: points on the timeline that move faders / master / pad over a transition length in beats; mute is instant | `AutomationCue{name,details,transitionBeats,sampleTimecode,sequenceTimecode,applyTransitionLengthCorrection,storedItems}`, `AutomationItem{automationID,storedValue}`, strings "Transition length is the length of time (in beats) the faders will start leading to the Automation point. Mute or unmute changes are instant.", "Set the Automation Snapshot", copy/paste | TODO (MIDI-only cues DONE) |
| Fade out (transport "5 Second Fade Out"), end fade, excludeFromFade | `SongArrangement.endFade`, `currentFadeVolume`, `Fadeable`, `FadersDisableForFade` | TODO |
| Setlist transitions: cue next song / stay in song, continue pad | `SongArrangement.storedTransition/transitionContinuePad`, `TransitionMenuViewController`, strings | TODO |
| MIDI out: banks, buses (port, channel), events (note, velocity, duration, type), copy/paste section cues | `MIDIBank`, `MIDIBus{channel,enabled,allChannels,storedPortID}`, `MIDIEvent`, callback `requestsMIDIEventOutputAtIndex:isPrerolled:isRewound:` | cues + clock DONE; banks/buses TODO |
| MIDI clock | `MIDIClockAU`, `MIDIDevice.selectedMIDIClockEndpointIDs` | DONE |
| MIDI in mapping + keyboard shortcuts | `ControlMapping{mappingID,mappingTypeID,intValue1..3,stringValue1}`, `MIDIDevice.selectedMIDIInEndpointIDs`, strings "MIDI Mapping 2.0", "Keyboard Mapping" | TODO |
| SMPTE/LTC | `TimecodeAU`, `SongArrangement{smpteStartTime,storedSMPTETimelineLocation,storedSMPTEEnabled}`, "Follow Default Arrangement" | DONE (basic) |
| Tempo / key change (time-stretch) | `CelastiqueSOLOV3`, `TimePitchProcessingManager`, strings "Requires shift to bpm/keyID" | DONE (own algorithm) |
| Ambient Pad Player (keyed pad loops, crossfade, intro/outro only) | `Pad`, `PadTrack`, `SongPadTrack`, `SongArrangement.{includePad,padIntroOutroOnly,useDefaultPad}` | no pad audio in the package: out of scope |
| Custom sounds directories (clicks, guides, pads) | strings "Custom Clicks/Guides/Pads Directory Path" | TODO |
| Playback Remote (local-network control) | `WSServer`, `PlaybackRemoteView`, strings "Allow Remote Connections" | TODO (low) |
| Waveform: sections, markers, grid, trim, veil | `Waveform*` classes, setting "Waveform Grid" | partial |
