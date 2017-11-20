#ifndef STARFIELD_H
#define STARFIELD_H

#include "Game.h"

class Starfield {
  WORD starX[NUM_STARS], startY[NUM_STARS];

public:
  void init();
  void render(WORD x, WORD Y, WORD z);
};

#endif
