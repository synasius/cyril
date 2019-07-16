#include "CyrilScaleOp.h"

CyrilScaleOp::CyrilScaleOp(Cyril* _c)
  : CyrilOp(_c)
{
  int s = c->size();
  if (!(s == 1 || s == 3)) {
    yyerror("Scale command requires 1 or 3 arguments");
    valid = false;
  }
}

void
CyrilScaleOp::print()
{
  c->print();
  cout << "Scale" << endl;
}

int
CyrilScaleOp::size()
{
  return 0;
}

void
CyrilScaleOp::eval(CyrilState& _s)
{
  c->eval(_s);
  float x = 0, y = 0, z = 0;
  switch (c->size()) {
    case 3:
      z = _s.stk->top();
      _s.stk->pop();
      y = _s.stk->top();
      _s.stk->pop();
      x = _s.stk->top();
      _s.stk->pop();
      break;
    case 1:
      z = _s.stk->top();
      _s.stk->pop();
      y = z;
      x = z;
      break;
  }
  ofScale(x, y, z);
  _s.ms->scale(x, y, z);
}

