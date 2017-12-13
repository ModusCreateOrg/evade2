#define DEBUG_ME

#include "Evade2.h"

#include "img/boss_1_img.h"
#include "img/boss_2_img.h"
#include "img/boss_3_img.h"
#include "img/boss_4_img.h"

static const FLOAT z_dist = 256;
static const FLOAT frames = 32;
BYTE Boss::hit_points = 0;


static BOOL hit(Object *o) {
  if (o->flags & OFLAG_COLLISION) {
    Boss::hit_points--; 
    Serial.println(F("Collide"));
    o->flags &= ~OFLAG_COLLISION;
    return TRUE;
  }

  return FALSE;
}

const BYTE getBossType() {
  if (Game::wave % 3 == 0) {
    return 3;
  }
  if (Game::wave % 2 == 0) {
    return 2;
  }
  
  return 1;
}

const BYTE *getBossLines() {
  BYTE bossType = getBossType();;
  if (bossType == 3) {
    return boss_3_img;
  }
  
  if (bossType == 2) {
      return boss_2_img;
  }
   
  return boss_1_img;
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
    o->vz = Camera::vz;
    return TRUE;
  }
  if (game_mode != MODE_GAME) {
    o->vz = 0;
  }
  return FALSE;
}

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

/**
instead of randomizing vx, vy, you can set y to sin(theta)*64 or something like that (edited)

[18:43] 
and change theta over time

[18:43] 
it'll make it a sinusoidal pattern
*/
static void engage_player(Object *oo) {
  // oo->theta += 5;
  if (--oo->timer > 0) {
    return;
  }
  oo->timer = 30;
  EBullet::fire(oo, EBULLET_BOMB);
  oo->vx = random(-7, 7);
  oo->vy = random(-7, 7);
}

/**
 * Boss is exploding state.
 */
void Boss::explode(Process *me, Object *o) {
  const WORD NUM_FRAMES = 58;
  o->flags |= OFLAG_EXPLODE;
  o->state++;
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
    o->y = random(-5, 5);
    o->lines = NULL;
  }
  else {
    o->lines = getBossLines();
    engage_player(o);
  }
  // o->vy = Camera::vy / 2;
  // o->vx = Camera::vx / 2;
  o->z = Camera::z + z_dist;
  me->sleep(1);
}

void Boss::enter(Process *me, Object *o) {
  BYTE bossType = getBossType();

  if (bossType == 1) {
    o->y = Camera::y;
    o->z = Camera::z + z_dist;
    if (o->x <= Camera::x) {
      game_mode = MODE_GAME;
      me->sleep(1, action);
    }
    else {
      me->sleep(1);
    }
  }
  else if (bossType == 2) {
    o->y = Camera::y;
    o->z = Camera::z + z_dist;
    if (o->x <= Camera::x) {
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
    if (o->x <= Camera::x) {
      game_mode = MODE_GAME;
      me->sleep(1, action);
    }
    else {
      me->sleep(1);
    }
  }
}



// void Boss::enter_boss_2(Process *me, Object *o) {
//   o->y = Camera::y;
//   o->z = Camera::z + z_dist;
//   if (o->x <= Camera::x) {
//     game_mode = MODE_GAME;
//     me->sleep(1, action);
//   }
//   else {
//     me->sleep(1);
//   }
// }


// void Boss::enter_boss_3(Process *me, Object *o) {
//   o->y = Camera::y;
//   o->z = Camera::z + z_dist;
//   if (o->x <= Camera::x) {
//     game_mode = MODE_GAME;
//     me->sleep(1, action);
//   }
//   else {
//     me->sleep(1);
//   }
// }




void Boss::entry(Process *me, Object *o) {
  Boss::hit_points = 1; // Todo: HitPoints per boss per wave
  game_mode = MODE_NEXT_WAVE;
  Game::kills = 0;
  Camera::vz = -10;


  o->set_type(OTYPE_ENEMY);
  o->state = 50;
  o->x = Camera::x + 512;
  o->vx = -10;
  o->y = Camera::y;
  o->z = Camera::z + z_dist;
  o->lines = getBossLines();


  BYTE bossType = getBossType();

  if (bossType == 1) {
    Sound::play_score(STAGE_1_BOSS_SONG);
    // me->sleep(1, Boss::enter_boss_1);
  }
  if (bossType == 2) {
    Sound::play_score(STAGE_2_BOSS_SONG);
    // me->sleep(1, Boss::enter_boss_2);
  }
  else {
    Sound::play_score(STAGE_3_BOSS_SONG);
    // me->sleep(1, Boss::entry);
  }

  me->sleep(1, Boss::enter);


 

  
}
