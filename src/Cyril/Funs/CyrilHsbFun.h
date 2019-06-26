#pragma once

//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilFun.h"
#include "ofMain.h"

class CyrilHsbFun : public CyrilFun
{
public:
  CyrilHsbFun(Cyril* _c);
  CyrilHsbFun(const CyrilHsbFun& other);

  virtual void print() override;
  virtual Cyril* clone() override;
  virtual int size() override;
  virtual void eval(CyrilState&) override;
};

