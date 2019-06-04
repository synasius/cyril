#pragma once

//  Created by Darren Mothersele on 05/11/2013.

#include <cyril/cmds.h>
#include <ofMain.h>

#include "CyrilState.h"

class Particle;

void
yyerror(const char*);

class Cyril
{
public:
  bool valid;
  Cyril() { valid = true; }
  Cyril(const Cyril& other);

  virtual ~Cyril() {}

  virtual Cyril* clone();
  virtual void print(){};
  virtual int size();
  virtual void update(CyrilState&);
  virtual void eval(CyrilState&);
  virtual int matchPushPop() { return 0; }
};

