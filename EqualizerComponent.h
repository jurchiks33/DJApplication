
//*
//  ==============================================================================
//
//    EqualizerComponent.h
//
//  ==============================================================================
//*/

#pragma once

#include <JuceHeader.h>
#include <juce_dsp/juce_dsp.h>

class DJAudioPlayer;

class EqualizerComponent : public juce::Component,
                           public juce::Slider::Listener,
                           public juce::Button::Listener
{
public:
    EqualizerComponent(DJAudioPlayer& player);
    ~EqualizerComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button* button) override;

    void process(juce::dsp::AudioBlock<float>& audioBlock);
    
private:
    void updateBypassButtonColor();
    
    DJAudioPlayer& player;

    // Sliders
    juce::Slider bassSlider;
    juce::Slider lowMidSlider;
    juce::Slider midSlider;
    juce::Slider highMidSlider;
    juce::Slider trebleSlider;
    juce::Slider presenceSlider;
    juce::Slider brillianceSlider;
    juce::Slider bpmSlider;

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

    bool isBypassed = false; // Flag for bypassing all filters

    void setupSlider(juce::Slider& slider, const juce::String& name);
    void initializeFilters();
    void updateFilter(juce::dsp::IIR::Filter<float>& filter, const juce::dsp::IIR::Coefficients<float>::Ptr& coefficients);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EqualizerComponent)
};
