#include <cyril/cmds.h>
#include <ofMain.h>

#include "Cyril.h"
#include "Particle.h"

class CyrilParticle : public Cyril
{
public:
  CyrilParticle(Cyril* _e, Cyril* _c);
  ;
  CyrilParticle(const CyrilParticle& other);
  ~CyrilParticle() override;

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
  int matchPushPop() override { return c->matchPushPop(); }

private:
  Cyril* e;
  Cyril* c;
};
