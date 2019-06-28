#pragma once

//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilFun.h"
#include "ofMain.h"

class CyrilTanFun : public CyrilFun
{
public:
  CyrilTanFun(Cyril* _c);
  CyrilTanFun(const CyrilTanFun& other);

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};
