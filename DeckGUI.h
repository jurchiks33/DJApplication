/*
=====================================================================================
// DeckGUI.h
=====================================================================================
*/
#pragma once

#include <JuceHeader.h>
#include "DjAudioPlayer.h"
#include "WaveformDisplay.h"

class DeckGUI : public juce::Component,
                public juce::Button::Listener,
                public juce::Slider::Listener,
                public juce::FileDragAndDropTarget,
                public juce::Timer
{
public:
    // constructor to initialize DeckGUI with DjAudioPlayer, AudioFormatManager, and AudioThumbnailCache
    DeckGUI(DJAudioPlayer* player,
            juce::AudioFormatManager & formatManagerToUse,
            juce::AudioThumbnailCache & cacheToUse);
    
    // destructor to clean up resources used by DeckGUI
    ~DeckGUI() override;

    // override paint method
    void paint (juce::Graphics&) override;
    
    // override resized method
    void resized() override;
    
    // override buttonslicked method
    void buttonClicked (juce::Button *) override;
    
    // override slidervalue change method
    void sliderValueChanged(juce::Slider *slider) override;
    
    // override isInterestedInFileDrag method
    bool isInterestedInFileDrag(const juce::StringArray &files) override;
    
    // override filesDropped method
    void filesDropped (const juce::StringArray &files, int x, int y) override;
    
    // override timerCallback
    void timerCallback() override;
    
    // loads tracks using the file path
    void loadTrack(const juce::String& trackName);
    
    // loads a track using URL
    void loadTrack(const juce::URL& audioURL);

    // Setts the other DeckGUI instance for syncranisation
    void setOtherDeck(DeckGUI* otherDeck) { deck2 = otherDeck; }

    // Gets the player's BPM
    double getPlayerBPM() const { return player->getBPM(); }
    
    // Gets the player's position
    double getPlayerPosition() const { return player->getPositionRelative(); }

private:
    // buttons to control playback
    juce::TextButton playButton{"PLAY"};
    juce::TextButton stopButton{"STOP"};
    juce::TextButton syncButton{"SYNC"};
    
    juce::Slider volSlider;  // Volume slider
    juce::Slider posSlider;  // Position slider

    // pointer for DjAudioPlayer instance
    DJAudioPlayer* player;
    
    // displays waveform of the loaded track
    WaveformDisplay waveformDisplay;
    
    // Pointer to the other deck instance
    DeckGUI* deck2 = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};

