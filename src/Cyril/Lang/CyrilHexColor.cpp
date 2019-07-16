#include "CyrilHexColor.h"

CyrilHexColor::CyrilHexColor(const char* _s)
  : s(_s)
{
  std::string converter(s);
  std::stringstream sr(converter.substr(0, 2));
  std::stringstream sg(converter.substr(2, 2));
  std::stringstream sb(converter.substr(4, 2));
  int ir, ig, ib;
  sr >> hex >> ir;
  sg >> hex >> ig;
  sb >> hex >> ib;
  r = ir;
  g = ig;
  b = ib;
  // cout << "Debug color: " << r << "," << g << "," << b << endl;
  valid = true;
}

CyrilHexColor::~CyrilHexColor() {}

void
CyrilHexColor::print()
{
  std::cout << "Hex: " << s << std::endl;
}

int
CyrilHexColor::size()
{
  return 3;
}

void
CyrilHexColor::eval(CyrilState& state)
{
  state.stk->push(r);
  state.stk->push(g);
  state.stk->push(b);
}
