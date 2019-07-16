#include "CyrilConeOp.h"

CyrilConeOp::CyrilConeOp(Cyril* _c)
  : CyrilOp(_c)
{
  int s = c->size();
  if (!(s == 0 || s == 1 || s == 2)) {
    yyerror("Cone command requires 0, 1 or 2 arguments");
    valid = false;
  }
}

void
CyrilConeOp::print()
{
  c->print();
  cout << "Cone" << endl;
}

int
CyrilConeOp::size()
{
  return 0;
}

void
CyrilConeOp::eval(CyrilState& _s)
{
  c->eval(_s);
  float r = 0, h = 0;
  switch (c->size()) {
    case 2:
      h = _s.stk->top();
      _s.stk->pop();
      r = _s.stk->top();
      _s.stk->pop();
      break;
    case 1:
      h = _s.stk->top();
      _s.stk->pop();
      r = h;
      break;
    case 0:
      h = 1;
      r = 1;
      break;
  }
  ofDrawCone(r, h);
}

