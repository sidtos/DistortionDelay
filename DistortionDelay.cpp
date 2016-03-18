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
  kHP,
  kLP,
  kNumParams
};

enum ELayout
{
  kWidth = GUI_WIDTH,
  kHeight = GUI_HEIGHT,

  kThresholdX = 10,
  kThresholdY = 100,
  kKnobFrames = 60,
  
  kSpeedX = 60,
  kSpeedY = 100,
  
  kTapDelayX = 110,
  kTapDelayY = 100,
  
  kTapGainX = 160,
  kTapGainY = 100,
  
  kHPX = 210,
  kHPY = 100,
  
  kLPX = 260,
  kLPY = 100,
};

DistortionDelay::DistortionDelay(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo), mThreshold(1.)
{
  TRACE;

  //arguments are: name, defaultVal, minVal, maxVal, step, label
  GetParam(kThreshold)->InitDouble("Threshold", 100., 0.01, 100., 0.01, "%");
  GetParam(kThreshold)->SetShape(2.);
  
  GetParam(kSpeed)->InitInt("Speed", 1, 1, 4, "note");
  
  GetParam(kTapDelay)->InitInt("Delay", 1, 1, 4, "note");
  
  GetParam(kTapGain)->InitInt("DelayGain", -10, -44, 0, "dB");
  
  GetParam(kHP)->InitDouble("HP", 20., 20., 10000., 1., "%");
  GetParam(kHP)->SetShape(2.);
  
  GetParam(kLP)->InitDouble("LP", 20000., 300., 20000., 1., "%");
  GetParam(kLP)->SetShape(2.);

  IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);
  pGraphics->AttachPanelBackground(&COLOR_RED);

  IBitmap knob = pGraphics->LoadIBitmap(KNOB_ID, KNOB_FN, kKnobFrames);

  pGraphics->AttachControl(new IKnobMultiControl(this, kThresholdX, kThresholdY, kThreshold, &knob));
  pGraphics->AttachControl(new IKnobMultiControl(this, kSpeedX, kSpeedY, kSpeed, &knob));
  pGraphics->AttachControl(new IKnobMultiControl(this, kTapDelayX, kTapDelayY, kTapDelay, &knob));
  pGraphics->AttachControl(new IKnobMultiControl(this, kTapGainX, kTapGainY, kTapGain, &knob));
  pGraphics->AttachControl(new IKnobMultiControl(this, kHPX, kHPY, kHP, &knob));
  pGraphics->AttachControl(new IKnobMultiControl(this, kLPX, kLPY, kLP, &knob));

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
  double distIn1, distIn2, distOut1, distOut2, stutOut1, stutOut2, delOut1, delOut2, hpOut1, hpOut2, lpOut1, lpOut2;

  mStutter.setBPM(GetTempo());
  mDelay.setBPM(GetTempo());
  
  for (int s = 0; s < nFrames; ++s, ++in1, ++in2, ++out1, ++out2)
  {
    distIn1 = *in1;
    distIn2 = *in2;
    
    mDistortion.processSamples(distIn1, distIn2, distOut1, distOut2, nFrames);
    mStutter.processSamples(distOut1, distOut2, stutOut1, stutOut2, nFrames);
    mDelay.processSamples(stutOut1, stutOut2, delOut1, delOut2, nFrames);
    mFilter.processSamplesLP(delOut1, delOut2, lpOut1, lpOut2, nFrames);
    mFilter.processSamplesHP(lpOut1, lpOut2, hpOut1, hpOut2, nFrames);
    
    *out1 = *in1 + hpOut1;
    *out2 = *in2 + hpOut2;
  }
}

void DistortionDelay::Reset()
{
  TRACE;
  IMutexLock lock(this);
  mDistortion.setSampleRate(GetSampleRate());
  mStutter.setSampleRate(GetSampleRate());
  mDelay.setSampleRate(GetSampleRate());
  mFilter.setSampleRate(GetSampleRate());
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
      
    case kHP:
      mFilter.setHPFreq(GetParam(kHP)->Value());
      break;
      
    case kLP:
      mFilter.setLPFreq(GetParam(kLP)->Value());
      break;

    default:
      break;
  }
}
