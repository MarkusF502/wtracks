// Deck-specific part of the FFI bridge (generated from the former ffi_bridge.cpp). ffi_bridge.cpp includes it once per deck with
// WT_DECK, WT(name) and ENGINE defined. Every function acts on ENGINE (decks[WT_DECK]).

WTRACKS_API bool WT(load_track)(const char* songId, const char** channelPaths, int channelCount)
{
    if (!ENGINE)
        return false;

    try {
        std::vector<juce::File> files;
        for (int i = 0; i < channelCount; ++i) {
            const char* p = channelPaths[i];
            juce::String s = p != nullptr ? juce::String(juce::CharPointer_UTF8(p)) : juce::String("<null>");
            juce::File f(s);
            files.emplace_back(std::move(f));
        }

        return ENGINE->loadTrack(juce::String(songId), files);
    } catch (...) {
        // Se explodir qualquer limite de RAM no C++, captura aqui e não derruba o Dart.
        ENGINE->setLastError(wtracks::EngineErrorCode::Unknown, "C++ Exception catastrófica ao carregar arquivos");
        return false;
    }
}

// Expõe a string de erro com segurança de memória
WTRACKS_API const char* WT(get_last_error)()
{
    static juce::String lastErrorBuffer;   // one per deck: the pointer handed to Dart must outlive the call
    if (!ENGINE) return "";
    lastErrorBuffer = ENGINE->getLastError();
    return lastErrorBuffer.toRawUTF8();
}

WTRACKS_API int WT(get_last_error_code)()
{
    return static_cast<int>(ENGINE ? ENGINE->getLastErrorCode() : wtracks::EngineErrorCode::DeviceInitFailed);
}

WTRACKS_API void WT(unload_track)()
{
    if (ENGINE) ENGINE->unloadCurrentTrack();
}

WTRACKS_API void WT(play)()  { if (ENGINE) ENGINE->play();  }
WTRACKS_API void WT(pause)() { if (ENGINE) ENGINE->pause(); }
WTRACKS_API void WT(stop)()  { if (ENGINE) ENGINE->stop();  }

WTRACKS_API void WT(seek)(double seconds)
{
    if (ENGINE) ENGINE->seekToSeconds(seconds);
}

WTRACKS_API double WT(get_position)()
{
    return ENGINE ? ENGINE->getCurrentPositionSeconds() : 0.0;
}

WTRACKS_API double WT(get_length)()
{
    return ENGINE ? ENGINE->getTotalLengthSeconds() : 0.0;
}

WTRACKS_API bool WT(is_playing)()
{
    return ENGINE && ENGINE->isPlaying();
}

WTRACKS_API void WT(set_channel_volume)(int channelIndex, float volume)
{
    if (ENGINE) ENGINE->setChannelVolume(channelIndex, volume);
}

WTRACKS_API void WT(set_channel_muted)(int channelIndex, bool muted)
{
    if (ENGINE) ENGINE->setChannelMuted(channelIndex, muted);
}

WTRACKS_API bool WT(set_channel_route)(int channelIndex, int outputBase, bool mono)
{
    return ENGINE ? ENGINE->setChannelRoute(channelIndex, outputBase, mono) : false;
}

WTRACKS_API void WT(set_master_volume)(float volume)
{
    if (ENGINE) ENGINE->setMasterVolume(volume);
}

WTRACKS_API int WT(get_channel_count)()
{
    return ENGINE ? ENGINE->getChannelCount() : 0;
}

WTRACKS_API bool WT(set_time_scale)(double scale)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    return ENGINE ? ENGINE->setTimeScale(scale) : false;
}

WTRACKS_API double WT(get_time_scale)() { return ENGINE ? ENGINE->getTimeScale() : 1.0; }

WTRACKS_API bool WT(midi_open_output)(const char* identifier)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    return ENGINE && identifier ? ENGINE->openMidiOutput(juce::String::fromUTF8(identifier)) : false;
}

WTRACKS_API void WT(midi_close_output)()
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (ENGINE) ENGINE->closeMidiOutput();
}

WTRACKS_API bool WT(midi_output_open)() { return ENGINE && ENGINE->isMidiOutputOpen(); }
WTRACKS_API void WT(set_midi_clock_enabled)(bool enabled) { if (ENGINE) ENGINE->setMidiClockEnabled(enabled); }
WTRACKS_API void WT(set_midi_cues_muted)(bool muted) { if (ENGINE) ENGINE->setMidiCuesMuted(muted); }

WTRACKS_API bool WT(send_midi)(const uint8_t* bytes, int size)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    return ENGINE ? ENGINE->sendMidiMessage(bytes, size) : false;
}

WTRACKS_API bool WT(configure_cues)(const double* times, const uint8_t* midiBytes, const uint8_t* midiSizes, int count)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!ENGINE) return false;
    try { return ENGINE->configureCues(times, midiBytes, midiSizes, count); }
    catch (...) { ENGINE->setLastError(wtracks::EngineErrorCode::Unknown, "Cue preparation failed"); return false; }
}

WTRACKS_API int WT(poll_cues)(uint32_t* out, int maxCount) { return ENGINE ? ENGINE->pollCues(out, maxCount) : 0; }
WTRACKS_API uint64_t WT(get_midi_dropped)() { return ENGINE ? ENGINE->getMidiDroppedCount() : 0; }

WTRACKS_API bool WT(configure_timecode)(int rateIndex, int64_t startFrame, double onsetSeconds, int outputChannel, float gain)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    return ENGINE ? ENGINE->configureTimecode(rateIndex, startFrame, onsetSeconds, outputChannel, gain) : false;
}

WTRACKS_API void WT(set_timecode_enabled)(bool enabled) { if (ENGINE) ENGINE->setTimecodeEnabled(enabled); }

WTRACKS_API bool WT(set_click_tempo_changes)(const double* starts, const double* bpms, const int* numerators, const int* denominators, int count)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    return ENGINE ? ENGINE->setClickTempoChanges(starts, bpms, numerators, denominators, count) : false;
}

WTRACKS_API bool WT(set_click_times)(const double* times, const uint8_t* voices, int count)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    return ENGINE ? ENGINE->setClickTimes(times, voices, count) : false;
}

WTRACKS_API bool WT(configure_preset_loops)(const double* starts, const double* ends, const int* repeats, int count)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!ENGINE) return false;
    try { return ENGINE->configurePresetLoops(starts, ends, repeats, count); }
    catch (...) { ENGINE->setLastError(wtracks::EngineErrorCode::Unknown, "Preset loop preparation failed"); return false; }
}

WTRACKS_API bool WT(configure_guides)(const double* times, const char** paths, const float* gains, int count)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!ENGINE) return false;
    try { return ENGINE->configureGuides(times,paths,gains,count); }
    catch (...) { ENGINE->setLastError(wtracks::EngineErrorCode::Unknown,"Guide preparation failed"); return false; }
}
WTRACKS_API void WT(set_guides_enabled)(bool enabled) { if (ENGINE) ENGINE->setGuidesEnabled(enabled); }

WTRACKS_API bool WT(configure_guides_ex)(const double* times, const char** paths, const char** replacementPaths,
                                 const double* targets, const float* gains, int count)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!ENGINE) return false;
    try { return ENGINE->configureGuides(times,paths,replacementPaths,targets,gains,count); }
    catch (...) { ENGINE->setLastError(wtracks::EngineErrorCode::Unknown,"Guide preparation failed"); return false; }
}

WTRACKS_API bool WT(configure_preroll)(bool enabled, const double* starts, int startCount, const char** countPaths, int countCount)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!ENGINE) return false;
    try { return ENGINE->configurePreroll(enabled,starts,startCount,countPaths,countCount); }
    catch (...) { ENGINE->setLastError(wtracks::EngineErrorCode::Unknown,"Pre-roll preparation failed"); return false; }
}

WTRACKS_API bool WT(is_prerolling)() { return ENGINE ? ENGINE->isPrerolling() : false; }

WTRACKS_API bool WT(configure_mixer_automation)(const double* starts, const double* ends, const int* params, const float* values, int count)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!ENGINE) return false;
    try { return ENGINE->configureMixerAutomation(starts,ends,params,values,count); }
    catch (...) { ENGINE->setLastError(wtracks::EngineErrorCode::Unknown,"Mixer automation failed"); return false; }
}

WTRACKS_API void WT(set_automation_enabled)(bool enabled) { if (ENGINE) ENGINE->setAutomationEnabled(enabled); }

WTRACKS_API int WT(get_mix_state)(float* volumes, uint8_t* mutes, int capacity, float* master)
{
    return ENGINE ? ENGINE->getMixState(volumes,mutes,capacity,master) : 0;
}

WTRACKS_API void WT(set_channel_solo_muted)(int channelIndex, bool muted) { if (ENGINE) ENGINE->setChannelSoloMuted(channelIndex,muted); }
WTRACKS_API bool WT(set_fade)(bool down, double seconds) { return ENGINE ? ENGINE->setFade(down,seconds) : false; }
WTRACKS_API bool WT(get_fade_down)() { return ENGINE ? ENGINE->isFadeDown() : false; }
WTRACKS_API bool WT(set_play_range)(double startSeconds, double endSeconds) { return ENGINE ? ENGINE->setPlayRange(startSeconds,endSeconds) : false; }
WTRACKS_API void WT(get_play_range)(double* out2) { if (ENGINE) ENGINE->getPlayRange(out2); else out2[0]=out2[1]=0; }
WTRACKS_API void WT(reset_transport_state)() { if (ENGINE) ENGINE->resetTransportState(); }
WTRACKS_API bool WT(set_end_fade)(double seconds) { return ENGINE ? ENGINE->setEndFade(seconds) : false; }
WTRACKS_API void WT(set_channel_excluded_from_fade)(int channelIndex, bool excluded) { if (ENGINE) ENGINE->setChannelExcludedFromFade(channelIndex,excluded); }
WTRACKS_API double WT(get_fade_gain)() { return ENGINE ? ENGINE->getFadeGain() : 1.0; }
WTRACKS_API uint32_t WT(poll_transport_events)() { return ENGINE ? ENGINE->pollTransportEvents() : 0; }
WTRACKS_API int WT(take_meters)(float* channelPeaks, int capacity, float* outputPeaks, int outputCapacity)
{
    return ENGINE ? ENGINE->takeMeters(channelPeaks,capacity,outputPeaks,outputCapacity) : 0;
}
WTRACKS_API bool WT(configure_cues_ex)(const double* times, const uint8_t* midiBytes, const uint8_t* midiSizes, const uint8_t* flags, int count)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!ENGINE) return false;
    try { return ENGINE->configureCues(times,midiBytes,midiSizes,flags,count); }
    catch (...) { ENGINE->setLastError(wtracks::EngineErrorCode::Unknown,"Cue preparation failed"); return false; }
}

WTRACKS_API bool WT(midi_open_input)(const char* identifier)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    return ENGINE && identifier ? ENGINE->openMidiInput(juce::String::fromUTF8(identifier)) : false;
}

WTRACKS_API void WT(midi_close_input)() { const std::lock_guard<std::mutex> lock(engineLifetimeMutex); if (ENGINE) ENGINE->closeMidiInput(); }
WTRACKS_API bool WT(midi_input_open)() { return ENGINE ? ENGINE->isMidiInputOpen() : false; }
WTRACKS_API int WT(poll_midi_input)(uint32_t* out, int maxCount) { return ENGINE ? ENGINE->pollMidiInput(out,maxCount) : 0; }
WTRACKS_API bool WT(inject_midi_input)(const uint8_t* bytes, int size) { return ENGINE ? ENGINE->injectMidiInput(bytes,size) : false; }

WTRACKS_API void WT(get_loop_pass)(int32_t* pass, int32_t* repeats) { if (ENGINE) ENGINE->getLoopPass(pass,repeats); else { if (pass) *pass=0; if (repeats) *repeats=0; } }
WTRACKS_API bool WT(configure_skips)(const double* starts, const double* ends, int count)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!ENGINE) return false;
    try { return ENGINE->configureSkips(starts,ends,count); }
    catch (...) { ENGINE->setLastError(wtracks::EngineErrorCode::Unknown,"Trim preparation failed"); return false; }
}

WTRACKS_API bool WT(configure_buses)(int count) { return ENGINE ? ENGINE->configureBuses(count) : false; }
WTRACKS_API bool WT(set_bus)(int index, float volume, bool muted, int outputBase, bool mono) { return ENGINE ? ENGINE->setBus(index,volume,muted,outputBase,mono) : false; }
WTRACKS_API void WT(set_bus_solo_muted)(int index, bool muted) { if (ENGINE) ENGINE->setBusSoloMuted(index,muted); }
WTRACKS_API bool WT(set_channel_bus)(int channelIndex, int bus) { return ENGINE ? ENGINE->setChannelBus(channelIndex,bus) : false; }
WTRACKS_API void WT(set_stereo_split)(bool enabled) { if (ENGINE) ENGINE->setStereoSplit(enabled); }
WTRACKS_API int WT(get_bus_state)(float* volumes, uint8_t* mutes, int capacity) { return ENGINE ? ENGINE->getBusState(volumes,mutes,capacity) : 0; }
WTRACKS_API int WT(take_bus_meters)(float* peaks, int capacity) { return ENGINE ? ENGINE->takeBusMeters(peaks,capacity) : 0; }

WTRACKS_API bool WT(set_loop)(double start, double end, bool enabled)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!ENGINE) return false;
    try { return ENGINE->setLoop(start,end,enabled); }
    catch (...) { ENGINE->setLastError(wtracks::EngineErrorCode::Unknown,"Loop preparation failed"); return false; }
}
WTRACKS_API bool WT(set_loop_repeats)(double start, double end, bool enabled, int repeats)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!ENGINE) return false;
    try { return ENGINE->setLoop(start, end, enabled, repeats); }
    catch (...) { ENGINE->setLastError(wtracks::EngineErrorCode::Unknown, "Loop preparation failed"); return false; }
}

WTRACKS_API bool WT(enqueue_loop_repeats)(double start, double end, int repeats)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!ENGINE) return false;
    try { return ENGINE->enqueueLoop(start, end, repeats); }
    catch (...) { ENGINE->setLastError(wtracks::EngineErrorCode::Unknown, "Loop preparation failed"); return false; }
}

WTRACKS_API bool WT(enqueue_loop)(double start, double end)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!ENGINE) return false;
    try { return ENGINE->enqueueLoop(start,end); }
    catch (...) { ENGINE->setLastError(wtracks::EngineErrorCode::Unknown,"Queued loop preparation failed"); return false; }
}
WTRACKS_API void WT(clear_queued_loop)() { if (ENGINE) ENGINE->clearQueuedLoop(); }
WTRACKS_API void WT(get_loop_state)(double* out6) { if (!out6) return; if (ENGINE) ENGINE->getLoopState(out6); else for (int i=0;i<6;++i) out6[i]=0; }
WTRACKS_API bool WT(get_loop_enabled)() { return ENGINE && ENGINE->getLoopEnabled(); }
WTRACKS_API bool WT(get_queued_loop_enabled)() { return ENGINE && ENGINE->getQueuedLoopEnabled(); }
WTRACKS_API double WT(get_loop_start)() { return ENGINE ? ENGINE->getLoopStart() : 0; }
WTRACKS_API double WT(get_loop_end)() { return ENGINE ? ENGINE->getLoopEnd() : 0; }
WTRACKS_API double WT(get_queued_loop_start)() { return ENGINE ? ENGINE->getQueuedLoopStart() : 0; }
WTRACKS_API double WT(get_queued_loop_end)() { return ENGINE ? ENGINE->getQueuedLoopEnd() : 0; }
WTRACKS_API uint64_t WT(get_underrun_count)() { return ENGINE ? ENGINE->getUnderrunCount() : 0; }
// out8 = callbacks, overruns, maxMs, maxLoad, p50Load, p95Load, p99Load, deadlineMs (load = duração do callback / prazo).
WTRACKS_API void WT(get_render_stats)(double* out8)
{
    if (!out8) return;
    const auto s=ENGINE ? ENGINE->getRenderStats() : RenderStats::Snapshot{};
    const double v[8]={static_cast<double>(s.callbacks),static_cast<double>(s.overruns),s.maxMs,s.maxLoad,s.p50Load,s.p95Load,s.p99Load,s.lastDeadlineMs};
    for (int i=0;i<8;++i) out8[i]=v[i];
}
WTRACKS_API void WT(reset_render_stats)() { if (ENGINE) ENGINE->resetRenderStats(); }

WTRACKS_API bool WT(configure_click)(double bpm, int numerator, int denominator, int unit, double offset, double accent, double quarter, double eighth, double sixteenth)
{
    return ENGINE && ENGINE->configureClick(bpm,numerator,denominator,unit,offset,accent,quarter,eighth,sixteenth);
}
WTRACKS_API bool WT(load_click_sound)(int voice, const char* path)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!ENGINE) return false;
    try { return ENGINE->loadClickSound(voice, path ? juce::String::fromUTF8(path) : juce::String()); }
    catch (...) { ENGINE->setLastError(wtracks::EngineErrorCode::Unknown,"Click sound loading failed"); return false; }
}
WTRACKS_API bool WT(load_click_bank)(const char** paths, int voiceCount)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!ENGINE) return false;
    if (!paths || voiceCount != 4) { ENGINE->setLastError(wtracks::EngineErrorCode::FormatMismatch,"Click bank requires four voices"); return false; }
    try {
        std::array<juce::String,4> names;
        for (int voice=0;voice<4;++voice) names[voice]=paths[voice] ? juce::String::fromUTF8(paths[voice]) : juce::String();
        return ENGINE->loadClickBank(names);
    } catch (...) { ENGINE->setLastError(wtracks::EngineErrorCode::Unknown,"Click bank loading failed"); return false; }
}
WTRACKS_API void WT(set_click_gain)(float gain) { if (ENGINE) ENGINE->setClickGain(gain); }

WTRACKS_API void WT(set_click_enabled)(bool enabled)
{
    if (ENGINE) ENGINE->setClickEnabled(enabled);
}

WTRACKS_API void WT(set_click_bpm)(double bpm)
{
    if (ENGINE) ENGINE->setClickBpm(bpm);
}

WTRACKS_API void WT(set_click_time_signature)(int numerator, int denominator)
{
    if (ENGINE) ENGINE->setClickTimeSignature(numerator, denominator);
}

WTRACKS_API void WT(set_click_offset)(double offsetSeconds)
{
    if (ENGINE) ENGINE->setClickOffsetSeconds(offsetSeconds);
}

