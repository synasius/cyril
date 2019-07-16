#pragma once

//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilFun.h"
#include "ofMain.h"

class CyrilRandFun : public CyrilFun
{
public:
  CyrilRandFun(Cyril* _c);

  void print() override;
  int size() override;
  void eval(CyrilState&) override;
};
