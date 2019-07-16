#include <memory>
#include <cyril/cmds.h>
#include <ofMain.h>

#include "Cyril.h"
#include "Particle.h"

class CyrilParticle : public Cyril
{
public:
  CyrilParticle(Cyril* _e, Cyril* _c);
  ;
  ~CyrilParticle() override;

  void print() override;
  int size() override;
  void eval(CyrilState&) override;
  int matchPushPop() override { return c->matchPushPop(); }

private:
  Cyril* e;
  std::shared_ptr<Cyril> c;
};
