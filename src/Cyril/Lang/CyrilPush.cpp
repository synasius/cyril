#include "CyrilPush.h"

CyrilPush::CyrilPush(float _f)
  : f(_f)
{
  valid = true;
}

CyrilPush::CyrilPush(const CyrilPush& other)
  : Cyril(other)
{
  f = other.f;
}

CyrilPush::~CyrilPush() {}

void
CyrilPush::print()
{
  cout << "Push: " << f << endl;
}

Cyril*
CyrilPush::clone()
{
  return new CyrilPush(*this);
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
