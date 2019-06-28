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

  ~CyrilAnimation() override;
  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};
