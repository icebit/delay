#include "DelayLine.h"
#include <JuceHeader.h>

DelayLine::DelayLine(int maxDelayInSamples, int sampleRate) {
    buffer.resize(maxDelayInSamples, 0.0f);
    setDelayTime(0.5f * sampleRate);  // Default 500ms delay
}

float DelayLine::processSample(float inputSample) {
    int readIndex = (writeIndex - delayInSamples + buffer.size()) % buffer.size();

    float delayedSample = buffer[readIndex];

    buffer[writeIndex] = inputSample;

    writeIndex = (writeIndex + 1) % buffer.size();

    return delayedSample;
}

void DelayLine::setDelayTime(int delaySamples) {
    delayInSamples = juce::jlimit(0, (int)buffer.size() - 1, delaySamples);
}
