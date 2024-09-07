/*
============================================================================================================
//DjAudioPlayer.h
============================================================================================================
*/

#pragma once

#include <JuceHeader.h>

class EqualizerComponent;  // Forward declaration of EqualizerComponent

// class that handles loading, playing, manipulating audio files and equalization effects.
class DJAudioPlayer : public juce::AudioSource {
public:
    // constructor to initialize DJAudioPLayer with references
    DJAudioPlayer(juce::AudioFormatManager& formatManager, EqualizerComponent& eqComponent);
    
    //destructor
    ~DJAudioPlayer();

    // prepare audio source for playback
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    
    // fills audiobuffer with next block audio data
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    
    // release resources used by audio source
    void releaseResources() override;

    // load audio file from URL into a player
    void loadURL(juce::URL audioURL);
    
    // sets playback volume for audio source
    void setGain(double gain);
    
    // sets playback speed
    void setSpeed(double ratio);
    
    // sets playback position in seconds
    void setPosition(double posInSec);
    
    // sets playback position relative to total lenght of audio file
    void setPositionRelative(double pos);

    // starts audio playback
    void start();
    
    // stops audio playback
    void stop();
    
    // sets bpm per minute for audio player
    void setBPM(double newBPM);
    
    // gets current bpm for audio player
    double getBPM() const;
    
    // sets players bpm with reference bpm (120)
    void syncBPM();

    // gets current playback position as a relative value between 0.0 and 1.0
    double getPositionRelative();

private:
    // reference to audioformatmanager
    juce::AudioFormatManager& formatManager;
    
    // pointer to audio reader source
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    
    // audio transport source
    juce::AudioTransportSource transportSource;
    
    // resampling source to adjust playback speed
    juce::ResamplingAudioSource resampleSource{&transportSource, false, 2};

    // Reference to EqualizerComponent
    EqualizerComponent& equalizerComponent;

    // default BPM value
    double bpm = 120.0; // Default BPM

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DJAudioPlayer)
};
