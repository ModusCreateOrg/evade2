#ifndef STARFIELD_H
#define STARFIELD_H

#include "Game.h"

class Starfield {
  WORD starX[NUM_STARS], starY[NUM_STARS], starZ[NUM_STARS];

protected:
  void initStar(int i);

public:
  void init();
  void render();
};

extern Starfield starfield;

#endif
