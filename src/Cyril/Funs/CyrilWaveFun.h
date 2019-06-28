#pragma once

//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilFun.h"
#include "ofMain.h"

class CyrilWaveFun : public CyrilFun
{
public:
  CyrilWaveFun(Cyril* _c);
  CyrilWaveFun(const CyrilWaveFun& other);

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};

