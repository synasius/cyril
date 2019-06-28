//
//  CyrilParticle.h
//  cyril2
//
//  Created by Darren Mothersele on 05/11/2013.
//
//

#ifndef cyril2_CyrilParticle_h
#define cyril2_CyrilParticle_h

#include <ofMain.h>
#include <cyril/cmds.h>

#include "Cyril.h"
#include "Particle.h"

class CyrilParticle : public Cyril
{
  Cyril* e;
  Cyril* c;

public:
  CyrilParticle(Cyril* _e, Cyril* _c)
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
  CyrilParticle(const CyrilParticle& other);
  ~CyrilParticle() override;
  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
  int matchPushPop() override { return c->matchPushPop(); }
};

#endif
