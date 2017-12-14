#ifndef EBULLET_H
#define EBULLET_H

#include "Process.h"

#define EBULLET_BULLET 1
#define EBULLET_BOMB 2

class EBullet {
public:
  // fire an enemy bullet at the player from the enemy Object o.
  // returns false if bullet not fired (no free Objects)
  static BOOL fire(Object *o, BYTE type);
  static void run();
  static void genocide();

public:
  static const BYTE *bullet_img();
  static const BYTE *bomb_img();
};

#endif
