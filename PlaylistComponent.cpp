/*
  ==============================================================================

    PlaylistComponent.cpp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    //tableComponent.getHeader().addColumn("Track title", 0, 400);
    
    trackTitles.push_back("Track 1");
    trackTitles.push_back("Track 2");
    trackTitles.push_back("Track 3");
    trackTitles.push_back("Track 4");
    trackTitles.push_back("Track 5");
    trackTitles.push_back("Track 6");
    
    tableComponent.getHeader().addColumn("Track title", 1, 400, 50, -1, juce::TableHeaderComponent::visible);
    tableComponent.getHeader().addColumn("", 2, 200, 50, -1, juce::TableHeaderComponent::visible); //experimental 
    
    tableComponent.setModel(this);

    
    addAndMakeVisible(tableComponent);

}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    tableComponent.setBounds(0, 0, getWidth(), getHeight());

}

int PlaylistComponent::getNumRows ()
{
    return trackTitles.size();
}

void PlaylistComponent::paintRowBackground (juce::Graphics & g,
                         int rowNumber,
                         int width,
                         int height,
                         bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(juce::Colours::orange);
    }
    else{
        g.fillAll(juce::Colours::darkgrey);
    }
}

void PlaylistComponent::paintCell (juce::Graphics & g,
                int rowNumber,
                int columnId,
                int width,
                int height,
                bool rowIsSelected)
{
    g.drawText (trackTitles[rowNumber], 
                2, 0,
                width - 4, height,
                juce::Justification::centredLeft,
                true);
}


juce::Component* PlaylistComponent::refreshComponentForCell (int rowNumber,
                                    int columnId,
                                    bool isRowSelected,
                                    juce::Component *existingComponentToUpdate)
{
    if (columnId == 2)
    {
        if (existingComponentToUpdate == nullptr)
        {
            juce::TextButton* btn = new juce::TextButton{"Play"};
            juce::String id{std::to_string(rowNumber)};
            btn->setComponentID(id);
            
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
    
}


void PlaylistComponent::buttonClicked(juce::Button* button)
{
    int id = std::stoi(button->getComponentID().toStdString());
    
    std::cout << "PlaylistComponent::buttonClicked " << trackTitles[id] << std::endl;
}

