/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FilterTestAudioProcessorEditor::FilterTestAudioProcessorEditor (FilterTestAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    mGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    mGainSlider.setComponentID(getComponentID());
    mGainSlider.setRange(0.0f, 1.0f, 0.01f);
    mGainSlider.setValue(0.5f);
    mGainSlider.addListener(this);
    addAndMakeVisible(mGainSlider);

    mGainSliderLabel.setText("Gain", juce::NotificationType::dontSendNotification);
    mGainSliderLabel.attachToComponent(&mGainSlider, false);
    addAndMakeVisible(mGainSliderLabel);

    mFreqSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    mFreqSlider.setComponentID(getComponentID());
    mFreqSlider.setRange(-200.0f, 200.0f, 0.01f);
    mFreqSlider.setValue(0.0f);
    mFreqSlider.addListener(this);
    addAndMakeVisible(mFreqSlider);

    mFreqSliderLabel.setText("Freq", juce::NotificationType::dontSendNotification);
    mFreqSliderLabel.attachToComponent(&mFreqSlider, false);
    addAndMakeVisible(mFreqSliderLabel);

    mAlphSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mAlphSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    mAlphSlider.setComponentID(getComponentID());
    mAlphSlider.setRange(0.1f, 1.0f, 0.01f);
    mAlphSlider.setValue(1.0f);
    mAlphSlider.addListener(this);
    addAndMakeVisible(mAlphSlider);

    mAlphSliderLabel.setText("Alpha", juce::NotificationType::dontSendNotification);
    mAlphSliderLabel.attachToComponent(&mAlphSlider, false);
    addAndMakeVisible(mAlphSliderLabel);

    mAmpSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mAmpSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    mAmpSlider.setComponentID(getComponentID());
    mAmpSlider.setRange(0.0f, 1, 0.01f);
    mAmpSlider.setValue(1.0f);
    mAmpSlider.addListener(this);
    addAndMakeVisible(mAmpSlider);

    mAmpSliderLabel.setText("Amp", juce::NotificationType::dontSendNotification);
    mAmpSliderLabel.attachToComponent(&mAmpSlider, false);
    addAndMakeVisible(mAmpSliderLabel);

    mWetDrySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mWetDrySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    mWetDrySlider.setComponentID(getComponentID());
    mWetDrySlider.setRange(0.0f, 1, 0.01f);
    mWetDrySlider.setValue(1.0f);
    mWetDrySlider.addListener(this);
    addAndMakeVisible(mWetDrySlider);

    mWetDrySliderLabel.setText("Wet/Dry", juce::NotificationType::dontSendNotification);
    mWetDrySliderLabel.attachToComponent(&mWetDrySlider, false);
    addAndMakeVisible(mWetDrySliderLabel);


    setSize(600, 600);
}

FilterTestAudioProcessorEditor::~FilterTestAudioProcessorEditor()
{
}

//==============================================================================
void FilterTestAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void FilterTestAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    mGainSlider.setBounds(getWidth() / 2 - 0, getHeight() / 2 - 75, 100, 150);
    mFreqSlider.setBounds(getWidth() / 2 - 75, getHeight() / 2 - 75, 100, 150);
    mAlphSlider.setBounds(getWidth() / 2 - 150, getHeight() / 2 - 75, 100, 150);
    mAmpSlider.setBounds(getWidth() / 2 - 225, getHeight() / 2 - 75, 100, 150);
    mWetDrySlider.setBounds(getWidth() / 2 - 300, getHeight() / 2 - 75, 100, 150);
}

void FilterTestAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &mGainSlider)
    {
        audioProcessor.mGain = mGainSlider.getValue();
    }
    if (slider == &mAmpSlider)
    {
        audioProcessor.mAmp = mAmpSlider.getValue();
    }
    if (slider == &mAlphSlider)
    {
        audioProcessor.mAlph = mAlphSlider.getValue();
    }
    if (slider == &mWetDrySlider)
    {
        audioProcessor.mWetDry = mWetDrySlider.getValue();
    }
    if (slider == &mFreqSlider)
    {
        audioProcessor.mFreq = mFreqSlider.getValue();
    }
}