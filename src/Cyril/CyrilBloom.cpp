//  Created by Darren Mothersele on 15/09/2014

#include "CyrilBloom.h"

CyrilBloom::CyrilBloom(Cyril* _e)
  : e(_e)
{
  s = e->size();
  if (!(s == 1 || s == 0)) {
    // Width, Height - or single argument for same w and h
    yyerror("Bloom FX command takes 0 or 1 arguments");
    valid = false;
  }
  prevBloom = 0.001953125;
}

CyrilBloom::~CyrilBloom() {}

void
CyrilBloom::print()
{
  cout << "CyrilBloom" << endl;
}

int
CyrilBloom::size()
{
  return 0;
}

void
CyrilBloom::update(CyrilState& state)
{
  // FX_BLOOM = 3
  state.post[3]->enable();
}

void
CyrilBloom::eval(CyrilState& state)
{
  float bloom;
  if (s == 1) {
    e->eval(state);
    bloom = (state.stk->top()) / 1000.0f;
    state.stk->pop();
  } else {
    // same defaults as ofxPostProcessing:
    bloom = 0.001953125;
  }
  if (bloom != prevBloom) {
    prevBloom = bloom;
    state.bloom->setIncrements(bloom, 0, 0, bloom);
  }
}
