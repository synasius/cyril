#include "CyrilFillOp.h"

CyrilFillOp::CyrilFillOp(Cyril* _c)
  : CyrilOp(_c)
{
  int s = c->size();
  if (!(s == 0 || s == 1 || s == 2 || s == 3 || s == 4)) {
    yyerror(
      "Fill command takes 0 (standard) or 1, 2, 3, or 4 arguments (color)");
    valid = false;
  }
}

void
CyrilFillOp::print()
{
  c->print();
  cout << "Fill" << endl;
}

Cyril*
CyrilFillOp::clone()
{
  return new CyrilFillOp(*this);
}

int
CyrilFillOp::size()
{
  return 0;
}

void
CyrilFillOp::eval(CyrilState& _s)
{
  int _size = c->size();
  if (_size == 0) {
    ofFill();
    return;
  }

  c->eval(_s);
  float r = 0, g = 0, b = 0, a = 0;
  switch (_size) {
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
  ofFill();
}

