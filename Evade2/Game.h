#ifndef GAME_H
#define GAME_H

#include "Evade2.h"

class Game {
public:
  // game difficulty
  static UBYTE difficulty;

public:
  // initial state
  static void entry(Process *me, Object *o);

private:
  // states
  static void get_ready(Process *me, Object *o);

private:
  // methods
  static void start_game(Process *me);
};

#endif
