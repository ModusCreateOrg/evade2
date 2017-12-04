#ifndef ENEMY_SCOUT_H
#define ENEMY_SCOUT_H

#include "Game.h"

/**
 * Enemy_Scout process.
 *
 * We only expose the initial state/function as extern here, so it can be ProcessManager::birth()
 * from anywhere.
 *
 * The remaining states are static/local to the Enemy_Scout.cpp file.
 */
class Enemy_Scout : public EnemyBase {
  // how long explosion lasts (in game loops)
  static const BYTE NUM_FRAMES = 48;

public:
  static void enemy_scout_process(Process *me);

private:
  static void evade(Process *me);
  static void patrol(Process *me);
  static void explode(Process *me);

private:
  // initialize/respawn the enemy object
  static void init(Object *o);
};

#endif
