//
//  CyrilSphereOp.h
//  cyril2
//
//  Created by Darren Mothersele on 05/11/2013.
//
//

#ifndef __cyril2__CyrilSphereOp__
#define __cyril2__CyrilSphereOp__

#include "ofMain.h"
#include "CyrilOp.h"

class CyrilSphereOp : public CyrilOp {
public:
  CyrilSphereOp(Cyril* _c);
  CyrilSphereOp (const CyrilSphereOp &other);
  ~CyrilSphereOp () override;
  void print() override;
  Cyril *clone () override;
  int size() override;
  void eval(CyrilState &) override;
};

#endif /* defined(__cyril2__CyrilSphereOp__) */
