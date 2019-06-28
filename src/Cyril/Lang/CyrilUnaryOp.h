#pragma once

//  Created by Darren Mothersele on 05/11/2013.

#include "Cyril.h"
#include <cyril/cmds.h>

class CyrilUnaryOp : public Cyril
{
public:
  CyrilUnaryOp(string _o, Cyril* _e);
  CyrilUnaryOp(const CyrilUnaryOp& other);

  ~CyrilUnaryOp() override;
  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState& _s) override;

private:
  std::string o;
  int op;
  Cyril* e;
};
