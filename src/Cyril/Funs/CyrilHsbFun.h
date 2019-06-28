#pragma once

//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilFun.h"
#include "ofMain.h"

class CyrilHsbFun : public CyrilFun
{
public:
  CyrilHsbFun(Cyril* _c);
  CyrilHsbFun(const CyrilHsbFun& other);

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};

