//  Created by Darren Mothersele on 15/09/2014.

#include "CyrilPixelate.h"

CyrilPixelate::CyrilPixelate(Cyril* _e)
  : e(_e)
{
  s = e->size();
  if (!(s == 2 || s == 1 || s == 0)) {
    // Width, Height - or single argument for same w and h
    yyerror("Pixelate FX command takes 0, 1 or 2 arguments");
    valid = false;
  }
}

CyrilPixelate::~CyrilPixelate() {}

void
CyrilPixelate::print()
{
  cout << "CyrilPixelate" << endl;
}

int
CyrilPixelate::size()
{
  return 0;
}

void
CyrilPixelate::update(CyrilState& state)
{
  // FX_PIXELATE = 2
  state.post[2]->enable();
}

void
CyrilPixelate::eval(CyrilState& state)
{
  float width, height;
  if (s == 2) {
    e->eval(state);
    height = state.stk->top();
    state.stk->pop();
    width = state.stk->top();
    state.stk->pop();
  } else if (s == 1) {
    e->eval(state);
    height = state.stk->top();
    width = height;
    state.stk->pop();
  } else {
    // same defaults as ofxPostProcessing:
    width = 100;
    height = 100;
  }
  state.pixelate->setResolution(width, height);
}
