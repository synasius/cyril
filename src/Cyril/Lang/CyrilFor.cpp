#include "CyrilFor.h"
#include "CyrilPush.h"

CyrilFor::CyrilFor(int _i, Cyril* _e1, Cyril* _e2, Cyril* _e3, Cyril* _c)
  : loc(_i)
  , e1(_e1)
  , e2(_e2)
  , e3(_e3)
  , c(_c)
{
  valid = e1->valid && e2->valid && e3->valid && c->valid;
  if (_e1->size() != 1 || _e2->size() != 1 || _e3->size() != 1) {
    yyerror("Incorrect size of expression in for loop");
    valid = false;
  }
  CyrilPush* sC = dynamic_cast<CyrilPush*>(e3);
  if (sC == nullptr) {
    yyerror("Step of FOR loop must be a number");
    valid = false;
  } else {
    step = sC->getValue();
  }
}

CyrilFor::~CyrilFor()
{
  delete e1;
  delete e2;
  delete e3;
  delete c;
}

void
CyrilFor::print()
{
  e1->print();
  e2->print();
  e3->print();
  c->print();
  cout << "For: " << loc << endl;
}

int
CyrilFor::size()
{
  return 0;
}

void
CyrilFor::eval(CyrilState& _s)
{
  e1->eval(_s);
  (*_s.sym)[loc] = _s.stk->top();
  _s.stk->pop();
  float limit;
  e2->eval(_s);
  limit = _s.stk->top();
  _s.stk->pop();
  while ((*_s.sym)[loc] < limit) {
    c->eval(_s);
    (*_s.sym)[loc] += step;
  }
}

int
CyrilFor::matchPushPop()
{
  return c->matchPushPop();
}
