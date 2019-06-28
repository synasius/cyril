#include "CyrilOp.h"
#include "ofMain.h"

class CyrilPegOp : public CyrilOp
{
public:
  CyrilPegOp(Cyril* _c);

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
};
