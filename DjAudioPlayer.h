//DjAudioPlayer.h

#pragma once

#include <JuceHeader.h>
#include "EqualizerComponent.h"

class DJAudioPlayer : public juce::AudioSource {
public:
    DJAudioPlayer(juce::AudioFormatManager& _formatManager, EqualizerComponent& eqComponent);

    ~DJAudioPlayer();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void loadURL(juce::URL audioURL);
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSec);
    void setPositionRelative(double pos);

    void start();
    void stop();

    double getPositionRelative();

private:
    juce::AudioFormatManager& formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    juce::ResamplingAudioSource resampleSource{&transportSource, false, 2};

    EqualizerComponent& equalizerComponent;  // Reference to EqualizerComponent

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DJAudioPlayer)
};

