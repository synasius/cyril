#include "CyrilNamedColor.h"

CyrilNamedColor::CyrilNamedColor(const char* _s)
  : s(_s)
{

  ofColor c = colorNameMap[s];

  r = c.r;
  g = c.g;
  b = c.b;
  // cout << "Debug color: " << r << "," << g << "," << b << endl;
  valid = true;
}

CyrilNamedColor::CyrilNamedColor(const CyrilNamedColor& other)
  : Cyril(other)
{
  s = other.s;
}

CyrilNamedColor::~CyrilNamedColor() {}

void
CyrilNamedColor::print()
{
  cout << "Named color: " << s << endl;
}

Cyril*
CyrilNamedColor::clone()
{
  return new CyrilNamedColor(*this);
}

int
CyrilNamedColor::size()
{
  return 3;
}

void
CyrilNamedColor::eval(CyrilState& state)
{
  state.stk->push(r);
  state.stk->push(g);
  state.stk->push(b);
}