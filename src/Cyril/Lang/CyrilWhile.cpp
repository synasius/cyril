
#include "CyrilWhile.h"

CyrilWhile::CyrilWhile(Cyril* _e, Cyril* _c)
  : e(_e)
  , c(_c)
{
  valid = e->valid && c->valid;
  if (_e->size() != 1) {
    yyerror("Incorrect size of expression in while loop");
    valid = false;
  }
}

CyrilWhile::~CyrilWhile()
{
  delete e;
  delete c;
}

void
CyrilWhile::print()
{
  c->print();
  e->print();
  cout << "While: " << endl;
}

int
CyrilWhile::size()
{
  return 0;
}

void
CyrilWhile::eval(CyrilState& _s)
{
  float test;
  e->eval(_s);
  test = _s.stk->top();
  _s.stk->pop();
  while (test > 0) {
    c->eval(_s);
    e->eval(_s);
    test = _s.stk->top();
    _s.stk->pop();
  }
}

int
CyrilWhile::matchPushPop()
{
  return c->matchPushPop();
}

