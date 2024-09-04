//
//
//#include "MainComponent.h"
//
////==============================================================================
//MainComponent::MainComponent()
//    : player1(formatManager, equalizerComponent1),
//      player2(formatManager, equalizerComponent2),
//      deckGUI1(&player1, formatManager, thumbCache),
//      deckGUI2(&player2, formatManager, thumbCache),
//      playlistComponent(&deckGUI1, &deckGUI2)
//{
//    setSize(800, 600);
//
//    // Setup the references between decks
//    deckGUI1.setOtherDeck(&deckGUI2);
//    deckGUI2.setOtherDeck(&deckGUI1);
//
//    // Request audio permissions if needed
//    if (juce::RuntimePermissions::isRequired(juce::RuntimePermissions::recordAudio)
//        && !juce::RuntimePermissions::isGranted(juce::RuntimePermissions::recordAudio))
//    {
//        juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
//                                           [&](bool granted) { setAudioChannels(granted ? 2 : 0, 2); });
//    }
//    else
//    {
//        setAudioChannels(0, 2); // Setup audio channels
//    }
//
//    // Add components to the visible area
//    addAndMakeVisible(deckGUI1);
//    addAndMakeVisible(deckGUI2);
//    addAndMakeVisible(playlistComponent);
//    addAndMakeVisible(equalizerComponent1); // Add the first EqualizerComponent
//    addAndMakeVisible(equalizerComponent2); // Add the second EqualizerComponent
//
//    // Register basic audio formats
//    formatManager.registerBasicFormats();
//}
//
//MainComponent::~MainComponent()
//{
//    shutdownAudio(); // Clean up audio resources
//}
//
//void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
//{
//    // Prepare players and mixer for audio playback
//    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
//    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
//    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
//
//    // Add input sources to the mixer; ensure the second argument is false (not owning sources)
//    mixerSource.addInputSource(&player1, false);
//    mixerSource.addInputSource(&player2, false);
//}
//
//void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
//{
//    // Fill the audio buffer from the mixer source
//    mixerSource.getNextAudioBlock(bufferToFill);
//}
//
//void MainComponent::releaseResources()
//{
//    // Release resources for players and mixer
//    player1.releaseResources();
//    player2.releaseResources();
//    mixerSource.releaseResources();
//}
//
//void MainComponent::paint(juce::Graphics& g)
//{
//    // Fill background with the look and feel color
//    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
//}
//
//void MainComponent::resized()
//{
//    // Calculate component heights based on the window height
//    auto deckHeight = getHeight() / 3;
//
//    // Set bounds for Deck GUI components
//    deckGUI1.setBounds(0, 0, getWidth() / 2, deckHeight);
//    deckGUI2.setBounds(getWidth() / 2, 0, getWidth() / 2, deckHeight);
//
//    // Set bounds for the Equalizer components side by side with the central shared controls
//    equalizerComponent1.setBounds(0, deckHeight, getWidth() / 2, deckHeight);
//    equalizerComponent2.setBounds(getWidth() / 2, deckHeight, getWidth() / 2, deckHeight);
//
//    // Set bounds for the Playlist component
//    playlistComponent.setBounds(0, deckHeight * 2, getWidth(), deckHeight);
//}
//


// MainComponent.cpp

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
    : player1(formatManager, equalizerComponent1),
      player2(formatManager, equalizerComponent2),
      deckGUI1(&player1, formatManager, thumbCache),
      deckGUI2(&player2, formatManager, thumbCache),
      playlistComponent(&deckGUI1, &deckGUI2, formatManager) // Correct constructor call
{
    setSize(800, 600);

    // Setup the references between decks
    deckGUI1.setOtherDeck(&deckGUI2);
    deckGUI2.setOtherDeck(&deckGUI1);

    // Request audio permissions if needed
    if (juce::RuntimePermissions::isRequired(juce::RuntimePermissions::recordAudio)
        && !juce::RuntimePermissions::isGranted(juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
                                           [&](bool granted) { setAudioChannels(granted ? 2 : 0, 2); });
    }
    else
    {
        setAudioChannels(0, 2); // Ensure 2 output channels are set up
    }


    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);
    addAndMakeVisible(playlistComponent);
    addAndMakeVisible(equalizerComponent1);
    addAndMakeVisible(equalizerComponent2);

    formatManager.registerBasicFormats();
}

MainComponent::~MainComponent()
{
    shutdownAudio(); // Clean up audio resources
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    // Prepare all sources
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    // Add to mixer if not already added
    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);
    mixerSource.addInputSource(playlistComponent.getPreviewPlayer(), false);


    // Check if playlistComponent's previewPlayer needs to be added
    if (playlistComponent->hasPreviewPlayer())
    {
        mixerSource.addInputSource(playlistComponent->getPreviewPlayer(), false);
    }
}


void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Get audio from the mixer source
    mixerSource.getNextAudioBlock(bufferToFill);
}


void MainComponent::releaseResources()
{
    // Release resources for players and mixer
    player1.releaseResources();
    player2.releaseResources();
    mixerSource.releaseResources();
}

void MainComponent::paint(juce::Graphics& g)
{
    // Fill background with the look and feel color
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    // Calculate component heights based on the window height
    auto deckHeight = getHeight() / 3;

    // Set bounds for Deck GUI components
    deckGUI1.setBounds(0, 0, getWidth() / 2, deckHeight);
    deckGUI2.setBounds(getWidth() / 2, 0, getWidth() / 2, deckHeight);

    // Set bounds for the Equalizer components side by side with the central shared controls
    equalizerComponent1.setBounds(0, deckHeight, getWidth() / 2, deckHeight);
    equalizerComponent2.setBounds(getWidth() / 2, deckHeight, getWidth() / 2, deckHeight);

    // Set bounds for the Playlist component
    playlistComponent.setBounds(0, deckHeight * 2, getWidth(), deckHeight);
}


