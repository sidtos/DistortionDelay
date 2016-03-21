#include "Filter.h"
#include "math.h"

void Filter::setSampleRate(double sampleRate) {
    mSampleRate = sampleRate;
}

void Filter::setLPFreq(double lpFreq) {
    mLPFreq = lpFreq;
    setLPCoefficient();
}

void Filter::setHPFreq(double hpFreq) {
    mHPFreq = hpFreq;
    setHPCoefficient();
}

void Filter::setLPCoefficient() {
    initializeCoefficients();
    lpx = exp(-2.0 * M_PI * mLPFreq / mSampleRate);
    lpa0 = 1.0 - lpx;
    lpb1 = -lpx;
}

void Filter::setHPCoefficient() {
    initializeCoefficients();
    hpx = exp(-2.0 * M_PI * mHPFreq / mSampleRate);
    hpa0 = 1.0 - hpx;
    hpb1 = -hpx;
}

void Filter::initializeCoefficients() {
    lpa0 = hpa0 = lpb1 = hpb1 = lpx = hpx = lpTmp1 = lpTmp2 = hpTmp1 = hpTmp2 = 0.0;
}

void Filter::processSamplesLP(double inputbuffer1, double inputbuffer2, double &outputbuffer1, double &outputbuffer2, int nFrames) {
    //left
    outputbuffer1 = lpa0 * inputbuffer1 - lpb1 * lpTmp1;
    lpTmp1 = outputbuffer1;
    //right
    outputbuffer2 = lpa0 * inputbuffer2 - lpb1 * lpTmp2;
    lpTmp2 = outputbuffer2;
}

void Filter::processSamplesHP(double inputbuffer1, double inputbuffer2, double &outputbuffer1, double &outputbuffer2, int nFrames) {
    //left
    hpTmp1 = hpa0 * inputbuffer1 - hpb1 * hpTmp1;
    outputbuffer1 = inputbuffer1 - hpTmp1;
    //right
    hpTmp2 = hpa0 * inputbuffer2 - hpb1 * hpTmp2;
    outputbuffer2 = inputbuffer2 - hpTmp2;
}
