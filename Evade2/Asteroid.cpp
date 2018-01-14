#include "Evade2.h"

#include "img/environment_asteroid_img.h"

static BOOL alt = FALSE;

static void init_rock(Object *o) {
  if (alt) {
    // off right side
    o->x = Camera::x + (512 - random(0, 512));
    o->state = -4;
  }
  else {
    // off left side
    o->x = Camera::x - (512 - random(0, 512));
    o->state = 4;
  }
  alt = !alt;
  o->y = Camera::y + random(-100, 100);
  o->z = Camera::z + 768;
  o->vz = CAMERA_VZ - 4;
  o->lines = environment_asteroid_img;
}

static BOOL clipped(Object *o) {
  if (o->state > 0) {
    if (o->x > Camera::x + 1024) {
      return TRUE;
    }
  }
  else {
    if (o->x < Camera::x - 1024) {
      return TRUE;
    }
  }
  if (o->z < Camera::z || o->z > (Camera::z + 768)) {
    return TRUE;
  }
  return FALSE;
}

void Asteroid::loop(Process *me, Object *o) {
  if (o->flags & OFLAG_COLLISION) {
    // absorb player bullets
    o->flags &= ~OFLAG_COLLISION;
  }
  if (Camera::collides_with(o)) {
    if (game_mode == MODE_GAME) {
      Player::hit(30);
    }
    // bounce
    // we could have a Asteroid::bounce() loop/state, but this works
    o->vz = Camera::vz + 2;
    o->z = Camera::z + 10;
    o->vx = 8 - random(0, 16);
  }
  else if (clipped(o)) {
    respawn(me, o);
    return;
  }
  o->theta += FXP_RADIANS(16);
  o->vy = Camera::vy / 2;
  me->sleep(1);
}

void Asteroid::delay(Process *me, Object *o) {
  if (--o->timer < 0) {
    init_rock(o);
    me->sleep(1, loop);
    return;
  }
  me->sleep(1);
}

void Asteroid::respawn(Process *me, Object *o) {
  o->lines = NULL;
  o->timer = random(0, 60) + 30;
  me->sleep(1, delay);
}

void Asteroid::entry(Process *me, Object *o) {
  o->set_type(OTYPE_ASTEROID);
  respawn(me, o);
}
