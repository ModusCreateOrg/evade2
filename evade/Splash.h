#ifndef SPLASH_H
#define SPLASH_H

#include "Game.h"

class Splash {
private:
  static void start_game(Process *me);
  // states
  static void wait(Process *me, Object *o);
  static void get_ready(Process *me, Object *o);
  static void settings_screen(Process *me, Object *o);

public:
  // initial state
  static void entry(Process *me, Object *o);
};

#endif
