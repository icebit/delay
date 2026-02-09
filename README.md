https://juce.com/tutorials/tutorial_dsp_delay_line/
Great! Let me walk you through how a circular buffer delay line works.

  The Core Concept

  A circular buffer is like a tape loop that plays back delayed audio. Here's the key
  idea:

  ┌─────────────────────────────────────────┐
  │  0  │  1  │  2  │  3  │  4  │  5  │  6  │  ← Buffer (stores past samples)
  └─────────────────────────────────────────┘
             ▲                       ▲
          Read                     Write
         (old data)              (new data)

  As new samples come in, you:
  1. Write incoming audio at the write pointer
  2. Read old audio from the read pointer (delay time ago)
  3. Mix the delayed audio with the current sample
  4. Advance both pointers forward (wrapping around at the end)

  Simple Example

  class SimpleDelayLine {
  private:
      std::vector<float> buffer;
      int writeIndex = 0;
      int delayInSamples = 0;

  public:
      SimpleDelayLine(int maxDelayInSamples, int sampleRate) {
          buffer.resize(maxDelayInSamples, 0.0f);
      }

      float processSample(float inputSample) {
          // Calculate where to read (delay time ago)
          int readIndex = (writeIndex - delayInSamples + buffer.size()) % buffer.size();

          // Get the delayed sample
          float delayedSample = buffer[readIndex];

          // Write new sample to buffer
          buffer[writeIndex] = inputSample;

          // Move write pointer forward (wrap around)
          writeIndex = (writeIndex + 1) % buffer.size();

          // Return delayed sample (caller will mix with input)
          return delayedSample;
      }
  };

  Visual Example: What Happens Over Time

  Say your buffer is 5 samples and delay is 2 samples:

  Step 1: Write sample 0.5
  Index:  0    1    2    3    4
  Data:  [0.5  0    0    0    0]  ← write at 0
          W

  Step 2: Write sample 0.3, read 2 samples back
  Index:  0    1    2    3    4
  Data:  [0.5  0.3  0    0    0]  ← write at 1
                      ^
                read from index -1 wrapped = 3 → 0 (empty)

  Step 3: Write sample 0.7, read 2 samples back
  Index:  0    1    2    3    4
  Data:  [0.5  0.3  0.7  0    0]  ← write at 2
                      ^
                read from index 0 → 0.5 (first delayed output!)

  Step 4: Write sample 0.2, read 2 samples back
  Index:  0    1    2    3    4
  Data:  [0.5  0.3  0.7  0.2  0]  ← write at 3
                           ^
                      read from index 1 → 0.3

  Key Operations

  1. Calculate read index (looking back in time):
  int readIndex = (writeIndex - delayInSamples + buffer.size()) % buffer.size();
  The + buffer.size() prevents negative numbers; % buffer.size() wraps around.

  2. Feedback (optional):
  // Mix delayed signal with input before writing
  float mixedInput = inputSample + (delayedSample * feedbackAmount);
  buffer[writeIndex] = mixedInput;  // Feed delayed signal back in

  3. Wet/Dry Mix:
  // After getting delayed sample, blend with original
  float output = inputSample * (1.0f - mix) + delayedSample * mix;

  ★ ─────────────────────────────────────
  Key insight: The modulo operator (%) is critical—it lets you treat a fixed array as an
  infinite loop. Without it, you'd need to check boundaries and reset pointers manually.
  The delay time is determined purely by how far back you read; changing the read offset
  changes the delay time in real-time.
  ─────────────────────────────────────

  Would you like me to implement a full delay plugin for your JUCE project using this
  circular buffer approach?
