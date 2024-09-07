
/*
//  ==============================================================================
//
//    EqualizerComponent.h
//
//  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <juce_dsp/juce_dsp.h>

class DJAudioPlayer;  // Forward declaration to avoid circular dependencies

class EqualizerComponent : public juce::Component,
                           public juce::Slider::Listener,   // handle slider events
                           public juce::Button::Listener,   // handle button events
                           public juce::ComboBox::Listener  // handle ComboBox events
{
public:
    // constructor with referenco to djaudioplayer
    EqualizerComponent(DJAudioPlayer& player);
    // handles cleanup after component destruction
    ~EqualizerComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    // handler for slider value change
    void sliderValueChanged(juce::Slider* slider) override;
    
    // handler for button clicked
    void buttonClicked(juce::Button* button) override;
    
    // handler for combobox
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;
    
    // processing audio through equalizer
    void process(juce::dsp::AudioBlock<float>& audioBlock);

private:
    // updates color for bypass button on a state on/off
    void updateBypassButtonColor();
    
    // helper function for a slider setups
    void setupSlider(juce::Slider& slider, const juce::String& name);
    
    // displays a name for the slider
    void addLabelForSlider(juce::Slider& slider, const juce::String& labelText);
    
    // setup for combobox with available presets
    void setupPresetSelector();
    
    // initialization of filters with default values
    void initializeFilters();
    
    // update for a filters with a new values
    void updateFilter(juce::dsp::IIR::Filter<float>& filter, const juce::dsp::IIR::Coefficients<float>::Ptr& coefficients);
    
    //aplies selected EQ preset for sliders and filters
    void applyPreset(int presetType);

    DJAudioPlayer& player;

    // Sliders for adjustings in EQ
    juce::Slider bassSlider;
    juce::Slider lowMidSlider;
    juce::Slider midSlider;
    juce::Slider highMidSlider;
    juce::Slider trebleSlider;
    juce::Slider presenceSlider;
    juce::Slider brillianceSlider;
    juce::Slider bpmSlider;

    // Buttons to controll EQ state and presets
    juce::TextButton bypassButton;
    juce::TextButton resetButton;
    juce::TextButton rockPresetButton;
    juce::TextButton jazzPresetButton;
    juce::TextButton classicalPresetButton;

    // Preset selector for different EQ presets
    juce::ComboBox presetSelector;

    // Filters for each EQ slider
    juce::dsp::IIR::Filter<float> bassFilter;
    juce::dsp::IIR::Filter<float> lowMidFilter;
    juce::dsp::IIR::Filter<float> midFilter;
    juce::dsp::IIR::Filter<float> highMidFilter;
    juce::dsp::IIR::Filter<float> trebleFilter;
    juce::dsp::IIR::Filter<float> presenceFilter;
    juce::dsp::IIR::Filter<float> brillianceFilter;

    bool isBypassed = false; // Flag for bypassing all filters

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EqualizerComponent)
};

