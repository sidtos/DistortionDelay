#ifndef __DISTORTIONDELAY__
#define __DISTORTIONDELAY__

#include "IPlug_include_in_plug_hdr.h"
#include "Distortion.h"
#include "Stutter.h"
#include "SimpleDelay.h"
#include "Filter.h"

class DistortionDelay : public IPlug
{
public:
  DistortionDelay(IPlugInstanceInfo instanceInfo);
  ~DistortionDelay();

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

private:
  double mThreshold;
  Distortion mDistortion;
  double mSpeed;
  Stutter mStutter;
  double mTapDelay;
  SimpleDelay mDelay;
  double mLPFreq;
  double mHPFreq;
  Filter mFilter;
  IKnobControl *mControl;
  void createPresets();
  double distIn1, distIn2, distOut1, distOut2, stutOut1, stutOut2, delOut1, delOut2, hpOut1, hpOut2, lpOut1, lpOut2;
};

#endif
