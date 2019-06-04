#pragma once

//  Created by Darren Mothersele on 05/11/2013.

#include "Cyril.h"

#include <cyril/cmds.h>

class CyrilFor : public Cyril
{
public:
  CyrilFor(int _i, Cyril* _e1, Cyril* _e2, Cyril* _e3, Cyril* _c);
  CyrilFor(const CyrilFor& other);
  virtual ~CyrilFor();

  void print();
  virtual Cyril* clone();
  virtual int size();
  virtual void eval(CyrilState& _s);
  virtual int matchPushPop();

private:
  int loc;
  Cyril* e1;
  Cyril* e2;
  Cyril* e3;
  float step;
  Cyril* c;
};

