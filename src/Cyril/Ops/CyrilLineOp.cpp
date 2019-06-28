#include "CyrilLineOp.h"

CyrilLineOp::CyrilLineOp(Cyril* _c)
  : CyrilOp(_c)
{
  int s = c->size();
  if (!(s == 2 || s == 4)) {
    yyerror("Line command requires 2 or 4 arguments");
    valid = false;
  }
}

void
CyrilLineOp::print()
{
  c->print();
  cout << "Line" << endl;
}
Cyril*
CyrilLineOp::clone()
{
  return new CyrilLineOp(*this);
}
int
CyrilLineOp::size()
{
  return 0;
}
void
CyrilLineOp::eval(CyrilState& _s)
{
  c->eval(_s);
  float x1 = 0, x2 = 0, y1 = 0, y2 = 0;
  switch (c->size()) {
    case 4:
      y2 = _s.stk->top();
      _s.stk->pop();
      x2 = _s.stk->top();
      _s.stk->pop();
      y1 = _s.stk->top();
      _s.stk->pop();
      x1 = _s.stk->top();
      _s.stk->pop();
      break;
    case 2:
      y2 = _s.stk->top();
      _s.stk->pop();
      x2 = _s.stk->top();
      _s.stk->pop();
      y1 = 0;
      x1 = 0;
      break;
  }
  ofDrawLine(x1, y1, x2, y2);
}

