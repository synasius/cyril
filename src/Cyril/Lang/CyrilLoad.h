#pragma once

//  Created by Darren Mothersele on 05/11/2013.

#include "Cyril.h"
#include <cyril/cmds.h>

class CyrilLoad : public Cyril
{
public:
  CyrilLoad(int _i);
  CyrilLoad(const CyrilLoad& other);
  ~CyrilLoad() override;

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState& _s) override;

private:
  int m_loc;
};
