#pragma once

#include "CyrilOp.h"
#include "ofMain.h"

class CyrilMoveOp : public CyrilOp
{
public:
  CyrilMoveOp(Cyril* _c);

  void print() override;
  int size() override;
  void eval(CyrilState&) override;
};
