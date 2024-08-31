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
    
    // setting up treble slider
    trebleSlider.setSliderStyle(juce::Slider::LinearVertical);
    trebleSlider.setRange(-12.0, 12.0);
    trebleSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    trebleSlider.setValue(0.0);
    trebleSlider.setName("Treble");
    trebleSlider.addListener(this);
    addAndMakeVisible(trebleSlider);
    
    // setting up presence slider
    presenceSlider.setSliderStyle(juce::Slider::LinearVertical);
    presenceSlider.setRange(-12.0, 12.0);
    presenceSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    presenceSlider.setValue(0.0);
    presenceSlider.setName("Presence");
    presenceSlider.addListener(this);
    addAndMakeVisible(presenceSlider);
    
    // setting up brilliance slider
    brillianceSlider.setSliderStyle(juce::Slider::LinearVertical);
    brillianceSlider.setRange(-12.0, 12.0);
    brillianceSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    brillianceSlider.setValue(0.0);
    brillianceSlider.setName("Brilliance");
    brillianceSlider.addListener(this);
    addAndMakeVisible(brillianceSlider);
    

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
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Equalizer", getLocalBounds(), juce::Justification::centredTop, true);
}

void EqualizerComponent::resized()
{
    auto area = getLocalBounds();
    auto sliderArea = area.removeFromLeft(area.getWidth() * 0.7);  // Left 70% for sliders
    int sliderWidth = sliderArea.getWidth() / 7; // Divide area for 7 sliders

    // Position sliders in left section
    bassSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
    lowMidSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
    midSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
    highMidSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
    trebleSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
    presenceSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
    brillianceSlider.setBounds(sliderArea);

    // Position buttons in right section
    auto buttonArea = area;  // Remaining area on the right
    bypassButton.setBounds(buttonArea.removeFromTop(40)); // 40px height per button
    resetButton.setBounds(buttonArea.removeFromTop(40));
}

void EqualizerComponent::sliderValueChanged(juce::Slider* slider)
{
    // Handle slider value changes for frequency adjustments
    if (slider == &bassSlider)
    {
        // Adjust bass frequencies
    }
    else if (slider == &lowMidSlider)
    {
        // Adjust low-mid frequencies
    }
    else if (slider == &midSlider)
    {
        // Adjust mid frequencies
    }
    else if (slider == &highMidSlider)
    {
        // Adjust high-mid frequencies
    }
    else if (slider == &trebleSlider)
    {
        // Adjust treble frequencies
    }
    else if (slider == &presenceSlider)
    {
        // Adjust presence frequencies
    }
    else if (slider == &brillianceSlider)
    {
        // Adjust brilliance frequencies
    }
}

void EqualizerComponent::buttonClicked(juce::Button* button)
{
    if (button == &bypassButton)
    {
        // Toggle EQ bypass
        if (bypassButton.getToggleState())
        {
            std::cout << "EQ Bypassed" << std::endl;
        }
        else
        {
            std::cout << "EQ Enabled" << std::endl;
        }
    }
    else if (button == &resetButton)
    {
        // Reset sliders to default positions
        bassSlider.setValue(0.0);
        lowMidSlider.setValue(0.0);
        midSlider.setValue(0.0);
        highMidSlider.setValue(0.0);
        trebleSlider.setValue(0.0);
        presenceSlider.setValue(0.0);
        brillianceSlider.setValue(0.0);
        std::cout << "EQ Reset to default" << std::endl;
    }
}

