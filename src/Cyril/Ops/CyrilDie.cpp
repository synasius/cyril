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

void
CyrilDie::print()
{
  c->print();
  cout << "Die" << endl;
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
