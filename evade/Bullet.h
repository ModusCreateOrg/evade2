#ifndef BULLET_H
#define BULLET_H

// bullet process entrypoint
#include "Process.h"

class Bullet {
public:
  /**
   * fire is called to fire a player bullet.
   */
  static void fire(BYTE deltaX, BYTE deltaY);
  /*
   * run is called to run all the bullet logic.
   */
  static void run();
  /*
   * remove all bullet objects
   */
  static void genocide();
};

#endif
