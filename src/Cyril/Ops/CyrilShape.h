#pragma once

//  Created by Darren Mothersele on 17/11/2013.

#include "Cyril.h"
#include "ofMain.h"

class CyrilShape : public Cyril
{
  Cyril* e;

public:
  CyrilShape(Cyril* _e);
  CyrilShape(const CyrilShape& other);

  ~CyrilShape() override;
  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};
