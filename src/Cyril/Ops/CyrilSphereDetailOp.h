#include "CyrilOp.h"
#include "ofMain.h"

class CyrilSphereDetailOp : public CyrilOp
{
public:
  CyrilSphereDetailOp(Cyril* _c);

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};

