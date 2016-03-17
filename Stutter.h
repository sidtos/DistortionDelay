#ifndef __DistortionDelay__Stutter__
#define __DistortionDelay__Stutter__

#include <math.h>

class Stutter {
private:
    double mSpeed;
    double mSampleRate;
    double mBPM;
    double mPhase;
public:
    void setSampleRate(double sampleRate);
    void setSpeed(double speed);
    void setBPM(double bpm);
    void processSamples(double* inputbuffer, double* outputbuffer, int nFrames);
};

#endif /* defined(__DistortionDelay__Stutter__) */
