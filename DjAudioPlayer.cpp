/*
===============================================================================
//DjAudioPlayer.cpp
===============================================================================
*/



#include "DjAudioPlayer.h"
#include "EqualizerComponent.h"
#include <JuceHeader.h>

// constructor for initializations
DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& formatManager,
                             EqualizerComponent& eqComponent) 
: formatManager(formatManager), equalizerComponent(eqComponent)
{
}

// destructor
DJAudioPlayer::~DJAudioPlayer()
{
}

// prepare audio player for playback
void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);  // prepare transportsource for playback
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);   // prepare resamplesource for playback
}

// get next audioblock of data to be played
void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    resampleSource.getNextAudioBlock(bufferToFill);
    
    juce::dsp::AudioBlock<float> block(*bufferToFill.buffer);
    equalizerComponent.process(block);
}

// release any resources held by audio sources
void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

// loads audio file from URL into a player
void DJAudioPlayer::loadURL(juce::URL audioURL)
{
    juce::URL::InputStreamOptions options(juce::URL::ParameterHandling::inPostData);

    options.withNumRedirectsToFollow(5)
           .withConnectionTimeoutMs(10000);

    auto inputStream = audioURL.createInputStream(options);

    if (inputStream != nullptr)
    {
        auto* reader = formatManager.createReaderFor(std::move(inputStream));
        if (reader != nullptr)
        {
            auto newSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
            transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
            readerSource = std::move(newSource);
        }
        else
        {
            std::cout << "Failed to create reader for the input stream." << std::endl;
        }
    }
    else
    {
        std::cout << "Failed to create input stream from URL." << std::endl;
    }
}

// sets playback volume for the player
void DJAudioPlayer::setGain(double gain)
{
    if (gain < 0 || gain > 1.0)
    {
        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1" << std::endl;
    }
    else {
        transportSource.setGain(gain);
    }
}

// sets playback speed for audio
void DJAudioPlayer::setSpeed(double ratio)
{
    if (ratio <= 0)
    {
        std::cout << "Speed ratio must be positive. Current ratio: " << ratio << std::endl;
        return;
    }

    ratio = juce::jlimit(0.5, 2.0, ratio);

    // Set the resampling ratio for speed adjustment
    resampleSource.setResamplingRatio(ratio);
    std::cout << "Set speed ratio to: " << ratio << std::endl;
}

// sets playback position in seconds
void DJAudioPlayer::setPosition(double posInSec)
{
    transportSource.setPosition(posInSec);
}

// sets playback position relative to total audio file lenght
void DJAudioPlayer::setPositionRelative(double pos)
{
    if (pos < 0 || pos > 1.0)
    {
        std::cout << "DJAudioPlayer::setPositionRelative pos should be between 0 and 1" << std::endl;
    }
    else {
        double posInSec = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSec);
    }
}

// starts audio playback
void DJAudioPlayer::start()
{
    transportSource.start();
}

// stops audio playback
void DJAudioPlayer::stop()
{
    transportSource.stop();
}

// gets current playback position between 0.0 and 1.0
double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

// sets BPM (Beats per minute) for the player and ensures they are positive
void DJAudioPlayer::setBPM(double newBPM)
{
    if (newBPM > 0)
    {
        bpm = newBPM;   // sets BPM
        std::cout << "BPM set to " << bpm << std::endl;
    }
    else
    {
        std::cout << "Invalid BPM value." << std::endl;
    }
}

// gets current bpm from the player
double DJAudioPlayer::getBPM() const
{
    return bpm; // returns current bpm
}

// adjusts playback speed to match reference bpm
void DJAudioPlayer::syncBPM()
{
    double referenceBPM = 120.0;
    double currentBPM = getBPM();
    if (currentBPM > 0)
    {
        double speedRatio = referenceBPM / currentBPM;
        setSpeed(speedRatio); // Adjust speed to match the reference BPM
        std::cout << "Syncing BPM to " << referenceBPM << std::endl;
    }
}

