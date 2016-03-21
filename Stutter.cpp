#include "Stutter.h"
#include "math.h"

void Stutter::setSampleRate(double sampleRate) {
    mSampleRate = sampleRate;
}

void Stutter::setBPM(double bpm) {
    mBPM = bpm;
}

void Stutter::setSpeed(int speed) {
    mSpeed = speed;
}

void Stutter::processSamples(double inputbuffer1, double inputbuffer2, double &outputbuffer1, double &outputbuffer2, int nFrames) {    
    
    //multiply by square wave
    outputbuffer1 = inputbuffer1 * (((tanh(sin(mPhase) * 150.)) / 2.) + 0.5);
    outputbuffer2 = inputbuffer2 * (((tanh(sin(mPhase) * 150.)) / 2.) + 0.5);
    //increase wave position
    mPhase += (mSpeed * (1. / (60. / mBPM))) * 2. * M_PI / mSampleRate;
}
