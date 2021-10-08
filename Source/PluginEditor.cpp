/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RFDistortionAudioProcessorEditor::RFDistortionAudioProcessorEditor (RFDistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    juce::Slider::SliderStyle style = juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag;
    juce::Slider::TextEntryBoxPosition textBox = juce::Slider::TextEntryBoxPosition::NoTextBox;

    driveKnob.setSliderStyle(style);
    driveKnob.setTextBoxStyle(textBox, false, 100, 100);
    driveKnob.setSkewFactorFromMidPoint(100);
    addAndMakeVisible(driveKnob);

    rangeKnob.setSliderStyle(style);
    rangeKnob.setTextBoxStyle(textBox, false, 100, 100);
    addAndMakeVisible(rangeKnob);

    blendKnob.setSliderStyle(style);
    blendKnob.setTextBoxStyle(textBox, false, 100, 100);
    addAndMakeVisible(blendKnob);
    
    volumeKnob.setSliderStyle(style);
    volumeKnob.setTextBoxStyle(textBox, false, 100, 100);
    addAndMakeVisible(volumeKnob);

    driveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
      (audioProcessor.parameterState, "DRIVE_ID", driveKnob);

    rangeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
      (audioProcessor.parameterState, "RANGE_ID", rangeKnob);

    blendAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
      (audioProcessor.parameterState, "BLEND_ID", blendKnob);
      
    volumeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
      (audioProcessor.parameterState, "VOLUME_ID", volumeKnob);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 100);
}

RFDistortionAudioProcessorEditor::~RFDistortionAudioProcessorEditor()
{
}

//==============================================================================
void RFDistortionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colour(30,70,50));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);

    int 
      x = getWidth() / 4, 
      y = getHeight(), 
      w = 100, h = 100;
    
    g.drawFittedText ("Drive", x*1-w, y-h, w, h, juce::Justification::centred, 1);
    g.drawFittedText ("Range", x*2-w, y-h, w, h, juce::Justification::centred, 1);
    g.drawFittedText ("Blend", x*3-w, y-h, w, h, juce::Justification::centred, 1);
    g.drawFittedText ("Volume",x*4-w, y-h, w, h, juce::Justification::centred, 1);
}

void RFDistortionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    int 
      x = (getWidth() / 4), 
      y = (getHeight() / 1), 
      w = 100, h = 100;
    
    driveKnob.setBounds(  x*1-w, y-h, w, h);
    rangeKnob.setBounds(  x*2-w, y-h, w, h);
    blendKnob.setBounds(  x*3-w, y-h, w, h);
    volumeKnob.setBounds( x*4-w, y-h, w, h);
}
