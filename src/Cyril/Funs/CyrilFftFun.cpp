#include "CyrilFftFun.h"

CyrilFftFun::CyrilFftFun(Cyril* _c)
  : CyrilFun(_c)
{
  int s = _c->size();
  if (s != 1) {
    yyerror("FFT function has 1 argument");
    valid = false;
  }
}

void
CyrilFftFun::print()
{
  c->print();
  cout << "Palette" << endl;
}

int
CyrilFftFun::size()
{
  return 1;
}

void
CyrilFftFun::eval(CyrilState& state)
{
  c->eval(state);
  int d = state.stk->top();
  state.stk->pop();
  auto v = (*state.sym)[REG_BEAT_FFT_START + (d % 32)];
  //std::cout << "FFT of " << (d % 32) << " is " << v << std::endl;
  // float f = fftSubbands[d % 32];

  state.stk->push((*state.sym)[REG_BEAT_FFT_START + (d % 32)]);
}
