#pragma once

#include "CyrilOp.h"
#include <ofMain.h>

class CyrilDie : public CyrilOp
{
public:
  CyrilDie(Cyril* _c);

  void print() override;
  int size() override;
  void eval(CyrilState&) override;
};

