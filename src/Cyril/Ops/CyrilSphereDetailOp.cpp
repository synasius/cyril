#include "CyrilSphereDetailOp.h"

CyrilSphereDetailOp::CyrilSphereDetailOp(Cyril* _c)
  : CyrilOp(_c)
{
  if (_c->size() != 1) {
    yyerror("SphereDetail command requires 1 argument");
    valid = false;
  }
}

void
CyrilSphereDetailOp::print()
{
  c->print();
  cout << "SphereDetail" << endl;
}

int
CyrilSphereDetailOp::size()
{
  return 0;
}

void
CyrilSphereDetailOp::eval(CyrilState& _s)
{
  c->eval(_s);
  float d = _s.stk->top();
  _s.stk->pop();
  ofSetSphereResolution(d);
}

