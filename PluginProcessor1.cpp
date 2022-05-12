/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



# define M_PI           3.14159265358979323846  /* pi */


//==============================================================================
FilterTestAudioProcessor::FilterTestAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif //CONSTRUCTOR BELOW
{   
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    std::string potlidFileArr[4] = { "potlidIRalpES.txt", "potlidIRampES.txt", "potlidIRfreES.txt", "potlidIRphaES.txt" };
    for (int i = 0; i < 3; i++) 
    {
        std::ifstream fileLocation(dir + potlidFileArr[i]);

        std::string value;
        int filterNum = 0;

        while (!fileLocation.eof())
        {
            getline(fileLocation, value, '\n');

            if (i == 0)
            {
                potlidAlpES[filterNum] = ::atof(value.c_str());
            }
            if (i == 1)
            {
                potlidAmpES[filterNum] = ::atof(value.c_str()) * 1.5;
            }
            if (i == 2)
            {
                potlidFreES[filterNum] = ::atof(value.c_str());
            }
            if (i == 3)
            {
                potlidPhaES[filterNum] = ::atof(value.c_str());
            }

            filterNum += 1;
        }
        fileLocation.close();
    }

    

    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------

    std::string djembeFileArr[4] = { "djembe2IRalpES.txt", "djembe2IRampES.txt", "djembe2IRfreES.txt", "djembe2IRphaES.txt" };
    for (int i = 0; i < 3; i++)
    {
        std::ifstream fileLocation(dir + djembeFileArr[i]);

        std::string value;
        int filterNum = 0;

        while (!fileLocation.eof())
        {
            getline(fileLocation, value, '\n');

            if (i == 0)
            {
                djembeAlpES[filterNum] = ::atof(value.c_str());
            }
            if (i == 1)
            {
                djembeAmpES[filterNum] = ::atof(value.c_str());
            }
            if (i == 2)
            {
                djembeFreES[filterNum] = ::atof(value.c_str());
            }
            if (i == 3)
            {
                djembePhaES[filterNum] = ::atof(value.c_str());
            }

            filterNum += 1;
        }
        fileLocation.close();
    }

    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------

    std::string TanpuraFileArr[4] = { "TanpuraIRalpES.txt", "TanpuraIRampES.txt", "TanpuraIRfreES.txt", "TanpuraIRphaES.txt" };
    for (int i = 0; i < 3; i++)
    {
        std::ifstream fileLocation(dir + TanpuraFileArr[i]);

        std::string value;
        int filterNum = 0;

        while (!fileLocation.eof())
        {
            getline(fileLocation, value, '\n');

            if (i == 0)
            {
                TanpuraAlpES[filterNum] = ::atof(value.c_str());
            }
            if (i == 1)
            {
                TanpuraAmpES[filterNum] = ::atof(value.c_str());
            }
            if (i == 2)
            {
                TanpuraFreES[filterNum] = ::atof(value.c_str());
            }
            if (i == 3)
            {
                TanpuraPhaES[filterNum] = ::atof(value.c_str());
            }

            filterNum += 1;
        }
        fileLocation.close();
    }

    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------

    std::string BanjoFileArr[4] = { "BanjoIRalpES.txt", "BanjoIRampES.txt", "BanjoIRfreES.txt", "BanjoIRphaES.txt" };
    for (int i = 0; i < 3; i++)
    {
        std::ifstream fileLocation(dir + BanjoFileArr[i]);

        std::string value;
        int filterNum = 0;

        while (!fileLocation.eof())
        {
            getline(fileLocation, value, '\n');

            if (i == 0)
            {
                BanjoAlpES[filterNum] = ::atof(value.c_str());
            }
            if (i == 1)
            {
                BanjoAmpES[filterNum] = ::atof(value.c_str()) * 1.5;
            }
            if (i == 2)
            {
                BanjoFreES[filterNum] = ::atof(value.c_str());
            }
            if (i == 3)
            {
                BanjoPhaES[filterNum] = ::atof(value.c_str());
            }

            filterNum += 1;
        }
        fileLocation.close();
    }

    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------

    std::string BazoukiFileArr[4] = { "BazoukiIRalpES.txt", "BazoukiIRampES.txt", "BazoukiIRfreES.txt", "BazoukiIRphaES.txt" };
    for (int i = 0; i < 3; i++)
    {
        std::ifstream fileLocation(dir + BazoukiFileArr[i]);

        std::string value;
        int filterNum = 0;

        while (!fileLocation.eof())
        {
            getline(fileLocation, value, '\n');

            if (i == 0)
            {
                BazoukiAlpES[filterNum] = ::atof(value.c_str());
            }
            if (i == 1)
            {
                BazoukiAmpES[filterNum] = ::atof(value.c_str())*1.5;
            }
            if (i == 2)
            {
                BazoukiFreES[filterNum] = ::atof(value.c_str());
            }
            if (i == 3)
            {
                BazoukiPhaES[filterNum] = ::atof(value.c_str());
            }

            filterNum += 1;
        }
        fileLocation.close();
    }

    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------

    std::string GuitarFileArr[4] = { "GuitarIRalpES.txt", "GuitarIRampES.txt", "GuitarIRfreES.txt", "GuitarIRphaES.txt" };
    for (int i = 0; i < 3; i++)
    {
        std::ifstream fileLocation(dir + GuitarFileArr[i]);

        std::string value;
        int filterNum = 0;

        while (!fileLocation.eof())
        {
            getline(fileLocation, value, '\n');

            if (i == 0)
            {
                GuitarAlpES[filterNum] = ::atof(value.c_str());
            }
            if (i == 1)
            {
                GuitarAmpES[filterNum] = ::atof(value.c_str())*0.25;
            }
            if (i == 2)
            {
                GuitarFreES[filterNum] = ::atof(value.c_str());
            }
            if (i == 3)
            {
                GuitarPhaES[filterNum] = ::atof(value.c_str());
            }

            filterNum += 1;
        }
        fileLocation.close();
    }
    //----------------------------------------------------------------------------------------






    addParameter(mGainParam = new juce::AudioParameterFloat("gain", "Gain", 0.0, 1.0, 1.0));
    mGainParamSmooth = mGainParam->get();

    addParameter(mFreqParam = new juce::AudioParameterFloat("freq", "Freq", -1000.0, 1000.0, 0.0));
    mFreqParamSmooth = mFreqParam->get();

    addParameter(mAlphParam = new juce::AudioParameterFloat("alph", "Alph", 0.000, 1.0, 1.0));
    mAlphParamSmooth = mAlphParam->get();

    addParameter(mAmpParam = new juce::AudioParameterFloat("amp", "Amp", 0.0, 1.0, 1.0));
    mAmpParamSmooth = mAmpParam->get();

    addParameter(mWetDryParam = new juce::AudioParameterFloat("wet_dry", "Wet/Dry", 0.0, 1.0, 1.0));
    mWetDryParamSmooth = mWetDryParam->get();

    addParameter(mIRParam = new juce::AudioParameterInt("ir", "IR", 1.0, 6.0, 1.0));

}

FilterTestAudioProcessor::~FilterTestAudioProcessor()
{
}

//==============================================================================
const juce::String FilterTestAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FilterTestAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FilterTestAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FilterTestAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FilterTestAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FilterTestAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FilterTestAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FilterTestAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FilterTestAudioProcessor::getProgramName (int index)
{
    return {};
}

void FilterTestAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FilterTestAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    x = 0;

    out = 0;

    fs = getSampleRate();

    for (int i = 104; i < 371; i++)
    {
        djembeFreES[i] = 0;
        djembeAlpES[i] = 0;
        djembeAmpES[i] = 0;
        djembePhaES[i] = 0;
    }

    for (int i = 314; i < 371; i++)
    {
        potlidFreES[i] = 0;
        potlidAlpES[i] = 0;
        potlidAmpES[i] = 0;
        potlidPhaES[i] = 0;
    }

    for (int i = 203; i < 371; i++)
    {
        GuitarFreES[i] = 0;
        GuitarAlpES[i] = 0;
        GuitarAmpES[i] = 0;
        GuitarPhaES[i] = 0;
    }

    for (int i = 348; i < 371; i++)
    {
        BanjoFreES[i] = 0;
        BanjoAlpES[i] = 0;
        BanjoAmpES[i] = 0;
        BanjoPhaES[i] = 0;
    }

    for (int i = 317; i < 371; i++)
    {
        BazoukiFreES[i] = 0;
        BazoukiAlpES[i] = 0;
        BazoukiAmpES[i] = 0;
        BazoukiPhaES[i] = 0;
    }

}

void FilterTestAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FilterTestAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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







void FilterTestAudioProcessor::calculate_coefficients(float f, float alpha, float A, int IR)
{
    if (preIR != IR)                    //ensures that there are no values left over from filters when switching to a lower filter amount
    {
        for (int i = 0; i < M; i++)     
        {
            xz[i] = 0;
            yz[i] = 0;
            yzz[i] = 0;
            y[i] = 0;
        }
        
    }

    preIR = IR;                         //updates previous IR value

    if (IR < 2)
    {
        phaES = djembePhaES;
        freES = djembeFreES;
        alpES = djembeAlpES;
        ampES = djembeAmpES;
    }
    else if (IR < 3)
    {
        phaES = potlidPhaES;
        freES = potlidFreES;
        alpES = potlidAlpES;
        ampES = potlidAmpES;

    }
    else if (IR < 4)
    {
        phaES = GuitarPhaES;
        freES = GuitarFreES;
        alpES = GuitarAlpES;
        ampES = GuitarAmpES;

    }
    else if (IR < 5)
    {
        phaES = BanjoPhaES;
        freES = BanjoFreES;
        alpES = BanjoAlpES;
        ampES = BanjoAmpES;

    }
    else if (IR < 6)
    {
        phaES = BazoukiPhaES;
        freES = BazoukiFreES;
        alpES = BazoukiAlpES;
        ampES = BazoukiAmpES;

    }
    else
    {
        phaES = TanpuraPhaES;
        freES = TanpuraFreES;
        alpES = TanpuraAlpES;
        ampES = TanpuraAmpES;
    }

    for (int i = 1; i < M; i++) {

        

        f_i = f + freES[i];
        alpha_i = alpha * alpES[i];
        A_i = A * ampES[i];


        if (f_i > 20000) {	//ensures there is not a sudden drop in amplitude at Nyquist
            A_i = A_i * (1 + (f_i - 20000) * (-1 / 2050));
        }
        if (f_i > 22050) {	//ensures frequencies above Nyquist aren't heard, avoiding aliasing
            A_i = 0;
        }



        if (f_i < 20) {		//ensures there is not a sudden drop in amplitude at 0Hz
            A_i = A_i * (1 + (f_i - 20) * (1 / 20));
        }
        if (f_i < 0) {		//ensures negative frequencies aren't used
            A_i = 0.0;
        }

        Phase = phaES[i] * (M_PI / 180);

        C = cos(Phase);
        S = sin(Phase);

        omega = 2 * M_PI * f_i;

        R = exp(-alpha_i / fs);


        a1[i] = -2 * R * cos(omega / fs);
        a2[i] = pow(R, 2);

        b1[i] = (0.25*A_i * R) * (C * sin(omega / fs) - S * cos(omega / fs));
        b0[i] = (0.25*A_i * R) * S;

    }

}







void FilterTestAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    //----------------------------------------------------------------------------------
    mGainParamSmooth = mGainParamSmooth - 0.04 * (mGainParamSmooth - mGainParam->get());
    mFreqParamSmooth = mFreqParamSmooth - 0.04 * (mFreqParamSmooth - mFreqParam->get());
    mAlphParamSmooth = mAlphParamSmooth - 0.04 * (mAlphParamSmooth - mAlphParam->get());
    mAmpParamSmooth = mAmpParamSmooth - 0.04 * (mAmpParamSmooth - mAmpParam->get());
    mWetDryParamSmooth = mWetDryParamSmooth - 0.04 * (mWetDryParamSmooth - mWetDryParam->get());

    mIR = mIRParam->get();

    calculate_coefficients(mFreqParamSmooth, mAlphParamSmooth, 1.0, mIR);

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

    float* channelLeft = buffer.getWritePointer(0);
    float* channelRight = buffer.getWritePointer(1);
    
    
        //auto* channelData = buffer.getWritePointer (channel);

    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {

        x = channelLeft[sample];
        out = 0;
        for (int j = 0; j < M; j++) {
            y[j] = (b0[j] * x) +(b1[j] * xz[j]) - (a1[j] * yz[j]) - (a2[j] * yzz[j]);

            yzz[j] = yz[j];
            yz[j] = y[j];

            xz[j] = x;

            out = out + y[j];
        }

        channelLeft[sample] = mGainParamSmooth *(mWetDryParamSmooth *out + (mWetDryParamSmooth -1)*x);
        channelRight[sample] = mGainParamSmooth *(mWetDryParamSmooth *out + (mWetDryParamSmooth - 1)*x);
        }
        // ..do something to the data...
}

//==============================================================================
bool FilterTestAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FilterTestAudioProcessor::createEditor()
{
    return new FilterTestAudioProcessorEditor (*this);
}

//==============================================================================
void FilterTestAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FilterTestAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FilterTestAudioProcessor();
}
