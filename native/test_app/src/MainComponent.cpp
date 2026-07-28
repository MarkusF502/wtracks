#include "MainComponent.h"

MainComponent::MainComponent()
{
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
        fileChooser = std::make_unique<juce::FileChooser>(
            "Selecione a pasta com os arquivos de canal (WAV)",
            juce::File::getSpecialLocation(juce::File::userMusicDirectory));

        fileChooser->launchAsync(juce::FileBrowserComponent::canSelectDirectories,
            [this](const juce::FileChooser& fc)
            {
                auto folder = fc.getResult();
                if (folder != juce::File())
                    loadTrackFromFolder(folder);
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

void MainComponent::loadTrackFromFolder(const juce::File& folder)
{
    engine.stop();

    juce::Array<juce::File> wavFiles;
    folder.findChildFiles(wavFiles, juce::File::findFiles, false, "*.wav");

    if (wavFiles.isEmpty())
    {
        juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon,
            "Aviso", "Nenhum arquivo .wav encontrado nessa pasta.");
        return;
    }

    std::vector<juce::File> channelFiles;
    for (auto& f : wavFiles)
        channelFiles.push_back(f);

    if (! engine.loadTrack(folder.getFileName(), channelFiles))
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
    auto area = getLocalBounds().reduced(10);

    loadButton.setBounds(area.removeFromTop(30));
    area.removeFromTop(10);

    auto transportRow = area.removeFromTop(30);
    playButton.setBounds(transportRow.removeFromLeft(80));
    transportRow.removeFromLeft(5);
    pauseButton.setBounds(transportRow.removeFromLeft(80));
    transportRow.removeFromLeft(5);
    stopButton.setBounds(transportRow.removeFromLeft(80));

    area.removeFromTop(10);
    seekSlider.setBounds(area.removeFromTop(24));
    positionLabel.setBounds(area.removeFromTop(20));

    area.removeFromTop(10);
    auto clickRow = area.removeFromTop(24);
    clickToggle.setBounds(clickRow.removeFromLeft(160));
    bpmLabel.setBounds(clickRow.removeFromLeft(40));
    bpmSlider.setBounds(clickRow);

    area.removeFromTop(15);

    // Canais dinamicos: uma linha [label][slider][mute] por canal
    for (int i = 0; i < channelVolumeSliders.size(); ++i)
    {
        auto row = area.removeFromTop(28);
        channelLabels[i]->setBounds(row.removeFromLeft(70));
        row.removeFromLeft(5);
        channelMuteButtons[i]->setBounds(row.removeFromRight(60));
        row.removeFromRight(5);
        channelVolumeSliders[i]->setBounds(row);
        area.removeFromTop(4);
    }
}