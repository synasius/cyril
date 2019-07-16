#pragma once

#include "CyrilOp.h"
#include "ofMain.h"

class CyrilRotateOp : public CyrilOp
{
public:
  CyrilRotateOp(Cyril* _c);

  void print() override;
  int size() override;
  void eval(CyrilState&) override;
};
