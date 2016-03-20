#ifndef __DistortionDelay__SimpleDelay__
#define __DistortionDelay__SimpleDelay__

#include <math.h>

class SimpleDelay {
private:
    int mSampleRate;
    double mBPM;
    double* delayBuffer1;
    double* delayBuffer2;
    double mTapGain;
    double mTapDelay;
    double mOutDelay;
    unsigned int sampleCount;
public:
    void setSampleRate(double sampleRate);
    void setBPM(double BPM);
    void setTapGain(double tapGain);
    void setTapDelay(int tapDelay);
    void updateBuffer();
    void processSamples(double inputbuffer1, double inputbuffer2, double &outputbuffer1, double &outputbuffer2, int nFrames);
};

#endif /* defined(__DistortionDelay__SimpleDelay__) */
