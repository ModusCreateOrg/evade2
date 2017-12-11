#ifndef STARFIELD_H
#define STARFIELD_H

#include "Game.h"

class Starfield {
  static WORD starX[NUM_STARS], starY[NUM_STARS];
  static FLOAT starZ[NUM_STARS];

protected:
  static void initStar(int i);

public:
  static void init();
  static void render();
};

#endif
