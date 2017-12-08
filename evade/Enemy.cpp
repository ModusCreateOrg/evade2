#define DEBUGME

#include "Game.h"

#include "img/enemy_assault_1_img.h"
#include "img/enemy_assault_2_img.h"
#include "img/enemy_heavy_bomber_1_img.h"
#include "img/enemy_heavy_bomber_2_img.h"
#include "img/enemy_scout_1_img.h"
#include "img/enemy_scout_2_img.h"

#define BANK_LEFT (1 << OFLAG_USER_BIT)
#define ORBIT_LEFT (1 << (OFLAG_USER_BIT + 1))

/******************************************************************************************
 *** Helpers
 *****************************************************************************************/

static BOOL behind_camera(Object *o) {
  return o->z <= Camera::z;
}

/**
 * Check to see if Object collided with player bullet and set up
 * Object to explode if so.
 *
 * Returns TRUE if Object collided.
 */
static BOOL death(Object *o) {
  if (o->flags & OFLAG_COLLISION) {
    o->flags &= OFLAG_EXPLODE;
    o->state = 0;
    o->vz = Camera::vz;
    return TRUE;
  }
  return FALSE;
}

// TODO: fire time based upon enemy type and difficulty
#define FIRE_TIME (60 + random(1, 60))
void fire(Object *o) {
  o->timer--;
  if (o->timer <= 0) {
    if (Camera::vx || Camera::vy) {
      o->timer = 1;
      return;
    }
    // fire!
    if (EBullet::fire(o)) {
      o->timer = FIRE_TIME;
    }
    else {
      // try again next frame
      o->timer = 1;
    }
  }
  else {
    o->timer--;
  }
}

#define DELTA_THETA 8
static void bank(Object *o, WORD delta = 45) {
  if (o->flags & BANK_LEFT) {
    o->theta -= DELTA_THETA;
    if (o->theta < -delta) {
      o->flags &= ~BANK_LEFT;
    }
  }
  else {
    o->theta += DELTA_THETA;
    if (o->theta > delta) {
      o->flags |= BANK_LEFT;
    }
  }
}
/**
 * Initialize Object for assault enemy
 */
static void init_assault(Object *o, BOOL left) {
  FLOAT angle = left ? 0 : (2 * PI);
  o->z = cos(angle) * 256;
  o->z = Camera::z + sin(angle) * 256;
  o->y = Camera::y; //  + 64 - random(0, 128);
  o->vx = o->vy = o->vz = 0;
  o->state = 0;
}

/**
 * Initialize object for scout enemy
 */
static void init_scout(Object *o) {
  o->x = Camera::x + 64 - random(0, 127);
  o->y = Camera::y + 64 - random(0, 127);
  o->z = Camera::z + 1024;
  o->vz = CAMERA_VZ - 3;
  o->vx = o->vy = 0;
}

/**
 * Initialize object for bomber enemy
 */
static void init_bomber(Object *o) {
  o->x = Camera::x + 128 - random(0, 127);
  o->y = Camera::y + 128 - random(0, 127);
  o->z = Camera::z - 10;
  o->vz = CAMERA_VZ + 2;
  o->vx = o->vy = 0;
}

/**
 * Initialize enemy:
 *
 * 1. Choose random type
 * 2. Set lines/image based upon type
 * 3. Set initial state based upon type
 */
void Enemy::init(Process *me, Object *o) {
  o->flags &= ~OFLAG_EXPLODE;
  o->flags &= ~OFLAG_COLLISION;
  o->flags |= OFLAG_ENEMY;
  o->timer = FIRE_TIME;
  o->theta = 0;
  switch (random(0, 5)) {
    case 0:
      o->lines = enemy_assault_1_img;
      init_assault(o, TRUE);
      me->sleep(1, orbit);
      break;
    case 1:
      o->lines = enemy_assault_2_img;
      init_assault(o, FALSE);
      me->sleep(1, orbit);
      break;
    case 2:
      o->lines = enemy_heavy_bomber_1_img;
      init_bomber(o);
      me->sleep(1, evade);
      break;
    case 3:
      o->lines = enemy_heavy_bomber_2_img;
      init_bomber(o);
      me->sleep(1, evade);
      break;
    case 4:
      o->lines = enemy_scout_1_img;
      init_scout(o);
      me->sleep(1, orbit);
      break;
    case 5:
      o->lines = enemy_scout_2_img;
      init_scout(o);
      me->sleep(1, orbit);
      break;
  }
}

/**
 * This state simply waits for timer to hit 0 and then
 * calls init().  This is to delay respawning the
 * enemy (random delay).
 */
void Enemy::wait_init(Process *me, Object *o) {
  if (o->timer < 0) {
    init(me, o);
  }
  o->timer--;
  me->sleep(1);
}

/**
 * Called to respawn the enemy.  It sets timer to a random
 * number and then puts the Process into wait_init state.
 */
void Enemy::respawn(Process *me, Object *o) {
  o->timer = random(0, 40) + 20;
  me->sleep(1, Enemy::wait_init);
}

/******************************************************************************************
 *** Process/AI States
 *****************************************************************************************/

/**
 * Enemy is exploding state.
 */
void Enemy::explode(Process *me, Object *o) {
  const WORD NUM_FRAMES = 58;
  o->flags |= OFLAG_EXPLODE;
  o->state++;
  if (behind_camera(o) || o->state > NUM_FRAMES) {
    respawn(me, o);
  }
  else {
    me->sleep(1, explode);
  }
}

/*
 * Enemy is flying away to exit.
 */
void Enemy::run_away(Process *me, Object *o) {
  o->vz += o->state;
  o->vx += o->vx > 0 ? .1 : -.1;
  o->vy += o->vy > 0 ? .1 : -.1;
  if (behind_camera(o) || (o->z - Camera::z) > 1024) {
    respawn(me, o);
    return;
  }
  if (death(o)) {
    me->sleep(1, explode);
    return;
  }
  bank(o);
  fire(o);
  me->sleep(1);
}

void Enemy::evade(Process *me, Object *o) {
  if (o->z - Camera::z > 512) {
    o->state = 1;
    me->sleep(1, run_away);
    return;
  }
  if (death(o)) {
    me->sleep(1, explode);
    return;
  }
  bank(o, 15);
  fire(o);
  me->sleep(1);
}

void Enemy::seek(Process *me, Object *o) {
  if (behind_camera(o)) {
    respawn(me, o);
    return;
  }
  if (death(o)) {
    me->sleep(1, explode);
    return;
  }
  bank(o);
  fire(o);
  if (o->z - Camera::z < 256) {
    o->state = -1;
    me->sleep(1, run_away);
    return;
  }
  o->vx = Camera::x + (64 - random(0, 128)) > o->x ? 4 : -4;
  o->vy = Camera::y + (64 - random(0, 128)) > o->y ? 4 : -4;
  me->sleep(1);
}

void Enemy::orbit(Process *me, Object *o) {
  if (death(o)) {
    me->sleep(1, explode);
    return;
  }
  fire(o);

  if (o->flags & ORBIT_LEFT) {
    o->state--;
    if (o->state < 0) {
      o->state = 0;
      o->flags &= ~ORBIT_LEFT;
    }
    else {
      o->theta -= 8;
    }
  }
  else {
    o->state++;
    if (o->state > 180) {
      o->state = 180;
      o->flags |= ORBIT_LEFT;
    }
    else {
      o->theta += 8;
    }
  }

  FLOAT rad = RADIANS(o->state);
  o->vy = (Camera::y > o->y) ? -2 : 2;
  o->y = Camera::y;
  o->x = cos(rad) * 256;
  o->z = Camera::z + sin(rad) * 256;

  me->sleep(1);
}

#if 0
static void implode(Process *me) {
  Object *o = me->o;

  o->state--;
  if (o->state < 0) {
    o->vz = 0;
    o->flags &= ~OFLAG_EXPLODE;
    o->flags |= OFLAG_ENEMY;
    o->state = 0;
    me->sleep(1, orbit);
    return;
  }
  o->vz = Camera::vz;
  me->sleep(1, implode);
}
#endif

void Enemy::entry(Process *me, Object *o) {
  o = ObjectManager::alloc();
  me->o = o;
  respawn(me, o);
}
