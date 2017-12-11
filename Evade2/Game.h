#ifndef GAME_H
#define GAME_H

#include "Evade2.h"

class Game {
public:
  static void entry(Process *me, Object *o);

private:
  static void get_ready(Process *me, Object *o);

private:
  static void start_game(Process *me);
};

#endif
