#pragma once

#include "CyrilOp.h"
#include <ofMain.h>

class CyrilDie : public CyrilOp
{
public:
  CyrilDie(Cyril* _c);
  CyrilDie(const CyrilDie& other);

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};

