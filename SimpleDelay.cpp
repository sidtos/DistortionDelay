#include "SimpleDelay.h"
#include "math.h"

void SimpleDelay::setSampleRate(double sampleRate) {
    mSampleRate = sampleRate;
    delayBuffer1 = new double [mSampleRate];
    delayBuffer2 = new double [mSampleRate];
    sampleCount = 0;
}

void SimpleDelay::setTapGain(double tapGain) {
    mTapGain = tapGain;
}

void SimpleDelay::setTapDelay(double tapDelay) {
    mTapDelay = tapDelay;
    mOutDelay = mSampleRate * (0.001 * mTapDelay);
}

void SimpleDelay::processSamples(double *inputbuffer1, double *inputbuffer2, double *outputbuffer1, double* outputbuffer2, int nFrames) {
    
    for (int i=0; i < nFrames; i++) {
        double temp1 = inputbuffer1[i];
        double temp2 = inputbuffer2[i];
        
        outputbuffer1[i] = (inputbuffer1[i] + (delayBuffer1[sampleCount] * mTapGain));
        outputbuffer2[i] = (inputbuffer2[i] + (delayBuffer2[sampleCount] * mTapGain));
        delayBuffer1[sampleCount] = temp1;
        delayBuffer2[sampleCount] = temp2;
        sampleCount++;
        if (sampleCount > mOutDelay)
            sampleCount = 0;
    }
}