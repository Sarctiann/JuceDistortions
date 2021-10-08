/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RFDistortionAudioProcessor::RFDistortionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    createParametersLayout();
}

RFDistortionAudioProcessor::~RFDistortionAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout 
        RFDistortionAudioProcessor::createParametersLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "DRIVE_ID",
        "Drive",
        juce::NormalisableRange<float>(1.f, 500.f, 0.01, 0.5),
        1.f
    ));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "RANGE_ID",
        "Range",
        juce::NormalisableRange<float>(0.f, 1.f, 0.01), 
        0.f
    ));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "BLEND_ID",
        "Blend",
        juce::NormalisableRange<float>(0.f, 1.f, 0.01), 
        0.5
    ));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "VOLUME_ID",
        "Volume",
        juce::NormalisableRange<float>(0.f, 2.f, 0.01, 0.5), 
        1.f
    ));

    return layout;
}

//==============================================================================
const juce::String RFDistortionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool RFDistortionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool RFDistortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool RFDistortionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double RFDistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int RFDistortionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int RFDistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void RFDistortionAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String RFDistortionAudioProcessor::getProgramName (int index)
{
    return {};
}

void RFDistortionAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void RFDistortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void RFDistortionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool RFDistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void RFDistortionAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    float drive = *parameterState.getRawParameterValue("DRIVE_ID");
    float range = *parameterState.getRawParameterValue("RANGE_ID");
    float blend = *parameterState.getRawParameterValue("BLEND_ID");
    float volume = *parameterState.getRawParameterValue("VOLUME_ID");
    float PI = juce::MathConstants<float>::pi;

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            float *sig = &channelData[sample];

            float cleanSig = *sig * (1 - blend);

            float ds = *sig * drive; // distorted signal
            float soft = (2.f / PI ) * atan(ds) * (1 - range);
            float hard = (ds < 1 && -1 < ds ? ds : ds < 0 ? -1 : 1) * range;
            float distSig = ( soft + hard ) * blend;

            channelData[sample] = (cleanSig + distSig) * volume;
        }
    }
}

//==============================================================================
bool RFDistortionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* RFDistortionAudioProcessor::createEditor()
{
    return new RFDistortionAudioProcessorEditor (*this);
}

//==============================================================================
void RFDistortionAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::MemoryOutputStream mos(destData, true);
    parameterState.state.writeToStream(mos);
}

void RFDistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ValueTree tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if( tree.isValid() )
    {
        parameterState.replaceState(tree);
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RFDistortionAudioProcessor();
}
