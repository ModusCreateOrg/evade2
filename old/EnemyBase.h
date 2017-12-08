#ifndef ENEMYBASE_H
#define ENEMYBASE_H

#include "Game.h"

#define FIRE_TIME (60 + random(1, 60))

#define OFLAG_BANK_LEFT (1 << OFLAG_USER_BIT)

#define DELTA_THETA 8

class EnemyBase {
protected:
  // return true if enemy behind the camera
  static BOOL clipped(Object *o);
  // return true if enemy collided with player/bullet
  // initializes object for explosion
  static BOOL collide(Object *o);
  // bank object left/right depending on OFLAG_BANK_LEFT, up to max of delta degrees
  static void bank(Object *o, WORD delta = 45);
  // barrel roll Object, based upon OFLAG_BANK_LEFT
  static void roll(Object *o);
  // maybe fire at player, based upon fire timer in o->state
  static void fire(Object *o, BYTE type);
};

#endif
