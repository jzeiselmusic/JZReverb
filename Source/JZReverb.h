/*
  ==============================================================================

    JZReverb.h
    Created: 16 Oct 2023 11:57:55am
    Author:  Jacob Zeisel

  ==============================================================================
*/

#pragma once

#include"JuceHeader.h"
#include <vector>
#include "Diffuser.h"
#include "FDN.h"

class JZReverb
{
public:
    JZReverb(int size,int num_diffusers,std::vector<double> lengths,double decay,double sampleRate, std::vector<int> rd_seeds, std::vector<int> delay_times);
    ~JZReverb(void);
    double processAndReturnSample(double input_sample);
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JZReverb);
    
    int num_diffusers;
    int size;
    
    std::vector<Diffuser*> diffuser_stages;
    
    std::vector<FDN*> fdn_stages;

};
