#include "CyrilGridOp.h"

CyrilGridOp::CyrilGridOp(Cyril* _c)
  : CyrilOp(_c)
{
  int s = c->size();
  if (!(s == 0 || s == 1)) {
    yyerror("Grid command requires 0 or 1 argument");
    cout << _c->size() << endl;
    valid = false;
  }
}

void
CyrilGridOp::print()
{
  c->print();
  cout << "Grid" << endl;
}

Cyril*
CyrilGridOp::clone()
{
  return new CyrilGridOp(*this);
}

int
CyrilGridOp::size()
{
  return 0;
}

void
CyrilGridOp::eval(CyrilState& _s)
{
  c->eval(_s);
  float s;
  if (c->size() == 1) {
    s = _s.stk->top();
    _s.stk->pop();
  } else {
    s = 1;
  }
  if (s > 0) {
    ofDrawGridPlane(s);
  }
}

