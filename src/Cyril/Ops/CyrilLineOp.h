#pragma once

#include "CyrilOp.h"
#include "ofMain.h"

class CyrilLineOp : public CyrilOp
{
public:
  CyrilLineOp(Cyril* _c);

  void print() override;
  int size() override;
  void eval(CyrilState&) override;
};

