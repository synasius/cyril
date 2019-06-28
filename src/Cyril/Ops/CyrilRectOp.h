#pragma once

#include "CyrilOp.h"
#include "ofMain.h"

class CyrilRectOp : public CyrilOp
{
public:
  CyrilRectOp(Cyril* _c);

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};
