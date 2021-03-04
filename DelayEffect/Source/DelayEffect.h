/*
  ==============================================================================

    DelayEffect.h
    Created: 3 Mar 2021 11:39:11pm
    Author:  William Holk

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DelayEffect{

public:
 
    DelayEffect();
    
    float processSample(float x, int c);
    
    void prepare(float newFs);
    
    void setDelayMS(float newDelayMS);
    
    void setBPM(float newBPM);
    
    void setNoteDuration(float newNoteDuration);
    
    void setFeedbackGain(float newFeedbackGain);
    
    void setLowPassFreq(float newLowPassFreq);
    
private:
    
    float Fs = 48000.f;
    
    float delayMS = 500.f;
    
    int delaySamples = round(Fs*delayMS/1000.f);
    
    float bpm = 120.f;
    
    float noteDuration = 1.f; // 1 - quarter, 2 - falf, 0.5 - 8th, 0.25 - 16th
    
    float feedbackGain = 1.f;
    
    float lowPassFreq = 20000.f;
    
};
