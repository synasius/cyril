//  Created by Darren Mothersele on 05/11/2013.

#include "CyrilOp.h"

CyrilOp::CyrilOp(Cyril* _c)
  : c(_c)
{}

CyrilOp::~CyrilOp()
{
  delete c;
}

void
CyrilOp::print()
{
  c->print();
  cout << "No Op" << endl;
}

int
CyrilOp::size()
{
  return 0;
}

void
CyrilOp::eval(CyrilState&)
{}

