#include "SimpleDelay.h"
#include "math.h"

void SimpleDelay::setSampleRate(double sampleRate) {
    mSampleRate = sampleRate;
    delayBuffer1 = new double [mSampleRate];
    delayBuffer2 = new double [mSampleRate];
    sampleCount = 0;
    updateBuffer();
}

void SimpleDelay::setTapGain(double tapGain) {
    mTapGain = tapGain;
}

void SimpleDelay::setTapDelay(double tapDelay) {
    mTapDelay = tapDelay;
    updateBuffer();
}

void SimpleDelay::updateBuffer() {
    mOutDelay = mSampleRate * (0.001 * mTapDelay);
}

void SimpleDelay::processSamples(double *inputbuffer1, double *inputbuffer2, double *outputbuffer1, double *outputbuffer2, int nFrames) {
    
    for (int i=0; i < nFrames; i++) {
        //temporary buffers
        double temp1 = inputbuffer1[i];
        double temp2 = inputbuffer2[i];
        //outputs wet signal only
        outputbuffer1[i] = delayBuffer1[sampleCount] * mTapGain;
        outputbuffer2[i] = delayBuffer2[sampleCount] * mTapGain;
        //fill delay buffers
        delayBuffer1[sampleCount] = temp1;
        delayBuffer2[sampleCount] = temp2;
        //increase position
        sampleCount++;
        //flip the buffer
        if (sampleCount > mOutDelay)
            sampleCount = 0;
    }
}