#include "Distortion.h"
#include "math.h"

void Distortion::setSampleRate(double sampleRate) {
    mSampleRate = sampleRate;
}

void Distortion::setThreshold(double threshold) {
    mThreshold = threshold;
}

void Distortion::processSamples(double* inputbuffer1, double* inputbuffer2, double* outputbuffer1, double* outputbuffer2, int nFrames) {
    
    for (int i = 0; i < nFrames; i++) {
        
        //left
        if(inputbuffer1[i] >= 0) {
            outputbuffer1[i] = fmin(inputbuffer1[i], mThreshold);
        } else {
            outputbuffer1[i] = fmax(inputbuffer1[i], -mThreshold);
        }
        outputbuffer1[i] /= mThreshold;
        
        //right
        if(inputbuffer2[i] >= 0) {
            outputbuffer2[i] = fmin(inputbuffer2[i], mThreshold);
        } else {
            outputbuffer2[i] = fmax(inputbuffer2[i], -mThreshold);
        }
        outputbuffer2[i] /= mThreshold;
    }
    
}
