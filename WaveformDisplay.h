/*
  ==============================================================================

    WaveformDisplay.h
    Created: 22 Aug 2024 11:38:46am
    Author:  Juris Slisans

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
    WaveformDisplay(juce::AudioFormatManager & formatManagerToUse,
                    juce::AudioThumbnailCache & cacheToUse);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void changeListenerCallBack (juce::ChangeBroadcaster *source) override;
    
    void loadURL(juce::URL audioURL);

private:
    juce::AudioThumbnail audioThumb;
    bool fileLoaded;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
