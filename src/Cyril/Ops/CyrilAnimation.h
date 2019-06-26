#pragma once

//  Created by Darren Mothersele on 07/11/2013.

#include "Cyril.h"
#include "ofMain.h"

class CyrilAnimation : public Cyril
{
  Cyril* e;

public:
  CyrilAnimation(Cyril* _e);
  CyrilAnimation(const CyrilAnimation& other);

  virtual ~CyrilAnimation() override;
  virtual void print() override;
  virtual Cyril* clone() override;
  virtual int size() override;
  virtual void eval(CyrilState&) override;
};
