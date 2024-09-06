

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
    // Create a gradient background
    juce::ColourGradient gradient(juce::Colours::darkslateblue,
                                  0, 0,
                                  juce::Colours::midnightblue,
                                  getWidth(), getHeight(),
                                  false);

    // Fill the background with the gradient
    g.setGradientFill(gradient);
    g.fillAll();

    // Optional: Add a border with a subtle shadow effect
    g.setColour(juce::Colours::black.withAlpha(0.6f));
    g.drawRect(getLocalBounds(), 1);

    // Optional: Add a drop shadow effect
    juce::DropShadow shadow(juce::Colours::black.withAlpha(0.3f), 10, {0, 2});
    shadow.drawForRectangle(g, getLocalBounds().reduced(2));

    // Optional: Add a stylish outline or pattern if desired
    g.setColour(juce::Colours::whitesmoke.withAlpha(0.2f));
    for (int i = 0; i < getWidth(); i += 20)
    {
        g.drawLine(i, 0, i, getHeight(), 0.5f);
    }
}

void DeckGUI::resized()
{
    // Define the new height and width for the buttons
    int buttonHeight = getHeight() / 8;  // Adjust the button height proportionally
    int buttonWidth = getWidth();        // Full width of the component

    // Add padding space for positioning
    int padding = 1;  // Space between elements

    // Position the buttons with the new dimensions
    playButton.setBounds(padding, padding, buttonWidth - 2 * padding, buttonHeight - padding);  // Adjusted size and padding
    stopButton.setBounds(padding, playButton.getBottom() + padding, buttonWidth - 2 * padding, buttonHeight - padding);
    syncButton.setBounds(padding, stopButton.getBottom() + padding, buttonWidth - 2 * padding, buttonHeight - padding);

    // Extra space below SYNC button
    int extraSpace = 20;

    // Position sliders below buttons with extra space
    volSlider.setBounds(padding, syncButton.getBottom() + extraSpace, buttonWidth - 2 * padding, buttonHeight);
    posSlider.setBounds(padding, volSlider.getBottom() + padding, buttonWidth - 2 * padding, buttonHeight);

    // Increase the height of the waveform display and add additional space to move it down
    int waveformHeight = buttonHeight * 2;  // Increase height as desired
    int waveformYOffset = 10; // Set the offset value in pixels (about 1 cm depending on screen DPI)

    // Position waveform display below sliders with additional offset
    waveformDisplay.setBounds(padding, posSlider.getBottom() + padding + waveformYOffset, buttonWidth - 2 * padding, waveformHeight);
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
