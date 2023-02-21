/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 19 Jan 2021 9:37:09pm
    Author:  user

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class DJAudioPlayer : public AudioSource {

public:
    DJAudioPlayer(AudioFormatManager& _formatManager);
    ~DJAudioPlayer();

    //tells the source to prepare for playing
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

    //called repeatedly to fetch subsequent blocks of audio data
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

    //allows the source to release anything it no longer needs after playback has stopped
    void releaseResources() override;

    //load the URL
    void loadURL(URL audioURL);

    //sets a gain to apply to the audio data
    void setGain(double gain);

    //sets a speed of the track
    void setSpeed(double ratio);

    //changes the current playback position in the source stream
    void setPosition(double posInSecs);

    //set the relative position of the playhead
    void setPositionRelative(double pos);

    //Start playing the tracks
    void start();

    //Stop playing the tracks
    void stop();

    //get the relative position of the playhead
    double getPositionRelative();

private:
    AudioFormatManager& formatManager;
    std::unique_ptr <AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    ResamplingAudioSource resampleSource{&transportSource, false, 2};
};