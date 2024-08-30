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
                            public juce::Slider::Listener,
                            public juce::Button::Listener
{
public:
    EqualizerComponent();
    ~EqualizerComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /**Slider::Listener**/
    void sliderValueChanged (juce::Slider* slider) override;

    /**Button::Listener**/
    void buttonClicked(juce::Button* button) override;
    
private:
    juce::Slider lowSlider;     //low frequency slider
    juce::Slider midSlider;     // middle frequency slider
    juce::Slider highSlider;    // high frequency slider
    
    juce::TextButton bypassButton;  // Bypass EQ
    juce::TextButton resetButton;   // Reset EQ settings
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EqualizerComponent)
};
