#ifndef ENEMYASSAULT_H
#define ENEMYASSAULT_H

#include "Game.h"

class Enemy {
private:
  static void init(Process *me, Object *o);
  static void respawn(Process *me, Object *o);

public:
  static void entry(Process *me, Object *o);

private:
  static void wait_init(Process *me, Object *o);
  static void explode(Process *me, Object *o);
  static void orbit(Process *me, Object *o);
  static void seek(Process *me, Object *o);
  static void run_away(Process *me, Object *o);
  static void evade(Process *me, Object *o);
};

#endif
