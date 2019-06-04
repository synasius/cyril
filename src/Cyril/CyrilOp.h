#pragma once

//  Created by Darren Mothersele on 05/11/2013.

#include <cyril/cmds.h>
#include <ofMain.h>

#include "Cyril.h"

class CyrilOp : public Cyril
{
protected:
  Cyril* c;

public:
  CyrilOp(Cyril* _c = nullptr);
  CyrilOp(const CyrilOp& other);
  virtual ~CyrilOp();
  virtual void print();
  virtual Cyril* clone();
  virtual int size();
  virtual void eval(CyrilState&);
};

