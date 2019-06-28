#pragma once

#include "CyrilOp.h"
#include "ofMain.h"

class CyrilImgOp : public CyrilOp
{
public:
  CyrilImgOp(Cyril* _c);

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};
