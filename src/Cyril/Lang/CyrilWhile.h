#pragma once

//  Created by Darren Mothersele on 05/11/2013.

#include "Cyril.h"
#include <cyril/cmds.h>

class CyrilWhile : public Cyril
{
public:
  CyrilWhile(Cyril* _e, Cyril* _c);
  CyrilWhile(const CyrilWhile& other);
  ~CyrilWhile() override;

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState& _s) override;
  int matchPushPop() override;

private:
  Cyril* e;
  Cyril* c;
};
