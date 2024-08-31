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
    juce::Slider bassSlider;     // Low frequency (Bass)
    juce::Slider lowMidSlider;   // Low-mid frequencies
    juce::Slider midSlider;      // Mid frequencies
    juce::Slider highMidSlider;  // High-mid frequencies
    juce::Slider trebleSlider;   // High frequencies (Treble)
    juce::Slider presenceSlider; // Presence frequencies
    juce::Slider brillianceSlider; // High frequencies (Brilliance)
    
    juce::TextButton bypassButton;  // Bypass EQ
    juce::TextButton resetButton;   // Reset EQ settings
    
    // filters for equalizer frequency sliders
    juce::dsp::IIR::Filter<float> bassFilter;
    juce::dsp::IIR::Filter<float> lowMidFilter;
    juce::dsp::IIR::Filter<float> midFilter;
    juce::dsp::IIR::Filter<float> highMidFilter;
    juce::dsp::IIR::Filter<float> trebleFilter;
    juce::dsp::IIR::Filter<float> presenceFilter;
    juce::dsp::IIR::Filter<float> brillianceFilter;
    
    // filter state objects
    juce::dsp::IIR::Coefficients<float>::Ptr bassCoefficients;
    juce::dsp::IIR::Coefficients<float>::Ptr lowMidCoefficients;
    juce::dsp::IIR::Coefficients<float>::Ptr midCoefficients;
    juce::dsp::IIR::Coefficients<float>::Ptr highMidCoefficients;
    juce::dsp::IIR::Coefficients<float>::Ptr trebleCoefficients;
    juce::dsp::IIR::Coefficients<float>::Ptr presenceCoefficients;
    juce::dsp::IIR::Coefficients<float>::Ptr brillianceCoefficients;
    
    void updateFilterCoefficients();
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EqualizerComponent)
};
