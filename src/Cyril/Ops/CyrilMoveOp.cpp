#include "CyrilMoveOp.h"

CyrilMoveOp::CyrilMoveOp(Cyril* _c)
  : CyrilOp(_c)
{
  int s = c->size();
  if (!(s == 0 || s == 1 || s == 2 || s == 3)) {
    yyerror("Move command requires 1, 2 or 3 arguments");
    valid = false;
  }
}

void
CyrilMoveOp::print()
{
  c->print();
  cout << "Move" << endl;
}

int
CyrilMoveOp::size()
{
  return 0;
}

void
CyrilMoveOp::eval(CyrilState& _s)
{
  c->eval(_s);
  float x, y, z;
  switch (c->size()) {
    case 3:
      z = _s.stk->top();
      _s.stk->pop();
      y = _s.stk->top();
      _s.stk->pop();
      x = _s.stk->top();
      _s.stk->pop();
      break;
    case 2:
      z = 0;
      y = _s.stk->top();
      _s.stk->pop();
      x = _s.stk->top();
      _s.stk->pop();
      break;
    case 1:
      z = 0;
      y = 0;
      x = _s.stk->top();
      _s.stk->pop();
      break;
    default:
      z = 0;
      y = 0;
      x = sin((*_s.sym)[REG_TIME] / 1000);
  }
  ofTranslate(x, y, z);
  _s.ms->translate(x, y, z);
}

