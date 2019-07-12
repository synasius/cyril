#include "Particle.h"

Particle::~Particle()
{
  delete shape;
}

void
Particle::draw(CyrilState* _s)
{

  ofPushMatrix();
  ofGetCurrentRenderer()->multMatrix(origin);
  ofGetCurrentRenderer()->multMatrix(location);

  _sub_state.parent = _s;

  shape->eval(_sub_state);

  ofPopMatrix();
}

