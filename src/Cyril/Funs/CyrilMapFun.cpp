//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilMapFun.h"

CyrilMapFun::CyrilMapFun(Cyril* _c)
  : CyrilFun(_c)
{
  int s = _c->size();
  if (!(s == 5)) {
    yyerror("Map function has 5 arguments");
    valid = false;
  }
}

void
CyrilMapFun::print()
{
  c->print();
  cout << "MAP" << endl;
}

int
CyrilMapFun::size()
{
  return 1;
}

void
CyrilMapFun::eval(CyrilState& _s)
{
  c->eval(_s);
  float v, min1, max1, min2, max2;
  max2 = _s.stk->top();
  _s.stk->pop();
  min2 = _s.stk->top();
  _s.stk->pop();
  max1 = _s.stk->top();
  _s.stk->pop();
  min1 = _s.stk->top();
  _s.stk->pop();
  v = _s.stk->top();
  _s.stk->pop();
  _s.stk->push(ofMap(v, min1, max1, min2, max2));
}

