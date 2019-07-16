#pragma once

//  Created by Darren Mothersele on 07/11/2013.

#include "Cyril.h"
#include "ofMain.h"

class CyrilAnimStep : public Cyril
{
public:
  CyrilAnimStep(float _n, Cyril* _e1, Cyril* _e2);
  ~CyrilAnimStep() override;

  void print() override;
  int size() override;
  void eval(CyrilState&) override;

private:
  float n;
  Cyril* e1;
  Cyril* e2;
};
