#pragma once

//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilFun.h"
#include "Palette.h"
#include "ofMain.h"

class CyrilLerpFun : public CyrilFun
{
public:
  CyrilLerpFun(Cyril* _c);
  CyrilLerpFun(const CyrilLerpFun& other);

  virtual void print() override;
  virtual Cyril* clone() override;
  virtual int size() override;
  virtual void eval(CyrilState&) override;
};

