#ifndef FIGHTER1_H
#define FIGHTER1_H

#include "Process.h"
/**
 * Fighter1 process.
 *
 * We only expose the initial state/function as extern here, so it can be ProcessManager::birth()
 * from anywhere.
 *
 * The remaining states are static/local to the Fighter1.cpp file.
 */
class Fighter1 {
  // how long explosion lasts (in game loops)
  static const BYTE NUM_FRAMES = 48;

public:
  static void fighter1_process(Process *me);

private:
  static void bankLeft(Process *me);
  static void bankRight(Process *me);
  static void explode(Process *me);

private:
  // initialize/respawn the enemy object
  static void init(Object *o);
};

#endif
