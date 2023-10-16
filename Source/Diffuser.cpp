/*
  ==============================================================================

    Diffuser.cpp
    Created: 29 Jul 2023 2:38:40pm
    Author:  Jacob Zeisel

  ==============================================================================
*/

#include "Diffuser.h"
#include "utilities.h"
#include <random>

using namespace juce;

Diffuser::Diffuser(double length, int size, double sampleRate, int rd_seed)
{
    
    this->delay_module = new Delayer(length, size, sampleRate, rd_seed);
    
    this->size = size;
    
    for (int i = 0; i < size; ++i)
    {
        std::mt19937 temp(rd_seed);
        inverter.push_back(getRandomMult(temp));
    }
    
    /* set the audio buffer to all zeros */
    audio_buffer.resize(size);
    std::fill(audio_buffer.begin(), audio_buffer.end(), 0.0);
    
    this->hadamard_matrix = new Hadamard(size);
}

Diffuser::~Diffuser(void)
{
    delete hadamard_matrix;
    delete delay_module;
}

void Diffuser::invertSamples(std::vector<double>* buffer)
{
    // go through each channels current value and invert them randomly
    for (int i = 0; i < this->size; ++i)
    {
        buffer->at(i) *= inverter[i];
    }
}

std::vector<double> Diffuser::processDiffuserOneSample(double sample)
{
    delay_module->process(sample);
    
    std::vector<double>* output = delay_module->getSamples();
    
    invertSamples(output);
    
    hadamard_matrix->inPlaceTransform(output);
    
    return *output;
}


std::vector<double> Diffuser::processDiffuserArray(std::vector<double> buffer)
{
    delay_module->processParallelSamples(&buffer);
    
    std::vector<double>* output = delay_module->getSamples();
    
    invertSamples(output);
    
    hadamard_matrix->inPlaceTransform(output);
    
    return *output;
}
