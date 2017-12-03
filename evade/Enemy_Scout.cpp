#define DEBUGME
#include "Game.h"

#include "img/enemy_scout_img.h"

#define OFLAG_BANK_LEFT (1 << OFLAG_USER_BIT)

#define DELTA_THETA 8
/**
 * Initialize the figther Object's position and velocity.
 *
 * The Object is initialized near the camera position in x and y so it will appear
 * right away.
 */
void Enemy_Scout::init(Object *o) {
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
void Enemy_Scout::explode(Process *me) {
  Object *o = me->o;

  o->flags &= ~OFLAG_COLLISION;
  o->flags |= OFLAG_EXPLODE;
  if (clipped(o) || o->state > NUM_FRAMES) {
    Enemy_Scout::init(o);
    me->sleep(1, Enemy_Scout::patrol);
  }
  else {
    o->theta += 1;
    o->state++;
  }
  me->sleep(1);
}

static void bank(Object *o, WORD delta = 45) {
  if (o->flags & OFLAG_BANK_LEFT) {
    o->theta -= DELTA_THETA;
    if (o->theta < -delta) {
      o->flags &= ~OFLAG_BANK_LEFT;
    }
  }
  else {
    o->theta += DELTA_THETA;
    if (o->theta > delta) {
      o->flags |= OFLAG_BANK_LEFT;
    }
  }
}

static void roll(Object *o) {
  if (o->flags & OFLAG_BANK_LEFT) {
    o->theta -= DELTA_THETA;
  }
  else {
    o->theta += DELTA_THETA;
  }
}

static void fire(Object *o) {
  o->state--;
  if (o->state <= 0) {
    // fire!
    Process *p = ProcessManager::birth(EBullet::ebullet_process);
    if (p) {
      Object *bullet = ObjectManager::alloc();
      bullet->x = o->x - 8;
      bullet->y = o->y - 16; //  - 32;
      bullet->z = o->z;
      p->o = bullet;
    }
    o->state = 120;
  }
  else {
    o->state--;
  }
}
void Enemy_Scout::attack(Process *me) {
  Object *o = me->o;
  o->vz = CAMERA_VZ;
  o->vx = 0;
  o->vy = 0;
  if (clipped(o)) {
    init(o);
    me->sleep(1, Enemy_Scout::patrol);
    return;
  }
  bank(o, 30);
  if (collide(o)) {
    me->sleep(1, Enemy_Scout::explode);
    return;
  }
  fire(o);
  me->sleep(1);
}

#define SEEK_DISTANCE 256
void Enemy_Scout::seek(Process *me) {
  Object *o = me->o;
  if (clipped(o)) {
    init(o);
    return;
  }
  if (collide(o)) {
    me->sleep(1, Enemy_Scout::explode);
    return;
  }
  if ((o->z - Camera::z) <= SEEK_DISTANCE) {
    o->state = 60;
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

void Enemy_Scout::patrol(Process *me) {
  Object *o = me->o;

  if (clipped(o)) {
    init(o);
    return;
  }
  bank(o);
  if (collide(o)) {
    me->sleep(1, Enemy_Scout::explode);
    return;
  }
  if ((o->z - Camera::z) < 512) {
    me->sleep(1, Enemy_Scout::seek);
  }
  me->sleep(1);
}

/*
 * fighter1_process
 *
 * Initial state/entry point for the Enemy_Scout Process.
 *
 * Allocates an Object and sets its image (lines).
 */
void Enemy_Scout::enemy_scout_process(Process *me) {
  Object *o = ObjectManager::alloc();
  me->o = o;
  o->lines = enemy_scout_img;
  init(o);
  me->sleep(1, Enemy_Scout::patrol); // next frame we resume running the wait() state.
}
