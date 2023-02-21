/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 5 Mar 2021 3:24:33pm
    Author:  weeki

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    trackTitles.push_back("Track 1");
    trackTitles.push_back("Track 2");
    trackTitles.push_back("Track 3");
    trackTitles.push_back("Track 4");
    trackTitles.push_back("Track 5");
    trackTitles.push_back("Track 6");

    tableComponent.getHeader().addColumn("Track title",1,375);
    tableComponent.getHeader().addColumn("Duration",2,175);
    tableComponent.getHeader().addColumn("Add?", 3, 50);
    tableComponent.getHeader().addColumn("Play?",4, 50);
    tableComponent.getHeader().addColumn("Load Deck1",5,75);
    tableComponent.getHeader().addColumn("Load Deck2",6,75);
    
    
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
    g.setFont (14.0f);
    
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    tableComponent.setBounds(0, 0, getWidth(), getHeight());
}

int PlaylistComponent::getNumRows() {
    return trackTitles.size();
}

void PlaylistComponent::paintRowBackground(Graphics & g, int rowNumber, int width, int height, bool rowIsSelected) {
    if (rowIsSelected) {
        g.fillAll(Colours::orange);
    }
    else {
        g.fillAll(Colours::darkgrey);
    }

}

void PlaylistComponent::paintCell(Graphics & g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) {
    g.drawText(trackTitles[rowNumber], 2, 0, width - 4, height, Justification::centredLeft, true);
}

Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) {
    if (columnId == 3) {
        if (existingComponentToUpdate == nullptr) {
            TextButton* btn = new TextButton{ "ADD" };
            //String id{ std::to_string(rowNumber) };
            String id{ std::to_string(columnId) + std::to_string(rowNumber) };
            btn->setComponentID(id);
            btn->addListener(this);
            addAndMakeVisible(btn);
            existingComponentToUpdate = btn;
        }
    }
    else if (columnId == 4) {
        if (existingComponentToUpdate == nullptr) {         
            TextButton* btn = new TextButton{ "PLAY" };
            String id{ std::to_string(rowNumber) };
            //String id{ std::to_string(columnId) + std::to_string(rowNumber) };
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    else if (columnId == 5) {
        if (existingComponentToUpdate == nullptr) {
            TextButton* btn = new TextButton{ "Load Deck1" };
            String id{ std::to_string(rowNumber) };
            //String id{ std::to_string(columnId) + std::to_string(rowNumber) };
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate = btn;

        }
    }
    else if (columnId == 6) {
        if (existingComponentToUpdate == nullptr) {
            TextButton* btn = new TextButton{ "Load Deck2" };
            String id{ std::to_string(rowNumber) };
            //String id{ std::to_string(columnId) + std::to_string(rowNumber) };
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(Button* button) {
    int id = std::stoi(button->getComponentID().toStdString());
    //std::cout << "PlaylistComponent::buttonClicked" <<trackTitles[id]<< std::endl;
    
    
    //Add tracks into library
    if (id/10 == 3) {
        FileChooser chooser{ "Select a track add into playlist..." };
        if (chooser.browseForFileToOpen()) {
            chooser.getResult();
            //trackTitles.push_back(getFileName);
        }   
    }  

    //Play the tracks
    else if (id/10 == 4) {
       // trackTitles[id]->start();
        
    }

    //Load Deck1
    else if (id/10 == 5) {
        //player1->loadURL(URL{ trackTitles[id] });
    }

    //Load Deck2
    else if (id/10 == 6) {
        //player2->loadURL(URL{ trackTitles[id] });
    }
}

void PlaylistComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlaylistComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) {
    resampleSource.getNextAudioBlock(bufferToFill);

}

void PlaylistComponent::releaseResources() {
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

