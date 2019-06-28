#include "CyrilOp.h"
#include "ofMain.h"

class CyrilPushMatrixOp : public CyrilOp
{
public:
  CyrilPushMatrixOp(Cyril* _c);

  void print() override;
  Cyril* clone() override;
  int size() override;
  void eval(CyrilState&) override;
  int matchPushPop() override;
};
