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
    if (result.isNotEmpty())
        return false;

    juce::AudioDeviceManager::AudioDeviceSetup setup;
    deviceManager.getAudioDeviceSetup(setup);
    setup.sampleRate = sampleRate;
    setup.bufferSize = bufferSize;
    deviceManager.setAudioDeviceSetup(setup, true);

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
    setLastError(""); // Zera erros antigos

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
            setLastError(err);
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
                setLastError(err);
                return false;
            }
        }

        Channel channel;
        channel.name = file.getFileNameWithoutExtension();
        channel.readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);

        // Mesmo se o sample rate for diferente (ex: 44.1k vs 48k), o resampler 
        // vai ser configurado AGORA, no vetor fantasma, sem travar o áudio que já está tocando!
        if (isPrepared) {
            DBG("C++ [loadTrack] isPrepared=true. Configurando resampling/buffer...");
            channel.readerSource->prepareToPlay(preparedBlockSize, preparedSampleRate);
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
        currentBeatIndex = 0;
        clickReadPosition = -1;
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

void AudioEngine::setLastError(const juce::String& errorMessage)
{
    const juce::SpinLock::ScopedLockType lock(errorLock);
    lastError = errorMessage;
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
    currentSamplePosition = 0;
    currentBeatIndex = 0;      
    clickReadPosition = -1;

    const juce::SpinLock::ScopedLockType lock(channelsLock);
    for (auto& channel : channels)
        if (channel.readerSource != nullptr)
            channel.readerSource->setNextReadPosition(0);
}

void AudioEngine::seekToSeconds(double seconds)
{
    currentSamplePosition = static_cast<int64_t>(seconds * currentSampleRate);

    const juce::SpinLock::ScopedLockType lock(channelsLock);
    for (auto& channel : channels)
        if (channel.readerSource != nullptr)
            channel.readerSource->setNextReadPosition(currentSamplePosition);

    if (samplesPerBeat > 0) {
        const int64_t offsetSamples = clickOffsetSamples.load();
        const int64_t effectivePosition = currentSamplePosition.load() - offsetSamples;
        if (effectivePosition >= 0) {
            int64_t totalBeatsElapsed = effectivePosition / samplesPerBeat;
            currentBeatIndex = static_cast<int>(totalBeatsElapsed % timeSignatureNumerator);
        } else {
            currentBeatIndex = 0; // ainda não chegou no 1º tempo -- estado neutro
        }
    }
    clickReadPosition = -1;
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
    return reader != nullptr ? reader->lengthInSamples / currentSampleRate : 0.0;
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

void AudioEngine::setClickBpm(double bpm)
{
    clickBpm = bpm;
    samplesPerBeat = static_cast<int64_t>((60.0 / bpm) * currentSampleRate);
}

void AudioEngine::setClickTimeSignature(int numerator, int denominator)
{
    if (numerator > 0)
        timeSignatureNumerator = numerator;
}

void AudioEngine::setClickOffsetSeconds(double offsetSeconds)
{
    clickOffsetSecondsValue = offsetSeconds;
    clickOffsetSamples = static_cast<int64_t>(offsetSeconds * currentSampleRate);
}

void AudioEngine::generateClickBuffers(double sampleRate)
{
    const int numSamples = static_cast<int>(sampleRate * 0.03);
    clickBufferAccent.setSize(1, numSamples);
    clickBufferNormal.setSize(1, numSamples);

    const double freqAccent = 1760.0;
    const double freqNormal = 880.0;

    for (int i = 0; i < numSamples; ++i)
    {
        float envelope = 1.0f - (static_cast<float>(i) / numSamples);
        float sampleAccent = static_cast<float>(std::sin(2.0 * juce::MathConstants<double>::pi * freqAccent * i / sampleRate)) * envelope * 0.5f;
        float sampleNormal = static_cast<float>(std::sin(2.0 * juce::MathConstants<double>::pi * freqNormal * i / sampleRate)) * envelope * 0.5f;

        clickBufferAccent.setSample(0, i, sampleAccent);
        clickBufferNormal.setSample(0, i, sampleNormal);
    }
}

void AudioEngine::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    currentSampleRate = sampleRate;
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    clickOffsetSamples = static_cast<int64_t>(clickOffsetSecondsValue * currentSampleRate);

    generateClickBuffers(sampleRate);

    preparedBlockSize = samplesPerBlockExpected;
    preparedSampleRate = sampleRate;
    isPrepared = true;

    scratchBuffer.setSize(2, samplesPerBlockExpected);

    for (auto& channel : channels)
        if (channel.readerSource != nullptr)
            channel.readerSource->prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void AudioEngine::releaseResources()
{
    mixerSource.releaseResources();

    for (auto& channel : channels)
        if (channel.readerSource != nullptr)
            channel.readerSource->releaseResources();

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
        channel.readerSource->getNextAudioBlock(channelInfo);

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

    const int64_t spb = samplesPerBeat.load(); 
    if (clickEnabled && spb > 0)
    {
        auto& outBuffer = *bufferToFill.buffer;
        const int numOutChannels = outBuffer.getNumChannels();

        int64_t localSamplePos = currentSamplePosition.load();
        int localBeatIndex = currentBeatIndex.load();
        int64_t localClickReadPos = clickReadPosition.load();
        const int64_t offsetSamples = clickOffsetSamples.load();

        for (int i = 0; i < numSamples; ++i)
        {
            const int64_t globalSample = localSamplePos + i;
            const int64_t effectiveSample = globalSample - offsetSamples;

            // Antes do offset (música ainda não chegou no 1º tempo real): sem click.
            if (effectiveSample >= 0 && effectiveSample % spb == 0)
            {
                if (effectiveSample == 0)
                    localBeatIndex = 0;
                else
                    localBeatIndex = (localBeatIndex + 1) % timeSignatureNumerator;

                localClickReadPos = 0;
            }

            if (localClickReadPos >= 0)
            {
                auto& activeBuffer = (localBeatIndex == 0) ? clickBufferAccent : clickBufferNormal;
                
                if (localClickReadPos < activeBuffer.getNumSamples())
                {
                    float clickSample = activeBuffer.getSample(0, static_cast<int>(localClickReadPos));
                    
                    for (int ch = 0; ch < numOutChannels; ++ch)
                        outBuffer.addSample(ch, bufferToFill.startSample + i, clickSample);

                    localClickReadPos++;
                }
                else
                {
                    localClickReadPos = -1;
                }
            }
        }

        currentBeatIndex.store(localBeatIndex);
        clickReadPosition.store(localClickReadPos);
    }

    currentSamplePosition.fetch_add(numSamples);
}

} // namespace wtracks