//
//  CyrilPegOp.h
//  cyril2
//
//  Created by Darren Mothersele on 05/11/2013.
//
//

#ifndef __cyril2__CyrilPegOp__
#define __cyril2__CyrilPegOp__

#include "ofMain.h"
#include "CyrilOp.h"

class CyrilPegOp : public CyrilOp {
public:
  CyrilPegOp(Cyril* _c);
  CyrilPegOp (const CyrilPegOp &other);
  ~CyrilPegOp () override;
  void print() override;
  Cyril *clone () override;
  int size() override;
  void eval(CyrilState &) override;
};

#endif /* defined(__cyril2__CyrilPegOp__) */
