#define DEBUGME
//#undef DEBUGME

#include "Game.h"

#include "img/ebullet_img.h"

void EBullet::wait(Process *me) {
  Object *o = me->o;
  float dz = o->z - Camera::z;

  // If enemy bullet collides with player
  if (abs(dz) < abs(o->vz) && abs(o->x - Camera::x) < 32 && abs(o->y - Camera::y) < 32) {
    Player::flags |= PLAYER_FLAG_HIT;
    Sound::play_sound(PlAYER_HIT_BY_ENEMY);
    me->suicide();
    return;
  }
  if (dz < 0 || --o->state <= 0) {
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
  o->state = 128;

  const FLOAT frames = 64;
  //  Sound::play_sound(ENEMY_FIRE_SOUND);
  o->flags |= OFLAG_ENEMY_BULLET;
  o->lines = ebullet_img;
  o->vx = (Camera::x - o->x) / frames;
  o->vy = (Camera::y - o->y) / frames;

  //  o->vx = (o->x - Camera::x) / frames;
  //  o->vy = (o->y - Camera::y - 32) / frames;
  //  debug("ebullet x,y %f,%f / cx,cy %f,%f / vx,vy %f,%f\n", o->x, o->y, Camera::x, Camera::y, o->vx, o->vy);
  o->vz = Camera::vz - (o->z - Camera::z) / frames;
  me->sleep(1, EBullet::wait);
}
