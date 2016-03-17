#ifndef __DISTORTIONDELAY__
#define __DISTORTIONDELAY__

#include "IPlug_include_in_plug_hdr.h"
#include "Distortion.h"
#include "Stutter.h"
#include "SimpleDelay.h"

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
};

#endif
