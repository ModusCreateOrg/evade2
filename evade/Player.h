#ifndef PLAYER_H
#define PLAYER_H

#include "Process.h"

class Player {
public:
  static BYTE power;
  static BYTE life;
  static BCD score;

public:
  static void player_process(Process *p);
  // this is called after rendering everything, so HUD can be rendered, etc.
  static void after_render();

private:
  // states
  static void loop(Process *p);
};

#endif
