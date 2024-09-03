//DeckGUI.h

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
    DeckGUI(DJAudioPlayer* player,
            juce::AudioFormatManager & formatManagerToUse,
            juce::AudioThumbnailCache & cacheToUse);
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void buttonClicked (juce::Button *) override;
    void sliderValueChanged(juce::Slider *slider) override;
    
    bool isInterestedInFileDrag(const juce::StringArray &files) override;
    void filesDropped (const juce::StringArray &files, int x, int y) override;
    
    void timerCallback() override;
    
    void loadTrack(const juce::String& trackName);
    void loadTrack(const juce::URL& audioURL);

    // New method to set the other deck
    void setOtherDeck(DeckGUI* otherDeck) { this->otherDeck = otherDeck; }

    // Methods to access BPM and position (assuming these are implemented)
    double getPlayerBPM() const { return player->getBPM(); }
    double getPlayerPosition() const { return player->getPositionRelative(); }
    
private:
    juce::TextButton playButton{"PLAY"};
    juce::TextButton stopButton{"STOP"};
    juce::TextButton loadButton{"LOAD"};
    juce::TextButton syncButton{"SYNC"};
    
    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;

    DJAudioPlayer* player;
    WaveformDisplay waveformDisplay;

    juce::FileChooser fChooser {"Please select a file..."};

    // Pointer to the other DeckGUI
    DeckGUI* otherDeck = nullptr; // Initialize to nullptr

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
