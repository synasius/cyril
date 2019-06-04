#pragma once

//  Created by Darren Mothersele on 05/11/2013.

#include <ofMain.h>

#include "Cyril.h"
#include "CyrilAssign.h"
#include "CyrilBinaryOp.h"
#include "CyrilDo.h"
#include "CyrilFor.h"
#include "CyrilFun.h"
#include "CyrilHexColor.h"
#include "CyrilIf.h"
#include "CyrilList.h"
#include "CyrilLoad.h"
#include "CyrilOp.h"
#include "CyrilParticle.h"
#include "CyrilPush.h"
#include "CyrilUnaryOp.h"
#include "CyrilWhile.h"

class CyrilParser
{
public:
  static Cyril* parseString(string progStr);
  static Cyril* parseFile(string fileName);
};

