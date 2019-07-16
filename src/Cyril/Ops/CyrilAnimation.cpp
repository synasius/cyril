#include "CyrilAnimation.h"

CyrilAnimation::CyrilAnimation(Cyril* _e)
  : e(_e)
{}

CyrilAnimation::~CyrilAnimation()
{
  delete e;
}

void
CyrilAnimation::print()
{
  e->print();
  std::cout << "Animation" << std::endl;
}

int
CyrilAnimation::size()
{
  return 0;
}

void
CyrilAnimation::eval(CyrilState& state)
{
  // cout << endl << "Anim start" << endl;
  int total = e->size();
  // Push the total step size and current step time
  state.stk->push(total);
  state.stk->push((ofGetElapsedTimeMillis() % total));
  e->eval(state);
}
