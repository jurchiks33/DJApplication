//
////PlaylistComponent.cpp
//

#include <JuceHeader.h>
#include "PlaylistComponent.h"
#include "DeckGUI.h"

// Constructor for PlaylistComponent
PlaylistComponent::PlaylistComponent(DeckGUI* deck1GUI, DeckGUI* deck2GUI)
    : deck1(deck1GUI), deck2(deck2GUI)  // initialization of a deck pointers
{
    std::cout << "Initializing PlaylistComponent..." << std::endl;

    // Setup columns: Track title, Deck, and Remove
    tableComponent.getHeader().addColumn("Track title", 1, 500); // column for track titles
    tableComponent.getHeader().addColumn("Deck", 2, 200);        // column for deck buttons
    tableComponent.getHeader().addColumn("Remove", 3, 100);      // column for remove buttons

    tableComponent.setModel(this);      // model for the table
    addAndMakeVisible(tableComponent);  // make table visible
    std::cout << "Table component added to PlaylistComponent." << std::endl;

    // creation and cofiguration for load playlist button
    loadPlaylistButton = std::make_unique<juce::TextButton>("Load Playlist");
    loadPlaylistButton->onClick = [this] 
    {
        std::cout << "Load Playlist button clicked." << std::endl;
        loadPlaylist(); // triggering on a click
    };

    // Style for Load Playlist button
    loadPlaylistButton->setColour(juce::TextButton::buttonColourId,
                                  juce::Colours::darkorange);
    loadPlaylistButton->setColour(juce::TextButton::textColourOnId, 
                                  juce::Colours::white);
    loadPlaylistButton->setLookAndFeel(&customLookAndFeel);

    addAndMakeVisible(loadPlaylistButton.get());
    std::cout << "Load Playlist button added to PlaylistComponent." << std::endl;
}

// destructor
PlaylistComponent::~PlaylistComponent()
{
    std::cout << "Destroying PlaylistComponent..." << std::endl;
    loadPlaylistButton->setLookAndFeel(nullptr); // Reset LookAndFeel on destruction
}

// styling for component
void PlaylistComponent::paint(juce::Graphics& g)
{
    // radial gradient background
    juce::ColourGradient gradient(juce::Colours::darkslategrey, 
                                  getWidth() / 2,
                                  getHeight() / 2,
                                  juce::Colours::black, 
                                  getWidth(),
                                  getHeight(), true);
    gradient.addColour(0.4, juce::Colours::slategrey.darker(0.2f));
    g.setGradientFill(gradient);
    g.fillAll();

    // Decorative border
    g.setColour(juce::Colours::whitesmoke.withAlpha(0.3f));
    g.drawRect(getLocalBounds(), 2);

    // diagonal lines for added texture
    g.setColour(juce::Colours::whitesmoke.withAlpha(0.1f));
    for (int i = -getHeight(); i < getWidth(); i += 25)
    {
        g.drawLine(i, 0, i + getHeight(), getHeight(), 0.5f);
    }
}

void PlaylistComponent::resized()
{
    auto area = getLocalBounds();
    tableComponent.setBounds(area.removeFromTop(getHeight() - 50)); // Adjust to fit the load button
    loadPlaylistButton->setBounds(area.reduced(10));                // reduce of area size for padding
    std::cout << "Resized PlaylistComponent." << std::endl;
}

// returning of the rows in a table same as the number of tracks
int PlaylistComponent::getNumRows()
{
    std::cout << "Getting number of rows: " << trackTitles.size() << std::endl;
    return static_cast<int>(trackTitles.size());
}

// styling for row background in each table
void PlaylistComponent::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    auto baseColour = rowIsSelected ? juce::Colours::orange.withAlpha(0.4f) :
                                      juce::Colours::darkgrey.withAlpha(0.2f);
    g.fillAll(baseColour);

    // Adding subtle stripes for unselected rows
    if (!rowIsSelected)
    {
        g.setColour(juce::Colours::black.withAlpha(0.05f));
        g.drawRect(0, 0, width, height, 1);
    }
}

// painting of the content of each cell in the table
void PlaylistComponent::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour(rowIsSelected ? juce::Colours::black : 
                                juce::Colours::white);
    g.setFont(14.0f);

    if (columnId == 1) // Track title column
    {
        g.drawText(trackTitles[rowNumber],
                   2, 0,
                   width - 4, height,
                   juce::Justification::centredLeft,
                   true);
    }
}

// refreshes components for cells and adds buttons for specific columns
juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, juce::Component* existingComponentToUpdate)
{
    const int buttonWidth = 70;  // Set a consistent width
    const int buttonHeight = 20; // Set a consistent height
    const int spacing = 10;      // Space between buttons

    if (columnId == 2) // Deck buttons column
    {
        if (existingComponentToUpdate == nullptr)
        {
            auto* deckButtonContainer = new juce::Component();

            // Create "Deck 1" button
            auto* deck1Button = new juce::TextButton{"Deck 1"};
            deck1Button->setComponentID("deck1_" + std::to_string(rowNumber));
            deck1Button->addListener(this);
            deck1Button->setSize(buttonWidth, buttonHeight);
            deck1Button->setColour(juce::TextButton::buttonColourId, 
                                   juce::Colours::steelblue);
            deck1Button->setColour(juce::TextButton::textColourOnId, 
                                   juce::Colours::white);
            deckButtonContainer->addAndMakeVisible(deck1Button);

            // Create "Deck 2" button
            auto* deck2Button = new juce::TextButton{"Deck 2"};
            deck2Button->setComponentID("deck2_" + std::to_string(rowNumber));
            deck2Button->addListener(this);
            deck2Button->setSize(buttonWidth, buttonHeight);
            deck2Button->setColour(juce::TextButton::buttonColourId, 
                                   juce::Colours::seagreen);
            deck2Button->setColour(juce::TextButton::textColourOnId, 
                                   juce::Colours::white);
            deckButtonContainer->addAndMakeVisible(deck2Button);

            // Arrange buttons in a row using FlexBox
            juce::FlexBox flexBox;
            flexBox.flexDirection = juce::FlexBox::Direction::row;
            flexBox.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
            flexBox.items.add(juce::FlexItem(*deck1Button).
                              withMinWidth(buttonWidth).
                              withMinHeight(buttonHeight));
            flexBox.items.add(juce::FlexItem(*deck2Button).
                              withMinWidth(buttonWidth).
                              withMinHeight(buttonHeight).
                              withMargin(juce::FlexItem::Margin(0, 0, 0, spacing)));

            deckButtonContainer->setBounds(0, 0, 2 * buttonWidth + spacing, buttonHeight);
            flexBox.performLayout(deckButtonContainer->getLocalBounds());

            existingComponentToUpdate = deckButtonContainer;
            std::cout << "Created Deck buttons for row " << rowNumber << std::endl;
        }
    }
    else if (columnId == 3) // remove column
    {
        if (existingComponentToUpdate == nullptr)
        {
            // Create a container for the Remove button to ensure layout consistency
            auto* removeButtonContainer = new juce::Component();

            // Create "Remove" button
            auto* removeButton = new juce::TextButton{"Remove"};
            removeButton->setComponentID("remove_" + std::to_string(rowNumber));
            removeButton->addListener(this);
            removeButton->setSize(buttonWidth, buttonHeight);
            removeButton->setColour(juce::TextButton::buttonColourId, 
                                    juce::Colours::crimson);
            removeButton->setColour(juce::TextButton::textColourOnId, 
                                    juce::Colours::white);
            removeButtonContainer->addAndMakeVisible(removeButton);

            // Set bounds of the container
            removeButtonContainer->setBounds(0, 0, buttonWidth, buttonHeight);

            // Use FlexBox layout to center the button in its container
            juce::FlexBox flexBox;
            flexBox.flexDirection = juce::FlexBox::Direction::row;
            flexBox.justifyContent = juce::FlexBox::JustifyContent::center;
            flexBox.alignContent = juce::FlexBox::AlignContent::center;
            flexBox.items.add(juce::FlexItem(*removeButton).
                              withMinWidth(buttonWidth).
                              withMinHeight(buttonHeight));

            flexBox.performLayout(removeButtonContainer->getLocalBounds());

            existingComponentToUpdate = removeButtonContainer;
            std::cout << "Created Remove button for row " << rowNumber << std::endl;
        }
    }

    return existingComponentToUpdate;
}

// handler for button clicks, track loading into decks and removing from playlist
void PlaylistComponent::buttonClicked(juce::Button* button)
{
    std::cout << "Button clicked: " << button->getComponentID() << std::endl;

    auto id = button->getComponentID().toStdString();
    auto rowIndex = std::stoi(id.substr(id.find('_') + 1));

    if (id.find("deck1_") != std::string::npos)
    {
        deck1->loadTrack(trackUrls[rowIndex]); // load track in deck 1
        std::cout << "Loaded on Deck 1: " << trackTitles[rowIndex] << std::endl;
    }
    else if (id.find("deck2_") != std::string::npos)
    {
        deck2->loadTrack(trackUrls[rowIndex]); // load track in deck 2
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

// playlist loading from user system
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
