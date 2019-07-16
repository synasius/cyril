//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilHsbFun.h"

CyrilHsbFun::CyrilHsbFun(Cyril* _c)
  : CyrilFun(_c)
{
  int s = _c->size();
  if (!(s == 1 || s == 2 || s == 3)) {
    yyerror("HSB function has 1, 2 or 3 arguments");
    valid = false;
  }
}

void
CyrilHsbFun::print()
{
  c->print();
  std::cout << "HSB" << std::endl;
}

int
CyrilHsbFun::size()
{
  return 3;
}

void
CyrilHsbFun::eval(CyrilState& _s)
{
  c->eval(_s);
  float h = 0, s = 0, b = 0;
  switch (c->size()) {
    case 1:
      b = 255;
      s = 255;
      h = _s.stk->top();
      _s.stk->pop();
      break;
    case 2:
      b = _s.stk->top();
      _s.stk->pop();
      s = 255;
      h = _s.stk->top();
      _s.stk->pop();
      break;
    case 3:
      b = _s.stk->top();
      _s.stk->pop();
      s = _s.stk->top();
      _s.stk->pop();
      h = _s.stk->top();
      _s.stk->pop();
      break;
  }
  ofColor col;
  col.setHsb(h, s, b);
  // col = ofColor(col.r, col.g, col.b);
  _s.stk->push(float(col.r));
  _s.stk->push(float(col.g));
  _s.stk->push(float(col.b));
}

