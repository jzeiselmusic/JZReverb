/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "JZReverb.h"

//==============================================================================
/**
*/
class JZReverbAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    JZReverbAudioProcessor();
    ~JZReverbAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JZReverbAudioProcessor)
    
    /* define reverb modules */
    
    std::vector<double> diffuser_lengths = {0.011, 0.023, 0.037, 0.059};
    std::vector<int> fdn_delay_lengths = {551, 607, 689, 731};
    std::vector<int> rd_seeds = {10,20,30,40};
    JZReverb reverb_left_channel = JZReverb(4, 4, diffuser_lengths, 0.7, 44100.0, rd_seeds, fdn_delay_lengths);
    JZReverb reverb_right_channel = JZReverb(4, 4, diffuser_lengths, 0.7, 44100.0, rd_seeds, fdn_delay_lengths);
};
