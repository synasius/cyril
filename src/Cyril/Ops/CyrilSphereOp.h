#include "CyrilOp.h"
#include "ofMain.h"

class CyrilSphereOp : public CyrilOp
{
public:
  CyrilSphereOp(Cyril* _c);

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};
