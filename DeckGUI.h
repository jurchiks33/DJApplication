//
//// DeckGUI.h
//
//#pragma once
//
//#include <JuceHeader.h>
//#include "DjAudioPlayer.h"
//#include "WaveformDisplay.h"
//
//class DeckGUI : public juce::Component,
//                public juce::Button::Listener,
//                public juce::Slider::Listener,
//                public juce::FileDragAndDropTarget,
//                public juce::Timer
//{
//public:
//    DeckGUI(DJAudioPlayer* player,
//            juce::AudioFormatManager & formatManagerToUse,
//            juce::AudioThumbnailCache & cacheToUse);
//    ~DeckGUI() override;
//
//    void paint (juce::Graphics&) override;
//    void resized() override;
//    
//    void buttonClicked (juce::Button *) override;
//    void sliderValueChanged(juce::Slider *slider) override;
//    
//    bool isInterestedInFileDrag(const juce::StringArray &files) override;
//    void filesDropped (const juce::StringArray &files, int x, int y) override;
//    
//    void timerCallback() override;
//    
//    void loadTrack(const juce::String& trackName);
//    void loadTrack(const juce::URL& audioURL);
//
//    // Setter for the other DeckGUI instance
//    void setOtherDeck(DeckGUI* otherDeck) { deck2 = otherDeck; }
//
//    // Getter for the player's BPM
//    double getPlayerBPM() const { return player->getBPM(); }
//    // Add a getter for the player's position if needed
//    double getPlayerPosition() const { return player->getPositionRelative(); }
//
//private:
//    juce::TextButton playButton{"PLAY"};
//    juce::TextButton stopButton{"STOP"};
//    juce::TextButton syncButton{"SYNC"};
//    
//    juce::Slider volSlider;
//    juce::Slider speedSlider;
//    juce::Slider posSlider;
//
//    DJAudioPlayer* player;
//    
//    WaveformDisplay waveformDisplay;
//    
//    DeckGUI* deck2 = nullptr; // Pointer to the other deck instance
//
//    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
//};
//

// DeckGUI.h

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

    // Setter for the other DeckGUI instance
    void setOtherDeck(DeckGUI* otherDeck) { deck2 = otherDeck; }

    // Getter for the player's BPM
    double getPlayerBPM() const { return player->getBPM(); }

    // Add a getter for the player's position if needed
    double getPlayerPosition() const { return player->getPositionRelative(); }

    // Start and stop methods to control playback from PlaylistComponent
    void start() { player->start(); }
    void stop() { player->stop(); }

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
    
    DeckGUI* deck2 = nullptr; // Pointer to the other deck instance

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};


