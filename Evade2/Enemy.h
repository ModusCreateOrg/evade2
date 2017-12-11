#ifndef ENEMY_H
#define ENEMY_H

#include "Evade2.h"

class Enemy {
private:
  static void init(Process *me, Object *o);
  static void respawn(Process *me, Object *o);

public:
  static void entry(Process *me, Object *o);
  static const BYTE *enemy_graphic(BYTE n); // one of ENEMY_ defines below

private:
  static void wait_init(Process *me, Object *o);
  static void explode(Process *me, Object *o);
  static void orbit(Process *me, Object *o);
  static void seek(Process *me, Object *o);
  static void run_away(Process *me, Object *o);
  static void evade(Process *me, Object *o);
};

#define ENEMY_ASSAULT 0
#define ENEMY_BOMBER 1
#define ENEMY_SCOUT 2

#endif
