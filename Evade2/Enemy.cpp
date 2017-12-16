#define DEBUGME

#include "Evade2.h"

#include "img/enemy_assault_1_img.h"
#include "img/enemy_heavy_bomber_1_img.h"
#include "img/enemy_scout_1_img.h"

const BYTE *Enemy::enemy_graphic(BYTE n) {
  switch (n) {
    case ENEMY_ASSAULT:
      return (const BYTE *)&enemy_assault_1_img;
    case ENEMY_BOMBER:
      return (const BYTE *)&enemy_heavy_bomber_1_img;
    default:
      return (const BYTE *)&enemy_scout_1_img;
  }
}



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
    Game::kills++;
    o->flags &= OFLAG_EXPLODE;
    o->state = 0;
    // o->vz = Camera::vz - 3;
    return TRUE;
  }
  return FALSE;
}

// TODO: fire time based upon enemy type and difficulty
#define FIRE_TIME (60 / Game::difficulty + random(1, 60 / Game::Game::difficulty))
void fire(Object *o) {
  o->timer--;
  if (o->timer <= 0) {
    if (Camera::vx || Camera::vy) {
      o->timer = 1;
      return;
    }
    // fire!

    if (EBullet::fire(o, random(0, 5) ? EBULLET_BULLET : EBULLET_BOMB)) {
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
  o->x = cos(angle) * 256;
  o->z = Camera::z + sin(angle) * 256;
  o->y = Camera::y; //  + 64 - random(0, 128);
  o->vx = o->vy = o->vz = 0;
  o->state = 0;
}

/**
 * Initialize object for scout enemy
 */
static void init_scout(Object *o) {
  o->x = Camera::x + random(-256, 256);
  o->y = Camera::y + random(-256, 256);
  o->z = Camera::z + 1024;
  o->vz = CAMERA_VZ - 12;
  o->vx = o->vy = 0;
  o->theta = random(-50, 50);
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
  o->set_type(OTYPE_ENEMY);
  o->timer = FIRE_TIME;
  o->theta = 0;

  switch (random(0, 3)) {
    case 0:
      o->lines = (const BYTE *)&enemy_assault_1_img;
      init_assault(o, random() & 1);
      me->sleep(1, orbit);
      break;
    case 1:
      o->lines = (const BYTE *)&enemy_heavy_bomber_1_img;
      init_bomber(o);
      me->sleep(1, evade);
      break;
    case 2:
      o->lines = (const BYTE *)&enemy_scout_1_img;
      init_scout(o);
      me->sleep(1, seek);
      break;
  }
}

/**
 * This state simply waits for timer to hit 0 and then
 * calls init().  This is to delay respawning the
 * enemy (random delay).
 */
void Enemy::wait_init(Process *me, Object *o) {
  if (o->timer <= 0 && game_mode == MODE_GAME) {
    init(me, o);
  }
  else {
    o->timer = 1;
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
  if (game_mode != MODE_GAME) {
    o->vz += o->state * 8;
  }
  else {
    o->vz += o->state;
  }
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
  // bank(o);
  fire(o);
  o->theta += 8;
  if (o->z - Camera::z < random(256, 512)) {
    o->state = -1;
    me->sleep(1, run_away);
    return;
  }

  me->sleep(1);
}

void Enemy::orbit(Process *me, Object *o) {
  if (death(o)) {
    me->sleep(1, explode);
    return;
  }
  fire(o);

  if (o->flags & ORBIT_LEFT) {
    o->state -= Game::difficulty;
    if (o->state < 0) {
      o->state = 0;
      o->flags &= ~ORBIT_LEFT;
    }
    else {
      o->theta -= 12;
    }
  }
  else {
    o->state += Game::difficulty;
    if (o->state > 180) {
      o->state = 180;
      o->flags |= ORBIT_LEFT;
    }
    else {
      o->theta += 12;
    }
  }

  FLOAT rad = RADIANS(o->state);
  o->vy = (Camera::y > o->y) ? -2 : 2;
  o->y = Camera::y;
  o->x = cos(rad) * 256;
  if (game_mode == MODE_GAME) {
    o->z = Camera::z + sin(rad) * 256;
  }

  me->sleep(1);
}

void Enemy::entry(Process *me, Object *o) {
  respawn(me, o);
}
