#ifndef BOSS_H
#define BOSS_H

#include "Evade2.h"

class Boss {
public:
  static uint16_t hit_points;
  static UBYTE boss_type;
  static void entry(Process *me, Object *o);
  static void explode(Process *me, Object *o);
private:
  static void start_action(Process *me, Object *o);
  static void action(Process *me, Object *o);
};

#endif
