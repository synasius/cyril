//  Created by Darren Mothersele on 06/11/2013.

#include "CyrilState.h"
#include "Palette.h"
#include "Particle.h"

CyrilState::CyrilState() {}

CyrilState::~CyrilState()
{
  delete sym;
  delete stk;
  delete ms;

  for (auto it = cs->begin(); it != cs->end(); ++it) {
    delete (*it).second;
  }

  delete cs;
  for (auto it = img->begin(); it != img->end(); ++it) {
    delete (*it).second;
  }

  delete img;
}
