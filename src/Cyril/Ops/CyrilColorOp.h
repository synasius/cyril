#pragma once

#include "CyrilOp.h"
#include "ofMain.h"

class CyrilColorOp : public CyrilOp
{
public:
  CyrilColorOp(Cyril* _c);

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};
