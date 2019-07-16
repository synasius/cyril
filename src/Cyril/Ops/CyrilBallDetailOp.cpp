#include "CyrilBallDetailOp.h"

CyrilBallDetailOp::CyrilBallDetailOp(Cyril* _c)
  : CyrilOp(_c)
{
  if (_c->size() != 1) {
    yyerror("BallDetail command requires 1 argument");
    valid = false;
  }
}

void
CyrilBallDetailOp::print()
{
  c->print();
  cout << "BallDetail" << endl;
}

int
CyrilBallDetailOp::size()
{
  return 0;
}

void
CyrilBallDetailOp::eval(CyrilState& _s)
{
  c->eval(_s);
  float d = _s.stk->top();
  _s.stk->pop();
  if (d > 5)
    d = 5;
  ofSetIcoSphereResolution(d);
}

