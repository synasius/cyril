#pragma once

#include "CyrilOp.h"
#include "ofMain.h"

class CyrilBallOp : public CyrilOp
{
public:
  CyrilBallOp(Cyril* _c);

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};
