/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DelayEffectAudioProcessorEditor::DelayEffectAudioProcessorEditor (DelayEffectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 250);
    
    delayKnob.addListener(this);
    delayKnob.setBounds(100, 50, 150, 150);
    delayKnob.setCentrePosition(250, 140);
    delayKnob.setValue(audioProcessor.delayMS);
    delayKnob.setRange(10.f, 1000.f,1.f);
    delayKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    delayKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayKnob.setTextValueSuffix("ms");
    addAndMakeVisible(delayKnob);
    
    noteSelector.addListener(this);
    noteSelector.addItem("Half", 1);
    noteSelector.addItem("Quarter", 2);
    noteSelector.addItem("8th", 3);
    noteSelector.addItem("16th", 4);
    noteSelector.addItem("32nd", 5);
    noteSelector.setSelectedId(2);
    noteSelector.setBounds(325, 25, 120, 40);
    noteSelector.setCentrePosition(250, 25);
    addAndMakeVisible(noteSelector);
    
    tempoSyncButton.addListener(this);
    tempoSyncButton.setBounds(270, 178, 100, 40);
    tempoSyncButton.setCentrePosition(250, 60);
    tempoSyncButton.setButtonText("BPM Sync");
    tempoSyncButton.setToggleState(audioProcessor.tempoSyncd, dontSendNotification);
    tempoSyncButton.setRadioGroupId(1);
    addAndMakeVisible(tempoSyncButton);
    
    notTempoSyncButton.addListener(this);
    notTempoSyncButton.setBounds(270, 130, 100, 40);
    notTempoSyncButton.setCentrePosition(250, 230);
    notTempoSyncButton.setButtonText("Sync Off");
    notTempoSyncButton.setToggleState(!audioProcessor.tempoSyncd, dontSendNotification);
    notTempoSyncButton.setRadioGroupId(1);
    addAndMakeVisible(notTempoSyncButton);
    
    feedbackKnob.addListener(this);
    feedbackKnob.setBounds(50, 50, 110, 110);
    feedbackKnob.setCentrePosition(100, 125);
    feedbackKnob.setValue(audioProcessor.feedbackGain);
    feedbackKnob.setRange(0.f, 1.f,0.01f);
    feedbackKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    feedbackKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(feedbackKnob);
    
    lowPassKnob.addListener(this);
    lowPassKnob.setBounds(50, 50, 110, 110);
    lowPassKnob.setCentrePosition(400, 125);
    lowPassKnob.setRange(20.f, 20000.f, 1.f);
    lowPassKnob.setSkewFactorFromMidPoint(2000);
    lowPassKnob.setValue(audioProcessor.lowPassFreq);
    lowPassKnob.setTextValueSuffix("Hz");
    lowPassKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    lowPassKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(lowPassKnob);
    
    delayKnob.setEnabled(!audioProcessor.tempoSyncd);
    noteSelector.setEnabled(audioProcessor.tempoSyncd);
    
    
}

DelayEffectAudioProcessorEditor::~DelayEffectAudioProcessorEditor()
{
}

//==============================================================================
void DelayEffectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("ms", getLocalBounds(), juce::Justification::centred, 1);
    //g.drawFittedText("ms", 300, 150, 100, 25, juce::Justification::verticallyCentred, 1);
    
    g.drawText("Feedback", 70, 55, 100, 25, NULL);
    
    g.drawText("LPF", 388, 55, 100, 25, NULL);
}

void DelayEffectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void DelayEffectAudioProcessorEditor::sliderValueChanged(Slider * slider){
    
    if (slider == &delayKnob){
        audioProcessor.delayMS = delayKnob.getValue();
    }
    
    if (slider == &feedbackKnob){
        audioProcessor.feedbackGain = feedbackKnob.getValue();
    }
    
    if (slider == &lowPassKnob){
        audioProcessor.lowPassFreq = lowPassKnob.getValue();
        audioProcessor.filter.setFreq(audioProcessor.lowPassFreq);
    }
    
}

void DelayEffectAudioProcessorEditor::comboBoxChanged(ComboBox *comboBox){
   
    if (comboBox == &noteSelector){
        if(noteSelector.getSelectedId() == 1){
            // half note
            audioProcessor.noteDuration = 2.f;
        }
        if(noteSelector.getSelectedId() == 2){
            // quarter note
            audioProcessor.noteDuration = 1.f;
        }
        if(noteSelector.getSelectedId() == 3){
            // 8th note
            audioProcessor.noteDuration = 0.5f;
        }
        if(noteSelector.getSelectedId() == 4){
            // 16th note
            audioProcessor.noteDuration = 0.25f;
        }
        if(noteSelector.getSelectedId() == 5){
            // 32nd note
            audioProcessor.noteDuration = 0.125f;
        }
    }
}

void DelayEffectAudioProcessorEditor::buttonClicked(Button *button){
    
    if(button == &tempoSyncButton){
        audioProcessor.tempoSyncd = true;
        delayKnob.setEnabled(false);
        noteSelector.setEnabled(true);
    }
    
    if(button == &notTempoSyncButton){
        audioProcessor.tempoSyncd = false;
        delayKnob.setEnabled(true);
        noteSelector.setEnabled(false);
    }
    
}
