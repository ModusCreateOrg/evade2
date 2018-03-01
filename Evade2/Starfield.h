#ifndef STARFIELD_H
#define STARFIELD_H

#include "Evade2.h"

class Starfield {
  static FXP_WORLD_COORD starX[NUM_STARS], starY[NUM_STARS];
  static FXP_WORLD_COORD starZ[NUM_STARS];

protected:
  static void initStar(int i);

public:
  static void init();
  static void render();
};

#endif
