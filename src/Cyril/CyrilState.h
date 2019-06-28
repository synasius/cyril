#pragma once

//  Created by Darren Mothersele on 06/11/2013.

#include "ofMain.h"
#include "ofxPostProcessing.h"

class Particle;
class Palette;

class CyrilState
{
public:
  std::map<int, float>* sym;
  std::stack<float>* stk;
  ofMatrixStack* ms;
  std::vector<Particle*>* ps;
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

  CyrilState(std::map<int, float>* _t,
             std::stack<float>* _s,
             ofMatrixStack* _m,
             std::vector<Particle*>* _p,
             std::map<int, Palette*>* _c,
             std::map<int, ofImage*>* _i,
             CyrilState*);
  CyrilState();
  ~CyrilState();
};

