#include "Game.h"


/**
 * Initialize the figther Object's position and velocity.
 *
 * For demonstration purposes, the Fighter only moves in Z, and faster than
 * the camera so it will shrink as it goes into the distance.
 *
 * The Object is initialized right at the camera position so it will appear
 * right away.
 */
static void init(Object *o) {
  o->x = Camera::x; // 64 - (COORD)random(0, 128) + Camera::x;
  o->y = Camera::y; // 32 - (COORD)random(0, 64) + Camera::y;
  o->z = Camera::z; // (COORD)random(200, 255);
  o->vz = 6;
}

/**
 * Wait until the Object's Z is far into the distance.
 *
 * Then we re-initialize the Object.
 */
static void wait(Process *me) {
  Object *o = me->o;

  if (o->z > (Camera::z + 1024)) {
    init(o);
  }
  me->sleep(1);
}

/*
 * enemy1_process
 *
 * Initial state/entry point for the enemy1 Process.
 *
 * Allocates an Object and sets its image (lines).
 */
void enemy1_process(Process *me) {
  Object *o = ObjectManager::alloc();
  me->o = o;
  o->lines = enemy1_img;
  init(o);
  me->sleep(1, wait); // next frame we resume running the wait() state.
}
