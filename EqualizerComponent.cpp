/*
  ==============================================================================

    EqualizerComponent.cpp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EqualizerComponent.h"
#include <juce_dsp/juce_dsp.h>

//==============================================================================
EqualizerComponent::EqualizerComponent() :
    bypassButton("Bypass"), resetButton("Reset")
{
    // Initialize sliders
    bassSlider.setSliderStyle(juce::Slider::LinearVertical);
    bassSlider.setRange(-12.0, 12.0);
    bassSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    bassSlider.setValue(0.0);
    bassSlider.setName("Bass");
    bassSlider.addListener(this);
    addAndMakeVisible(bassSlider);

    lowMidSlider.setSliderStyle(juce::Slider::LinearVertical);
    lowMidSlider.setRange(-12.0, 12.0);
    lowMidSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    lowMidSlider.setValue(0.0);
    lowMidSlider.setName("Low-Mid");
    lowMidSlider.addListener(this);
    addAndMakeVisible(lowMidSlider);

    midSlider.setSliderStyle(juce::Slider::LinearVertical);
    midSlider.setRange(-12.0, 12.0);
    midSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    midSlider.setValue(0.0);
    midSlider.setName("Mid");
    midSlider.addListener(this);
    addAndMakeVisible(midSlider);

    highMidSlider.setSliderStyle(juce::Slider::LinearVertical);
    highMidSlider.setRange(-12.0, 12.0);
    highMidSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    highMidSlider.setValue(0.0);
    highMidSlider.setName("High-Mid");
    highMidSlider.addListener(this);
    addAndMakeVisible(highMidSlider);

    trebleSlider.setSliderStyle(juce::Slider::LinearVertical);
    trebleSlider.setRange(-12.0, 12.0);
    trebleSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    trebleSlider.setValue(0.0);
    trebleSlider.setName("Treble");
    trebleSlider.addListener(this);
    addAndMakeVisible(trebleSlider);

    presenceSlider.setSliderStyle(juce::Slider::LinearVertical);
    presenceSlider.setRange(-12.0, 12.0);
    presenceSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    presenceSlider.setValue(0.0);
    presenceSlider.setName("Presence");
    presenceSlider.addListener(this);
    addAndMakeVisible(presenceSlider);

    brillianceSlider.setSliderStyle(juce::Slider::LinearVertical);
    brillianceSlider.setRange(-12.0, 12.0);
    brillianceSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    brillianceSlider.setValue(0.0);
    brillianceSlider.setName("Brilliance");
    brillianceSlider.addListener(this);
    addAndMakeVisible(brillianceSlider);

    // Setup round buttons
    bypassButton.setClickingTogglesState(true);
    bypassButton.setButtonText("Bypass");
    bypassButton.addListener(this);
    addAndMakeVisible(bypassButton);

    resetButton.setButtonText("Reset");
    resetButton.addListener(this);
    addAndMakeVisible(resetButton);

    // Initialize filter coefficients
    bassCoefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(44100, 100.0f, 0.707f, juce::Decibels::decibelsToGain(0.0f));
    bassFilter.coefficients = bassCoefficients;

    lowMidCoefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 250.0f, 0.707f, juce::Decibels::decibelsToGain(0.0f));
    lowMidFilter.coefficients = lowMidCoefficients;

    midCoefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 500.0f, 0.707f, juce::Decibels::decibelsToGain(0.0f));
    midFilter.coefficients = midCoefficients;

    highMidCoefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 1000.0f, 0.707f, juce::Decibels::decibelsToGain(0.0f));
    highMidFilter.coefficients = highMidCoefficients;

    trebleCoefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(44100, 2000.0f, 0.707f, juce::Decibels::decibelsToGain(0.0f));
    trebleFilter.coefficients = trebleCoefficients;

    presenceCoefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 4000.0f, 0.707f, juce::Decibels::decibelsToGain(0.0f));
    presenceFilter.coefficients = presenceCoefficients;

    brillianceCoefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(44100, 8000.0f, 0.707f, juce::Decibels::decibelsToGain(0.0f));
    brillianceFilter.coefficients = brillianceCoefficients;
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
    auto sliderArea = area.removeFromLeft(area.getWidth() * 0.7);
    int sliderWidth = sliderArea.getWidth() / 7;

    bassSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
    lowMidSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
    midSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
    highMidSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
    trebleSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
    presenceSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
    brillianceSlider.setBounds(sliderArea);

    auto buttonArea = area;
    bypassButton.setBounds(buttonArea.removeFromTop(40));
    resetButton.setBounds(buttonArea.removeFromTop(40));
}

void EqualizerComponent::sliderValueChanged(juce::Slider* slider)
{
    // Handle slider value changes for frequency adjustments
    if (slider == &bassSlider)
    {
        bassCoefficients->setCoefficients(juce::dsp::IIR::Coefficients<float>::makeLowShelf(44100, 100.0f, 0.707f, juce::Decibels::decibelsToGain(bassSlider.getValue())));
    }
    else if (slider == &lowMidSlider)
    {
        lowMidCoefficients->setCoefficients(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 250.0f, 0.707f, juce::Decibels::decibelsToGain(lowMidSlider.getValue())));
    }
    else if (slider == &midSlider)
    {
        midCoefficients->setCoefficients(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 500.0f, 0.707f, juce::Decibels::decibelsToGain(midSlider.getValue())));
    }
    else if (slider == &highMidSlider)
    {
        highMidCoefficients->setCoefficients(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 1000.0f, 0.707f, juce::Decibels::decibelsToGain(highMidSlider.getValue())));
    }
    else if (slider == &trebleSlider)
    {
        trebleCoefficients->setCoefficients(juce::dsp::IIR::Coefficients<float>::makeHighShelf(44100, 2000.0f, 0.707f, juce::Decibels::decibelsToGain(trebleSlider.getValue())));
    }
    else if (slider == &presenceSlider)
    {
        presenceCoefficients->setCoefficients(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 4000.0f, 0.707f, juce::Decibels::decibelsToGain(presenceSlider.getValue())));
    }
    else if (slider == &brillianceSlider)
    {
        brillianceCoefficients->setCoefficients(juce::dsp::IIR::Coefficients<float>::makeHighShelf(44100, 8000.0f, 0.707f, juce::Decibels::decibelsToGain(brillianceSlider.getValue())));
    }
}

void EqualizerComponent::buttonClicked(juce::Button* button)
{
    if (button == &bypassButton)
    {
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
