#pragma once

//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilFun.h"
#include "ofMain.h"

class CyrilTanFun : public CyrilFun
{
public:
  CyrilTanFun(Cyril* _c);

  void print() override;
  int size() override;
  void eval(CyrilState&) override;
};
