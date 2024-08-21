/*
  ==============================================================================

    DeckGUI.h
    Created: 21 Aug 2024 11:40:00am
    Author:  Juris Slisans

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DeckGUI  : public juce::Component
{
public:
    DeckGUI();
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::TextButton playButton{"PLAY"};
    juce::TextButton stopButton{"STOP"};
    juce::TextButton loadButton{"LOAD"};
    
    
    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
