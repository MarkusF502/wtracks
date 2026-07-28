#pragma once

#include "AudioEngine.h"
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

// UI minima e feia de proposito -- este app existe so para validar o
// AudioEngine em hardware real (latencia, sincronizacao, drift do click),
// nao para ser bonito. Nao invista tempo em estetica aqui.
class MainComponent : public juce::Component,
                      private juce::Timer
{
public:
    MainComponent();
    ~MainComponent() override;

    void resized() override;

private:
    wtracks::AudioEngine engine;

    // Transporte
    juce::TextButton loadButton { "Carregar musica (escolher pasta com canais)" };
    juce::TextButton playButton { "Play" };
    juce::TextButton pauseButton { "Pause" };
    juce::TextButton stopButton { "Stop" };
    juce::Slider seekSlider;
    juce::Label positionLabel;

    // Click
    juce::ToggleButton clickToggle { "Click habilitado" };
    juce::Slider bpmSlider;
    juce::Label bpmLabel { {}, "BPM" };

    // Canais (criados dinamicamente apos carregar a musica)
    juce::OwnedArray<juce::Slider> channelVolumeSliders;
    juce::OwnedArray<juce::ToggleButton> channelMuteButtons;
    juce::OwnedArray<juce::Label> channelLabels;

    std::unique_ptr<juce::FileChooser> fileChooser;

    void loadTrackFromFolder(const juce::File& folder);
    void rebuildChannelControls();
    void timerCallback() override; // atualiza posicao/seek a cada 100ms, como fara o Flutter via polling

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};