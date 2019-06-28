#pragma once

#include "Cyril.h"
#include <cyril/cmds.h>

extern map<string, ofColor> colorNameMap;

class CyrilNamedColor : public Cyril
{
  std::string s;
  float r, g, b;

public:
  CyrilNamedColor(const char* _s);
  CyrilNamedColor(const CyrilNamedColor& other) ;
  ~CyrilNamedColor() override;

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState& _s) override;
};

