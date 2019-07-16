#include "CyrilParticle.h"

CyrilParticle::CyrilParticle(Cyril* _e, Cyril* _c)
  : e(_e)
  , c(_c)
{
  valid = e->valid && c->valid;
  int s = e->size();
  if (!(s == 1 || s == 4)) {
    yyerror("Particle command requires 1 or 4 arguments");
    valid = false;
  }
}

CyrilParticle::~CyrilParticle()
{
  delete e;
}

void
CyrilParticle::print()
{
  e->print();
  c->print();
  cout << "Particle" << endl;
}

int
CyrilParticle::size()
{
  return 0;
}

void
CyrilParticle::eval(CyrilState& _s)
{
  e->eval(_s);
  float x = 0, w = 0, h = 0, d = 0;

  switch (e->size()) {
    case 1:
      d = 0;
      h = 0;
      w = 0;
      x = _s.stk->top();
      _s.stk->pop();
      break;
    case 4:
      d = _s.stk->top();
      _s.stk->pop();
      h = _s.stk->top();
      _s.stk->pop();
      w = _s.stk->top();
      _s.stk->pop();
      x = _s.stk->top();
      _s.stk->pop();
      break;
  }
  // cout << "Release particle at " << x << ", " << y << ", " << z << endl;
  // GLfloat matrix[16];
  // glGetFloatv (GL_MODELVIEW_MATRIX, matrix);
  // ofMatrix4x4 m(matrix);
  _s.ps.push_back(std::make_unique<Particle>(_s.ms->getCurrentMatrix(),
                                             ofVec3f(x, 0, 0),
                                             ofVec3f(w, h, d),
                                             (*_s.sym)[REG_PARTICLE_HEALTH],
                                             (*_s.sym)[REG_PARTICLE_DECAY],
                                             c));
}
