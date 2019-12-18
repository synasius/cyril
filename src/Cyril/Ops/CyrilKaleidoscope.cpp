#include "CyrilKaleidoscope.h"

CyrilKaleidoscope::CyrilKaleidoscope(std::unique_ptr<Cyril> e)
  : m_e(std::move(e))
{
  m_s = m_e->size();
  if (!(m_s == 1 || m_s == 0)) {
    yyerror("Kaleidoscope command takes 0 or 1 argument");
    valid = false;
  }
}

void
CyrilKaleidoscope::print()
{
  std::cout << "Kaleidoscope" << std::endl;
}

int
CyrilKaleidoscope::size()
{
  return 0;
}

void
CyrilKaleidoscope::update(CyrilState& state)
{
  // FX_KALEIDOSCOPE = 0
  state.post[0]->enable();
}

void
CyrilKaleidoscope::eval(CyrilState& state)
{
  float d;
  if (m_s == 0) {
    d = 2.0;
  } else {
    m_e->eval(state);

    d = state.stk->top();
    state.stk->pop();
  }
  state.kaleido->setSegments(d);
}
