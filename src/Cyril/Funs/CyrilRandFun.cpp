#include "CyrilRandFun.h"

CyrilRandFun::CyrilRandFun(Cyril* _c)
  : CyrilFun(_c)
{
  int s = _c->size();
  if (!(s == 0 || s == 1 || s == 2)) {
    yyerror("Rand function has 0, 1 or 2 arguments");
    valid = false;
  }
}

void
CyrilRandFun::print()
{
  c->print();
  cout << "Rand" << endl;
}

int
CyrilRandFun::size()
{
  return 1;
}

void
CyrilRandFun::eval(CyrilState& state)
{
  c->eval(state);
  float r = 0, x = 0, y = 0;
  switch (c->size()) {
    case 0:
      r = ofRandomf();
      break;
    case 1:
      x = state.stk->top();
      state.stk->pop();
      r = ofRandom(x);
      break;
    case 2:
      x = state.stk->top();
      state.stk->pop();
      y = state.stk->top();
      state.stk->pop();
      r = ofRandom(x, y);
      break;
  }
  state.stk->push(r);
}
