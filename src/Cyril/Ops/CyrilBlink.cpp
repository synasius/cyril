#include "CyrilBlink.h"

CyrilBlink::CyrilBlink(Cyril* _e, Cyril* _c)
  : e(_e)
  , c(_c)
{
  if (_e->size() != 2) {
    yyerror("Blink command requires on and off times");
    valid = false;
  }
}

CyrilBlink::~CyrilBlink()
{
  delete e;
  delete c;
}

void
CyrilBlink::print()
{
  e->print();
  c->print();
  std::cout << "Blink" << std::endl;
}

int
CyrilBlink::size()
{
  return 0;
}

void
CyrilBlink::eval(CyrilState& _s)
{
  e->eval(_s);
  float v2 = _s.stk->top();
  _s.stk->pop();
  float v1 = _s.stk->top();
  _s.stk->pop();
  // float t = (ofGetElapsedTimeMillis() / 1000.0);
  if ((v1 + v2) == 0) {
    std::cout << "Mod by 0 error in blink" << std::endl;
    return;
  }
  if ((ofGetElapsedTimeMillis() % int(v1 + v2)) < v1) {
    c->eval(_s);
  }
}

