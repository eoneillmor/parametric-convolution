/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <fstream>


using namespace std;

//==============================================================================
/**
*/
class FilterTestAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    FilterTestAudioProcessor();
    ~FilterTestAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void calculate_coefficients(float f, float alpha, float A, int IR);

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

    // MY CODE

    string dir = "C:\\Users\\eonei\\OneDrive - Queen's University Belfast\\Masters\\AHS7031\\IR txts\\";

    float x;
    float xz[371] = {};

    float yz[371] = {};
    float yzz[371] = {};
    float y[371] = {};
    float out;

    float C;
    float S;
    float omega;
    float omegaT;
    float R;

    float f_i;
    float alpha_i;
    float A_i;

    float a1[371] = {};
    float a2[371] = {};
    float b1[371] = {};
    float b0[371] = {};

    float Phase;

    float mAlph = 1;
    float mFreq = 0;
    float mGain = 0.5;
    float mWetDry = 1;

    int M = 371;

    float potlidAlpES[371] = {};
    float potlidAmpES[371] = {};
    float potlidFreES[371] = {};
    float potlidPhaES[371] = {};
    

    float djembeFreES[371] = {};
    float djembeAmpES[371] = {};
    float djembeAlpES[371] = {};
    float djembePhaES[371] = {};

    float TanpuraFreES[371] = {};
    float TanpuraAmpES[371] = {};
    float TanpuraAlpES[371] = {};
    float TanpuraPhaES[371] = {};

    float BanjoFreES[371] = {};
    float BanjoAmpES[371] = {};
    float BanjoAlpES[371] = {};
    float BanjoPhaES[371] = {};

    float BazoukiFreES[371] = {};
    float BazoukiAmpES[371] = {};
    float BazoukiAlpES[371] = {};
    float BazoukiPhaES[371] = {};

    float GuitarFreES[371] = {};
    float GuitarAmpES[371] = {};
    float GuitarAlpES[371] = {};
    float GuitarPhaES[371] = {};

    //---------------------------------------------------------------------------------------------------


    float* phaES = djembePhaES;
    float* freES = djembeFreES;
    float* alpES = djembeAlpES;
    float* ampES = djembeAmpES;


    float fs;


    // MY CODE
private:

    float* mCircularBufferL;
    float* mCircularBufferR;

    int newIR;


    juce::AudioParameterFloat* mGainParam;
    float mGainParamSmooth;
    juce::AudioParameterFloat* mFreqParam;
    float mFreqParamSmooth;
    juce::AudioParameterFloat* mAlphParam;
    float mAlphParamSmooth;
    juce::AudioParameterFloat* mWetDryParam;
    float mWetDryParamSmooth;

    juce::AudioParameterInt* mIRParam;
    int mIR;

    int preIR;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterTestAudioProcessor)
};
