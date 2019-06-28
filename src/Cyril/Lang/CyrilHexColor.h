#pragma once

#include "Cyril.h"
#include <cyril/cmds.h>

class CyrilHexColor : public Cyril
{
  std::string s;
  float r, g, b;

public:
  CyrilHexColor(const char* _s);
  CyrilHexColor(const CyrilHexColor& other);
  ~CyrilHexColor() override;

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState& _s) override;
};
