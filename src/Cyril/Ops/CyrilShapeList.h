#pragma once

//  Created by Darren Mothersele on 17/11/2013.

#include "Cyril.h"
#include "ofMain.h"

class CyrilShapeList : public Cyril
{
public:
  CyrilShapeList(Cyril* _c);

  ~CyrilShapeList() override;
  void print() override;
  int size() override;
  void eval(CyrilState&) override;

private:
  Cyril* e;
  Cyril* c;
};
