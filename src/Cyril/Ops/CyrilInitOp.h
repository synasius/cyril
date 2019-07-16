#pragma once

#include "CyrilOp.h"
#include "ofMain.h"

class CyrilInitOp : public CyrilOp
{
public:
  CyrilInitOp(Cyril* _c);

  void print() override;
  int size() override;
  void eval(CyrilState&) override;
};
