#include "Game.h"

#include "img/bullet_img.h"

static bool alt = false;
static BYTE num_bullts = 0;

static void wait(Process *me) {
  Object *o = me->o;
  if ((o->flags & OFLAG_COLLISION) || o->z - Camera::z > 256) {
    me->suicide();
    return;
  }
  o->theta -= 15;
  me->sleep(1);
}

void bullet_process(Process *me) {
  Object *o = ObjectManager::alloc();
  if (!o) {
    me->suicide();
    return;
  }
  Sound::play_sound(FIRE_SOUND);
  o->flags |= OFLAG_PLAYER_BULLET;
  o->z = Camera::z;
  if (alt) {
    o->x = Camera::x + 28;
    o->y = Camera::y - 28;
  }
  else {
    o->x = Camera::x - 28;
    o->y = Camera::y - 28;
  }
  alt = !alt;
  o->vz = BULLET_VZ;
  o->lines = bullet_img;
  me->o = o;
  me->sleep(1, wait);
}
