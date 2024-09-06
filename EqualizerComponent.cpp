//
///*
//  ==============================================================================
//
//    EqualizerComponent.cpp
//
//  ==============================================================================
//*/


#include "EqualizerComponent.h"
#include "DjAudioPlayer.h"
#include <JuceHeader.h>

EqualizerComponent::EqualizerComponent(DJAudioPlayer& playerRef)
    : player(playerRef), // Initialize the player reference
      bypassButton("Bypass"), resetButton("Reset"),
      rockPresetButton("Rock"), jazzPresetButton("Jazz"), classicalPresetButton("Classical"), // Initialize preset buttons
      presetSelector()  // Initialize presetSelector
{
    // Setup sliders for EQ bands
    setupSlider(bassSlider, "Bass (60 Hz)");
    setupSlider(lowMidSlider, "Low-Mid (250 Hz)");
    setupSlider(midSlider, "Mid (500 Hz)");
    setupSlider(highMidSlider, "High-Mid (1 kHz)");
    setupSlider(trebleSlider, "Treble (2 kHz)");
    setupSlider(presenceSlider, "Presence (4 kHz)");
    setupSlider(brillianceSlider, "Brilliance (8 kHz)");

    // Add labels to sliders
    addLabelForSlider(bassSlider, "Bass");
    addLabelForSlider(lowMidSlider, "Low-Mid");
    addLabelForSlider(midSlider, "Mid");
    addLabelForSlider(highMidSlider, "High-Mid");
    addLabelForSlider(trebleSlider, "Treble");
    addLabelForSlider(presenceSlider, "Presence");
    addLabelForSlider(brillianceSlider, "Brilliance");

    // Setup bypass and reset buttons
    bypassButton.setClickingTogglesState(true);
    bypassButton.setButtonText("Bypass");
    bypassButton.addListener(this);
    addAndMakeVisible(bypassButton);
    updateBypassButtonColor();

    resetButton.setButtonText("Reset");
    resetButton.setColour(juce::TextButton::buttonColourId, juce::Colours::lightcoral);
    resetButton.addListener(this);
    addAndMakeVisible(resetButton);

    // Setup BPM slider
    bpmSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    bpmSlider.setRange(60.0, 200.0);
    bpmSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    bpmSlider.setValue(120.0);
    bpmSlider.addListener(this);
    bpmSlider.setName("BPM");
    addAndMakeVisible(bpmSlider);

    // Setup preset selector
    setupPresetSelector();

    initializeFilters();
}

EqualizerComponent::~EqualizerComponent() = default;

void EqualizerComponent::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &presetSelector)
    {
        // Apply the selected preset
        applyPreset(presetSelector.getSelectedId() - 1);
    }
}

void EqualizerComponent::paint(juce::Graphics& g)
{
    // Create a vertical gradient background
    juce::ColourGradient gradient(juce::Colours::darkgrey, getLocalBounds().toFloat().getTopLeft(),
                                  juce::Colours::black, getLocalBounds().toFloat().getBottomLeft(), false);
    g.setGradientFill(gradient);
    g.fillAll();

    // Add a border
    g.setColour(juce::Colours::white);
    g.drawRect(getLocalBounds(), 1);

    // Add title text
    g.setColour(juce::Colours::white);
    g.setFont(18.0f);
    g.drawText("Equalizer", getLocalBounds().removeFromTop(20), juce::Justification::centredTop);
}

void EqualizerComponent::resized()
{
    auto area = getLocalBounds();
    auto sliderArea = area.removeFromLeft(area.getWidth() * 0.5);
    int sliderWidth = sliderArea.getWidth() / 7;

    // Position sliders on the left
    bassSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
    lowMidSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
    midSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
    highMidSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
    trebleSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
    presenceSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
    brillianceSlider.setBounds(sliderArea);

    // Position buttons and BPM slider on the right
    auto buttonArea = area.removeFromRight(area.getWidth());
    bypassButton.setBounds(buttonArea.removeFromTop(40).reduced(10));
    resetButton.setBounds(buttonArea.removeFromTop(40).reduced(10));
    bpmSlider.setBounds(buttonArea.removeFromTop(60).reduced(10));

    // Position preset selector below BPM slider
    presetSelector.setBounds(buttonArea.removeFromTop(30).reduced(5));
}

void EqualizerComponent::sliderValueChanged(juce::Slider* slider)
{
    auto sampleRate = 44100.0;

    if (slider == &bassSlider)
    {
        updateFilter(bassFilter, juce::dsp::IIR::Coefficients<float>::makeLowShelf(sampleRate, 60.0f, 0.707f, juce::Decibels::decibelsToGain(bassSlider.getValue())));
    }
    else if (slider == &lowMidSlider)
    {
        updateFilter(lowMidFilter, juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 250.0f, 0.707f, juce::Decibels::decibelsToGain(lowMidSlider.getValue())));
    }
    else if (slider == &midSlider)
    {
        updateFilter(midFilter, juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 500.0f, 0.707f, juce::Decibels::decibelsToGain(midSlider.getValue())));
    }
    else if (slider == &highMidSlider)
    {
        updateFilter(highMidFilter, juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 1000.0f, 0.707f, juce::Decibels::decibelsToGain(highMidSlider.getValue())));
    }
    else if (slider == &trebleSlider)
    {
        updateFilter(trebleFilter, juce::dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, 2000.0f, 0.707f, juce::Decibels::decibelsToGain(trebleSlider.getValue())));
    }
    else if (slider == &presenceSlider)
    {
        updateFilter(presenceFilter, juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 4000.0f, 0.707f, juce::Decibels::decibelsToGain(presenceSlider.getValue())));
    }
    else if (slider == &brillianceSlider)
    {
        updateFilter(brillianceFilter, juce::dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, 8000.0f, 0.707f, juce::Decibels::decibelsToGain(brillianceSlider.getValue())));
    }
    else if (slider == &bpmSlider) // Handle BPM slider changes
    {
        std::cout << "BPM set to " << bpmSlider.getValue() << std::endl;
        
        // Update the player's BPM
        player.setBPM(bpmSlider.getValue());
    }
}


void EqualizerComponent::buttonClicked(juce::Button* button)
{
    if (button == &bypassButton)
    {
        isBypassed = bypassButton.getToggleState();
        updateBypassButtonColor();
        bypassButton.repaint();
        std::cout << (isBypassed ? "EQ Bypassed" : "EQ Enabled") << std::endl;
    }
    else if (button == &resetButton)
    {
        // Reset all sliders to neutral (0.0) values
        bassSlider.setValue(0.0);
        lowMidSlider.setValue(0.0);
        midSlider.setValue(0.0);
        highMidSlider.setValue(0.0);
        trebleSlider.setValue(0.0);
        presenceSlider.setValue(0.0);
        brillianceSlider.setValue(0.0);
        bpmSlider.setValue(120.0);
        presetSelector.setSelectedId(1); // Set preset to Neutral
        std::cout << "EQ Reset to default" << std::endl;
    }
}


void EqualizerComponent::applyPreset(int presetType)
{
    switch (presetType)
    {
        case 0: // Neutral Preset
            bassSlider.setValue(0.0);
            lowMidSlider.setValue(0.0);
            midSlider.setValue(0.0);
            highMidSlider.setValue(0.0);
            trebleSlider.setValue(0.0);
            presenceSlider.setValue(0.0);
            brillianceSlider.setValue(0.0);
            break;

        case 1: // Rock Preset
            bassSlider.setValue(6.0);
            lowMidSlider.setValue(4.0);
            midSlider.setValue(-2.0);
            highMidSlider.setValue(2.0);
            trebleSlider.setValue(3.0);
            presenceSlider.setValue(5.0);
            brillianceSlider.setValue(4.0);
            break;

        case 2: // Jazz Preset
            bassSlider.setValue(2.0);
            lowMidSlider.setValue(1.0);
            midSlider.setValue(0.0);
            highMidSlider.setValue(3.0);
            trebleSlider.setValue(5.0);
            presenceSlider.setValue(4.0);
            brillianceSlider.setValue(6.0);
            break;

        case 3: // Classical Preset
            bassSlider.setValue(0.0);
            lowMidSlider.setValue(0.0);
            midSlider.setValue(1.0);
            highMidSlider.setValue(1.0);
            trebleSlider.setValue(0.0);
            presenceSlider.setValue(0.0);
            brillianceSlider.setValue(0.0);
            break;

        default:
            break;
    }
    std::cout << "Preset applied: " << (presetType == 0 ? "Neutral" : presetType == 1 ? "Rock" : presetType == 2 ? "Jazz" : "Classical") << std::endl;
}


void EqualizerComponent::setupSlider(juce::Slider& slider, const juce::String& name)
{
    slider.setSliderStyle(juce::Slider::LinearVertical);
    slider.setRange(-12.0, 12.0);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    slider.setValue(0.0);
    slider.setName(name);
    slider.addListener(this);

    // Set custom colors for the sliders
    slider.setColour(juce::Slider::thumbColourId, juce::Colours::aqua);
    slider.setColour(juce::Slider::trackColourId, juce::Colours::darkgrey);
    slider.setColour(juce::Slider::backgroundColourId, juce::Colours::black);

    addAndMakeVisible(slider);
}

void EqualizerComponent::addLabelForSlider(juce::Slider& slider, const juce::String& labelText)
{
    auto* label = new juce::Label();
    label->setText(labelText, juce::dontSendNotification);
    label->attachToComponent(&slider, false);
    label->setJustificationType(juce::Justification::centredTop);
    label->setColour(juce::Label::textColourId, juce::Colours::lightgrey);
    addAndMakeVisible(label);
}

void EqualizerComponent::setupPresetSelector()
{
    presetSelector.addItem("Neutral", 1);  // Add Neutral preset
    presetSelector.addItem("Rock", 2);
    presetSelector.addItem("Jazz", 3);
    presetSelector.addItem("Classical", 4);
    presetSelector.setSelectedId(1);  // Set Neutral as the default
    presetSelector.addListener(this); // Register the listener
    addAndMakeVisible(presetSelector);
}

void EqualizerComponent::initializeFilters()
{
    bassFilter.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(44100, 100.0f, 0.707f, juce::Decibels::decibelsToGain(0.0f));
    lowMidFilter.coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 250.0f, 0.707f, juce::Decibels::decibelsToGain(0.0f));
    midFilter.coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 500.0f, 0.707f, juce::Decibels::decibelsToGain(0.0f));
    highMidFilter.coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 1000.0f, 0.707f, juce::Decibels::decibelsToGain(0.0f));
    trebleFilter.coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(44100, 2000.0f, 0.707f, juce::Decibels::decibelsToGain(0.0f));
    presenceFilter.coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 4000.0f, 0.707f, juce::Decibels::decibelsToGain(0.0f));
    brillianceFilter.coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(44100, 8000.0f, 0.707f, juce::Decibels::decibelsToGain(0.0f));
}

void EqualizerComponent::updateFilter(juce::dsp::IIR::Filter<float>& filter, const juce::dsp::IIR::Coefficients<float>::Ptr& coefficients)
{
    if (coefficients != nullptr)
    {
        filter.coefficients = coefficients;
    }
}

void EqualizerComponent::updateBypassButtonColor()
{
    if (isBypassed)
    {
        bypassButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::lightcoral);
        bypassButton.setColour(juce::TextButton::buttonColourId, juce::Colours::lightcoral);
    }
    else
    {
        bypassButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::lightgreen);
        bypassButton.setColour(juce::TextButton::buttonColourId, juce::Colours::lightgreen);
    }
    
    bypassButton.repaint();
}

void EqualizerComponent::process(juce::dsp::AudioBlock<float>& audioBlock)
{
    if (isBypassed)
        return; // Skip processing if bypassed

    auto context = juce::dsp::ProcessContextReplacing<float>(audioBlock);
    
    jassert(audioBlock.getNumChannels() > 0 && audioBlock.getNumSamples() > 0);

    // Process each filter in order
    bassFilter.process(context);
    lowMidFilter.process(context);
    midFilter.process(context);
    trebleFilter.process(context);
    presenceFilter.process(context);
    brillianceFilter.process(context);
}


