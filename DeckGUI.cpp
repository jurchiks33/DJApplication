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
    addAndMakeVisible(posSlider);
    addAndMakeVisible(waveformDisplay);
    
    // Add button listeners
    playButton.addListener(this);
    stopButton.addListener(this);
    syncButton.addListener(this);

    // Add slider listeners
    volSlider.addListener(this);
    posSlider.addListener(this);

    // Set slider ranges
    volSlider.setRange(0.0, 1.0);
    posSlider.setRange(0.0, 1.0);
    
    // Set initial values
    volSlider.setValue(1.0); // Start with volume at 1 (full volume)
    
    // Style sliders
    volSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    volSlider.setColour(juce::Slider::thumbColourId, juce::Colours::aqua);
    volSlider.setColour(juce::Slider::trackColourId, juce::Colours::darkgrey);
    volSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::black);

    posSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    posSlider.setColour(juce::Slider::thumbColourId, juce::Colours::lightblue);
    posSlider.setColour(juce::Slider::trackColourId, juce::Colours::darkgrey);
    posSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::black);

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
//
//void DeckGUI::resized()
//{
//    double rowH = getHeight() / 6; // Adjusted height division for 2 sliders
//
//    playButton.setBounds(0, 0, getWidth(), rowH);
//    stopButton.setBounds(0, rowH, getWidth(), rowH);
//    syncButton.setBounds(0, rowH * 2, getWidth(), rowH);
//
//    volSlider.setBounds(0, rowH * 3, getWidth(), rowH);
//    posSlider.setBounds(0, rowH * 4, getWidth(), rowH);
//    waveformDisplay.setBounds(0, rowH * 5, getWidth(), rowH);
//}

void DeckGUI::resized()
{
    // Define the new height and width for the buttons
    int buttonHeight = getHeight() / 7;  // Adjust the button height proportionally
    int buttonWidth = getWidth();        // Full width of the component

    // Add padding space for positioning
    int padding = 10;  // Space between elements

    // Position the buttons with the new dimensions
    playButton.setBounds(padding, padding, buttonWidth - 2 * padding, buttonHeight - padding);  // Adjusted size and padding
    stopButton.setBounds(padding, playButton.getBottom() + padding, buttonWidth - 2 * padding, buttonHeight - padding);
    syncButton.setBounds(padding, stopButton.getBottom() + padding, buttonWidth - 2 * padding, buttonHeight - padding);

    // Extra space below SYNC button
    int extraSpace = 20;

    // Position sliders below buttons with extra space
    volSlider.setBounds(padding, syncButton.getBottom() + extraSpace, buttonWidth - 2 * padding, buttonHeight);
    posSlider.setBounds(padding, volSlider.getBottom() + padding, buttonWidth - 2 * padding, buttonHeight);

    // Position waveform display below sliders
    waveformDisplay.setBounds(padding, posSlider.getBottom() + padding, buttonWidth - 2 * padding, getHeight() - posSlider.getBottom() - 2 * padding);
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

