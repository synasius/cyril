#include "CyrilPush.h"

CyrilPush::CyrilPush(float _f)
  : f(_f)
{
  valid = true;
}

CyrilPush::~CyrilPush() {}

void
CyrilPush::print()
{
  cout << "Push: " << f << endl;
}

int
CyrilPush::size()
{
  return 1;
}

float
CyrilPush::getValue()
{
  return f;
}

void
CyrilPush::eval(CyrilState& _s)
{
  _s.stk->push(f);
}
