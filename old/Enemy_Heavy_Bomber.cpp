#define DEBUGME
//#undef DEBUGME
#include "Game.h"

#include "img/enemy_heavy_bomber_1_img.h"
#include "img/enemy_heavy_bomber_2_img.h"

/**
 * Initialize the figther Object's position and velocity.
 *
 * The Object is initialized near the camera position in x and y so it will appear
 * right away.
 */
void Enemy_Heavy_Bomber::init(Object *o) {
  o->state = -1;
  WORD zz = random(256, 512),
       w = 128 + zz * 2;

  o->z = Camera::z + zz + 512;
  o->x = w / 2 - random(0, w) + Camera::x;
  o->y = w / 2 - random(0, w) + Camera::y;
  o->vz = -CAMERA_VZ / 4;
  o->flags |= OFLAG_ENEMY;
  o->flags &= ~OFLAG_EXPLODE;
}

/**
 * Explosion takes place over NUM_FRAMES frames (frame = game loop)
 */
void Enemy_Heavy_Bomber::explode(Process *me) {
  Object *o = me->o;

  o->flags &= ~OFLAG_COLLISION;
  o->flags |= OFLAG_EXPLODE;
  if (clipped(o) || o->state > NUM_FRAMES) {
    Enemy_Heavy_Bomber::init(o);
    me->sleep(1, Enemy_Heavy_Bomber::patrol);
  }
  else {
    o->theta += 1;
    o->state++;
  }
  me->sleep(1);
}

void Enemy_Heavy_Bomber::attack(Process *me) {
  Object *o = me->o;
  o->vz = CAMERA_VZ;
  o->vx = 0;
  o->vy = 0;
  if (clipped(o)) {
    init(o);
    me->sleep(1, Enemy_Heavy_Bomber::patrol);
    return;
  }
  bank(o, 30);
  if (collide(o)) {
    Player::add_score(0x05);
    me->sleep(1, Enemy_Heavy_Bomber::explode);
    return;
  }
  fire(o);
  me->sleep(1);
}

#define SEEK_DISTANCE 256
void Enemy_Heavy_Bomber::seek(Process *me) {
  Object *o = me->o;
  if (clipped(o)) {
    init(o);
    return;
  }
  if (collide(o)) {
    Player::add_score(0x05);
    me->sleep(1, Enemy_Heavy_Bomber::explode);
    return;
  }
  if ((o->z - Camera::z) <= SEEK_DISTANCE) {
    o->state = FIRE_TIME;
    me->sleep(1, attack);
  }
  else {
    FLOAT dx = Camera::x - o->x,
          dy = Camera::y - o->y;

    o->vz = -CAMERA_VZ / SEEK_DISTANCE;
    o->vx = dx / SEEK_DISTANCE;
    o->vy = dy / SEEK_DISTANCE;
    if (dx >= 0) {
      o->flags |= OFLAG_BANK_LEFT;
    }
    else {
      o->flags &= ~OFLAG_BANK_LEFT;
    }
    if (o->theta > -45 && o->theta < 45) {
      bank(o);
    }
    else {
      roll(o);
    }
    me->sleep(1);
  }
}

void Enemy_Heavy_Bomber::patrol(Process *me) {
  Object *o = me->o;

  if (clipped(o)) {
    init(o);
    return;
  }
  bank(o);
  if (collide(o)) {
    Player::add_score(0x05);
    me->sleep(1, Enemy_Heavy_Bomber::explode);
    return;
  }
  if ((o->z - Camera::z) < 512) {
    me->sleep(1, Enemy_Heavy_Bomber::seek);
  }
  me->sleep(1);
}

/*
 * fighter1_process
 *
 * Initial state/entry point for the Enemy_Heavy_Bomber Process.
 *
 * Allocates an Object and sets its image (lines).
 */
void Enemy_Heavy_Bomber::enemy_heavy_bomber_process(Process *me) {
  Object *o = ObjectManager::alloc();
  me->o = o;
  o->lines = enemy_heavy_bomber_1_img;
  init(o);
  me->sleep(1, Enemy_Heavy_Bomber::patrol); // next frame we resume running the wait() state.
}
