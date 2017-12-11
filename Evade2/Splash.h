#ifndef SPLASH_H
#define SPLASH_H

#include "Evade2.h"

class Splash {
private:
  // states
  static void wait(Process *me, Object *o);

public:
  // initial state
  static void entry(Process *me, Object *o);
};

#endif
