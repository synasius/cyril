#pragma once

//  Created by Darren Mothersele on 15/09/2014.

#include "Cyril.h"

class CyrilPixelate : public Cyril
{
public:
  CyrilPixelate(Cyril* _e);
  CyrilPixelate(const CyrilPixelate& other);

  ~CyrilPixelate() override;
  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
  void update(CyrilState&) override;

protected:
  Cyril* e;
  int s;
};
