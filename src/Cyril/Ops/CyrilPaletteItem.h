//
//  CyrilPaletteItem.h
//  cyril2
//
//  Created by Darren Mothersele on 06/11/2013.
//
//

#ifndef __cyril2__CyrilPaletteItem__
#define __cyril2__CyrilPaletteItem__

#include <ofMain.h>
#include <cyril/cmds.h>

#include "Cyril.h"
#include "Palette.h"

class CyrilPaletteItem : public Cyril
{
  Cyril* e;
  bool paletteCalc;
  float d, r, g, b;

public:
  CyrilPaletteItem(float _f, Cyril* _e);
  CyrilPaletteItem(const CyrilPaletteItem& other);
  ~CyrilPaletteItem() override;
  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};

#endif /* defined(__cyril2__CyrilPaletteItem__) */
