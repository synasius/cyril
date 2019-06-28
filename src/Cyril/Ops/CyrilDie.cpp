#include "CyrilDie.h"

CyrilDie::CyrilDie(Cyril* _c)
  : CyrilOp(_c)
{
  int s = c->size();
  if (!(s == 0)) {
    yyerror("Die command requires no arguments");
    valid = false;
  }
}

CyrilDie::CyrilDie(const CyrilDie& other)
  : CyrilOp(other)
{}

void
CyrilDie::print()
{
  c->print();
  cout << "Die" << endl;
}

Cyril*
CyrilDie::clone()
{
  return new CyrilDie(*this);
}

int
CyrilDie::size()
{
  return 0;
}

void
CyrilDie::eval(CyrilState&)
{
  valid = false;
}
