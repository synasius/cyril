#pragma once

//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilFun.h"
#include "Palette.h"
#include "ofMain.h"

class CyrilPaletteFun : public CyrilFun
{
public:
  CyrilPaletteFun(Cyril* _c);
  CyrilPaletteFun(const CyrilPaletteFun& other);

  virtual void print() override;
  virtual Cyril* clone() override;
  virtual int size() override;
  virtual void eval(CyrilState&) override;
};
