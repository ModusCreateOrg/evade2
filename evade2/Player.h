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
  static void init();
  static void hit(BYTE amount);
  static void add_score(BCD amount);
  // this is called before rendering everything
  static void before_render();
  // this is called after rendering everything, so HUD can be rendered, etc.
  static void after_render();
  static void render_score();
};

#endif
