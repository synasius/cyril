#pragma once

#include "Cyril.h"
#include "ofMain.h"

class CyrilBlink : public Cyril
{
  Cyril* e;
  Cyril* c;

public:
  CyrilBlink(Cyril* _e, Cyril* _c);
  ~CyrilBlink() override;

  void print() override;
  int size() override;
  void eval(CyrilState&) override;
  int matchPushPop() override { return c->matchPushPop(); }
};
