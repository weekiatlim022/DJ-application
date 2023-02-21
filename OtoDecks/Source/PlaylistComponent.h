/*
  ==============================================================================

    PlaylistComponent.h
    Created: 5 Mar 2021 3:24:33pm
    Author:  weeki

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component, public TableListBoxModel, public Button::Listener
{
public:
    PlaylistComponent();
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    //return the number of rows currently in the table
    int getNumRows() override;

    //draw the background behind one of the rows in the table
    void paintRowBackground(Graphics &, int rowNumber, int width, int height, bool rowIsSelected) override;

    //draw one of the cells
    void paintCell(Graphics &, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

    //create or update a custom component to go in a cell
    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate)override;

    //Called when the button is clicked
    void buttonClicked(Button* button)override;

    //tells the source to prepare for playing
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);

    //called repeatedly to fetch subsequent blocks of audio data
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);

    //allows the source to release anything it no longer needs after playback has stopped
    void releaseResources();


private:

    TableListBox tableComponent;
    std::vector<std::string>trackTitles;

    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    ResamplingAudioSource resampleSource{ &transportSource, false, 2 };

    AudioThumbnailCache thumbCache{ 100 };
    DJAudioPlayer player1{ formatManager };
    DeckGUI deckGUI1{ &player1,formatManager,thumbCache };
    DJAudioPlayer player2{ formatManager };
    DeckGUI deckGUI2{ &player2,formatManager,thumbCache };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
