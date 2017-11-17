#ifndef _STAR_H_
#define _STAR_H_

#include "Arduino.h"

/**
 * Class that represents a single star on the screen.
 */
class Star {
public:
  void randomize(int xMin, int xMax, int yMin, int yMax, int zMin, int zMax,
                 int speedMin, int speedMax);
  void update(int travel);
  float x, y, z;
  int screen_x, screen_y, old_screen_x, old_screen_y, speed;
};

#endif
