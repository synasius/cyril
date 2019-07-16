#pragma once

#include <memory>
#include <cyril/cmds.h>
#include <ofMain.h>

#include "Cyril.h"
#include "CyrilState.h"

class Particle
{
public:
  ofMatrix4x4 origin;
  ofMatrix4x4 location;
  ofVec3f velocity;
  ofVec3f acceleration;
  float health;
  float decay;
  std::shared_ptr<Cyril> shape;
  CyrilState _sub_state;

  Particle(ofMatrix4x4 _o,
           ofVec3f _v,
           ofVec3f _a,
           float _h,
           float _d,
           std::shared_ptr<Cyril> _s);

  // deleted copy constructor and assignment operator
  Particle(const Particle&) = delete;
  Particle& operator=(const Particle&) = delete;

  Particle(Particle&&) = default;
  Particle& operator=(Particle&&) = default;

  void update();
  void draw(CyrilState* _s);

  bool isDead() const;
};
