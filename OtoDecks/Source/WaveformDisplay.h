/*
  ==============================================================================

    WaveformDisplay.h
    Created: 2 Feb 2021 3:51:55pm
    Author:  user

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component, public juce::ChangeListener
{
public:
    WaveformDisplay(AudioFormatManager& formatManagerToUse, AudioThumbnailCache& cacheToUse);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    //implement this method to receive the callback.
    void changeListenerCallback (ChangeBroadcaster *source);

    //load the URL
    void loadURL(URL audioURL);

    //set the relative position of the playhead
    void setPositionRelative(double pos);

private:
    AudioThumbnail audioThumb;
    bool fileloaded;
    double position;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
