/*
  ==============================================================================

    DeckGUI.cpp
    Created: 31 Jan 2021 2:55:46pm
    Author:  user

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player, AudioFormatManager& formatManagerToUse, AudioThumbnailCache& cacheToUse) : player(_player),waveformDisplay(formatManagerToUse,cacheToUse)
{
    //Set the play button colour
    playButton.setColour(TextButton::buttonColourId, Colours::purple);
    addAndMakeVisible(playButton);
    playButton.addListener(this);

    //Set the stop button colour
    stopButton.setColour(TextButton::buttonColourId, Colours::red);
    addAndMakeVisible(stopButton);
    stopButton.addListener(this);

    //Set the load button colour
    loadButton.setColour(TextButton::buttonColourId, Colours::darkblue);
    addAndMakeVisible(loadButton);
    loadButton.addListener(this);

    repeatButton.setColour(TextButton::buttonColourId, Colours::limegreen);
    addAndMakeVisible(repeatButton);
    repeatButton.addListener(this);

    //Set the volume slider style,colour,and Range
    volSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    volSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 70, 20);
    volSlider.setColour(juce::Slider::thumbColourId, juce::Colours::red);
    volSlider.setRange(0.0, 1.0);
    addAndMakeVisible(volSlider);
    volSlider.addListener(this);
    
    //Set the speed slider style,colour,and Range
    speedSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    speedSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 70, 20);
    speedSlider.setColour(juce::Slider::thumbColourId, juce::Colours::yellow);
    speedSlider.setRange(0.5, 10.0);
    addAndMakeVisible(speedSlider);
    speedSlider.addListener(this);
    
    //Set the position slider style,colour,and Range
    posSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    posSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 70, 20);
    posSlider.setColour(juce::Slider::thumbColourId, juce::Colours::green);
    posSlider.setRange(0.0, 1.0);
    addAndMakeVisible(posSlider);
    posSlider.addListener(this);

    addAndMakeVisible(waveformDisplay); 
    startTimer(500);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    double rowH = getHeight() / 13;
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    g.fillAll(Colours::rosybrown);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::black);
    g.setFont (14.0f);
    g.drawText("VOLUME", -80, rowH * 3 -10, getWidth() - 100, 130,juce::Justification::centred, true);   //draw volume placeholder text
    g.drawText ("SPEED", 180, rowH * 3 -10, getWidth() - 100, 130,juce::Justification::centred, true);   //draw speed placeholder text
    g.drawText("POSITION", 50,rowH * 6 -10, getWidth() - 100, 130,juce::Justification::centred, true);   //draw position placeholder text
}

void DeckGUI::resized()
{
    double rowH = getHeight() / 13;
    loadButton.setBounds(0, 0, getWidth(), rowH);
    waveformDisplay.setBounds(0, rowH, getWidth(), rowH * 2);
    volSlider.setBounds(-80, rowH *3, getWidth()-100, 130);
    speedSlider.setBounds(180, rowH * 3, getWidth() - 100, 130);
    posSlider.setBounds(50, rowH * 6, getWidth() - 100, 130);
    playButton.setBounds(0, rowH * 10, getWidth()/2, rowH);
    stopButton.setBounds(getWidth()/2, rowH * 10, getWidth()/2, rowH);
    repeatButton.setBounds(100, rowH * 11, getWidth()/2, rowH);
}

void DeckGUI::buttonClicked(Button* button) {

    if (button == &playButton) {
        player->start();
    }
    else if (button == &stopButton) {
        player->stop();
    }
    else if (button == &loadButton) {
        FileChooser chooser{"Select a file ..."};
        if (chooser.browseForFileToOpen()) {
            player->loadURL(URL{chooser.getResult()});
            waveformDisplay.loadURL(URL{chooser.getResult()});
        }
    }
    else if (button == &repeatButton) {
        player->start();
        player->setPosition(0.0);
    }
}

void DeckGUI::sliderValueChanged(Slider* slider) {
    if (slider == &volSlider) {
        player->setGain(slider->getValue());
    }
    else if (slider == &speedSlider) {
        player->setSpeed(slider->getValue());
    }
    else if (slider == &posSlider) {
        player->setPositionRelative(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag(const StringArray &files) {
    std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
    return true;
}

void DeckGUI::filesDropped(const StringArray &files, int x, int y) {
    std::cout << "DeckGUI::fileDropped" << std::endl;
    if (files.size() == 1) {
        player->loadURL(URL{ File{files[0]} });
    }
}

void DeckGUI::timerCallback() {
    std::cout << "DeckGUI::timerCallback()" << std::endl;
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}
