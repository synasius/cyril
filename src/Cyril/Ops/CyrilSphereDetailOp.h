//
//  CyrilSphereDetailOp.h
//  cyril2
//
//  Created by Darren Mothersele on 06/11/2013.
//
//

#ifndef __cyril2__CyrilSphereDetailOp__
#define __cyril2__CyrilSphereDetailOp__

#include "ofMain.h"
#include "CyrilOp.h"

class CyrilSphereDetailOp : public CyrilOp {
public:
  CyrilSphereDetailOp(Cyril* _c);
  CyrilSphereDetailOp (const CyrilSphereDetailOp &other);
  ~CyrilSphereDetailOp () override;
  void print() override;
  Cyril *clone () override;
  int size() override;
  void eval(CyrilState &) override;
};

#endif /* defined(__cyril2__CyrilSphereDetailOp__) */
