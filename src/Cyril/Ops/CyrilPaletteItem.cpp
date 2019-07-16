#include "CyrilPaletteItem.h"

CyrilPaletteItem::CyrilPaletteItem(float _f, Cyril* _e)
  : e(_e)
  , d(_f)
{
  /*
  string converter(_s);
  stringstream sr(converter.substr(0,2));
  stringstream sg(converter.substr(2,2));
  stringstream sb(converter.substr(4,2));
  int ir, ig, ib;
  sr >> hex >> ir;
  sg >> hex >> ig;
  sb >> hex >> ib;
  r = ir; g = ig; b = ib;
  */

  int sz = _e->size();
  if (!(sz == 3)) {
    yyerror("Palette item requires 3 arguments");
    valid = false;
  }
  paletteCalc = false;
}

CyrilPaletteItem::~CyrilPaletteItem()
{
  delete e;
}

void
CyrilPaletteItem::print()
{

  cout << "PaletteItem" << endl;
}

int
CyrilPaletteItem::size()
{
  return 4;
}

void
CyrilPaletteItem::eval(CyrilState& _s)
{
  if (!paletteCalc) {
    e->eval(_s);
    b = _s.stk->top();
    _s.stk->pop();
    g = _s.stk->top();
    _s.stk->pop();
    r = _s.stk->top();
    _s.stk->pop();
    paletteCalc = true;
  }
  _s.stk->push(r);
  _s.stk->push(g);
  _s.stk->push(b);
  _s.stk->push(d);
}
