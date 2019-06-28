#include "CyrilDebugOp.h"

CyrilDebugOp::CyrilDebugOp(Cyril* _c)
  : CyrilOp(_c)
{}

void
CyrilDebugOp::print()
{
  c->print();
  cout << "Debug" << endl;
}

Cyril*
CyrilDebugOp::clone()
{
  return new CyrilDebugOp(*this);
}

int
CyrilDebugOp::size()
{
  return 0;
}

void
CyrilDebugOp::eval(CyrilState& _s)
{
  c->eval(_s);
  std::cout << "DEBUG:";
  int sz = c->size();
  for (int i = 0; i < sz; i++) {
    std::cout << " " << _s.stk->top();
    _s.stk->pop();
  }
  std::cout << std::endl;
}

