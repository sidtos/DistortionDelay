#ifndef __DistortionDelay__SimpleDelay__
#define __DistortionDelay__SimpleDelay__

#include <math.h>

class SimpleDelay {
private:
    int mSampleRate;
    double* delayBuffer1;
    double* delayBuffer2;
    double mTapGain;
    double mTapDelay;
    double mOutDelay;
    unsigned int sampleCount;
    void updateBuffer();
public:
    void setSampleRate(double sampleRate);
    void setTapGain(double tapGain);
    void setTapDelay(double tapDelay);
    void processSamples(double inputbuffer1, double inputbuffer2, double &outputbuffer1, double &outputbuffer2, int nFrames);
};

#endif /* defined(__DistortionDelay__SimpleDelay__) */
