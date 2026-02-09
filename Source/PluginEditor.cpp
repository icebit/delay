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
    gainSlider (juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox),
    toneSlider (juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox)
{
  gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "gain", gainSlider);
  toneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "tone", toneSlider);

  gainSlider.setTextValueSuffix("");
  toneSlider.setTextValueSuffix("");

  gainLabel.setText("Gain", juce::dontSendNotification);
  gainLabel.setFont(juce::FontOptions(14.0f));
  gainLabel.setJustificationType(juce::Justification::centred);
  gainLabel.setEditable(false);

  toneLabel.setText("Tone", juce::dontSendNotification);
  toneLabel.setFont(juce::FontOptions(14.0f));
  toneLabel.setJustificationType(juce::Justification::centred);
  toneLabel.setEditable(false);

  addAndMakeVisible(gainSlider);
  addAndMakeVisible(toneSlider);
  addAndMakeVisible(gainLabel);
  addAndMakeVisible(toneLabel);

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

    gainSlider.setBounds(bounds.getWidth() / 4 - knobSize / 2, knobY, knobSize, knobSize);
    gainLabel.setBounds(bounds.getWidth() / 4 - knobSize / 2, labelY, knobSize, labelHeight);

    toneSlider.setBounds(bounds.getWidth() * 3 / 4 - knobSize / 2, knobY, knobSize, knobSize);
    toneLabel.setBounds(bounds.getWidth() * 3 / 4 - knobSize / 2, labelY, knobSize, labelHeight);
}
