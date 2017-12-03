#ifndef PLAYER_H
#define PLAYER_H

#include "Process.h"

// player hit by enemy bullet
#define PLAYER_FLAG_HIT (1 << 0)

class Player {
public:
  static BYTE power;
  static BYTE life;
  static BYTE num_bullets;
  static BCD score;
  static UBYTE flags;

public:
  static void init(Process *p);
  static void player_process(Process *p);
  // this is called after rendering everything, so HUD can be rendered, etc.
  static void after_render();

private:
  // states
  static void loop(Process *p);
};

#endif
