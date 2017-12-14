#define DEBUG_ME

#include "Enemy.h"
#include "Evade2.h"

#include "img/boss_1_img.h"
#include "img/boss_2_img.h"
#include "img/boss_3_img.h"

static const FLOAT z_dist = 256;
static const FLOAT frames = 32;
uint16_t Boss::hit_points = 0;
UBYTE Boss::boss_type;

static BOOL hit(Object *o) {
  if (o->flags & OFLAG_COLLISION) {
    Boss::hit_points--;
    o->flags &= ~OFLAG_COLLISION;
    return TRUE;
  }
  return FALSE;
}

const BYTE *getBossLines() {
  switch (Boss::boss_type) {
    case 3:
      return boss_3_img;
      break;
    case 2:
      return boss_2_img;
      break;
    default:
      return boss_1_img;
  }
}

#if 0
// Shoot from a specific X/Y space within the Boss's space.
static void fire_one(FLOAT x, FLOAT y, FLOAT z) {
  Object *o = ObjectManager::alloc();
  if (!o) {
    return;
  }
  o->set_type(OTYPE_ENEMY_BULLET);
  o->x = x;
  o->y = y;
  o->z = z;
  o->vx = ((Camera::x + 15 - random(0, 30)) - x) / frames;
  o->vy = ((Camera::y + 15 - random(0, 30)) - y) / frames;
  o->state = 384; // timeout
  o->lines = EBullet::bomb_img();
  o->vz = Camera::vz - (z - Camera::z) / 20;
}
#endif

/**
Ideas:
instead of randomizing vx, vy, you can set y to sin(theta)*64 or something like that (edited)
[18:43] and change theta over time
[18:43] it'll make it a sinusoidal pattern
*/
static void engage_player_random_xy(Object *oo) {
  oo->z = Camera::z + z_dist;

  if (--oo->timer > 0) {
    return;
  }
  oo->timer = Game::wave > 10 ? 0 : (20 - Game::wave);

  EBullet::fire(oo, EBULLET_BOMB);
  oo->vx = random(-10, 10);
  oo->vy = random(-10, 10);
}

static void init_flee(Object *o) {
  o->x = Camera::x - 512;
  o->vx = +10;
  o->y = Camera::y;
  o->z = Camera::z + z_dist;
  o->state = 0;
}

static void randomize_flee(Object *o) {
  o->y = Camera::y + random(-150, 150);
  o->vy = random(-7, 7);
  o->vx = random(-7, 7);
  o->z = Camera::z - 50;
  o->vz = Camera::vz + (random(1, 7) * Game::difficulty);
  o->theta = random(-180, 180);
}

static void engage_player_flee(Object *o) {

  if (o->flags & ORBIT_LEFT) {
    o->state -= Game::difficulty;
    if (o->state < 0) {
      o->state = 0;
      randomize_flee(o);
      o->flags &= ~ORBIT_LEFT;
    }
  }
  else {
    o->state += Game::difficulty;
    if (o->state > 120) {
      o->state = 120;

      randomize_flee(o);
      o->flags |= ORBIT_LEFT;
    }
  }

  if (--o->timer > 0) {
    return;
  }
  o->timer = Game::wave > 10 ? 0 : (20 - Game::wave);

  o->vx += random(-7, 7);
  o->vy += random(-7, 7);
}

static void engage_player_zoom(Object *oo) {
  // oo->z = Camera::z + z_dist;

  if (--oo->timer > 0) {
    return;
  }
  oo->timer = Game::wave > 10 ? 0 : (20 - Game::wave);

  EBullet::fire(oo, EBULLET_BOMB);
}

// Copy of init_ssault
static void init_orbit(Object *o, BOOL left) {
  FLOAT angle = left ? 0 : (2 * PI);
  o->x = cos(angle) * 256;
  o->z = Camera::z + sin(angle) * 256;
  o->y = Camera::y + 64 - random(0, 128);
  o->vy = random(-5, 5) + (Game::difficulty * 2);
  o->vx = 0;
  o->vz = -50 - (Game::difficulty * 2);
  o->state = left ? 0 : 180;
}

static void engage_player_orbit(Object *o) {

  if (o->flags & ORBIT_LEFT) {
    o->state -= Game::difficulty;
    if (o->state < 0) {
      o->y = Camera::y + random(-150, 150);
      // o->vy = random(-7,7);

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
      o->y = Camera::y + random(-150, 150);
      o->state = 180;
      o->flags |= ORBIT_LEFT;
    }
    else {
      o->theta += 12;
    }
  }

  FLOAT rad = RADIANS(o->state);
  o->x = cos(rad) * 512;
  o->z = Camera::z + sin(rad) * 512;

  if (--o->timer <= 0) {
    o->timer = Game::wave > 10 ? 0 : (20 - Game::wave);
    EBullet::fire(o, EBULLET_BOMB);
  }
}

/**
 * Boss is exploding state.
 */
void Boss::explode(Process *me, Object *o) {
  const WORD NUM_FRAMES = 58;
  o->flags |= OFLAG_EXPLODE;
  o->state++;
  EBullet::genocide(); // Kill all enemy bullets
  // Done exploding, move forward to the next wave
  if (o->state > NUM_FRAMES) {
    game_mode = MODE_NEXT_WAVE;
    Game::kills = 120;
    Camera::vz = 20;

    ProcessManager::birth(Game::next_wave);
    me->suicide();
  }
  else {
    me->sleep(1, explode);
  }
}

void Boss::action(Process *me, Object *o) {
  game_mode = MODE_GAME;
  if (hit(o)) {
    if (Boss::hit_points <= 2) {

      o->flags &= OFLAG_EXPLODE;
      o->state = 0;
      o->vz = Camera::vz;

      me->sleep(1, explode);
      return;
    }
    if (Boss::boss_type == 1) {
      o->y = random(-5, 5);
      o->lines = NULL;
    }
    else if (Boss::boss_type == 2) {
      init_orbit(o, random() & 1);
    }
    else {
      o->lines = NULL;
    }
  }
  else {
    o->lines = getBossLines();
    if (Boss::boss_type == 1) {
      engage_player_random_xy(o);
    }
    else if (Boss::boss_type == 2) {
      engage_player_orbit(o);
    }
    else {
      engage_player_flee(o);
    }
  }

  me->sleep(1);
}

void Boss::start_action(Process *me, Object *o) {

  if (Boss::boss_type == 1) {
    o->y = Camera::y;
    o->z = Camera::z + z_dist;
    if (o->x <= Camera::x) {
      Starfield::init();

      game_mode = MODE_GAME;
      me->sleep(1, action);
    }
    else {
      me->sleep(1);
    }
  }
  else if (Boss::boss_type == 2) {
    if (--o->timer > 0) {
      game_mode = MODE_GAME;
      me->sleep(1, action);
    }
    else {
      me->sleep(1);
    }
  }
  else {
    o->y = Camera::y;
    o->z = Camera::z + z_dist;
    if (o->x >= Camera::x) {
      game_mode = MODE_GAME;
      me->sleep(1, action);
    }
    else {
      me->sleep(1);
    }
  }
}

void Boss::entry(Process *me, Object *o) {
  Boss::boss_type = random(1, 3);

  game_mode = MODE_NEXT_WAVE;
  Game::kills = 0;
  Camera::vz = -20;

  o->set_type(OTYPE_ENEMY);
  o->lines = getBossLines();

  // This too much? :D

  Boss::hit_points = 3 * (Game::difficulty + Boss::boss_type);

  if (Boss::boss_type == 1) {

    o->x = Camera::x + 512;
    o->vx = -10;
    o->y = Camera::y;
    o->z = Camera::z + z_dist;

    Sound::play_score(STAGE_1_BOSS_SONG);
  }
  else if (Boss::boss_type == 2) {

    init_orbit(o, random() & 1);

    Sound::play_score(STAGE_2_BOSS_SONG);
  }
  else {
    init_flee(o);

    Sound::play_score(STAGE_3_BOSS_SONG);
  }

  me->sleep(1, Boss::start_action);
}
