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

CyrilSinFun::CyrilSinFun(const CyrilSinFun& other)
  : CyrilFun(other)
{}

void
CyrilSinFun::print()
{
  c->print();
  std::cout << "Sin" << std::endl;
}

Cyril*
CyrilSinFun::clone()
{
  return new CyrilSinFun(*this);
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
