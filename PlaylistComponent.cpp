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

PlaylistComponent::PlaylistComponent(DeckGUI* _deck1, DeckGUI* _deck2)
    : deck1(_deck1), deck2(_deck2)
{
    trackTitles = {"Track 1", "Track 2", "Track 3", "Track 4", "Track 5", "Track 6"};
    
    tableComponent.getHeader().addColumn("Track title", 1, 400);
    tableComponent.getHeader().addColumn("", 2, 200); // Play button column
    tableComponent.getHeader().addColumn("", 3, 200); // Deck buttons column

    tableComponent.setModel(this);
    addAndMakeVisible(tableComponent);
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);
    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);
}

void PlaylistComponent::resized()
{
    tableComponent.setBounds(0, 0, getWidth(), getHeight());
}

int PlaylistComponent::getNumRows ()
{
    return static_cast<int>(trackTitles.size());
}

void PlaylistComponent::paintRowBackground (juce::Graphics & g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(juce::Colours::orange);
    }
    else {
        g.fillAll(juce::Colours::darkgrey);
    }
}

void PlaylistComponent::paintCell (juce::Graphics & g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    if (columnId == 1) // Track Title Column
    {
        g.drawText (trackTitles[rowNumber],
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
            juce::TextButton* playButton = new juce::TextButton{"Play"};
            playButton->setComponentID("play_" + std::to_string(rowNumber));
            playButton->addListener(this);
            existingComponentToUpdate = playButton;
        }
    }
    else if (columnId == 3) // Deck buttons column
    {
        if (existingComponentToUpdate == nullptr)
        {
            juce::Component* deckButtonContainer = new juce::Component();
            deckButtonContainer->setBounds(0, 0, 200, 25); // Set the container height as needed

            // Adjust the bounds to reduce height but keep the width
            auto* deck1Button = new juce::TextButton{"Deck 1"};
            deck1Button->setComponentID("deck1_" + std::to_string(rowNumber));
            deck1Button->addListener(this);
            deck1Button->setBounds(0, 0, 90, 20); // Set height to 20, width 90
            deckButtonContainer->addAndMakeVisible(deck1Button);

            auto* deck2Button = new juce::TextButton{"Deck 2"};
            deck2Button->setComponentID("deck2_" + std::to_string(rowNumber));
            deck2Button->addListener(this);
            deck2Button->setBounds(100, 0, 90, 20); // Set height to 20, width 90
            deckButtonContainer->addAndMakeVisible(deck2Button);

            existingComponentToUpdate = deckButtonContainer;
        }
    }
    return existingComponentToUpdate;
}


void PlaylistComponent::buttonClicked(juce::Button* button)
{
    juce::String buttonID = button->getComponentID();
    int trackIndex = buttonID.fromLastOccurrenceOf("_", false, false).getIntValue();
    
    if (buttonID.startsWith("play_"))
    {
        std::cout << "Play button clicked for " << trackTitles[trackIndex] << std::endl;
    }
    else if (buttonID.startsWith("deck1_"))
    {
        std::cout << "Assigning " << trackTitles[trackIndex] << " to Deck 1" << std::endl;
        deck1->loadTrack(trackTitles[trackIndex]); // Replace with the actual track loading logic
    }
    else if (buttonID.startsWith("deck2_"))
    {
        std::cout << "Assigning " << trackTitles[trackIndex] << " to Deck 2" << std::endl;
        deck2->loadTrack(trackTitles[trackIndex]); // Replace with the actual track loading logic
    }
}

