
// DeckGUI.cpp

#include "DeckGUI.h"
#include "DjAudioPlayer.h"
#include "WaveformDisplay.h"
#include <JuceHeader.h>

//==============================================================================

DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 juce::AudioFormatManager & formatManagerToUse,
                 juce::AudioThumbnailCache & cacheToUse)
                 : player(_player),
                   waveformDisplay(formatManagerToUse, cacheToUse)
{
    // Add and make buttons visible
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(syncButton);

    // Set button colors
    playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::coral);
    syncButton.setColour(juce::TextButton::buttonColourId, juce::Colours::lightblue);

    // Add sliders and waveform display
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(waveformDisplay);
    
    // Add button listeners
    playButton.addListener(this);
    stopButton.addListener(this);
    syncButton.addListener(this);

    // Add slider listeners
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    // Set slider ranges
    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 100.0);
    posSlider.setRange(0.0, 1.0);
    
    startTimer(500);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);
    g.setColour(juce::Colours::white);
    g.setFont(juce::Font(14.0f));
    g.drawText("DeckGUI", getLocalBounds(), juce::Justification::centred, true);
}

void DeckGUI::resized()
{
    double rowH = getHeight() / 8;
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    syncButton.setBounds(0, rowH * 2, getWidth(), rowH);

    volSlider.setBounds(0, rowH * 3, getWidth(), rowH);
    speedSlider.setBounds(0, rowH * 4, getWidth(), rowH);
    posSlider.setBounds(0, rowH * 5, getWidth(), rowH);
    waveformDisplay.setBounds(0, rowH * 6, getWidth(), rowH * 2);
}

void DeckGUI::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        player->start();
    }
    else if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->stop();
    }
    else if (button == &syncButton)
    {
        std::cout << "Sync button was clicked " << std::endl;

        double targetBPM = deck2 ? deck2->getPlayerBPM() : 120.0;
        double currentBPM = player->getBPM();

        std::cout << "Current BPM: " << currentBPM << ", Target BPM: " << targetBPM << std::endl;

        if (currentBPM > 0 && targetBPM > 0)
        {
            double speedRatio = targetBPM / currentBPM;
            player->setSpeed(speedRatio);
            std::cout << "Adjusted speed to ratio: " << speedRatio << std::endl;
        }
    }
}

void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volSlider)
    {
        double gainValue = slider->getValue();
        player->setGain(gainValue);
        std::cout << "Volume slider set to: " << gainValue << std::endl;
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
    return true;
}

void DeckGUI::filesDropped (const juce::StringArray &files, int x, int y)
{
    if (files.size() == 1)
    {
        auto url = juce::URL{juce::File{files[0]}};
        player->loadURL(url);
        waveformDisplay.loadURL(url);
        std::cout << "Loaded file via drag and drop: " << files[0] << std::endl;
    }
}

void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}

void DeckGUI::loadTrack(const juce::String& trackName)
{
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

