#ifndef __DistortionDelay__Filter__
#define __DistortionDelay__Filter__

#include <math.h>

class Filter {
private:
    double mLPFreq;
    double mSampleRate;
    double mHPFreq;
    double lpa0, hpa0, lpb1, hpb1, lpx, hpx, lpTmp1, lpTmp2, hpTmp1, hpTmp2;
public:
    void setSampleRate(double sampleRate);
    void setLPFreq(double lpFreq);
    void setHPFreq(double hpFreq);
    void setLPCoefficient();
    void setHPCoefficient();
    void initializeCoefficients();
    void processSamplesLP(double inputbuffer1, double inputbuffer2, double &outputbuffer1, double &outputbuffer2, int nFrames);
    void processSamplesHP(double inputbuffer1, double inputbuffer2, double &outputbuffer1, double &outputbuffer2, int nFrames);
};

#endif /* defined(__DistortionDelay__Filter__) */
