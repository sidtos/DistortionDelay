#include "DistortionDelay.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"

// GUI
//-----------------------------------------------------------------------

const int kNumPrograms = 1;

enum EParams
{
  kThreshold = 0,
  kSpeed,
  kTapDelay,
  kTapGain,
  kNumParams
};

enum ELayout
{
  kWidth = GUI_WIDTH,
  kHeight = GUI_HEIGHT,

  kThresholdX = 50,
  kThresholdY = 100,
  kKnobFrames = 60,
  
  kSpeedX = 100,
  kSpeedY = 100,
  
  kTapDelayX = 150,
  kTapDelayY = 100,
  
  kTapGainX = 200,
  kTapGainY = 100
};

DistortionDelay::DistortionDelay(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo), mThreshold(1.)
{
  TRACE;
  
  mDelay.setSampleRate(GetSampleRate());

  //arguments are: name, defaultVal, minVal, maxVal, step, label
  GetParam(kThreshold)->InitDouble("Threshold", 500., 0., 100., 1., "%");
  GetParam(kThreshold)->SetShape(2.);
  
  GetParam(kSpeed)->InitDouble("Speed", 1., 1., 4., 1., "%");
  GetParam(kSpeed)->SetShape(2.);
  
  GetParam(kTapDelay)->InitInt("Delay", 500, 0, 1000, "ms");
  
  GetParam(kTapGain)->InitInt("DelayGain", -10, -44, 0, "dB");

  IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);
  pGraphics->AttachPanelBackground(&COLOR_RED);

  IBitmap knob = pGraphics->LoadIBitmap(KNOB_ID, KNOB_FN, kKnobFrames);

  pGraphics->AttachControl(new IKnobMultiControl(this, kThresholdX, kThresholdY, kThreshold, &knob));
  pGraphics->AttachControl(new IKnobMultiControl(this, kSpeedX, kSpeedY, kSpeed, &knob));
  pGraphics->AttachControl(new IKnobMultiControl(this, kTapDelayX, kTapDelayY, kTapDelay, &knob));
  pGraphics->AttachControl(new IKnobMultiControl(this, kTapGainX, kTapGainY, kTapGain, &knob));

  AttachGraphics(pGraphics);

  //MakePreset("preset 1", ... );
  MakeDefaultPreset((char *) "-", kNumPrograms);
}

DistortionDelay::~DistortionDelay() {}

// DSP
//-----------------------------------------------------------------------

void DistortionDelay::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
  double* in1 = inputs[0];
  double* in2 = inputs[1];
  double* out1 = outputs[0];
  double* out2 = outputs[1];
  double distIn1, distIn2, distOut1, distOut2, stutOut1, stutOut2, delOut1, delOut2;

  mStutter.setBPM(GetTempo());
  
  for (int s = 0; s < nFrames; ++s, ++in1, ++in2, ++out1, ++out2)
  {
    distIn1 = *in1;
    distIn2 = *in2;
    
    mDistortion.processSamples(distIn1, distIn2, distOut1, distOut2, nFrames);
    mStutter.processSamples(distOut1, distOut2, stutOut1, stutOut2, nFrames);
    mDelay.processSamples(stutOut1, stutOut2, delOut1, delOut2, nFrames);
    
    *out1 = *in1 + delOut1;
    *out2 = *in2 + delOut2;
  }
}

void DistortionDelay::Reset()
{
  TRACE;
  IMutexLock lock(this);
  mDistortion.setSampleRate(GetSampleRate());
  mStutter.setSampleRate(GetSampleRate());
}

void DistortionDelay::OnParamChange(int paramIdx)
{
  IMutexLock lock(this);

  switch (paramIdx)
  {
    case kThreshold:
      mDistortion.setThreshold(GetParam(kThreshold)->Value() / 100.);
      break;
    
    case kSpeed:
      mStutter.setSpeed(GetParam(kSpeed)->Value());
      break;
      
    case kTapDelay:
      mDelay.setTapDelay(GetParam(kTapDelay)->Value());
      break;
      
    case kTapGain:
      mDelay.setTapGain(GetParam(kTapGain)->DBToAmp());
      break;

    default:
      break;
  }
}
