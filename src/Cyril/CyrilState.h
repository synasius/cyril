#pragma once

//  Created by Darren Mothersele on 06/11/2013.

#include <memory>

#include "ofMain.h"
#include "ofxPostProcessing.h"

class Particle;
class Palette;

class CyrilState
{
  using ParticleVector = std::vector<std::unique_ptr<Particle>>;

public:
  std::map<int, float>* sym;
  std::stack<float>* stk;
  ofMatrixStack* ms;
  ParticleVector ps;
  std::map<int, Palette*>* cs;
  std::map<int, ofImage*>* img;
  CyrilState* parent;
  ofLight* light;
  ofxPostProcessing post;
  KaleidoscopePass::Ptr kaleido;
  NoiseWarpPass::Ptr noisewarp;
  PixelatePass::Ptr pixelate;
  BloomPass::Ptr bloom;
  float kaleidosegments;

  CyrilState();
  ~CyrilState();
};

