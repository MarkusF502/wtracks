#include "MainComponent.h"

MainComponent::MainComponent()
{
    // No Android 13+ (API 33+), READ_MEDIA_AUDIO e uma permissao "perigosa"
    // que precisa ser solicitada em tempo de execucao -- declarar no
    // AndroidManifest.xml sozinho nao e suficiente. Sem essa solicitacao
    // explicita, o sistema nega silenciosamente a abertura de streams de
    // conteudo de midia, mesmo que o FileChooser em si abra normalmente
    // (foi exatamente o erro "falha ao abrir stream" reportado).
    if (! juce::RuntimePermissions::isGranted(juce::RuntimePermissions::readExternalStorage))
    {
        juce::RuntimePermissions::request(juce::RuntimePermissions::readExternalStorage,
            [](bool granted)
            {
                if (! granted)
                {
                    juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon,
                        "Permissao necessaria",
                        "O WTracks precisa de acesso a arquivos de audio para funcionar. "
                        "Va em Configuracoes > Apps > WTracks Test > Permissoes e habilite "
                        "o acesso a musica/audio manualmente.");
                }
            });
    }

    // Inicializa o motor com valores tipicos -- em Android real, teste tambem
    // com bufferSize menor (ex: 128, 64) para achar o limite de latencia
    // aceitavel de cada aparelho.
    if (! engine.initialise(44100, 256))
    {
        juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon,
            "Erro", "Falha ao inicializar o dispositivo de audio.");
    }

    addAndMakeVisible(loadButton);
    loadButton.onClick = [this]
    {
        if (! juce::RuntimePermissions::isGranted(juce::RuntimePermissions::readExternalStorage))
        {
            juce::RuntimePermissions::request(juce::RuntimePermissions::readExternalStorage,
                [this](bool granted)
                {
                    if (granted)
                        loadButton.triggerClick(); // tenta de novo apos conceder
                });
            return;
        }

        // Selecionar arquivos individuais (em vez de uma pasta inteira) evita
        // depender de enumeracao de diretorio via content:// URI no Android
        // (Scoped Storage) -- cada arquivo escolhido no seletor do sistema
        // ja vem com uma URI resolvida corretamente, sem essa fragilidade.
        fileChooser = std::make_unique<juce::FileChooser>(
            "Selecione os arquivos .wav dos canais (segure para selecionar varios)",
            juce::File::getSpecialLocation(juce::File::userMusicDirectory),
            "*.wav");

        fileChooser->launchAsync(
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectMultipleItems,
            [this](const juce::FileChooser& fc)
            {
                auto urls = fc.getURLResults();
                if (! urls.isEmpty())
                    loadTrackFromFiles(urls);
            });
    };

    addAndMakeVisible(playButton);
    playButton.onClick = [this] { engine.play(); };

    addAndMakeVisible(pauseButton);
    pauseButton.onClick = [this] { engine.pause(); };

    addAndMakeVisible(stopButton);
    stopButton.onClick = [this] { engine.stop(); };

    addAndMakeVisible(seekSlider);
    seekSlider.setRange(0.0, 1.0);
    seekSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    seekSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    // onDragEnded evita chamar seek() a cada pixel arrastado -- so no soltar
    seekSlider.onDragEnd = [this]
    {
        auto totalLength = engine.getTotalLengthSeconds();
        engine.seekToSeconds(seekSlider.getValue() * totalLength);
    };

    addAndMakeVisible(positionLabel);
    positionLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(clickToggle);
    clickToggle.onClick = [this] { engine.setClickEnabled(clickToggle.getToggleState()); };

    addAndMakeVisible(bpmLabel);

    addAndMakeVisible(bpmSlider);
    bpmSlider.setRange(40.0, 220.0, 1.0);
    bpmSlider.setValue(120.0);
    bpmSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    bpmSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 60, 20);
    bpmSlider.onValueChange = [this] { engine.setClickBpm(bpmSlider.getValue()); };
    engine.setClickBpm(120.0); // sincroniza o estado inicial do engine com o slider

    setSize(600, 500);
    startTimerHz(10); // 100ms, mesma cadencia que o Flutter usara via polling FFI
}

MainComponent::~MainComponent()
{
    stopTimer();
    engine.shutdown();
}

void MainComponent::loadTrackFromFiles(const juce::Array<juce::URL>& wavFileUrls)
{
    if (wavFileUrls.isEmpty())
    {
        juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon,
            "Aviso", "Nenhum arquivo .wav foi selecionado.");
        return;
    }

    engine.stop();

    // No Android, os resultados do FileChooser sao content:// URIs, nao
    // caminhos de arquivo reais -- por isso usamos juce::URL::createInputStream()
    // (que sabe abrir esse tipo de URI corretamente via ContentResolver por
    // baixo dos panos) em vez de tentar tratar como juce::File diretamente.
    // Copiamos o conteudo para a pasta de cache privada do app, e so entao
    // trabalhamos com arquivos locais de verdade a partir dali.
    auto cacheDir = juce::File::getSpecialLocation(juce::File::tempDirectory)
                        .getChildFile("wtracks_import");
    cacheDir.createDirectory();

    std::vector<juce::File> channelFiles;

    for (auto& url : wavFileUrls)
    {
        auto fileName = url.getFileName();
        if (fileName.isEmpty())
            fileName = "canal_" + juce::String(channelFiles.size()) + ".wav";

        auto localCopy = cacheDir.getChildFile(fileName);

        auto inputStream = url.createInputStream(juce::URL::InputStreamOptions(
            juce::URL::ParameterHandling::inAddress));

        if (inputStream == nullptr)
        {
            DBG("FALHA ao abrir stream de leitura para: " + url.toString(false));
            juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon,
                "Erro", "Falha ao abrir o arquivo: " + fileName
                        + "\nVerifique se a permissao de acesso a midia foi concedida.");
            return;
        }

        localCopy.deleteFile();
        auto outputStream = localCopy.createOutputStream();
        if (outputStream == nullptr)
        {
            DBG("FALHA ao criar arquivo local de destino: " + localCopy.getFullPathName());
            return;
        }

        outputStream->writeFromInputStream(*inputStream, -1); // -1 = copiar tudo
        outputStream.reset(); // garante flush/fechamento antes de ler de volta

        DBG("Copiado para cache local: " + localCopy.getFullPathName()
            + " | tamanho: " + juce::String(localCopy.getSize()) + " bytes");

        if (localCopy.getSize() == 0)
        {
            juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon,
                "Erro", "Copia resultou em arquivo vazio: " + fileName);
            return;
        }

        channelFiles.push_back(localCopy);
    }

    if (! engine.loadTrack("teste_manual", channelFiles))
    {
        juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon,
            "Erro", "Falha ao carregar um ou mais canais -- verifique se todos "
                    "tem o mesmo sample rate e duracao compativel.");
        return;
    }

    rebuildChannelControls();
}

void MainComponent::rebuildChannelControls()
{
    channelVolumeSliders.clear();
    channelMuteButtons.clear();
    channelLabels.clear();

    const int count = engine.getChannelCount();
    for (int i = 0; i < count; ++i)
    {
        auto* label = channelLabels.add(new juce::Label({}, "Canal " + juce::String(i)));
        addAndMakeVisible(label);

        auto* slider = channelVolumeSliders.add(new juce::Slider());
        slider->setRange(0.0, 1.0);
        slider->setValue(1.0);
        slider->setSliderStyle(juce::Slider::LinearHorizontal);
        slider->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        slider->onValueChange = [this, i, slider]
        {
            engine.setChannelVolume(i, static_cast<float>(slider->getValue()));
        };
        addAndMakeVisible(slider);

        auto* muteButton = channelMuteButtons.add(new juce::ToggleButton("Mute"));
        muteButton->onClick = [this, i, muteButton]
        {
            engine.setChannelMuted(i, muteButton->getToggleState());
        };
        addAndMakeVisible(muteButton);
    }

    resized();
}

void MainComponent::timerCallback()
{
    // Este e o mesmo padrao de polling que o Flutter vai usar via FFI, ja que
    // nao ha callback nativo->Dart simples sem NativeCallable. Serve tambem
    // para validar aqui que getCurrentPositionSeconds() e thread-safe o
    // suficiente para ser chamado a essa cadencia sem travar a UI.
    auto position = engine.getCurrentPositionSeconds();
    auto length = engine.getTotalLengthSeconds();

    positionLabel.setText(
        juce::String(position, 1) + " s / " + juce::String(length, 1) + " s"
        + (engine.isPlaying() ? "  [tocando]" : "  [parado]"),
        juce::dontSendNotification);

    if (length > 0.0 && ! seekSlider.isMouseButtonDown())
        seekSlider.setValue(position / length, juce::dontSendNotification);
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds().withTrimmedTop(50).reduced(20);

    loadButton.setBounds(bounds.removeFromTop(30));
    bounds.removeFromTop(10);

    auto transportRow = bounds.removeFromTop(30);
    playButton.setBounds(transportRow.removeFromLeft(80));
    transportRow.removeFromLeft(5);
    pauseButton.setBounds(transportRow.removeFromLeft(80));
    transportRow.removeFromLeft(5);
    stopButton.setBounds(transportRow.removeFromLeft(80));

    bounds.removeFromTop(10);
    seekSlider.setBounds(bounds.removeFromTop(24));
    positionLabel.setBounds(bounds.removeFromTop(20));

    bounds.removeFromTop(10);
    auto clickRow = bounds.removeFromTop(24);
    clickToggle.setBounds(clickRow.removeFromLeft(160));
    bpmLabel.setBounds(clickRow.removeFromLeft(40));
    bpmSlider.setBounds(clickRow);

    bounds.removeFromTop(15);

    // Canais dinamicos: uma linha [label][slider][mute] por canal
    for (int i = 0; i < channelVolumeSliders.size(); ++i)
    {
        auto row = bounds.removeFromTop(28);
        channelLabels[i]->setBounds(row.removeFromLeft(70));
        row.removeFromLeft(5);
        channelMuteButtons[i]->setBounds(row.removeFromRight(60));
        row.removeFromRight(5);
        channelVolumeSliders[i]->setBounds(row);
        bounds.removeFromTop(4);
    }
}