#include "CyrilBinaryOp.h"

CyrilBinaryOp::CyrilBinaryOp(string _o, Cyril* _e1, Cyril* _e2)
  : o(_o)
  , e1(_e1)
  , e2(_e2)
{
  valid = e1->valid && e2->valid;
  if ("+" == o) {
    op = OP_PLUS;
    if (e1->size() != 1) {
      yyerror("Left operand to + should be 1 value");
      valid = false;
    }
    if (e2->size() != 1) {
      yyerror("Right operand to + should be 1 value");
      valid = false;
    }
  } else if ("-" == o) {
    op = OP_MINUS;
    if (e1->size() != 1) {
      yyerror("Left operand to - should be 1 value");
      valid = false;
    }
    if (e2->size() != 1) {
      yyerror("Right operand to - should be 1 value");
      valid = false;
    }
  } else if ("/" == o) {
    op = OP_DIV;
    if (e1->size() != 1) {
      yyerror("Left operand to / should be 1 value");
      valid = false;
    }
    if (e2->size() != 1) {
      yyerror("Right operand to / should be 1 value");
      valid = false;
    }
  } else if ("*" == o) {
    op = OP_MULT;
    if (e1->size() != 1) {
      yyerror("Left operand to * should be 1 value");
      valid = false;
    }
    if (e2->size() != 1) {
      yyerror("Right operand to * should be 1 value");
      valid = false;
    }
  } else if ("%" == o) {
    op = OP_MOD;
    if (e1->size() != 1) {
      yyerror("Left operand to % should be 1 value");
      valid = false;
    }
    if (e2->size() != 1) {
      yyerror("Right operand to % should be 1 value");
      valid = false;
    }
  } else if ("==" == o) {
    op = OP_EQ;
    if (e1->size() != 1) {
      yyerror("Left operand to == should be 1 value");
      valid = false;
    }
    if (e2->size() != 1) {
      yyerror("Right operand to == should be 1 value");
      valid = false;
    }
  } else if ("!=" == o) {
    op = OP_NOTEQ;
    if (e1->size() != 1) {
      yyerror("Left operand to != should be 1 value");
      valid = false;
    }
    if (e2->size() != 1) {
      yyerror("Right operand to != should be 1 value");
      valid = false;
    }
  } else if ("<" == o) {
    op = OP_LESS;
    if (e1->size() != 1) {
      yyerror("Left operand to < should be 1 value");
      valid = false;
    }
    if (e2->size() != 1) {
      yyerror("Right operand to < should be 1 value");
      valid = false;
    }
  } else if ("<=" == o) {
    op = OP_LESSEQ;
    if (e1->size() != 1) {
      yyerror("Left operand to <= should be 1 value");
      valid = false;
    }
    if (e2->size() != 1) {
      yyerror("Right operand to <= should be 1 value");
      valid = false;
    }
  } else if (">" == o) {
    op = OP_GR;
    if (e1->size() != 1) {
      yyerror("Left operand to > should be 1 value");
      valid = false;
    }
    if (e2->size() != 1) {
      yyerror("Right operand to > should be 1 value");
      valid = false;
    }
  } else if (">=" == o) {
    op = OP_GREQ;
    if (e1->size() != 1) {
      yyerror("Left operand to >= should be 1 value");
      valid = false;
    }
    if (e2->size() != 1) {
      yyerror("Right operand to >= should be 1 value");
      valid = false;
    }
  } else if ("&" == o) {
    op = OP_AND;
    if (e1->size() != 1) {
      yyerror("Left operand to AND should be 1 value");
      valid = false;
    }
    if (e2->size() != 1) {
      yyerror("Right operand to AND should be 1 value");
      valid = false;
    }
  } else if ("|" == o) {
    op = OP_OR;
    if (e1->size() != 1) {
      yyerror("Left operand to OR should be 1 value");
      valid = false;
    }
    if (e2->size() != 1) {
      yyerror("Right operand to OR should be 1 value");
      valid = false;
    }
  } else {
    yyerror("Unknown operation");
    valid = false;
  }
}

CyrilBinaryOp::~CyrilBinaryOp()
{
  delete e1;
  delete e2;
}

void
CyrilBinaryOp::print()
{
  e1->print();
  e2->print();
  std::cout << "Binary: " << o << endl;
}

int
CyrilBinaryOp::size()
{
  return 1;
}

void
CyrilBinaryOp::eval(CyrilState& _s)
{
  e1->eval(_s);
  float v1 = _s.stk->top();
  _s.stk->pop();
  e2->eval(_s);
  float v2 = _s.stk->top();
  _s.stk->pop();
  switch (op) {
    case OP_MINUS:
      _s.stk->push(v1 - v2);
      break;
    case OP_PLUS:
      _s.stk->push(v1 + v2);
      break;
    case OP_MULT:
      _s.stk->push(v1 * v2);
      break;
    case OP_DIV:
      if (v2 == 0) {
        std::cout << "Warning: divide by 0" << endl;
        _s.stk->push(0);
      } else {
        _s.stk->push(v1 / v2);
      }
      break;
    case OP_MOD:
      if (v2 == 0) {
        std::cout << "Warning: divide(mod) by 0" << endl;
        _s.stk->push(0);
      } else {
        auto res = std::fmod(v1, v2);
        _s.stk->push(res);
      }
      break;
    case OP_EQ:
      if (v1 == v2) {
        _s.stk->push(1);
      } else {
        _s.stk->push(0);
      }
      break;
    case OP_NOTEQ:
      if (v1 != v2) {
        _s.stk->push(1);
      } else {
        _s.stk->push(0);
      }
      break;
    case OP_LESS:
      if (v1 < v2) {
        _s.stk->push(1);
      } else {
        _s.stk->push(0);
      }
      break;
    case OP_LESSEQ:
      if (v1 <= v2) {
        _s.stk->push(1);
      } else {
        _s.stk->push(0);
      }
      break;
    case OP_GR:
      if (v1 > v2) {
        _s.stk->push(1);
      } else {
        _s.stk->push(0);
      }
      break;
    case OP_GREQ:
      if (v1 >= v2) {
        _s.stk->push(1);
      } else {
        _s.stk->push(0);
      }
      break;
    case OP_AND:
      if (v1 > 0 && v2 > 0) {
        _s.stk->push(1);
      } else {
        _s.stk->push(0);
      }
      break;
    case OP_OR:
      if (v1 > 0 || v2 > 0) {
        _s.stk->push(1);
      } else {
        _s.stk->push(0);
      }
      break;
    default:
      _s.stk->push(0);
      std::cout << "Warning unknown operator " << op << endl;
  }
}
