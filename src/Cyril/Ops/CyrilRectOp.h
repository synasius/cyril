//
//  CyrilRectOp.h
//  cyril2
//
//  Created by Darren Mothersele on 05/11/2013.
//
//

#ifndef __cyril2__CyrilRectOp__
#define __cyril2__CyrilRectOp__

#include "ofMain.h"
#include "CyrilOp.h"

class CyrilRectOp : public CyrilOp {
public:
  CyrilRectOp(Cyril* _c);
  CyrilRectOp (const CyrilRectOp &other);
  ~CyrilRectOp () override;
  void print() override;
  Cyril *clone () override;
  int size() override;
  void eval(CyrilState &) override;
};

#endif /* defined(__cyril2__CyrilRectOp__) */
