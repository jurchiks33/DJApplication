/*
 ==============================================================================
     PlaylistComponent.h
 ==============================================================================
*/
#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>


class DeckGUI;

// class definitions
class PlaylistComponent : public juce::Component,
                          public juce::TableListBoxModel,
                          public juce::Button::Listener
{
public:
    // constructor for two DeckGUI
    PlaylistComponent(DeckGUI* deck1, DeckGUI* deck2);
    // destructor
    ~PlaylistComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    int getNumRows() override;

    // painting for the background in each row and higlighting selected rows
    void paintRowBackground(juce::Graphics&,
                            int rowNumber,
                            int width,
                            int height,
                            bool rowIsSelected) override;

    // painitng of the cell content
    void paintCell(juce::Graphics&,
                   int rowNumber,
                   int columnId,
                   int width,
                   int height,
                   bool rowIsSelected) override;

    // refreshig of cell components
    juce::Component* refreshComponentForCell(int rowNumber,
                                             int columnId,
                                             bool isRowSelected,
                                             juce::Component* existingComponentToUpdate) override;

    // button click handler within component
    void buttonClicked(juce::Button* button) override;

    // for playlist loading from users system
    void loadPlaylist();

private:
    // TableListBox for playlist display in a tabular form
    juce::TableListBox tableComponent;
    // vector for title storing
    std::vector<std::string> trackTitles;
    // vector for URL storing for the files
    std::vector<juce::URL> trackUrls;

    // pointer to button for load playlist
    std::unique_ptr<juce::TextButton> loadPlaylistButton;
    // pointer for FileChooser for selecting audio files
    std::unique_ptr<juce::FileChooser> chooser;

    // pointers to the both DeckGUI
    DeckGUI* deck1;
    DeckGUI* deck2;

    // object for styling component and its elements
    juce::LookAndFeel_V4 customLookAndFeel; // Add this member for custom styling

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
};
