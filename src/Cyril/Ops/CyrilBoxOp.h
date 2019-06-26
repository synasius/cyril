#pragma once

//  Created by Darren Mothersele on 05/11/2013.

#include "CyrilOp.h"
#include "ofMain.h"

class CyrilBoxOp : public CyrilOp
{
public:
  CyrilBoxOp(Cyril* _c);
  CyrilBoxOp(const CyrilBoxOp& other);

  virtual ~CyrilBoxOp() override;
  virtual void print() override;
  virtual Cyril* clone() override;
  virtual int size() override;
  virtual void eval(CyrilState&) override;
};

