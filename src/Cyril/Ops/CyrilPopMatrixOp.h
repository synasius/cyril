#include "CyrilOp.h"
#include "ofMain.h"

class CyrilPopMatrixOp : public CyrilOp
{
public:
  CyrilPopMatrixOp(Cyril* _c);

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
  int matchPushPop() override;
};
