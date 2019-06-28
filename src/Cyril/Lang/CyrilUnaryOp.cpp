#include "CyrilUnaryOp.h"

CyrilUnaryOp::CyrilUnaryOp(string _o, Cyril* _e)
  : o(_o)
  , e(_e)
{
  valid = e->valid;
  if ("!" == o) {
    op = OP_NOT;
    if (e->size() != 1) {
      yyerror("Operand to ! should be 1 value");
      valid = false;
    }
  } else {
    yyerror("Unknown operation");
    valid = false;
  }
}

CyrilUnaryOp::CyrilUnaryOp(const CyrilUnaryOp& other)
  : Cyril(other)
{
  o = other.o;
  e = other.e->clone();
}

CyrilUnaryOp::~CyrilUnaryOp()
{
  delete e;
}

void
CyrilUnaryOp::print()
{
  e->print();
  cout << "Unary: " << o << endl;
}

Cyril*
CyrilUnaryOp::clone()
{
  return new CyrilUnaryOp(*this);
}

int
CyrilUnaryOp::size()
{
  return 1;
}

void
CyrilUnaryOp::eval(CyrilState& _s)
{
  e->eval(_s);
  float v1 = _s.stk->top();
  _s.stk->pop();
  switch (op) {
    case OP_NOT:
      if (v1 > 0) {
        _s.stk->push(0);
      } else {
        _s.stk->push(1);
      }
      break;
    default:
      _s.stk->push(0);
      cout << "Warning unknown unary operator " << op << endl;
  }
}
