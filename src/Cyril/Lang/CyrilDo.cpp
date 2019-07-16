#include "CyrilDo.h"

CyrilDo::CyrilDo(Cyril* _e, Cyril* _c)
  : e(_e)
  , c(_c)
{
  valid = c->valid;
  if (_e->size() != 1) {
    yyerror("Incorrect size of expression in do loop");
    valid = false;
  }
}

CyrilDo::~CyrilDo()
{
  delete e;
  delete c;
}

void
CyrilDo::print()
{
  c->print();
  e->print();
  cout << "Do: " << endl;
}

int
CyrilDo::size()
{
  return 0;
}

void
CyrilDo::eval(CyrilState& _s)
{
  e->eval(_s);
  float val = _s.stk->top();
  _s.stk->pop();
  while (val > 0) {
    c->eval(_s);
    val--;
  }
}

int
CyrilDo::matchPushPop()
{
  return c->matchPushPop();
}

