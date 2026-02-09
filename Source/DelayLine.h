#pragma once

#include <vector>

class DelayLine {
public:
    DelayLine(int maxDelayInSamples, int sampleRate);

    float processSample(float inputSample);
    void setDelayTime(int delaySamples);

private:
    std::vector<float> buffer;
    int writeIndex = 0;
    int delayInSamples = 0;
};
