/*
  ==============================================================================

    EqualizerComponent.cpp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EqualizerComponent.h"

//==============================================================================
EqualizerComponent::EqualizerComponent()
{
    // setting up low slider
    lowSlider.setSliderStyle(juce::Slider::LinearVertical);
    lowSlider.setRange(-12.0, 12.0);
    lowSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    lowSlider.setValue(0.0);
    lowSlider.setName("Low");
    lowSlider.addListener(this);
    addAndMakeVisible(lowSlider);
    
    // setting up middle slider
    midSlider.setSliderStyle(juce::Slider::LinearVertical);
    midSlider.setRange(-12.0, 12.0);
    midSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    midSlider.setValue(0.0);
    midSlider.setName("Mid");
    midSlider.addListener(this);
    addAndMakeVisible(midSlider);
    
    // setting up high slider
    highSlider.setSliderStyle(juce::Slider::LinearVertical);
    highSlider.setRange(-12.0, 12.0);
    highSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    highSlider.setValue(0.0);
    highSlider.setName("High");
    highSlider.addListener(this);
    addAndMakeVisible(highSlider);

}

EqualizerComponent::~EqualizerComponent()
{
}

void EqualizerComponent::paint (juce::Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Equalizer", getLocalBounds(),
                juce::Justification::centredTop, true);   // draw placeholder text
}

void EqualizerComponent::resized()
{

}
