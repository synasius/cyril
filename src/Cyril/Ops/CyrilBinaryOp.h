#pragma once

//  Created by Darren Mothersele on 05/11/2013.

#include "Cyril.h"
#include <cyril/cmds.h>

class CyrilBinaryOp : public Cyril
{
public:
  CyrilBinaryOp(std::string _o, Cyril* _e1, Cyril* _e2);
  ~CyrilBinaryOp() override;

  void print() override;
  int size() override;
  void eval(CyrilState& _s) override;

private:
  std::string o;
  int op;
  Cyril* e1;
  Cyril* e2;
};
