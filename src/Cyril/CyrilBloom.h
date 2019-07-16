#pragma once

//  Created by Darren Mothersele on 15/09/2014.

#include "Cyril.h"

class CyrilBloom : public Cyril
{
public:
  CyrilBloom(Cyril* _e);
  ~CyrilBloom() override;

  void print() override;
  int size() override;
  void eval(CyrilState&) override;
  void update(CyrilState&) override;

protected:
  Cyril* e;
  int s;
  float prevBloom;
};
