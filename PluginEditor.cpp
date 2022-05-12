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

    
    //---------------------------------------------------------------------------------------------------------------
{
    setSize(750, 500);

    //---------------------------------------------------------------------------------------------------------------
    mFrequencyResetButton.setBounds(340, 370, 20, 20);
    mFrequencyResetButton.onClick = [this]() {FrequencyReset();};
    addAndMakeVisible(mFrequencyResetButton);

    mFrequencyResetButtonLabel.setText("Frequency Reset", juce::dontSendNotification);
    mFrequencyResetButtonLabel.attachToComponent(&mFrequencyResetButton, true);
    addAndMakeVisible(mFrequencyResetButtonLabel);
    //---------------------------------------------------------------------------------------------------------------



    mPresetCombo.setBounds(220, 40, 150, 30);

    mPresetCombo.addItem("Djembe", 1);
    mPresetCombo.addItem("Sauce Pan", 2);
    mPresetCombo.addItem("Guitar", 3);
    mPresetCombo.addItem("Banjo", 4);
    mPresetCombo.addItem("Bazouki", 5);


    mPresetCombo.onChange = [this] { PresetSelector(); };
    mPresetCombo.setSelectedId(1);

    addAndMakeVisible(mPresetCombo);


    //Access the processor params
    auto& params = processor.getParameters();
    juce::AudioParameterFloat* mGainParam = (juce::AudioParameterFloat*)params.getUnchecked(0);
    juce::AudioParameterFloat* mFreqParam = (juce::AudioParameterFloat*)params.getUnchecked(1);
    juce::AudioParameterFloat* mAlphParam = (juce::AudioParameterFloat*)params.getUnchecked(2);
    juce::AudioParameterFloat* mWetDryParam = (juce::AudioParameterFloat*)params.getUnchecked(3);
    juce::AudioParameterInt* mIRParam = (juce::AudioParameterInt*)params.getUnchecked(4);

    //---------------------------------------------------------------------------------------------------------------
    mGainSlider.setBounds(20, 30, 120, 120);
    mGainSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    mGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mGainSlider.setComponentID(getComponentID());
    mGainSlider.setRange(mGainParam->range.start, mGainParam->range.end);
    mGainSlider.setValue(*mGainParam);

    mGainSliderLabel.setText("Gain", juce::dontSendNotification);
    mGainSliderLabel.attachToComponent(&mGainSlider, false);
    addAndMakeVisible(mGainSliderLabel);

    addAndMakeVisible(mGainSlider);

    mGainSlider.onValueChange = [this, mGainParam] { *mGainParam = mGainSlider.getValue(); };
    mGainSlider.onDragStart = [mGainParam] { mGainParam->beginChangeGesture(); };
    mGainSlider.onDragEnd = [mGainParam] { mGainParam->endChangeGesture(); };

    //---------------------------------------------------------------------------------------------------------------
    mFreqSlider.setBounds(10, 320, 580, 60);
    mFreqSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    mFreqSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mFreqSlider.setComponentID(getComponentID());
    mFreqSlider.setRange(mFreqParam->range.start, mFreqParam->range.end);
    mFreqSlider.setValue(*mFreqParam);

    mFreqSliderLabel.setText("-1000Hz                                                Frequency                                                +1000Hz", juce::dontSendNotification);
    mFreqSliderLabel.attachToComponent(&mFreqSlider, false);
    addAndMakeVisible(mFreqSliderLabel);

    addAndMakeVisible(mFreqSlider);

    mFreqSlider.onValueChange = [this, mFreqParam] { *mFreqParam = mFreqSlider.getValue(); };
    mFreqSlider.onDragStart = [mFreqParam] { mFreqParam->beginChangeGesture(); };
    mFreqSlider.onDragEnd = [mFreqParam] { mFreqParam->endChangeGesture(); };

    //---------------------------------------------------------------------------------------------------------------
    mAlphSlider.setBounds(10, 220, 580, 60);
    mAlphSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    mAlphSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mAlphSlider.setComponentID(getComponentID());
    mAlphSlider.setRange(mAlphParam->range.start, mAlphParam->range.end);
    mAlphSlider.setValue(*mAlphParam);

    mAlphSliderLabel.setText("infinite                                                       Alpha                                                       unaltered", juce::dontSendNotification);
    mAlphSliderLabel.attachToComponent(&mAlphSlider, false);
    addAndMakeVisible(mAlphSliderLabel);

    addAndMakeVisible(mAlphSlider);

    mAlphSlider.onValueChange = [this, mAlphParam] { *mAlphParam = mAlphSlider.getValue(); };
    mAlphSlider.onDragStart = [mAlphParam] { mAlphParam->beginChangeGesture(); };
    mAlphSlider.onDragEnd = [mAlphParam] { mAlphParam->endChangeGesture(); };


    //---------------------------------------------------------------------------------------------------------------
    mWetDrySlider.setBounds(450, 30, 120, 120);
    mWetDrySlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    mWetDrySlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mWetDrySlider.setComponentID(getComponentID());
    mWetDrySlider.setRange(mWetDryParam->range.start, mWetDryParam->range.end);
    mWetDrySlider.setValue(*mWetDryParam);

    mWetDrySliderLabel.setText("Wet/Dry", juce::dontSendNotification);
    mWetDrySliderLabel.attachToComponent(&mWetDrySlider, false);
    addAndMakeVisible(mWetDrySliderLabel);

    addAndMakeVisible(mWetDrySlider);

    mWetDrySlider.onValueChange = [this, mWetDryParam] { *mWetDryParam = mWetDrySlider.getValue(); };
    mWetDrySlider.onDragStart = [mWetDryParam] { mWetDryParam->beginChangeGesture(); };
    mWetDrySlider.onDragEnd = [mWetDryParam] { mWetDryParam->endChangeGesture(); };

    //---------------------------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------------------------

    mIRSlider.onValueChange = [this, mIRParam] { *mIRParam = mIRSlider.getValue(); };
    mIRSlider.onDragStart = [mIRParam] { mIRParam->beginChangeGesture(); };
    mIRSlider.onDragEnd = [mIRParam] { mIRParam->endChangeGesture(); };


    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    /*mGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
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

    mWetDrySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mWetDrySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    mWetDrySlider.setComponentID(getComponentID());
    mWetDrySlider.setRange(0.0f, 1, 0.01f);
    mWetDrySlider.setValue(1.0f);
    mWetDrySlider.addListener(this);
    addAndMakeVisible(mWetDrySlider);

    mWetDrySliderLabel.setText("Wet/Dry", juce::NotificationType::dontSendNotification);
    mWetDrySliderLabel.attachToComponent(&mWetDrySlider, false);
    addAndMakeVisible(mWetDrySliderLabel);*/

}

FilterTestAudioProcessorEditor::~FilterTestAudioProcessorEditor()
{
}

//==============================================================================
void FilterTestAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.fillAll(juce::Colours::slategrey);
    g.setColour(juce::Colours::white);
    g.setFont(35.0f);
    g.drawFittedText("Tremolo", getLocalBounds(), juce::Justification::bottomRight, juce::Justification::Justification::horizontallyJustified, 1);

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void FilterTestAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
   /* mGainSlider.setBounds(getWidth() / 2 - 0, getHeight() / 2 - 75, 100, 150);
    mFreqSlider.setBounds(getWidth() / 2 - 75, getHeight() / 2 - 75, 100, 150);
    mAlphSlider.setBounds(getWidth() / 2 - 150, getHeight() / 2 - 75, 100, 150);
    mWetDrySlider.setBounds(getWidth() / 2 - 300, getHeight() / 2 - 75, 100, 150);*/
}

void FilterTestAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &mGainSlider)
    {
        audioProcessor.mGain = mGainSlider.getValue();
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


void FilterTestAudioProcessorEditor::PresetSelector()
{
    switch (mPresetCombo.getSelectedId())
    {
    case 1: //Djembe
        mIRSlider.setValue(1);
        break;



    case 2: //Sauce Pan
        mIRSlider.setValue(2);
        break;



    case 3: //Guitar
        mIRSlider.setValue(3);
        break;



    case 4: //Banjo
        mIRSlider.setValue(4);
        break;



    case 5: //Bazouki
        mIRSlider.setValue(5);
        break;
    }
}

void FilterTestAudioProcessorEditor::FrequencyReset()
{
    mFreqSlider.setValue(0.0f);
}