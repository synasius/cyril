#include "CyrilRectOp.h"

CyrilRectOp::CyrilRectOp(Cyril* _c)
  : CyrilOp(_c)
{
  int s = c->size();
  if (!(s == 0 || s == 1 || s == 2)) {
    yyerror("Rect command requires 0, 1 or 2 arguments");
    valid = false;
  }
}

void
CyrilRectOp::print()
{
  c->print();
  cout << "Rect" << endl;
}

Cyril*
CyrilRectOp::clone()
{
  return new CyrilRectOp(*this);
}

int
CyrilRectOp::size()
{
  return 0;
}

void
CyrilRectOp::eval(CyrilState& _s)
{
  c->eval(_s);
  float w = 0, h = 0;
  switch (c->size()) {
    case 2:
      h = _s.stk->top();
      _s.stk->pop();
      w = _s.stk->top();
      _s.stk->pop();
      break;
    case 1:
      h = _s.stk->top();
      _s.stk->pop();
      w = h;
      break;
    case 0:
      h = 1;
      w = 1;
      break;
  }
  // ofDrawBox(w, h, 1);
  w = w / 2.0;
  h = h / 2.0;
  ofBeginShape();
  ofVertex(-w, -h);
  ofVertex(w, -h);
  ofVertex(w, h);
  ofVertex(-w, h);
  ofEndShape();
}

