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
    
private:
    
    float Fs = 48000.f;
    
    float delayMS = 500.f;
    int delaySamples = round(Fs*delayMS/1000.f);
    
};
