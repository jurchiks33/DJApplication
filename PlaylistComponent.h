//
////    PlaylistComponent.h
//
//#pragma once
//
//#include <JuceHeader.h>
//#include <vector>
//#include <string>
//
//class DeckGUI; // Forward declaration to use DeckGUI pointers
//
//class PlaylistComponent : public juce::Component,
//                          public juce::TableListBoxModel,
//                          public juce::Button::Listener
//{
//public:
//    PlaylistComponent(DeckGUI* deck1, DeckGUI* deck2); // Constructor with DeckGUI pointers
//    ~PlaylistComponent() override;
//
//    void paint(juce::Graphics&) override;
//    void resized() override;
//
//    int getNumRows() override;
//
//    void paintRowBackground(juce::Graphics&,
//                            int rowNumber,
//                            int width,
//                            int height,
//                            bool rowIsSelected) override;
//
//    void paintCell(juce::Graphics&,
//                   int rowNumber,
//                   int columnId,
//                   int width,
//                   int height,
//                   bool rowIsSelected) override;
//
//    juce::Component* refreshComponentForCell(int rowNumber,
//                                             int columnId,
//                                             bool isRowSelected,
//                                             juce::Component* existingComponentToUpdate) override;
//
//    void buttonClicked(juce::Button* button) override;
//
//    void loadPlaylist(); // Method to load playlist
//
//private:
//    juce::TableListBox tableComponent;
//    std::vector<std::string> trackTitles;
//    std::vector<juce::URL> trackUrls;
//
//    std::unique_ptr<juce::TextButton> loadPlaylistButton;
//    std::unique_ptr<juce::FileChooser> chooser; // Declare FileChooser as a member variable
//
//    DeckGUI* deck1;
//    DeckGUI* deck2;
//
//    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
//};

// PlaylistComponent.h

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>

class DeckGUI;
class DJAudioPlayer;
#include "EqualizerComponent.h"

class PlaylistComponent : public juce::Component,
                          public juce::TableListBoxModel,
                          public juce::Button::Listener
{
public:
    PlaylistComponent(DeckGUI* deck1, DeckGUI* deck2, juce::AudioFormatManager& formatManager);
    ~PlaylistComponent() override;
    
    DJAudioPlayer* getPreviewPlayer() { return previewPlayer.get(); }
    bool hasPreviewPlayer() { return previewPlayer != nullptr; }

    void paint(juce::Graphics&) override;
    void resized() override;

    int getNumRows() override;

    void paintRowBackground(juce::Graphics&,
                            int rowNumber,
                            int width,
                            int height,
                            bool rowIsSelected) override;

    void paintCell(juce::Graphics&,
                   int rowNumber,
                   int columnId,
                   int width,
                   int height,
                   bool rowIsSelected) override;

    juce::Component* refreshComponentForCell(int rowNumber,
                                             int columnId,
                                             bool isRowSelected,
                                             juce::Component* existingComponentToUpdate) override;

    void buttonClicked(juce::Button* button) override;

    void loadPlaylist();

private:
    juce::TableListBox tableComponent;
    std::vector<std::string> trackTitles;
    std::vector<juce::URL> trackUrls;

    std::unique_ptr<juce::TextButton> loadPlaylistButton;
    std::unique_ptr<juce::FileChooser> chooser;

    DeckGUI* deck1;
    DeckGUI* deck2;

    std::unique_ptr<DJAudioPlayer> previewPlayer;
    bool isPlayingPreview = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
};

