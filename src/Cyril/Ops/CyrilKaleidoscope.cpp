#include "CyrilKaleidoscope.h"

CyrilKaleidoscope::CyrilKaleidoscope(Cyril* _e)
  : e(_e)
{
  s = e->size();
  if (!(s == 1 || s == 0)) {
    yyerror("Kaleidoscope command takes 0 or 1 argument");
    valid = false;
  }
}

CyrilKaleidoscope::~CyrilKaleidoscope()
{
  delete e;
}

void
CyrilKaleidoscope::print()
{
  cout << "Kaleidoscope" << endl;
}

int
CyrilKaleidoscope::size()
{
  return 0;
}

void
CyrilKaleidoscope::update(CyrilState& _s)
{
  // FX_KALEIDOSCOPE = 0
  _s.post[0]->enable();
}

void
CyrilKaleidoscope::eval(CyrilState& _s)
{
  float d;
  if (s == 0) {
    d = 2.0;
  } else {
    e->eval(_s);
    d = _s.stk->top();
    _s.stk->pop();
  }
  _s.kaleido->setSegments(d);
}

