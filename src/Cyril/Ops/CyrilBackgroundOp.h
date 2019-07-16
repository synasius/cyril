#pragma once

#include "CyrilOp.h"
#include "Palette.h"
#include "ofMain.h"

class CyrilBackgroundOp : public CyrilOp
{
public:
  CyrilBackgroundOp(Cyril* _c);

  void print() override;
  int size() override;
  void eval(CyrilState&) override;
};
