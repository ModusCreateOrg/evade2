#define DEBUGME
#include "Game.h"

#include "img/fighter1_img.h"

static void bankLeft(Process *me);
static void bankRight(Process *me);

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
  o->step = -1;
  //  o->x = Camera::x; // 64 - (COORD)random(0, 128) + Camera::x;
  //  o->y = Camera::y; // 32 - (COORD)random(0, 64) + Camera::y;
  //  o->z = Camera::z; // (COORD)random(200, 255);
  //  o->vz = CAMERA_VZ * 2;
  WORD zz = random(256, 512),
       w = 128 + zz * 2;
  o->z = Camera::z + zz + 512;
  o->x = w / 2 - random(0, w) + Camera::x;
  o->y = w / 2 - random(0, w) + Camera::y;
  o->vz = -CAMERA_VZ / 4;
  o->flags |= OFLAG_ENEMY;
}

static BOOL clipped(Object *o) {
  return (o->z < Camera::z);
}

static BOOL collide(Object *o) {
  if (o->flags & OFLAG_COLLISION) {
    o->step = 0;
    o->flags &= ~OFLAG_COLLISION;
    return TRUE;
  }
  return false;
}

/**
 * Explosion takes place over NUM_FRAMES frames (frame = game loop)
 */
static const BYTE NUM_FRAMES = 48;
static void explode(Process *me) {
  Object *o = me->o;

  o->flags &= ~OFLAG_COLLISION;
  if (clipped(o) || o->step > NUM_FRAMES) {
    init(o);
    me->sleep(1, bankLeft);
  }
  else {
    o->theta += 1;
    o->step++;
  }
  me->sleep(1);
}

static void bankLeft(Process *me) {
  Object *o = me->o;

  if (clipped(o)) {
    init(o);
  }
  else if (collide(o)) {
    me->sleep(1, explode);
  }
  else {
    o->theta -= 4;
    if (o->theta < -45) {
      me->sleep(1, bankRight);
    }
    else {
      me->sleep(1);
    }
  }
}

static void bankRight(Process *me) {
  Object *o = me->o;

  if (clipped(o)) {
    init(o);
  }
  else if (collide(o)) {
    me->sleep(1, explode);
  }
  else {
    o->theta += 4;
    if (o->theta > 45) {
      me->sleep(1, bankLeft);
    }
    else {
      me->sleep(1);
    }
  }
}

/*
 * fighter1_process
 *
 * Initial state/entry point for the Fighter1 Process.
 *
 * Allocates an Object and sets its image (lines).
 */
void fighter1_process(Process *me) {
  Object *o = ObjectManager::alloc();
  me->o = o;
  o->lines = fighter1_img;
  init(o);
  me->sleep(1, bankLeft); // next frame we resume running the wait() state.
}
