#include <cyril/cmds.h>
#include <ofMain.h>

#include "Cyril.h"
#include "Palette.h"

class CyrilPalette : public Cyril
{
  int loc;
  Palette* palette;

public:
  CyrilPalette(int _l, Cyril* _p);
  CyrilPalette(const CyrilPalette& other);
  ~CyrilPalette() override;

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};

