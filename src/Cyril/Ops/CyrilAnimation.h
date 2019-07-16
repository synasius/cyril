#pragma once

//  Created by Darren Mothersele on 07/11/2013.

#include "Cyril.h"
#include "ofMain.h"

class CyrilAnimation : public Cyril
{
  Cyril* e;

public:
  CyrilAnimation(Cyril* _e);

  ~CyrilAnimation() override;
  void print() override;
  int size() override;
  void eval(CyrilState&) override;
};
