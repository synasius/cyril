#pragma once

#include "Cyril.h"
#include <cyril/cmds.h>

class CyrilIf : public Cyril
{
public:
  CyrilIf(Cyril* _e, Cyril* _c);
  ~CyrilIf() override;

  void print() override;
  int size() override;
  void eval(CyrilState& _s) override;
  int matchPushPop() override;

private:
  Cyril* e;
  Cyril* c;
};
