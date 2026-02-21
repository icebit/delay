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
    sizeSlider (juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox),
    spreadSlider (juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox),
    feedbackSlider (juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox),
    mixSlider (juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox)
{
  sizeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "size", sizeSlider);
  spreadAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "spread", spreadSlider);
  feedbackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "feedback", feedbackSlider);
  mixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "mix", mixSlider);

  auto setupLabel = [](juce::Label& label, const juce::String& text) {
      label.setText (text, juce::dontSendNotification);
      label.setFont (juce::FontOptions (14.0f));
      label.setJustificationType (juce::Justification::centred);
      label.setEditable (false);
  };

  setupLabel (sizeLabel, "Size");
  setupLabel (spreadLabel, "Spread");
  setupLabel (feedbackLabel, "Feedback");
  setupLabel (mixLabel, "Mix");

  addAndMakeVisible (sizeSlider);
  addAndMakeVisible (spreadSlider);
  addAndMakeVisible (feedbackSlider);
  addAndMakeVisible (mixSlider);
  addAndMakeVisible (sizeLabel);
  addAndMakeVisible (spreadLabel);
  addAndMakeVisible (feedbackLabel);
  addAndMakeVisible (mixLabel);

  setSize (500, 300);
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
    auto numKnobs = 4;

    auto knobY = bounds.getHeight() / 2 - knobSize / 2 - labelHeight;
    auto labelY = knobY + knobSize + spacing / 2;

    auto placeKnob = [&](juce::Slider& slider, juce::Label& label, int index) {
        auto x = bounds.getWidth() * (index * 2 + 1) / (numKnobs * 2) - knobSize / 2;
        slider.setBounds (x, knobY, knobSize, knobSize);
        label.setBounds (x, labelY, knobSize, labelHeight);
    };

    placeKnob (sizeSlider, sizeLabel, 0);
    placeKnob (spreadSlider, spreadLabel, 1);
    placeKnob (feedbackSlider, feedbackLabel, 2);
    placeKnob (mixSlider, mixLabel, 3);
}
