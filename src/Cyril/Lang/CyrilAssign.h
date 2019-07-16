#pragma once

#include "Cyril.h"
#include <cyril/cmds.h>

class CyrilAssign : public Cyril
{
public:
  CyrilAssign(int _i, Cyril* _c);
  ~CyrilAssign() override;

  void print() override;
  int size() override;
  void eval(CyrilState& _s) override;
  int matchPushPop() override;

private:
  int loc;
  Cyril* c;
};
