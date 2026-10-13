# TimePitchProcessingManager — static contract (cycle 6)

Binary: `Playback` main executable, SHA256 `2a11a6f98134ba035c9df55d0ab5cabd376597ce83980ff40704f4f42b1ad423`.
Sources: `TimePitchProcessingManager-process.c`, `TimePitchProcessingManager-operation.c`, batch-000013.json
(profile `decompiled/Playback/2a11a6f98134-2a4a38e34a84`), function `10000df64`.

## Observed

- `processAudioFileWithInputURL:outputURL:elastiqueTimeFactor:elastiquePitchFactor:useComplexAlgorithm:error:`
  (0x10000da98) wraps an `AudioObfuscator performOperationOnObfuscatedAudioFile:audioOperationBlock:` call; the block
  (0x10000df18) forwards to `FUN_10000df64(44100.0, timeFactor, pitchFactor, state+8, 2, in, out, complexFlag)`.
  The `0x40e5888000000000` literal is the double 44100.0, and `2` is the channel count.
- `FUN_10000df64` stores the sample rate (as float) and channel count, initialises two `TPCircularBuffer`s, converts the
  factors to floats, and creates a processor through `FUN_1008aa34c(sampleRate, 0.5f, &handle, blockSize, channels, mode)`
  with `mode = 0` when `useComplexAlgorithm` is true, `2` when false. Two virtual calls then set the time factor and the pitch factor.
- The loop reads the input file (ExtAudioFile) into one ring, processes, and writes the output file until the input is exhausted. Errors
  are reported with `Context`, `Errorcode`, `InputURL`, `OutputURL`, `TimeFactor`, `PitchFactor`, `UseComplexAlgorithm`.
- The result is an offline-rendered file, not a realtime stretch: Playback plays a processed copy.

## Inferences

- The parameter names (`elastique…`) indicate the zplane Élastique engine (proprietary, licensed). The vtable offsets are consistent with
  separate time and pitch setters. The meaning of `0.5f` and of the `mode` values is not recovered.
- Time factor is read as output length / input length (1.0 = unchanged); pitch factor as frequency ratio. The binary does not state this; it is
  our reading of the Élastique API naming.

## Our reconstruction (not equivalence)

- Élastique cannot be reused. `native/include/TimePitch.h` is an own offline phase vocoder (identity phase locking) plus a windowed-sinc resampler.
  `complex=true` selects the longer analysis window (higher frequency resolution, more transient smearing).
- Playback is offline: stems are rendered once per (timeFactor, pitchFactor) and cached; the engine plays the processed files and converts
  between song time and processed time (`AudioEngine::setTimeScale`).
- Quality has not been compared with Playback on iOS. Record the iOS version/build when that comparison is possible.
