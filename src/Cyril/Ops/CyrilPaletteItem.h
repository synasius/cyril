#pragma once

#include <cyril/cmds.h>
#include <ofMain.h>

#include "Cyril.h"
#include "Palette.h"

class CyrilPaletteItem : public Cyril
{
public:
  CyrilPaletteItem(float _f, Cyril* _e);
  ~CyrilPaletteItem() override;

  void print() override;
  int size() override;
  void eval(CyrilState&) override;

private:
  Cyril* e;
  bool paletteCalc;
  float d, r, g, b;
};

