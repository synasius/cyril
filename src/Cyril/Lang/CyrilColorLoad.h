#pragma once

#include <cyril/cmds.h>
#include <ofMain.h>

#include "Cyril.h"

class CyrilColorLoad : public Cyril
{
public:
  CyrilColorLoad(int _i);
  ~CyrilColorLoad() override;

  void print() override;
  int size() override;
  void eval(CyrilState&) override;

private:
  int loc;
};
