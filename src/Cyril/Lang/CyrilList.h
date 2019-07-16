#pragma once

//  Created by Darren Mothersele on 05/11/2013.

#include "Cyril.h"
#include <cyril/cmds.h>

class CyrilList : public Cyril
{
public:
  CyrilList(Cyril* _c1, Cyril* _c2);
  ~CyrilList() override;

  void print() override;
  int size() override;
  void update(CyrilState& _s) override;
  void eval(CyrilState& _s) override;
  int matchPushPop() override;

private:
  Cyril* c1;
  Cyril* c2;
};
