/*
  ==============================================================================

    DeckGUI.h
    Created: 31 Jan 2021 2:55:46pm
    Author:  user

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
//==============================================================================
/*
*/
class DeckGUI  : public Component, public Button::Listener, public Slider::Listener, public FileDragAndDropTarget, public Timer
{
public:
    DeckGUI(DJAudioPlayer* player, AudioFormatManager & formatManagerToUse, AudioThumbnailCache & cacheToUse);
    ~DeckGUI();

    void paint (juce::Graphics&) override;
    void resized() override;

    //implement Button::Listener
    void buttonClicked(Button *) override;

    //implement Slider::Listener
    void sliderValueChanged(Slider *slider) override;

    //callback to check whether this target is interested in the set of files being offered.
    bool isInterestedInFileDrag(const StringArray &files) override;

    //callback to indicate that the user has dropped the files onto this component
    void filesDropped(const StringArray &files, int x, int y) override;

    //callback routine that actually gets called periodically
    void timerCallback() override;

private:

    TextButton playButton{ "PLAY" };
    TextButton stopButton{ "PAUSE" };
    TextButton loadButton{ "LOAD" };
    TextButton repeatButton{ "REPEAT" };

    Slider volSlider;
    Slider speedSlider;
    Slider posSlider;

    DJAudioPlayer* player;

    WaveformDisplay waveformDisplay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
