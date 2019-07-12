#include "CyrilNoFillOp.h"

CyrilNoFillOp::CyrilNoFillOp(Cyril* _c)
  : CyrilOp(_c)
{
  int s = c->size();
  if (!(s == 0 || s == 1)) {
    yyerror("noFill command takes 0 or 1 arguments");
    valid = false;
  }
}

void
CyrilNoFillOp::print()
{
  c->print();
  cout << "Fill" << endl;
}

Cyril*
CyrilNoFillOp::clone()
{
  return new CyrilNoFillOp(*this);
}

int
CyrilNoFillOp::size()
{
  return 0;
}

void
CyrilNoFillOp::eval(CyrilState& _s)
{
  int _size = c->size();
  if (_size == 1) {
    c->eval(_s);
    ofSetLineWidth(_s.stk->top());
    _s.stk->pop();
    ofFill();
  }
  ofNoFill();
}

