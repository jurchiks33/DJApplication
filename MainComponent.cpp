//#include "MainComponent.h"
//
////==============================================================================
//MainComponent::MainComponent()
//    : player1(formatManager, equalizerComponent),
//      player2(formatManager, equalizerComponent),
//      deckGUI1(&player1, formatManager, thumbCache),
//      deckGUI2(&player2, formatManager, thumbCache),
//      playlistComponent(&deckGUI1, &deckGUI2)
//{
//    setSize (800, 600);
//
//    // Setup the references between decks
//    deckGUI1.setOtherDeck(&deckGUI2);
//    deckGUI2.setOtherDeck(&deckGUI1);
//
//    // Request audio permissions if needed
//    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
//        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
//    {
//        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
//                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
//    }
//    else
//    {
//        setAudioChannels (0, 2); // Setup audio channels
//    }
//    
//    // Add components to the visible area
//    addAndMakeVisible(deckGUI1);
//    addAndMakeVisible(deckGUI2);
//    addAndMakeVisible(playlistComponent);
//    addAndMakeVisible(equalizerComponent);
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
//    // Set bounds for the Equalizer component
//    equalizerComponent.setBounds(0, deckHeight, getWidth(), deckHeight);
//    
//    // Set bounds for the Playlist component
//    playlistComponent.setBounds(0, deckHeight * 2, getWidth(), deckHeight);
//}

//MainComponent.cpp

#include <JuceHeader.h>
#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
    : equalizerComponent1(player1),
      equalizerComponent2(player2),
      player1(formatManager, equalizerComponent1),
      player2(formatManager, equalizerComponent2),
      deckGUI1(&player1, formatManager, thumbCache),
      deckGUI2(&player2, formatManager, thumbCache),
      playlistComponent(&deckGUI1, &deckGUI2)
{
    setSize(800, 600);

    // Setup the references between decks after ensuring they are initialized
    deckGUI1.setOtherDeck(&deckGUI2);
    deckGUI2.setOtherDeck(&deckGUI1);

    // Request audio permissions if needed
    if (juce::RuntimePermissions::isRequired(juce::RuntimePermissions::recordAudio)
        && !juce::RuntimePermissions::isGranted(juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
            [&](bool granted) {
                if (granted)
                {
                    juce::String error = deviceManager.initialiseWithDefaultDevices(0, 2); // 0 input channels, 2 output channels
                    if (!error.isEmpty())
                    {
                        juce::Logger::writeToLog("Error initializing audio channels: " + error);
                        juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon,
                                                               "Audio Initialization Error",
                                                               "Failed to initialize audio: " + error);
                    }
                }
                else
                {
                    juce::Logger::writeToLog("Audio permissions not granted.");
                }
            });
    }
    else
    {
        // Correct initialization of audio channels
        juce::String error = deviceManager.initialise(0, 2, nullptr, true);
        if (!error.isEmpty()) {
            juce::Logger::writeToLog("Error initializing audio channels: " + error);
            juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon,
                                                   "Audio Initialization Error",
                                                   "Failed to initialize audio: " + error);
        }
    }

    // Add components to the visible area after ensuring they are properly initialized
    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);
    addAndMakeVisible(playlistComponent);
    addAndMakeVisible(equalizerComponent1);
    addAndMakeVisible(equalizerComponent2);

    // Register basic audio formats
    formatManager.registerBasicFormats();
}

MainComponent::~MainComponent()
{
    shutdownAudio(); // Clean up audio resources
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    player1.releaseResources();
    player2.releaseResources();
    mixerSource.releaseResources();
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    auto deckHeight = getHeight() / 3;
    deckGUI1.setBounds(0, 0, getWidth() / 2, deckHeight);
    deckGUI2.setBounds(getWidth() / 2, 0, getWidth() / 2, deckHeight);
    equalizerComponent1.setBounds(0, deckHeight, getWidth() / 2, deckHeight);
    equalizerComponent2.setBounds(getWidth() / 2, deckHeight, getWidth() / 2, deckHeight);
    playlistComponent.setBounds(0, deckHeight * 2, getWidth(), deckHeight);
}
