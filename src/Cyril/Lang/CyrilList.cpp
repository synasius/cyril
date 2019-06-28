#include "CyrilList.h"

CyrilList::CyrilList(Cyril* _c1, Cyril* _c2)
  : c1(_c1)
  , c2(_c2)
{
  valid = c1->valid && c2->valid;
}

CyrilList::CyrilList(const CyrilList& other)
  : Cyril(other)
{
  c1 = other.c1->clone();
  c2 = other.c2->clone();
}

CyrilList::~CyrilList()
{
  delete c1;
  delete c2;
}

void
CyrilList::print()
{
  c1->print();
  c2->print();
}

Cyril*
CyrilList::clone()
{
  return new CyrilList(*this);
}

int
CyrilList::size()
{
  return c1->size() + c2->size();
}

void
CyrilList::update(CyrilState& _s)
{
  c1->update(_s);
  c2->update(_s);
}

void
CyrilList::eval(CyrilState& _s)
{
  c1->eval(_s);
  c2->eval(_s);
}

int
CyrilList::matchPushPop()
{
  return c1->matchPushPop() + c2->matchPushPop();
}
