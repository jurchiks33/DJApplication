//
////PlaylistComponent.cpp
//

#include <JuceHeader.h>
#include "PlaylistComponent.h"
#include "DeckGUI.h"

// Constructor
PlaylistComponent::PlaylistComponent(DeckGUI* deck1GUI, DeckGUI* deck2GUI)
    : deck1(deck1GUI), deck2(deck2GUI)
{
    std::cout << "Initializing PlaylistComponent..." << std::endl;

    // Setup columns: Track title, Deck, and Remove
    tableComponent.getHeader().addColumn("Track title", 1, 500); // Adjust width as needed
    tableComponent.getHeader().addColumn("Deck", 2, 200);        // Adjust width as needed
    tableComponent.getHeader().addColumn("Remove", 3, 100);      // New column for remove button

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
}

PlaylistComponent::~PlaylistComponent()
{
    std::cout << "Destroying PlaylistComponent..." << std::endl;
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
    std::cout << "Resized PlaylistComponent." << std::endl;
}

int PlaylistComponent::getNumRows()
{
    std::cout << "Getting number of rows: " << trackTitles.size() << std::endl;
    return static_cast<int>(trackTitles.size()); // Return the number of tracks
}

void PlaylistComponent::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    g.fillAll(rowIsSelected ? juce::Colours::orange : juce::Colours::darkgrey);
}

void PlaylistComponent::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    if (columnId == 1) // Track title column
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
    if (columnId == 2) // Deck buttons column
    {
        if (existingComponentToUpdate == nullptr)
        {
            auto* deckButtonContainer = new juce::Component();

            auto* deck1Button = new juce::TextButton{"Deck 1"};
            deck1Button->setComponentID("deck1_" + std::to_string(rowNumber));
            deck1Button->addListener(this);
            deck1Button->setBounds(0, 0, 90, 20); // Adjust height
            deckButtonContainer->addAndMakeVisible(deck1Button);

            auto* deck2Button = new juce::TextButton{"Deck 2"};
            deck2Button->setComponentID("deck2_" + std::to_string(rowNumber));
            deck2Button->addListener(this);
            deck2Button->setBounds(100, 0, 90, 20); // Adjust height
            deckButtonContainer->addAndMakeVisible(deck2Button);

            existingComponentToUpdate = deckButtonContainer;
            std::cout << "Created Deck buttons for row " << rowNumber << std::endl;
        }
    }
    else if (columnId == 3) // Remove column
    {
        if (existingComponentToUpdate == nullptr)
        {
            auto* removeButton = new juce::TextButton{"Remove"};
            removeButton->setComponentID("remove_" + std::to_string(rowNumber));
            removeButton->addListener(this);
            removeButton->setBounds(0, 0, 60, 20); // Adjust dimensions as needed
            existingComponentToUpdate = removeButton;
            std::cout << "Created Remove button for row " << rowNumber << std::endl;
        }
    }

    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(juce::Button* button)
{
    std::cout << "Button clicked: " << button->getComponentID() << std::endl;

    auto id = button->getComponentID().toStdString();
    auto rowIndex = std::stoi(id.substr(id.find('_') + 1));

    if (id.find("deck1_") != std::string::npos)
    {
        deck1->loadTrack(trackUrls[rowIndex]); // Implement loadTrack in DeckGUI
        std::cout << "Loaded on Deck 1: " << trackTitles[rowIndex] << std::endl;
    }
    else if (id.find("deck2_") != std::string::npos)
    {
        deck2->loadTrack(trackUrls[rowIndex]); // Implement loadTrack in DeckGUI
        std::cout << "Loaded on Deck 2: " << trackTitles[rowIndex] << std::endl;
    }
    else if (id.find("remove_") != std::string::npos)
    {
        // Remove the track from the playlist
        trackTitles.erase(trackTitles.begin() + rowIndex);
        trackUrls.erase(trackUrls.begin() + rowIndex);
        tableComponent.updateContent();
        std::cout << "Removed track at index: " << rowIndex << std::endl;
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

    std::cout << "FileChooser created." << std::endl;

    auto fileChooserFlags = juce::FileBrowserComponent::openMode |
                            juce::FileBrowserComponent::canSelectFiles |
                            juce::FileBrowserComponent::canSelectMultipleItems;

    chooser->launchAsync(fileChooserFlags, [this](const juce::FileChooser& fc)
    {
        std::cout << "FileChooser callback triggered." << std::endl;

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
            else
            {
                std::cout << "File does not exist: " << file.getFullPathName() << std::endl;
            }
        }

        tableComponent.updateContent();
        tableComponent.repaint();

        std::cout << "Playlist loaded and table updated." << std::endl;
    });

    std::cout << "After launchAsync call." << std::endl;
}

