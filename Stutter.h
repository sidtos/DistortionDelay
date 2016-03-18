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
    void setSpeed(int speed);
    void setBPM(double bpm);
    void processSamples(double inputbuffer1, double inputbuffer2, double &outputbuffer1, double &outputbuffer2, int nFrames);
};

#endif /* defined(__DistortionDelay__Stutter__) */
