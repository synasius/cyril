#pragma once

//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilFun.h"
#include "ofMain.h"

class CyrilMapFun : public CyrilFun
{
public:
  CyrilMapFun(Cyril* _c);
  CyrilMapFun(const CyrilMapFun& other);

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};
