#include "../include/AudioEngine.h"

namespace wtracks
{

AudioEngine::AudioEngine()
{
    formatManager.registerBasicFormats(); // habilita leitura de WAV, AIFF, etc.
}

AudioEngine::~AudioEngine()
{
    shutdown();
}

bool AudioEngine::initialise(int sampleRate, int bufferSize)
{
    currentSampleRate = sampleRate;

    // Abre o dispositivo de audio padrao da plataforma. No Android isso passa
    // por Oboe/AAudio via JUCE; no Windows por WASAPI -- ambos escondidos
    // atras do AudioDeviceManager, entao nao precisamos tratar por plataforma.
    auto result = deviceManager.initialiseWithDefaultDevices(0, 2);
    if (result.isNotEmpty())
        return false;

    // Tenta aplicar o sample rate e buffer size pedidos. Se o dispositivo nao
    // suportar exatamente esses valores, o JUCE ajusta para o mais proximo
    // suportado -- prepareToPlay() sera chamado com o valor real logo em seguida.
    juce::AudioDeviceManager::AudioDeviceSetup setup;
    deviceManager.getAudioDeviceSetup(setup);
    setup.sampleRate = sampleRate;
    setup.bufferSize = bufferSize;
    deviceManager.setAudioDeviceSetup(setup, true);

    // AudioSourcePlayer e o adaptador entre o callback de audio do dispositivo
    // e este AudioEngine (que e um juce::AudioSource). Sem isso, o dispositivo
    // fica aberto mas nenhum audio e efetivamente processado.
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
    unloadCurrentTrack();

    double referenceSampleRate = 0.0;
    juce::int64 referenceLengthSamples = 0;

    for (const auto& file : channelFiles)
    {
        auto* reader = formatManager.createReaderFor(file);
        if (reader == nullptr)
        {
            DBG("Falha ao criar reader para: " + file.getFileName());
            unloadCurrentTrack();
            return false; // TODO: reportar erro de forma mais explicita para a UI
        }

        DBG("Canal: " + file.getFileName()
            + " | sampleRate: " + juce::String(reader->sampleRate)
            + " | lengthInSamples: " + juce::String(reader->lengthInSamples)
            + " | bitsPerSample: " + juce::String(reader->bitsPerSample)
            + " | numChannels: " + juce::String(reader->numChannels));

        // Valida que todos os canais tem o mesmo sample rate e um comprimento
        // compativel (tolerancia de 50ms) antes de aceitar a musica como
        // "pronta para tocar" -- isso evita dessincronia sutil entre trilhas.
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
                delete reader; // ainda nao foi adotado por nenhum readerSource
                unloadCurrentTrack();
                return false; // TODO: reportar erro de forma mais explicita para a UI
            }
        }

        Channel channel;
        channel.name = file.getFileNameWithoutExtension();
        channel.readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);

        // Se o motor ja estiver rodando (prepareToPlay ja foi chamado), prepara
        // este canal imediatamente para que ele possa entrar tocando sem glitch.
        if (isPrepared)
            channel.readerSource->prepareToPlay(preparedBlockSize, preparedSampleRate);

        { // <-- CRIAR UM BLOCO SÓ PARA O LOCK
            const juce::SpinLock::ScopedLockType lock(channelsLock);
            channels.push_back(std::move(channel));
        }
    }

    return true;
}

void AudioEngine::unloadCurrentTrack()
{
    stop();
    const juce::SpinLock::ScopedLockType lock(channelsLock);
    channels.clear();
}

void AudioEngine::play()
{
    // O callback de audio (via AudioSourcePlayer, ligado em initialise()) ja
    // esta rodando continuamente -- play() so precisa liberar getNextAudioBlock
    // para de fato produzir som a partir da posicao atual.
    {
        const juce::SpinLock::ScopedLockType lock(channelsLock);
        if (channels.empty())
            return;
    }

    playing = true;
}

void AudioEngine::pause()
{
    // Apenas interrompe a producao de audio; currentSamplePosition e a posicao
    // de leitura de cada readerSource nao sao alteradas, entao um play()
    // seguinte retoma exatamente de onde parou.
    playing = false;
}

void AudioEngine::stop()
{
    playing = false;
    currentSamplePosition = 0;
    currentBeatIndex = 0;      // Zera o compasso
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

    // RECALCULA O COMPASSO DO CLICK
    if (samplesPerBeat > 0) {
        int64_t totalBeatsElapsed = currentSamplePosition / samplesPerBeat;
        currentBeatIndex = static_cast<int>(totalBeatsElapsed % timeSignatureNumerator);
    }
    clickReadPosition = -1; // Cala o bipe no meio do seek
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
    // O denominador (ex: 4 em 4/4) já é coberto matematicamente pelo BPM.
    // O numerador dita a cada quantas batidas o acento (Tempo 1) se repete.
    if (numerator > 0)
        timeSignatureNumerator = numerator;
}

void AudioEngine::generateClickBuffers(double sampleRate)
{
    // Cria um bipe curto de 30 milissegundos
    const int numSamples = static_cast<int>(sampleRate * 0.03);
    clickBufferAccent.setSize(1, numSamples);
    clickBufferNormal.setSize(1, numSamples);

    // Frequências: A6 (1760Hz) para acento e A5 (880Hz) para normal
    const double freqAccent = 1760.0;
    const double freqNormal = 880.0;

    for (int i = 0; i < numSamples; ++i)
    {
        // Envelope linear simples: começa em 1.0 e cai até 0.0 (evita estalos/pops)
        float envelope = 1.0f - (static_cast<float>(i) / numSamples);

        // Gera a onda senoidal pura e aplica o envelope e um volume mestre (0.5f)
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

    generateClickBuffers(sampleRate);

    preparedBlockSize = samplesPerBlockExpected;
    preparedSampleRate = sampleRate;
    isPrepared = true;

    // Estereo e suficiente por enquanto -- getNextAudioBlock faz downmix/
    // duplicacao de canais mono na hora de somar no buffer de saida.
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

    // Uma verificação rápida ANTES do lock para não gastar CPU se não precisar
    if (! playing.load() || bufferToFill.buffer == nullptr)
        return;

    // TRAVA A THREAD DE ÁUDIO APENAS DURANTE O PROCESSAMENTO
    const juce::SpinLock::ScopedLockType lock(channelsLock); // <-- TRAVAR AQUI

    if (channels.empty())
         return;

    const int numSamples = bufferToFill.numSamples;

    if (scratchBuffer.getNumSamples() < numSamples)
        scratchBuffer.setSize(2, numSamples, false, false, true);

    // 1 + 2 + 3: le cada canal por vez em scratchBuffer e soma (com volume
    // aplicado) diretamente no buffer de saida. Todos os canais avancam a
    // mesma quantidade de samples neste bloco, entao permanecem sample-accurate
    // entre si mesmo sem um clock central explicito.
    for (auto& channel : channels)
    {
        if (channel.readerSource == nullptr)
            continue;

        // IMPORTANTE: getNextAudioBlock() do readerSource precisa ser chamado
        // SEMPRE, mesmo quando o canal esta mutado ou com volume 0. E essa
        // chamada quem avanca a posicao de leitura do canal -- se pularmos
        // aqui, o canal mutado "congela" no tempo em vez de continuar
        // avancando junto com os demais, e ao desmutar ele retoma de onde
        // parou, dessincronizado do resto (foi exatamente o bug reportado).
        scratchBuffer.clear(); // evita vazamento de dados do canal anterior (ex: fontes mono)

        juce::AudioSourceChannelInfo channelInfo(&scratchBuffer, 0, numSamples);
        channel.readerSource->getNextAudioBlock(channelInfo);

        // Mute/volume decidem apenas se o resultado entra no mix de saida --
        // nunca se a leitura acontece.
        if (channel.muted)
            continue;

        const float gain = channel.volume;
        if (gain <= 0.0f)
            continue;

        // TODO: quando o roteamento por outputBus (P.A./monitor/fone) for
        // implementado, este e o ponto de somar em buffers separados por
        // saida fisica em vez de sempre no mesmo par estereo de saida.
        for (int destChannel = 0; destChannel < bufferToFill.buffer->getNumChannels(); ++destChannel)
        {
            const int srcChannel = juce::jmin(destChannel, scratchBuffer.getNumChannels() - 1);
            bufferToFill.buffer->addFrom(destChannel, bufferToFill.startSample,
                                          scratchBuffer, srcChannel, 0, numSamples, gain);
        }
    }

    // INJEÇÃO DO CLICK TRACK SINTETIZADO
    const int64_t spb = samplesPerBeat.load(); // Leitura segura fora do loop
    if (clickEnabled && spb > 0)
    {
        auto& outBuffer = *bufferToFill.buffer;
        const int numOutChannels = outBuffer.getNumChannels();

        // 1. Faz o cache local dos atomics para evitar overhead de CPU no loop
        int64_t localSamplePos = currentSamplePosition.load();
        int localBeatIndex = currentBeatIndex.load();
        int64_t localClickReadPos = clickReadPosition.load();

        for (int i = 0; i < numSamples; ++i)
        {
            const int64_t globalSample = localSamplePos + i;

            // Caiu exatamente em cima da cabeça de um tempo?
            if (globalSample % spb == 0)
            {
                if (globalSample == 0) 
                    localBeatIndex = 0;
                else 
                    localBeatIndex = (localBeatIndex + 1) % timeSignatureNumerator;

                localClickReadPos = 0; // Armar gatilho do bipe!
            }

            // Se o bipe está tocando, injeta o som
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

        // 2. Salva os resultados de volta nos atomics para as outras threads verem
        currentBeatIndex.store(localBeatIndex);
        clickReadPosition.store(localClickReadPos);
    }

    // Avança a posição global de forma atômica e segura (fetch_add é nativo do std::atomic)
    currentSamplePosition.fetch_add(numSamples);
}

} // namespace wtracks