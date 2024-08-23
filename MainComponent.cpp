//MainComponent.cpp

#include "MainComponent.h"

//==============================================================================

MainComponent::MainComponent()
{
    setSize (800, 600);

    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        setAudioChannels (0, 2);
    }
    
    addAndMakeVisible(deckGUI1);  // Add the first DeckGUI
    addAndMakeVisible(deckGUI2);  // Add the second DeckGUI
    
    formatManager.registerBasicFormats();

}


MainComponent::~MainComponent()
{
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);
    
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    player1.releaseResources();
    player2.releaseResources();
    mixerSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

//void MainComponent::resized()
//{
//    deckGUI1.setBounds(0, 0, getWidth()/2, getHeight());
//    deckGUI2.setBounds(getWidth()/2, 0, getWidth()/2, getHeight());  //EXPERIMENTAL!!!!!!!!!!!!!
//}

void MainComponent::resized()
{
    deckGUI1.setBounds(0, 0, getWidth()/2, getHeight());
    deckGUI2.setBounds(getWidth()/2, 0, getWidth()/2, getHeight());
}



