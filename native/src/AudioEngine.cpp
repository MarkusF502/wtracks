#include "../include/AudioEngine.h"

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

    audioSourcePlayer.setSource(nullptr);
    deviceManager.removeAudioCallback(&audioSourcePlayer);
    deviceManager.closeAudioDevice();

    const juce::SpinLock::ScopedLockType lock(channelsLock);
    channels.clear();
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
    
    // 2. Swap Atômico: Substitui as trilhas instantaneamente!
    {
        const juce::SpinLock::ScopedLockType lock(channelsLock);
        playing = false; // Pausa por segurança
        channels = std::move(newChannels);
        loopEnabled=false; queuedLoopEnabled=false; activeLoop.reset(); queuedLoop.reset();
        currentSamplePosition = 0;
        clickTimeline.reset();
    }

    DBG("C++ [loadTrack] Swap concluido. Retornando SUCESSO para o Dart!");
    return true;
}

void AudioEngine::unloadCurrentTrack()
{
    const std::lock_guard<std::recursive_mutex> control(controlMutex);
    stop();
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    channels.clear();
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
}

void AudioEngine::stop()
{
    const std::lock_guard<std::recursive_mutex> control(controlMutex);
    playing=false;
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
        seconds = channels.empty() ? 0.0 : juce::jmin(seconds, channels.front().readerSource->getTotalLength() / channels.front().fileSampleRate);
        if (loopEnabled && activeLoop && (seconds < activeLoop->start || seconds >= activeLoop->end)) seconds=activeLoop->start;
        currentSamplePosition = static_cast<int64_t>(std::llround(seconds * currentSampleRate));
        for (auto& channel : channels) if (channel.bufferedSource) {
            channel.bufferedSource->setNextReadPosition(static_cast<juce::int64>(std::llround(seconds*channel.fileSampleRate)));
            channel.resampler->flushBuffers();
        }
        clickTimeline.reset();
    }
    if (prefillChannels()) playing=resume;
}

double AudioEngine::getCurrentPositionSeconds() const
{
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    return static_cast<double>(currentSamplePosition.load()) / currentSampleRate;
}

double AudioEngine::getTotalLengthSeconds() const
{
    const juce::SpinLock::ScopedLockType lock(channelsLock);

    if (channels.empty() || channels[0].readerSource == nullptr)
        return 0.0;

    auto* reader = channels[0].readerSource->getAudioFormatReader();
    return reader != nullptr ? reader->lengthInSamples / channels[0].fileSampleRate : 0.0;
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

bool AudioEngine::setLoop(double start, double end, bool enabled)
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
    auto bank=prepareLoop(start,end); if (!bank) return false;
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    activeLoop=std::move(bank); queuedLoop.reset(); queuedLoopEnabled=false; loopEnabled=true;
    const double seconds=static_cast<double>(currentSamplePosition.load())/currentSampleRate;
    if (seconds < start || seconds >= end) currentSamplePosition=static_cast<int64_t>(std::llround(start*currentSampleRate));
    clickTimeline.reset(); setLastError(EngineErrorCode::None,""); return true;
}

bool AudioEngine::enqueueLoop(double start, double end)
{
    const std::lock_guard<std::recursive_mutex> control(controlMutex);
    { const juce::SpinLock::ScopedLockType lock(channelsLock);
      if (!loopEnabled || !activeLoop) { setLastError(EngineErrorCode::FormatMismatch,"Enable a loop before enqueueing"); return false; } }
    auto bank=prepareLoop(start,end); if (!bank) return false;
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
    out6[0]=loopEnabled ? 1 : 0; out6[1]=loopEnabled && activeLoop ? activeLoop->start : 0;
    out6[2]=loopEnabled && activeLoop ? activeLoop->end : 0; out6[3]=queuedLoopEnabled ? 1 : 0;
    out6[4]=queuedLoopEnabled && queuedLoop ? queuedLoop->start : 0;
    out6[5]=queuedLoopEnabled && queuedLoop ? queuedLoop->end : 0;
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
        activeLoop.swap(queuedLoop); queuedLoopEnabled=false;
    }
    const auto nextStart=static_cast<int64_t>(std::llround(activeLoop->start*currentSampleRate));
    const auto nextEnd=static_cast<int64_t>(std::llround(activeLoop->end*currentSampleRate));
    currentSamplePosition=nextStart+overflow % juce::jmax<int64_t>(1,nextEnd-nextStart);
    clickTimeline.reset();
}
bool AudioEngine::getLoopEnabled() const { const juce::SpinLock::ScopedLockType lock(channelsLock); return loopEnabled; }
bool AudioEngine::getQueuedLoopEnabled() const { const juce::SpinLock::ScopedLockType lock(channelsLock); return queuedLoopEnabled; }
double AudioEngine::getLoopStart() const { const juce::SpinLock::ScopedLockType lock(channelsLock); return loopEnabled && activeLoop ? activeLoop->start : 0; }
double AudioEngine::getLoopEnd() const { const juce::SpinLock::ScopedLockType lock(channelsLock); return loopEnabled && activeLoop ? activeLoop->end : 0; }
double AudioEngine::getQueuedLoopStart() const { const juce::SpinLock::ScopedLockType lock(channelsLock); return queuedLoopEnabled && queuedLoop ? queuedLoop->start : 0; }
double AudioEngine::getQueuedLoopEnd() const { const juce::SpinLock::ScopedLockType lock(channelsLock); return queuedLoopEnabled && queuedLoop ? queuedLoop->end : 0; }

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
    clickTimeline.bpm=bpm; clickTimeline.numerator=numerator; clickTimeline.denominator=denominator;
    clickTimeline.bpmUnit=unit; clickTimeline.offset=offset; clickTimeline.gains=levels;
    clickTimeline.reset();
    return true;
}

void AudioEngine::setClickBpm(double bpm)
{
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    if (!std::isfinite(bpm) || bpm < 1 || bpm > 1000) { setLastError(EngineErrorCode::FormatMismatch,"Invalid click BPM"); return; }
    clickTimeline.bpm=bpm; clickTimeline.reset();
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
    clickTimeline.offset=offsetSeconds; clickTimeline.reset();
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
        clickTimeline.reset();
        mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

        generateClickBuffers(sampleRate);

        preparedBlockSize = samplesPerBlockExpected;
        preparedSampleRate = sampleRate;
        isPrepared = true;

        scratchBuffer.setSize(2, samplesPerBlockExpected);

        for (auto& channel : channels)
            if (channel.resampler != nullptr)
            {
                channel.bufferedSource->setNextReadPosition(static_cast<juce::int64>(std::llround(positionSeconds*channel.fileSampleRate)));
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
    if (!playing.load() || info.buffer == nullptr || info.numSamples <= 0) return;
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    if (!playing.load() || channels.empty() || !isPrepared || preparedBlockSize <= 0) return;
    const auto& first=channels.front();
    const int64_t end=static_cast<int64_t>(std::llround(first.readerSource->getTotalLength()/first.fileSampleRate*currentSampleRate));
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
            if (channel.muted || channel.volume <= 0) continue;
            for (int output=0;output<info.buffer->getNumChannels();++output)
                info.buffer->addFrom(output,info.startSample+written,scratchBuffer,juce::jmin(output,scratchBuffer.getNumChannels()-1),0,count,channel.volume);
        }
        clickTimeline.render(*info.buffer,info.startSample+written,count,position,currentSampleRate,clickEnabled.load());
        currentSamplePosition=position+count; written+=count;
        normalizeLoopPosition();
        if (!loopEnabled && position+count >= end) { currentSamplePosition=end; playing=false; break; }
    }
}

} // namespace wtracks
