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
class FilterTestAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                        public juce::Slider::Listener
{
public:
    FilterTestAudioProcessorEditor (FilterTestAudioProcessor&);
    ~FilterTestAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;

private:

    juce::Slider mGainSlider;
    juce::Slider mWetDrySlider;
    juce::Slider mFreqSlider;
    juce::Slider mAlphSlider;
    juce::Slider mAmpSlider;

    juce::Label mGainSliderLabel;
    juce::Label mWetDrySliderLabel;
    juce::Label mFreqSliderLabel;
    juce::Label mAlphSliderLabel;
    juce::Label mAmpSliderLabel;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FilterTestAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterTestAudioProcessorEditor)
};
