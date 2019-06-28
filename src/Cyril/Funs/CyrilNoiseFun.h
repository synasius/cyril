#pragma once

//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilFun.h"
#include "ofMain.h"

class CyrilNoiseFun : public CyrilFun
{
public:
  CyrilNoiseFun(Cyril* _c);
  CyrilNoiseFun(const CyrilNoiseFun& other);

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};
