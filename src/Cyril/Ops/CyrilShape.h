#pragma once

//  Created by Darren Mothersele on 17/11/2013.

#include "Cyril.h"
#include "ofMain.h"

class CyrilShape : public Cyril
{
  Cyril* e;

public:
  CyrilShape(Cyril* _e);

  ~CyrilShape() override;
  void print() override;
  int size() override;
  void eval(CyrilState&) override;
};
