//
////    PlaylistComponent.cpp
//
//#include <JuceHeader.h>
//#include "PlaylistComponent.h"
//#include "DeckGUI.h"
//
//// Include headers necessary for file operations
//#include <fstream>
//#include <sstream>
//
//
//// Constructor
//PlaylistComponent::PlaylistComponent(DeckGUI* deck1GUI, DeckGUI* deck2GUI)
//    : deck1(deck1GUI), deck2(deck2GUI)
//{
//    std::cout << "Initializing PlaylistComponent..." << std::endl;
//
//    tableComponent.getHeader().addColumn("Track title", 1, 400);
//    tableComponent.getHeader().addColumn("Play", 2, 100); // Column for Play button
//    tableComponent.getHeader().addColumn("Deck", 3, 200); // Column for Deck buttons
//
//    tableComponent.setModel(this);
//    addAndMakeVisible(tableComponent);
//    std::cout << "Table component added to PlaylistComponent." << std::endl;
//
//    // Button to load playlist
//    loadPlaylistButton = std::make_unique<juce::TextButton>("Load Playlist");
//    loadPlaylistButton->onClick = [this] {
//        std::cout << "Load Playlist button clicked." << std::endl;
//        loadPlaylist();
//    };
//    addAndMakeVisible(loadPlaylistButton.get());
//    std::cout << "Load Playlist button added to PlaylistComponent." << std::endl;
//}
//
//PlaylistComponent::~PlaylistComponent()
//{
//    std::cout << "Destroying PlaylistComponent..." << std::endl;
//}
//
//void PlaylistComponent::paint(juce::Graphics& g)
//{
//    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
//    g.setColour(juce::Colours::grey);
//    g.drawRect(getLocalBounds(), 1);
//    g.setColour(juce::Colours::white);
//    g.setFont(14.0f);
//    g.drawText("PlaylistComponent", getLocalBounds(),
//               juce::Justification::centred, true);
//}
//
//void PlaylistComponent::resized()
//{
//    auto area = getLocalBounds();
//    tableComponent.setBounds(area.removeFromTop(getHeight() - 40)); // Adjust the bounds to fit the load button
//    loadPlaylistButton->setBounds(area);
//    std::cout << "Resized PlaylistComponent." << std::endl;
//}
//
//int PlaylistComponent::getNumRows()
//{
//    std::cout << "Getting number of rows: " << trackTitles.size() << std::endl;
//    return static_cast<int>(trackTitles.size()); // Return the number of tracks
//}
//
//void PlaylistComponent::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
//{
//    g.fillAll(rowIsSelected ? juce::Colours::orange : juce::Colours::darkgrey);
//}
//
//void PlaylistComponent::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
//{
//    if (columnId == 1)
//    {
//        g.drawText(trackTitles[rowNumber],
//                   2, 0,
//                   width - 4, height,
//                   juce::Justification::centredLeft,
//                   true);
//    }
//}
//
//juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, juce::Component* existingComponentToUpdate)
//{
//    if (columnId == 2) // Play button column
//    {
//        if (existingComponentToUpdate == nullptr)
//        {
//            auto* playButton = new juce::TextButton{"Play"};
//            playButton->setComponentID("play_" + std::to_string(rowNumber));
//            playButton->addListener(this);
//            existingComponentToUpdate = playButton;
//            std::cout << "Created Play button for row " << rowNumber << std::endl;
//        }
//    }
//    else if (columnId == 3) // Deck buttons column
//    {
//        if (existingComponentToUpdate == nullptr)
//        {
//            auto* deckButtonContainer = new juce::Component();
//
//            auto* deck1Button = new juce::TextButton{"Deck 1"};
//            deck1Button->setComponentID("deck1_" + std::to_string(rowNumber));
//            deck1Button->addListener(this);
//            deck1Button->setBounds(0, 0, 90, 25);
//            deckButtonContainer->addAndMakeVisible(deck1Button);
//
//            auto* deck2Button = new juce::TextButton{"Deck 2"};
//            deck2Button->setComponentID("deck2_" + std::to_string(rowNumber));
//            deck2Button->addListener(this);
//            deck2Button->setBounds(100, 0, 90, 25);
//            deckButtonContainer->addAndMakeVisible(deck2Button);
//
//            existingComponentToUpdate = deckButtonContainer;
//            std::cout << "Created Deck buttons for row " << rowNumber << std::endl;
//        }
//    }
//    return existingComponentToUpdate;
//}
//
//void PlaylistComponent::buttonClicked(juce::Button* button)
//{
//    std::cout << "Button clicked: " << button->getComponentID() << std::endl;
//
//    auto id = button->getComponentID().toStdString();
//    auto rowIndex = std::stoi(id.substr(id.find('_') + 1));
//
//    if (id.find("play_") != std::string::npos)
//    {
//        std::cout << "Playing: " << trackTitles[rowIndex] << std::endl;
//    }
//    else if (id.find("deck1_") != std::string::npos)
//    {
//        deck1->loadTrack(trackUrls[rowIndex]); // Implement loadTrack in DeckGUI
//        std::cout << "Loaded on Deck 1: " << trackTitles[rowIndex] << std::endl;
//    }
//    else if (id.find("deck2_") != std::string::npos)
//    {
//        deck2->loadTrack(trackUrls[rowIndex]); // Implement loadTrack in DeckGUI
//        std::cout << "Loaded on Deck 2: " << trackTitles[rowIndex] << std::endl;
//    }
//}
//
//// PlaylistComponent.cpp
//void PlaylistComponent::loadPlaylist()
//{
//    std::cout << "Starting loadPlaylist function." << std::endl;
//
//    // Use the member FileChooser instance
//    chooser = std::make_unique<juce::FileChooser>(
//        "Select Audio Files",
//        juce::File::getSpecialLocation(juce::File::userMusicDirectory),
//        "*.wav;*.mp3;*.flac;*.aiff"
//    );
//
//    std::cout << "FileChooser created." << std::endl;
//
//    auto fileChooserFlags = juce::FileBrowserComponent::openMode |
//                            juce::FileBrowserComponent::canSelectFiles |
//                            juce::FileBrowserComponent::canSelectMultipleItems;
//
//    chooser->launchAsync(fileChooserFlags, [this](const juce::FileChooser& fc)
//    {
//        std::cout << "FileChooser callback triggered." << std::endl;
//
//        auto results = fc.getResults();
//        if (results.isEmpty())
//        {
//            std::cout << "No files were selected." << std::endl;
//            return;
//        }
//
//        for (const auto& file : results)
//        {
//            if (file.existsAsFile())
//            {
//                trackTitles.push_back(file.getFileName().toStdString());
//                trackUrls.push_back(juce::URL(file));
//                std::cout << "Loaded track: " << file.getFileName() << std::endl;
//            }
//            else
//            {
//                std::cout << "File does not exist: " << file.getFullPathName() << std::endl;
//            }
//        }
//
//        tableComponent.updateContent();
//        tableComponent.repaint();
//
//        std::cout << "Playlist loaded and table updated." << std::endl;
//    });
//
//    std::cout << "After launchAsync call." << std::endl;
//}

// PlaylistComponent.cpp

#include <JuceHeader.h>
#include "PlaylistComponent.h"
#include "DeckGUI.h"
#include "DjAudioPlayer.h"
#include "EqualizerComponent.h"

// Constructor
PlaylistComponent::PlaylistComponent(DeckGUI* deck1GUI, DeckGUI* deck2GUI, juce::AudioFormatManager& formatManager)
    : deck1(deck1GUI), deck2(deck2GUI)
{
    std::cout << "Initializing PlaylistComponent..." << std::endl;

    tableComponent.getHeader().addColumn("Track title", 1, 400);
    tableComponent.getHeader().addColumn("Play", 2, 100); // Column for Play button
    tableComponent.getHeader().addColumn("Deck", 3, 200); // Column for Deck buttons

    tableComponent.setModel(this);
    addAndMakeVisible(tableComponent);
    std::cout << "Table component added to PlaylistComponent." << std::endl;

    // Button to load playlist
    loadPlaylistButton = std::make_unique<juce::TextButton>("Load Playlist");
    loadPlaylistButton->onClick = [this] {
        std::cout << "Load Playlist button clicked." << std::endl;
        loadPlaylist();
    };
    addAndMakeVisible(loadPlaylistButton.get());
    std::cout << "Load Playlist button added to PlaylistComponent." << std::endl;

    // Correct initialization: Ensure DJAudioPlayer and EqualizerComponent are correctly linked
    previewPlayer = std::make_unique<DJAudioPlayer>(formatManager, *previewEqualizer);
    previewPlayer->setEqualizerComponent(previewEqualizer.get());
    previewPlayer->setGain(0.7); // Set default gain for audibility

    auto previewEqualizer = std::make_unique<EqualizerComponent>(*previewPlayer);
    previewPlayer->setEqualizerComponent(previewEqualizer.get()); // Link the equalizer, if applicable

    // Add the previewPlayer to your audio output/mixer if not already added
    // If using a mixer in MainComponent, ensure previewPlayer is added there
}

PlaylistComponent::~PlaylistComponent()
{
    std::cout << "Destroying PlaylistComponent..." << std::endl;
}

int PlaylistComponent::getNumRows()
{
    return static_cast<int>(trackTitles.size()); // Return the number of tracks
}

void PlaylistComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);
    g.setColour(juce::Colours::white);
    g.setFont(14.0f);
    g.drawText("PlaylistComponent", getLocalBounds(),
               juce::Justification::centred, true);
}

void PlaylistComponent::resized()
{
    auto area = getLocalBounds();
    tableComponent.setBounds(area.removeFromTop(getHeight() - 40)); // Adjust the bounds to fit the load button
    loadPlaylistButton->setBounds(area);
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
    std::cout << "Button clicked: " << button->getComponentID() << std::endl;

    auto id = button->getComponentID().toStdString();
    auto rowIndex = std::stoi(id.substr(id.find('_') + 1));

    if (id.find("play_") != std::string::npos)
    {
        if (isPlayingPreview)
        {
            previewPlayer->stop();
            button->setButtonText("Play");
            isPlayingPreview = false;
        }
        else
        {
            previewPlayer->loadURL(trackUrls[rowIndex]);
            previewPlayer->start();
            button->setButtonText("Stop");
            isPlayingPreview = true;
        }
        std::cout << (isPlayingPreview ? "Playing" : "Stopped") << ": " << trackTitles[rowIndex] << std::endl;
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
    std::cout << "Starting loadPlaylist function." << std::endl;

    chooser = std::make_unique<juce::FileChooser>(
        "Select Audio Files",
        juce::File::getSpecialLocation(juce::File::userMusicDirectory),
        "*.wav;*.mp3;*.flac;*.aiff"
    );

    auto fileChooserFlags = juce::FileBrowserComponent::openMode |
                            juce::FileBrowserComponent::canSelectFiles |
                            juce::FileBrowserComponent::canSelectMultipleItems;

    chooser->launchAsync(fileChooserFlags, [this](const juce::FileChooser& fc)
    {
        auto results = fc.getResults();
        if (results.isEmpty())
        {
            std::cout << "No files were selected." << std::endl;
            return;
        }

        for (const auto& file : results)
        {
            if (file.existsAsFile())
            {
                trackTitles.push_back(file.getFileName().toStdString());
                trackUrls.push_back(juce::URL(file));
                std::cout << "Loaded track: " << file.getFileName() << std::endl;
            }
        }

        tableComponent.updateContent();
        tableComponent.repaint();
    });
}
