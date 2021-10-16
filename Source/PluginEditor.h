/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class AleDistortionAudioProcessorEditor  : public juce::AudioProcessorEditor
{
  public:
    AleDistortionAudioProcessorEditor (AleDistortionAudioProcessor&);
    ~AleDistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

  private:

    juce::Slider driveKnob;
    juce::Slider rangeKnob;
    juce::Slider blendKnob;
    juce::Slider volumeKnob;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      driveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      rangeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      blendAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      volumeAttachment;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AleDistortionAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AleDistortionAudioProcessorEditor)
};
