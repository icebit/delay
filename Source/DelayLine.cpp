#include "DelayLine.h"

DelayLine::DelayLine(int maxDelayInSamples, int sampleRate) {
    buffer.resize(maxDelayInSamples, 0.0f);
}

float DelayLine::processSample(float inputSample) {
    int readIndex = (writeIndex - delayInSamples + buffer.size()) % buffer.size();

    float delayedSample = buffer[readIndex];

    buffer[writeIndex] = inputSample;

    writeIndex = (writeIndex + 1) % buffer.size();

    return delayedSample;
}

void DelayLine::setDelayTime(int delaySamples) {
    delayInSamples = delaySamples;
}
