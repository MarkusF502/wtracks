# Static subsystem contracts

Static Ghidra pseudocode and immutable Mach-O rate table; no iOS execution. These contracts are preliminary; unknowns must be resolved before claiming equivalence.

## MIDIClockAUFramework

Artifact SHA256: `8a282176f92a429bfc4bde96fc34d2f159f2b2d84ae231ce0e7487d63abcec4c`

Evidence: `MIDIClockAUFramework:00005548`, `MIDIClockAUFramework:00004810`, `MIDIClockAUFramework:00004ad8`, `MIDIClockAUFramework:000056a4`. Full bodies, exact batch paths and hashes are in subsystem-contracts.json.

**Observed bodies**

- Per-sample clock comparison; nextPulse = int(float(previousPulse) + sampleRate*60/(tempo*24)). Observed 24 pulses per tempo beat and iterative truncation.
- Initial active render sends 0xFA at absolute sample <=4, otherwise 0xFB; parameter1=0 sends 0xFC when parameter0 flag enabled.
- Modern MIDIEventList uses mach_absolute_time() immediately; old MIDIPacketList F8/FC timestamps are now+10ms converted host ticks. Modern path ignores F2.
- Audio output cleared; timeline advances only when both active flags are true.

**Inferences**

- Parameter2 represents BPM. Parameter0 and1 are enable/play gates, exact UI mapping unconfirmed.

**Unknowns**

- Destination endpoint ownership and modern/legacy parity need runtime validation; packet prebuilding paths need additional study.

**Proposed tests**

- 24 pulses per beat; fractional BPM accumulated truncation comparison against improved absolute schedule.
- Start at samples0/4/5; stop/unmute; zero tempo; seek to nonzero position.
- Fake MIDI sink verifies one-byte realtime messages and both timestamp branches without hardware.

## MixerAUFramework

Artifact SHA256: `d0b6117feeabbd3681224b2966350b1f8a86a1ca26d1106e643d132583242677`

Evidence: `MixerAUFramework:0000563c`. Full bodies, exact batch paths and hashes are in subsystem-contracts.json.

**Observed bodies**

- Each sample calculates a common ParameterRamper gain and sums gain*inputBus[channel][sample] across buses into output channel.
- Input bus lacking current channel terminates summation, rather than demonstrably duplicating mono to stereo.

**Inferences**

- No pan or normalization appears in this kernel; pan likely upstream or another subsystem.

**Unknowns**

- ParameterRamper time constants and upstream track pan mapping not yet resolved.

**Proposed tests**

- Two buses known constants; missing channel in middle bus; gain ramp sample-by-sample; ensure no implicit clipping.

## BusChannelAUFramework

Artifact SHA256: `5692b4e9ff963e1c091bb0dcf5f1d3a867d3a5b22a5ff0eca9ff5d5b2a22006a`

Evidence: `BusChannelAUFramework:00004870`, `BusChannelAUFramework:000058b0`. Full bodies, exact batch paths and hashes are in subsystem-contracts.json.

**Observed bodies**

- Parameter0 updates ramper target; parameter1 boolean silencing gate; parameter2 integer output channel base; parameter3 mono/stereo mode flag.
- Requires two input channels; clears all destination channels before routing.
- Mono branch writes gain*(left+right)*0.5 into selected output. Stereo branch writes gain*input[c] to output[base+c]. Invalid routes and mute produce silence.

**Inferences**

- Boolean parameter1 is mute based on observed silence, parameter3 selects stereo.

**Unknowns**

- This body does not implement pan law; route validity around final output must be tested.

**Proposed tests**

- Mono sum cancellation; independent stereo impulses; mute; invalid base; output isolation; gain changes.

## GuideAUFramework

Artifact SHA256: `2522677d34ef08ac038f4dbecd8aaff5989079ac173a4a002d4c7b20b37dedd9`

Evidence: `GuideAUFramework:00006140`, `GuideAUFramework:0000667c`, `GuideAUFramework:000051e8`, `GuideAUFramework:00005254`. Full bodies, exact batch paths and hashes are in subsystem-contracts.json.

**Observed bodies**

- Up to four PCM playback slots are mixed with per-channel gains; mute suppresses audio while read indices continue.
- Cue descriptors use 0x28-byte stride. Process evaluates cue time*sampleRate against playhead+frame, selects normal or replacement resource then dispatches async file update/play.
- After end/next-loop remapping, calls resetGuideCuesNextIndex. Reset searches using cue sequence time*sampleRate plus int(sampleRate*0.05).
- Seek wrappers dispatch asynchronous prepare with sample index or truncated time*sampleRate.

**Inferences**

- 50ms tolerance in index selection prevents dropping cues near seek boundary; exact intent requires caller tracing.

**Unknowns**

- Cue-type0/1, sectionType7, replacement selection, queued completion ordering and cueEnabled mapping require more investigation before shipping.
- Do not claim sample-accurate cue audio start: render schedules asynchronous work.

**Proposed tests**

- Seek ±50ms around cue; loop overshoot; muted cues still advance; simultaneous four voices; resource missing; stale async prepare cancellation.

## MIDIOutAUFramework

Artifact SHA256: `a76d7007c4f1a53d5c687a094311ec1274e6e3ce9f10e8b4a28c670f9ff3101f`

Evidence: `MIDIOutAUFramework:00005a2c`, `MIDIOutAUFramework:00004fe0`, `MIDIOutAUFramework:00005044`. Full bodies, exact batch paths and hashes are in subsystem-contracts.json.

**Observed bodies**

- Events are doubles converted to samples using float sampleRate; equality comparison drains simultaneous timestamps in a while loop.
- Callback receives event index and two booleans; module itself does not construct note/program-change byte messages.
- Seek selects first event with timeSample>=playhead; future loop state reset to -1; process remaps at end and next-loop transition.
- Conditional pretransition adjustment is literal 0x6e4 (1764 samples), not derived from sampleRate in this body.

**Inferences**

- 1764 equals 40ms at44.1k but constant should remain observation until app intent is traced.

**Unknowns**

- Meaning of callback boolean flags and MIDI message payload generation lies in main application.

**Proposed tests**

- Equal-time events; seek exactly before/on/after event; no duplicate callbacks after rewind; literal1764 at44.1/48k characterization.

## AutomationAUFramework

Artifact SHA256: `19a5173c77eb697226dcb11336f5266d9a51a8b1e2c274ca71d9a41be15caa98`

Evidence: `AutomationAUFramework:00005920`, `AutomationAUFramework:00006090`, `AutomationAUFramework:00004d88`. Full bodies, exact batch paths and hashes are in subsystem-contracts.json.

**Observed bodies**

- Cue records contain string UUID and double time at offset0x18, stride0x20.
- Active process emits callback when int(cueTime*sampleRate)<=playhead+frame and cue sample != end boundary; advances cue index once.
- Seek selects first cue at or beyond sample and clears next-loop sentinels. Time wrapper narrows input to float before sample conversion.
- Loop transition preserves overshoot then recomputes next cue.

**Inferences**

- Unlike MIDIOut equality draining, automation processes one eligible cue per frame.

**Unknowns**

- Caller policy for ordering equal UUID/time and exclusions at exact end needs validation.

**Proposed tests**

- Several cues at same sample; exact end exclusion; seek and loop overshoot; fractional time conversion; UUID roundtrip.

## TimecodeAUFramework

Artifact SHA256: `ae88b748f0e40b7333c0ad34f314f8f60d55fc084a39e13a548cfa747303d7da`

Evidence: `TimecodeAUFramework:00004830`, `TimecodeAUFramework:00004ab0`, `TimecodeAUFramework:00005650`, `TimecodeAUFramework:000057e8`, `TimecodeAUFramework:00005a70`, `TimecodeAUFramework:00005a94`. Full bodies, exact batch paths and hashes are in subsystem-contracts.json.

**Observed bodies**

- Rate table at VM0x64e0 read from Mach-O segment: indices0..10 = 24,25,30,30,30000/1001,30000/1001,60,60000/1001,60,60000/1001,50.
- BCD frame units bits0..3/tens8..9; seconds16..19/24..26; minutes32..35/40..42; hours48..51/56..57. Drop flag bit10 controlled by enum mask0x324 (indices2,5,8,9). Sync word0xbffc at next16bits.
- Wavetable emits80 bits/frame, bipolar ±1, transition every bit boundary and extra midpoint transition for1. Fractional samples/bit are accumulated.
- Frame counter carry to second/minute/hour; conditional minute skip sets frame2. Rate fractional-carry enum mask0x2b0 covers4,5,7,9.
- Seek resets bit index/polarity/fractional carry; effective counter time maps onset+offset fields before encoding.

**Inferences**

- Encoding is LTC biphase mark. Decompiled modulo10 minute predicate appears drop-frame rule; verify assembly before committing exact inverse predicate.

**Unknowns**

- Parameter names, frame-rate enum display labels, initial bit polarity alignment and drop at60fps (body sets2) need characterization.
- Wavetable uses std::vector allocation; do not copy render-time allocation into WTracks.

**Proposed tests**

- Decode generated frames;80bit sync;24/25/30/29.97/50/59.94 durations; minute1/10 boundaries; seek onset/offset; phase continuity; sampleRate44.1/48k.

## LoopingFilePlaybackAUFramework

Artifact SHA256: `70854b549062f9ce7e30f5e51ea2cd25144cc2410eb1435adf08532b3e08cb0f`

Evidence: `LoopingFilePlaybackAUFramework:0000650c`, `LoopingFilePlaybackAUFramework:0000671c`, `LoopingFilePlaybackAUFramework:00007048`. Full bodies, exact batch paths and hashes are in subsystem-contracts.json.

**Observed bodies**

- Render consumes interleaved float PCM from circular buffer, applies channel gains and mute, outputs silence past available frames.
- Consumed byte count advances modulo ring capacity and atomically decrements fill count; negative count asserts.
- When fill below threshold and work flag clear, render dispatches asynchronous fillCircularBuffer(false). Preparation also queues work.

**Inferences**

- This module is buffered looping file source; song-section loop policy likely primarily in main/master subsystem.

**Unknowns**

- fillCircularBuffer file wrap, seek validity, I/O errors and stale async jobs require further investigation.

**Proposed tests**

- Underflow zero fill; wrap boundary; mute consumption; refill threshold; prepare failure callback; delayed file read and cancellation.
