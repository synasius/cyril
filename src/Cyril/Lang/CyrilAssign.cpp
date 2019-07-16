#include "CyrilAssign.h"

CyrilAssign::CyrilAssign(int _i, Cyril* _c)
  : loc(_i)
  , c(_c)
{
  valid = c->valid;
  int sz = _c->size();
  if (!(sz == 1 || sz == 3)) {
    yyerror("Assignment requires 1 argument (or 3 for color)");
    valid = false;
  }
}

CyrilAssign::~CyrilAssign()
{
  delete c;
}

void
CyrilAssign::print()
{
  c->print();
  cout << "Assign: " << loc << endl;
}

int
CyrilAssign::size()
{
  return 0;
}

void
CyrilAssign::eval(CyrilState& _s)
{
  c->eval(_s);
  switch (c->size()) {
    case 1:
      (*_s.sym)[loc] = _s.stk->top();
      _s.stk->pop();
      break;
    case 3:
      float b = _s.stk->top();
      _s.stk->pop();
      float g = _s.stk->top();
      _s.stk->pop();
      float r = _s.stk->top();
      _s.stk->pop();
      (*_s.sym)[loc] = ofColor(r, g, b).getHex();
      break;
  }
}

int
CyrilAssign::matchPushPop()
{
  return c->matchPushPop();
}

