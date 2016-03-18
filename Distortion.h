#ifndef __DistortionDelay__Distortion__
#define __DistortionDelay__Distortion__

#include <math.h>

class Distortion {
private:
    double mThreshold;
    double mSampleRate;
public:
    void setSampleRate(double sampleRate);
    void setThreshold(double threshold);
    void processSamples(double inputbuffer1, double inputbuffer2, double &outputbuffer1, double &outputbuffer2, int nFrames);
};

#endif /* defined(__DistortionDelay__Distortion__) */
