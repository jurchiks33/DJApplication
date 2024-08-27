/*
  ==============================================================================

    PlaylistComponent.h
    Created: 27 Aug 2024 1:07:50pm
    Author:  Juris Slisans

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component
{
public:
    PlaylistComponent();
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::TableListBox tableComponent;
    std::vector<std::string> trackTitles;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};