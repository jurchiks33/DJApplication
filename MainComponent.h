//
//
////MainComponent.h
//
//#pragma once
//
//#include <JuceHeader.h>
//#include "DjAudioPlayer.h"
//#include "DeckGUI.h"
//#include "PlaylistComponent.h"
//#include "EqualizerComponent.h"
//
//class MainComponent : public juce::AudioAppComponent
//{
//public:
//    MainComponent();
//    ~MainComponent() override;
//
//    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
//    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
//    void releaseResources() override;
//
//    void paint(juce::Graphics& g) override;
//    void resized() override;
//
//private:
//    juce::AudioFormatManager formatManager;
//    juce::AudioThumbnailCache thumbCache{100};
//
//    DJAudioPlayer player1{formatManager, equalizerComponent1};
//    DJAudioPlayer player2{formatManager, equalizerComponent2};
//
//    EqualizerComponent equalizerComponent1{player1}; // Equalizer for Deck 1
//    EqualizerComponent equalizerComponent2{player2}; // Equalizer for Deck 2
//
//    DeckGUI deckGUI1{&player1, formatManager, thumbCache};
//    DeckGUI deckGUI2{&player2, formatManager, thumbCache};
//
//    juce::MixerAudioSource mixerSource;
//    PlaylistComponent playlistComponent{&deckGUI1, &deckGUI2};
//
//    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
//};

// MainComponent.h

#pragma once

#include <JuceHeader.h>
#include "DjAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"
#include "EqualizerComponent.h"

class MainComponent : public juce::AudioAppComponent
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::AudioFormatManager formatManager;
    juce::AudioThumbnailCache thumbCache{100};

    DJAudioPlayer player1{formatManager, equalizerComponent1};
    DJAudioPlayer player2{formatManager, equalizerComponent2};

    EqualizerComponent equalizerComponent1{player1}; // Equalizer for Deck 1
    EqualizerComponent equalizerComponent2{player2}; // Equalizer for Deck 2

    DeckGUI deckGUI1{&player1, formatManager, thumbCache};
    DeckGUI deckGUI2{&player2, formatManager, thumbCache};

    juce::MixerAudioSource mixerSource;
    PlaylistComponent playlistComponent{&deckGUI1, &deckGUI2, formatManager}; // Correct constructor

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};

