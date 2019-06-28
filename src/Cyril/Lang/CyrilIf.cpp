#include "CyrilIf.h"

CyrilIf::CyrilIf(Cyril* _e, Cyril* _c)
  : e(_e)
  , c(_c)
{
  valid = e->valid && c->valid;
  if (_e->size() != 1) {
    yyerror("Incorrect size of expression in if condition");
    valid = false;
  }
}

CyrilIf::CyrilIf(const CyrilIf& other)
  : Cyril(other)
{
  e = other.e->clone();
  c = other.c->clone();
}

CyrilIf::~CyrilIf()
{
  delete e;
  delete c;
}

void
CyrilIf::print()
{
  c->print();
  e->print();
  cout << "If: " << endl;
}

Cyril*
CyrilIf::clone()
{
  return new CyrilIf(*this);
}

int
CyrilIf::size()
{
  return 0;
}

void
CyrilIf::eval(CyrilState& _s)
{
  e->eval(_s);
  float b = _s.stk->top();
  _s.stk->pop();
  if (b > 0) {
    c->eval(_s);
  }
}

int
CyrilIf::matchPushPop()
{
  return c->matchPushPop();
}
