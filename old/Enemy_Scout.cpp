#define DEBUGME
//#undef DEBUGME

#include "Game.h"

#include "img/enemy_scout_1_img.h"
#include "img/enemy_scout_2_img.h"

/**
 * Initialize the figther Object's position and velocity.
 *
 * The Object is initialized near the camera position in x and y so it will appear
 * right away.
 */
void Enemy_Scout::init(Object *o) {
  o->state = FIRE_TIME;

  o->z = Camera::z - 128;
  o->x = Camera::x + (random(0, 128) - 64);
  o->y = Camera::y + (random(0, 128) - 64);

  o->vx = o->vy = 0;
  o->vz = CAMERA_VZ + 4;
  o->flags |= OFLAG_ENEMY;
  o->flags &= ~OFLAG_EXPLODE;
}

/**
 * Explosion takes place over NUM_FRAMES frames (frame = game loop)
 */
void Enemy_Scout::explode(Process *me) {
  Object *o = me->o;

  o->flags &= ~OFLAG_COLLISION;
  o->flags |= OFLAG_EXPLODE;
  if (clipped(o) || o->state > NUM_FRAMES) {
    Enemy_Scout::init(o);
    me->sleep(1, Enemy_Scout::patrol);
  }
  else {
    // o->theta += 1;
    o->state++;
  }
  me->sleep(1);
}

void Enemy_Scout::evade(Process *me) {
  Object *o = me->o;

  if (o->z - Camera::z > 1024 + 512) {
    init(o);
    me->sleep(1, patrol);
    return;
  }
  if (collide(o)) {
    Player::add_score(0x10);
    me->sleep(1, Enemy_Scout::explode);
    return;
  }
  o->vz++;
  o->vx += o->vx * .1;
  o->vy += o->vy * .1;
  bank(o);
  me->sleep(1);
}

void Enemy_Scout::patrol(Process *me) {
  Object *o = me->o;

  if (clipped(o)) {
    // behind camera, keep flying
    return;
  }
  if (o->z - Camera::z > 256) {
    o->vx = random(0, 16) - 8;
    o->vy = random(0, 16) - 8;
    me->sleep(1, evade);
    return;
  }
  fire(o);
  bank(o);
  if (collide(o)) {
    Player::add_score(0x10);
    me->sleep(1, Enemy_Scout::explode);
    return;
  }
  me->sleep(1);
}

/*
 * enemy_scout_process
 *
 * Initial state/entry point for the Enemy Scout Process.
 *
 * Allocates an Object and sets its image (lines).
 */
void Enemy_Scout::enemy_scout_process(Process *me) {
  Object *o = ObjectManager::alloc();
  me->o = o;
  o->lines = enemy_scout_1_img;
  init(o);
  me->sleep(1, Enemy_Scout::patrol); // next frame we resume running the wait() state.
}
