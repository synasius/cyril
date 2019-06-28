#pragma once

#include "CyrilOp.h"
#include "ofMain.h"

class CyrilGridOp : public CyrilOp
{
public:
  CyrilGridOp(Cyril* _c);

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};
