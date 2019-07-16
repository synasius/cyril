#include "CyrilInitOp.h"

CyrilInitOp::CyrilInitOp(Cyril* _c)
  : CyrilOp(_c)
{
  int s = c->size();
  if (!(s == 0)) {
    yyerror("Init command takes 0 arguments");
    valid = false;
  }
}

void
CyrilInitOp::print()
{
  c->print();
  cout << "Init" << endl;
}

int
CyrilInitOp::size()
{
  return 0;
}

void
CyrilInitOp::eval(CyrilState& _s)
{
  if ((*_s.sym)[REG_FRAME] == 0) {
    c->eval(_s);
  }
}

