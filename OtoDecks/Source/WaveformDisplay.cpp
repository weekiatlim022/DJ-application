/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 2 Feb 2021 3:51:55pm
    Author:  user

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager& formatManagerToUse, AudioThumbnailCache& cacheToUse) : audioThumb(1000,formatManagerToUse,cacheToUse),fileloaded(false),position(0)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::plum);
    if (fileloaded) {
        audioThumb.drawChannel(g, getLocalBounds(), 0, audioThumb.getTotalLength(), 0, 1.0f);
        g.setColour(Colours::red);
        g.drawRect(position * getWidth(), 0 , getWidth()/20, getHeight());
    }
    else {
        g.setFont(20.0f);
        g.drawText("~ LOAD A FILE ~", getLocalBounds(),
        juce::Justification::centred, true);   // draw some placeholder text
    }   
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void WaveformDisplay::loadURL(URL audioURL) {  
    audioThumb.clear();
    fileloaded = audioThumb.setSource(new URLInputSource(audioURL));

    if (fileloaded) {
        std::cout << "wfd::loaded!" << std::endl;
        repaint();
    }
    else {
        std::cout << "wfd::not loaded!" << std::endl;
    }
}

void WaveformDisplay::changeListenerCallback(ChangeBroadcaster *source) {
    std::cout << "wfd::change received!" << std::endl;
    repaint();
}

void WaveformDisplay::setPositionRelative(double pos) {
    if (pos != position) {
        position = pos;
        repaint();
    }   
}