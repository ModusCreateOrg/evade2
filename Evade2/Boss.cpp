#include "Evade2.h"

#include "img/boss_1_img.h"
#include "img/boss_2_img.h"
#include "img/boss_3_img.h"
#include "img/boss_4_img.h"

static const FLOAT z_dist = 256;
static const FLOAT frames = 32;

static BOOL hit(Object *o) {
  if (o->flags & OFLAG_COLLISION) {
    Game::kills++;
    return TRUE;
  }
  return FALSE;
}

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

static void avoid(Object *oo) {
  oo->theta += 5;
  if (--oo->timer > 0) {
    return;
  }
  oo->timer = 15;
  EBullet::fire(oo, EBULLET_BOMB);
  oo->vx = random(-15, 15);
  oo->vy =  random(-15, 15);
}



void Boss::action(Process *me, Object *o) {
  game_mode = MODE_GAME;
  if (hit(o)) {
    if (Game::kills > 30) {
      ProcessManager::genocide();
      game_mode = MODE_NEXT_WAVE;
      Game::kills = 120;
      Camera::vz = 20;
      ProcessManager::birth(Game::next_wave);
      me->suicide();
    }
    o->lines = NULL;
  }
  else {
    // o->lines = boss_2_img; //<-- seems redundant
    avoid(o);
  }
  // o->vy = Camera::vy / 2;
  // o->vx = Camera::vx / 2;
  o->z = Camera::z + z_dist;
  me->sleep(1);
}

void Boss::enter(Process *me, Object *o) {
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

void Boss::entry(Process *me, Object *o) {
  game_mode = MODE_NEXT_WAVE;
  Game::kills = 0;
  Camera::vz = 0;
  o->set_type(OTYPE_ENEMY);
  o->state = 50;
  o->x = Camera::x + 512;
  o->vx = -4;
  o->y = Camera::y;
  o->z = Camera::z + z_dist;
  o->lines = boss_1_img;
  me->sleep(1, Boss::enter);
}
