/*
  ==============================================================================

    EqualizerComponent.h


  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <juce_dsp/juce_dsp.h>

class EqualizerComponent : public juce::Component,
                           public juce::Slider::Listener,
                           public juce::Button::Listener
{
public:
    EqualizerComponent();
    ~EqualizerComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button* button) override;

    void process(juce::dsp::AudioBlock<float>& audioBlock);

private:
    // Sliders
    juce::Slider bassSlider;
    juce::Slider lowMidSlider;
    juce::Slider midSlider;
    juce::Slider highMidSlider;
    juce::Slider trebleSlider;
    juce::Slider presenceSlider;
    juce::Slider brillianceSlider;
    juce::Slider bpmSlider; // New BPM slider

    // Buttons
    juce::TextButton bypassButton;
    juce::TextButton resetButton;

    // Filters
    juce::dsp::IIR::Filter<float> bassFilter;
    juce::dsp::IIR::Filter<float> lowMidFilter;
    juce::dsp::IIR::Filter<float> midFilter;
    juce::dsp::IIR::Filter<float> highMidFilter;
    juce::dsp::IIR::Filter<float> trebleFilter;
    juce::dsp::IIR::Filter<float> presenceFilter;
    juce::dsp::IIR::Filter<float> brillianceFilter;

    // Helper functions
    void setupSlider(juce::Slider& slider, const juce::String& name);
    void initializeFilters();
    void updateFilter(juce::dsp::IIR::Filter<float>& filter, const juce::dsp::IIR::Coefficients<float>::Ptr& coefficients);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EqualizerComponent)
};
