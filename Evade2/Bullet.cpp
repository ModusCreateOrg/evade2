#define DEBUGME
//#undef DEBUGME

#include "Evade2.h"

#include "img/bullet_img.h"

void Bullet::genocide() {
  for (Object *o = ObjectManager::first(); o;) {
    Object *next = o->next;
    if (o->get_type() == OTYPE_PLAYER_BULLET) {
      ObjectManager::free(o);
    }
    o = next;
  }
  Player::num_bullets = 0;
}

void Bullet::run() {
  for (Object *o = ObjectManager::first(); o;) {
    Object *next = o->next;
    if (o->get_type() == OTYPE_PLAYER_BULLET) {
      if (o->flags & OFLAG_COLLISION) {
        o->flags &= ~OFLAG_COLLISION;
        o->flags |= OFLAG_EXPLODE;
        o->state = 0;
      }
      else if (o->flags & OFLAG_EXPLODE) {
        o->state++;
        if (o->state > 20) {
          Player::num_bullets--;
          ObjectManager::free(o);
        }
      }
      else if (o->z - Camera::z > 512) {
        Player::num_bullets--;
        ObjectManager::free(o);
      }
      else {
        o->theta += FXP_RADIANS(o->state);
      }
    }
    o = next;
  }
}

void Bullet::fire(BYTE deltaX, BYTE deltaY, BOOL alt) {
  if (Player::num_bullets >= MAX_BULLETS) {
    return;
  }
  Object *o = ObjectManager::alloc();
  if (!o) {
    return;
  }
  Player::num_bullets++;
  Sound::play_sound(SFX_PLAYER_SHOOT);
  o->set_type(OTYPE_PLAYER_BULLET);
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

  o->vx = deltaX;
  o->vy = deltaY;
  alt = !alt;
  o->vz = Camera::vz + BULLET_VZ;
  o->lines = bullet_img;
}
