#include "Game.h"

#include "img/ebullet_img.h"

void EBullet::wait(Process *me) {
  Object *o = me->o;
  if (o->z < Camera::z) {
    me->suicide();
    return;
  }
  o->theta += 40;
  me->sleep(1);
}

void EBullet::ebullet_process(Process *me) {
  Object *o = me->o;
  if (!o) {
    me->suicide();
  }
  const FLOAT frames = 128;
  //  Sound::play_sound(ENEMY_FIRE_SOUND);
  o->flags |= OFLAG_ENEMY_BULLET;
  o->lines = ebullet_img;
  o->vx = (Camera::x - o->x) / 64;
  o->vy = (Camera::y - o->y) / 64;
  //  o->vx = (o->x - Camera::x) / frames;
  //    o->vy = (o->y - Camera::y - 32) / frames;
  o->vz = (o->z - (Camera::z + Camera::vz)) / frames;
  me->sleep(1, EBullet::wait);
}
