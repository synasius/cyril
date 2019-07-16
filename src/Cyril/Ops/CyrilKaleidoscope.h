#pragma once

#include "Cyril.h"

class CyrilKaleidoscope : public Cyril
{
protected:
  Cyril* e;
  int s;

public:
  CyrilKaleidoscope(Cyril* _e);
  ~CyrilKaleidoscope() override;

  void print() override;
  int size() override;
  void eval(CyrilState&) override;
  void update(CyrilState&) override;
};
