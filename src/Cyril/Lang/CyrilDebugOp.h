#pragma once

#include "CyrilOp.h"
#include "ofMain.h"

class CyrilDebugOp : public CyrilOp
{
public:
  CyrilDebugOp(Cyril* _c);

  void print() override;
  int size() override;
  void eval(CyrilState&) override;
};
