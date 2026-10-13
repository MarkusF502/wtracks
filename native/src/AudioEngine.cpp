#include "../include/AudioEngine.h"
#include <map>

namespace wtracks
{

AudioEngine::AudioEngine()
{
    formatManager.registerBasicFormats();
    readAheadThread.startThread();
}

AudioEngine::~AudioEngine()
{
    shutdown();
    readAheadThread.stopThread(10000);
}

bool AudioEngine::initialise(int sampleRate, int bufferSize)
{
    currentSampleRate = sampleRate;

    auto result = deviceManager.initialiseWithDefaultDevices(0, 2);
    if (result.isNotEmpty()) {
        setLastError(EngineErrorCode::DeviceInitFailed, result);
        return false;
    }

    juce::AudioDeviceManager::AudioDeviceSetup setup;
    deviceManager.getAudioDeviceSetup(setup);
    setup.sampleRate = sampleRate;
    setup.bufferSize = bufferSize;
    const auto setupError = deviceManager.setAudioDeviceSetup(setup, true);
    if (setupError.isNotEmpty()) {
        setLastError(EngineErrorCode::DeviceInitFailed, setupError);
        return false;
    }
    setLastError(EngineErrorCode::None, "");

    audioSourcePlayer.setSource(this);
    deviceManager.addAudioCallback(&audioSourcePlayer);

    return true;
}

void AudioEngine::shutdown()
{
    const std::lock_guard<std::recursive_mutex> control(controlMutex);
    stop();
    midiRouter.close();

    audioSourcePlayer.setSource(nullptr);
    deviceManager.removeAudioCallback(&audioSourcePlayer);
    deviceManager.closeAudioDevice();

    const juce::SpinLock::ScopedLockType lock(channelsLock);
    channels.clear();
    guideTimeline=GuideTimeline{}; cueTimeline=CueTimeline{}; timeScale=1.0; userTempoChanges.clear(); applyClickScale();
}

bool AudioEngine::loadTrack(const juce::String& songId, const std::vector<juce::File>& channelFiles)
{
    const std::lock_guard<std::recursive_mutex> control(controlMutex);
    DBG("C++ [loadTrack] Iniciando carregamento para: " + songId);
    setLastError(EngineErrorCode::None, ""); // Zera erros antigos

    double referenceSampleRate = 0.0;
    juce::int64 referenceLengthSamples = 0;

    // 1. Cross-loading Seguro: Preparamos as novas faixas em um vetor temporário!
    // NENHUM lock da thread de áudio é feito aqui.
    std::vector<Channel> newChannels;

    for (size_t i = 0; i < channelFiles.size(); ++i)
    {
        const auto& file = channelFiles[i];
        DBG("C++ [loadTrack] Lendo arquivo " + juce::String(i) + ": " + file.getFileName());

        auto* reader = formatManager.createReaderFor(file);
        if (reader == nullptr)
        {
            juce::String err = "Formato nao suportado ou arquivo corrompido: " + file.getFileName();
            DBG("C++ [loadTrack] ERRO CRITICO: " + err);
            setLastError(EngineErrorCode::FileUnreadable, err);
            return false; 
        }

        if (!std::isfinite(reader->sampleRate) || reader->sampleRate < 8000 || reader->sampleRate > 192000 || reader->lengthInSamples <= 0) {
            delete reader; setLastError(EngineErrorCode::FormatMismatch,"Invalid track sample rate or length"); return false;
        }

        if (referenceSampleRate == 0.0)
        {
            referenceSampleRate = reader->sampleRate;
            referenceLengthSamples = reader->lengthInSamples;
        }
        else
        {
            const auto toleranceSamples = static_cast<juce::int64>(referenceSampleRate * 0.05);
            const auto lengthDiff = std::abs(reader->lengthInSamples - referenceLengthSamples);

            if (reader->sampleRate != referenceSampleRate || lengthDiff > toleranceSamples)
            {
                delete reader; 
                juce::String err = "Incompatibilidade de formato ou duracao: " + file.getFileName();
                DBG("C++ [loadTrack] ERRO CRITICO: " + err);
                setLastError(EngineErrorCode::FormatMismatch, err);
                return false;
            }
        }

        Channel channel;
        channel.name = file.getFileNameWithoutExtension();
        channel.file=file;
        channel.fileSampleRate = reader->sampleRate;
        channel.readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
        channel.readAheadCapacity=static_cast<int>(channel.fileSampleRate*4)+64;
        channel.bufferedSource=std::make_unique<juce::BufferingAudioSource>(channel.readerSource.get(),readAheadThread,false,channel.readAheadCapacity,2,false);
        channel.resampler = std::make_unique<juce::ResamplingAudioSource>(channel.bufferedSource.get(), false, 2);
        channel.resampler->setResamplingRatio(channel.fileSampleRate / preparedSampleRate);

        // Mesmo se o sample rate for diferente (ex: 44.1k vs 48k), o resampler 
        // vai ser configurado AGORA, no vetor fantasma, sem travar o áudio que já está tocando!
        if (isPrepared) {
            DBG("C++ [loadTrack] isPrepared=true. Configurando resampling/buffer...");
            channel.resampler->prepareToPlay(preparedBlockSize, preparedSampleRate);
            juce::AudioSourceChannelInfo ready(nullptr,0,channel.readAheadCapacity-2048);
            if (!channel.bufferedSource->waitForNextAudioBlockReady(ready,5000)) {
                setLastError(EngineErrorCode::FileUnreadable,"Read-ahead preparation timed out"); return false;
            }
        }

        newChannels.push_back(std::move(channel));
    }

    DBG("C++ [loadTrack] Todos os arquivos lidos. Fazendo Swap Atomico (Lock)...");
    
    // 2. Swap Atômico: Substitui as trilhas instantaneamente! A agenda de guias
    // pertencia à música anterior e é descartada fora do lock.
    GuideTimeline staleGuides; CueTimeline staleCues;
    {
        const juce::SpinLock::ScopedLockType lock(channelsLock);
        playing = false; // Pausa por segurança
        channels = std::move(newChannels);
        loopEnabled=false; queuedLoopEnabled=false; activeLoop.reset(); queuedLoop.reset();
        currentSamplePosition = 0;
        timeScale=1.0; userTempoChanges.clear(); applyClickScale(); std::swap(guideTimeline,staleGuides); staleCues=std::move(cueTimeline); cueTimeline=CueTimeline{};
    }

    clearCueQueue();
    DBG("C++ [loadTrack] Swap concluido. Retornando SUCESSO para o Dart!");
    return true;
}

void AudioEngine::unloadCurrentTrack()
{
    const std::lock_guard<std::recursive_mutex> control(controlMutex);
    stop();
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    channels.clear();
    guideTimeline=GuideTimeline{}; cueTimeline=CueTimeline{}; timeScale=1.0; userTempoChanges.clear(); applyClickScale();
}

juce::String AudioEngine::getLastError() const
{
    const juce::SpinLock::ScopedLockType lock(errorLock);
    return lastError;
}

EngineErrorCode AudioEngine::getLastErrorCode() const
{
    const juce::SpinLock::ScopedLockType lock(errorLock);
    return lastErrorCode;
}

void AudioEngine::setLastError(EngineErrorCode code, const juce::String& errorMessage)
{
    const juce::SpinLock::ScopedLockType lock(errorLock);
    lastError = errorMessage;
    lastErrorCode = code;
}

void AudioEngine::play()
{
    {
        const juce::SpinLock::ScopedLockType lock(channelsLock);
        if (channels.empty())
            return;
    }
    playing = true;
}

void AudioEngine::pause()
{
    playing = false;
    stopMidiClock();
}

void AudioEngine::stop()
{
    const std::lock_guard<std::recursive_mutex> control(controlMutex);
    playing=false;
    stopMidiClock();
    { const juce::SpinLock::ScopedLockType lock(channelsLock);
      loopEnabled=false; queuedLoopEnabled=false; activeLoop.reset(); queuedLoop.reset(); }
    seekToSeconds(0);
}

void AudioEngine::seekToSeconds(double seconds)
{
    const std::lock_guard<std::recursive_mutex> control(controlMutex);
    if (!std::isfinite(seconds) || seconds < 0) return;
    const bool resume=playing.exchange(false);
    {
        const juce::SpinLock::ScopedLockType lock(channelsLock);
        seconds = channels.empty() ? 0.0 : juce::jmin(seconds * timeScale, channels.front().readerSource->getTotalLength() / channels.front().fileSampleRate);
        if (loopEnabled && activeLoop && (seconds < activeLoop->start || seconds >= activeLoop->end)) seconds=activeLoop->start;
        currentSamplePosition = static_cast<int64_t>(std::llround(seconds * currentSampleRate));
        for (auto& channel : channels) if (channel.bufferedSource) {
            // A counted loop plays from its cache; the streams wait at the loop end for the continuation.
            const double streamSeconds = (loopEnabled && activeLoop && activeLoop->repeats > 0) ? activeLoop->end : seconds;
            channel.bufferedSource->setNextReadPosition(static_cast<juce::int64>(std::llround(streamSeconds*channel.fileSampleRate)));
            channel.resampler->flushBuffers();
        }
        loopPasses=0;
        clickTimeline.reset(); guideTimeline.reset();
    }
    if (prefillChannels()) playing=resume;
}

double AudioEngine::getCurrentPositionSeconds() const
{
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    return static_cast<double>(currentSamplePosition.load()) / (currentSampleRate * timeScale);
}

double AudioEngine::getTotalLengthSeconds() const
{
    const juce::SpinLock::ScopedLockType lock(channelsLock);

    if (channels.empty() || channels[0].readerSource == nullptr)
        return 0.0;

    auto* reader = channels[0].readerSource->getAudioFormatReader();
    return reader != nullptr ? reader->lengthInSamples / channels[0].fileSampleRate / timeScale : 0.0;
}

bool AudioEngine::isPlaying() const
{
    return playing.load();
}

uint64_t AudioEngine::getUnderrunCount() const { return underrunCount.load(); }

std::shared_ptr<AudioEngine::LoopCache> AudioEngine::prepareLoop(double start, double end)
{
    // Caller holds controlMutex; file list and ownership cannot change while decoding.
    if (channels.empty() || !std::isfinite(start) || !std::isfinite(end) || start < 0 || end-start < 1.0/8000
        || end > channels.front().readerSource->getTotalLength()/channels.front().fileSampleRate) {
        setLastError(EngineErrorCode::FormatMismatch,"Invalid loop range"); return {};
    }
    constexpr uint64_t limit=128ULL*1024*1024;
    uint64_t bytes=0;
    for (const auto& channel : channels) {
        const long double frames=std::ceil(static_cast<long double>(end-start)*channel.fileSampleRate)+3;
        if (frames*2*sizeof(float) > limit-bytes) { setLastError(EngineErrorCode::FormatMismatch,"Loop cache exceeds 128 MiB"); return {}; }
        bytes+=static_cast<uint64_t>(frames)*2*sizeof(float);
    }
    auto result=std::make_shared<LoopCache>(); result->start=start; result->end=end;
    result->stems.resize(channels.size()); result->firstFrames.resize(channels.size());
    juce::AudioFormatManager loader; loader.registerBasicFormats();
    for (size_t index=0;index<channels.size();++index) {
        const auto& channel=channels[index];
        std::unique_ptr<juce::AudioFormatReader> reader(loader.createReaderFor(channel.file));
        if (!reader || reader->sampleRate!=channel.fileSampleRate) { setLastError(EngineErrorCode::FileUnreadable,"Loop source unavailable"); return {}; }
        const int64_t first=static_cast<int64_t>(std::floor(start*channel.fileSampleRate));
        const int length=static_cast<int>(std::ceil(end*channel.fileSampleRate)-first)+2;
        result->firstFrames[index]=first; auto& data=result->stems[index]; data.setSize(2,length); data.clear();
        if (!reader->read(&data,0,length,first,true,true)) { setLastError(EngineErrorCode::FileUnreadable,"Loop decoding failed"); return {}; }
        if (reader->numChannels==1) data.copyFrom(1,0,data,0,0,length);
    }
    return result;
}

void AudioEngine::loopToFileTime(double& start, double& end)
{
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    start*=timeScale; end*=timeScale;
    if (channels.empty()) return;
    const double total=channels.front().readerSource->getTotalLength()/channels.front().fileSampleRate;
    if (end > total && end-total < 1e-6) end=total; // song-end round trip through the scale
}

bool AudioEngine::setLoop(double start, double end, bool enabled, int repeats)
{
    const std::lock_guard<std::recursive_mutex> control(controlMutex);
    if (!enabled) {
        const bool resume=playing.exchange(false);
        const double seconds=getCurrentPositionSeconds();
        { const juce::SpinLock::ScopedLockType lock(channelsLock);
          loopEnabled=false; queuedLoopEnabled=false; activeLoop.reset(); queuedLoop.reset(); }
        seekToSeconds(seconds);
        if (prefillChannels()) playing=resume;
        return true;
    }
    loopToFileTime(start,end);
    if (repeats < 0 || repeats > 1000) { setLastError(EngineErrorCode::FormatMismatch,"Invalid loop repeat count"); return false; }
    auto bank=prepareLoop(start,end); if (!bank) return false;
    bank->repeats=repeats;
    if (repeats > 0) parkStreamsAt(bank->end);  // the continuation after the last pass reads ahead while the cache plays
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    activeLoop=std::move(bank); queuedLoop.reset(); queuedLoopEnabled=false; loopEnabled=true; loopPasses=0;
    const double seconds=static_cast<double>(currentSamplePosition.load())/currentSampleRate;
    if (seconds < start || seconds >= end) currentSamplePosition=static_cast<int64_t>(std::llround(start*currentSampleRate));
    clickTimeline.reset(); guideTimeline.reset(); setLastError(EngineErrorCode::None,""); return true;
}

bool AudioEngine::enqueueLoop(double start, double end, int repeats)
{
    const std::lock_guard<std::recursive_mutex> control(controlMutex);
    { const juce::SpinLock::ScopedLockType lock(channelsLock);
      if (!loopEnabled || !activeLoop) { setLastError(EngineErrorCode::FormatMismatch,"Enable a loop before enqueueing"); return false; } }
    loopToFileTime(start,end);
    if (repeats < 0 || repeats > 1000) { setLastError(EngineErrorCode::FormatMismatch,"Invalid loop repeat count"); return false; }
    auto bank=prepareLoop(start,end); if (!bank) return false;
    bank->repeats=repeats;
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    queuedLoop=std::move(bank); queuedLoopEnabled=true; setLastError(EngineErrorCode::None,""); return true;
}

void AudioEngine::clearQueuedLoop()
{
    const std::lock_guard<std::recursive_mutex> control(controlMutex);
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    queuedLoopEnabled=false; queuedLoop.reset();
}
void AudioEngine::getLoopState(double* out6) const
{
    if (!out6) return;
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    out6[0]=loopEnabled ? 1 : 0; out6[1]=loopEnabled && activeLoop ? activeLoop->start/timeScale : 0;
    out6[2]=loopEnabled && activeLoop ? activeLoop->end/timeScale : 0; out6[3]=queuedLoopEnabled ? 1 : 0;
    out6[4]=queuedLoopEnabled && queuedLoop ? queuedLoop->start/timeScale : 0;
    out6[5]=queuedLoopEnabled && queuedLoop ? queuedLoop->end/timeScale : 0;
}
void AudioEngine::parkStreamsAt(double seconds)
{
    // Control thread, loop mode: the streams are idle, so point them at the loop end and let read-ahead fill.
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    for (auto& channel : channels) if (channel.bufferedSource) {
        channel.bufferedSource->setNextReadPosition(static_cast<juce::int64>(std::llround(seconds*channel.fileSampleRate)));
        channel.resampler->flushBuffers();
    }
}

void AudioEngine::normalizeLoopPosition()
{
    if (!loopEnabled || !activeLoop) return;
    const int64_t position=currentSamplePosition.load();
    const auto start=static_cast<int64_t>(std::llround(activeLoop->start*currentSampleRate));
    const auto end=static_cast<int64_t>(std::llround(activeLoop->end*currentSampleRate));
    if (position >= start && position < end) return;
    const int64_t overflow=position >= end ? position-end : 0;
    if (position >= end && queuedLoopEnabled && queuedLoop) {
        // Retain the previous cache until a control-thread queue operation destroys it.
        activeLoop.swap(queuedLoop); queuedLoopEnabled=false; loopPasses=0;
    } else if (position >= end && activeLoop->repeats > 0 && ++loopPasses >= activeLoop->repeats) {
        // Last pass done: continue streaming right after the loop end (the streams were parked there when the loop was set).
        loopEnabled=false; currentSamplePosition=end; return;
    }
    const auto nextStart=static_cast<int64_t>(std::llround(activeLoop->start*currentSampleRate));
    const auto nextEnd=static_cast<int64_t>(std::llround(activeLoop->end*currentSampleRate));
    currentSamplePosition=nextStart+overflow % juce::jmax<int64_t>(1,nextEnd-nextStart);
    clickTimeline.reset(); guideTimeline.reset();
}
bool AudioEngine::getLoopEnabled() const { const juce::SpinLock::ScopedLockType lock(channelsLock); return loopEnabled; }
bool AudioEngine::getQueuedLoopEnabled() const { const juce::SpinLock::ScopedLockType lock(channelsLock); return queuedLoopEnabled; }
double AudioEngine::getLoopStart() const { const juce::SpinLock::ScopedLockType lock(channelsLock); return loopEnabled && activeLoop ? activeLoop->start/timeScale : 0; }
double AudioEngine::getLoopEnd() const { const juce::SpinLock::ScopedLockType lock(channelsLock); return loopEnabled && activeLoop ? activeLoop->end/timeScale : 0; }
double AudioEngine::getQueuedLoopStart() const { const juce::SpinLock::ScopedLockType lock(channelsLock); return queuedLoopEnabled && queuedLoop ? queuedLoop->start/timeScale : 0; }
double AudioEngine::getQueuedLoopEnd() const { const juce::SpinLock::ScopedLockType lock(channelsLock); return queuedLoopEnabled && queuedLoop ? queuedLoop->end/timeScale : 0; }

bool AudioEngine::channelsReady(int outputSamples, uint32_t timeoutMs)
{
    for (auto& channel : channels) {
        const int inputSamples=static_cast<int>(std::ceil(outputSamples*channel.fileSampleRate/currentSampleRate))+3;
        juce::AudioSourceChannelInfo ready(nullptr,0,inputSamples);
        if (!channel.bufferedSource->waitForNextAudioBlockReady(ready,timeoutMs)) return false;
    }
    return true;
}

bool AudioEngine::waitForReadAhead(int outputSamples, uint32_t timeoutMs)
{
    const std::lock_guard<std::recursive_mutex> control(controlMutex);
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    return channelsReady(juce::jmin(outputSamples,preparedBlockSize),timeoutMs);
}

bool AudioEngine::prefillChannels()
{
    if (!isPrepared) return true;
    for (auto& channel : channels) {
        juce::AudioSourceChannelInfo ready(nullptr,0,channel.readAheadCapacity-2048);
        if (!channel.bufferedSource->waitForNextAudioBlockReady(ready,5000)) {
            setLastError(EngineErrorCode::FileUnreadable,"Read-ahead preparation timed out"); return false;
        }
    }
    return true;
}

void AudioEngine::setChannelVolume(int channelIndex, float volume)
{
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    if (channelIndex >= 0 && channelIndex < static_cast<int>(channels.size()))
        channels[static_cast<size_t>(channelIndex)].volume = juce::jlimit(0.0f, 1.0f, volume);
}

void AudioEngine::setChannelMuted(int channelIndex, bool muted)
{
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    if (channelIndex >= 0 && channelIndex < static_cast<int>(channels.size()))
        channels[static_cast<size_t>(channelIndex)].muted = muted;
}

bool AudioEngine::setChannelRoute(int channelIndex, int outputBase, bool mono)
{
    // Whether the route fits the device is decided at render time (invalid routes are silent).
    if (outputBase < 0 || outputBase > 63) { setLastError(EngineErrorCode::FormatMismatch,"Invalid channel route"); return false; }
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    if (channelIndex < 0 || channelIndex >= static_cast<int>(channels.size())) { setLastError(EngineErrorCode::FormatMismatch,"Invalid channel index"); return false; }
    channels[static_cast<size_t>(channelIndex)].route={outputBase,mono}; return true;
}

void AudioEngine::setMasterVolume(float volume)
{
    if (!std::isfinite(volume)) return;
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    masterVolume = juce::jlimit(0.0f, 2.0f, volume);
}

bool AudioEngine::setTimeScale(double scale)
{
    const std::lock_guard<std::recursive_mutex> control(controlMutex);
    if (!std::isfinite(scale) || scale < 0.25 || scale > 4.0) { setLastError(EngineErrorCode::FormatMismatch,"Invalid time scale"); return false; }
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    timeScale=scale; loopEnabled=false; queuedLoopEnabled=false; activeLoop.reset(); queuedLoop.reset();
    applyClickScale(); guideTimeline.setTimeScale(scale); cueTimeline.setTimeScale(scale);
    setLastError(EngineErrorCode::None,""); return true;
}

double AudioEngine::getTimeScale() const { const juce::SpinLock::ScopedLockType lock(channelsLock); return timeScale; }

int AudioEngine::getChannelCount() const
{
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    return static_cast<int>(channels.size());
}

void AudioEngine::setClickEnabled(bool enabled)
{
    clickEnabled = enabled;
}

bool AudioEngine::configureClick(double bpm, int numerator, int denominator, int unit, double offset,
                                 double accent, double quarter, double eighth, double sixteenth)
{
    const std::array<double,4> levels {{accent,quarter,eighth,sixteenth}};
    if (!ClickTimeline::valid(bpm,numerator,denominator,unit,offset,levels)) {
        setLastError(EngineErrorCode::FormatMismatch, "Invalid click configuration"); return false;
    }
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    userClickBpm=bpm; userClickOffset=offset;
    clickTimeline.numerator=numerator; clickTimeline.denominator=denominator;
    clickTimeline.bpmUnit=unit; clickTimeline.gains=levels;
    applyClickScale();
    return true;
}

void AudioEngine::setClickBpm(double bpm)
{
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    if (!std::isfinite(bpm) || bpm < 1 || bpm > 1000) { setLastError(EngineErrorCode::FormatMismatch,"Invalid click BPM"); return; }
    userClickBpm=bpm; applyClickScale();
}
void AudioEngine::setClickTimeSignature(int numerator, int denominator)
{
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    if (numerator < 1 || numerator > 64 || !ClickTimeline::unitValid(denominator)) { setLastError(EngineErrorCode::FormatMismatch,"Invalid click meter"); return; }
    clickTimeline.numerator=numerator; clickTimeline.denominator=denominator; clickTimeline.reset();
}
void AudioEngine::setClickOffsetSeconds(double offsetSeconds)
{
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    if (!std::isfinite(offsetSeconds) || offsetSeconds < 0 || offsetSeconds > 86400) { setLastError(EngineErrorCode::FormatMismatch,"Invalid click offset"); return; }
    userClickOffset=offsetSeconds; applyClickScale();
}
void AudioEngine::applyClickScale()
{
    // Caller holds channelsLock. Beats are laid out on the processed timeline.
    clickTimeline.bpm=userClickBpm/timeScale; clickTimeline.offset=userClickOffset*timeScale; clickTimeline.reset();
    timecode.onsetSeconds=userTimecodeOnset*timeScale; timecode.reset();
    if (!tempoChangesValid(userTempoChanges,userClickOffset)) userTempoChanges.clear();  // an offset past a change invalidates it
    clickTimeline.changes=userTempoChanges;
    for (auto& change : clickTimeline.changes) { change.start*=timeScale; change.bpm/=timeScale; }
    midiClock.changes=clickTimeline.changes;
    midiClock.bpm=clickTimeline.bpm; midiClock.offset=clickTimeline.offset; midiClock.bpmUnit=clickTimeline.bpmUnit;
}

bool AudioEngine::setClickTempoChanges(const double* starts, const double* bpms, const int* numerators, const int* denominators, int count)
{
    if (count < 0 || count > 512 || (count && (!starts || !bpms || !numerators || !denominators))) {
        setLastError(EngineErrorCode::FormatMismatch,"Invalid tempo changes"); return false;
    }
    std::vector<TempoChange> proposed(static_cast<size_t>(count));
    for (int i=0;i<count;++i) proposed[static_cast<size_t>(i)]={starts[i],bpms[i],numerators[i],denominators[i]};
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    if (!tempoChangesValid(proposed,userClickOffset)) { setLastError(EngineErrorCode::FormatMismatch,"Invalid tempo changes"); return false; }
    userTempoChanges=std::move(proposed); applyClickScale(); setLastError(EngineErrorCode::None,""); return true;
}

void AudioEngine::setClickGain(float gain)
{
    if (!std::isfinite(gain) || gain < 0 || gain > 2) { setLastError(EngineErrorCode::FormatMismatch,"Invalid click gain"); return; }
    const juce::SpinLock::ScopedLockType lock(channelsLock); clickTimeline.masterGain=gain;
}
bool AudioEngine::decodeClickSound(const juce::String& path, juce::AudioBuffer<float>& decoded, double& rate)
{
    rate=44100;
    if (path.isEmpty()) return true;
    juce::AudioFormatManager loader; loader.registerBasicFormats();
    std::unique_ptr<juce::AudioFormatReader> reader(loader.createReaderFor(juce::File(path)));
    if (!reader || reader->lengthInSamples <= 0 || !std::isfinite(reader->sampleRate) || reader->sampleRate < 8000 || reader->sampleRate > 192000
        || reader->lengthInSamples > reader->sampleRate*10) { setLastError(EngineErrorCode::FileUnreadable,"Click sound unavailable or exceeds ten seconds"); return false; }
    rate=reader->sampleRate; decoded.setSize(1,static_cast<int>(reader->lengthInSamples));
    if (!reader->read(&decoded,0,decoded.getNumSamples(),0,true,false)) { setLastError(EngineErrorCode::FileUnreadable,"Click sound decoding failed"); return false; }
    return true;
}

bool AudioEngine::loadClickSound(int voice, const juce::String& path)
{
    if (voice < 0 || voice > 3) { setLastError(EngineErrorCode::FormatMismatch,"Invalid click voice"); return false; }
    juce::AudioBuffer<float> decoded; double rate;
    if (!decodeClickSound(path,decoded,rate)) return false;
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    clickTimeline.sounds[voice]=std::move(decoded); clickTimeline.soundRates[voice]=rate; clickTimeline.starts[voice]=-1;
    setLastError(EngineErrorCode::None, "");
    return true;
}

bool AudioEngine::loadClickBank(const std::array<juce::String,4>& paths)
{
    std::array<juce::AudioBuffer<float>,4> decoded;
    std::array<double,4> rates;
    for (int voice=0;voice<4;++voice)
        if (!decodeClickSound(paths[voice],decoded[voice],rates[voice])) return false;
    // Publish only after all four voices decode; a failure retains the old bank and tails.
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    clickTimeline.sounds=std::move(decoded); clickTimeline.soundRates=rates; clickTimeline.reset();
    setLastError(EngineErrorCode::None, "");
    return true;
}

void AudioEngine::setGuidesEnabled(bool enabled) { guidesEnabled=enabled; }

bool AudioEngine::configureTimecode(int rateIndex, int64_t startFrame, double onsetSeconds, int outputChannel, float gain)
{
    if (!TimecodeGenerator::valid(rateIndex,startFrame,onsetSeconds,gain) || outputChannel < 0 || outputChannel > 63) {
        setLastError(EngineErrorCode::FormatMismatch,"Invalid timecode configuration"); return false;
    }
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    timecode.rateIndex=rateIndex; timecode.startFrame=startFrame; timecode.gain=gain; userTimecodeOnset=onsetSeconds;
    timecode.onsetSeconds=onsetSeconds*timeScale; timecodeOutput=outputChannel; timecode.reset();
    setLastError(EngineErrorCode::None,""); return true;
}

void AudioEngine::setTimecodeEnabled(bool enabled) { timecodeEnabled=enabled; }

bool AudioEngine::configureGuides(const double* times, const char** paths, const float* gains, int count)
{
    const std::lock_guard<std::recursive_mutex> control(controlMutex);
    const double length=getTotalLengthSeconds();
    if (count < 0 || count > 4096 || (count && (!times || !paths || !gains || length <= 0))) {
        setLastError(EngineErrorCode::FormatMismatch,"Invalid guide schedule"); return false;
    }
    std::vector<GuideTimeline::Cue> cues; cues.reserve(count);
    std::map<juce::String,std::shared_ptr<const GuideTimeline::Sound>> decoded;
    uint64_t bytes=0; double previous=-1;
    juce::AudioFormatManager loader; loader.registerBasicFormats();
    for (int index=0;index<count;++index) {
        if (!std::isfinite(times[index]) || times[index]<0 || times[index]>length || times[index]<previous
            || !std::isfinite(gains[index]) || gains[index]<0 || gains[index]>2 || !paths[index] || !*paths[index]) {
            setLastError(EngineErrorCode::FormatMismatch,"Invalid guide cue"); return false;
        }
        previous=times[index]; const auto path=juce::String::fromUTF8(paths[index]);
        auto found=decoded.find(path);
        if (found==decoded.end()) {
            std::unique_ptr<juce::AudioFormatReader> reader(loader.createReaderFor(juce::File(path)));
            if (!reader || !std::isfinite(reader->sampleRate) || reader->sampleRate<8000 || reader->sampleRate>192000
                || reader->numChannels<1 || reader->numChannels>64 || reader->lengthInSamples<=0 || reader->lengthInSamples>reader->sampleRate*60) {
                setLastError(EngineErrorCode::FileUnreadable,"Guide sound unavailable or exceeds 60 seconds"); return false;
            }
            const uint64_t added=static_cast<uint64_t>(reader->lengthInSamples)*sizeof(float);
            if (added>64ULL*1024*1024-bytes) { setLastError(EngineErrorCode::FormatMismatch,"Guide PCM exceeds 64 MiB"); return false; }
            bytes+=added;
            auto sound=std::make_shared<GuideTimeline::Sound>(); sound->sourceRate=reader->sampleRate;
            sound->mono.resize(static_cast<size_t>(reader->lengthInSamples)); juce::AudioBuffer<float> block(reader->numChannels,1024);
            for(int64_t offset=0;offset<reader->lengthInSamples;offset+=1024) {
                const int n=static_cast<int>(juce::jmin<int64_t>(1024,reader->lengthInSamples-offset));
                if (!reader->read(block.getArrayOfWritePointers(),block.getNumChannels(),offset,n)) {
                    setLastError(EngineErrorCode::FileUnreadable,"Guide decoding failed"); return false;
                }
                for(int frame=0;frame<n;++frame) { double sum=0; for(int ch=0;ch<block.getNumChannels();++ch) sum+=block.getSample(ch,frame);
                    sound->mono[static_cast<size_t>(offset+frame)]=static_cast<float>(sum/block.getNumChannels()); }
            }
            found=decoded.emplace(path,std::move(sound)).first;
        }
        cues.push_back({times[index],gains[index],found->second});
    }
    GuideTimeline prepared; prepared.setTimeScale(timeScale);
    if (!prepared.configure(std::move(cues))) { setLastError(EngineErrorCode::FormatMismatch,"Invalid guide PCM"); return false; }
    {   // Swap under the lock; the previous PCM is freed after the audio thread is released.
        const juce::SpinLock::ScopedLockType lock(channelsLock);
        std::swap(guideTimeline,prepared);
    }
    setLastError(EngineErrorCode::None,""); return true;
}

juce::StringArray AudioEngine::listMidiOutputs()
{
    juce::StringArray result;
    for (const auto& device : juce::MidiOutput::getAvailableDevices()) result.add(device.identifier + "\t" + device.name);
    return result;
}

bool AudioEngine::openMidiOutput(const juce::String& deviceIdentifier)
{
    const std::lock_guard<std::recursive_mutex> control(controlMutex);
    auto device = juce::MidiOutput::openDevice(deviceIdentifier);
    if (!device) { setLastError(EngineErrorCode::DeviceInitFailed,"MIDI output unavailable"); return false; }
    attachMidiSink(std::make_unique<JuceMidiSink>(std::move(device)));
    return true;
}

void AudioEngine::attachMidiSink(std::unique_ptr<MidiSink> sink)
{
    const std::lock_guard<std::recursive_mutex> control(controlMutex);
    midiClockRunning=false;
    midiRouter.open(std::move(sink));
    setLastError(EngineErrorCode::None,"");
}

void AudioEngine::closeMidiOutput()
{
    const std::lock_guard<std::recursive_mutex> control(controlMutex);
    stopMidiClock();
    midiRouter.flush(200);
    midiRouter.close();
}

bool AudioEngine::isMidiOutputOpen() const { return midiRouter.isOpen(); }
uint64_t AudioEngine::getMidiDroppedCount() const { return midiRouter.droppedEvents() + cueDropped.load(); }

void AudioEngine::setMidiClockEnabled(bool enabled)
{
    midiClockEnabled=enabled;
    if (!enabled) stopMidiClock();
}

void AudioEngine::clearCueQueue()
{
    const std::lock_guard<std::mutex> lock(cuePollMutex);
    cueTail.store(cueHead.load(std::memory_order_acquire),std::memory_order_release);
}

void AudioEngine::stopMidiClock()
{
    // Only one of the control thread and the audio callback sends the stop message.
    if (midiClockRunning.exchange(false)) { const uint8_t stop=MidiClockTimeline::kStop; midiRouter.sendNow(&stop,1); }
}

bool AudioEngine::sendMidiMessage(const uint8_t* bytes, int size)
{
    CueTimeline::Cue cue; cue.midiSize=static_cast<uint8_t>(juce::jlimit(0,255,size));
    if (!bytes || size < 2 || size > 3) { setLastError(EngineErrorCode::FormatMismatch,"Invalid MIDI message"); return false; }
    for (int i=0;i<size;++i) cue.midi[i]=bytes[i];
    if (!CueTimeline::midiValid(cue)) { setLastError(EngineErrorCode::FormatMismatch,"Invalid MIDI message"); return false; }
    if (!midiRouter.isOpen()) { setLastError(EngineErrorCode::DeviceInitFailed,"MIDI output not open"); return false; }
    midiRouter.sendNow(bytes,size); return true;
}

bool AudioEngine::configureCues(const double* times, const uint8_t* midiBytes, const uint8_t* midiSizes, int count)
{
    const std::lock_guard<std::recursive_mutex> control(controlMutex);
    const double length=getTotalLengthSeconds();
    if (count < 0 || static_cast<size_t>(count) > CueTimeline::kMaxCues || (count && (!times || !midiBytes || !midiSizes || length <= 0))) {
        setLastError(EngineErrorCode::FormatMismatch,"Invalid cue schedule"); return false;
    }
    std::vector<CueTimeline::Cue> cues(static_cast<size_t>(count));
    for (int i=0;i<count;++i) {
        auto& cue=cues[static_cast<size_t>(i)]; cue.timeSeconds=times[i]; cue.midiSize=midiSizes[i];
        if (cue.midiSize > 3) { setLastError(EngineErrorCode::FormatMismatch,"Invalid cue message"); return false; }
        for (int b=0;b<cue.midiSize;++b) cue.midi[b]=midiBytes[3*i+b];
    }
    CueTimeline prepared;
    if (!prepared.configure(std::move(cues),length)) { setLastError(EngineErrorCode::FormatMismatch,"Invalid cue schedule"); return false; }
    CueTimeline stale;
    {
        const juce::SpinLock::ScopedLockType lock(channelsLock);
        prepared.setTimeScale(timeScale); std::swap(cueTimeline,prepared); stale=std::move(prepared);
    }
    clearCueQueue(); setLastError(EngineErrorCode::None,""); return true;
}

int AudioEngine::pollCues(uint32_t* out, int maxCount)
{
    if (!out || maxCount <= 0) return 0;
    const std::lock_guard<std::mutex> lock(cuePollMutex);
    int n=0; auto tail=cueTail.load(std::memory_order_relaxed); const auto head=cueHead.load(std::memory_order_acquire);
    while (tail != head && n < maxCount) { out[n++]=cueQueue[tail % cueQueue.size()].load(std::memory_order_relaxed); ++tail; }
    cueTail.store(tail,std::memory_order_release); return n;
}

void AudioEngine::generateClickBuffers(double sampleRate)
{
    const int length = static_cast<int>(sampleRate*0.03);
    clickTimeline.fallbackRate=sampleRate;
    for (int voice=0;voice<4;++voice) {
        auto& buffer=clickTimeline.fallback[voice]; buffer.setSize(1,length);
        const double frequency=voice==0 ? 1760.0 : voice==1 ? 880.0 : voice==2 ? 660.0 : 440.0;
        for (int i=0;i<length;++i)
            buffer.setSample(0,i,static_cast<float>(std::sin(2.0*juce::MathConstants<double>::pi*frequency*i/sampleRate)*(1.0-double(i)/length)*0.5));
    }
}

void AudioEngine::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    const std::lock_guard<std::recursive_mutex> control(controlMutex);
    if (!std::isfinite(sampleRate) || sampleRate < 8000 || sampleRate > 192000 || samplesPerBlockExpected < 1 || samplesPerBlockExpected > 8192) {
        setLastError(EngineErrorCode::FormatMismatch,"Invalid audio preparation format"); return;
    }
    const bool resume=playing.exchange(false);
    {
        const juce::SpinLock::ScopedLockType lock(channelsLock);
        const double positionSeconds=static_cast<double>(currentSamplePosition.load())/currentSampleRate;
        currentSampleRate = sampleRate;
        currentSamplePosition=static_cast<int64_t>(std::llround(positionSeconds*sampleRate));
        clickTimeline.reset(); guideTimeline.reset();
        mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

        generateClickBuffers(sampleRate);

        preparedBlockSize = samplesPerBlockExpected;
        preparedSampleRate = sampleRate;
        isPrepared = true;

        scratchBuffer.setSize(2, samplesPerBlockExpected);
        guideScratch.setSize(1,samplesPerBlockExpected);
        timecodeScratch.setSize(1,samplesPerBlockExpected);

        for (auto& channel : channels)
            if (channel.resampler != nullptr)
            {
                const double streamSeconds = (loopEnabled && activeLoop && activeLoop->repeats > 0) ? activeLoop->end : positionSeconds;
                channel.bufferedSource->setNextReadPosition(static_cast<juce::int64>(std::llround(streamSeconds*channel.fileSampleRate)));
                channel.resampler->setResamplingRatio(channel.fileSampleRate / sampleRate);
                channel.resampler->prepareToPlay(samplesPerBlockExpected, sampleRate);
                channel.resampler->flushBuffers();
            }
    }
    if (prefillChannels()) playing=resume;
}

void AudioEngine::releaseResources()
{
    const std::lock_guard<std::recursive_mutex> control(controlMutex);
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    mixerSource.releaseResources();

    for (auto& channel : channels)
        if (channel.resampler != nullptr)
            channel.resampler->releaseResources();

    isPrepared = false;
}

void AudioEngine::getNextAudioBlock(const juce::AudioSourceChannelInfo& info)
{
    info.clearActiveBufferRegion();
    if (!playing.load() && midiClockRunning.exchange(false)) {  // pause/EOF seen by the audio thread: realtime-safe path
        const uint8_t stop=MidiClockTimeline::kStop; midiRouter.push(juce::Time::getMillisecondCounterHiRes(),0,44100.0,&stop,1);
    }
    if (!playing.load() || info.buffer == nullptr || info.numSamples <= 0) return;
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    if (!playing.load() || channels.empty() || !isPrepared || preparedBlockSize <= 0) return;
    const auto& first=channels.front();
    const int64_t end=static_cast<int64_t>(std::llround(first.readerSource->getTotalLength()/first.fileSampleRate*currentSampleRate));
    const float rampStep=GainRamp::stepFor(currentSampleRate);
    const double blockHostMs=juce::Time::getMillisecondCounterHiRes();
    int written=0;
    while (written < info.numSamples) {
        normalizeLoopPosition();
        const int64_t position=currentSamplePosition.load();
        const int64_t boundary=loopEnabled && activeLoop ? static_cast<int64_t>(std::llround(activeLoop->end*currentSampleRate)) : end;
        const int count=static_cast<int>(juce::jmin<int64_t>(juce::jmin(preparedBlockSize,info.numSamples-written),boundary-position));
        if (count <= 0) { currentSamplePosition=end; playing=false; break; }
        if (!loopEnabled && !channelsReady(count,0)) { ++underrunCount; break; }
        for (size_t index=0;index<channels.size();++index) {
            auto& channel=channels[index]; scratchBuffer.clear();
            if (loopEnabled && activeLoop) {
                const auto& data=activeLoop->stems[index];
                for (int sample=0;sample<count;++sample) {
                    const double source=(position+sample)/currentSampleRate*channel.fileSampleRate-activeLoop->firstFrames[index];
                    const int a=juce::jlimit(0,data.getNumSamples()-1,static_cast<int>(source));
                    const int b=juce::jmin(a+1,data.getNumSamples()-1); const float alpha=static_cast<float>(source-std::floor(source));
                    for (int ch=0;ch<2;++ch) scratchBuffer.setSample(ch,sample,data.getSample(ch,a)+alpha*(data.getSample(ch,b)-data.getSample(ch,a)));
                }
            } else { juce::AudioSourceChannelInfo source(&scratchBuffer,0,count); channel.resampler->getNextAudioBlock(source); }
            channel.ramp.set(channel.muted ? 0.0f : channel.volume);
            if (channel.ramp.silent()) continue;
            mixStem(scratchBuffer.getReadPointer(0),scratchBuffer.getReadPointer(1),info.buffer->getArrayOfWritePointers(),
                    info.buffer->getNumChannels(),info.startSample+written,count,channel.route,channel.ramp,rampStep);
        }
        clickTimeline.render(*info.buffer,info.startSample+written,count,position,currentSampleRate,clickEnabled.load());
        guideScratch.clear(); guideTimeline.render(guideScratch.getWritePointer(0),count,position,currentSampleRate,guidesEnabled.load());
        for(int output=0;output<info.buffer->getNumChannels();++output)
            info.buffer->addFrom(output,info.startSample+written,guideScratch,0,0,count);
        if (midiRouter.isOpen()) {
            if (midiClockEnabled.load()) {
                if (!midiClockRunning.load()) {
                    const uint8_t start=MidiClockTimeline::startMessageFor(position); midiClockRunning=true;
                    midiRouter.push(blockHostMs,written,currentSampleRate,&start,1);
                }
                midiClock.render(count,position,currentSampleRate,[&](int offset) {
                    const uint8_t pulse=MidiClockTimeline::kClock; midiRouter.push(blockHostMs,written+offset,currentSampleRate,&pulse,1); });
            }
        }
        cueTimeline.render(count,position,currentSampleRate,[&](size_t index,int offset) {
            const auto& cue=cueTimeline.at(index);
            if (cue.midiSize && midiRouter.isOpen()) midiRouter.push(blockHostMs,written+offset,currentSampleRate,cue.midi,cue.midiSize);
            const auto head=cueHead.load(std::memory_order_relaxed);
            if (head-cueTail.load(std::memory_order_acquire) >= cueQueue.size()) { cueDropped.fetch_add(1); return; }
            cueQueue[head % cueQueue.size()].store(static_cast<uint32_t>(index),std::memory_order_relaxed);
            cueHead.store(head+1,std::memory_order_release);
        });
        masterRamp.set(masterVolume);
        applyGain(info.buffer->getArrayOfWritePointers(),info.buffer->getNumChannels(),info.startSample+written,count,masterRamp,rampStep);
        if (timecodeEnabled.load() && timecodeOutput < info.buffer->getNumChannels()) {  // after the master stage: timecode keeps its own level
            timecodeScratch.clear(); timecode.render(timecodeScratch.getWritePointer(0),count,position,currentSampleRate);
            info.buffer->addFrom(timecodeOutput,info.startSample+written,timecodeScratch,0,0,count);
        }
        currentSamplePosition=position+count; written+=count;
        normalizeLoopPosition();
        if (!loopEnabled && position+count >= end) { currentSamplePosition=end; playing=false; break; }
    }
}

} // namespace wtracks
