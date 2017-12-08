#ifndef ENEMY_HEAVY_BOMBER_H
#define ENEMY_HEAVY_BOMBER_H

#include "Game.h"
/**
 * Enemy_Scout process.
 *
 * We only expose the initial state/function as extern here, so it can be ProcessManager::birth()
 * from anywhere.
 *
 * The remaining states are static/local to the Enemy_Scout.cpp file.
 */
class Enemy_Heavy_Bomber : public EnemyBase {
  // how long explosion lasts (in game loops)
  static const BYTE NUM_FRAMES = 48;

public:
  static void enemy_heavy_bomber_process(Process *me);

private:
  static void patrol(Process *me);
  static void seek(Process *me);
  static void attack(Process *me);
  static void explode(Process *me);

private:
  // initialize/respawn the enemy object
  static void init(Object *o);
};

#endif
