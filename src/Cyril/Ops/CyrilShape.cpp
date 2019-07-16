//  Created by Darren Mothersele on 17/11/2013.

#include "CyrilShape.h"

CyrilShape::CyrilShape(Cyril* _e)
  : e(_e)
{}

CyrilShape::~CyrilShape()
{
  delete e;
}

void
CyrilShape::print()
{
  e->print();
  cout << "Shape" << endl;
}

int
CyrilShape::size()
{
  return 0;
}

void
CyrilShape::eval(CyrilState& state)
{
  ofBeginShape();
  e->eval(state);
  ofEndShape();
}
