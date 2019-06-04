#pragma once

//  Created by Darren Mothersele on 06/11/2013.

#include "ofMain.h"
#include "ofxPostProcessing.h"

class Particle;
class Palette;

class CyrilState
{
public:
  map<int, float>* sym;
  stack<float>* stk;
  ofMatrixStack* ms;
  vector<Particle*>* ps;
  map<int, Palette*>* cs;
  map<int, ofImage*>* img;
  CyrilState* parent;
  ofLight* light;
  ofxPostProcessing post;
  KaleidoscopePass::Ptr kaleido;
  NoiseWarpPass::Ptr noisewarp;
  PixelatePass::Ptr pixelate;
  BloomPass::Ptr bloom;
  float kaleidosegments;

  CyrilState(map<int, float>* _t,
             stack<float>* _s,
             ofMatrixStack* _m,
             vector<Particle*>* _p,
             map<int, Palette*>* _c,
             map<int, ofImage*>* _i,
             CyrilState*);
  CyrilState();
  ~CyrilState();
};

