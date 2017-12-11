#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "Process.h"

class GameOver {
public:
  static void entry(Process *me, Object *o);

protected:
  static void loop(Process *me, Object *o);
};

#endif
