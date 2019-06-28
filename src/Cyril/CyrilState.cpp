//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilState.h"
#include "Palette.h"
#include "Particle.h"

CyrilState::CyrilState(std::map<int, float>* _t,
                       std::stack<float>* _s,
                       ofMatrixStack* _m,
                       std::vector<Particle*>* _p,
                       std::map<int, Palette*>* _c,
                       std::map<int, ofImage*>* _i,
                       CyrilState* _pr)
  : sym(_t)
  , stk(_s)
  , ms(_m)
  , ps(_p)
  , cs(_c)
  , img(_i)
  , parent(_pr)
{}

CyrilState::CyrilState() {}

CyrilState::~CyrilState()
{
  delete sym;
  delete stk;
  delete ms;

  while (!ps->empty()) {
    delete ps->back(), ps->pop_back();
  }

  delete ps;
  for (auto it = cs->begin(); it != cs->end(); ++it) {
    delete (*it).second;
  }

  delete cs;
  for (auto it = img->begin(); it != img->end(); ++it) {
    delete (*it).second;
  }

  delete img;
}
