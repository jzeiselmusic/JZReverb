/*
  ==============================================================================

    JZReverb.cpp
    Created: 16 Oct 2023 11:57:47am
    Author:  Jacob Zeisel

  ==============================================================================
*/

#include "JZReverb.h"

JZReverb::JZReverb(int size, int num_diffusers, std::vector<double> lengths, double decay, double sampleRate, std::vector<int> rd_seeds, std::vector<int> delay_times)
{
    /* instantiate however many diffusion stages we want by creating new objects */
    for (int i = 0; i < num_diffusers; ++i)
    {
        diffuser_stages.push_back(new Diffuser(lengths[i], size, sampleRate, rd_seeds[i]));
    }
    
    /* create one FDN stage for now */
    fdn_stages.push_back(new FDN(size, delay_times, decay));
    
    this->num_diffusers = num_diffusers;
    this->size = size;
}

JZReverb::~JZReverb(void)
{
    for (int i = 0; i < num_diffusers; ++i)
    {
        delete diffuser_stages[i];
    }
    
    delete fdn_stages[0];
}

double JZReverb::processAndReturnSample(double input_sample)
{
    std::vector<double> output_buffer;
    
    for (int i = 0; i < num_diffusers; ++i)
    {
        if (i == 0)
        {
            /* first diffuser */
            output_buffer = diffuser_stages[i]->processDiffuserOneSample(input_sample);
        }
        else
        {
            output_buffer = diffuser_stages[i]->processDiffuserArray(output_buffer);
        }
    }
    
    output_buffer = fdn_stages[0]->processFdnArray(output_buffer);
    
    return output_buffer[0];
}
