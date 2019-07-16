#pragma once

#include "CyrilOp.h"
#include "ofMain.h"

class CyrilConeOp : public CyrilOp
{
public:
  CyrilConeOp(Cyril* _c);

  void print() override;
  int size() override;
  void eval(CyrilState&) override;
};

