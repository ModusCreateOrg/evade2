#ifndef LOGO_H
#define LOGO_H

#include "Evade2.h"

class Logo {
public:
  static void entry(Process *me, Object *o);

private:
  static void loop(Process *me, Object *o);
};

#endif
