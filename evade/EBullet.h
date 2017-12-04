#ifndef EBULLET_H
#define EBULLET_H

#include "Process.h"

class EBullet {
public:
  // fire an enemy bullet at the player from the enemy Object o.
  // returns false if bullet not fired (no free Objects)
  static BOOL fire(Object *o);
  static void run();
};

#endif
