#define DEBUGME
#include "Game.h"

#include "img/fighter1_img.h"

#define DELTA_THETA 8
/**
 * Initialize the figther Object's position and velocity.
 *
 * The Object is initialized near the camera position in x and y so it will appear
 * right away.
 */
void Fighter1::init(Object *o) {
  o->state = -1;
  WORD zz = random(256, 512),
       w = 128 + zz * 2;

  o->z = Camera::z + zz + 512;
  o->x = w / 2 - random(0, w) + Camera::x;
  o->y = w / 2 - random(0, w) + Camera::y;
  o->vz = -CAMERA_VZ / 4;
  o->state = DELTA_THETA;
  o->flags |= OFLAG_ENEMY;
  o->flags &= ~OFLAG_EXPLODE;
}

static BOOL clipped(Object *o) {
  return (o->z < Camera::z);
}

static BOOL collide(Object *o) {
  if (o->flags & OFLAG_COLLISION) {
    o->state = 0;
    o->flags &= ~OFLAG_COLLISION;
    return TRUE;
  }
  return false;
}

/**
 * Explosion takes place over NUM_FRAMES frames (frame = game loop)
 */
void Fighter1::explode(Process *me) {
  Object *o = me->o;

  o->flags &= ~OFLAG_COLLISION;
  o->flags |= OFLAG_EXPLODE;
  if (clipped(o) || o->state > NUM_FRAMES) {
    Fighter1::init(o);
    me->sleep(1, Fighter1::patrol);
  }
  else {
    o->theta += 1;
    o->state++;
  }
  me->sleep(1);
}

static void bank(Object *o) {
  if (o->state < 0) {
    if (o->theta < -45) {
      o->state = DELTA_THETA;
    }
  }
  else {
    if (o->theta > 45) {
      o->state = -DELTA_THETA;
    }
  }
  o->theta += o->state;
}

static void roll(Object *o) {
  o->theta += o->state;
}

void Fighter1::attack(Process *me) {
  Object *o = me->o;
  o->vz = CAMERA_VZ;
  o->vx = 0;
  o->vy = 0;
  if (clipped(o)) {
    init(o);
    me->sleep(1, Fighter1::patrol);
    return;
  }
  bank(o);
  if (collide(o)) {
    me->sleep(1, Fighter1::explode);
    return;
  }
  me->sleep(1);
}

#define SEEK_DISTANCE 128
void Fighter1::seek(Process *me) {
  Object *o = me->o;
  if (clipped(o)) {
    init(o);
    return;
  }
  if (collide(o)) {
    me->sleep(1, Fighter1::explode);
    return;
  }
  if ((o->z - Camera::z) <= SEEK_DISTANCE) {
    me->sleep(1, attack);
  }
  else {
    WORD dx = Camera::x - o->x,
         dy = Camera::y - o->y;

    if (abs(dx) > 16) {
      o->vz = -CAMERA_VZ / 4;
      o->vx = dx / 64;
    }
    else {
      o->vx = 0;
    }
    if (abs(dy) > 16) {
      o->vy = dy / 64;
      o->vz = -CAMERA_VZ / 4;
    }
    else {
      o->vy = 0;
    }
    if (o->vx == 0 && o->vy == 0) {
      bank(o);
    }
    else {
      roll(o);
    }
    me->sleep(1);
  }
}
void Fighter1::patrol(Process *me) {
  Object *o = me->o;

  if (clipped(o)) {
    init(o);
    return;
  }
  bank(o);
  if (collide(o)) {
    me->sleep(1, Fighter1::explode);
    return;
  }
  if ((o->z - Camera::z) < 512) {
    me->sleep(1, Fighter1::seek);
  }
  me->sleep(1);
}

/*
 * fighter1_process
 *
 * Initial state/entry point for the Fighter1 Process.
 *
 * Allocates an Object and sets its image (lines).
 */
void Fighter1::fighter1_process(Process *me) {
  Object *o = ObjectManager::alloc();
  me->o = o;
  o->lines = fighter1_img;
  init(o);
  me->sleep(1, Fighter1::patrol); // next frame we resume running the wait() state.
}
