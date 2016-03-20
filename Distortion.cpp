#include "Distortion.h"
#include "math.h"

void Distortion::setSampleRate(double sampleRate) {
    mSampleRate = sampleRate;
}

void Distortion::setThreshold(double threshold) {
    mThreshold = threshold;
}

void Distortion::processSamples(double inputbuffer1, double inputbuffer2, double &outputbuffer1, double &outputbuffer2, int nFrames) {
    
    //left
    if(inputbuffer1 >= 0) {
        outputbuffer1 = fmin(inputbuffer1, mThreshold);
    } else {
        outputbuffer1 = fmax(inputbuffer1, -mThreshold);
    }
    outputbuffer1 /= mThreshold;
    
    //right
    if(inputbuffer2 >= 0) {
        outputbuffer2 = fmin(inputbuffer2, mThreshold);
    } else {
        outputbuffer2 = fmax(inputbuffer2, -mThreshold);
    }
    outputbuffer2 /= mThreshold;
}
