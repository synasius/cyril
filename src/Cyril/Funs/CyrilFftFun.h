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

  virtual void print() override;
  virtual Cyril* clone() override;
  virtual int size() override;
  virtual void eval(CyrilState&) override;
};

