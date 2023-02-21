#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    //tells the source to prepare for playing
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;

    //called repeatedly to fetch subsequent blocks of audio data
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;

    ///allows the source to release anything it no longer needs after playback has stopped
    void releaseResources() override;
    //==============================================================================

    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...

    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{ 100 };

    DJAudioPlayer player1{ formatManager };
    DeckGUI deckGUI1{&player1,formatManager,thumbCache};

    DJAudioPlayer player2{ formatManager };
    DeckGUI deckGUI2{&player2,formatManager,thumbCache };

    MixerAudioSource mixerSource;

    PlaylistComponent playlistComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
