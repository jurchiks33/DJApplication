////DjAudioPlayer.cpp
//
//#include "DjAudioPlayer.h"
//#include "EqualizerComponent.h"  // Include EqualizerComponent here
//#include <JuceHeader.h>
//// Ensure all JUCE headers are included
//
//DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& formatManager, EqualizerComponent& eqComponent)
//: formatManager(formatManager), equalizerComponent(eqComponent) 
//{
//}
//
//DJAudioPlayer::~DJAudioPlayer()
//{
//}
//
//void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
//{
//    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
//    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
//}
//
//void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
//{
//    resampleSource.getNextAudioBlock(bufferToFill);
//    
//    juce::dsp::AudioBlock<float> block(*bufferToFill.buffer);
//    equalizerComponent.process(block);
//}
//
//
//void DJAudioPlayer::releaseResources()
//{
//    transportSource.releaseResources();
//    resampleSource.releaseResources();
//}
//
//void DJAudioPlayer::loadURL(juce::URL audioURL)
//{
//    juce::URL::InputStreamOptions options(juce::URL::ParameterHandling::inPostData);
//
//    options.withNumRedirectsToFollow(5)
//           .withConnectionTimeoutMs(10000);
//
//    auto inputStream = audioURL.createInputStream(options);
//
//    if (inputStream != nullptr)
//    {
//        auto* reader = formatManager.createReaderFor(std::move(inputStream));
//        if (reader != nullptr)
//        {
//            auto newSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
//            transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
//            readerSource = std::move(newSource);
//        }
//        else
//        {
//            std::cout << "Failed to create reader for the input stream." << std::endl;
//        }
//    }
//    else
//    {
//        std::cout << "Failed to create input stream from URL." << std::endl;
//    }
//}
//
//
//void DJAudioPlayer::setGain(double gain)
//{
//    if (gain < 0 || gain > 1.0)
//    {
//        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1" << std::endl;
//    }
//    else {
//        transportSource.setGain(gain);
//    }
//}
//
//void DJAudioPlayer::setSpeed(double ratio)
//{
//    if (ratio < 0 || ratio > 100.0)
//    {
//        std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 100" << std::endl;
//    }
//    else {
//        resampleSource.setResamplingRatio(ratio);
//    }
//}
//
//void DJAudioPlayer::setPosition(double posInSec)
//{
//    transportSource.setPosition(posInSec);
//}
//
//void DJAudioPlayer::setPositionRelative(double pos)
//{
//    if (pos < 0 || pos > 1.0)
//    {
//        std::cout << "DJAudioPlayer::setPositionRelative pos should be between 0 and 1" << std::endl;
//    }
//    else {
//        double posInSec = transportSource.getLengthInSeconds() * pos;
//        setPosition(posInSec);
//    }
//}
//
//void DJAudioPlayer::start()
//{
//    transportSource.start();
//}
//
//void DJAudioPlayer::stop()
//{
//    transportSource.stop();
//}
//
//double DJAudioPlayer::getPositionRelative()
//{
//    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
//}
//
//void DJAudioPlayer::setBPM(double newBPM)
//{
//    if (newBPM > 0)
//    {
//        bpm = newBPM;
//        std::cout << "BPM set to " << bpm << std::endl;
//    }
//    else
//    {
//        std::cout << "Invalid BPM value." << std::endl;
//    }
//}
//
//double DJAudioPlayer::getBPM() const
//{
//    return bpm;
//}
//
//void DJAudioPlayer::syncBPM()
//{
//    double referenceBPM = 120.0; 
//    double currentBPM = getBPM();
//    if (currentBPM > 0)
//    {
//        double speedRatio = referenceBPM / currentBPM;
//        setSpeed(speedRatio); // Adjust speed to match the reference BPM
//        std::cout << "Syncing BPM to " << referenceBPM << std::endl;
//    }
//}



//DjAudioPlayer.cpp

#include "DjAudioPlayer.h"
#include "EqualizerComponent.h"  // Include EqualizerComponent here
#include <JuceHeader.h> // Include JUCE headers

DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& formatManager, EqualizerComponent& eqComponent)
    : formatManager(formatManager), equalizerComponent(&eqComponent)  // Initialize with a reference
{
}

DJAudioPlayer::~DJAudioPlayer()
{
}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    resampleSource.getNextAudioBlock(bufferToFill);
    
    if (equalizerComponent != nullptr)  // Check if the EqualizerComponent is set
    {
        juce::dsp::AudioBlock<float> block(*bufferToFill.buffer);
        equalizerComponent->process(block);
    }
}

void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

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

void DJAudioPlayer::setSpeed(double ratio)
{
    if (ratio < 0 || ratio > 100.0)
    {
        std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 100" << std::endl;
    }
    else {
        resampleSource.setResamplingRatio(ratio);
    }
}

void DJAudioPlayer::setPosition(double posInSec)
{
    transportSource.setPosition(posInSec);
}

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

void DJAudioPlayer::start()
{
    transportSource.start();
}

void DJAudioPlayer::stop()
{
    transportSource.stop();
}

double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

void DJAudioPlayer::setBPM(double newBPM)
{
    if (newBPM > 0)
    {
        bpm = newBPM;
        std::cout << "BPM set to " << bpm << std::endl;
    }
    else
    {
        std::cout << "Invalid BPM value." << std::endl;
    }
}

double DJAudioPlayer::getBPM() const
{
    return bpm;
}

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

void DJAudioPlayer::setEqualizerComponent(EqualizerComponent* eqComponent)
{
    if (eqComponent != nullptr)
    {
        equalizerComponent = eqComponent;
    }
}

