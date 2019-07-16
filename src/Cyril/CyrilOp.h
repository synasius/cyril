#pragma once

//  Created by Darren Mothersele on 05/11/2013.

#include <cyril/cmds.h>
#include <ofMain.h>

#include "Cyril.h"

class CyrilOp : public Cyril
{
public:
  CyrilOp(Cyril* _c = nullptr);
  ~CyrilOp() override;

  void print() override;
  int size() override;
  void eval(CyrilState&) override;

protected:
  Cyril* c;
};

