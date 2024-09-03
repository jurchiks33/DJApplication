///*
//  ==============================================================================
//
//    PlaylistComponent.cpp
//
//  ==============================================================================
//*/
//
//#include <JuceHeader.h>
//#include "PlaylistComponent.h"
//
////==============================================================================
//PlaylistComponent::PlaylistComponent()
//{
//    trackTitles = {"Track 1", "Track 2", "Track 3", "Track 4", "Track 5", "Track 6"};
//    
//    tableComponent.getHeader().addColumn("Track title", 1, 400);
//    tableComponent.getHeader().addColumn("", 2, 200);
//
//
//    tableComponent.setModel(this);
//    addAndMakeVisible(tableComponent);
//}
//
//PlaylistComponent::~PlaylistComponent()
//{
//}
//
//void PlaylistComponent::paint (juce::Graphics& g)
//{
//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
//    g.setColour (juce::Colours::grey);
//    g.drawRect (getLocalBounds(), 1);
//    g.setColour (juce::Colours::white);
//    g.setFont (14.0f);
//    g.drawText ("PlaylistComponent", getLocalBounds(),
//                juce::Justification::centred, true);
//}
//
//void PlaylistComponent::resized()
//{
//    tableComponent.setBounds(0, 0, getWidth(), getHeight());
//}
//
//int PlaylistComponent::getNumRows ()
//{
//    return static_cast<int>(trackTitles.size());  // Correct implicit conversion warning
//}
//
//void PlaylistComponent::paintRowBackground (juce::Graphics & g, int rowNumber, int width, int height, bool rowIsSelected)
//{
//    if (rowIsSelected)
//    {
//        g.fillAll(juce::Colours::orange);
//    }
//    else{
//        g.fillAll(juce::Colours::darkgrey);
//    }
//}
//
//void PlaylistComponent::paintCell (juce::Graphics & g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
//{
//    g.drawText (trackTitles[rowNumber],
//                2, 0,
//                width - 4, height,
//                juce::Justification::centredLeft,
//                true);
//}
//
//juce::Component* PlaylistComponent::refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, juce::Component *existingComponentToUpdate)
//{
//    if (columnId == 2)
//    {
//        if (existingComponentToUpdate == nullptr)
//        {
//            juce::TextButton* btn = new juce::TextButton{"Play"};
//            juce::String id{std::to_string(rowNumber)};
//            btn->setComponentID(id);
//            btn->addListener(this);
//            existingComponentToUpdate = btn;
//        }
//    }
//    return existingComponentToUpdate;
//}
//
//void PlaylistComponent::buttonClicked(juce::Button* button)
//{
//    int id = std::stoi(button->getComponentID().toStdString());
//    std::cout << "PlaylistComponent::buttonClicked " << trackTitles[id] << std::endl;
//}

//-------------------------------------------------------

//    PlaylistComponent.cpp

#include <JuceHeader.h>
#include "PlaylistComponent.h"
#include "DeckGUI.h"

// Include headers necessary for file operations
#include <fstream>
#include <sstream>

PlaylistComponent::PlaylistComponent(DeckGUI* deck1GUI, DeckGUI* deck2GUI)
    : deck1(deck1GUI), deck2(deck2GUI)
{
    tableComponent.getHeader().addColumn("Track title", 1, 400);
    tableComponent.getHeader().addColumn("Play", 2, 100); // Column for Play button
    tableComponent.getHeader().addColumn("Deck", 3, 200); // Column for Deck buttons

    tableComponent.setModel(this);
    addAndMakeVisible(tableComponent);

    // Button to load playlist
    loadPlaylistButton = std::make_unique<juce::TextButton>("Load Playlist");
    loadPlaylistButton->onClick = [this] { loadPlaylist(); };
    addAndMakeVisible(*loadPlaylistButton);
}


PlaylistComponent::~PlaylistComponent() {}

void PlaylistComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // Draw a border around the component
}

void PlaylistComponent::resized()
{
    auto area = getLocalBounds();
    tableComponent.setBounds(area.removeFromTop(getHeight() - 30)); // Adjust height for the table
    loadPlaylistButton->setBounds(area.removeFromBottom(30).reduced(10)); // Place button at the bottom
}


int PlaylistComponent::getNumRows()
{
    return static_cast<int>(trackTitles.size()); // Return the number of tracks
}

void PlaylistComponent::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    g.fillAll(rowIsSelected ? juce::Colours::orange : juce::Colours::darkgrey);
}

void PlaylistComponent::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    if (columnId == 1)
    {
        g.drawText(trackTitles[rowNumber],
                   2, 0,
                   width - 4, height,
                   juce::Justification::centredLeft,
                   true);
    }
}

juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, juce::Component* existingComponentToUpdate)
{
    if (columnId == 2) // Play button column
    {
        if (existingComponentToUpdate == nullptr)
        {
            auto* playButton = new juce::TextButton{"Play"};
            playButton->setComponentID("play_" + std::to_string(rowNumber));
            playButton->addListener(this);
            existingComponentToUpdate = playButton;
        }
    }
    else if (columnId == 3) // Deck buttons column
    {
        if (existingComponentToUpdate == nullptr)
        {
            auto* deckButtonContainer = new juce::Component();

            auto* deck1Button = new juce::TextButton{"Deck 1"};
            deck1Button->setComponentID("deck1_" + std::to_string(rowNumber));
            deck1Button->addListener(this);
            deck1Button->setBounds(0, 0, 90, 25);
            deckButtonContainer->addAndMakeVisible(deck1Button);

            auto* deck2Button = new juce::TextButton{"Deck 2"};
            deck2Button->setComponentID("deck2_" + std::to_string(rowNumber));
            deck2Button->addListener(this);
            deck2Button->setBounds(100, 0, 90, 25);
            deckButtonContainer->addAndMakeVisible(deck2Button);

            existingComponentToUpdate = deckButtonContainer;
        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(juce::Button* button)
{
    auto id = button->getComponentID().toStdString();
    auto rowIndex = std::stoi(id.substr(id.find('_') + 1));

    if (id.find("play_") != std::string::npos)
    {
        std::cout << "Playing: " << trackTitles[rowIndex] << std::endl;
    }
    else if (id.find("deck1_") != std::string::npos)
    {
        deck1->loadTrack(trackUrls[rowIndex]); // Implement loadTrack in DeckGUI
        std::cout << "Loaded on Deck 1: " << trackTitles[rowIndex] << std::endl;
    }
    else if (id.find("deck2_") != std::string::npos)
    {
        deck2->loadTrack(trackUrls[rowIndex]); // Implement loadTrack in DeckGUI
        std::cout << "Loaded on Deck 2: " << trackTitles[rowIndex] << std::endl;
    }
}

void PlaylistComponent::loadPlaylist()
{
    auto chooser = std::make_unique<juce::FileChooser>("Select a Playlist File", juce::File{}, "*.wav;*.mp3"); // You can add more supported formats
    chooser->launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles | juce::FileBrowserComponent::canSelectMultipleItems,
                         [this](const juce::FileChooser& fc)
    {
        auto results = fc.getResults();
        for (const auto& file : results)
        {
            if (file.existsAsFile())
            {
                trackTitles.push_back(file.getFileName().toStdString());
                trackUrls.push_back(juce::URL(file));
            }
        }
        // Refresh table content to display loaded tracks
        tableComponent.updateContent();
        tableComponent.repaint();
    });
}


