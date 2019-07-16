#pragma once

//  Created by Darren Mothersele on 05/11/2013.

#include "ofMain.h"
#include <cyril/cmds.h>

#include "CyrilState.h"

class Particle;

void
yyerror(const char*);

class Cyril
{
public:
  bool valid;
  Cyril();
  virtual ~Cyril(){};

  Cyril(const Cyril& other) = delete;
  Cyril& operator=(const Cyril& other) = delete;

  virtual void print(){};
  virtual int size();
  virtual void update(CyrilState&);
  virtual void eval(CyrilState&);
  virtual int matchPushPop();
};

