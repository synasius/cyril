#include "CyrilBallOp.h"

CyrilBallOp::CyrilBallOp(Cyril* _c)
  : CyrilOp(_c)
{
  int s = c->size();
  if (!(s == 0 || s == 1)) {
    yyerror("Ball command requires 0 or 1 argument");
    valid = false;
  }
}

void
CyrilBallOp::print()
{
  c->print();
  cout << "Ball" << endl;
}

Cyril*
CyrilBallOp::clone()
{
  return new CyrilBallOp(*this);
}

int
CyrilBallOp::size()
{
  return 0;
}

void
CyrilBallOp::eval(CyrilState& _s)
{
  c->eval(_s);
  float r;
  if (c->size() == 1) {
    r = _s.stk->top();
    _s.stk->pop();
  } else {
    r = 1;
  }
  ofDrawIcoSphere(r);
}

