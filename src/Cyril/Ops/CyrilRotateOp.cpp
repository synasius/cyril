#include "CyrilRotateOp.h"

CyrilRotateOp::CyrilRotateOp(Cyril* _c)
  : CyrilOp(_c)
{
  int s = c->size();
  if (!(s == 0 || s == 1 || s == 3 || s == 4)) {
    yyerror("Rotate command requires 4, 3, 1 or 0 arguments");
    valid = false;
  }
}

void
CyrilRotateOp::print()
{
  c->print();
  std::cout << "Rotate" << std::endl;
}

Cyril*
CyrilRotateOp::clone()
{
  return new CyrilRotateOp(*this);
}

int
CyrilRotateOp::size()
{
  return 0;
}

void
CyrilRotateOp::eval(CyrilState& state)
{
  c->eval(state);
  float w = 0, x = 0, y = 0, z = 0;
  switch (c->size()) {
    case 4:
      z = state.stk->top();
      state.stk->pop();
      y = state.stk->top();
      state.stk->pop();
      x = state.stk->top();
      state.stk->pop();
      w = state.stk->top();
      state.stk->pop();
      ofRotateDeg(w, x, y, z);

      state.ms->rotateRad(ofDegToRad(w), x, y, z);
      break;

    case 3:
      y = state.stk->top();
      state.stk->pop();
      x = state.stk->top();
      state.stk->pop();
      w = state.stk->top();
      state.stk->pop();
      ofRotateXDeg(x);
      ofRotateYDeg(y);
      ofRotateZDeg(z);

      state.ms->rotateRad(ofDegToRad(x), 1, 0, 0);
      state.ms->rotateRad(ofDegToRad(y), 0, 1, 0);
      state.ms->rotateRad(ofDegToRad(z), 0, 0, 1);
      break;

    case 1:
      w = state.stk->top();
      state.stk->pop();
      ofRotateZDeg(w);
      state.ms->rotateRad(ofDegToRad(w), 0, 0, 1);
      break;

    default:
      w = (*state.sym)[REG_TIME] / 36.0;
      ofRotateDeg(w, 0, 1, 0.5);
      state.ms->rotateRad(ofDegToRad(w), 0, 1, 0.5);
      break;
  }
}
