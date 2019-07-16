#pragma once

#include "CyrilOp.h"
#include "ofMain.h"

class CyrilNoFillOp : public CyrilOp
{
public:
  CyrilNoFillOp(Cyril* _c);

  void print() override;
  int size() override;
  void eval(CyrilState&) override;
};

