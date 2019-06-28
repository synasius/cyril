#include "CyrilAnimation.h"

CyrilAnimation::CyrilAnimation(Cyril* _e)
  : e(_e)
{}

CyrilAnimation::CyrilAnimation(const CyrilAnimation& other)
  : Cyril(other)
{
  e = other.e->clone();
}

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

Cyril*
CyrilAnimation::clone()
{
  return new CyrilAnimation(*this);
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
