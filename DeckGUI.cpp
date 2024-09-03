//DeckGUI.cpp

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 juce::AudioFormatManager & formatManagerToUse,
                 juce::AudioThumbnailCache & cacheToUse) : player(_player),
                    waveformDisplay(formatManagerToUse, cacheToUse)
{
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(syncButton); // Add the Sync button

    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(waveformDisplay);
    
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    syncButton.addListener(this); // Add listener for Sync button

    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 100.0);
    posSlider.setRange(0.0, 1.0);
    
    startTimer(500);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText ("DeckGUI", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    double rowH = getHeight() / 9;
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    syncButton.setBounds(0, rowH * 2, getWidth(), rowH); // Set bounds for Sync button

    volSlider.setBounds(0, rowH * 3, getWidth(), rowH);
    speedSlider.setBounds(0, rowH * 4, getWidth(), rowH);
    posSlider.setBounds(0, rowH * 5, getWidth(), rowH);
    waveformDisplay.setBounds(0, rowH * 6, getWidth(), rowH * 2);
    loadButton.setBounds(0, rowH * 8, getWidth(), rowH);
}

void DeckGUI::buttonClicked(juce::Button* button)
{
    if (button == &syncButton)
    {
        std::cout << "Sync button was clicked " << std::endl;

        // Retrieve the BPM from the other deck
        double targetBPM = deck2 ? deck2->getPlayerBPM() : 120.0; // Ensure deck2 is correctly set up
        double currentBPM = player->getBPM();

        std::cout << "Current BPM: " << currentBPM << ", Target BPM: " << targetBPM << std::endl;

        if (currentBPM > 0 && targetBPM > 0)
        {
            double speedRatio = targetBPM / currentBPM;
            player->setSpeed(speedRatio); // Adjust speed without resetting position
            std::cout << "Adjusted speed to ratio: " << speedRatio << std::endl;
        }
    }
}


void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }
    else if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    else if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray &files)
{
    std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
    return true;
}

void DeckGUI::filesDropped (const juce::StringArray &files, int x, int y)
{
    std::cout << " DeckGUI::filesDropped" << std::endl;
    if (files.size() == 1)
    {
        player->loadURL(juce::URL{juce::File{files[0]}});
    }
}

void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}

//----------------------------------------
void DeckGUI::loadTrack(const juce::String& trackName)
{
    // Logic to find the corresponding URL for the given track name
    juce::File audioFile(trackName);
    
    if (audioFile.existsAsFile())
    {
        juce::URL audioURL(audioFile);
        player->loadURL(audioURL);
        waveformDisplay.loadURL(audioURL);
        std::cout << "Loading track into Deck: " << trackName << std::endl;
    }
    else
    {
        std::cout << "File does not exist: " << trackName << std::endl;
    }
}


void DeckGUI::loadTrack(const juce::URL& audioURL)
{
    player->loadURL(audioURL);
    waveformDisplay.loadURL(audioURL);
}
