/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AleDistortionAudioProcessorEditor::AleDistortionAudioProcessorEditor (AleDistortionAudioProcessor& p)
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
    setSize (400, 150);
}

AleDistortionAudioProcessorEditor::~AleDistortionAudioProcessorEditor()
{
}

//==============================================================================
void AleDistortionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colour(252,120,183));
    
    const int 
      x = getWidth() / 4, 
      y = getHeight(), 
      w = 100, h = 100;
    
    g.setColour (juce::Colour(255,255,255));
    g.setFont (juce::Font(30.f, juce::Font::bold | juce::Font::italic));
    g.drawFittedText (
      "AM - 37", 50, 0, 300, 40, juce::Justification::centred, 1);
    g.setColour (juce::Colour(147,135,247));
    g.setFont (juce::Font(12.0f, 1));
    g.drawFittedText (
      "by SARC", 50, 40, 300, 10, juce::Justification::centred, 1);
    g.setColour (juce::Colour(255,255,255));
    g.setFont (juce::Font(15.0f, juce::Font::plain));

    g.drawFittedText (
      "Drive", x*1-w, y-h-10, w, h, juce::Justification::centred, 1);
    g.drawFittedText (
      "Range", x*2-w, y-h-10, w, h, juce::Justification::centred, 1);
    g.drawFittedText (
      "Blend", x*3-w, y-h-10, w, h, juce::Justification::centred, 1);
    g.drawFittedText (
      "Volume",x*4-w, y-h-10, w, h, juce::Justification::centred, 1);

    g.drawFittedText (
      ">>>",x*1-w, y-15, w, 5, juce::Justification::centred, 1);
    g.drawFittedText (
      "soft | hard",x*2-w, y-15, w, 5, juce::Justification::centred, 1);
    g.drawFittedText (
      "clean |  dirty",x*3-w, y-15, w, 5, juce::Justification::centred, 1);
    g.drawFittedText (
      ">>>",x*4-w, y-15, w, 5, juce::Justification::centred, 1);

    getLookAndFeel().setColour(
      juce::Slider::thumbColourId, juce::Colour(255,255,255));
    getLookAndFeel().setColour(
      juce::Slider::rotarySliderFillColourId, juce::Colour(116,246,232));
    getLookAndFeel().setColour(
      juce::Slider::rotarySliderOutlineColourId, juce::Colour(253,155,202));
}

void AleDistortionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    const int 
      x = (getWidth() / 4), 
      y = (getHeight() / 1), 
      w = 100, h = 100;
    
    driveKnob.setBounds(  x*1-w, y-h-10, w, h);
    rangeKnob.setBounds(  x*2-w, y-h-10, w, h);
    blendKnob.setBounds(  x*3-w, y-h-10, w, h);
    volumeKnob.setBounds( x*4-w, y-h-10, w, h);
}
