//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilCosFun.h"

CyrilCosFun::CyrilCosFun(Cyril* _c)
  : CyrilFun(_c)
{
  int s = c->size();
  if (!(s == 1)) {
    yyerror("Cos function 1 argument");
    valid = false;
  }
}

void
CyrilCosFun::print()
{
  c->print();
  cout << "Cos" << endl;
}

int
CyrilCosFun::size()
{
  return 1;
}

void
CyrilCosFun::eval(CyrilState& _s)
{
  c->eval(_s);
  float result = cos(_s.stk->top());
  _s.stk->pop();
  _s.stk->push(result);
}

