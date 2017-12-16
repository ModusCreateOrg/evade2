#define DEBUGME
//#undef DEBUGME

#include "Evade2.h"

#include "img/ebomb_img.h"
#include "img/ebullet_img.h"

void EBullet::genocide() {
  for (Object *o = ObjectManager::first(); o;) {
    Object *next = o->next;
    if (o->get_type() == OTYPE_ENEMY_BULLET) {
      ObjectManager::free(o);
    }
    o = next;
  }
}

void EBullet::run() {
  for (Object *o = ObjectManager::first(); o;) {
    Object *next = o->next;
    if (o->get_type() == OTYPE_ENEMY_BULLET) {
      // If enemy bullet collides with player
      if (Camera::collides_with(o)) {
        if (game_mode == MODE_GAME) {
          Player::hit(10);
        }
        ObjectManager::free(o);
      }
      else if (o->z < Camera::z || --o->state <= 0) {
        ObjectManager::free(o);
      }
      else {
        // Put a wild spin on the missile
        o->theta += (o->lines == ebomb_img) ? o->x : 40;
      }
    }
    o = next;
  }
}

BOOL EBullet::fire(Object *oo, BYTE type) {
  const FLOAT frames = 64 / Game::difficulty; // time to hit player (how many ticks)

  if (game_mode != MODE_GAME) {
    return FALSE;
  }
  Object *o = ObjectManager::alloc();
  if (!o) {
    return FALSE;
  }

  o->set_type(OTYPE_ENEMY_BULLET);
  o->lines = type == EBULLET_BOMB ? ebomb_img : ebullet_img;

  o->state = 256; // timeout

  Sound::play_sound(SFX_ENEMY_SHOOT);

  // position the bullet
  o->x = oo->x - 8;
  o->y = oo->y - 8; //  - 32;
  o->z = oo->z;
  // fly at the player (where he will be in Z)
  o->vx = (Camera::x - o->x) / frames;
  o->vy = (Camera::y - o->y) / frames;
  o->vz = Camera::vz - (o->z - Camera::z) / frames;
  return TRUE;
}
