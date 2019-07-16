#include "CyrilLightOp.h"

CyrilLightOp::CyrilLightOp(Cyril* _c)
  : CyrilOp(_c)
{
  int s = c->size();
  if (!(s == 3 || s == 6)) {
    yyerror("Light command requires 3 or 6 arguments");
    valid = false;
  }
}

void
CyrilLightOp::print()
{
  c->print();
  cout << "Light" << endl;
}

int
CyrilLightOp::size()
{
  return 0;
}

void
CyrilLightOp::eval(CyrilState& _s)
{
  if (_s.light != nullptr) {
    c->eval(_s);
    float x, y, z;
    switch (c->size()) {
      case 3:
        z = _s.stk->top();
        _s.stk->pop();
        y = _s.stk->top();
        _s.stk->pop();
        x = _s.stk->top();
        _s.stk->pop();
        _s.light->setPosition(x, y, z);
        break;
      case 6:
        z = _s.stk->top();
        _s.stk->pop();
        y = _s.stk->top();
        _s.stk->pop();
        x = _s.stk->top();
        _s.stk->pop();
        //_s.light->setAmbientColor(ofColor(x, y, z));
        _s.light->setDiffuseColor(ofColor(x, y, z));
        //_s.light->setAmbientColor(ofColor(x, y, z));
        z = _s.stk->top();
        _s.stk->pop();
        y = _s.stk->top();
        _s.stk->pop();
        x = _s.stk->top();
        _s.stk->pop();
        //_s.light->setSpecularColor(ofColor(x, y, z));
        _s.light->setAmbientColor(ofColor(x, y, z));
        break;
    }
  }
}

