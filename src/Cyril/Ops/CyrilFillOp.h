#pragma once

#include "CyrilOp.h"
#include "ofMain.h"

  class CyrilFillOp : public CyrilOp
{
public:
  CyrilFillOp(Cyril* _c);

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};
