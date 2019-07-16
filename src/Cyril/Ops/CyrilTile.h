#include "Cyril.h"

class CyrilTile : public Cyril
{
protected:
  Cyril* e;
  Cyril* c;

public:
  CyrilTile(Cyril* _e, Cyril* _c);
  ~CyrilTile() override;

  void print() override;
  int size() override;
  void eval(CyrilState&) override;
  int matchPushPop() override { return c->matchPushPop(); }
};
