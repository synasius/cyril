#include <map>

#include "CyrilLoad.h"

CyrilLoad::CyrilLoad(int _i)
  : m_loc(_i)
{
  valid = true;
}

CyrilLoad::~CyrilLoad() {}

void
CyrilLoad::print()
{
  cout << "Load: " << m_loc << endl;
}

int
CyrilLoad::size()
{
  return 1;
}

void
CyrilLoad::eval(CyrilState& state)
{
  // Here we should check if the location exists in the current map
  auto search = state.sym->find(m_loc);
  if (search != state.sym->end()) {
    state.stk->push((*state.sym)[m_loc]);
    return;
  }

  // If the location m_loc does not exists we check on the parent state
  if (state.parent->sym != nullptr) {
    auto search = state.parent->sym->find(m_loc);
    if (search != state.parent->sym->end()) {
      state.stk->push((*state.parent->sym)[m_loc]);
    } else {
      state.stk->push((*state.sym)[m_loc]);
    }
  }
}
