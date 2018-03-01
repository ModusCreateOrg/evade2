#ifndef GAME_H
#define GAME_H

#include "Evade2.h"

class Game {
public:
  static UBYTE wave; // wave #
  // game difficulty
  static UBYTE difficulty;
  static UBYTE kills;

public:
  // run each game loop
  static void run();

public:
  // initial state
  static void entry(Process *me, Object *o);
  static void next_wave(Process *me, Object *o);

public:
  static void birth();

private:
  // states
  static void get_ready(Process *me, Object *o);
  static void spawn_boss(Process *me, Object *o);

private:
  // methods
  static void start_game(Process *me);
};

#endif
