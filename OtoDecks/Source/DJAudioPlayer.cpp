/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 19 Jan 2021 9:37:09pm
    Author:  user

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager):formatManager(_formatManager) {

}

DJAudioPlayer::~DJAudioPlayer() {

}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected,sampleRate);
}

void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)  {
    resampleSource.getNextAudioBlock(bufferToFill);

}

void DJAudioPlayer::releaseResources() {
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

void DJAudioPlayer::loadURL(URL audioURL) {
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) //good file
    {
        std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }
}

void DJAudioPlayer::setGain(double gain) {
    if (gain < 0 || gain > 1.0) {
        std::cout << "Gain should be between 0 and 1" << std::endl;
    }
    else {
        transportSource.setGain(gain);
    }
}

void DJAudioPlayer::setSpeed(double ratio) {
    if (ratio < 0.5 || ratio > 10.0) {
        std::cout << "Ratio should be between 0 and 10" << std::endl;
    }
    else {
        resampleSource.setResamplingRatio(ratio);
    }
}

void DJAudioPlayer::setPosition(double posInSecs) {
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double pos) {
    if (pos < 0 || pos > 1.0) {
        std::cout << "Position should be between 0 and 1" << std::endl;
    }
    else {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}

void DJAudioPlayer::start() {
    transportSource.start();
}

void DJAudioPlayer::stop() {
    transportSource.stop();
}

double DJAudioPlayer::getPositionRelative() {
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}