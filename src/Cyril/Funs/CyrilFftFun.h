#pragma once

#include "CyrilFun.h"
#include "Palette.h"
#include "ofMain.h"

extern float fftSubbands[32];

class CyrilFftFun : public CyrilFun
{
public:
  CyrilFftFun(Cyril* _c);
  CyrilFftFun(const CyrilFftFun& other);

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};

