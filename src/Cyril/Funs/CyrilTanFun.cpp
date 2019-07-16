//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilTanFun.h"

CyrilTanFun::CyrilTanFun(Cyril* _c)
  : CyrilFun(_c)
{
  int s = c->size();
  if (!(s == 1)) {
    yyerror("Tan function 1 argument");
    valid = false;
  }
}

void
CyrilTanFun::print()
{
  c->print();
  cout << "Tan" << endl;
}

int
CyrilTanFun::size()
{
  return 1;
}

void
CyrilTanFun::eval(CyrilState& state)
{
  c->eval(state);
  float result = tan(state.stk->top());
  state.stk->pop();
  state.stk->push(result);
}
