#pragma once

//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilOp.h"
#include "ofMain.h"

class CyrilBallDetailOp : public CyrilOp
{
public:
  CyrilBallDetailOp(Cyril* _c);

  void print() override;
  int size() override;
  void eval(CyrilState&) override;
};
