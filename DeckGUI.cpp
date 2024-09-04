////DeckGUI.cpp
//
//#include "DeckGUI.h"
//#include "DjAudioPlayer.h"
//#include "WaveformDisplay.h"
//#include <JuceHeader.h>
//
////==============================================================================
//DeckGUI::DeckGUI(DJAudioPlayer* _player,
//                 juce::AudioFormatManager & formatManagerToUse,
//                 juce::AudioThumbnailCache & cacheToUse) : player(_player),
//                    waveformDisplay(formatManagerToUse, cacheToUse)
//{
//    addAndMakeVisible(playButton);
//    addAndMakeVisible(stopButton);
//    addAndMakeVisible(loadButton);
//    addAndMakeVisible(syncButton); // Add the Sync button
//
//    addAndMakeVisible(volSlider);
//    addAndMakeVisible(speedSlider);
//    addAndMakeVisible(posSlider);
//    addAndMakeVisible(waveformDisplay);
//    
//    playButton.addListener(this);
//    stopButton.addListener(this);
//    loadButton.addListener(this);
//    syncButton.addListener(this); // Add listener for Sync button
//
//    volSlider.addListener(this);
//    speedSlider.addListener(this);
//    posSlider.addListener(this);
//
//    volSlider.setRange(0.0, 1.0);
//    speedSlider.setRange(0.0, 100.0);
//    posSlider.setRange(0.0, 1.0);
//    
//    startTimer(500);
//}
//
//DeckGUI::~DeckGUI()
//{
//    stopTimer();
//}
//
//void DeckGUI::paint (juce::Graphics& g)
//{
//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
//    g.setColour (juce::Colours::grey);
//    g.drawRect (getLocalBounds(), 1);
//    g.setColour (juce::Colours::white);
//    g.setFont(juce::Font(14.0f));
//    g.drawText ("DeckGUI", getLocalBounds(),
//                juce::Justification::centred, true);
//}
//
//void DeckGUI::resized()
//{
//    double rowH = getHeight() / 9;
//    playButton.setBounds(0, 0, getWidth(), rowH);
//    stopButton.setBounds(0, rowH, getWidth(), rowH);
//    syncButton.setBounds(0, rowH * 2, getWidth(), rowH); // Set bounds for Sync button
//
//    volSlider.setBounds(0, rowH * 3, getWidth(), rowH);
//    speedSlider.setBounds(0, rowH * 4, getWidth(), rowH);
//    posSlider.setBounds(0, rowH * 5, getWidth(), rowH);
//    waveformDisplay.setBounds(0, rowH * 6, getWidth(), rowH * 2);
//    loadButton.setBounds(0, rowH * 8, getWidth(), rowH);
//    
//    //debugging bounds
//    std::cout << "Load button bounds: " << loadButton.getBounds().toString() << std::endl;
//
//}
//
//
//void DeckGUI::buttonClicked(juce::Button* button)
//{
//    if (button == &playButton)
//    {
//        std::cout << "Play button was clicked " << std::endl;
//        player->start();  // Start playing
//    }
//    else if (button == &stopButton)
//    {
//        std::cout << "Stop button was clicked " << std::endl;
//        player->stop();  // Stop playing
//    }
//    else if (button == &loadButton)
//    {
//        std::cout << "Load button was clicked" << std::endl;
//        juce::FileChooser chooser("Select an audio file to load...", {}, "*.mp3;*.wav;*.aiff");
//        chooser.launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
//                            [this](const juce::FileChooser& fc)
//        {
//            std::cout << "FileChooser callback triggered." << std::endl;
//            auto result = fc.getResult();
//
//            if (result.existsAsFile())
//            {
//                std::cout << "Selected file: " << result.getFullPathName() << std::endl;
//                player->loadURL(juce::URL{result});
//                waveformDisplay.loadURL(juce::URL{result});
//            }
//            else
//            {
//                std::cout << "No file was selected or the file does not exist." << std::endl;
//            }
//        });
//    }
//
//    else if (button == &syncButton)
//    {
//        std::cout << "Sync button was clicked " << std::endl;
//
//        // Retrieve the BPM from the other deck
//        double targetBPM = deck2 ? deck2->getPlayerBPM() : 120.0; // Ensure deck2 is correctly set up
//        double currentBPM = player->getBPM();
//
//        std::cout << "Current BPM: " << currentBPM << ", Target BPM: " << targetBPM << std::endl;
//
//        if (currentBPM > 0 && targetBPM > 0)
//        {
//            double speedRatio = targetBPM / currentBPM;
//            player->setSpeed(speedRatio); // Adjust speed without resetting position
//            std::cout << "Adjusted speed to ratio: " << speedRatio << std::endl;
//        }
//    }
//}
//
//
//
//void DeckGUI::sliderValueChanged(juce::Slider* slider)
//{
//    if (slider == &volSlider)
//    {
//        player->setGain(slider->getValue());
//    }
//    else if (slider == &speedSlider)
//    {
//        player->setSpeed(slider->getValue());
//    }
//    else if (slider == &posSlider)
//    {
//        player->setPositionRelative(slider->getValue());
//    }
//}
//
//bool DeckGUI::isInterestedInFileDrag(const juce::StringArray &files)
//{
//    std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
//    return true;
//}
//
//void DeckGUI::filesDropped (const juce::StringArray &files, int x, int y)
//{
//    std::cout << "DeckGUI::filesDropped" << std::endl;
//    if (files.size() == 1)
//    {
//        auto url = juce::URL{juce::File{files[0]}};
//        player->loadURL(url);
//        waveformDisplay.loadURL(url);
//        std::cout << "Loaded file via drag and drop: " << files[0] << std::endl;
//    }
//}
//
//void DeckGUI::timerCallback()
//{
//    waveformDisplay.setPositionRelative(player->getPositionRelative());
//}
//
//void DeckGUI::loadTrack(const juce::String& trackName)
//{
//    // Logic to find the corresponding URL for the given track name
//    juce::File audioFile(trackName);
//    
//    if (audioFile.existsAsFile())
//    {
//        juce::URL audioURL(audioFile);
//        player->loadURL(audioURL);
//        waveformDisplay.loadURL(audioURL);
//        std::cout << "Loading track into Deck: " << trackName << std::endl;
//    }
//    else
//    {
//        std::cout << "File does not exist: " << trackName << std::endl;
//    }
//}
//
//void DeckGUI::loadTrack(const juce::URL& audioURL)
//{
//    player->loadURL(audioURL);
//    waveformDisplay.loadURL(audioURL);
//}


// DeckGUI.cpp

#include "DeckGUI.h"
#include "DjAudioPlayer.h"
#include "WaveformDisplay.h"
#include <JuceHeader.h>

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 juce::AudioFormatManager & formatManagerToUse,
                 juce::AudioThumbnailCache & cacheToUse) : player(_player),
                    waveformDisplay(formatManagerToUse, cacheToUse)
{
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(syncButton); // Add the Sync button

    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(waveformDisplay);
    
    playButton.addListener(this);
    stopButton.addListener(this);
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
    g.setFont(juce::Font(14.0f)); // Correct font usage
    g.drawText ("DeckGUI", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    double rowH = getHeight() / 8; // Adjusted division since "Load" button is removed
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    syncButton.setBounds(0, rowH * 2, getWidth(), rowH); // Set bounds for Sync button

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
        player->start();  // Start playing
    }
    else if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->stop();  // Stop playing
    }
    else if (button == &syncButton)
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
    std::cout << "DeckGUI::filesDropped" << std::endl;
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

