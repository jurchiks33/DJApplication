//DjAudioPlayer.h

#pragma once

#include <JuceHeader.h>

class EqualizerComponent;  // Forward declaration of EqualizerComponent

class DJAudioPlayer : public juce::AudioSource {
public:
    DJAudioPlayer(juce::AudioFormatManager& formatManager, EqualizerComponent& eqComponent);
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
    
    void setBPM(double newBPM);
    double getBPM() const;
    void syncBPM();

    double getPositionRelative();

private:
    juce::AudioFormatManager& formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    juce::ResamplingAudioSource resampleSource{&transportSource, false, 2};

    EqualizerComponent& equalizerComponent;  // Reference to EqualizerComponent

    double bpm = 120.0; // Default BPM

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DJAudioPlayer)
};
