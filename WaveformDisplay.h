/*
  ==============================================================================
    WaveformDisplay.h
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component,
                         public juce::ChangeListener
{
public:
    // constructor which takes referances
    WaveformDisplay(juce::AudioFormatManager & formatManagerToUse,
                    juce::AudioThumbnailCache & cacheToUse);
    // destructor
    ~WaveformDisplay() override;

    // override paint method from component
    void paint (juce::Graphics&) override;
    
    // override resized method from component
    void resized() override;
    
    // callback when audio thumbnail send change notification
    void changeListenerCallback (juce::ChangeBroadcaster *source) override;
    
    // loads audio file from URL and prepares it to display
    void loadURL(juce::URL audioURL);
    
    /**set the relative position of the playhead**/
    void setPositionRelative(double pos);

private:
    juce::AudioThumbnail audioThumb;    // generate and hold visual representation of the audio waveform
    bool fileLoaded;                    // indicator for audio file successfull load
    double position;                    // for current position of the playhead showing from total waveform width
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
