#include "Particle.h"

Particle::Particle(ofMatrix4x4 _o,
                   ofVec3f _v,
                   ofVec3f _a,
                   float _h,
                   float _d,
                   std::shared_ptr<Cyril> _s)
  : origin(_o)
  , velocity(_v)
  , acceleration(_a)
  , health(_h)
  , decay(_d)
  , shape(_s)
{

  _sub_state.stk = new stack<float>;
  _sub_state.ms = new ofMatrixStack(ofGetWindowPtr());
  // FIXME: DELETE
  //_sub_state.ps = new vector<Particle*>;
  _sub_state.sym = new map<int, float>;
  _sub_state.cs = new map<int, Palette*>;
  _sub_state.img = new map<int, ofImage*>;
  (*_sub_state.sym)[REG_PARTICLE_HEALTH] = health;
  (*_sub_state.sym)[REG_PARTICLE_DECAY] = decay;
}

void
Particle::update()
{
  velocity += acceleration;
  location.translate(velocity);
  health -= decay;
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

bool Particle::isDead() const {
  return health <= 0;
}

