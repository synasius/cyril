#pragma once

#include "CyrilFun.h"
#include "Palette.h"
#include "ofMain.h"

extern float fftSubbands[32];

class CyrilFftFun : public CyrilFun
{
public:
  CyrilFftFun(Cyril* _c);

  void print() override;
  int size() override;
  void eval(CyrilState&) override;
};

