//  Created by Darren Mothersele on 17/11/2013.

#include "CyrilShapeList.h"

CyrilShapeList::CyrilShapeList(Cyril* _c)
  : c(_c)
{
  int sz = _c->size();
  if (!(sz == 2 || sz == 3)) {
    yyerror("Shape list point requires 2 or 3 arguments");
    valid = false;
  }
}

CyrilShapeList::CyrilShapeList(const CyrilShapeList& other)
  : Cyril(other)
{
  c = other.c->clone();
}

CyrilShapeList::~CyrilShapeList()
{
  delete c;
}

void
CyrilShapeList::print()
{
  c->print();
  cout << "ShapeList point" << endl;
}

Cyril*
CyrilShapeList::clone()
{
  return new CyrilShapeList(*this);
}

int
CyrilShapeList::size()
{
  return 0;
}

void
CyrilShapeList::eval(CyrilState& state)
{
  c->eval(state);
  float x, y, z;
  switch (c->size()) {
    case 2:
      y = state.stk->top();
      state.stk->pop();
      x = state.stk->top();
      state.stk->pop();
      ofVertex(x, y);
      break;
    case 3:
      z = state.stk->top();
      state.stk->pop();
      y = state.stk->top();
      state.stk->pop();
      x = state.stk->top();
      state.stk->pop();
      ofVertex(x, y, z);
      break;
  }
}
