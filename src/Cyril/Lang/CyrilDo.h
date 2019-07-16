#pragma once

#include "Cyril.h"
#include <cyril/cmds.h>

class CyrilDo : public Cyril
{
public:
  CyrilDo(Cyril* _e, Cyril* _c);
  ~CyrilDo() override;

  void print() override;
  int size() override;
  void eval(CyrilState& _s) override;
  int matchPushPop() override;

private:
  Cyril* e;
  Cyril* c;

};
