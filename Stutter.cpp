#include "Stutter.h"
#include "math.h"

void Stutter::setSampleRate(double sampleRate) {
    mSampleRate = sampleRate;
}

void Stutter::setBPM(double bpm) {
    mBPM = bpm;
}

void Stutter::setSpeed(double speed) {
    mSpeed = speed;
}

void Stutter::processSamples(double* inputbuffer1, double* inputbuffer2, double* outputbuffer1, double* outputbuffer2, int nFrames) {
    
    for (int i = 0; i < nFrames; i++) {
        outputbuffer1[i] = inputbuffer1[i] * (((tanh(sin(mPhase) * 200.)) / 2.) + 0.5);
        outputbuffer2[i] = inputbuffer2[i] * (((tanh(sin(mPhase) * 200.)) / 2.) + 0.5);
        mPhase += (mSpeed * (1. / (60. / mBPM))) * 2. * M_PI / mSampleRate;
    }
}
