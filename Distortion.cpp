#include "Distortion.h"
#include "math.h"

void Distortion::setSampleRate(double sampleRate) {
    mSampleRate = sampleRate;
}

void Distortion::setThreshold(double threshold) {
    mThreshold = threshold;
}

void Distortion::processSamples(double *inputbuffer, double *outputbuffer, int nFrames) {
    for (int i = 0; i < nFrames; i++) {
        if(inputbuffer[i] >= 0) {
            outputbuffer[i] = fmin(inputbuffer[i], mThreshold);
        } else {
            outputbuffer[i] = fmax(inputbuffer[i], -mThreshold);
        }
        outputbuffer[i] /= mThreshold;
    }
}
