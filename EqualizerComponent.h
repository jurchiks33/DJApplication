/*
  ==============================================================================

    EqualizerComponent.h


  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <juce_dsp/juce_dsp.h>

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

    /** Slider::Listener **/
    void sliderValueChanged (juce::Slider* slider) override;

    /** Button::Listener **/
    void buttonClicked(juce::Button* button) override;

private:
    // Sliders for different frequency bands
    juce::Slider bassSlider;
    juce::Slider lowMidSlider;
    juce::Slider midSlider;
    juce::Slider highMidSlider;
    juce::Slider trebleSlider;
    juce::Slider presenceSlider;
    juce::Slider brillianceSlider;

    // Text buttons
    juce::TextButton bypassButton;
    juce::TextButton resetButton;

    // Filters for each frequency band
    juce::dsp::IIR::Filter<float> bassFilter;
    juce::dsp::IIR::Filter<float> lowMidFilter;
    juce::dsp::IIR::Filter<float> midFilter;
    juce::dsp::IIR::Filter<float> highMidFilter;
    juce::dsp::IIR::Filter<float> trebleFilter;
    juce::dsp::IIR::Filter<float> presenceFilter;
    juce::dsp::IIR::Filter<float> brillianceFilter;

    // Filter state objects
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
