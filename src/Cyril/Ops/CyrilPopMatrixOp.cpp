#include "CyrilPopMatrixOp.h"

CyrilPopMatrixOp::CyrilPopMatrixOp(Cyril* _c)
  : CyrilOp(_c)
{
  if (_c->size() != 0) {
    yyerror("popMatrix command requires 0 arguments");
    valid = false;
  }
}

void
CyrilPopMatrixOp::print()
{
  c->print();
  cout << "PopMatrix" << endl;
}

Cyril*
CyrilPopMatrixOp::clone()
{
  return new CyrilPopMatrixOp(*this);
}

int
CyrilPopMatrixOp::size()
{
  return 0;
}

void
CyrilPopMatrixOp::eval(CyrilState& _s)
{
  ofPopMatrix();
  _s.ms->popMatrix();
}

int
CyrilPopMatrixOp::matchPushPop()
{
  return 1;
}
