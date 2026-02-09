/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DelayAudioProcessorEditor::DelayAudioProcessorEditor (DelayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    delayTimeSlider (juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox),
    mixSlider (juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox)
{
  delayTimeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "delayTime", delayTimeSlider);
  mixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "mix", mixSlider);

  delayTimeSlider.setTextValueSuffix(" ms");
  mixSlider.setTextValueSuffix("");

  delayTimeLabel.setText("Delay Time", juce::dontSendNotification);
  delayTimeLabel.setFont(juce::FontOptions(14.0f));
  delayTimeLabel.setJustificationType(juce::Justification::centred);
  delayTimeLabel.setEditable(false);

  mixLabel.setText("Mix", juce::dontSendNotification);
  mixLabel.setFont(juce::FontOptions(14.0f));
  mixLabel.setJustificationType(juce::Justification::centred);
  mixLabel.setEditable(false);

  addAndMakeVisible(delayTimeSlider);
  addAndMakeVisible(mixSlider);
  addAndMakeVisible(delayTimeLabel);
  addAndMakeVisible(mixLabel);

  setSize (400, 300);
}

DelayAudioProcessorEditor::~DelayAudioProcessorEditor()
{
}

//==============================================================================
void DelayAudioProcessorEditor::paint (juce::Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void DelayAudioProcessorEditor::resized()
{

    auto bounds = getLocalBounds();
    auto knobSize = 80;
    auto labelHeight = 25;
    auto spacing = 10;

    auto knobY = bounds.getHeight() / 2 - knobSize / 2 - labelHeight;
    auto labelY = knobY + knobSize + spacing / 2;

    delayTimeSlider.setBounds(bounds.getWidth() / 4 - knobSize / 2, knobY, knobSize, knobSize);
    delayTimeLabel.setBounds(bounds.getWidth() / 4 - knobSize / 2, labelY, knobSize, labelHeight);

    mixSlider.setBounds(bounds.getWidth() * 3 / 4 - knobSize / 2, knobY, knobSize, knobSize);
    mixLabel.setBounds(bounds.getWidth() * 3 / 4 - knobSize / 2, labelY, knobSize, labelHeight);
}
