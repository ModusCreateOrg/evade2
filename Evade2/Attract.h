#ifndef ATTRACT_H
#define ATTRACT_H

#include "Evade2.h"

class Attract {
public:
  static void entry(Process *me, Object *o);

private:
  static void typewriter(Process *me, Object *o);

private:
  static void next(Process *me, Object *o);
};

#endif
