#define DEBUGME
//#undef DEBUGME

#include "Game.h"

#include "img/ebullet_img.h"

void EBullet::run() {
  for (Object *o = ObjectManager::first(); o;) {
    Object *next = o->next;
    if (o->flags & OFLAG_ENEMY_BULLET) {
      float dz = o->z - Camera::z;

      // If enemy bullet collides with player
      if (abs(dz) < abs(o->vz) && abs(o->x - Camera::x) < 32 && abs(o->y - Camera::y) < 32) {
        Player::flags |= PLAYER_FLAG_HIT;
        Sound::play_sound(PlAYER_HIT_BY_ENEMY);
        ObjectManager::free(o);
      }
      else if (dz < 0 || --o->state <= 0) {
        ObjectManager::free(o);
      }
      else {
        // Get theta from the final value in the stack of coordinates.
        o->theta += pgm_read_byte(o->lines + (pgm_read_byte(o->lines + 2) * 4) + 3);
      }
    }
    o = next;
  }
}

BOOL EBullet::fire(Object *oo) {
  const FLOAT frames = 64; // time to hit player (how many ticks)

  Object *o = ObjectManager::alloc();
  if (!o) {
    return FALSE;
  }

  o->flags |= OFLAG_ENEMY_BULLET;

  if (random(0, 24) % 2) {
    o->lines = ebullet_img;
  }
  else {
    o->lines = emissile_img;  
  }

  o->state = 128; // timeout

  // TODO: @jaygarcia
  //  Sound::play_sound(ENEMY_FIRE_SOUND);

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
