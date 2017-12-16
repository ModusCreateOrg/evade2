#ifndef ASTEROID_H
#define ASTEROID_H

/**
 * Monitor asteroids and kick some out from the asteroid belt once in a while.
 */
#include "Evade2.h"

class Asteroid {
public:
  static void entry(Process *p, Object *o);

private:
  static void loop(Process *p, Object *o);
  static void delay(Process *p, Object *o);

private:
  static void respawn(Process *p, Object *o);
};
#endif
