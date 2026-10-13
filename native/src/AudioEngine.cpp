#include "../include/AudioEngine.h"

namespace wtracks
{

AudioEngine::AudioEngine()
{
    formatManager.registerBasicFormats(); 
}

AudioEngine::~AudioEngine()
{
    shutdown();
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
    stop();

    audioSourcePlayer.setSource(nullptr);
    deviceManager.removeAudioCallback(&audioSourcePlayer);
    deviceManager.closeAudioDevice();

    const juce::SpinLock::ScopedLockType lock(channelsLock);
    channels.clear();
}

bool AudioEngine::loadTrack(const juce::String& songId, const std::vector<juce::File>& channelFiles)
{
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
        channel.fileSampleRate = reader->sampleRate;
        channel.readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
        channel.resampler = std::make_unique<juce::ResamplingAudioSource>(channel.readerSource.get(), false, 2);
        channel.resampler->setResamplingRatio(channel.fileSampleRate / preparedSampleRate);

        // Mesmo se o sample rate for diferente (ex: 44.1k vs 48k), o resampler 
        // vai ser configurado AGORA, no vetor fantasma, sem travar o áudio que já está tocando!
        if (isPrepared) {
            DBG("C++ [loadTrack] isPrepared=true. Configurando resampling/buffer...");
            channel.resampler->prepareToPlay(preparedBlockSize, preparedSampleRate);
        }

        newChannels.push_back(std::move(channel));
    }

    DBG("C++ [loadTrack] Todos os arquivos lidos. Fazendo Swap Atomico (Lock)...");
    
    // 2. Swap Atômico: Substitui as trilhas instantaneamente!
    {
        const juce::SpinLock::ScopedLockType lock(channelsLock);
        playing = false; // Pausa por segurança
        channels = std::move(newChannels);
        currentSamplePosition = 0;
        clickTimeline.reset();
    }

    DBG("C++ [loadTrack] Swap concluido. Retornando SUCESSO para o Dart!");
    return true;
}

void AudioEngine::unloadCurrentTrack()
{
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
    playing = false;
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    currentSamplePosition = 0;
    clickTimeline.reset();
    for (auto& channel : channels)
        if (channel.readerSource != nullptr)
        {
            channel.readerSource->setNextReadPosition(0);
            channel.resampler->flushBuffers();
        }
}

void AudioEngine::seekToSeconds(double seconds)
{
    if (!std::isfinite(seconds) || seconds < 0) return;
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    seconds = channels.empty() ? 0.0 : juce::jmin(seconds, channels.front().readerSource->getTotalLength() / channels.front().fileSampleRate);
    currentSamplePosition = static_cast<int64_t>(seconds * currentSampleRate);
    for (auto& channel : channels)
        if (channel.readerSource != nullptr)
        {
            channel.readerSource->setNextReadPosition(static_cast<juce::int64>(seconds * channel.fileSampleRate));
            channel.resampler->flushBuffers();
        }

    clickTimeline.reset();
}

double AudioEngine::getCurrentPositionSeconds() const
{
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
bool AudioEngine::loadClickSound(int voice, const juce::String& path)
{
    if (voice < 0 || voice > 3) { setLastError(EngineErrorCode::FormatMismatch,"Invalid click voice"); return false; }
    juce::AudioBuffer<float> decoded;
    double rate=44100;
    if (path.isNotEmpty()) {
        juce::AudioFormatManager loader; loader.registerBasicFormats();
        std::unique_ptr<juce::AudioFormatReader> reader(loader.createReaderFor(juce::File(path)));
        if (!reader || reader->lengthInSamples <= 0 || !std::isfinite(reader->sampleRate) || reader->sampleRate < 8000 || reader->sampleRate > 192000
            || reader->lengthInSamples > reader->sampleRate*10) { setLastError(EngineErrorCode::FileUnreadable,"Click sound unavailable or exceeds ten seconds"); return false; }
        rate=reader->sampleRate; decoded.setSize(1,static_cast<int>(reader->lengthInSamples));
        if (!reader->read(&decoded,0,decoded.getNumSamples(),0,true,false)) { setLastError(EngineErrorCode::FileUnreadable,"Click sound decoding failed"); return false; }
    }
    // Decoding and allocation are complete before acquiring the render lock.
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    clickTimeline.sounds[voice]=std::move(decoded); clickTimeline.soundRates[voice]=rate; clickTimeline.starts[voice]=-1;
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
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    currentSampleRate = sampleRate;
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
            channel.resampler->setResamplingRatio(channel.fileSampleRate / sampleRate);
            channel.resampler->prepareToPlay(samplesPerBlockExpected, sampleRate);
        }
}

void AudioEngine::releaseResources()
{
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    mixerSource.releaseResources();

    for (auto& channel : channels)
        if (channel.resampler != nullptr)
            channel.resampler->releaseResources();

    isPrepared = false;
}

void AudioEngine::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();

    if (! playing.load() || bufferToFill.buffer == nullptr)
        return;

    const juce::SpinLock::ScopedLockType lock(channelsLock); 

    if (channels.empty())
         return;

    const int numSamples = bufferToFill.numSamples;

    if (scratchBuffer.getNumSamples() < numSamples)
        scratchBuffer.setSize(2, numSamples, false, false, true);

    for (auto& channel : channels)
    {
        if (channel.readerSource == nullptr)
            continue;

        scratchBuffer.clear(); 

        juce::AudioSourceChannelInfo channelInfo(&scratchBuffer, 0, numSamples);
        channel.resampler->getNextAudioBlock(channelInfo);

        if (channel.muted)
            continue;

        const float gain = channel.volume;
        if (gain <= 0.0f)
            continue;

        for (int destChannel = 0; destChannel < bufferToFill.buffer->getNumChannels(); ++destChannel)
        {
            const int srcChannel = juce::jmin(destChannel, scratchBuffer.getNumChannels() - 1);
            bufferToFill.buffer->addFrom(destChannel, bufferToFill.startSample,
                                          scratchBuffer, srcChannel, 0, numSamples, gain);
        }
    }

    clickTimeline.render(*bufferToFill.buffer, bufferToFill.startSample, numSamples,
                         currentSamplePosition.load(), currentSampleRate, clickEnabled.load());

    const auto& first = channels.front();
    const auto endPosition = static_cast<int64_t>(
        first.readerSource->getTotalLength() / first.fileSampleRate * currentSampleRate);
    if (currentSamplePosition.fetch_add(numSamples) + numSamples >= endPosition)
    {
        currentSamplePosition = endPosition;
        playing = false;
    }
}

} // namespace wtracks