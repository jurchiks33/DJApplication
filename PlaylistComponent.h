///*
//  ==============================================================================
//
//    PlaylistComponent.h
//
//  ==============================================================================
//*/
//#pragma once
//
//#include <JuceHeader.h>
//#include <vector>
//#include <string>
//
////==============================================================================
///*
//*/
//class PlaylistComponent  : public juce::Component,
//                           public juce::TableListBoxModel,
//                           public juce::Button::Listener
//{
//public:
//    PlaylistComponent();
//    ~PlaylistComponent() override;
//
//    void paint (juce::Graphics&) override;
//    void resized() override;
//    
//    int getNumRows () override;
//    
//    void paintRowBackground (juce::Graphics &,
//                             int rowNumber,
//                             int width,
//                             int height,
//                             bool rowIsSelected) override;
//    
//    void paintCell (juce::Graphics &,
//                    int rowNumber,
//                    int columnId,
//                    int width,
//                    int height,
//                    bool rowIsSelected) override;
//
//    Component* refreshComponentForCell (int rowNumber,
//                                        int columnId,
//                                        bool isRowSelected,
//                                        Component *existingComponentToUpdate) override;
//    
//    void buttonClicked(juce::Button* button) override;
//    
//private:
//    juce::TableListBox tableComponent;
//    std::vector<std::string> trackTitles;
//    
//    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
//};

//---------------------------------------------------

//    PlaylistComponent.h

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>

class DeckGUI; // Forward declaration to use DeckGUI pointers

class PlaylistComponent : public juce::Component,
                          public juce::TableListBoxModel,
                          public juce::Button::Listener
{
public:
    PlaylistComponent(DeckGUI* deck1, DeckGUI* deck2); // Constructor with DeckGUI pointers
    ~PlaylistComponent() override;

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

    void loadPlaylist(); // Method to load playlist

private:
    juce::TableListBox tableComponent;
    std::vector<std::string> trackTitles; // To store track titles
    std::vector<juce::URL> trackUrls; // To store track URLs

    std::unique_ptr<juce::TextButton> loadPlaylistButton; // Unique pointer for the Load Playlist button

    DeckGUI* deck1; // Pointers to DeckGUIs
    DeckGUI* deck2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
};
