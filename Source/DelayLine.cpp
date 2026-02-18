#include "DelayLine.h"
#include <JuceHeader.h>

DelayLine::DelayLine(int maxDelayInSamples) {
    buffer.resize(maxDelayInSamples, 0.0f);
    setDelayTime(0.5f * 44000);
}

float DelayLine::processSample(float inputSample) {
    int readIndex = (writeIndex - delayInSamples) % static_cast<int>(buffer.size()); // UNSAFE

    float delayedSample = buffer[readIndex];

    buffer[writeIndex] = inputSample;

    writeIndex = (writeIndex + 1) % buffer.size();

    return delayedSample;
}

void DelayLine::setDelayTime(int delaySamples) {
    delayInSamples = juce::jlimit(0, (int)buffer.size() - 1, delaySamples);
}
