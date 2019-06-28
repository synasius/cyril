#include "CyrilBackgroundOp.h"

CyrilBackgroundOp::CyrilBackgroundOp(Cyril* _c)
  : CyrilOp(_c)
{
  int s = c->size();
  if (!(s == 4 || s == 3 || s == 1)) {
    yyerror("background command requires 1 (palette) or 3 arguments (r,g,b) or "
            "a hex color");
    valid = false;
  }
}

void
CyrilBackgroundOp::print()
{
  c->print();
  cout << "Background" << endl;
}

Cyril*
CyrilBackgroundOp::clone()
{
  return new CyrilBackgroundOp(*this);
}

int
CyrilBackgroundOp::size()
{
  return 0;
}

void
CyrilBackgroundOp::eval(CyrilState& _s)
{
  c->eval(_s);
  float r, g, b;
  float a = 255.0;
  if (c->size() == 4) {
    a = _s.stk->top();
    _s.stk->pop();
    b = _s.stk->top();
    _s.stk->pop();
    g = _s.stk->top();
    _s.stk->pop();
    r = _s.stk->top();
    _s.stk->pop();

    ofClear(r, g, b, a);
    return;
  }
  if (c->size() == 3) {
    b = _s.stk->top();
    _s.stk->pop();
    g = _s.stk->top();
    _s.stk->pop();
    r = _s.stk->top();
    _s.stk->pop();

    ofClear(r, g, b, a);
    return;
  } else {
    b = _s.stk->top();
    _s.stk->pop();
    // load palette from b
    (*_s.cs)[b]->drawBackground();
  }
}

