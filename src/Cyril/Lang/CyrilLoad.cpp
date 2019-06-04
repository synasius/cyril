#include <map>

#include "CyrilLoad.h"

CyrilLoad::CyrilLoad(int _i)
  : m_loc(_i)
{
  valid = true;
}

CyrilLoad::CyrilLoad(const CyrilLoad& other)
{
  m_loc = other.m_loc;
}

CyrilLoad::~CyrilLoad() {}

void
CyrilLoad::print()
{
  cout << "Load: " << m_loc << endl;
}

Cyril*
CyrilLoad::clone()
{
  return new CyrilLoad(*this);
}

int
CyrilLoad::size()
{
  return 1;
}

void
CyrilLoad::eval(CyrilState& _s)
{
  // Here we should check if the location exists in the current map
  auto search = _s.sym->find(m_loc);
  if (search != _s.sym->end()) {
      _s.stk->push((*_s.sym)[m_loc]);
      return;
  }

  // If the location m_loc does not exists we check on the parent state
  if (_s.parent->sym != nullptr) {
    auto search = _s.parent->sym->find(m_loc);
    if (search != _s.parent->sym->end()) {
      _s.stk->push((*_s.parent->sym)[m_loc]);
    } else {
      _s.stk->push((*_s.sym)[m_loc]);
    }
  }
}

