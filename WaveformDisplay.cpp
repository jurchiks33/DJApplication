/*
==========================================================================
//    WaveformDisplay.cpp
==========================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

// constructor for waveform display
WaveformDisplay::WaveformDisplay(juce::AudioFormatManager& formatManagerToUse,
                                 juce::AudioThumbnailCache& cacheToUse)
    : audioThumb(1000, formatManagerToUse, cacheToUse),
      fileLoaded(false),
      position(0)
{
    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

// overrides paint method to draw waveform display
void WaveformDisplay::paint(juce::Graphics& g)
{
    // Clear the background
    g.fillAll(juce::Colours::darkslategrey);

    // Draw gradient background
    juce::ColourGradient gradient(juce::Colours::darkgrey, 
                                  getLocalBounds().toFloat().getTopLeft(),
                                  juce::Colours::black, 
                                  getLocalBounds().toFloat().getBottomRight(),
                                  false);
    g.setGradientFill(gradient);
    g.fillRect(getLocalBounds());

    // set color for waveform
    g.setColour(juce::Colours::azure);
    if (fileLoaded)
    {
        audioThumb.drawChannel(g,
                               getLocalBounds().reduced(4), // Add some padding
                               0,
                               audioThumb.getTotalLength(),
                               0,
                               1.0f);

        // Draw a playhead indicator and style it
        g.setColour(juce::Colours::cyan);
        auto playheadX = position * getWidth();
        g.drawLine(playheadX, 0.0f, playheadX, (float)getHeight(), 2.0f);
        
        // draw rounded rectangle around waveform
        g.setColour(juce::Colours::black.withAlpha(0.5f));
        g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(2), 4.0f, 1.5f);
    }
    else    // if no file uploaded display a message
    {
        g.setFont(20.0f);
        g.setColour(juce::Colours::white);
        g.drawText("File not loaded...", getLocalBounds(),
                   juce::Justification::centred, true);
    }
}

void WaveformDisplay::resized()
{
    // to adjust any internal layout here if needed
}

// loads file from URL into waveform display
void WaveformDisplay::loadURL(juce::URL audioURL)
{
    std::cout << "wfd:loadURL" << std::endl;

    audioThumb.clear(); // clear any existing audio in the thumbnail
    fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));
    if (fileLoaded) // check if file successfully loaded
    {
        std::cout << "wfd:loaded!" << std::endl;
    }
    else
    {
        std::cout << "wfd: not loaded!" << std::endl;
    }
}

// callback which triggers when audio thumbnail is changed
void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    std::cout << "wfd: change received!" << std::endl;

    repaint();  // redraw component to display new changes
}

// sets relative position of the playhead within waveform display
void WaveformDisplay::setPositionRelative(double pos)
{
    if (pos >= 0.0 && pos <= 1.0)   // ensure position range between 0.0 and 1.0
    {
        if (pos != position)
        {
            position = pos;
            repaint();
        }
    }
    else
    {
        std::cout << "Invalid position value: " << pos << std::endl;    // log error if position is invalid
    }
}

