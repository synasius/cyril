#pragma once

#include "Cyril.h"

class CyrilKaleidoscope : public Cyril
{
protected:
  Cyril* e;
  int s;

public:
  CyrilKaleidoscope(Cyril* _e);
  CyrilKaleidoscope(const CyrilKaleidoscope& other);
  ~CyrilKaleidoscope() override;
  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
  void update(CyrilState&) override;
};
