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

void Stutter::processSamples(double *inputbuffer, double *outputbuffer, int nFrames) {
    for (int i = 0; i < nFrames; i++) {
        outputbuffer[i] = inputbuffer[i] * (((tanh(sin(mPhase) * 200.)) / 2.) + 0.5);
        mPhase += (mSpeed * (1. / (60. / mBPM))) * 2. * M_PI / mSampleRate;
    }
}
