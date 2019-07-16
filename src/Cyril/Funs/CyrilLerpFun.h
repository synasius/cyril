#pragma once

//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilFun.h"
#include "Palette.h"
#include "ofMain.h"

class CyrilLerpFun : public CyrilFun
{
public:
  CyrilLerpFun(Cyril* _c);

  void print() override;
  int size() override;
  void eval(CyrilState&) override;
};

