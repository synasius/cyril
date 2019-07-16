//  Created by Darren Mothersele on 07/11/2013.

#include "CyrilAnimStep.h"

CyrilAnimStep::CyrilAnimStep(float _n, Cyril* _e1, Cyril* _e2)
  : n(_n)
  , e1(_e1)
  , e2(_e2)
{}

CyrilAnimStep::~CyrilAnimStep()
{
  delete e1;
  delete e2;
}

void
CyrilAnimStep::print()
{
  e1->print();
  e2->print();
  cout << "AnimStep " << n << endl;
}

int
CyrilAnimStep::size()
{
  if (!dynamic_cast<CyrilAnimStep*>(e2)) {
    // cout << " " << n << " " << endl;
    // we're last so just report to stack and we're done
    return n;
  }
  // cout << " " << n + e2->size();
  return n + e2->size();
}

void
CyrilAnimStep::eval(CyrilState& state)
{
  int step = state.stk->top();
  state.stk->pop();
  int total = state.stk->top();
  state.stk->pop();
  // cout << total << ":" << step << endl;
  if ((total - n) < step) {
    e1->eval(state);
  } else {
    state.stk->push(total - n);
    state.stk->push(step);
    e2->eval(state);
  }
}
