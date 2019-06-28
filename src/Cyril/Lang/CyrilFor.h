#pragma once

//  Created by Darren Mothersele on 05/11/2013.

#include "Cyril.h"

#include <cyril/cmds.h>

class CyrilFor : public Cyril
{
public:
  CyrilFor(int _i, Cyril* _e1, Cyril* _e2, Cyril* _e3, Cyril* _c);
  CyrilFor(const CyrilFor& other);
  ~CyrilFor() override;

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState& _s) override;
  int matchPushPop() override;

private:
  int loc;
  Cyril* e1;
  Cyril* e2;
  Cyril* e3;
  float step;
  Cyril* c;
};

