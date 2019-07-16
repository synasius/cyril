#include "CyrilSinFun.h"

CyrilSinFun::CyrilSinFun(Cyril* _c)
  : CyrilFun(_c)
{
  int s = c->size();
  if (!(s == 1)) {
    yyerror("Sin function 1 argument");
    valid = false;
  }
}

void
CyrilSinFun::print()
{
  c->print();
  std::cout << "Sin" << std::endl;
}

int
CyrilSinFun::size()
{
  return 1;
}

void
CyrilSinFun::eval(CyrilState& state)
{
  c->eval(state);
  float result = sin(state.stk->top());
  state.stk->pop();
  state.stk->push(result);
}
