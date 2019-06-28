#pragma once

//  Created by Darren Mothersele on 05/11/2013.

#include "CyrilOp.h"
#include "ofMain.h"

class CyrilBoxOp : public CyrilOp
{
public:
  CyrilBoxOp(Cyril* _c);

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};

