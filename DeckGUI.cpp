
/*
==============================================================================
// DeckGUI.cpp
==============================================================================
*/
 
#include "DeckGUI.h"
#include "DjAudioPlayer.h"
#include "WaveformDisplay.h"
#include <JuceHeader.h>

// constructor for initialization with DjAudioPlayer, AudioFormatManager and AudioThumbnailCache
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
    playButton.setColour(juce::TextButton::buttonColourId, 
                         juce::Colours::green);
    stopButton.setColour(juce::TextButton::buttonColourId, 
                         juce::Colours::coral);
    syncButton.setColour(juce::TextButton::buttonColourId, 
                         juce::Colours::lightblue);

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
    
    // Style volume sliders
    volSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    volSlider.setColour(juce::Slider::thumbColourId, 
                        juce::Colours::aqua);
    volSlider.setColour(juce::Slider::trackColourId, 
                        juce::Colours::darkgrey);
    volSlider.setColour(juce::Slider::backgroundColourId, 
                        juce::Colours::black);

    // style position slyders
    posSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    posSlider.setColour(juce::Slider::thumbColourId, 
                        juce::Colours::lightblue);
    posSlider.setColour(juce::Slider::trackColourId, 
                        juce::Colours::darkgrey);
    posSlider.setColour(juce::Slider::backgroundColourId, 
                        juce::Colours::black);
    // timer with interval 500ms for waveform position update
    startTimer(500);
}

// destructor to stop timer when deckgui is destroyed
DeckGUI::~DeckGUI()
{
    stopTimer();
}

//styling for DeckGUI
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

    // Add a border with a subtle shadow effect
    g.setColour(juce::Colours::black.withAlpha(0.6f));
    g.drawRect(getLocalBounds(), 1);

    // Add a drop shadow effect
    juce::DropShadow shadow(juce::Colours::black.withAlpha(0.3f), 10, {0, 2});
    shadow.drawForRectangle(g, getLocalBounds().reduced(2));

    // Add a stylish outline or pattern if desired
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
    playButton.setBounds(padding, 
                         padding,
                         buttonWidth - 2 * padding,
                         buttonHeight - padding);  // Adjusted size and padding
    stopButton.setBounds(padding, 
                         playButton.getBottom() + padding,
                         buttonWidth - 2 * padding,
                         buttonHeight - padding);
    syncButton.setBounds(padding, 
                         stopButton.getBottom() + padding,
                         buttonWidth - 2 * padding,
                         buttonHeight - padding);

    // Extra space below SYNC button
    int extraSpace = 20;

    // Position sliders below buttons with extra space
    volSlider.setBounds(padding, 
                        syncButton.getBottom() + extraSpace,
                        buttonWidth - 2 * padding, 
                        buttonHeight);
    posSlider.setBounds(padding, 
                        volSlider.getBottom() + padding,
                        buttonWidth - 2 * padding,
                        buttonHeight);

    // Increase the height of the waveform display and add additional space to move it down
    int waveformHeight = buttonHeight * 2;  // Increase height as needed
    int waveformYOffset = 10; // Set the offset value in pixels (about 1 cm depending on screen DPI)

    // Position waveform display below sliders with additional offset
    waveformDisplay.setBounds(padding, 
                              posSlider.getBottom() + padding + waveformYOffset,
                              buttonWidth - 2 * padding,
                              waveformHeight);
}

// handles button clicking events
void DeckGUI::buttonClicked(juce::Button* button)
{
    if (button == &playButton)  // play button
    {
        std::cout << "Play button was clicked " << std::endl;
        player->start();    // start player
    }
    else if (button == &stopButton) // stop button
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->stop();
    }
    else if (button == &syncButton) //sync button
    {
        std::cout << "Sync button was clicked " << std::endl;

        // sync current BPM with target BPM
        double targetBPM = deck2 ? deck2->getPlayerBPM() : 120.0;   // default bpm 120
        double currentBPM = player->getBPM();

        std::cout << "Current BPM: " << currentBPM << ", Target BPM: " << targetBPM << std::endl;

        //  adjust speed if both BPM values are valid
        if (currentBPM > 0 && targetBPM > 0)
        {
            double speedRatio = targetBPM / currentBPM; // calculate speed ratio
            player->setSpeed(speedRatio);   // adjust players speed to match target BPM
            std::cout << "Adjusted speed to ratio: " << speedRatio << std::endl;
        }
    }
}

// handler for sslider value changes
void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volSlider)   // volume slider
    {
        double gainValue = slider->getValue();  // get current value
        player->setGain(gainValue);             // set players gain
        std::cout << "Volume slider set to: " << gainValue << std::endl;
    }
    else if (slider == &posSlider)  // position slider
    {
        player->setPositionRelative(slider->getValue());    // set players position relative to track lenght
    }
}

// file drag events
bool DeckGUI::isInterestedInFileDrag(const juce::StringArray &files)
{
    return true;
}

// handles files dropped in DeckGUI
void DeckGUI::filesDropped (const juce::StringArray &files, int x, int y)
{
    if (files.size() == 1)  // if one file is dropped
    {
        auto url = juce::URL{juce::File{files[0]}}; // create URL from file path
        player->loadURL(url);           // load file into player
        waveformDisplay.loadURL(url);   // load file into waveform display
        std::cout << "Loaded file via drag and drop: " << files[0] << std::endl;
    }
}

// timer callback to update playheads position in waveform display
void DeckGUI::timerCallback()
{
    // sycn waveform display with players position
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}

// load track using file path
void DeckGUI::loadTrack(const juce::String& trackName)
{
    juce::File audioFile(trackName);    // create file object
    
    if (audioFile.existsAsFile())       // check if file exists
    {
        juce::URL audioURL(audioFile);  // convert file into URL
        player->loadURL(audioURL);      // load URL into player
        waveformDisplay.loadURL(audioURL);  // load URL into waveform display
        std::cout << "Loading track into Deck: " << trackName << std::endl;
    }
    else
    {
        std::cout << "File does not exist: " << trackName << std::endl;
    }
}

// load tracks using URL
void DeckGUI::loadTrack(const juce::URL& audioURL)
{
    player->loadURL(audioURL);
    waveformDisplay.loadURL(audioURL);
}
