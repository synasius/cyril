#pragma once

//  Created by Darren Mothersele on 05/11/2013.

#include "Cyril.h"
#include <cyril/cmds.h>

class CyrilPush : public Cyril
{
  float f;

public:
  CyrilPush(float _f);
  CyrilPush(const CyrilPush& other);
  ~CyrilPush();

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState& _s) override;

  float getValue();
};

