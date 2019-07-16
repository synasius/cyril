#include "CyrilPushMatrixOp.h"

CyrilPushMatrixOp::CyrilPushMatrixOp(Cyril* _c)
  : CyrilOp(_c)
{
  if (_c->size() != 0) {
    yyerror("pushMatrix command requires 0 arguments");
    valid = false;
  }
}

void
CyrilPushMatrixOp::print()
{
  c->print();
  cout << "PushMatrix" << endl;
}

int
CyrilPushMatrixOp::size()
{
  return 0;
}

void
CyrilPushMatrixOp::eval(CyrilState& _s)
{
  ofPushMatrix();
  _s.ms->pushMatrix();
}

int
CyrilPushMatrixOp::matchPushPop()
{
  return -1;
}

