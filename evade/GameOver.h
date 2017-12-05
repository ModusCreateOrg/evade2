#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "Process.h"

class GameOver {
public:
  static void process(Process *me);

protected:
  static void loop(Process *me);
};

#endif
