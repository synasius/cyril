//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilPaletteFun.h"

CyrilPaletteFun::CyrilPaletteFun(Cyril* _c)
  : CyrilFun(_c)
{
  int s = _c->size();
  if (!(s == 1 || s == 2)) {
    yyerror("Palette function has 1 or 2 arguments");
    valid = false;
  }
}

void
CyrilPaletteFun::print()
{
  c->print();
  cout << "Palette" << endl;
}

int
CyrilPaletteFun::size()
{
  return 3;
}

void
CyrilPaletteFun::eval(CyrilState& state)
{
  c->eval(state);
  float p, d;
  if (c->size() == 2) {
    d = state.stk->top();
    state.stk->pop();
  } else {
    d = ofRandomuf();
  }
  p = state.stk->top();
  state.stk->pop();
  ofColor _c = (*state.cs)[p]->getColorAt(d);
  state.stk->push(_c.r);
  state.stk->push(_c.g);
  state.stk->push(_c.b);
}

