#pragma once

#include "CyrilOp.h"
#include "ofMain.h"

class CyrilScaleOp : public CyrilOp
{
public:
  CyrilScaleOp(Cyril* _c);

  void print() override;
  int size() override;
  void eval(CyrilState&) override;
};
