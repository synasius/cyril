#pragma once

#include <cyril/cmds.h>
#include <ofMain.h>

#include "Cyril.h"

class CyrilFun : public Cyril
{
protected:
  Cyril* c;

public:
  CyrilFun(Cyril* _c = nullptr);

  ~CyrilFun() override;
  void print() override;
  int size() override;
  void eval(CyrilState&) override;
};

