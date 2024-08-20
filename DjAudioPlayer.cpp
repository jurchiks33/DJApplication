/*
  ==============================================================================

    DjAudioPlayer.cpp
    Created: 14 Aug 2024 10:07:23am
    Author:  Juris Slisans

  ==============================================================================
*/

#include "DjAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer()
{
    
}
DJAudioPlayer::~DJAudioPlayer()
{
    
}

//==============================================================================
void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    formatManager.registerBasicFormats();
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}
void DJAudioPlayer::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    resampleSource.getNextAudioBlock(bufferToFill);
}
void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

void DJAudioPlayer::loadURL(juce::URL audioURL)
{
    // Create an input stream directly from the URL
    std::unique_ptr<juce::InputStream> inputStream(audioURL.createInputStream(false));

    if (inputStream != nullptr)
    {
        auto* reader = formatManager.createReaderFor(std::move(inputStream));
        if (reader != nullptr)
        {
            std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
            transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
            readerSource.reset(newSource.release());
        }
    }
}
void DJAudioPlayer::setGain(double gain)
{
    
}
void DJAudioPlayer::setSpeed(double ratio)
{
    
}
void DJAudioPlayer::setPosition(double posInSec)
{
    
}

void DJAudioPlayer::start()
{
    transportSource.start();
}
void DJAudioPlayer::stop()
{
    transportSource.stop();
}
