#pragma once
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_core/juce_core.h>
#include "TimePitch.h"

namespace wtracks {
struct TimePitchResult {
    bool ok = false;
    bool cancelled = false;
    juce::String error;
};

// Renders `input` to a 32-bit float WAV at the same rate and channel count (stereo-or-less stems, 8 channels at most).
// The output appears atomically (temporary file + rename). Safe to call from several threads; it does not touch the engine.
// `token` identifies the call for cancelTimePitch(), which may arrive before or while the call runs.
TimePitchResult processTimePitchFile(const juce::File& input, const juce::File& output, const timepitch::Options& options, int64_t token);
void cancelTimePitch(int64_t token);
}
