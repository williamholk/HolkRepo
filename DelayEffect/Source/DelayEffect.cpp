/*
  ==============================================================================

    DelayEffect.cpp
    Created: 3 Mar 2021 11:39:11pm
    Author:  William Holk

  ==============================================================================
*/

#include "DelayEffect.h"

DelayEffect::DelayEffect(){}

void DelayEffect::prepare(float newFs){
    Fs = newFs;
    delaySamples = round(Fs*delayMS/1000.f);
}

void DelayEffect::setDelayMS(float newDelayMS){
    if (newDelayMS <= 1000.f){
        delayMS = newDelayMS;
        delaySamples = round(Fs*delayMS/1000.f);
    }
}

float DelayEffect::processSample(float x, int c){
    
    int delayIndex = writeIndex[c] - delaySamples;
    
    if (delayIndex < 0){
        delayIndex += BUFFERSIZE;
    }
    
    float y = x + feedbackGain * w[c][delayIndex];
    
    w[c][writeIndex[c]] = y;
    
    writeIndex[c]++;
    if (writeIndex[c] >= BUFFERSIZE){
        writeIndex[c] = 0;
    }
    
    return y;
    
}

void DelayEffect::setBPM(float newBPM){
    bpm = newBPM;
}


void DelayEffect::setNoteDuration(float newNoteDuration){
    noteDuration = newNoteDuration;
    
    // Convert to delaySamples;
    float beatSec = bpm * (1.f/60.f);
    float secBeat = 1/beatSec;
    float secNote = noteDuration * secBeat;
    float msNote = secNote * 1000.f;
    setDelayMS(msNote);
    
}

void DelayEffect::setFeedbackGain(float newFeedbackGain){
    if(newFeedbackGain > 1 || newFeedbackGain < 0){
        feedbackGain = 0;
    }
    else{
        feedbackGain = newFeedbackGain;
    }
}

void DelayEffect::setLowPassFreq(float newLowPassFreq){
    if(newLowPassFreq > 20000.f){
        lowPassFreq = 20000.f;
    }
    else if(newLowPassFreq < 0.f){
        lowPassFreq = 0.f;
    }
    else{
        lowPassFreq = newLowPassFreq;
    }
    
}
