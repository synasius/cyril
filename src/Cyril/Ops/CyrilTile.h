//
//  CyrilTileOp.h
//  Cyril
//
//  Created by Darren Mothersele on 17/11/2013.
//
//

#ifndef __Cyril__CyrilTileOp__
#define __Cyril__CyrilTileOp__

#include "Cyril.h"


class CyrilTile : public Cyril {
protected:
  Cyril* e;
  Cyril* c;
public:
  CyrilTile(Cyril* _e, Cyril* _c);
  CyrilTile (const CyrilTile &other);
  ~CyrilTile () override;
  void print() override;
  Cyril *clone () override;
  int size() override;
  void eval(CyrilState &) override;
  int matchPushPop() override { return c->matchPushPop(); }
};

#endif /* defined(__Cyril__CyrilTileOp__) */
