/*
  ==============================================================================

    EqualizerComponent.cpp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EqualizerComponent.h"

//==============================================================================
EqualizerComponent::EqualizerComponent() :
bypassButton("Bypass"), resetButton("Reset")
{
    // setting up bass slider
    bassSlider.setSliderStyle(juce::Slider::LinearVertical);
    bassSlider.setRange(-12.0, 12.0);
    bassSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    bassSlider.setValue(0.0);
    bassSlider.setName("Bass");
    bassSlider.addListener(this);
    addAndMakeVisible(bassSlider);
    
    // setting up low-mid slider
    lowMidSlider.setSliderStyle(juce::Slider::LinearVertical);
    lowMidSlider.setRange(-12.0, 12.0);
    lowMidSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    lowMidSlider.setValue(0.0);
    lowMidSlider.setName("Low-Mid");
    lowMidSlider.addListener(this);
    addAndMakeVisible(lowMidSlider);
    
    // setting up middle slider
    midSlider.setSliderStyle(juce::Slider::LinearVertical);
    midSlider.setRange(-12.0, 12.0);
    midSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    midSlider.setValue(0.0);
    midSlider.setName("Mid");
    midSlider.addListener(this);
    addAndMakeVisible(midSlider);
    
    
    // setting up high-mid slider
    highMidSlider.setSliderStyle(juce::Slider::LinearVertical);
    highMidSlider.setRange(-12.0, 12.0);
    highMidSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    highMidSlider.setValue(0.0);
    highMidSlider.setName("High-Mid");
    highMidSlider.addListener(this);
    addAndMakeVisible(highMidSlider);
    

    //Set round buttons
    bypassButton.setClickingTogglesState(true);
    bypassButton.setButtonText("Bypass");
    bypassButton.addListener(this);
    addAndMakeVisible(bypassButton);
    
    resetButton.setButtonText("reset");
    resetButton.addListener(this);
    addAndMakeVisible(resetButton);

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
    auto area = getLocalBounds();
    int sliderWidth = area.getWidth() / 5;      // Split area in a 5 parts
    
    lowSlider.setBounds(area.removeFromLeft(sliderWidth));
    bypassButton.setBounds(area.removeFromLeft(sliderWidth));   //first button
    midSlider.setBounds(area.removeFromLeft(sliderWidth));
    resetButton.setBounds(area.removeFromLeft(sliderWidth));    //second button
    highSlider.setBounds(area);
}

void EqualizerComponent::sliderValueChanged(juce::Slider* slider)
{
    //slider handling for equalizer
    if (slider == &lowSlider)
    {
        //place for low frequency slider
    }
    else if (slider == &midSlider)
    {
        //place for middle frequency slider
    }
    else if (slider == &highSlider)
    {
        // place for high frequency slider
    }
}

void EqualizerComponent::buttonClicked(juce::Button* button)
{
    if (button == &bypassButton)
    {
        // bypass EQ
        if (bypassButton.getToggleState())
        {
            // code for EQ bypassing
            std::cout << "EQ Bypassed" << std::endl;
        }
        else
        {
            // code for enabling EQ
            std::cout << "EQ Enabled" << std::endl;
        }
    }
    else if (button == &resetButton)
    {
        // Reset EQ sliders to default positions
        lowSlider.setValue(0.0);
        midSlider.setValue(0.0);
        highSlider.setValue(0.0);
        std::cout << "EQ Reset to default" << std::endl;
    }
}

