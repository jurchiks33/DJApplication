/*
  ==============================================================================

    EqualizerComponent.h


  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class EqualizerComponent  : public juce::Component,
                            public juce::Slider::Listener
{
public:
    EqualizerComponent();
    ~EqualizerComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /**Slider::Listener**/
    void sliderValueChanged (juce::Slider* slider) override;

private:
    juce::Slider lowSlider;     //low frequency slider
    juce::Slider midSlider;     // middle frequency slider
    juce::Slider highSlider;    // high frequency slider
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EqualizerComponent)
};
