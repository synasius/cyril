#include "CyrilColorOp.h"

CyrilColorOp::CyrilColorOp(Cyril* _c)
  : CyrilOp(_c)
{
  int s = c->size();
  if (!(s == 1 || s == 2 || s == 3 || s == 4)) {
    yyerror("Color command needs 1, 2, 3 or 4 arguments");
    valid = false;
  }
}

void
CyrilColorOp::print()
{
  c->print();
  cout << "Color" << endl;
}

Cyril*
CyrilColorOp::clone()
{
  return new CyrilColorOp(*this);
}

int
CyrilColorOp::size()
{
  return 0;
}

void
CyrilColorOp::eval(CyrilState& _s)
{
  c->eval(_s);
  float r = 0, g = 0, b = 0, a = 0;
  switch (c->size()) {
    case 4:
      a = _s.stk->top();
      _s.stk->pop();
      b = _s.stk->top();
      _s.stk->pop();
      g = _s.stk->top();
      _s.stk->pop();
      r = _s.stk->top();
      _s.stk->pop();
      break;
    case 3:
      a = 255;
      b = _s.stk->top();
      _s.stk->pop();
      g = _s.stk->top();
      _s.stk->pop();
      r = _s.stk->top();
      _s.stk->pop();
      break;
    case 2:
      a = _s.stk->top();
      _s.stk->pop();
      b = _s.stk->top();
      _s.stk->pop();
      g = b;
      r = b;
      break;
    case 1:
      a = 255;
      b = _s.stk->top();
      _s.stk->pop();
      g = b;
      r = b;
      break;
  }
  ofSetColor(r, g, b, a);
}
