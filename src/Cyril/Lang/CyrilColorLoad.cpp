//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilColorLoad.h"

CyrilColorLoad::CyrilColorLoad(int _i)
  : loc(_i)
{
  valid = true;
}

CyrilColorLoad::CyrilColorLoad(const CyrilColorLoad& other)
  : Cyril(other)
{
  loc = other.loc;
}

CyrilColorLoad::~CyrilColorLoad() {}

void
CyrilColorLoad::print()
{
  cout << "Color Load: " << loc << endl;
}

Cyril*
CyrilColorLoad::clone()
{
  return new CyrilColorLoad(*this);
}

int
CyrilColorLoad::size()
{
  return 3;
}

void
CyrilColorLoad::eval(CyrilState& state)
{
  ofColor c = ofColor::fromHex((*state.sym)[loc]);
  // cout << "Load color: " << c << endl;
  state.stk->push(float(c.r));
  state.stk->push(float(c.g));
  state.stk->push(float(c.b));
}
