#define DEBUGME
//#undef DEBUGME

#include "Game.h"

#include "img/bullet_img.h"

// which gun to fire from (true = right)
static bool alt = false;

void Bullet::run() {
  for (Object *o = ObjectManager::first(); o;) {
    Object *next = o->next;
    if ((o->flags & OFLAG_PLAYER_BULLET)) {
      if ((o->flags & OFLAG_COLLISION) || o->z - Camera::z > 512) {
        Player::num_bullets--;
        ObjectManager::free(o);
      }
      else {
        o->theta += o->state;
      }
    }
    o = next;
  }
}

void Bullet::fire() {
  if (Player::num_bullets >= MAX_BULLETS) {
    return;
  }
  Object *o = ObjectManager::alloc();
  if (!o) {
    return;
  }
  Player::num_bullets++;
  Sound::play_sound(FIRE_SOUND);
  o->flags |= OFLAG_PLAYER_BULLET;
  o->z = Camera::z;
  if (alt) {
    o->x = Camera::x + 28;
    o->y = Camera::y - 28;
    o->state = 20;
  }
  else {
    o->x = Camera::x - 28;
    o->y = Camera::y - 28;
    o->state = -20;
  }
  alt = !alt;
  o->vz = BULLET_VZ;
  o->lines = bullet_img;
}
