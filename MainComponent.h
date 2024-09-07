/*
==============================================================================
//MainComponent.h
==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DjAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"
#include "EqualizerComponent.h"

// class managing overall audio processing
class MainComponent : public juce::AudioAppComponent
{
public:
    // constructor to initialize components and setup audio format manager and thumbnail
    MainComponent();
    
    // deconstructor to release resources
    ~MainComponent() override;

    // prepares audio playback
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    
    // fills audio buffer with next audio block
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    
    // release any resources that were allocated for audio processing
    void releaseResources() override;

    // paints component
    void paint(juce::Graphics& g) override;
    
    // resizes and arranges child component
    void resized() override;

private:
    // manages audio formats that can be used by application
    juce::AudioFormatManager formatManager;
    
    // cache for storing audio thumbnails for optimization
    juce::AudioThumbnailCache thumbCache{100};

    // djaudio player objects for handling audio playback
    DJAudioPlayer player1{formatManager, equalizerComponent1};
    DJAudioPlayer player2{formatManager, equalizerComponent2};

    // equalizer componennts for applying EQ settings to each player output
    EqualizerComponent equalizerComponent1{player1}; // Equalizer for Deck 1
    EqualizerComponent equalizerComponent2{player2}; // Equalizer for Deck 2

    // deckgui components to provide user interface and controll of decks
    DeckGUI deckGUI1{&player1, formatManager, thumbCache};
    DeckGUI deckGUI2{&player2, formatManager, thumbCache};

    // mixer for combination of audio sources from both djaudioplayer instances
    juce::MixerAudioSource mixerSource;
    
    // playlist component to handle and display management of audio tracks
    PlaylistComponent playlistComponent{&deckGUI1, &deckGUI2};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
