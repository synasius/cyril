#pragma once

//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilFun.h"
#include "ofMain.h"

class CyrilSinFun : public CyrilFun
{
public:
  CyrilSinFun(Cyril* _c);
  CyrilSinFun(const CyrilSinFun& other);

  virtual void print() override;
  virtual Cyril* clone() override;
  virtual int size() override;
  virtual void eval(CyrilState&) override;
};
