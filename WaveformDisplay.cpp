///*
//  ==============================================================================
//
//    WaveformDisplay.cpp
//
//  ==============================================================================

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
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

void WaveformDisplay::paint(juce::Graphics& g)
{
    // Clear the background
    g.fillAll(juce::Colours::darkslategrey);

    // Draw a fancy gradient background
    juce::ColourGradient gradient(juce::Colours::darkgrey, getLocalBounds().toFloat().getTopLeft(),
                                  juce::Colours::black, getLocalBounds().toFloat().getBottomRight(), false);
    g.setGradientFill(gradient);
    g.fillRect(getLocalBounds());

    // Draw the waveform
    g.setColour(juce::Colours::orange);
    if (fileLoaded)
    {
        audioThumb.drawChannel(g,
                               getLocalBounds().reduced(4), // Add some padding
                               0,
                               audioThumb.getTotalLength(),
                               0,
                               1.0f);

        // Draw a playhead indicator
        g.setColour(juce::Colours::cyan);
        auto playheadX = position * getWidth();
        g.drawLine(playheadX, 0.0f, playheadX, (float)getHeight(), 2.0f);
        g.setColour(juce::Colours::black.withAlpha(0.5f));
        g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(2), 4.0f, 1.5f);
    }
    else
    {
        g.setFont(20.0f);
        g.setColour(juce::Colours::white);
        g.drawText("File not loaded...", getLocalBounds(),
                   juce::Justification::centred, true);
    }
}

void WaveformDisplay::resized()
{
    // Optionally adjust any internal layout here if needed
}

void WaveformDisplay::loadURL(juce::URL audioURL)
{
    std::cout << "wfd:loadURL" << std::endl;

    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));
    if (fileLoaded)
    {
        std::cout << "wfd:loaded!" << std::endl;
    }
    else
    {
        std::cout << "wfd: not loaded!" << std::endl;
    }
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    std::cout << "wfd: change received!" << std::endl;

    repaint();
}

void WaveformDisplay::setPositionRelative(double pos)
{
    if (pos >= 0.0 && pos <= 1.0)
    {
        if (pos != position)
        {
            position = pos;
            repaint();
        }
    }
    else
    {
        std::cout << "Invalid position value: " << pos << std::endl;
    }
}

