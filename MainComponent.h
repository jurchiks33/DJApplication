//MainComponent.h
#pragma once

#include <JuceHeader.h>
#include "DjAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"
#include "EqualizerComponent.h"

class MainComponent  : public juce::AudioAppComponent
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    juce::AudioFormatManager formatManager;
    juce::AudioThumbnailCache thumbCache{100};

    EqualizerComponent equalizerComponent;  // Ensure this is declared before DJAudioPlayer

    DJAudioPlayer player1{formatManager, equalizerComponent};  // Correct constructor usage
    DJAudioPlayer player2{formatManager, equalizerComponent};  // Correct constructor usage

    DeckGUI deckGUI1{&player1, formatManager, thumbCache};
    DeckGUI deckGUI2{&player2, formatManager, thumbCache};

    juce::MixerAudioSource mixerSource;

    PlaylistComponent playlistComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
