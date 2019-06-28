#pragma once

#include "CyrilOp.h"
#include "ofMain.h"

class CyrilLightOp : public CyrilOp
{
public:
  CyrilLightOp(Cyril* _c);

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};
