#define DEBUGME
//#undef DEBUGME

#include "Game.h"

#include "img/bullet_img.h"

static bool alt = false;
//static BYTE num_bullts = 0;

void Bullet::wait(Process *me) {
  Object *o = me->o;
  if ((o->flags & OFLAG_COLLISION) || o->z - Camera::z > 512) {
    Player::num_bullets--;
    me->suicide();
    return;
  }
  o->theta += o->state;
  me->sleep(1);
}

void Bullet::bullet_process(Process *me) {
  if (Player::num_bullets >= MAX_BULLETS) {
    me->suicide();
    return;
  }
  Object *o = ObjectManager::alloc();
  if (!o) {
    me->suicide();
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
  me->o = o;
  me->sleep(1, Bullet::wait);
}
