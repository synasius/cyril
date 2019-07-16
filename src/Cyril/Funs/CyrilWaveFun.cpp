//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilWaveFun.h"

CyrilWaveFun::CyrilWaveFun(Cyril* _c)
  : CyrilFun(_c)
{
  int s = c->size();
  if (!(s == 1)) {
    yyerror("Wave function 1 argument");
    valid = false;
  }
}

void
CyrilWaveFun::print()
{
  c->print();
  cout << "Wave" << endl;
}

int
CyrilWaveFun::size()
{
  return 1;
}

void
CyrilWaveFun::eval(CyrilState& state)
{
  c->eval(state);
  float result = (sin(((*state.sym)[REG_TIME] / state.stk->top())) * 0.5) + 0.5;
  state.stk->pop();
  state.stk->push(result);
}
